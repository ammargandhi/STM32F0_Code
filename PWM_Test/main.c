#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_tim.h"
int i=0;

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t TimerPeriod = 0;
uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0, Channel4Pulse = 0;

void TIM_Config(void);

void PWM_Output(void)
{  TIM_Config();

  TimerPeriod = 1000;

  Channel1Pulse = (uint16_t) (((uint32_t) 75 * (TimerPeriod - 1)) / 100);

  Channel2Pulse = (uint16_t) (((uint32_t) 75 * (TimerPeriod - 1)) / 100);

  Channel3Pulse = (uint16_t) (((uint32_t) 75 * (TimerPeriod - 1)) / 100);

  Channel4Pulse = (uint16_t) (((uint32_t) 75 *  (TimerPeriod- 1)) / 100);


  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);


  TIM_TimeBaseStructure.TIM_Prescaler = 48;   // 1Mhz Clock
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);


  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = Channel3Pulse;
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = Channel4Pulse;
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);

  /* TIM1 counter enable */
  TIM_Cmd(TIM3, ENABLE);

  /* TIM1 Main Output Enable */
 TIM_CtrlPWMOutputs(TIM3, ENABLE);

  /* Infinite loop */
//  while (1);

}

void TIM_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;



  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOC, ENABLE);


  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_1);

}

int main()
{

	PWM_Output();
while(1){


}
}
