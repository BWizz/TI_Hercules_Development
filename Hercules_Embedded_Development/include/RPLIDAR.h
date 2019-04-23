/*
 * RPLIDAR.h
 *
 *  Created on: Jul 6, 2018
 *      Author: brian.wisniewski
 */

#include "sys_common.h"
#include "sci.h"
#include "FreeRTOS.h"
#include "os_queue.h"
#ifndef SOURCE_RPLIDAR_H_
#define SOURCE_RPLIDAR_H_
extern xQueueHandle queueSendDebugData_handle;
void vStartScan(void);
void vStopScan(void);
void vAddPacket(uint8 byte);
bool xAddDescriptor(uint8 byte);
float Get_Distance(uint16 idx);
float Get_Angle(uint16 idx);
bool Get_New_Scan_Flag(uint16 idx);

#endif /* SOURCE_RPLIDAR_H_ */
