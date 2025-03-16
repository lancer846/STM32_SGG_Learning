#include "key.h"

void Key_Init()
{
    // 1. ����ʱ��
    RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // 2. GPIO����ģʽ���ã�PF10��CNF - 10��MODE - 00
    GPIOF->CRH &= ~GPIO_CRH_MODE10;
    GPIOF->CRH |= GPIO_CRH_CNF10_1;
    GPIOF->CRH &= ~GPIO_CRH_CNF10_0;

    GPIOF->ODR &= ~GPIO_ODR_ODR10;

    // 3. AFIO�������Ÿ���ѡ��
    AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI10_PF;

    // 4. ����EXTI
    EXTI->RTSR |= EXTI_RTSR_TR10;
    EXTI->IMR |= EXTI_IMR_MR10;

    // 5. NVIC����
    NVIC_SetPriorityGrouping(3);    // ȫ��������ռ���ȼ�
    NVIC_SetPriority(EXTI15_10_IRQn, 3);
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

// �жϷ������
void EXTI15_10_IRQHandler(void)
{
    // ������жϹ����־λ
    EXTI->PR |= EXTI_PR_PR10;

    // �����ӳ�
    Delay_ms(10);

    // �ж������Ȼ���ָߵ�ƽ���ͷ�תLED1
    if ((GPIOF->IDR & GPIO_IDR_IDR10) != 0)
    {
        LED_Toggle(LED1);
    }
}
