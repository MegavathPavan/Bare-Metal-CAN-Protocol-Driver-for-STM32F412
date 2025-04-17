#ifndef CAN_H_
#define CAN_H_

#include <stdint.h>

// CAN message structure
typedef struct {
    uint32_t id;        // Message ID
    uint8_t data[8];    // Message data (up to 8 bytes)
    uint8_t len;        // Data length (0 to 8 bytes)
} CAN_Message;

// Initialize CAN peripheral
void CAN_Init();

// Send CAN message
void CAN_Send(CAN_Message *msg);

// Receive CAN message
void CAN_Receive(CAN_Message *msg);

#endif /* CAN_H_ */
