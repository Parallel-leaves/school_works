/*��ʼIP��ַ��192.168.1.111��ͨ����PB7�Ĳ�����ʵ��ȱʡֵ��flash֮����л������úõĲ���д��flash��w5500�ӵ���SPI2����Ƭ����stm32f103c8t6��
��һ����ҳû���κ��޸�Ȩ�ޣ�ֻ�������¼���루��ʼ���룺123456 �����������룺765997�������޸�ҳ�棬�����޸Ĳ�����������¼���붼�����޸ġ�
������õ���IE������������20��warning������ԣ������﷨���󣬲�Ӱ���κ�ʹ�á�*/

#include "stm32f10x.h"
#include "usart.h"
#include "config.h"
#include "device.h"
#include "spi2.h"
#include "socket.h"
#include "w5500.h"
#include "ult.h"
#include "httpult.h"
#include "flash.h"
#include <stdio.h>
#include <string.h>

uint8 reboot_flag = 0;

int main(void)
{
	Systick_Init(72);
	GPIO_Configuration(); //GPIO configuration
	USART1_Init(); //115200@8-n-1
	printf("W5500 EVB initialization over.\r\n");
	Reset_W5500();
	WIZ_SPI_Init();
	printf("W5500 initialized!\r\n");
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
	{
		DefaultSet();//����ֵ
	}
	else
	{
 		get_config();//read config data from flash
	}
	printf("Firmware ver%d.%d\r\n",ConfigMsg.sw_ver[0],ConfigMsg.sw_ver[1]);
	if(ConfigMsg.debug==0) ConfigMsg.debug=1;

	set_network();
	printf("Network is ready.\r\n");
	while(1)
	{
		if(ConfigMsg.JTXD_Control == 0)
		  	do_http();
		else
		  	JTXD_do_http();
		if(reboot_flag)
			NVIC_SystemReset();
//        reboot();
        
	}
}


