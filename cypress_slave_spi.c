/*
 * Copyright 2017, Sierra Telecom. All Rights Reserved.
 *
 * This software, associated documentation and materials ("Software"),
 * is owned by Sierra Telecom ("Sierra") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Sierra hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Sierra's
 * integrated circuit products. Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Sierra.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Sierra
 * reserves the right to make changes to the Software without notice. Sierra
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Sierra does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Sierra product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Sierra's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Sierra against all liability.
 */
/** @file cypress_slave_spi.c
 *
 *  Created on: April 26, 2017
 *      Author: greg.phillips
 */



#include <project.h>
#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "leds.h"
#include "cypress_slave_spi.h"
#include "arduino.h"
/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/
#define     DESCR0              0
#define     DESCR1              1
#define     BUFFER_SIZE         3

/* Packet size */
#define PACKET_SIZE      (3u)

/* Byte position within the packet */
#define PACKET_SOP_POS  (0u)
#define PACKET_CMD_POS  (1u)

/* Command and status share the same offset */
#define PACKET_STS_POS  (PACKET_CMD_POS)
#define PACKET_EOP_POS  (2u)

/* Start and end of the packet markers */
#define PACKET_SOP      (0x01u)
#define PACKET_EOP      (0x17u)

/* Command execution status */
#define STS_CMD_DONE    (0x00u)
#define STS_CMD_FAIL    (0xFFu)

/* Commands */
#define CMD_SET_OFF     (0u)
#define CMD_SET_RED     (1u)
#define CMD_SET_GREEN   (2u)
#define CMD_SET_BLUE    (3u)
#define CMD_SET_UNKNOWN (0xFFu)

#define SOH     0x02
#define EOT     0x04

/******************************************************
 *                   Enumerations
 ******************************************************/
enum {
   SPI_INIT,
   SPI_GET_CMD,
   SPI_READ_CMD,
   SPI_READ_BYTES,
   SPI_WRITE_BYTES,
};
/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *               Function Declarations
 ******************************************************/
/* SPIS functions */

/* Executes command and returns status */
static uint16_t SPI_read( uint16_t no_bytes );
static uint16_t SPI_write( uint8_t *ptr, uint16_t no_bytes );
static bool spi_read_command_complete(void);
static bool spi_read_complete(void);
static bool spi_write_complete(void);
/******************************************************
 *               Variable Definitions
 ******************************************************/
/* Data buffers */
/* Data buffers */

static uint8_t command_tx_buffer[ MAX_SPI_RESPONSE + 2 ];
static uint8_t command_rx_buffer[ MAX_SPI_RESPONSE + 2 ];
/* 
* This dummy buffer used by SPIS when it receives command packet.
*/
uint8_t dummyBuffer[PACKET_SIZE] = {0x03u, 0x02u, 0x00u};

uint32_t spi_nops = 0, no_commands, no_reads, no_writes;
static uint16_t spi_state = SPI_INIT;
static arduino_config_t local_acb;

static uint8_t spi_cmd[ SPI_COMMAND_LENGTH ];

extern arduino_config_t acb;

static bool look_for_SOH = true;
static bool look_for_EOT = false;
static uint32_t rx_buffer_index = 0;
static uint32_t rx_length = 0;

/******************************************************
 *               Function Definitions
 ******************************************************/
/**
  * @brief Process any SPI events
  * @param  None
  * @retval : None
  */
static bool clear_status = false;

