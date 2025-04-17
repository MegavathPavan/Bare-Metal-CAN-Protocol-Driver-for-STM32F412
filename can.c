//can.c
#include "can.h"
#include "stm32f4xx.h"
#include <stdio.h> // Include standard I/O library for printf

// Initialize CAN peripheral
void CAN_Init() {
    // Enable CAN clock
    RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;

    // Reset CAN1
    CAN1->MCR |= CAN_MCR_RESET;
    while (CAN1->MCR & CAN_MCR_RESET);

    // Configure CAN1
    CAN1->MCR &= ~CAN_MCR_SLEEP;    // Exit sleep mode
    CAN1->MCR &= ~CAN_MCR_TTCM;     // Deactivate time-triggered communication mode
    CAN1->MCR |= CAN_MCR_INRQ;      // Request initialization mode

    // Wait for initialization mode
    while (!(CAN1->MSR & CAN_MSR_INAK));

    // Configure bit timing
    CAN1->BTR = (2 << 20) |        // Baud rate prescaler (Tq = 1/42 MHz)
                (3 << 16) |        // Time segment 1 (Tq x (3+1))
                (2 << 12) |        // Time segment 2 (Tq x (2+1))
                (1 << 10);         // Resynchronization jump width (Tq x (1+1))

    // Leave initialization mode
    CAN1->MCR &= ~CAN_MCR_INRQ;

    // Wait for exit from initialization mode
    while (CAN1->MSR & CAN_MSR_INAK);

    // Print debug message
    printf("CAN Initialized\n");
}

// Send CAN message
void CAN_Send(CAN_Message *msg) {
    while (CAN1->TSR & CAN_TSR_TME0); // Wait until mailbox 0 is empty

    // Set message ID
    CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_TXRQ;
    CAN1->sTxMailBox[0].TIR |= (msg->id << 3);

    // Set message length
    CAN1->sTxMailBox[0].TDTR &= ~CAN_TDT0R_DLC;
    CAN1->sTxMailBox[0].TDTR |= msg->len;

    // Copy data to mailbox
    for (uint8_t i = 0; i < msg->len; i++) {
        CAN1->sTxMailBox[0].TDLR = msg->data[i];
    }

    // Request transmission
    CAN1->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ;

    // Print debug message
    printf("CAN Message Sent: ID=%X, Length=%d\n", msg->id, msg->len);
}

// Receive CAN message
void CAN_Receive(CAN_Message *msg) {
    while (!(CAN1->RF0R & CAN_RF0R_FMP0)); // Wait until FIFO 0 has a message

    // Get message ID
    msg->id = CAN1->sFIFOMailBox[0].RIR >> 21;

    // Get message length
    msg->len = CAN1->sFIFOMailBox[0].RDTR & CAN_RDT0R_DLC;

    // Copy data from mailbox
    for (uint8_t i = 0; i < msg->len; i++) {
        msg->data[i] = CAN1->sFIFOMailBox[0].RDLR;
    }

    // Release FIFO 0
    CAN1->RF0R |= CAN_RF0R_RFOM0;

    // Print debug message
    printf("CAN Message Received: ID=%X, Length=%d\n", msg->id, msg->len);
}
