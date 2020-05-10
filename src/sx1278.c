#include "sx1278.h"
#include "stdio.h"

sx127x_result_e sx127x_set_mode(sx127x_mode_t mode);

sx127x_result_e sx127x_set_active_modem(sx127x_radio_type_t radio_type);

sx127x_result_e sx127x_get_active_modem(sx127x_radio_type_t *radio_type);

sx127x_result_e sx127x_set_current_limit(uint16_t limit);

sx127x_result_e sx127x_clear_irq_flags();

sx127x_result_e sx1278_init(sx127x_config_t *config, spi_config_t *spi_config) {
    sx127x_result_e result = SX127X_OK;

    result |= spi_init(spi_config->channel, SPI_MODE_0, spi_config->freq, SPI_MSB);
    if (result) {
        return ERROR_SPI | result;
    }
    result |= gpio_init();
    if (result) {
        return ERROR_GPIO | result;
    }
    result |= sx12xx_dio_init();

    // Initialize modem in LoRa modem mode
    result |= sx127x_set_active_modem(LORA);

    if (config->preamble_length < 6) {
        return (ERROR_INVALID_PREAMBLE_LENGTH);
    }

    // set preamble length
//    result |= sx12xx_set_reg(SX127X_REG_PREAMBLE_MSB, (uint8_t) ((config->preamble_length >> 8) & 0xFF));
//    result |= sx12xx_set_reg(SX127X_REG_PREAMBLE_LSB, (uint8_t) (config->preamble_length & 0xFF));

//    result |= sx127x_set_current_limit(config->current_limit);

    // For debug
    sx1278_channel_status_e status = 0xff;
    sx1278_scan_channel(&status);
    if (status == SX1278_CHANNEL_FREE) {
        printf("kir");
    }
    return result;
}

sx127x_result_e sx1278_scan_channel(sx1278_channel_status_e *channel_status) {
    sx127x_result_e result = SX127X_OK;

    sx127x_radio_type_t radio = 0;
    result |= sx127x_get_active_modem(&radio);
    if (radio != SX127X_LORA) {
        return (ERROR_WRONG_MODEM);
    }

    result |= sx127x_set_mode(STANDBY);

    result |= sx12xx_set_regnm(SX127X_REG_DIO_MAPPING_1, SX127X_DIO0_CAD_DONE | SX127X_DIO1_CAD_DETECTED, 7, 4);
    result |= sx127x_clear_irq_flags();
    result |= sx127x_set_mode(CAD);

    uint8_t s = sx12xx_dio_read();
    printf("%x", s);

    return result;
}

void sx1278_close() {
    spi_close();
    gpio_close();
}

sx127x_result_e sx127x_set_mode(sx127x_mode_t mode) {
    return sx12xx_set_regnm(SX127X_REG_OP_MODE, mode, 2, 0);
}

sx127x_result_e sx127x_set_active_modem(sx127x_radio_type_t radio_type) {
    sx127x_result_e result = SX127X_OK;

    result |= sx127x_set_mode(SLEEP);
    result |= sx12xx_set_regnm(SX127X_REG_OP_MODE, radio_type, 7, 7);
    result |= sx127x_set_mode(STANDBY);

    return result;
}

sx127x_result_e sx127x_set_current_limit(uint16_t limit) {
    if (!(((limit >= 45) && (limit <= 240)) || (limit == 0))) {
        return (ERROR_INVALID_CURRENT_LIMIT);
    }

    uint8_t raw;
    sx127x_result_e result = SX127X_OK;
    if (limit == 0) {
        // limit set to 0, disable OCP
        result |= sx12xx_set_regnm(SX127X_REG_OCP, SX127X_OCP_OFF, 5, 5);
    } else if (limit <= 120) {
        raw = (limit - 45) / 5;
        result |= sx12xx_set_regnm(SX127X_REG_OCP, SX127X_OCP_ON | raw, 5, 0);
    } else if (limit <= 240) {
        raw = (limit + 30) / 10;
        result |= sx12xx_set_regnm(SX127X_REG_OCP, SX127X_OCP_ON | raw, 5, 0);
    }

    return result;
}

sx127x_result_e sx127x_get_active_modem(sx127x_radio_type_t *radio_type) {
    sx127x_result_e result = SX127X_OK;
    result |= sx12xx_get_regnm(SX127X_REG_OP_MODE, (uint8_t *)radio_type, 7, 7);

    return result;
}

sx127x_result_e sx127x_clear_irq_flags() {
    sx127x_result_e result = SX127X_OK;

    sx127x_radio_type_t radio = 0;
    result |= sx127x_get_active_modem(&radio);

    if (radio == LORA) {
        sx12xx_set_reg(SX127X_REG_IRQ_FLAGS, 0b11111111);
    } else if (radio == FSK_OOK) {
        result |= ERROR_OPERATION_NOT_SUPPORTED;
    }

    return result;
}