void process_slave_spi(void)
{
   uint8_t *ptr;
   uint16_t no_bytes;

   switch( spi_state ) {
        case SPI_INIT :
            /*
             * Set up to receive a command
             */
            no_commands = 0;
            no_reads = 0;
            no_writes = 0;
            spi_state = SPI_GET_CMD;
            break;
        case SPI_GET_CMD :
            /*
             * Set up for next read
             */
            ptr = (uint8_t *) &spi_cmd;
            no_bytes = SPI_COMMAND_LENGTH;
            SPI_read( no_bytes );
            spi_state = SPI_READ_CMD;
            break;
        case SPI_READ_CMD :
            if( ( spi_read_command_complete() == true ) ) {
                RGB_LED_ON_GREEN;
                no_commands += 1;
                /*
                 * Device is in Read command mode and has received a 3 byte command
                 */
                if( spi_cmd[ SPI_COMMAND ] == SPI_READ_REGS ) {
                    /*
                     * Set the pointer to the registers in the control block requested.
                     * Make sure that the register selected and length is correct to prevent reading from other parts of memory
                     */
                    if( ( spi_cmd[ SPI_REGISTER ] > SPI_SENSOR_7 ) || ( spi_cmd[ SPI_LENGTH ] > ( spi_cmd[ SPI_REGISTER ] + SPI_MAX_BYTE ) ) ) {
                        no_bytes = 1;
                        ptr = (uint8_t *) &spi_cmd;        // return 0xFF and clock will get all 0xFF from non responding device
                        spi_cmd[ 0 ] = 0xFF;
                    } else {
                        ptr = (uint8_t *)( &acb ) + (uint32_t) ( spi_cmd[ SPI_REGISTER ] * ARDUINO_REG_LENGTH );
                        if( spi_cmd[ SPI_REGISTER ] == SPI_CSR_SLAVE ) {
                            /*
                             * If reading the Status register, clear it after reading
                             */
                            clear_status = true;
                        }
                        no_bytes = spi_cmd[ SPI_LENGTH ];
                    }
                    // printf( "Read Reg: %u, Bytes: %u\r\n", (uint16_t) spi_cmd[ SPI_REGISTER ], no_bytes );

                    spi_state = SPI_WRITE_BYTES;
                } else if( spi_cmd[ SPI_COMMAND ] == SPI_WRITE_REGS ) {
                    /*
                    * Set the pointer to the registers in the control block requested.
                    * Make sure that the register selected and length is correct to prevent reading from other parts of memory
                    */
                    if(spi_cmd[ SPI_REGISTER ] > SPI_MAX_BYTE ) {
                        no_bytes = 1;
                        ptr = (uint8_t *) &spi_cmd;        // return 0xFF and clock will get all 0xFF from non responding device
                        spi_cmd[ 0 ] = 0xFF;
                    } else {
                        ptr = (uint8_t *)( &local_acb ) + ( spi_cmd[ SPI_REGISTER ] * ARDUINO_REG_LENGTH );
                            if( spi_cmd[ SPI_LENGTH ] > ( spi_cmd[ SPI_REGISTER ] + SPI_MAX_BYTE ) )
                                no_bytes = ( SPI_MAX_BYTE - spi_cmd[ SPI_REGISTER ] );  // Just transfer end of registers
                            else
                                no_bytes = spi_cmd[ SPI_LENGTH ];
                    }
                    spi_state = SPI_READ_BYTES;
                } else {
                    /*
                    * Ignore unknown commands
                    */
                    ptr = (uint8_t *) &spi_cmd;
                    no_bytes = SPI_COMMAND_LENGTH;
                }
                if( spi_state == SPI_READ_BYTES ) {
                    /*
                     * Set up to receive more data
                     */
                    SPI_read( no_bytes );
                } else {
                     /*
                     * Set up to send back data
                     */
                    SPI_write( ptr, no_bytes );
                }
            }
            break;
        case SPI_READ_BYTES :
            if( ( spi_read_complete() == true ) ) {
                RGB_LED_ON_BLUE;
                no_reads += 1;
                /*
                * Master has read - go back to get command
                */
                spi_state = SPI_GET_CMD;
            }
            break;
        case SPI_WRITE_BYTES :
            if( ( spi_write_complete() == true ) ) {
                no_writes += 1;
                RGB_LED_ON_RED;
                /*
                 * Master has written - process updates
                 */
                spi_state = SPI_GET_CMD;
            }
            break;
        default :
            /*
             * Ignore unknown transfers and return to waiting for a command, this will catch NOPs and ensure that system is ready for a command
             */
            spi_state = SPI_INIT;
            break;
    }
    
}
void init_slave_spi(void)
{

    /* Start SPI communication. */
    SPIS_Start();
    
}
uint32_t SPI_rx_count(void)
{
    return 0;
}
uint32_t SPI_tx_count(void)
{
    return 0;
}
uint32_t SPI_nops_count(void)
{
    return 0;
}
static uint16_t SPI_read( uint16_t no_bytes )
{
    if( no_bytes < MAX_SPI_RESPONSE ) {
        rx_length = no_bytes;
        /*
         * Fill the TX Buffer with dummy data to allow reception
         */
        memset( &command_tx_buffer, 0x55, no_bytes + 2 );
        SPIS_SpiUartPutArray( (uint8 *) &command_tx_buffer, no_bytes + 2 );
        return true;
    } else 
        return true;
}
static uint16_t SPI_write( uint8_t *ptr, uint16_t no_bytes )
{
    if( no_bytes < MAX_SPI_RESPONSE ) {
        command_tx_buffer[ 0 ] = SOH;
        memcpy( &command_tx_buffer[ 1 ], ptr, no_bytes );
        command_tx_buffer[ no_bytes + 1 ] = EOT;
        if( clear_status == true ) {
            acb.slave.status = 0;
            clear_status = false;
        }
        SPIS_SpiUartPutArray( (uint8 *) &command_tx_buffer, no_bytes + 2 ); 
        return true;
    } else 
        return false;
}

