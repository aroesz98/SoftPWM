/*
 * softpwm.cpp
 *
 *  Created on: Mar 4, 2022
 *      Author: asz
 */

#include "softpwm.h"

SoftPWM::SoftPWM(TIM_HandleTypeDef &htim, GPIO_TypeDef &GPIO_PORT) {
	__port = &GPIO_PORT;
	__tim = &htim;
}

SoftPWM::~SoftPWM() { }

void SoftPWM::init(void) {
	HAL_TIM_Base_Start(__tim);
	HAL_DMA_Start(&hdma_tim1_up, (uint32_t)&(__data[0]), (uint32_t)&(__port->BSRR), data_size);
	__HAL_TIM_ENABLE_DMA(__tim, TIM_DMA_UPDATE);
}

void SoftPWM::setMin(void){
	uint32_t i = 0;
	while(i++ < data_size - 1) __data[i] = 0;
}

void SoftPWM::setMax(void){
	uint32_t i = 0;
	while(i++ < data_size - 1) __data[i] = data_size - 1;
}

void SoftPWM::setPWM(uint16_t pin, uint32_t duty) {
	for (uint32_t i = 0;  i < data_size; ++ i) {
		if(i < duty) {//set pin
			__data[i] &= (uint32_t)~(pin << 16);
			__data[i] |= (uint32_t)pin;
		}

		else {
			__data[i] &= (uint32_t)~(pin);
			__data[i] |= (uint32_t)pin << 16;
		}
	}
}

