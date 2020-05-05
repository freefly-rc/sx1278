#include "stdio.h"
#include "spi.h"

int main() {
    printf("hello");
    char buff[2] = {0x12, 0x32};
    char *received;

    spi_init(SPI_CH_0, SPI_MODE_0, 1000000, SPI_MSB);
    received = spi_transfer(buff, 2);
    printf("value %x %x", received[0], received[1]);
    spi_stop();

    return 0;
}