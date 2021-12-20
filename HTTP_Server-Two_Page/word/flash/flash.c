#include "flash.h"
#include "config.h"
#include "string.h"
//��ȡָ����ַ�İ���(16λ����)
//faddr:����ַ(�˵�ַ����Ϊ2�ı���!!)
//����ֵ:��Ӧ����.
u16 STMFLASH_ReadHalfWord(u32 faddr)
{
	return *(vu16*)faddr; 
}

#if STM32_FLASH_WREN	//���ʹ����д   
//������д��
//WriteAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToWrite:����(16λ)��   
void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
	u16 i;
	for(i=0;i<NumToWrite;i++)
	{
		FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
	    WriteAddr+=2;//��ַ����2.
	}  
} 
//��ָ����ַ��ʼд��ָ�����ȵ�����
//WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ2�ı���!!)
//pBuffer:����ָ��
//NumToWrite:����(16λ)��(����Ҫд���16λ���ݵĸ���.)
#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE 1024 //�ֽ�
#else 
#define STM_SECTOR_SIZE	2048
#endif		 
u16 STMFLASH_BUF[STM_SECTOR_SIZE/2];//�����2K�ֽ�
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
{
	u32 secpos;	   //������ַ
	u16 secoff;	   //������ƫ�Ƶ�ַ(16λ�ּ���)
	u16 secremain; //������ʣ���ַ(16λ�ּ���)	   
 	u16 i;    
	u32 offaddr;   //ȥ��0X08000000��ĵ�ַ
	if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))return;//�Ƿ���ַ
	FLASH_Unlock();						//����
	offaddr=WriteAddr-STM32_FLASH_BASE;		//ʵ��ƫ�Ƶ�ַ.
	secpos=offaddr/STM_SECTOR_SIZE;			//������ַ  0~127 for STM32F103RBT6
	secoff=(offaddr%STM_SECTOR_SIZE)/2;		//�������ڵ�ƫ��(2���ֽ�Ϊ������λ.)
	secremain=STM_SECTOR_SIZE/2-secoff;		//����ʣ��ռ��С   
	if(NumToWrite<=secremain)secremain=NumToWrite;//�����ڸ�������Χ
	while(1) 
	{	
		STMFLASH_Read(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//������������������
		for(i=0;i<secremain;i++)//У������
		{
			if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;//��Ҫ����  	  
		}
		if(i<secremain)//��Ҫ����
		{
			FLASH_ErasePage(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE);//�����������
			for(i=0;i<secremain;i++)//����
			{
				STMFLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//д����������  
		}else STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
		if(NumToWrite==secremain)break;//д�������
		else//д��δ����
		{
			secpos++;				//������ַ��1
			secoff=0;				//ƫ��λ��Ϊ0 	 
		   	pBuffer+=secremain;  	//ָ��ƫ��
			WriteAddr+=secremain;	//д��ַƫ��	   
		   	NumToWrite-=secremain;	//�ֽ�(16λ)���ݼ�
			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;//��һ����������д����
			else secremain=NumToWrite;//��һ����������д����
		}	 
	};	
	FLASH_Lock();//����
}
#endif

//��ָ����ַ��ʼ����ָ�����ȵ�����
//ReadAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToWrite:����(16λ)��
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
	u16 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);//��ȡ2���ֽ�.
		ReadAddr+=2;//ƫ��2���ֽ�.	
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//WriteAddr:��ʼ��ַ
//WriteData:Ҫд�������
void Test_Write(u32 WriteAddr,u16 WriteData)   	
{
	STMFLASH_Write(WriteAddr,&WriteData,1);//д��һ���� 
}

u8 buf[CONFIG_MSG_LEN];
void DefaultSet(void)//����ֵ
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


