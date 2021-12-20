/******************** (C) COPYRIGHT 2014 91mcu **************************
 * �ļ���  ��system_init.c
 * ����    ��ϵͳ��ʼ��       
 * ʵ��ƽ̨��STM32F103VCT6������
 * ��汾  ��ST3.5.0
 *
 * ����    ��zhangsz
 * ��̳    ��http://www.91mcu.com
 * ��д���ڣ�
 * ��д���ڣ�2014-03-11
**********************************************************************************/	

#include "stm32f10x.h"              /* STM32F10x�� */
#include "led.h"
#include "usart1.h"
#include "device.h"
#include "w5500.h"


/*   SPI Initialization  */
void SPI_Configuration(void)
{
	GPIO_InitTypeDef 		GPIO_InitStructure;
	SPI_InitTypeDef   		SPI_InitStructure;

	/*����GPIOx������ʱ��*/
	/* Enable SPI1 and GPIOA clocks */
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_W5500_SCS, ENABLE);

  	/* Configure SPI1 pins: SCK, MISO and MOSI -------------*/
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
   	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;   //��������
   	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Set Chip Select pin */
	GPIO_InitStructure.GPIO_Pin=GPIO_W5500_SCS_Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_W5500_SCS_PORT, &GPIO_InitStructure);//PA4
	GPIO_SetBits(GPIO_W5500_SCS_PORT, GPIO_W5500_SCS_Pin);

	/* Set SPI interface */
	SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode=SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL=SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA=SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial=7;

	SPI_Init(SPI1,&SPI_InitStructure);

	SPI_Cmd(SPI1,ENABLE);					//Enable  SPI1
}

/* IO port Configuration */
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* Define Reset W5500 output */

		/*����GPIOx������ʱ��*/
	RCC_APB2PeriphClockCmd( RCC_W5500_RST, ENABLE); 
	GPIO_InitStructure.GPIO_Pin  = GPIO_W5500_RST_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_W5500_RST_PORT, &GPIO_InitStructure);
	GPIO_ResetBits(GPIO_W5500_RST_PORT, GPIO_W5500_RST_Pin);

}

/* system Configuration */
void System_Initialization(void)
{

	/* SPI Configuration */
	SPI_Configuration();

	/* IO Configuration */
	GPIO_Configuration();

	/* LED GPIO Configuration */
	LED_GPIO_Config();

	USART1_Config(115200);

	USART1_NVIC_Configuration();

}

void Socket0_Config(uint16_t usTCPPort)
{
	/* set Socket n Port Number */
	Write_SOCK_2_Byte(0, Sn_PORT, usTCPPort);

	Write_SOCK_2_Byte(0,RTR,6000);

	Write_SOCK_2_Byte(0,RCR,3);

	/* Set Maximum Segment Size as 1460 */
	Write_SOCK_2_Byte(0, Sn_MSSR, 1460);

	/* Set RX Buffer Size as 2K */
	Write_SOCK_1_Byte(0,Sn_RXBUF_SIZE, 0x02);
	/* Set TX Buffer Size as 2K */
	Write_SOCK_1_Byte(0,Sn_TXBUF_SIZE, 0x02);
}

