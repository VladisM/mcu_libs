#include "clock_ll.h"

#include <stm32.h>

uint32_t clock_ll_hclk_get(void){
    uint32_t div = 0;

    switch(RCC->CFGR & RCC_CFGR_HPRE_Msk){
        case RCC_CFGR_HPRE_DIV1:    div = 1;    break;
        case RCC_CFGR_HPRE_DIV2:    div = 2;    break;
        case RCC_CFGR_HPRE_DIV4:    div = 3;    break;
        case RCC_CFGR_HPRE_DIV8:    div = 8;    break;
        case RCC_CFGR_HPRE_DIV16:   div = 16;   break;
        case RCC_CFGR_HPRE_DIV64:   div = 64;   break;
        case RCC_CFGR_HPRE_DIV128:  div = 128;  break;
        case RCC_CFGR_HPRE_DIV256:  div = 256;  break;
        case RCC_CFGR_HPRE_DIV512:  div = 512;  break;
        default: div = 0; break;
    }

    SystemCoreClockUpdate();
    return SystemCoreClock / div;
}

void clock_ll_hclk_set_div(uint32_t div){
    uint32_t div_macro = 0;

    switch(div){
        case 1:     div_macro = RCC_CFGR_HPRE_DIV1;     break;
        case 2:     div_macro = RCC_CFGR_HPRE_DIV2;     break;
        case 3:     div_macro = RCC_CFGR_HPRE_DIV4;     break;
        case 8:     div_macro = RCC_CFGR_HPRE_DIV8;     break;
        case 16:    div_macro = RCC_CFGR_HPRE_DIV16;    break;
        case 64:    div_macro = RCC_CFGR_HPRE_DIV64;    break;
        case 128:   div_macro = RCC_CFGR_HPRE_DIV128;   break;
        case 256:   div_macro = RCC_CFGR_HPRE_DIV256;   break;
        case 512:   div_macro = RCC_CFGR_HPRE_DIV512;   break;
    }

    RCC->CFGR &= ~(RCC_CFGR_HPRE_Msk);
    RCC->CFGR |= div_macro;
}

uint32_t clock_ll_pclk1_get(void){
    uint32_t div = 0;

    switch(RCC->CFGR & RCC_CFGR_PPRE1_Msk){
        case RCC_CFGR_PPRE1_DIV1:   div = 1;    break;
        case RCC_CFGR_PPRE1_DIV2:   div = 2;    break;
        case RCC_CFGR_PPRE1_DIV4:   div = 4;    break;
        case RCC_CFGR_PPRE1_DIV8:   div = 8;    break;
        case RCC_CFGR_PPRE1_DIV16:  div = 16;   break;
        default: div = 1; break;
    }

    return clock_ll_hclk_get() / div;
}

void clock_ll_pclk1_set_div(uint32_t div){
    uint32_t div_macro = 0;

    switch(div){
        case 1:     div_macro = RCC_CFGR_PPRE1_DIV1;    break;
        case 2:     div_macro = RCC_CFGR_PPRE1_DIV2;    break;
        case 4:     div_macro = RCC_CFGR_PPRE1_DIV4;    break;
        case 8:     div_macro = RCC_CFGR_PPRE1_DIV8;    break;
        case 16:    div_macro = RCC_CFGR_PPRE1_DIV16;   break;
        default:    div_macro = RCC_CFGR_PPRE1_DIV1;    break;
    }

    RCC->CFGR &= ~(RCC_CFGR_PPRE1_Msk);
    RCC->CFGR |= div_macro;
}

uint32_t clock_ll_pclk2_get(void){
    uint32_t div = 0;

    switch(RCC->CFGR & RCC_CFGR_PPRE2_Msk){
        case RCC_CFGR_PPRE2_DIV1:   div = 1;    break;
        case RCC_CFGR_PPRE2_DIV2:   div = 2;    break;
        case RCC_CFGR_PPRE2_DIV4:   div = 4;    break;
        case RCC_CFGR_PPRE2_DIV8:   div = 8;    break;
        case RCC_CFGR_PPRE2_DIV16:  div = 16;   break;
        default: div = 1; break;
    }

    return clock_ll_hclk_get() / div;
}

