#include "sbd.h"

typedef struct {
    m_binary_arr_t slot;
    size_t expected_size;
} rx_request_t;

void rx_handle(const uint8_t *data, size_t len);
void rx_start_listen(rx_request_t *request);
bool rx_wait_for_expected(uint32_t timeout_ms);