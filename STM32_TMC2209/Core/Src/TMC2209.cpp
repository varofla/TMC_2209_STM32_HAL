/*
 * TMC2209.cpp
 *
 *  Created on: Oct 26, 2021
 *      Author: dhksr
 */

#include "TMC2209.h"

#include <string.h>
#include <stdio.h>
#include "stm32f1xx_hal.h"

// addresses
#define REG_GCONF           =   0x00
#define REG_GSTAT           =   0x01
#define REG_IFCNT           =   0x02
#define REG_IOIN            =   0x06
#define REG_IHOLD_IRUN      =   0x10
#define REG_TSTEP           =   0x12
#define REG_TCOOLTHRS       =   0x14
#define REG_SGTHRS          =   0x40
#define REG_SG_RESULT       =   0x41
#define REG_MSCNT           =   0x6A
#define REG_CHOPCONF        =   0x6C
#define REG_DRVSTATUS       =   0x6F

// GCONF
#define REG_i_scale_analog      = 1<<0
#define REG_internal_rsense     = 1<<1
#define REG_en_spreadcycle      = 1<<2
#define REG_shaft               = 1<<3
#define REG_index_otpw          = 1<<4
#define REG_index_step          = 1<<5
#define REG_mstep_reg_select    = 1<<7

// GSTAT
#define REG_reset               = 1<<0
#define REG_drv_err             = 1<<1
#define REG_uv_cp               = 1<<2

// CHOPCONF
#define REG_vsense              = 1<<17
#define REG_msres0              = 1<<24
#define REG_msres1              = 1<<25
#define REG_msres2              = 1<<26
#define REG_msres3              = 1<<27
#define REG_intpol              = 1<<28

// IOIN
#define REG_io_enn              = 1<<0
#define REG_io_step             = 1<<7
#define REG_io_spread           = 1<<8
#define REG_io_dir              = 1<<9

// DRVSTATUS
#define REG_stst                = 1<<31
#define REG_stealth             = 1<<30
#define REG_cs_actual           = 31<<16
#define REG_t157                = 1<<11
#define REG_t150                = 1<<10
#define REG_t143                = 1<<9
#define REG_t120                = 1<<8
#define REG_olb                 = 1<<7
#define REG_ola                 = 1<<6
#define REG_s2vsb               = 1<<5
#define REG_s2vsa               = 1<<4
#define REG_s2gb                = 1<<3
#define REG_s2ga                = 1<<2
#define REG_ot                  = 1<<1
#define REG_otpw                = 1<<0

// IHOLD_IRUN
#define REG_ihold               = 31<<0
#define REG_irun                = 31<<8
#define REG_iholddelay          = 15<<16

// SGTHRS
#define REG_sgthrs              = 255<<0

// others
#define REG_mres_256 = 0
#define REG_mres_128 = 1
#define REG_mres_64 = 2
#define REG_mres_32 = 3
#define REG_mres_16 = 4
#define REG_mres_8 = 5
#define REG_mres_4 = 6
#define REG_mres_2 = 7
#define REG_mres_1 = 8

TMC2209::TMC2209(TMC2209_InitTypeDef *TMC2209_InitStruct) {
	m_UART_TMC = TMC2209_InitStruct->UART_TMC;
	m_UART_DEBUG = TMC2209_InitStruct->UART_DEBUG;
    m_GPIOx_STEP = TMC2209_InitStruct->GPIOx_STEP;
    m_GPIO_Pin_STEP = TMC2209_InitStruct->GPIO_Pin_STEP;
    m_GPIOx_DIR = TMC2209_InitStruct->GPIOx_DIR;
    m_GPIO_Pin_DIR = TMC2209_InitStruct->GPIO_Pin_DIR;
    m_GPIOx_EN = TMC2209_InitStruct->GPIOx_EN;
    m_GPIO_Pin_EN = TMC2209_InitStruct->GPIO_Pin_EN;
    m_GPIOx_DIAG = TMC2209_InitStruct->GPIOx_DIAG;
    m_GPIO_Pin_DIAG = TMC2209_InitStruct->GPIO_Pin_DIAG;
}

TMC2209::~TMC2209() {

}

bool TMC2209::read_reg(uint8_t reg) {
	uint8_t buffer[9] = {0};
	uint8_t out[4] = {0};
	for(int i = 0; i<9; i++) {
		buffer[i] = 1;
	}

	m_UART_rFrame[1] = m_mtr_id;
	m_UART_rFrame[2] = reg;
	// crc8 체크
	uint8_t crc = 0;
	for(int i = 0; i < 3; i++) {
		uint8_t byte = m_UART_rFrame[i];
		for(int j = 0; j < 8; j++) {
			if((crc >> 7) ^ (byte & 0x01)) {
				crc = ((crc << 1) ^ 0x07) & 0xFF;
			} else {
				crc = (crc << 1) & 0xFF;
			}
			byte = byte >> 1;
		}
	}
	m_UART_rFrame[3] = crc;

	HAL_UART_Transmit(m_UART_TMC, m_UART_rFrame, 4, m_UART_communication_timeout);

//	HAL_Delay(6);

	HAL_UART_Receive(m_UART_TMC, buffer, 9, m_UART_communication_timeout);

	memcpy(out, buffer+4, 4);
	HAL_UART_Transmit(m_UART_DEBUG, out, 4, m_UART_communication_timeout);

	if()

	return true;
}

void TMC2209::test() {
	uint8_t buffer[256];
	sprintf((char *)buffer, "Hello, World!\n");
	HAL_UART_Transmit(m_UART_DEBUG, buffer, strlen((char *)buffer), 100);
}

void TMC2209::test2() {
	this->read_reg(0x06);
}
