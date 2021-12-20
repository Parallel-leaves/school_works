#include "flash.h"
#include "config.h"
#include "string.h"
//读取指定地址的半字(16位数据)
//faddr:读地址(此地址必须为2的倍数!!)
//返回值:对应数据.
u16 STMFLASH_ReadHalfWord(u32 faddr)
{
	return *(vu16*)faddr; 
}

#if STM32_FLASH_WREN	//如果使能了写   
//不检查的写入
//WriteAddr:起始地址
//pBuffer:数据指针
//NumToWrite:半字(16位)数   
void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
	u16 i;
	for(i=0;i<NumToWrite;i++)
	{
		FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
	    WriteAddr+=2;//地址增加2.
	}  
} 
//从指定地址开始写入指定长度的数据
//WriteAddr:起始地址(此地址必须为2的倍数!!)
//pBuffer:数据指针
//NumToWrite:半字(16位)数(就是要写入的16位数据的个数.)
#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE 1024 //字节
#else 
#define STM_SECTOR_SIZE	2048
#endif		 
u16 STMFLASH_BUF[STM_SECTOR_SIZE/2];//最多是2K字节
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
{
	u32 secpos;	   //扇区地址
	u16 secoff;	   //扇区内偏移地址(16位字计算)
	u16 secremain; //扇区内剩余地址(16位字计算)	   
 	u16 i;    
	u32 offaddr;   //去掉0X08000000后的地址
	if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))return;//非法地址
	FLASH_Unlock();						//解锁
	offaddr=WriteAddr-STM32_FLASH_BASE;		//实际偏移地址.
	secpos=offaddr/STM_SECTOR_SIZE;			//扇区地址  0~127 for STM32F103RBT6
	secoff=(offaddr%STM_SECTOR_SIZE)/2;		//在扇区内的偏移(2个字节为基本单位.)
	secremain=STM_SECTOR_SIZE/2-secoff;		//扇区剩余空间大小   
	if(NumToWrite<=secremain)secremain=NumToWrite;//不大于该扇区范围
	while(1) 
	{	
		STMFLASH_Read(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//读出整个扇区的内容
		for(i=0;i<secremain;i++)//校验数据
		{
			if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;//需要擦除  	  
		}
		if(i<secremain)//需要擦除
		{
			FLASH_ErasePage(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE);//擦除这个扇区
			for(i=0;i<secremain;i++)//复制
			{
				STMFLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//写入整个扇区  
		}else STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);//写已经擦除了的,直接写入扇区剩余区间. 				   
		if(NumToWrite==secremain)break;//写入结束了
		else//写入未结束
		{
			secpos++;				//扇区地址增1
			secoff=0;				//偏移位置为0 	 
		   	pBuffer+=secremain;  	//指针偏移
			WriteAddr+=secremain;	//写地址偏移	   
		   	NumToWrite-=secremain;	//字节(16位)数递减
			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;//下一个扇区还是写不完
			else secremain=NumToWrite;//下一个扇区可以写完了
		}	 
	};	
	FLASH_Lock();//上锁
}
#endif

//从指定地址开始读出指定长度的数据
//ReadAddr:起始地址
//pBuffer:数据指针
//NumToWrite:半字(16位)数
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
	u16 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);//读取2个字节.
		ReadAddr+=2;//偏移2个字节.	
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//WriteAddr:起始地址
//WriteData:要写入的数据
void Test_Write(u32 WriteAddr,u16 WriteData)   	
{
	STMFLASH_Write(WriteAddr,&WriteData,1);//写入一个字 
}

u8 buf[CONFIG_MSG_LEN];
void DefaultSet(void)//出厂值
{
	ConfigMsg.op[0] = 'J';//header: FIND;SETT;FACT...
	ConfigMsg.op[1] = 'T';
	ConfigMsg.op[2] = 'X';
	ConfigMsg.op[3] = 'D';
	ConfigMsg.mac[0] = 'J';
	ConfigMsg.mac[1] = 'T';
	ConfigMsg.mac[2] = 'X';
	ConfigMsg.mac[3] = 'D';
	ConfigMsg.mac[4] = 0x17;
	ConfigMsg.mac[5] = 0x07;
	ConfigMsg.sw_ver[0] = 1;
	ConfigMsg.sw_ver[1] = 0;
	ConfigMsg.lip[0] = 192;
	ConfigMsg.lip[1] = 168;
	ConfigMsg.lip[2] = 1;
	ConfigMsg.lip[3] = 111;
	ConfigMsg.sub[0] = 255;
	ConfigMsg.sub[1] = 255;
	ConfigMsg.sub[2] = 255;
	ConfigMsg.sub[3] = 0;
	ConfigMsg.gw[0] = 192;
	ConfigMsg.gw[1] = 168;
	ConfigMsg.gw[2] = 1;
	ConfigMsg.gw[3] = 1;
	ConfigMsg.dns[0] = 8;
	ConfigMsg.dns[1] = 8;
	ConfigMsg.dns[2] = 8;
	ConfigMsg.dns[3] = 8;
	ConfigMsg.Code[0] = 0x43;
	ConfigMsg.Code[1] = 0x01;
	ConfigMsg.Code[2] = 0x04;
	ConfigMsg.Code[3] = 0x01;
	ConfigMsg.Code[4] = 0x01;
	ConfigMsg.Code[5] = 0x01;
	ConfigMsg.DTMB_Freq[0] = 0x1D;
	ConfigMsg.DTMB_Freq[1] = 0xAE;
	ConfigMsg.DTMB_Freq[2] = 0xE0;
	ConfigMsg.DTMB_Freq[3] = 0x80;
	ConfigMsg.FM_Freq[0] = 0x25;
	ConfigMsg.FM_Freq[1] = 0xBC;
	ConfigMsg.Sx_Freq[0] = 0x01;
	ConfigMsg.Sx_Freq[1] = 0xB1;
	ConfigMsg.Password[0] = 1;
	ConfigMsg.Password[1] = 2;
	ConfigMsg.Password[2] = 3;
	ConfigMsg.Password[3] = 4;
	ConfigMsg.Password[4] = 5;
	ConfigMsg.Password[5] = 6;
	ConfigMsg.JTXD_Control = 0;
	ConfigMsg.dhcp = 0;
	ConfigMsg.debug = 1;
	ConfigMsg.fw_len = 0;
	ConfigMsg.state = NORMAL_STATE;
	STMFLASH_Write(STM32_FLASH_BASE,(u16 *)&ConfigMsg,CONFIG_MSG_LEN);
}


