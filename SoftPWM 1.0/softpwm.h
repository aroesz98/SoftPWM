/*
 * servo.h
 *
 *  Created on: Mar 4, 2022
 *      Author: asz
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "stm32f4xx_hal.h"
#include "dma.h"
#include "tim.h"

extern DMA_HandleTypeDef hdma_tim1_up;

class SoftPWM {
	private:
		uint32_t data_size = 1000;
		uint32_t *__data = new uint32_t[data_size];
		GPIO_TypeDef *__port;
		TIM_HandleTypeDef *__tim;
	public:
		SoftPWM(TIM_HandleTypeDef &htim, GPIO_TypeDef &GPIO_PORT);
		~SoftPWM();
		void init(void);
		void setMin(void);
		void setMax(void);
		void setPWM(uint16_t pin, uint32_t duty);
};



#endif /* INC_SERVO_H_ */
