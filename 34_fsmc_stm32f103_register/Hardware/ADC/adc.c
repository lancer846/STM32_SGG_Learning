#include "adc.h"

// ADC1 初始化配置
void ADC1_Init(void)
{
    // 开启时钟配置
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    // ADC 的最大时钟频率为 14 MHZ，需要进行分频
    // 此处配置为 6 分频，也就是 12MHZ
    RCC->CFGR &= ~RCC_CFGR_ADCPRE_0;
    RCC->CFGR |= RCC_CFGR_ADCPRE_1;

    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    // 模拟输入
    GPIOC->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
    GPIOC->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);

    // ADC 的相关配置

    // 配置独立模式，一般不会使用其他模式（默认就是）
    ADC1->CR1 &= ~ADC_CR1_DUALMOD;

    // 此处是多通道，需要扫描模式
    ADC1->CR1 |= ADC_CR1_SCAN;

    // 启用规则通道的外部触发转换模式
    ADC1->CR2 |= ADC_CR2_EXTTRIG;
    // 使用软件触发转换
    ADC1->CR2 |= ADC_CR2_EXTSEL;

    // 数据右对齐
    ADC1->CR2 &= ~ADC_CR2_ALIGN;

    // 启动连续转换，不断获取新的值
    ADC1->CR2 |= ADC_CR2_CONT;

    /*
        设置采样时间：
            该时间不包括转换时间，该芯片的 ADC 为 12 位，内部芯片是一位一位进行转换比对的，
            所以转换时间为 12 个时钟周期，一般还会预留 0.5 个时钟周期，也就是 12.5 个时钟周期
        总的时间就是 采样时间 + 转换时间
    */
    // 设置采样时间为 7.5 个周期（此处使用的是 ADC1 通道 10）
    ADC1->SMPR1 &= ~ADC_SMPR1_SMP10;
    ADC1->SMPR1 |= ADC_SMPR1_SMP10_0;
    ADC1->SMPR1 &= ~ADC_SMPR1_SMP12;
    ADC1->SMPR1 |= ADC_SMPR1_SMP12_0;

    // 设置需要转换的通道数，该计数 0 代表转换 1 个通道
    ADC1->SQR1 &= ~ADC_SQR1_L;
    ADC1->SQR1 |= ADC_SQR1_L_0;

    // 配置 ADC 规则序列，也就是设置每个通道第几位开始转换
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;
    ADC1->SQR3 |= (10 << 0); // 最先转换
    ADC1->SQR3 &= ~ADC_SQR3_SQ2;
    ADC1->SQR3 |= (12 << 5); // 第二位转换
}

// ADC1 DMA 初始化配置
void ADC1_DMA_Init(void)
{
    // 1. 开启DMA模块时钟
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    // 2. 设置通道1的传输方向, DIR = 0
    DMA1_Channel1->CCR &= ~DMA_CCR1_DIR;

    // 3. 数据宽度, SIZE = 01, 16位
    DMA1_Channel1->CCR &= ~DMA_CCR1_PSIZE_1;
    DMA1_Channel1->CCR |= DMA_CCR1_PSIZE_0;
    DMA1_Channel1->CCR &= ~DMA_CCR1_MSIZE_1;
    DMA1_Channel1->CCR |= DMA_CCR1_MSIZE_0;

    // 4. 地址自增，外设不增，内存地址要增
    DMA1_Channel1->CCR &= ~DMA_CCR1_PINC;
    DMA1_Channel1->CCR |= DMA_CCR1_MINC;

    // 5. 开启循环模式
    DMA1_Channel1->CCR |= DMA_CCR1_CIRC;

    // 使用 DMA
    ADC1->CR2 |= ADC_CR2_DMA;
}

// ADC1 开启转换
void ADC1_DMA_StartConvert(uint16_t* buff, uint8_t size)
{
    // 0. DMA配置源地址和目的地址，以及数据长度
    DMA1_Channel1->CPAR = (uint32_t)&(ADC1->DR);
    DMA1_Channel1->CMAR = (uint32_t)buff;
    DMA1_Channel1->CNDTR = size;

    DMA1_Channel1->CCR |= DMA_CCR1_EN;

    // 将 ADC 从断电模式下唤醒
    ADC1->CR2 |= ADC_CR2_ADON;

    // 复位校准
    ADC1->CR2 |= ADC_CR2_RSTCAL;
    // 等待校准完成
    while (ADC1->CR2 & ADC_CR2_RSTCAL)
        ;

    // 校准 ADC 数据
    ADC1->CR2 |= ADC_CR2_CAL;
    // 等待校准完成
    while (ADC1->CR2 & ADC_CR2_CAL)
        ;

    // 启动转换
    ADC1->CR2 |= ADC_CR2_SWSTART;
    // 等待转换完成
    while (!(ADC1->CR2 & ADC_SR_EOC))
        ;
}
