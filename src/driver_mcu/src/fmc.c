#include "fmc.h"

#include <stm32.h>

#include "driver_mcu_debug.h"
#include "clock.h"

#include <stdlib.h>
#include <string.h>

#include "common.h"

#define SDCMR_MODE_NORMAL 0
#define SDCMR_MODE_CCE    1
#define SDCMR_MODE_PALL   2
#define SDCMR_MODE_AR     3
#define SDCMR_MODE_LMR    4
#define SDCMR_MODE_SR     5
#define SDCMR_MODE_PD     6

#ifndef NDEBUG
#define PRINT_SDCR(c) print_sdcr(c)
void print_sdcr(fmc_driver_t *fmc);
#else
#define PRINT_SDCR(c)
#endif

static const char* eofr_str = "parameter out of range!";

void fmc_driver_init(fmc_driver_t **fmc){
    fmc_driver_t *tmp = (fmc_driver_t *)malloc(sizeof(fmc_driver_t));

    if(tmp == NULL){
        DRIVER_MCU_DEBUG_ERROR("%s", "Malloc failed!");
        *fmc = NULL;
        return;
    }

    memset(tmp, 0, sizeof(fmc_driver_t));

    tmp->bank_5_6.device = NULL;
    tmp->bank_5_6.configured = false;

    #ifndef NDEBUG
    tmp->fmc_name = "N/A";
    #endif

    *fmc = tmp;
}

static bool _calc_sdcr1(fmc_driver_t *fmc, uint32_t *sdcr1){
    uint32_t tmp = 0;

    tmp |= FMC_SDCR1_RPIPE_1; //TODO: meaning???
    tmp |= FMC_SDCR1_RBURST; //TODO: meaning???

    uint32_t cas = fmc->bank_5_6.device_config.cas;
    uint32_t banks = fmc->bank_5_6.device_config.banks;
    uint32_t column_address_width = fmc->bank_5_6.device_config.column_address_width;
    uint32_t data_width = fmc->bank_5_6.device_config.data_width;
    uint32_t row_address_width = fmc->bank_5_6.device_config.row_address_width;
    uint32_t pres = fmc->bank_5_6.device_timing.pres;

    if(cas <= 3 && cas > 0){
        tmp |= (((uint32_t)cas) << FMC_SDCR1_CAS_Pos);
    }
    else{
        DRIVER_MCU_DEBUG_ERROR("%s CAS out of range! %d", fmc->fmc_name, cas);
        return false;
    }

    if(banks == 4){
        tmp |= FMC_SDCR1_NB;
    }
    else if(banks == 2){
        //nothing to do
    }
    else{
        DRIVER_MCU_DEBUG_ERROR("%s unsupported number of banks! %d", fmc->fmc_name, banks);
        return false;
    }

    if(column_address_width <= 11 && column_address_width >= 8){
        tmp |= (((uint32_t)(column_address_width) - 8) << FMC_SDCR1_NC_Pos);
    }
    else{
        DRIVER_MCU_DEBUG_ERROR("%s unsupported count of columns! %d", fmc->fmc_name, column_address_width);
        return false;
    }

    if(data_width == 16){
        tmp |= FMC_SDCR1_MWID_0;
    }
    else if(data_width == 8){
        //nothing to do
    }
    else{
        DRIVER_MCU_DEBUG_ERROR("%s unsupported width of data bus! %d", fmc->fmc_name, data_width);
        return false;
    }

    if(row_address_width <= 13 && row_address_width >= 11){
        tmp |= (((uint32_t)(row_address_width) - 11) << FMC_SDCR1_NR_Pos);
    }
    else{
        DRIVER_MCU_DEBUG_ERROR("%s unsupported count of rows! %d", fmc->fmc_name, row_address_width);
        return false;
    }

    if(pres == 2 || pres == 3){
        tmp |= ((pres) << FMC_SDCR1_SDCLK_Pos);
    }
    else{
        DRIVER_MCU_DEBUG_ERROR("%s unsupported divider for clock! %d", fmc->fmc_name, pres);
        return false;
    }

    *sdcr1 = tmp;
    return true;
}