static bool spi_read_command_complete(void)
{
    uint8_t data;
    
    if( SPIS_SpiUartGetRxBufferSize() == 0 )
    {
        return false;
    }

    if( look_for_SOH ) {
        do {
            if( SPIS_SpiUartReadRxData() == SOH ) {
                look_for_SOH = false;
                look_for_EOT = false;
                rx_buffer_index = 0;
            }
        } while( look_for_SOH && ( SPIS_SpiUartGetRxBufferSize() != 0 ) );
    }    
    
    if( SPIS_SpiUartGetRxBufferSize() == 0 )
    {
        return false;
    }
    /*
     * Get any data
     */
    
    do {
        data = SPIS_SpiUartReadRxData();
        if( look_for_EOT ) {
            if( data == EOT ) {
                memcpy( &spi_cmd, &command_rx_buffer, SPI_COMMAND_LENGTH );
                look_for_SOH = true;
                return true;
            } else {
                look_for_SOH = true;
                return false;
            }
        } 
        command_rx_buffer[ rx_buffer_index++ ] = data;

        if( rx_buffer_index == SPI_COMMAND_LENGTH ) {
            look_for_EOT = true;
        } 
    } while( !look_for_SOH && ( SPIS_SpiUartGetRxBufferSize() != 0 ) );
    
    return false;
    
}

static bool spi_read_complete(void)
{
    uint8_t data;
    
    if( SPIS_SpiUartGetRxBufferSize() == 0 )
    {
        return false;
    }

    if( look_for_SOH ) {
        do {
            if( SPIS_SpiUartReadRxData() == SOH ) {
                look_for_SOH = false;
                look_for_EOT =  false;
                rx_buffer_index = 0;
            }
        } while( look_for_SOH && ( SPIS_SpiUartGetRxBufferSize() != 0 ) );
    }    
    
    if( SPIS_SpiUartGetRxBufferSize() == 0 )
    {
        return false;
    }
    /*
     * Get any data
     */
    
    do {
        data = SPIS_SpiUartReadRxData();
        if( data == EOT ) {
            memcpy( &spi_cmd, &command_rx_buffer, SPI_COMMAND_LENGTH );
            return true;
        }
        command_rx_buffer[ rx_buffer_index++ ] = data;

        if( rx_buffer_index == SPI_COMMAND_LENGTH ) {
            look_for_EOT = true;
        } 
    } while( !look_for_SOH && ( SPIS_SpiUartGetRxBufferSize() != 0 ) );
    
    return false;
    
}

bool spi_write_complete(void)
{
    if( SPIS_SpiUartGetTxBufferSize() == 0  ) {
        /*
         * Dump all data in RX buffer as it was just dummy data recevied during transmission of last packet
         */
        SPIS_SpiUartClearRxBuffer();
        return true;
    } else
        return false;
}

/* [] END OF FILE */
