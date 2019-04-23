#include "MyTasks.h"
xQueueHandle queue_handle = NULL;
xQueueHandle queueSendDebugData_handle = NULL;
xQueueHandle queueRx_handle = NULL;
TaskHandle_t vTask1_handle;
TaskHandle_t vTask2_handle;
TaskHandle_t vRxHandle = NULL;
//uint8 Data_g = 0;

void vTaskInit(void){
    sciReceive(sciREG,1,(uint8 *) &UART_rx);
    queue_handle = xQueueCreate(1,sizeof(int));
    queueRx_handle = xQueueCreate(1024,sizeof(uint8));
    queueSendDebugData_handle = xQueueCreate(1024,sizeof(uint16));
    if (xTaskCreate(vTask1,"Task1", configMINIMAL_STACK_SIZE, NULL, 5, &vTask1_handle) != pdTRUE)
    {
        /* Task could not be created */
        while(1);
    }
    if (xTaskCreate(vTask2,"Task2", configMINIMAL_STACK_SIZE, NULL, 1, &vTask2_handle) != pdTRUE)
    {
        /* Task could not be created */
        while(1);
    }
    if (xTaskCreate(vUARTRx,"RX", configMINIMAL_STACK_SIZE, NULL, 4, &vRxHandle) != pdTRUE)
    {
        /* Task could not be created */
        while(1);
    }
    if (xTaskCreate(vUARTTx,"TX", 400, NULL, 5, &vRxHandle) != pdTRUE)
    {
        /* Task could not be created */
        while(1);
    }
    vStartScan();
}


void vTask1( void * pvParameters )
{
TickType_t xLastWakeTime;

const TickType_t xFrequency = 200; //200ms

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
    vStartScan();
    for( ;; )
    {
        // Wait for the next cycle.
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
        gioToggleBit(gioPORTB,1);
        //sciSend(sciREG,3,(uint8 *) &Send_Data);
        //sciSend(sciREG,1,(uint8 *) &Send_Data2);
    }
}

void vTask2( void * pvParameters )
{
int mode = 0;
    for( ;; )
    {
        // Wait for the next cycle.
        xQueueReceive(queue_handle,&mode,portMAX_DELAY);
        mode = !mode;
        if(mode){
            vTaskSuspend(vTask1_handle);
            gioSetBit(gioPORTB,1,0);
        }
        else {
            vTaskResume(vTask1_handle);
        }
    }
}

void vUARTRx( void * pvParameters )
{
    int i=0;
    uint8 byte;
    for( ;; )
    {
        i++;
        xQueueReceive(queueRx_handle,&byte,portMAX_DELAY);
        vAddPacket(byte);
    }
}
void vUARTTx( void * pvParameters ){
    float distance;
    float angle;
    uint16 idx;
    bool flag;
    for(;;){
        xQueueReceive(queueSendDebugData_handle,&idx,portMAX_DELAY);
        taskENTER_CRITICAL();
        char Buff[50];
        //Critical Task Begin
        distance = Get_Distance(idx);
        angle = Get_Angle(idx);
        flag = Get_New_Scan_Flag(idx);
        sprintf(Buff, "%.1f,%.1f,%d \r\n", distance,angle,flag);
        //Critical Task End
        taskEXIT_CRITICAL();
        sciSend(scilinREG,strlen(Buff),(uint8 *) &Buff);
    }
}