void clock_ll_pclk2_set_div(uint32_t div){
    uint32_t div_macro = 0;

    switch(div){
        case 1:     div_macro = RCC_CFGR_PPRE2_DIV1;    break;
        case 2:     div_macro = RCC_CFGR_PPRE2_DIV2;    break;
        case 4:     div_macro = RCC_CFGR_PPRE2_DIV4;    break;
        case 8:     div_macro = RCC_CFGR_PPRE2_DIV8;    break;
        case 16:    div_macro = RCC_CFGR_PPRE2_DIV16;   break;
        default:    div_macro = RCC_CFGR_PPRE2_DIV1;    break;
    }

    RCC->CFGR &= ~(RCC_CFGR_PPRE2_Msk);
    RCC->CFGR |= div_macro;
}

void clock_ll_sysclk_set_src(sysclk_src_t sysclk_src){
    uint32_t macro = 0;
    uint32_t target_val = 0;

    switch(sysclk_src){
        case sysclk_hse:    macro = RCC_CFGR_SW_HSE;   target_val = RCC_CFGR_SWS_HSE;    break;
        case sysclk_hsi:    macro = RCC_CFGR_SW_HSI;   target_val = RCC_CFGR_SWS_HSI;    break;
        case sysclk_pllclk: macro = RCC_CFGR_SW_PLL;   target_val = RCC_CFGR_SWS_PLL;    break;
        case sysclk_pllr:   macro = RCC_CFGR_SW_PLLR;  target_val = RCC_CFGR_SWS_PLLR;   break;
        default: macro = RCC_CFGR_SWS_HSI; target_val = RCC_CFGR_SWS_HSI; break;
    }

    RCC->CFGR &= ~(RCC_CFGR_SW_Msk);
    RCC->CFGR |= macro;

    while((RCC->CFGR & RCC_CFGR_SWS_Msk) != target_val) __NOP();
}

void clock_ll_mco1_set_src(mco1_src_t src){
    uint32_t macro = 0;

    switch(src){
        case mco1_hsi: macro = 0;                                   break;
        case mco1_lse: macro = RCC_CFGR_MCO1_0;                     break;
        case mco1_hse: macro = RCC_CFGR_MCO1_1;                     break;
        case mco1_pll: macro = RCC_CFGR_MCO1_0 | RCC_CFGR_MCO1_1;   break;
        default: macro = 0; break;
    }

    RCC->CFGR &= ~(RCC_CFGR_MCO1_Msk);
    RCC->CFGR |= macro;
}

void clock_ll_mco1_set_div(uint32_t div){
    uint32_t macro = 0;

    switch(div){
        case 1: macro = 0;                                                              break;
        case 2: macro = RCC_CFGR_MCO1PRE_2;                                             break;
        case 3: macro = RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_0;                        break;
        case 4: macro = RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_1;                        break;
        case 5: macro = RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_1 | RCC_CFGR_MCO1PRE_0;   break;
        default: macro = 0; break;
    }

    RCC->CFGR &= ~(RCC_CFGR_MCO1PRE_Msk);
    RCC->CFGR |= macro;
}

void clock_ll_mco2_set_src(mco2_src_t src){
    uint32_t macro = 0;

    switch(src){
        case mco2_sysclk:   macro = 0;                                   break;
        case mco2_plli2s:   macro = RCC_CFGR_MCO2_0;                     break;
        case mco2_hse:      macro = RCC_CFGR_MCO2_1;                     break;
        case mco2_pll:      macro = RCC_CFGR_MCO2_0 | RCC_CFGR_MCO2_1;   break;
        default: macro = 0; break;
    }

    RCC->CFGR &= ~(RCC_CFGR_MCO1_Msk);
    RCC->CFGR |= macro;
}

