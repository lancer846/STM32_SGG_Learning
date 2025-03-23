#include "fsmc.h"

// FSMC GPIO 初始化
static void FSMC_GPIO_Init()
{
    // PG   PF  PE  PD
    // 1. 地址线 A0~A18，复用推挽输出，CNF-10，MODE-11
    // 1.1 MODE = 11
    GPIOF->CRL |= (GPIO_CRL_MODE0 |
                   GPIO_CRL_MODE1 |
                   GPIO_CRL_MODE2 |
                   GPIO_CRL_MODE3 |
                   GPIO_CRL_MODE4 |
                   GPIO_CRL_MODE5);

    GPIOF->CRH |= (GPIO_CRH_MODE12 |
                   GPIO_CRH_MODE13 |
                   GPIO_CRH_MODE14 |
                   GPIO_CRH_MODE15);

    GPIOG->CRL |= (GPIO_CRL_MODE0 |
                   GPIO_CRL_MODE1 |
                   GPIO_CRL_MODE2 |
                   GPIO_CRL_MODE3 |
                   GPIO_CRL_MODE4 |
                   GPIO_CRL_MODE5);

    GPIOD->CRH |= (GPIO_CRH_MODE11 |
                   GPIO_CRH_MODE12 |
                   GPIO_CRH_MODE13);

    // 1.2 CNF = 10
    GPIOF->CRL |= (GPIO_CRL_CNF0_1 |
                   GPIO_CRL_CNF1_1 |
                   GPIO_CRL_CNF2_1 |
                   GPIO_CRL_CNF3_1 |
                   GPIO_CRL_CNF4_1 |
                   GPIO_CRL_CNF5_1);
    GPIOF->CRL &= ~(GPIO_CRL_CNF0_0 |
                    GPIO_CRL_CNF1_0 |
                    GPIO_CRL_CNF2_0 |
                    GPIO_CRL_CNF3_0 |
                    GPIO_CRL_CNF4_0 |
                    GPIO_CRL_CNF5_0);

    GPIOF->CRH |= (GPIO_CRH_CNF12_1 |
                   GPIO_CRH_CNF13_1 |
                   GPIO_CRH_CNF14_1 |
                   GPIO_CRH_CNF15_1);
    GPIOF->CRH &= ~(GPIO_CRH_CNF12_0 |
                    GPIO_CRH_CNF13_0 |
                    GPIO_CRH_CNF14_0 |
                    GPIO_CRH_CNF15_0);

    GPIOG->CRL |= (GPIO_CRL_CNF0_1 |
                   GPIO_CRL_CNF1_1 |
                   GPIO_CRL_CNF2_1 |
                   GPIO_CRL_CNF3_1 |
                   GPIO_CRL_CNF4_1 |
                   GPIO_CRL_CNF5_1);
    GPIOG->CRL &= ~(GPIO_CRL_CNF0_0 |
                    GPIO_CRL_CNF1_0 |
                    GPIO_CRL_CNF2_0 |
                    GPIO_CRL_CNF3_0 |
                    GPIO_CRL_CNF4_0 |
                    GPIO_CRL_CNF5_0);

    GPIOD->CRH |= (GPIO_CRH_CNF11_1 |
                   GPIO_CRH_CNF12_1 |
                   GPIO_CRH_CNF13_1);
    GPIOD->CRH &= ~(GPIO_CRH_CNF11_0 |
                    GPIO_CRH_CNF12_0 |
                    GPIO_CRH_CNF13_0);

    // 2. 数据线，复用推挽输出，CNF-10， MODE-11
    /* =============MODE=============== */
    GPIOD->CRL |= (GPIO_CRL_MODE0 |
                   GPIO_CRL_MODE1);
    GPIOD->CRH |= (GPIO_CRH_MODE8 |
                   GPIO_CRH_MODE9 |
                   GPIO_CRH_MODE10 |
                   GPIO_CRH_MODE14 |
                   GPIO_CRH_MODE15);

    GPIOE->CRL |= (GPIO_CRL_MODE7);
    GPIOE->CRH |= (GPIO_CRH_MODE8 |
                   GPIO_CRH_MODE9 |
                   GPIO_CRH_MODE10 |
                   GPIO_CRH_MODE11 |
                   GPIO_CRH_MODE12 |
                   GPIO_CRH_MODE13 |
                   GPIO_CRH_MODE14 |
                   GPIO_CRH_MODE15);

    /* =============CNF=============== */
    GPIOD->CRL |= (GPIO_CRL_CNF0_1 |
                   GPIO_CRL_CNF1_1);
    GPIOD->CRL &= ~(GPIO_CRL_CNF0_0 |
                    GPIO_CRL_CNF1_0);

    GPIOD->CRH |= (GPIO_CRH_CNF8_1 |
                   GPIO_CRH_CNF9_1 |
                   GPIO_CRH_CNF10_1 |
                   GPIO_CRH_CNF14_1 |
                   GPIO_CRH_CNF15_1);
    GPIOD->CRH &= ~(GPIO_CRH_CNF8_0 |
                    GPIO_CRH_CNF9_0 |
                    GPIO_CRH_CNF10_0 |
                    GPIO_CRH_CNF14_0 |
                    GPIO_CRH_CNF15_0);

    GPIOE->CRL |= (GPIO_CRL_CNF7_1);
    GPIOE->CRL &= ~(GPIO_CRL_CNF7_0);

    GPIOE->CRH |= (GPIO_CRH_CNF8_1 |
                   GPIO_CRH_CNF9_1 |
                   GPIO_CRH_CNF10_1 |
                   GPIO_CRH_CNF11_1 |
                   GPIO_CRH_CNF12_1 |
                   GPIO_CRH_CNF13_1 |
                   GPIO_CRH_CNF14_1 |
                   GPIO_CRH_CNF15_1);
    GPIOE->CRH &= ~(GPIO_CRH_CNF8_0 |
                    GPIO_CRH_CNF9_0 |
                    GPIO_CRH_CNF10_0 |
                    GPIO_CRH_CNF11_0 |
                    GPIO_CRH_CNF12_0 |
                    GPIO_CRH_CNF13_0 |
                    GPIO_CRH_CNF14_0 |
                    GPIO_CRH_CNF15_0);

    // 3. 控制信号，复用推挽输出，CNF-10， MODE-11
    GPIOD->CRL |= (GPIO_CRL_MODE4 | GPIO_CRL_MODE5);
    GPIOD->CRL |= (GPIO_CRL_CNF4_1 | GPIO_CRL_CNF5_1);
    GPIOD->CRL &= ~(GPIO_CRL_CNF4_0 | GPIO_CRL_CNF5_0);

    GPIOE->CRL |= (GPIO_CRL_MODE0 | GPIO_CRL_MODE1);
    GPIOE->CRL |= (GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1);
    GPIOE->CRL &= ~(GPIO_CRL_CNF0_0 | GPIO_CRL_CNF1_0);

    GPIOG->CRH |= GPIO_CRH_MODE10;
    GPIOG->CRH |= GPIO_CRH_CNF10_1;
    GPIOG->CRH &= ~GPIO_CRH_CNF10_0;
}

