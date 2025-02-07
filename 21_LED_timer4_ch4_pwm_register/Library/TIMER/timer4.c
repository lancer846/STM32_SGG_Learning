#include "timer4.h"

// 定时器初始化
void Timer4_init(void) {
    // 时钟使能
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    // GPIO 模式设置 - 复用模式
    GPIOD->MODER |= GPIO_MODER_MODER15_1;
    GPIOD->MODER &= ~GPIO_MODER_MODER15_0;

    // 推挽输出
    GPIOD->OTYPER &= ~GPIO_OTYPER_OT_15;
    // 复用功能 - AF2
    GPIOD->AFR[1] |= (1 << 29);

    /*
        配置定时器生成 PWM 方波
        计数即可，不需要中断
    */
   // 关闭自动重装载预加载寄存器
   TIM4->CR1 &= ~TIM_CR1_ARPE;
   // 向上计数
   TIM4->CR1 &= ~TIM_CR1_CMS;
   TIM4->CR1 &= ~TIM_CR1_DIR;

   // 配置定时器模式为 PWM 模式 1
   TIM4->CCMR2 |= (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1);
   TIM4->CCMR2 &= ~TIM_CCMR2_OC4M_0;
   // cc4 配置作为输出
   TIM4->CCMR2 &= ~TIM_CCMR2_CC4S;
   // CC4 捕获/比较输出使能
   TIM4->CCER |= TIM_CCER_CC4E;

   // 预分频 - 分频后周期为 100us，即 0.1ms
   TIM4->PSC = 8400 - 1;
   // 自动重装载寄存器赋值 - 计数 100 个
   TIM4->ARR = 100 - 1;

   // 改变高低电平的节点 - 即占空比的值（随机值即可，后面会修改该值实现呼吸灯效果）
   TIM4->CCR4 = 0;
}

// 定时器启动
void Timer4_start(void) {
    TIM4->CR1 |= TIM_CR1_CEN;
}
// 定时器停止
void Timer4_stop(void) {
    TIM4->CR1 &= ~TIM_CR1_CEN;
}

// PWM 占空比设置
void Timer4_setDutyCircle(uint8_t dutyCircle) {
    TIM4->CCR4 = dutyCircle;
}
