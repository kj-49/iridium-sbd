#include "rx.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "common.h"

static bool listening_for_rx = false;
static rx_request_t *current_rx_request;

void rx_handle(const uint8_t *data, size_t len)
{
    if (!listening_for_rx || current_rx_request == NULL)
    {
        LOG("Got data but not listening for RX, ignoring. DATA: %.*s", (int)len, data);
        return;
    }
    LOG("Received data: %.*s", (int)len, data);
}

void rx_start_listen(rx_request_t *request)
{
    listening_for_rx = true;
    current_rx_request = request;
}

bool rx_wait_for_expected(uint32_t timeout_ms) {
    sbd_config_t config = get_config();
    uint32_t rough_elapsed = 0;
    while (current_rx_request != NULL && current_rx_request->slot.size != current_rx_request->expected_size)
    {
        LOG("Waiting for RX...");
        config.delay_ms(10);
        rough_elapsed += 10;

        if (rough_elapsed >= timeout_ms)
        {
            LOG("Timeout waiting for RX");
            return true;
        }
    }

    return false;
}
