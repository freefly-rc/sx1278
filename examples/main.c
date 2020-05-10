#include "stdio.h"
#include "sx1278.h"

int main() {
    printf("Starting Spi..\n");

    sx127x_config_t c = {
            .sync_word = 0x24,
            .current_limit = 50,
            .preamble_length = 512,
            .spreading_factor = SF_10
    };
    spi_config_t s = {.freq = 1000000, .channel = SPI_CH_0};

    sx127x_result_e result = sx1278_init(&c, &s);
    if (result == SX127X_OK) {
        printf("sx1278 ok");
    } else {
        printf("error %x", result);
    }

    sx1278_close();

    return 0;
}