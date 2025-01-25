#include "systick.h"

// 系统滴答定时器初始化 - 开启中断（systick 装载值只能减少）
void Systick_init() {
    // 清除标志位
    SysTick->CTRL &= ~SysTick_CTRL_COUNTFLAG_Msk;
    // 配置时钟源 - AHB 168M
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    /*
        开启定时中断
        此处中断不需要调用 NVIC，因为 Systick 属于 Cortex 内核的一部分，
        在内核中已经调过 NVIC 了
    */
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

    // 重装载 - 设置为 1ms 的值
    SysTick->LOAD |= 168000 - 1;
    // 定时器使能
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}


void SysTick_Handler() {

    systick_interrupt_handler();
}