void clock_ll_mco2_set_div(uint32_t div){
    uint32_t macro = 0;

    switch(div){
        case 1: macro = 0;                                                              break;
        case 2: macro = RCC_CFGR_MCO2PRE_2;                                             break;
        case 3: macro = RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_0;                        break;
        case 4: macro = RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_1;                        break;
        case 5: macro = RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_1 | RCC_CFGR_MCO2PRE_0;   break;
        default: macro = 0; break;
    }

    RCC->CFGR &= ~(RCC_CFGR_MCO2PRE_Msk);
    RCC->CFGR |= macro;
}

void clock_ll_rtc_set_div(uint32_t div){
    uint32_t macro = 0;

    if(div < 32)
        macro = (div << RCC_CFGR_RTCPRE_Pos);

    RCC->CFGR &= ~(RCC_CFGR_RTCPRE_Msk);
    RCC->CFGR |= macro;
}

void clock_ll_pll_set_src(pll_src_t src){
    uint32_t macro = 0;

    switch(src){
        case pll_src_hsi: macro = RCC_PLLCFGR_PLLSRC_HSI; break;
        case pll_src_hse: macro = RCC_PLLCFGR_PLLSRC_HSE; break;
        default: macro = 0; break;
    }

    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC_Msk);
    RCC->PLLCFGR |= macro;
}

void clock_ll_pll_set_conf(uint32_t r, uint32_t q, uint32_t p, uint32_t n, uint32_t m){
    uint32_t r_macro = 0;
    uint32_t q_macro = 0;
    uint32_t p_macro = 0;
    uint32_t n_macro = 0;
    uint32_t m_macro = 0;

    if((r >= 2) && (r <= 7)) r_macro = (r << RCC_PLLCFGR_PLLR_Pos);
    else return;

    if((q >= 2) && (q <= 15)) q_macro = (q << RCC_PLLCFGR_PLLQ_Pos);
    else return;

    switch(p){
        case 2: p_macro = 0;                                        break;
        case 4: p_macro = RCC_PLLCFGR_PLLP_0;                       break;
        case 6: p_macro = RCC_PLLCFGR_PLLP_1;                       break;
        case 8: p_macro = RCC_PLLCFGR_PLLP_0 | RCC_PLLCFGR_PLLP_1;  break;
        default: return;
    }

    if((n >= 50) && (n <= 432)) n_macro = (n << RCC_PLLCFGR_PLLN_Pos);
    else return;

    if((m >= 2) && (m <= 63)) m_macro = (m << RCC_PLLCFGR_PLLM_Pos);
    else return;

    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLR_Msk | RCC_PLLCFGR_PLLQ_Msk | RCC_PLLCFGR_PLLP_Msk | RCC_PLLCFGR_PLLN_Msk | RCC_PLLCFGR_PLLM_Msk);
    RCC->PLLCFGR |= (r_macro | q_macro | p_macro | n_macro | m_macro);
}

