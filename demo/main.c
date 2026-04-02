#include "sbd.h"
#include <stdio.h>

int main()
{
   sbd_config_t config = {
        .model = MODEL_9602, // Choose your SBD model
        .uart_write = NULL // Replace with actual UART write function
    };

    sbd_init(&config);

    const char *payload = "Hello, Iridium SBD!";
    result_t res = send_mo(payload, strlen(payload));

    if (res.succeeded)
    {
        printf("Message sent successfully!\n");
    }
    else
    {
        printf("Failed to send message.\n");
    };
}

void uart_tx(const uint8_t *data, size_t len)
{
    printf("TXing data");
}
