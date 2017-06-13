/*
 * $Copyright 2017, Sierra Telecom, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Sierra Telecom, Inc.;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Sierra Telecom, Inc.$
 */

/** @file integrated.h
 *
 *  Created on: April 26, 2017
 *      Author: greg.phillips
 */

#include <stdint.h>

#ifndef ARDUINO_H_
#define ARDUINO_H_


/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/
/*
 * Define the Arduino Code used for this system
 */
#define IMATRIX_ARDUINO_CODE    0x02
#define SPI_COMMAND_LENGTH 	    3
#define MAX_SPI_RESPONSE        40
#define SPI_COMMAND             0
#define SPI_REGISTER            1
#define SPI_LENGTH              2
/*
 * Define SPI interface commands
 */
#define SPI_NOP			        0
#define SPI_WRITE_REGS	        1
#define SPI_READ_REGS	        2
#define ARDUINO_REG_LENGTH	    4

/*
 * Define SPI interface commands
 */
#define SPI_NOP         0
#define SPI_WRITE_REGS  1
#define SPI_READ_REGS   2
#define ARDUINO_REG_LENGTH 4
/*
 * Define values for CSR
 */
#define  ARDUINO_NO_CHANGE 0  // – All operating normally – No update
#define  ARDUINO_NEW_VALUE 1  // – New value stored
#define  ARDUINO_ERROR     2  // – Control/Sensor is in Error
#define  ARDUINO_UNDEFINED 3  // – Undefined Control/Sensor
/*
 * Define Registers
 */
#define SPI_CONFIG_REG  0  // Configuration Register
#define SPI_SYS_STATUS  1  // System Status Code
#define SPI_ARD_STATUS  2  // Arduino Status Code (Read Only from ConnectKit)
#define SPI_CSR_MASTER  3  // Control / Sensor Status Register - Master
#define SPI_CSR_SLAVE   4  // Control / Sensor Status Register – Slave (Read Only from ConnectKit)
#define SPI_CONTROL_0   5  // 4-12  Control Values (Read / Write)
#define SPI_CONTROL_1   6
#define SPI_CONTROL_2   7
#define SPI_CONTROL_3   8
#define SPI_CONTROL_4   9
#define SPI_CONTROL_5   10
#define SPI_CONTROL_6   11
#define SPI_CONTROL_7   12
#define SPI_SENSOR_0 13 // 13-20 Sensor Values (Read Only from ConnectKit)
#define SPI_SENSOR_1 14
#define SPI_SENSOR_2 15
#define SPI_SENSOR_3 16
#define SPI_SENSOR_4 17
#define SPI_SENSOR_5 18
#define SPI_SENSOR_6 19
#define SPI_SENSOR_7 20
#define SPI_MAX_BYTE ( ( SPI_SENSOR_7 * ARDUINO_REG_LENGTH ) + ARDUINO_REG_LENGTH )
/*
 *    Define the number of controls and sensors in the system
 *
 */
#define MAX_ARDUINO_CONTROLS    8
#define MAX_ARDUINO_SENSORS     8

#define NO_ARDUINO_CONTROLS     3
#define NO_ARDUINO_SENSORS      5
/*
 * Define IDs for Controls & Sensor - will come from Online DB later
 */
#define ACONTROL_LED_RED_ID     0x10
#define ACONTROL_LED_GREEN_ID   0x11
#define ACONTROL_LED_BLUE_ID    0x12

#define ACB_LED_RED_ID          0x00
#define ACB_LED_GREEN_ID        0x01
#define ACB_LED_BLUE_ID         0x02
/*
 * Define Sensor IDs for our sensors - From master database online
 */
#define ASENSOR_TEMP            0x10

#define ASCB_SENSOR_TEMP            0x00
#define ASCB_SENSOR_CURRENT_SOURCE  0x01
#define ASCB_SENSOR_CAL_VOLTAGE     0x02
#define ASCB_SENSOR_RTD_VOLTAGE     0x03
#define ASCB_SENSOR_SWITCH          0x04

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/
typedef struct {
   unsigned int cfg             : 1;
   unsigned int reserved        : 7;
   unsigned int arduino_code    : 16;
   unsigned int no_controls     : 4;
   unsigned int no_sensors      : 4;
} device_configuration_t;

typedef struct {
         unsigned int cs7     : 2;
         unsigned int cs6     : 2;
         unsigned int cs5     : 2;
         unsigned int cs4     : 2;
         unsigned int cs3     : 2;
         unsigned int cs2     : 2;
         unsigned int cs1     : 2;
         unsigned int cs0     : 2;
         unsigned int ss7     : 2;
         unsigned int ss6     : 2;
         unsigned int ss5     : 2;
         unsigned int ss4     : 2;
         unsigned int ss3     : 2;
         unsigned int ss2     : 2;
         unsigned int ss1     : 2;
         unsigned int ss0     : 2;
} bits_t;

typedef union {
      uint32_t uint_32bit;
      int32_t int_32bit;
      float float_32bit;
} data_t;

typedef struct {
   device_configuration_t config;
   uint32_t system_status_code;
   uint32_t arduino_status_code;
   union {
      bits_t bits;
      uint32_t status;
   } master;
   union {
      bits_t bits;
      uint32_t status;
   } slave;
   data_t data_controls[ MAX_ARDUINO_CONTROLS ];
   data_t data_sensors[ MAX_ARDUINO_SENSORS ];
} arduino_config_t;

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *               Function Definitions
 ******************************************************/

#endif /* ARDUINO_H_ */

/* [] END OF FILE */
