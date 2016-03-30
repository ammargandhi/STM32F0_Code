#include<stm32f0xx_usart.h>
#include<stm32f0xx_gpio.h>
#include<stm32f0xx.h>
#include<stm32f0xx_rcc.h>
USART_InitTypeDef UART1_BT;
GPIO_InitTypeDef GPIO_RX_Pin;
int main(void)
{
USART1_Init();

    while(1)
    {

    	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
    	{
    	   USART_SendData(USART2, 'AT+CWJAP="CS","ammar123"');


    	}


    }
}




void USART1_Init(void)
{



RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE);

RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB , ENABLE);


  /* Configure USART1 pins:  Rx * - PB7 Alternative as TIM1 uses 4 channel PWM generation */

  GPIO_RX_Pin.GPIO_Pin =  GPIO_Pin_7 | GPIO_Pin_6;
  GPIO_RX_Pin.GPIO_Speed = GPIO_Speed_Level_1;
  GPIO_RX_Pin.GPIO_Mode = GPIO_Mode_AF;
  GPIO_RX_Pin.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_RX_Pin);

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_0);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_0);
    /* Configure USART1 */

UART1_BT.USART_BaudRate = 9600;
UART1_BT.USART_WordLength = USART_WordLength_8b;
UART1_BT.USART_StopBits = USART_StopBits_1;
UART1_BT.USART_Parity = USART_Parity_No ;
UART1_BT.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
UART1_BT.USART_HardwareFlowControl = USART_HardwareFlowControl_None;


USART_Init(USART1, &UART1_BT);

USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
NVIC_EnableIRQ(USART1_IRQn);
USART_Cmd(USART1, ENABLE);


}




// Finish the USART Handler.



void USART1_IRQHandler(void)
{


}
