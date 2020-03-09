#include"snack.h"

#include<stdlib.h>

pos head,speed;
pos food,body[20];
u16 length,score;

sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;



void SnackInit()
{
	
	food.x=rand()%8;
	food.y=rand()%8;
	head.x=3;
	head.y=3;
	speed.x=1;
	speed.y=0;
	length=2;
	score=0;
	body[0].x=2;
	body[0].y=3;
	body[1].x=1;
	body[1].y=3;
}

void snack_move()
{
	u16 i;
	slow++;
	if(slow==30)       //控制小蛇移动的快慢
	{
		slow=0;
		
		
		if(speed.x||speed.y )    //蛇身移动的条件：蛇头必须有速度，不然不移动
		{
			
			for(i=length-1;i>0;i--)
			{
				body[i].x=body[i-1].x;
				body[i].y=body[i-1].y;
			}
			body[0].x=head.x;body[0].y=head.y;
		}
		head.x=head.x+speed.x;
		head.y=head.y+speed.y;  
		if(speed.x==1&&head.x==8)
			head.x=0;
		if(speed.x==-1&&head.x==-1)
			head.x=7;
		if(speed.y==1&&head.y==8)
			head.y=0;
		if(speed.y==-1&&head.y==-1)
			head.y=7;
	}

		
}



void snack_turn()
{
	if(k1==0)
	{
		delay(1);
		if(k1==0&&speed.x!=0)
		{
		 	speed.x=0;
			speed.y=-1;
		}
	//	while(!k1);
	}
	if(k2==0)
	{
		delay(1);
		if(k2==0&&speed.y!=0)
		{
			speed.y=0;
			speed.x=-1;	
		}
	//	while(!k2);
	}

	if(k3==0)
	{
		delay(1);
		if(k3==0&&speed.x!=0)
		{
		 	speed.x=0;
			speed.y=1;
		}
	//	while(!k3);
	}
	if(k4==0)
	{
		delay(1);
		if(k4==0&&speed.y!=0)
		{
			speed.y=0;
			speed.x=1;
		}
	//	while(!k4);
	}	

}


void snack_add()
{
	u16 i;
	
	if((head.x)==food.x&&(head.y)==food.y)
	{
			
		length++;
		for(i=length-1;i>0;i--)
		{
			body[i].x=body[i-1].x;  
			body[i].y=body[i-1].y;
		}
		body[0].x=head.x;
		body[0].y=head.y;
		head.x=food.x;
		head.y=food.y;

		

		food.x=rand()%8;
		food.y=rand()%8;
		while(head.x==food.x&&head.y==food.y)
		{
			food.x=rand()%8;
			food.y=rand()%8;
		}
		for(i=0;i<length;i++)
		{
			while(body[i].x==food.x&&body[i].y==food.y)
			{
			 	food.x=rand()%8;
				food.y=rand()%8;
			}
		}		

	}
}


void snack_death()
{
	u16 i,flag=1;
	for(i=1;i<length;i++)
	{
		if(head.x==body[i].x&&head.y==body[i].y)
		{
			flag=0;
			speed.x=0;
			speed.y=0;
		}	
	}
	if(flag==0)
	{
		u16 i;
		u8  hang_1[8]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
		u8 lie_cry[8]={0x20,0x30,0x22,0x04,0x04,0x22,0x30,0x20};
		while(k4)
		{
			for(i=0;i<8;i++)
			{
				P0=hang_1[i];
				_74hc595send(lie_cry[i]);
				delay(1);
				_74hc595send(0x00);
			}
		}
		led=0xff;
		welcome();
		SnackInit();
			
	}
}

void snack_score()
{
	score=length-2;
	switch(score)
	{
		case 1:led=0xfe;break;
		case 2:led=0xfc;break;
		case 3:led=0xf8;break;
		case 4:led=0xf0;break;
		case 5:led=0xe0;break;
		case 6:led=0xc0;break;
		case 7:led=0x80;break;
		case 8:led=0x00;break;
		default:break;	
	}
}


void welcome()
{
	u8  hang_1[8]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
	u8 lie_2[8]={0x00,0x00,0x63,0x85,0x89,0x91,0x61,0x00};
	u8 lie_3[8]={0x00,0x00,0x42,0x81,0x91,0x91,0x6e,0x00};
	u8 lie_laugh[8]={0x20,0x40,0x24,0x02,0x02,0x24,0x40,0x20};
	u8  lie_1[8]={0x00,0x00,0x00,0x22,0x7e,0x02,0x00,0x00};
	u16 i,t=0;
	while(t<200)
	{
		t++;
		for(i=0;i<8;i++)
		{
			P0=hang_1[i];
			_74hc595send(lie_laugh[i]);
			delay(1);
			_74hc595send(0x00);
		}
	}
	t=0;
	while(t<100)
	{
		t++;
		for(i=0;i<8;i++)
		{
			P0=hang_1[i];
			_74hc595send(lie_3[i]);
			delay(1);
			_74hc595send(0x00);
		}
	}
	t=0;
	while(t<100)
	{
		t++;
		for(i=0;i<8;i++)
		{
			P0=hang_1[i];
			_74hc595send(lie_2[i]);
			delay(1);
			_74hc595send(0x00);
		}
	}
	t=0;
	while(t<100)
	{
		t++;
		for(i=0;i<8;i++)
		{
			P0=hang_1[i];
			_74hc595send(lie_1[i]);
			delay(1);
			_74hc595send(0x00);
		}
	}	
}


void snack_circulation()
{
	snack_move();
	snack_turn();
	snack_add();
	snack_death();
	snack_score();
}