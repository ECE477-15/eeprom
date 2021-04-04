/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32l0xx.h"
#include "stm32l0538_discovery.h"
#include "main.h"

void Eeprom_Write_Obj(uint8_t *wAddr, uint8_t *obj, uint16_t size);
void Eeprom_Read_Obj (uint8_t *wAddr, uint8_t *obj, uint16_t size);

int main(void)
{
	// Read and write entire struct
	eeprom_config_t writeConfig = {};
	writeConfig.ISR = 218;
	writeConfig.SMPR = 3129;
	EEPROM_WRITE_OBJ(eeprom_config, writeConfig);

	eeprom_config_t readConfig = {0};
	EEPROM_READ_OBJ(eeprom_config, readConfig);

	// Read and write parts of a struct
	uint32_t writeISR = 12345;
	EEPROM_WRITE(eeprom_config->ISR, writeISR);

	uint8_t readISR;
	EEPROM_READ(eeprom_config->ISR, readISR);

	uint32_t read_direct = eeprom_config->ISR;
	UNUSED(read_direct);

	// Read and write array in struct
	uint32_t writeArr1[10] = {9,8,7,6,5,4,3,2,1,0};
	EEPROM_WRITE(eeprom_config->testArr, writeArr1);

	uint32_t readArr1[10] = {0};
	EEPROM_READ(eeprom_config->testArr, readArr1);

	// Read and write array
	uint32_t writeArr[10] = {0,1,2,3,4,5,6,7,8,9};
	EEPROM_WRITE_OBJ((DATA_EEPROM_BASE+128), writeArr);

	uint32_t readArr[10] = {0};
	EEPROM_READ_OBJ((DATA_EEPROM_BASE+128), readArr);

//	assert(writeISR == readISR);
	for(;;);
}

void Eeprom_Write_Obj(uint8_t *wAddr, uint8_t *obj, uint16_t size) {
	if((FLASH->PECR & FLASH_PECR_PELOCK) != RESET) {
		/* Disable interrupts to avoid any interruption during unlock sequence */
		  uint32_t primask_bit = __get_PRIMASK();
		__disable_irq();

		/* Unlocking the Data memory and FLASH_PECR register access*/
		FLASH->PEKEYR = ((uint32_t)0x89ABCDEFU);
		FLASH->PEKEYR = ((uint32_t)0x02030405U);

		/* Re-enable the interrupts: restore previous priority mask */
		__set_PRIMASK(primask_bit);

		if((FLASH->PECR & FLASH_PECR_PELOCK) != RESET) {
//			error(); // TODO
		}
	}

    uint8_t *ptr = (uint8_t *)obj;

    for (uint8_t i=0;i<size;i++)
    	*(wAddr++) = *(ptr++);

    SET_BIT(FLASH->PECR, FLASH_PECR_PELOCK);
}

void Eeprom_Read_Obj(uint8_t *wAddr, uint8_t *obj, uint16_t size) {
	while(size--) {
		*obj++ = *wAddr++;
	}
}

