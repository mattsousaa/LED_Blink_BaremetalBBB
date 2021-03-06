#ifndef GPIO_H_
#define GPIO_H_

/*
 * =====================================================================================
 *
 *       Filename:  gpio.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/02/2017 10:39:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include "clock_module.h"
#include "control_module.h"
#include "pad.h"
#include "soc_AM335x.h"
#include "hw_types.h"

#define GPIO_REVISION           0x000
#define GPIO_SYSCONFIG          0x010
#define GPIO_EOI                0x020
#define GPIO_IRQSTATUS_RAW_0    0x024
#define GPIO_IRQSTATUS_RAW_1    0x028
#define GPIO_IRQSTATUS_0        0x02C
#define GPIO_IRQSTATUS_1        0x030
#define GPIO_IRQSTATUS_SET_0    0x034
#define GPIO_IRQSTATUS_SET_1    0x038
#define GPIO_IRQSTATUS_CLR_0    0x03C
#define GPIO_IRQSTATUS_CLR_1    0x040
#define GPIO_IRQWAKEN_0         0x044
#define GPIO_IRQWAKEN_1         0x048
#define GPIO_SYSSTATUS          0x114
#define GPIO_CTRL               0x130
#define GPIO_OE                 0x134
#define GPIO_DATAIN             0x138
#define GPIO_DATAOUT            0x13C
#define GPIO_LEVELDETECT0       0x140
#define GPIO_LEVELDETECT1       0x144
#define GPIO_RISINGDETECT       0x148
#define GPIO_FALLINGDETECT      0x14C
#define GPIO_DEBOUNCENABLE      0x150
#define GPIO_DEBOUNCINGTIME     0x154
#define GPIO_CLEARDATAOUT       0x190
#define GPIO_SETDATAOUT         0x194



/*-----------------------------------------------------------------------------
 *  GPIO pin number type (0-31)
 *-----------------------------------------------------------------------------*/
typedef unsigned char ucPinNumber;

/*-----------------------------------------------------------------------------
 *  init ENUMs
 *-----------------------------------------------------------------------------*/
typedef enum _pinLevel{
	LOW,
	HIGH
}pinLevel;				/* ----------  end of enum pinLevel  ---------- */

typedef enum _gpioPin{
	GPIO0,
	GPIO1,
	GPIO2,
	GPIO3,
	GPIO4,
	GPIO5,
	GPIO6,
	GPIO7,
	GPIO8,
	GPIO9,
	GPIO10,
	GPIO11,
	GPIO12,
	GPIO13,
	GPIO14,
	GPIO15,
	GPIO16,
	GPIO17,
	GPIO18,
	GPIO19,
	GPIO20,
	GPIO21,
	GPIO22,
	GPIO23,
	GPIO24,
	GPIO25,
	GPIO26,
	GPIO27,
	GPIO29,
	GPIO30,
	GPIO31
}gpioPins;				/* ----------  end of enum gpioPort  ---------- */


typedef enum _gpioPort{
	MODULE0,
	MODULE1,
	MODULE2,
	MODULE3
}gpioPort;				/* ----------  end of enum gpioPort  ---------- */

typedef enum _pinDirection{
	OUTPUT,
	INPUT
}pinDirection;				/* ----------  end of enum pinDirection  ---------- */



/*-----------------------------------------------------------------------------
 *  Function prototype
 *-----------------------------------------------------------------------------*/
void gpioInitModule(gpioPort );
void gpioInitPin(gpioPort ,ucPinNumber );
void gpioSetDirection(gpioPort ,ucPinNumber ,pinDirection );	
int  gpioGetDirection(ucPinNumber ,ucPinNumber );
void gpioSetPinValue(gpioPort ,ucPinNumber ,pinLevel );
unsigned int gpioGetPinValue(gpioPort ,ucPinNumber );
	
#endif /*GPIO_H_ */
