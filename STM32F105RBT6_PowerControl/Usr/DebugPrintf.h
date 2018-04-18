#ifndef __DEBUG_PRINTF_H
#define	__DEBUG_PRINTF_H

#include "stm32f10x.h"
#include <stdio.h>
#include <stdint.h>
#include "uart.h"

#ifdef DEBUG
	#define DEBUG_PRINTF(X,...) printf(X,##__VA_ARGS__)
#else 
	#define DEBUG_PRINTF(X,...) {;}
#endif
		

#endif 