static bool _calc_sdtr1(fmc_driver_t *fmc, uint32_t *sdtr1){
    uint32_t tmp = 0;

    uint32_t trp    = (uint32_t)fmc->bank_5_6.device_timing.trp;
    uint32_t trc    = (uint32_t)fmc->bank_5_6.device_timing.trc;
    uint32_t trcd   = (uint32_t)fmc->bank_5_6.device_timing.trcd;
    uint32_t twr    = (uint32_t)fmc->bank_5_6.device_timing.twr;
    uint32_t tras   = (uint32_t)fmc->bank_5_6.device_timing.tras;
    uint32_t txsr   = (uint32_t)fmc->bank_5_6.device_timing.txsr;
    uint32_t tmrd   = (uint32_t)fmc->bank_5_6.device_timing.tmrd;

    if(trp <= 16 && trp != 0){
        tmp |= (((trp - 1) << FMC_SDTR1_TRP_Pos)  & FMC_SDTR1_TRP_Msk);  //Row to precharge delay
    }
    else{
        DRIVER_MCU_DEBUG_ERROR("%s trp %s %d", fmc->fmc_name, eofr_str, trp);
        return false;
    }

    if(trc <= 16 && trc != 0){
        tmp |= (((trc - 1) << FMC_SDTR1_TRC_Pos)  & FMC_SDTR1_TRC_Msk);  //Row cycle delay
    }
    else{
        DRIVER_MCU_DEBUG_ERROR("%s trc %s %d", fmc->fmc_name, eofr_str, trc);
        return false;
    }

    if(trcd <= 16 && trcd != 0){
        tmp |= (((trcd - 1) << FMC_SDTR2_TRCD_Pos) & FMC_SDTR2_TRCD_Msk); //Row to column delay
    }
    else{
        DRIVER_MCU_DEBUG_ERROR("%s trcd %s %d", fmc->fmc_name, eofr_str, trcd);
        return false;
    }

    if(twr <= 16 && twr != 0){
        tmp |= (((twr - 1) << FMC_SDTR2_TWR_Pos)  & FMC_SDTR2_TWR_Msk);  //Recovery time
    }
    else{
        DRIVER_MCU_DEBUG_ERROR("%s twr %s %d", fmc->fmc_name, eofr_str, twr);
        return false;
    }

    if(tras <= 16 && tras != 0){
        tmp |= (((tras - 1) << FMC_SDTR2_TRAS_Pos) & FMC_SDTR2_TRAS_Msk); //Self refresh time
    }
    else{
        DRIVER_MCU_DEBUG_ERROR("%s tras %s %d", fmc->fmc_name, eofr_str, tras);
        return false;
    }

    if(txsr <= 16 && txsr != 0){
        tmp |= (((txsr - 1) << FMC_SDTR2_TXSR_Pos) & FMC_SDTR2_TXSR_Msk); //Exit felf refresh delay
    }
    else{
        DRIVER_MCU_DEBUG_ERROR("%s txsr %s %d", fmc->fmc_name, eofr_str, txsr);
        return false;
    }

    if(tmrd <= 16 && tmrd != 0){
        tmp |= (((tmrd - 1) << FMC_SDTR2_TMRD_Pos) & FMC_SDTR2_TMRD_Msk); //Load mode register to acrive
    }
    else{
        DRIVER_MCU_DEBUG_ERROR("%s tmrd %s %d", fmc->fmc_name, eofr_str, tmrd);
        return false;
    }

    *sdtr1 = tmp;
    return true;
}

static bool _calc_sdrtr(fmc_driver_t *fmc, uint32_t *sdrtr){
    uint32_t tmp = 0;

    uint32_t _rtr = fmc->bank_5_6.device_timing.rtr;

    if((_rtr << FMC_SDRTR_COUNT_Pos) > FMC_SDRTR_COUNT_Msk){
        DRIVER_MCU_DEBUG_ERROR("%s rtr %s %d", fmc->fmc_name, eofr_str, _rtr);
        return false;
    }
    else{
        tmp |= (_rtr) << FMC_SDRTR_COUNT_Pos;
    }

    *sdrtr = tmp;
    return true;
}

