#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "common.h"

#define MO_PAYLOAD_MAX_LEN 340

typedef struct {
    bool succeeded;
} result_t;

typedef enum {
    WRITE_BIN_ISU_SUCCEEDED = 0,
    /* NOTE: This response will not be followed by "OK", unlike the rest. */
    WRITE_BIN_ISU_TIMEOUT = 1,
    WRITE_BIN_ISU_BAD_CHECKSUM = 2,
    WRITE_BIN_ISU_BAD_MSG_SIZE = 3,
    WRITE_BIN_INTERNAL_ERROR = 4
} write_binary_response_t;

typedef struct {
    size_t size;
    uint8_t *data;
} m_binary_arr_t;

uart_rx_func sbd_init(sbd_config_t *config);

write_binary_response_t send_binary(const uint8_t* payload, size_t len);