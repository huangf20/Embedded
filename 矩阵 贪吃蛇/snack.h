#ifndef _snack_H
#define _snack_H

#ifndef led
#define led P2
#endif

#ifndef u16
#define u16 unsigned int 
#endif

#ifndef u8 
#define u8 unsigned char
#endif

#include<reg52.h>





typedef struct
{
	int x;
	int y;
}pos;

extern pos head,speed,food,body[20];//头文件中的变量定义前加entern，	再在某一个c文件的程序不加entern定义
extern u16 length,score;
static u16  slow=0;

void delay(u16 i);
void SnackInit();
void snack_move();
void snack_turn();
void snack_add();
void snack_death();
void snack_score();
void snack_circulation();
void _74hc595send(u8 _data);
void welcome();

//u16 key_value();


#endif