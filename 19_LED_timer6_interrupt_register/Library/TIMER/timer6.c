#include "timer6.h"

void Timer6_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
    // 开启自动重装载寄存器缓存
    //TIM6->CR1 |= TIM_CR1_ARPE;
    // 因为需要分频，所以时钟x2 = 84MHZ
    TIM6->PSC = 8400 - 1;
    // 设置重装载值
    TIM6->ARR = 5000 - 1;

    /*
        手动触发更新事件，将缓存中的值加载进影子寄存器中
        （否则会在一开始以 84MHZ 时钟频率先执行一遍，产生更新后再将缓存值加载进影子寄存器中）
     */
    TIM6->EGR |= TIM_EGR_UG;

    // 更新中断使能
    TIM6->DIER |= TIM_DIER_UIE;

    // 配置中断
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(TIM6_DAC_IRQn, 2);
    NVIC_EnableIRQ(TIM6_DAC_IRQn);

    // 计数使能
    TIM6->CR1 |= TIM_CR1_CEN;
}

void TIM6_DAC_IRQHandler() {
    // 清除中断标志位
    TIM6->SR &= ~TIM_SR_UIF;
    // 配置 回调函数
    Timer6_callback();
}