static bool _calc_sdcmr(fmc_driver_t *fmc, uint32_t mode, uint32_t *sdcmr){
    uint32_t tmp = 0;

    uint32_t mrd = fmc->bank_5_6.device_config.mode_register;
    uint32_t nrfs = fmc->bank_5_6.device_config.nrfs;

    bool ctb1 = false;
    bool ctb2 = false;

    switch(fmc->bank_5_6.bank_config){
        case FMC_ONLY_BANK_5:   ctb1 = true;                break;
        case FMC_ONLY_BANK_6:   ctb2 = true;                break;
        case FMC_BANK_5_AND_6:  ctb1 = true; ctb2 = true;   break;
    }

    if(FMC_SDCMR_MRD_Msk < (mrd << FMC_SDCMR_MRD_Pos)){
        DRIVER_MCU_DEBUG_ERROR("%s Device MODE register is out of range!", fmc->fmc_name);
        return false;
    }
    else{
        tmp |= (mrd << FMC_SDCMR_MRD_Pos);
    }

    if(nrfs > 16 || nrfs == 0){
        DRIVER_MCU_DEBUG_ERROR("%s nrfs %s %d", fmc->fmc_name, eofr_str, nrfs);
        return false;
    }
    else{
        tmp |= ((nrfs - 1) << FMC_SDCMR_NRFS_Pos);
    }

    if(FMC_SDCMR_MODE_Msk < (mode << FMC_SDCMR_MODE_Pos)){
        DRIVER_MCU_DEBUG_ERROR("%s SDCMR MODE is out of range!", fmc->fmc_name);
        return false;
    }
    else{
        tmp |= (mode << FMC_SDCMR_MODE_Pos);
    }

    if(ctb1) tmp |= FMC_SDCMR_CTB1;
    if(ctb2) tmp |= FMC_SDCMR_CTB2;

    *sdcmr = tmp;
    return true;
}

static void _wait_fmc_bank_5_6_busy(fmc_driver_t *fmc){
    FMC_Bank5_6_TypeDef *_device = (FMC_Bank5_6_TypeDef *)fmc->bank_5_6.device;

    while(_device->SDSR & FMC_SDSR_BUSY)
        __NOP();
}

static bool _execute_sdcmr(fmc_driver_t *fmc, uint32_t mode){
    FMC_Bank5_6_TypeDef *_device = (FMC_Bank5_6_TypeDef *)fmc->bank_5_6.device;

    uint32_t tmp = 0;

    if(!_calc_sdcmr(fmc, mode, &tmp)){
        return false;
    }

    DRIVER_MCU_DEBUG_INFO("SDCMR = %X", tmp);

    _device->SDCMR = tmp;
    _wait_fmc_bank_5_6_busy(fmc);

    return true;
}

static bool _execute_clock_configuration_enable(fmc_driver_t *fmc){
    return _execute_sdcmr(fmc, SDCMR_MODE_CCE);
}

static bool _execute_pall(fmc_driver_t *fmc){
    return _execute_sdcmr(fmc, SDCMR_MODE_PALL);
}

static bool _execute_auto_refresh(fmc_driver_t *fmc){
    return _execute_sdcmr(fmc, SDCMR_MODE_AR);
}

static bool _execute_load_mode_reg(fmc_driver_t *fmc){
    return _execute_sdcmr(fmc, SDCMR_MODE_LMR);
}

bool fmc_driver_bank_5_6_config(fmc_driver_t *fmc, void *device,
    fmc_driver_bank_5_6_timing_t *device_timing,
    fmc_driver_bank_5_6_device_config_t *device_config,
    fmc_driver_bank_5_6_bank_config_t bank_config
){
    DRIVER_MCU_DEBUG_INFO("Configuration of FMC bank 5 and 6.");

    if(fmc->bank_5_6.configured == true){
        DRIVER_MCU_DEBUG_ERROR("FMC Bank 5 and 6 is already configured!");
        return false;
    }

    if(bank_config != FMC_ONLY_BANK_5){
        DRIVER_MCU_DEBUG_ERROR("Only bank 5 is currently supported in driver!");
        return false;
    }

    memcpy(&(fmc->bank_5_6.device_config), device_config, sizeof(fmc_driver_bank_5_6_device_config_t));
    memcpy(&(fmc->bank_5_6.device_timing), device_timing, sizeof(fmc_driver_bank_5_6_timing_t));

    uint32_t sdcr1 = 0;
    uint32_t sdtr1 = 0;
    uint32_t sdrtr = 0;

    if(!_calc_sdcr1(fmc, &sdcr1) || !_calc_sdtr1(fmc, &sdtr1) || !_calc_sdrtr(fmc, &sdrtr)){
        return false;
    }

    FMC_Bank5_6_TypeDef *_device = (FMC_Bank5_6_TypeDef *)device;
    fmc->bank_5_6.device = device;

    clock_enable_peripheral_clock(device);

    _device->SDCR[0] = sdcr1;
    _device->SDTR[0] = sdtr1;

    DRIVER_MCU_DEBUG_INFO("SDCR[0] = %X", sdcr1);
    DRIVER_MCU_DEBUG_INFO("SDTR[0] = %X", sdtr1);

    if(!_execute_clock_configuration_enable(fmc))
        return false;

    //TODO: here should be short delay ...

    if(!_execute_pall(fmc))
        return false;

    if(!_execute_auto_refresh(fmc))
        return false;

    if(!_execute_load_mode_reg(fmc))
        return false;

    _device->SDRTR = sdrtr;

    DRIVER_MCU_DEBUG_INFO("SDRTR = %X", sdrtr);

    DRIVER_MCU_DEBUG_INFO("FMC bank 5 and 6 done.");
    fmc->bank_5_6.configured = true;

    return true;
}

