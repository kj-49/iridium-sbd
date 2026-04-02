#include <stdint.h>

typedef enum {
    MODEL_9522A,
    MODEL_9522B,
    MODEL_9601,
    MODEL_9602
} sbd_model_t;

typedef struct {
    uint16_t mo_max_size;
    uint16_t mt_max_size;
} model_config_t;

static const model_config_t model_configs[] = {
    [MODEL_9522A] = { .mo_max_size = 1960, .mt_max_size = 1890 },
    [MODEL_9522B] = { .mo_max_size = 1960, .mt_max_size = 1890 },
    [MODEL_9601] = { .mo_max_size = 340, .mt_max_size = 270 },
    [MODEL_9602] = { .mo_max_size = 340, .mt_max_size = 270 }
};

typedef struct {
    sbd_model_t model;
    uart_tx_func uart_write;
    delay_ms delay_ms;
} sbd_config_t;

typedef void (*uart_tx_func)(const uint8_t *data, size_t len);
typedef void (*uart_rx_func)(const uint8_t *data, size_t len);
typedef void (*delay_ms)(uint32_t ms);

void set_config(sbd_config_t *cfg);
sbd_config_t get_config();