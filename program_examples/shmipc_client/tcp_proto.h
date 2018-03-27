#ifndef __TCP_PROTO_H__
#define __TCP_PROTO_H__

#define CMD_MOVE_LEFT			0x01
#define CMD_MOVE_RIGHT			0x02
#define CMD_STOP			0x03

#define TCP_STATE_UNKNOWN		0x00
#define TCP_STATE_DISABLED		0x01
#define TCP_STATE_STOPPED		0x02
#define TCP_STATE_MOVE			0x03

#define TCP_POSITION_UNKNOWN		0x00
#define TCP_POSITION_MOVING_LEFT	0x01
#define TCP_POSITION_MOVING_RIGHT	0x02
#define TCP_POSITION_LEFT		0x03
#define TCP_POSITION_RIGHT		0x04

#define CAMERA_WIDTH		640
#define CAMERA_HEIGHT		480
#define DX_INCORRECT_VALUE	0x80000000

#define SERVER_PORT             32000
#define CRC_SIZE                4
#define MAX_BUFF_SIZE           1020 + CRC_SIZE

typedef struct __attribute__ ((__packed__)) {
    unsigned char command;
    unsigned int data;
} TCP_CONTROL_STRUCT;

typedef struct __attribute__ ((__packed__)) {
    unsigned char state;
    unsigned char position;
    unsigned char speed;
    int dx;
} TCP_STATUS_STRUCT;

#endif
