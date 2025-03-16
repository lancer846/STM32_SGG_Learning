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

    // 不需要复用引脚 GPIO 使能，因为走的是模拟通道，不需要施密特触发器这些

    // ADC 的相关配置

    // 配置独立模式，一般不会使用其他模式（默认就是）
    ADC1->CR1 &= ~ADC_CR1_DUALMOD;

    // 此处是单通道，不需要扫描模式
    ADC1->CR1 &= ~ADC_CR1_SCAN;

    // 启用规则通道的外部触发转换模式
    ADC1->CR2 |= ADC_CR2_EXTTRIG;
    // 使用软件触发转换
    ADC1->CR2 |= ADC_CR2_EXTSEL;

    // 数据右对齐
    ADC1->CR2 &= ~ADC_CR2_ALIGN;

    // 不使用 DMA
    ADC1->CR2 &= ~ADC_CR2_DMA;

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

    // 设置需要转换的通道数，该计数 0 代表转换 1 个通道
    ADC1->SQR1 &= ~ADC_SQR1_L;

    // 配置 ADC 规则序列，也就是设置每个通道第几位开始转换
    ADC1->SQR3 |= (10 << 0);
}

// ADC1 开启转换
void ADC1_StartConvert(void)
{
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

// ADC1 读取转换结果
double ADC1_GetResult(void)
{
    return ADC1->DR * 3.3 / 4095;
}
