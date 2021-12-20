/*初始IP地址是192.168.1.111，通过对PB7的操作来实现缺省值和flash之间的切换，设置好的参数写入flash，w5500接的是SPI2，单片机是stm32f103c8t6。
第一个网页没有任何修改权限，只有输入登录密码（初始密码：123456 或者万能密码：765997）进入修改页面，可以修改参数，包括登录密码都可以修改。
浏览器用的是IE，程序编译会有20个warning，请忽略，不是语法错误，不影响任何使用。*/

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
		DefaultSet();//出厂值
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