uint32_t fmc_driver_bank_5_get_address(fmc_driver_t *fmc){
    UNUSED(fmc);
    if((SYSCFG->MEMRMP & SYSCFG_MEMRMP_SWP_FMC_Msk) == (SYSCFG_MEMRMP_SWP_FMC_0)){
        return 0x60000000;
    }
    else{
        return 0xC0000000;
    }
}

uint32_t fmc_driver_bank_6_get_address(fmc_driver_t *fmc){
    UNUSED(fmc);
    if((SYSCFG->MEMRMP & SYSCFG_MEMRMP_SWP_FMC_Msk) == (SYSCFG_MEMRMP_SWP_FMC_0)){
        return 0x70000000;
    }
    else{
        return 0xD0000000;
    }
}

#ifndef NDEBUG
void fmc_driver_set_name(fmc_driver_t *fmc, const char *fmc_name){
    fmc->fmc_name = fmc_name;
}

void print_sdcr(fmc_driver_t *fmc){
    FMC_Bank5_6_TypeDef *_device = (FMC_Bank5_6_TypeDef *)fmc->bank_5_6.device;
    uint32_t sdcr = _device->SDCR[0];

    DRIVER_MCU_DEBUG_INFO("SDCR[0]:");
    DRIVER_MCU_DEBUG_INFO(" NC: %u", ((sdcr & FMC_SDCR1_NC_Msk) >> FMC_SDCR1_NC_Pos));
    DRIVER_MCU_DEBUG_INFO(" NR: %u", ((sdcr & FMC_SDCR1_NR_Msk) >> FMC_SDCR1_NR_Pos));
    DRIVER_MCU_DEBUG_INFO(" MWID: %u", ((sdcr & FMC_SDCR1_MWID_Msk) >> FMC_SDCR1_MWID_Pos));
    DRIVER_MCU_DEBUG_INFO(" NB: %u", ((sdcr & FMC_SDCR1_NB_Msk) >> FMC_SDCR1_NB_Pos));
    DRIVER_MCU_DEBUG_INFO(" NC: %u", ((sdcr & FMC_SDCR1_NC_Msk) >> FMC_SDCR1_NC_Pos));
    DRIVER_MCU_DEBUG_INFO(" CAS: %u", ((sdcr & FMC_SDCR1_CAS_Msk) >> FMC_SDCR1_CAS_Pos));
    DRIVER_MCU_DEBUG_INFO(" WP: %u", ((sdcr & FMC_SDCR1_WP_Msk) >> FMC_SDCR1_WP_Pos));
    DRIVER_MCU_DEBUG_INFO(" SDCLK: %u", ((sdcr & FMC_SDCR1_SDCLK_Msk) >> FMC_SDCR1_SDCLK_Pos));
    DRIVER_MCU_DEBUG_INFO(" RBURST: %u", ((sdcr & FMC_SDCR1_RBURST_Msk) >> FMC_SDCR1_RBURST_Pos));
    DRIVER_MCU_DEBUG_INFO(" RPIPE: %u", ((sdcr & FMC_SDCR1_RPIPE_Msk) >> FMC_SDCR1_RPIPE_Pos));
}
#endif
