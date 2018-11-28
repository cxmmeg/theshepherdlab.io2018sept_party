/*
*********************************************************************************************************
*
*	模块名称 : 利用STM32F4内部TIM输出PWM信号，顺便实现
*	文件名称 : bsp_tim_pwm.h
*	版    本 : V1.0
*	说    明 : 头文件
*
*	Copyright (C), 2012-2013, 
*
*********************************************************************************************************
*/

#ifndef __BSP_TIM_PWM_H__
#define __BSP_TIM_PWM_H__

void bsp_SetTIMOutPWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, TIM_TypeDef* TIMx, uint8_t _ucChannel,
	uint32_t _ulFreq, uint32_t _ulDutyCycle);

void bsp_SetTIMOutPWM_N(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, TIM_TypeDef* TIMx, uint8_t _ucChannel,
	uint32_t _ulFreq, uint32_t _ulDutyCycle);

void bsp_TIM_Init(TIM_TypeDef* TIMx, uint32_t _ulFreq, uint8_t _PreemptionPriority, uint8_t _SubPriority);

uint32_t bsp_GetRCCofGPIO(GPIO_TypeDef* GPIOx);
uint16_t bsp_GetPinSource(uint16_t gpio_pin);

#endif

/***************************** (END OF FILE) *********************************/
