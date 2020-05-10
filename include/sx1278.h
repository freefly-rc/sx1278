#ifndef SX1278_SX1278_H
#define SX1278_SX1278_H

#include "sx12xx_spi.h"
#include "sx12xx_gpio.h"
#include "sx127x_reg.h"

typedef enum {
    SX127X_OK = 0u,
    ERROR_SPI = 0x8000u,
    ERROR_GPIO = 0x4000u,
    ERROR_INVALID_PREAMBLE_LENGTH = 1u,
    ERROR_INVALID_CURRENT_LIMIT = 2u,
    ERROR_WRONG_MODEM = 4u,
    ERROR_OPERATION_NOT_SUPPORTED = 4u,

} sx127x_result_e;

typedef struct {
    int freq;
    spi_channel_t channel;

} spi_config_t;

typedef enum {
    SLEEP = SX127X_SLEEP,
    STANDBY = SX127X_STANDBY,
    FSTX = SX127X_FSTX,
    TX = SX127X_TX,
    FSRX = SX127X_FSRX,
    RXCONTINUOUS = SX127X_RXCONTINUOUS,
    RXSINGLE = SX127X_RXSINGLE,
    CAD = SX127X_CAD,
} sx127x_mode_t;

typedef enum {
    LORA = SX127X_LORA,
    FSK_OOK = SX127X_FSK_OOK,
} sx127x_radio_type_t;

typedef enum {
    SF_6 = SX127X_SF_6,
    SF_7 = SX127X_SF_7,
    SF_8 = SX127X_SF_8,
    SF_9 = SX127X_SF_9,
    SF_10 = SX127X_SF_10,
    SF_11 = SX127X_SF_11,
    SF_12 = SX127X_SF_12,
} sx127x_spreading_factor_t;

typedef struct {
    uint8_t sync_word;
    uint16_t preamble_length;
    int is_low_frequency;
    sx127x_spreading_factor_t spreading_factor;
    int current_limit;
} sx127x_config_t;

typedef enum {
    SX1278_CHANNEL_BUSY,
    SX1278_CHANNEL_FREE
} sx1278_channel_status_e;

sx127x_result_e sx1278_init(sx127x_config_t *config, spi_config_t *spi_config);
sx127x_result_e sx1278_scan_channel(sx1278_channel_status_e *channel_status);

void sx1278_close();



#endif //SX1278_SX1278_H

