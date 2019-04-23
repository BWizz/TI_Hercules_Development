#include "RPLIDAR.h"

#define NUM_PACKET 1000

typedef struct{
    bool packetIsFull;
    bool s;
    bool sbar;
    bool c;
    uint8 quality;
    uint16 angle_raw;
    uint16 distance_raw;
    double angle;
    double distance;
} packet_t;

typedef struct {
    uint8    descriptor[7];
    uint8    desc_idx;
    packet_t Data[NUM_PACKET];
    uint16    buff_index;
}rplidar_t;

rplidar_t rplidar;

void vAddPacket(uint8 byte){
    static uint8 offset = 0;
    uint16 idx = rplidar.buff_index;
    if( xAddDescriptor(byte) ){
        switch (offset){
        case 0:
            rplidar.Data[idx].s =       (bool)  byte & 0x01;
            rplidar.Data[idx].sbar =    (bool)  (byte & 0x02) >> 1;
            rplidar.Data[idx].quality = (uint8) (byte & 0b11111100)>>2 ;
            offset++;
            break;
        case 1:
            rplidar.Data[idx].c = (uint8) (byte & 0x01);
            rplidar.Data[idx].angle_raw =(uint16) (byte);
            offset++;
            break;
        case 2:
            rplidar.Data[idx].angle_raw = ((rplidar.Data[idx].angle_raw) | (((uint16) byte) << 8)) >> 1;
            rplidar.Data[idx].angle =     (rplidar.Data[idx].angle_raw  / 64.0);
            offset++;
            break;
        case 3:
            rplidar.Data[idx].distance_raw = (uint16) byte;
            offset++;
            break;
        case 4:
            rplidar.Data[idx].distance_raw = (((uint16) byte) << 8) | (rplidar.Data[idx].distance_raw);
            rplidar.Data[idx].packetIsFull = 1;
            rplidar.Data[idx].distance =   (rplidar.Data[idx].distance_raw) / (4.0);
            if(rplidar.buff_index < NUM_PACKET){
                rplidar.buff_index++;
            }
            else{
                rplidar.buff_index = 0;
            }
            offset = 0;
            xQueueSend(queueSendDebugData_handle,&rplidar.buff_index,0);
            break;
        }
    }
}


    void vStartScan(void){
        uint8 Data_rx[2] = {0xA5,0x20}; //Force Scan Request
        sciSend(sciREG,2,(uint8 *) &Data_rx);
    }

    void vStopScan(void){
        uint16 Data_rx = 0xA525; //Stop Scan Request
        sciSend(sciREG,1,(uint8 *) &Data_rx);
    }

    bool xAddDescriptor(uint8 byte){
        if(rplidar.desc_idx < 7){
            rplidar.descriptor[rplidar.desc_idx] = byte;
            rplidar.desc_idx++;
            return 0;
        }
        else{
            return 1;
        }
    }

    float Get_Distance(uint16 idx){
        return rplidar.Data[idx].distance;
    }
    float Get_Angle(uint16 idx){
        return rplidar.Data[idx].angle;
    }
    bool Get_New_Scan_Flag(uint16 idx){
        return rplidar.Data[idx].s;
    }
