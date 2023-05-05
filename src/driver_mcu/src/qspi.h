#ifndef QSPI_H_included
#define QSPI_H_included

#include "gpio.h"

typedef enum{
    MODE_SKIP,
    MODE_SINGLE,
    MODE_DUAL,
    MODE_QUAD
}qspi_mode_t;

typedef enum{
    LENGTH_ONE_B,
    LENGTH_TWO_B,
    LENGTH_THREE_B,
    LENGTH_FOUR_B
}qspi_length_t;

typedef enum{
    OPERATION_READ,
    OPERATION_WRITE
}qspi_operation_t;

typedef enum{
    SPI_MODE_0,
    SPI_MODE_3
}qspi_spi_operation_t;

typedef struct{
    struct{
        uint32_t CCR;
        uint32_t ABR;
        uint32_t AR;
        uint32_t DLR;
    }tmp_config;
    struct{
        struct{
            uint8_t instruction;
            qspi_mode_t mode;
        } instruction;
        struct{
            uint32_t address;
            qspi_length_t length;
            qspi_mode_t mode;
        }address;
        struct{
            uint32_t alternate;
            qspi_length_t length;
            qspi_mode_t mode;
        }alternate;
        struct{
            uint8_t cycles;
        }dummy;
        struct{
            uint32_t count;
            uint8_t *buffer;
            qspi_mode_t mode;
        }data;
        qspi_operation_t operation;
    } operation_config;
    struct {
        void *device;
        uint32_t peripheral_clock;
    } device;
    struct {
        gpio_driver_t *io0;
        gpio_driver_t *io1;
        gpio_driver_t *io2;
        gpio_driver_t *io3;
        gpio_driver_t *sck;
        gpio_driver_t *ncs;
    } gpio;
    const char *qspi_name;
}qspi_driver_t;

void qspi_driver_init(qspi_driver_t **qspi, void *device, uint32_t clock_prescaler, gpio_driver_t *io0, gpio_driver_t *io1, gpio_driver_t *io2, gpio_driver_t *io3, gpio_driver_t *sck, gpio_driver_t *ncs);

void qspi_driver_set_spimode(qspi_driver_t *qspi, qspi_spi_operation_t mode);
void qspi_driver_set_csht(qspi_driver_t *qspi, int csht);
void qspi_driver_set_fsize(qspi_driver_t *qspi, int fsize);
void qspi_driver_set_instruction(qspi_driver_t *qspi, uint8_t instruction, qspi_mode_t mode);
void qspi_driver_set_address(qspi_driver_t *qspi, uint32_t address, qspi_length_t length, qspi_mode_t mode);
void qspi_driver_set_alternate(qspi_driver_t *qspi, uint32_t alternate, qspi_length_t length, qspi_mode_t mode);
void qspi_driver_set_dummy(qspi_driver_t *qspi, uint8_t cycles);
void qspi_driver_set_data(qspi_driver_t *qspi, uint32_t count, uint8_t *buffer, qspi_mode_t mode);
void qspi_driver_set_operation(qspi_driver_t *qspi, qspi_operation_t operation);

void qspi_driver_trigger(qspi_driver_t *qspi);

uint32_t qspi_driver_get_bus_clock(qspi_driver_t *qspi);
bool qspi_driver_reconfigure_peripheral_clock(qspi_driver_t *qspi);
bool qspi_driver_reconfigure_bus_clock(qspi_driver_t *qspi, uint32_t clock);

void qspi_driver_set_name(qspi_driver_t *qspi, const char *qspi_name);

#endif
