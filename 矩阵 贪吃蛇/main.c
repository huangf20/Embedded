#include"reg52.h"
#include"snack.h"
#include<intrins.h>

u8  canvas[8][8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
					0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
					0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
					0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
					0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
					0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
					0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
					0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

sbit SRCLK=P3^6;//移位管脚
sbit RC_LK=P3^5;//存储位管脚
sbit SER=P3^4;

u8  dat[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
u8 hang[8]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};

void delay(u16 i)
{
	u16 j=100*i;
	while(j--);
}
void _74hc595send(u8 _data)
{
	u8 i;
	SRCLK=0;
	RCLK=0;
	for(i=0;i<8;i++)
	{
		SER=_data>>7;
		_data<<=1;
		SRCLK=1;
		_nop_();
		_nop_();
		SRCLK=0;

			
	}
	RC_LK=1;
	_nop_();//记忆周期
	_nop_();
	RC_LK=0;
}


void addDateToCanvos()
{
	u16 i,j;
	for(i=0;i<8;i++)      //画蛇头
		for(j=0;j<8;j++)
		{
			if(i==head.y&&j==head.x||i==food.y&&j==food.x)
			{
				canvas[i][j]=0x01;
			}
			
		}
	for(i=0;i<length;i++)
	{
		canvas[body[i].y][body[i].x]=0x01;
	}		
}

void Datapros()
{
	u16 i;
	for(i=0;i<8;i++)
	{
		dat[i]=canvas[7][i]*1+canvas[6][i]*2+canvas[5][i]*4+canvas[4][i]*8+
		canvas[3][i]*16+canvas[2][i]*32+canvas[1][i]*64+canvas[0][i]*128;
	}	
}
void draw()
{
	u16 i,j;
	
		Datapros();
		for(i=0;i<8;i++)
		{
			P0=hang[i];
			_74hc595send(dat[i]);
			delay(1);
			_74hc595send(0x00);
		}
		delay(1);
		for(i=0;i<8;i++)
			for(j=0;j<8;j++)
				{
					canvas[i][j]=0x00;
				}
}

void _51Draw()
{
	addDateToCanvos();
	Datapros();
	draw();
}

void main()
{
	u16 i=1;
	welcome();
	SnackInit();
	while(i>0)
	{
		
		
		_51Draw();
		snack_circulation();
		
		
			
	}
	
}