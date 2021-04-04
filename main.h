/*
 * main.h
 *
 *  Created on: Apr 4, 2021
 *      Author: grantweiss
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "stm32l0xx.h"

typedef struct
{
  __IO uint32_t ISR;          /*!< ADC Interrupt and Status register,                          Address offset:0x00 */
  __IO uint32_t IER;          /*!< ADC Interrupt Enable register,                              Address offset:0x04 */
  __IO uint32_t CR;           /*!< ADC Control register,                                       Address offset:0x08 */
  __IO uint32_t CFGR1;        /*!< ADC Configuration register 1,                               Address offset:0x0C */
  __IO uint32_t CFGR2;        /*!< ADC Configuration register 2,                               Address offset:0x10 */
  __IO uint32_t SMPR;         /*!< ADC Sampling time register,                                 Address offset:0x14 */
  __IO uint32_t testArr[10];
} eeprom_config_t;

#define eeprom_config ((eeprom_config_t *)DATA_EEPROM_BASE)

#define EEPROM_READ(addr, dest) Eeprom_Read_Obj((uint8_t *) &(addr), (uint8_t *)&dest, (uint16_t) sizeof(dest))
#define EEPROM_WRITE(addr, dest) Eeprom_Write_Obj((uint8_t *) &(addr), (uint8_t *)&dest, (uint16_t) sizeof(dest))

#define EEPROM_READ_OBJ(addr, dest) Eeprom_Read_Obj((uint8_t *)(addr), (uint8_t *)&dest, (uint16_t) sizeof(dest))
#define EEPROM_WRITE_OBJ(addr, dest) Eeprom_Write_Obj((uint8_t *)(addr), (uint8_t *)&dest, (uint16_t) sizeof(dest))

#endif /* MAIN_H_ */
