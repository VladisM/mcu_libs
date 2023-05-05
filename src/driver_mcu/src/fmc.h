#ifndef FMC_H_included
#define FMC_H_included

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t trp;    //Row to precharge delay
    uint8_t trc;    //Row cycle delay
    uint8_t trcd;   //Row to column delay
    uint8_t twr;    //Recovery time
    uint8_t tras;   //Self refresh time
    uint8_t txsr;   //Exit self refresh delay
    uint8_t tmrd;   //Load mode register to active
    uint8_t pres;   //control clock divider for device
    uint16_t rtr;   //timer value for refresh
} fmc_driver_bank_5_6_timing_t;

typedef struct {
    uint8_t cas;
    uint8_t banks;
    uint8_t data_width;
    uint8_t column_address_width;
    uint8_t row_address_width;
    uint8_t nrfs;
    uint16_t mode_register;
} fmc_driver_bank_5_6_device_config_t;

typedef enum {
    FMC_ONLY_BANK_5,
    FMC_ONLY_BANK_6,
    FMC_BANK_5_AND_6
} fmc_driver_bank_5_6_bank_config_t;

typedef struct{
    const char *fmc_name;
    struct {
        void *device;
        bool configured;
        fmc_driver_bank_5_6_timing_t device_timing;
        fmc_driver_bank_5_6_device_config_t device_config;
        fmc_driver_bank_5_6_bank_config_t bank_config;
    } bank_5_6;
} fmc_driver_t;

void fmc_driver_init(fmc_driver_t **fmc);

bool fmc_driver_bank_5_6_config(fmc_driver_t *fmc, void *device,
    fmc_driver_bank_5_6_timing_t *device_timing,
    fmc_driver_bank_5_6_device_config_t *device_config,
    fmc_driver_bank_5_6_bank_config_t bank_config
);

uint32_t fmc_driver_bank_5_get_address(fmc_driver_t *fmc);
uint32_t fmc_driver_bank_6_get_address(fmc_driver_t *fmc);

void fmc_driver_set_name(fmc_driver_t *fmc, const char *fmc_name);

#endif
