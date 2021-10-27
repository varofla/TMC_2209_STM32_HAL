/*
 * TMC2209.h
 *
 *  Created on: Oct 26, 2021
 *      Author: dhksr
 */

#ifndef TMC2209_H_
#define TMC2209_H_

#include "stm32f1xx_hal.h"

typedef struct {
	UART_HandleTypeDef *UART_TMC;
	GPIO_TypeDef *GPIOx_STEP;
	uint16_t GPIO_Pin_STEP;
	GPIO_TypeDef *GPIOx_DIR;
	uint16_t GPIO_Pin_DIR;
	GPIO_TypeDef *GPIOx_EN;
	uint16_t GPIO_Pin_EN;
	GPIO_TypeDef *GPIOx_DIAG;
	uint16_t GPIO_Pin_DIAG;
	UART_HandleTypeDef *UART_DEBUG;
} TMC2209_InitTypeDef;

class TMC2209 {
private:
	//------------------------------------
	// TMC2209 통신 및 배선
	//------------------------------------
	UART_HandleTypeDef *m_UART_TMC;
	UART_HandleTypeDef *m_UART_DEBUG;
	GPIO_TypeDef *m_GPIOx_STEP;
	uint16_t m_GPIO_Pin_STEP;
	GPIO_TypeDef *m_GPIOx_DIR;
	uint16_t m_GPIO_Pin_DIR;
	GPIO_TypeDef *m_GPIOx_EN;
	uint16_t m_GPIO_Pin_EN;
	GPIO_TypeDef *m_GPIOx_DIAG;
	uint16_t m_GPIO_Pin_DIAG;


	//------------------------------------
	// UART 관련 변수
	//------------------------------------
	uint8_t m_mtr_id = 0;
	uint8_t m_UART_rFrame[4] = {0x55, 0, 0, 0};
	uint8_t m_UART_wFrame[8] = {0x55, 0, 0, 0 , 0, 0, 0, 0};
	uint16_t m_UART_communication_pause = 4340; // int(500/baudrate*1000000)
	uint16_t m_UART_communication_timeout = 173; // int(20000/baudrate*1000)


public:
	TMC2209(TMC2209_InitTypeDef *TMC2209_InitStruct);
	virtual ~TMC2209();
	bool read_reg(uint8_t reg);


	void test();
	void test2();

};



#endif /* TMC2209_H_ */
