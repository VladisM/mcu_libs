#ifndef UART_H_included
#define UART_H_included

#include "gpio.h"

#include <stddef.h>

#include <utillib/core.h>

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
    const char *uart_name;
    buffer_t *rx_buffer;
}uart_driver_t;

void uart_driver_init(uart_driver_t **uart, void *device, gpio_driver_t *rx, gpio_driver_t*tx, uint32_t baudrate);

void uart_driver_enable_rx_interrupt(uart_driver_t *uart);
void uart_driver_disable_rx_interrupt(uart_driver_t *uart);

void uart_driver_write(uart_driver_t *uart, uint32_t len, uint8_t *data);
void uart_driver_putc(uart_driver_t *uart, char c);
void uart_driver_puts(uart_driver_t *uart, char *s);

void uart_driver_irq_callback(uart_driver_t *uart);

void uart_driver_reconfigure_clock(uart_driver_t *uart);
void uart_driver_reconfigure_baudrate(uart_driver_t *uart, uint32_t baudrate);

unsigned uart_driver_rx_buffer_count(uart_driver_t *uart);
bool uart_driver_rx_buffer_is_empty(uart_driver_t *uart);
uint8_t uart_driver_rx_buffer_read(uart_driver_t *uart);

void uart_driver_set_name(uart_driver_t *uart, const char *uart_name);

#endif
