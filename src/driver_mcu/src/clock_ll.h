#ifndef CLOCK_LL_H_included
#define CLOCK_LL_H_included

#include <stdint.h>

typedef enum{
    sysclk_hse = 0,
    sysclk_hsi,
    sysclk_pllclk,
    sysclk_pllr
} sysclk_src_t;

typedef enum{
    mco1_hsi = 0,
    mco1_lse,
    mco1_hse,
    mco1_pll
} mco1_src_t;

typedef enum{
    mco2_sysclk = 0,
    mco2_plli2s,
    mco2_hse,
    mco2_pll
} mco2_src_t;

typedef enum{
    pll_src_hsi = 0,
    pll_src_hse
} pll_src_t;

typedef enum{
    sdio_sysclk = 0,
    sdio_pll48clk
} sdio_clk_src_t;

void clock_ll_sysclk_set_src(sysclk_src_t sysclk_src);

uint32_t clock_ll_hclk_get(void);
uint32_t clock_ll_pclk1_get(void);
uint32_t clock_ll_pclk2_get(void);

void clock_ll_hclk_set_div(uint32_t div);
void clock_ll_pclk1_set_div(uint32_t div);
void clock_ll_pclk2_set_div(uint32_t div);
void clock_ll_mco1_set_src(mco1_src_t src);
void clock_ll_mco1_set_div(uint32_t div);
void clock_ll_mco2_set_src(mco2_src_t src);
void clock_ll_mco2_set_div(uint32_t div);
void clock_ll_rtc_set_div(uint32_t div);
void clock_ll_pll_set_src(pll_src_t src);
void clock_ll_pll_set_conf(uint32_t r, uint32_t q, uint32_t p, uint32_t n, uint32_t m);
void clock_ll_pll_en(void);
void clock_ll_pllsai_set_conf(uint32_t q, uint32_t p, uint32_t n, uint32_t m);
void clock_ll_pllsai_en(void);
void clock_ll_plli2s_set_conf(uint32_t r, uint32_t q, uint32_t p, uint32_t n, uint32_t m);
void clock_ll_plli2s_en(void);
void clock_ll_sdio_set_src(sdio_clk_src_t src);
void clock_ll_hse_en(void);

#endif
