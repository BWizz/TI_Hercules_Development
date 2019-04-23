/*
 * MyTasks.h
 *
 *  Created on: Jul 3, 2018
 *      Author: brian.wisniewski
 */
#include "FreeRTOS.h"
#include "het.h"
#include "gio.h"
#include "adc.h"
#include "sci.h"

#include <stdio.h>
#include "os_task.h"
#include "os_queue.h"
#include "os_timer.h"
#include "os_semphr.h"
#include "RPLIDAR.h"

#ifndef INCLUDE_MYTASKS_H_
#define INCLUDE_MYTASKS_H_
extern xQueueHandle queue_handle;
extern xQueueHandle queueRx_handle;
extern TaskHandle_t vRxHandle;
char UART_rx;
#define BUFF_SIZE 100
char Buff[BUFF_SIZE];
void vTaskInit(void);
void vTask1( void * pvParameters );
void vTask2( void * pvParameters );
void vUARTRx( void * pvParameters );
void vUARTTx( void * pvParameters );

#endif /* INCLUDE_MYTASKS_H_ */