void FSMC_Init(void)
{
    RCC->AHBENR |= RCC_AHBENR_FSMCEN;
    RCC->APB2ENR |= (RCC_APB2ENR_IOPDEN |
                     RCC_APB2ENR_IOPEEN |
                     RCC_APB2ENR_IOPFEN |
                     RCC_APB2ENR_IOPGEN);

    FSMC_GPIO_Init();

    // 根据手册可知，该芯片 sram 只支持异步
    // 存储器块使能
    FSMC_Bank1->BTCR[4] |= FSMC_BCR3_MBKEN;

    // 地址 / 数据 不复用
    FSMC_Bank1->BTCR[4] &= ~FSMC_BCR3_MUXEN;

    // 存储器类型：SRAM
    FSMC_Bank1->BTCR[4] &= ~FSMC_BCR3_MTYP;

    // 存储器数据总线宽度：16bit（由外置存储器手册定义）
    FSMC_Bank1->BTCR[4] &= ~FSMC_BCR3_MWID_1;
    FSMC_Bank1->BTCR[4] |= FSMC_BCR3_MWID_0;

    // 闪存访问：禁止对 NOR闪存存储器的操作
    FSMC_Bank1->BTCR[4] &= ~FSMC_BCR3_FACCEN;

    // 写使能
    FSMC_Bank1->BTCR[4] |= FSMC_BCR3_WREN;

    // 不使用扩展模式（也就是读写时序只用一个寄存器进行配置）
    FSMC_Bank1->BTCR[4] &= ~FSMC_BCR3_EXTMOD;

    // 地址建立时间：1 HCLK（由外置存储器手册定义）
    // 0000：ADDSET建立时间=1个HCLK时钟周期
    FSMC_Bank1->BTCR[5] &= ~FSMC_BTR3_ADDSET;

    // 地址保持时间（该寄存器只有在模式 D 才会用到）
    FSMC_Bank1->BTCR[5] &= ~FSMC_BTR3_ADDHLD;

    // 数据保持时间：大于 40ns 即可（由外置存储器手册定义）
    // 0000 0001：DATAST保持时间=2个HCLK时钟周期
    FSMC_Bank1->BTCR[5] &= ~FSMC_BTR3_DATAST;
    FSMC_Bank1->BTCR[5] |= (4 << 8);
}
