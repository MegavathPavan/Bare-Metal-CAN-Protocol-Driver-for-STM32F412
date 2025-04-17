#include "stm32f4xx.h"
#include "can.h"
#include <stdio.h> // Include standard I/O library for printf

int main(void) {
    // Initialize CAN peripheral
    CAN_Init();

    // Create a CAN message to send
    CAN_Message txMsg = {
        .id = 0x123,        // Message ID
        .data = {0xAA, 0xBB, 0xCC, 0xDD},    // Data bytes
        .len = 4            // Data length
    };

    // Create a CAN message structure to store received message
    CAN_Message rxMsg;

    // Print debug message
    printf("CAN Simulation Started\n");

    while (1) {
        // Send CAN message
        CAN_Send(&txMsg);

        // Print debug message
        printf("Waiting for CAN Message...\n");

        // Receive CAN message
        CAN_Receive(&rxMsg);

        // Process received message (e.g., toggle LED based on received data)
        if (rxMsg.id == 0x124 && rxMsg.len == 1 && rxMsg.data[0] == 0xFF) {
            // Toggle LED
            GPIOA->ODR ^= GPIO_ODR_OD5;
        }
    }
}