void clock_ll_pll_en(void){
    RCC->CR |= RCC_CR_PLLON;
    while((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY) __NOP();
}

void clock_ll_pllsai_set_conf(uint32_t q, uint32_t p, uint32_t n, uint32_t m){
    uint32_t q_macro = 0;
    uint32_t p_macro = 0;
    uint32_t n_macro = 0;
    uint32_t m_macro = 0;

    if((q >= 2) && (q <= 15)) q_macro = (q << RCC_PLLSAICFGR_PLLSAIQ_Pos);
    else return;

    switch(p){
        case 2: p_macro = 0;                                                    break;
        case 4: p_macro = RCC_PLLSAICFGR_PLLSAIP_0;                             break;
        case 6: p_macro = RCC_PLLSAICFGR_PLLSAIP_1;                             break;
        case 8: p_macro = RCC_PLLSAICFGR_PLLSAIP_0 | RCC_PLLSAICFGR_PLLSAIP_1;  break;
        default: return;
    }

    if((n >= 50) && (n <= 432)) n_macro = (n << RCC_PLLSAICFGR_PLLSAIN_Pos);
    else return;

    if((m >= 2) && (m <= 63)) m_macro = (m << RCC_PLLSAICFGR_PLLSAIM_Pos);
    else return;

    RCC->PLLSAICFGR &= ~(RCC_PLLSAICFGR_PLLSAIQ_Msk | RCC_PLLSAICFGR_PLLSAIP_Msk | RCC_PLLSAICFGR_PLLSAIN_Msk | RCC_PLLSAICFGR_PLLSAIM_Msk);
    RCC->PLLSAICFGR |= (q_macro | p_macro | n_macro | m_macro);
}

void clock_ll_pllsai_en(void){
    RCC->CR |= RCC_CR_PLLSAION;
    while((RCC->CR & RCC_CR_PLLSAIRDY) != RCC_CR_PLLSAIRDY) __NOP();
}

void clock_ll_plli2s_set_conf(uint32_t r, uint32_t q, uint32_t p, uint32_t n, uint32_t m){
    uint32_t r_macro = 0;
    uint32_t q_macro = 0;
    uint32_t p_macro = 0;
    uint32_t n_macro = 0;
    uint32_t m_macro = 0;

    if((r >= 2) && (r <= 7)) r_macro = (r << RCC_PLLI2SCFGR_PLLI2SR_Pos);
    else return;

    if((q >= 2) && (q <= 15)) q_macro = (q << RCC_PLLI2SCFGR_PLLI2SQ_Pos);
    else return;

    switch(p){
        case 2: p_macro = 0;                                                    break;
        case 4: p_macro = RCC_PLLI2SCFGR_PLLI2SP_0;                             break;
        case 6: p_macro = RCC_PLLI2SCFGR_PLLI2SP_1;                             break;
        case 8: p_macro = RCC_PLLI2SCFGR_PLLI2SP_0 | RCC_PLLI2SCFGR_PLLI2SP_1;  break;
        default: return;
    }

    if((n >= 50) && (n <= 432)) n_macro = (n << RCC_PLLI2SCFGR_PLLI2SN_Pos);
    else return;

    if((m >= 2) && (m <= 63)) m_macro = (m << RCC_PLLI2SCFGR_PLLI2SM_Pos);
    else return;

    RCC->PLLI2SCFGR &= ~(RCC_PLLI2SCFGR_PLLI2SR_Msk | RCC_PLLI2SCFGR_PLLI2SQ_Msk | RCC_PLLI2SCFGR_PLLI2SP_Msk | RCC_PLLI2SCFGR_PLLI2SN_Msk | RCC_PLLI2SCFGR_PLLI2SM_Msk);
    RCC->PLLI2SCFGR |= (r_macro | q_macro | p_macro | n_macro | m_macro);
}

void clock_ll_plli2s_en(void){
    RCC->CR |= RCC_CR_PLLI2SON;
    while((RCC->CR & RCC_CR_PLLI2SRDY) != RCC_CR_PLLI2SRDY) __NOP();
}

void clock_ll_sdio_set_src(sdio_clk_src_t src){
    uint32_t macro = 0;

    switch(src){
        case sdio_sysclk: macro = RCC_DCKCFGR2_SDIOSEL; break;
        case sdio_pll48clk: macro = 0; break;
        default: macro = 0; break;
    }

    RCC->DCKCFGR2 &= ~(RCC_DCKCFGR2_SDIOSEL_Msk);
    RCC->DCKCFGR2 |= macro;
}

void clock_ll_hse_en(void){
    RCC->CR |= RCC_CR_HSEON;
    while((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY) __NOP();
}
