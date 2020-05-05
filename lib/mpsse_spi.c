#include "spi.h"

#include "mpsse.h"
#include "stdio.h"

struct mpsse_context *mpsse = NULL;

inline static enum modes to_mpsse_mode(spi_mode_t mode);
inline static int to_mpsse_endianess(spi_endianess_t endianess);

int spi_init(spi_channel_t channel, spi_mode_t mode, int freq, spi_endianess_t endianess) {
    mpsse = MPSSE(to_mpsse_mode(mode), freq, to_mpsse_endianess(endianess));

    if (mpsse != NULL && mpsse->open) {
        return 0;
    }

    printf("Failed to open spi: %s\n", ErrorString(mpsse));
    return 1;
}

void spi_stop() {
    Stop(mpsse);
}

char *spi_transfer(char *buff, int size) {
    return Transfer(mpsse, buff, size);
}

inline static enum modes to_mpsse_mode(spi_mode_t mode) {
    switch (mode) {
        case SPI_MODE_0:
            return SPI0;

        case SPI_MODE_1:
            return SPI1;

        case SPI_MODE_2:
            return SPI2;

        case SPI_MODE_3:
            return SPI3;

        default:
            return SPI0;
    }
}

inline static int to_mpsse_endianess(spi_endianess_t endianess) {
    switch (endianess) {
        case SPI_MSB:
            return MSB;
        case SPI_LSB:
            return LSB;
        default:
            return MSB;
    }
}
