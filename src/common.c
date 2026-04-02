#include "common.h"

static sbd_config_t *config;

void set_config(sbd_config_t *cfg)
{
    config = cfg;
}

sbd_config_t get_config()
{
    return *config;
}