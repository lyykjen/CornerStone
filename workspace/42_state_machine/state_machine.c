/*************************************************************************
    > File Name: state_machine_test.c
    > Author: David
    > Mail: 
    > Created Time: Thu 16 Apr 2018 09:34:43 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<string.h>

#define PRINT_BUF_MSG(BUF,INDEX,LEN) {\
        int i = 0;\
        for(i=INDEX>0?INDEX:0;i<LEN;i++)\
        {\
            printf("0x%02x ",BUF[i]);\
        }\
        printf("\n");\
    }

typedef struct __ymavlink_message {
    uint16_t checksum;      ///< sent at end of packet
    uint8_t magic;          ///< protocol magic marker
    uint8_t len;            ///< Length of payload
    uint8_t seq;            ///< Sequence of packet
    uint8_t senderSysID;    ///< ID of the message sender system
    uint8_t senderCompID;   ///< ID of the message sender component
    uint8_t targetSysID;    ///< ID of the message target system
    uint8_t targetCompID;   ///< ID of the message target component
    uint8_t msgid;          ///< ID of message in payload
    uint64_t payload64[264];
}ymavlink_message_t;

typedef enum{
    YMAVLINK_HANDSHAKE_ACK_IDLE = 0,
    YMAVLINK_HANDSHAKE_ACK_STX,
    YMAVLINK_HANDSHAKE_ACK_LENGTH,
    YMAVLINK_HANDSHAKE_ACK_SEQ,
    YMAVLINK_HANDSHAKE_ACK_SENDERSYSID,
    YMAVLINK_HANDSHAKE_ACK_SENDERCOMPID,
    YMAVLINK_HANDSHAKE_ACK_TARGETSYSID,
    YMAVLINK_HANDSHAKE_ACK_TARGETCOMPID,
    YMAVLINK_HANDSHAKE_ACK_MSGID,
    YMAVLINK_HANDSHAKE_ACK_PAYLOAD,
    YMAVLINK_HANDSHAKE_ACK_CRC
} ymavlink_handshake_state;

uint16_t ymavlink_msg_to_buffer(uint8_t *buf, const ymavlink_message_t *msg)
{
    memcpy(buf, (const uint8_t *)&msg->magic, 8 + (uint16_t)msg->len);
    uint8_t *ck = buf + (8 + (uint16_t)msg->len);
    ck[0] = (uint8_t)(msg->checksum & 0xFF);
    ck[1] = (uint8_t)(msg->checksum >> 8);
    return 10 + (uint16_t)msg->len;
}

int find_handshake_ack(uint8_t c)
{
    int revLen;
    static uint8_t expect = 0xfe;
    unsigned char buf[512];
    int ret = 0;
    static int index_01 = 0;
    static int index_00 = 0;

    if (expect != c)
    {
        expect = 0xfe;
        index_01 = 0;
        index_00 = 0;
        return 0;
    }
    switch (c)
    {
    case 0xfe:
        expect = 0x1;
        index_01 = 1;
        break;
    case 0x1:
        if (1 == index_01)
        {
            expect = 0x1;
            index_01++;
        }
        else if (2 == index_01)
        {
            expect = 0x02;
        }
        break;
    case 0x02:
        expect = 0x00;
        index_00 = 1;
        break;
    case 0x00:
        if (1 == index_00)
        {
            expect = 0x0a;
        }
        else if (2 == index_00)
        {
            expect = 0x03;
        }
        break;
    case 0x0a:
        expect = 0x00;
        index_00++;
        break;
    case 0x03:
        expect = 0x88;
        break;
    case 0x88:
        expect = 0x21;
        break;
    case 0x21:
        expect = 0x54;
        break;
    case 0x54:
        expect = 0xfe; //reset
        ret = 1;
        break;
    default:
        printf("error char[%c]\n", c);
        break;
    }
    return ret;
}

//This parser looks for bytes like the following:
//0xfe 0x01 0x01 0x02 0x00 0x0a 0x00 0x03 0x88 0x21 0x54
int parse_handshake_ack(uint8_t c, ymavlink_message_t *pMsg)
{
    static ymavlink_handshake_state parse_state = YMAVLINK_HANDSHAKE_ACK_IDLE;
    static uint8_t expect_char = 0xfe;
    
    if(c != expect_char)
    {
        expect_char = 0xfe;
        parse_state = YMAVLINK_HANDSHAKE_ACK_IDLE;    
    }
    printf("parse_state = %d\n",parse_state);
    int ret = 0;
    
    switch(parse_state){
        case YMAVLINK_HANDSHAKE_ACK_IDLE:
            if(0xfe == c){
                parse_state = YMAVLINK_HANDSHAKE_ACK_STX;
                pMsg->magic = c;
                expect_char = 0x01;
            }
            break;
        case YMAVLINK_HANDSHAKE_ACK_STX:
            if(0x01 == c){
                parse_state = YMAVLINK_HANDSHAKE_ACK_LENGTH;
                pMsg->len = c;
                expect_char = 0x01;
            }
            break;
        case YMAVLINK_HANDSHAKE_ACK_LENGTH:
            if(0x01 == c){
                parse_state = YMAVLINK_HANDSHAKE_ACK_SEQ;
                pMsg->seq = c;
                expect_char = 0x02;
            }
            break;      
        case YMAVLINK_HANDSHAKE_ACK_SEQ:
            if(0x02 == c){
                parse_state = YMAVLINK_HANDSHAKE_ACK_SENDERSYSID;
                pMsg->senderSysID = c;
                expect_char = 0x00;
            }
            break;     
        case YMAVLINK_HANDSHAKE_ACK_SENDERSYSID:
            if(0x00 == c){
                parse_state = YMAVLINK_HANDSHAKE_ACK_SENDERCOMPID;
                pMsg->senderCompID = c;
                expect_char = 0x0a;
            }        
        case YMAVLINK_HANDSHAKE_ACK_SENDERCOMPID:
            if(0x0a == c){      
                parse_state = YMAVLINK_HANDSHAKE_ACK_TARGETSYSID;
                pMsg->targetSysID = c;
                expect_char = 0x00;
            }
            break;        
        case YMAVLINK_HANDSHAKE_ACK_TARGETSYSID:
            if(0x00 == c){
                parse_state = YMAVLINK_HANDSHAKE_ACK_TARGETCOMPID;
                pMsg->targetCompID = c;
                expect_char = 0x03;
            }
            break;        
        case YMAVLINK_HANDSHAKE_ACK_TARGETCOMPID:
            if(0x03 == c){
                parse_state = YMAVLINK_HANDSHAKE_ACK_MSGID;
                pMsg->msgid = c;
                expect_char = 0x88;
            }    
        case YMAVLINK_HANDSHAKE_ACK_MSGID:
            if(0x88 == c){
                parse_state = YMAVLINK_HANDSHAKE_ACK_PAYLOAD;
                pMsg->payload64[0] = c;
                expect_char = 0x21;
            }
            break;
        case YMAVLINK_HANDSHAKE_ACK_PAYLOAD:
            if(0x21 == c){
                parse_state = YMAVLINK_HANDSHAKE_ACK_CRC;
                pMsg->checksum = c&0xff;
                expect_char = 0x54;
            }
            break;
        case YMAVLINK_HANDSHAKE_ACK_CRC:
            if(0x54 == c){
                pMsg->checksum += (c<<8)&0xff00;
                ret = 1;
                expect_char = 0xfe;
                parse_state = YMAVLINK_HANDSHAKE_ACK_IDLE;
            }
            break;
    }
    return ret;
}

int main()
{
    uint8_t buf[20] = {0x69, 0x77, 0xfe, 0x01, 0xfe, 0x01, 0x01, 0x02, 0x00, 0xfe, 0x01, 0x01, 0x02, 0x00, 0x0a, 0x00, 0x03, 0x88, 0x21, 0x54};
    ymavlink_handshake_state parse_state = 0;
    ymavlink_message_t msg = {};
    uint8_t recv_buf[20] = {};
    int i;
    bool isfound = false;

    for(i = 0; i < sizeof(buf); i++){
		//use a state machine to parse handshake ack
        if(parse_handshake_ack(buf[i], &msg)){
            printf("find the handshake ack[0x%02x]\n", (uint8_t)msg.payload64[0]);
            int len = ymavlink_msg_to_buffer(recv_buf, &msg);
            PRINT_BUF_MSG(recv_buf,0,len);
            isfound = true;
            break;
        }
    }
    if(!isfound){
        printf("Not found\n");
    }

    return 0;
}
