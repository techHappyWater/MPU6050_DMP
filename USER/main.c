#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "mpu6050.h"  
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 

int main(void)
{

	float pitch,roll,yaw; 		//欧拉角

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	delay_init();	//延时初始化 
	LED_Init();		  			//初始化与LED连接的硬件接口
	MPU_Init();					//初始化MPU6050

	while(mpu_dmp_init())
	{
	delay_ms(20);
	}

	while(1)
	{
		delay_ms(2);
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		{
			LED=~LED;
		}
		printf("%f,%f,%f\r\n",pitch,roll,yaw);
	} 	
}
 


