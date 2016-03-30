
#include<stm32f0xx.h>
#include<stm32f0xx_gpio.h>
#include<stm32f0xx_rcc.h>
#include<stm32f0xx_usart.h>
#include<stm32f0xx_tim.h>
int i=0;

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
GPIO_InitTypeDef GPIOC_Init;
GPIO_InitTypeDef GPIOB_Init;
GPIO_InitTypeDef GPIOD_Init;
GPIO_InitTypeDef GPIO_PWMEnPins;
USART_InitTypeDef UART1_BT;
GPIO_InitTypeDef GPIO_RX_Pin;

uint16_t TimerPeriod = 0;



void USART1_Init(void);
void TIM_Config(void);
void PWM_Output(void);
void led_toggle2(void);

void Delay()
{int i;
	for(i=0;i<400000;i++);
}


void PWM_Output(void)
{


  TimerPeriod = 1000;



  /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);

  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 48;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 1;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  /* Channel 1, 2, 3 and 4 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;



  TIM_OCInitStructure.TIM_Pulse = 899;
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = 899;
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = 899;
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = 899;
  TIM_OC4Init(TIM1, &TIM_OCInitStructure);

  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);

  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, DISABLE);

}

void Motor_GPIO_Init()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOD|RCC_AHBPeriph_GPIOC, ENABLE);
	 GPIOB_Init.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_8;
	  GPIOB_Init.GPIO_Mode = GPIO_Mode_OUT;
	  GPIOB_Init.GPIO_OType = GPIO_OType_PP;
	  GPIOB_Init.GPIO_Speed = GPIO_Speed_Level_1;
	  GPIOB_Init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_Init(GPIOB, &GPIOB_Init);


	  GPIOD_Init.GPIO_Pin = GPIO_Pin_2;
	  GPIOD_Init.GPIO_Mode = GPIO_Mode_OUT;
	  GPIOD_Init.GPIO_OType = GPIO_OType_PP;
	  GPIOD_Init.GPIO_Speed = GPIO_Speed_Level_1;
	  GPIOD_Init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_Init(GPIOD, &GPIOD_Init);

	  GPIOC_Init.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_8|GPIO_Pin_9;
	  	  GPIOC_Init.GPIO_Mode = GPIO_Mode_OUT;
	  	  GPIOC_Init.GPIO_OType = GPIO_OType_PP;
	  	  GPIOC_Init.GPIO_Speed = GPIO_Speed_Level_1;
	  	  GPIOC_Init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  	  GPIO_Init(GPIOC, &GPIOC_Init);




	  	  GPIO_PWMEnPins.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	  	  GPIO_PWMEnPins.GPIO_Mode = GPIO_Mode_AF;
	  	  GPIO_PWMEnPins.GPIO_Speed = GPIO_Speed_Level_1;
	  	  GPIO_PWMEnPins.GPIO_OType = GPIO_OType_PP;
	  	  GPIO_PWMEnPins.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  	  GPIO_Init(GPIOA, &GPIO_PWMEnPins);

	  	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2);
	  	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_2);
	  	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_2);
	  	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_2);






}


void USART1_Init(void)
{



RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE);

RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB , ENABLE);


  /* Configure USART1 pins:  Rx * - PB7 Alternative as TIM1 uses 4 channel PWM generation */

  GPIO_RX_Pin.GPIO_Pin =  GPIO_Pin_7;
  GPIO_RX_Pin.GPIO_Speed = GPIO_Speed_Level_1;
  GPIO_RX_Pin.GPIO_Mode = GPIO_Mode_AF;
  GPIO_RX_Pin.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_RX_Pin);

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_0);
    /* Configure USART1 */

UART1_BT.USART_BaudRate = 9600;
UART1_BT.USART_WordLength = USART_WordLength_8b;
UART1_BT.USART_StopBits = USART_StopBits_1;
UART1_BT.USART_Parity = USART_Parity_No ;
UART1_BT.USART_Mode = USART_Mode_Rx;
UART1_BT.USART_HardwareFlowControl = USART_HardwareFlowControl_None;


USART_Init(USART1, &UART1_BT);

USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
NVIC_EnableIRQ(USART1_IRQn);
USART_Cmd(USART1, ENABLE);


}




