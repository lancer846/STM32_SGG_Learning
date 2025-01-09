#include "key.h"

void KEY_init(void) {
    // 初始化 RCC 时钟
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // 配置 PA0 引脚为输入模式
    GPIOA->MODER &= ~(GPIO_MODER_MODER0);
    // 配置 PA0 引脚无上拉下拉
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR0;

    // 配置 SYSCFG，开通 EXTI0 中断通道
    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;
    // 中断屏蔽置为 1
    EXTI->IMR |= EXTI_IMR_MR0;
    // 上升沿触发
    EXTI->RTSR |= EXTI_RTSR_TR0;

    // 中断使能
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(EXTI0_IRQn, 2);
    NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI0_IRQHandler(void) {
    // 消抖
    Delay_ms(10);
    if(GPIOA->IDR & ~GPIO_ODR_ODR_0) {
        flow_led = (FLOW_LED)((flow_led + 1) % 8);
    }
    // 清除中断标志位
    EXTI->PR |= EXTI_PR_PR0;
}
