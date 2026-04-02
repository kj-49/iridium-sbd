#include "sbd.h"
#include <string.h>
#include <stdio.h>
#include "rx.h"
#include "common.h"

#define LOG(...) do { \
    printf(__VA_ARGS__); \
    printf("\n"); \
} while(0)

uint16_t get_checksum(const uint8_t *data, size_t len);

uart_rx_func sbd_init(sbd_config_t *cfg)
{
    set_config(cfg);

    cfg->uart_write((const uint8_t *)"ATE0\r\n", 6); // Turn off echo

    return &rx_handle;
}

write_binary_response_t send_binary(const uint8_t* payload, size_t len) {
    sbd_config_t config = get_config();
    if (config.model == MODEL_9522A || config.model == MODEL_9522B)
    {
        return WRITE_BIN_INTERNAL_ERROR;
    }
    
    if (len > model_configs[config.model].mo_max_size) // +2 for checksum bytes
    {
        return WRITE_BIN_ISU_BAD_MSG_SIZE;
    }

    uint8_t wb_size_rx_buffer[7];
    rx_request_t wb_size_rx_request = {
        .slot = { 
            .size = 7, 
            .data = wb_size_rx_buffer 
         },
        .expected_size = len
    }; 
    // Since we are readying rx before tx, make sure echo is off (ATE0)
    start_listen(&wb_size_rx_request);
    
    uint8_t sbdwb_len = 12;
    uint8_t sbdwb_buffer[sbdwb_len];
    snprintf((char *)sbdwb_buffer, sizeof(sbdwb_buffer), "AT+SBDWB=%zu", len);
    
    config.uart_write(sbdwb_buffer, sbdwb_len);
    
    if (wait_for_rx(100))
    {
        // Timed out
        return WRITE_BIN_INTERNAL_ERROR;
    }
    
    if (memcmp(wb_size_rx_request.slot.data, "READY\r\n", 7) != 0) // Force 7 only since uart won't send null terminator
    {
        return WRITE_BIN_INTERNAL_ERROR;
    }
    
    uint16_t checksum = get_checksum(payload, len);
    
    // Handle different endianness
    uint8_t high_byte = (uint8_t)(checksum >> 8);   // Always the high 8 bits
    uint8_t low_byte  = (uint8_t)(checksum & 0xFF); // Always the low 8 bits
    
    uint8_t wb_data_rx_buffer[1];
    rx_request_t wb_data_rx_request = {
        .slot = {
            .size = 1, 
            .data = wb_data_rx_buffer 
         },
        .expected_size = len
    }; 
    start_listen(&wb_data_rx_request);

    config.uart_write(payload, len);
    config.uart_write(&high_byte, 1);
    config.uart_write(&low_byte, 1);

    if (wait_for_rx(100))
    {
        // Timed out
        return WRITE_BIN_INTERNAL_ERROR;
    }
    
    return (write_binary_response_t)wb_data_rx_request.slot.data[0];
}

uint16_t get_checksum(const uint8_t *data, size_t len)
{
    uint16_t checksum = 0;
    for (size_t i = 0; i < len; i++)
    {
        checksum += data[i];
    }
    return checksum;
}