void USART1_IRQHandler(void)
{


while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
{ 
   USART_SendData(USART2, 'X');
}


if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) /* RXNE if set, then data is received in DR register.*/
{
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	char a;


	a = USART_ReceiveData(USART1);
	if(a=='O'){
		  TIM_CtrlPWMOutputs(TIM1, DISABLE);
		  GPIO_SetBits(GPIOC, GPIO_Pin_9|GPIO_Pin_8);


	}
	    	else if(a=='W')
	{
	    		GPIO_ResetBits(GPIOB, GPIO_Pin_8|GPIO_Pin_5|GPIO_Pin_3);
	    		GPIO_ResetBits(GPIOC, GPIO_Pin_12|GPIO_Pin_9);
	    		GPIO_SetBits(GPIOB, GPIO_Pin_6|GPIO_Pin_4);
	    		GPIO_SetBits(GPIOD, GPIO_Pin_2);
	    		GPIO_SetBits(GPIOC, GPIO_Pin_11|GPIO_Pin_8);
	    		TIM_SetCompare1(TIM1,899);
	    					    		TIM_SetCompare2(TIM1,899);
	    					    		TIM_SetCompare3(TIM1,899);
	    					    		TIM_SetCompare4(TIM1,899);
	    		TIM_CtrlPWMOutputs(TIM1, ENABLE);


	}

	else if(a=='S'){

		GPIO_SetBits(GPIOB, GPIO_Pin_8|GPIO_Pin_5|GPIO_Pin_3);
			    		GPIO_SetBits(GPIOC, GPIO_Pin_12|GPIO_Pin_9);
			    		GPIO_ResetBits(GPIOB, GPIO_Pin_6|GPIO_Pin_4);
			    		GPIO_ResetBits(GPIOD, GPIO_Pin_2);
			    		GPIO_ResetBits(GPIOC, GPIO_Pin_11|GPIO_Pin_8);
			    		TIM_SetCompare1(TIM1,899);
			    					    		TIM_SetCompare2(TIM1,899);
			    					    		TIM_SetCompare3(TIM1,899);
			    					    		TIM_SetCompare4(TIM1,899);
			    		TIM_CtrlPWMOutputs(TIM1, ENABLE);


	}

	else if(a=='D'){
		//TIM_CtrlPWMOutputs(TIM1, DISABLE);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8|GPIO_Pin_5|GPIO_Pin_3);
			    		GPIO_ResetBits(GPIOC, GPIO_Pin_12|GPIO_Pin_9);
			    		GPIO_SetBits(GPIOB, GPIO_Pin_6|GPIO_Pin_4);
			    		GPIO_SetBits(GPIOD, GPIO_Pin_2);
			    		GPIO_SetBits(GPIOC, GPIO_Pin_11|GPIO_Pin_8);
			    		TIM_SetCompare1(TIM1,399);
			    		TIM_SetCompare2(TIM1,399);
			    		TIM_SetCompare3(TIM1,899);
			    		TIM_SetCompare4(TIM1,899);
			    		TIM_CtrlPWMOutputs(TIM1, ENABLE);



	}
	else if(a=='A')
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_8|GPIO_Pin_5|GPIO_Pin_3);
			    		GPIO_ResetBits(GPIOC, GPIO_Pin_12|GPIO_Pin_9);
			    		GPIO_SetBits(GPIOB, GPIO_Pin_6|GPIO_Pin_4);
			    		GPIO_SetBits(GPIOD, GPIO_Pin_2);
			    		GPIO_SetBits(GPIOC, GPIO_Pin_11|GPIO_Pin_8);
			    		  		TIM_SetCompare1(TIM1,899);
					    		TIM_SetCompare2(TIM1,899);
					    		TIM_SetCompare3(TIM1,399);
					    		TIM_SetCompare4(TIM1,399);
					    		TIM_CtrlPWMOutputs(TIM1, ENABLE);

	}

	     /*Clear the Flag*/
}


}

void led_toggle2()
{
	GPIO_SetBits(GPIOC,GPIO_Pin_8|GPIO_Pin_9);

	GPIO_ResetBits(GPIOC,GPIO_Pin_8|GPIO_Pin_9);


}


int main()
{
	Motor_GPIO_Init();
	USART1_Init();
	PWM_Output();

    while(1)
    {

    }

}




