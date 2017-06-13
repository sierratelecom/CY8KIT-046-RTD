/*
 * $Copyright 2017, Sierra Telecom, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Sierra Telecom, Inc.;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Sierra Telecom, Inc.$
 */

/** @file adi_arduino.h
 *
 *  Created on: Feb 23, 2017
 *      Author: greg.phillips
 */
#include <stdint.h> 
#ifndef ADI_ARDUINO_H_
#define ADI_ARDUINO_H_


/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *               Function Definitions
 ******************************************************/
void init_arduino(void);

uint32_t get_uint32_control_data( uint16_t control_no );
int32_t get_int32_sensor_data( uint16_t control_no  );
float get_float_sensor_data( uint16_t control_no  );

void set_uint32_sensor_data( uint16_t sensor_no, uint32_t value );
void set_int32_sensor_data( uint16_t sensor_no, int32_t value );
void set_float_sensor_data( uint16_t sensor_no, float value );

#endif /* ADI_ARDUINO_H_ */

/* [] END OF FILE */
