#ifndef UART_H_included
#define UART_H_included

#include "gpio.h"

typedef struct{
    struct {
        uint32_t baudrate;
    } config;
    struct {
        void *device;
        uint32_t peripheral_clock;
    } device;
    struct {
        gpio_driver_t *rx;
        gpio_driver_t *tx;
    } gpio;
    #ifndef NDEBUG
    const char *uart_name;
    #endif
}uart_driver_t;

void uart_driver_init(uart_driver_t **uart, void *device, gpio_driver_t *rx, gpio_driver_t*tx, uint32_t baudrate);

void uart_driver_write(uart_driver_t *uart, uint32_t len, uint8_t *data);
void uart_driver_putc(uart_driver_t *uart, char c);
void uart_driver_puts(uart_driver_t *uart, char *s);

void uart_driver_reconfigure_clock(uart_driver_t *uart);
void uart_driver_reconfigure_baudrate(uart_driver_t *uart, uint32_t baudrate);

#ifndef NDEBUG
#define UART_DRIVER_SET_NAME(uart, uart_name) uart_driver_set_name((uart), (uart_name))
void uart_driver_set_name(uart_driver_t *uart, const char *uart_name);
#else
#define UART_DRIVER_SET_NAME(uart, uart_name)
#endif

#endif
