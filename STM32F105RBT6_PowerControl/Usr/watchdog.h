#ifndef __WATCHDOG_H
#define	__WATCHDOG_H


#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>

#include "stm32f10x_iwdg.h"

void WatchDog_Init(void);
void FeedDog(void);

#endif /* __WATCHDOG_H */
