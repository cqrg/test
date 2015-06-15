/*
*********************************************************************************************************
*                                                ?/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2000, SEGGER Microcontroller Systeme GmbH          
*
*              ?/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed 
*              in any way. We appreciate your understanding and fairness.
*
* File        : MainTask.c
* Purpose     : Application program in windows simulator
*********************************************************************************************************
*/


#include "GUI.h"
#include "GUI_Protected.h"
#include "GUI.h"
#include "LCD_ConfDefaults.h"

#include "WM.h"
#include "DIALOG.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define CalendarX 35
#define CalendarY 90
#define ButtonX 40
#define ButtonY 205
#define ButtonDis 90
#define ButtonWidth 60
#define ButtonHeight 25
#define DataX 25
#define DataY 50
#define TimeX 190
#define TimeY 120

GUI_BITMAP bmMicriumLogo1;
GUI_BITMAP bmMicriumLogo2;
GUI_BITMAP bmMicriumLogo3;
GUI_BITMAP bmMicriumLogo4;
GUI_BITMAP bmdog;
GUI_BITMAP bm4;


/*
*******************************************************************
*
*              main()
*
*******************************************************************
*/
typedef struct
{
	int year;
	int mouth;
	int day;
	int hour;
	int minute;
	int second;
	int week;
}calendar;
int SEcont=0;
int secondm,minutem;
int Dy,Dy1,Dm,Dm1,Dd,Dd1,Dw;
int Th,Tm1,Tm,Tm2,Ts;

const GUI_BITMAP *pBitmap;

calendar c={2015,6,13,22,15,51};

void SetTimeMode(int i);
void DrawTimeGUI();
void RunTime();
void KeyTouch();
void ConWeek(int week);
const int isLeapYear(int year);
const int getMonthDays(int year,int mouth);
const int yearDays(int year);
const int isWeek(int year,int mouth,int day);
void printCalendar(int year,int mouth);//按日历格式打印


void MainTask(void) 
{
	Dy=DataX,Dy1=Dy+50,Dm=Dy1+24,Dm1=Dm+24,Dd=Dm1+24,Dd1=Dd+24,Dw=Dd1+24*2;
	Th=TimeX,Tm1=Th+24,Tm=Tm1+10,Tm2=Tm+24,Ts=Tm2+10;
	GUI_Init();
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(GUI_RED);
	GUI_Clear();
	pBitmap=&bm4;
    GUI_DrawBitmap(pBitmap,0,0);//显示位图
    GUI_SetTextMode(GUI_TM_TRANS | GUI_TM_REV);
    GUI_SetColor(GUI_BLUE);
    GUI_SetBkColor(GUI_WHITE);
    LCD_L0_FillRect(ButtonX, ButtonY, ButtonX+ButtonWidth, ButtonY+ButtonHeight);  
    GUI_SetFont(&GUI_FontHZ16);
    GUI_DispStringAt("SELECT", ButtonX+7, ButtonY+5);  
    LCD_L0_FillRect(ButtonX+ButtonDis, ButtonY, ButtonX+ButtonDis+ButtonWidth, ButtonY+ButtonHeight);  
    GUI_DispStringAt("UP", ButtonX+ButtonDis+24, ButtonY+5);  
    LCD_L0_FillRect(ButtonX+ButtonDis*2, ButtonY, ButtonX+ButtonDis*2+ButtonWidth, ButtonY+ButtonHeight);
    GUI_DispStringAt("DOWN", ButtonX+ButtonDis*2+15, ButtonY+5);
    GUI_SetColor(GUI_BLACK);
    GUI_SetFont(&GUI_FontHZ24);
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_DispStringHCenterAt("万年历", 150,10);  

    while(1)
    {  
    	RunTime();
    	DrawTimeGUI();
    	printCalendar(c.year,c.mouth);
    	SetTimeMode(SEcont);
    	KeyTouch();
    }
}

void DrawTimeGUI()
{

	GUI_SetTextMode(GUI_TM_NORMAL);
	GUI_SetBkColor(GUI_WHITE);
	GUI_SetColor(GUI_BLACK);
	GUI_SetFont(&GUI_FontHZ24);
	GUI_DispDecAt( c.year, Dy,DataY,4);
	GUI_DispStringAt("年", Dy1,DataY);  
	GUI_DispDecAt( c.mouth, Dm,DataY,2);  	  
	GUI_DispStringAt("月", Dm1,DataY);  
	GUI_DispDecAt( c.day, Dd,DataY,2);  	  
	GUI_DispStringAt("日", Dd1,DataY);  
	GUI_DispStringAt("星期", Dw,DataY);  
	ConWeek(c.week=isWeek(c.year,c.mouth,c.day)+1);  
	GUI_SetFont(&GUI_FontHZ24);
	GUI_DispDecAt( c.hour,Th,TimeY,2); 
	GUI_DispStringAt(":", Tm1,TimeY);  
	GUI_DispDecAt( c.minute,Tm,TimeY,2);  
	GUI_DispStringAt(":", Tm2,TimeY);  
	GUI_DispDecAt( c.second, Ts,TimeY,2);  
	// GUI_Clear();
}

void RunTime()
{
	secondm=GUI_GetTime()/100;//获取时钟信号
	secondm%=10;
	if(secondm==9)	{c.second++;GUI_Delay(100);}
	if(c.second==60) 	{c.minute++;c.second=0; }
	if(c.second==-1) {c.second=59; c.minute--; }
	if(c.minute==60) {c.hour++;c.minute=0; }
	if (c.minute==-1) {c.minute=59;c.hour--; }
	if (c.hour==24) {c.day++;c.hour=0; }
	if (c.hour==-1) {c.hour=23;c.day--; }
	if (c.day==getMonthDays(c.year,c.mouth)+1) {c.mouth++;c.day=1; }
	if (c.day==0) {c.day=getMonthDays(c.year,c.mouth)-1;c.mouth--; }
	if (c.mouth>12) {c.year++;c.mouth=1; }
	if (c.mouth<1) {c.mouth=12;c.year--; }
	if (SEcont==7) {SEcont=0; }
}

void SetTimeMode(SEcont)
{
	GUI_SetFont(&GUI_FontHZ24);

	switch(SEcont)
	{
			//set c.second 
		case 1:  	
		GUI_SetColor(GUI_RED);
		GUI_DispDecAt(c.second, Ts,TimeY,2); 
		break;

			//set c.minute
		case 2:		
		GUI_SetColor(GUI_RED);
		GUI_DispDecAt(c.minute,Tm,TimeY,2); 
		break; 	

			//set c.hour
		case 3:
		GUI_SetColor(GUI_RED);
		GUI_DispDecAt(c.hour,Th,TimeY,2); 
		break;

			//set c.day
		case 4:
		GUI_SetColor(GUI_RED);
		GUI_DispDecAt(c.day, Dd,DataY,2); 
		break;

			//set c.mouth
		case 5:
		GUI_SetColor(GUI_RED);
		GUI_DispDecAt(c.mouth, Dm,DataY,2);
		break;

			//set c.year		
		case 6:
		GUI_SetColor(GUI_RED);
		GUI_DispDecAt(c.year, Dy,DataY,4); 
		break;

			//set mode
		default:
		GUI_SetTextMode(GUI_TM_TRANS);
		GUI_SetFont(&GUI_FontHZ24);
		GUI_SetColor(GUI_RED);
		break;
	}
}

void KeyTouch()
{
	GUI_PID_STATE TouchState;
	if(GUI_TOUCH_GetState(&TouchState))	 /* Get the touch position in pixel */
	{
		if((TouchState.x>ButtonX)&&(TouchState.x<ButtonX+ButtonWidth)&&(TouchState.y>ButtonY)&&(TouchState.y<ButtonY+ButtonHeight)) //触摸屏的点击判断
		{ 
			SEcont++;
			while(GUI_TOUCH_GetState(&TouchState));
		}
		if((TouchState.x>ButtonX+ButtonDis)&&(TouchState.x<ButtonX+ButtonDis+ ButtonWidth)&&(TouchState.y>ButtonY)&&(TouchState.y<ButtonY+ButtonHeight)) //触摸屏的点击判断
		{   
			if (SEcont==1) c.second++;
			else if (SEcont==2) c.minute++;
			else if (SEcont==3) c.hour++;
			else if (SEcont==4) c.day++;
			else if (SEcont==5) c.mouth++;
			else if (SEcont==6) c.year++;
			// while(GUI_TOUCH_GetState(&TouchState));
			GUI_Delay(60);
		}			
		if((TouchState.x>ButtonX+ButtonDis*2)&&(TouchState.x<ButtonX+ButtonDis*2+ButtonWidth)&&(TouchState.y>ButtonY)&&(TouchState.y<ButtonY+ButtonHeight)) //触摸屏的点击判断
		{   
			if (SEcont==1) c.second--;
			else if (SEcont==2) c.minute--;
			else if (SEcont==3) c.hour--;
			else if (SEcont==4) c.day--;
			else if (SEcont==5) c.mouth--;
			else if (SEcont==6) c.year--;
			// while(GUI_TOUCH_GetState(&TouchState));
			GUI_Delay(60);
		}	
	}
	GUI_Delay(50);
}

const int isLeapYear(int year)
{
	if((year%4==0&&year%100!=0)||(year%100==0&&year%400==0))
		return 1;
	else return 0;
}

const int getMonthDays(int year,int mouth){
	switch(mouth){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:return 31;break;
		case 4:
		case 6:
		case 9:
		case 11:return 30;break;
		case 2:
		if(isLeapYear(year))
		{
			return 29;
		}
		else{
			return 28;
		}
		break;
		default:return 0;break;
	}
}

const int yearDays(int year){
	if (isLeapYear(year)) return 366;
	else
		return 365;
}

const int isWeek(int year,int mouth,int day){
	int week;
	int temp=mouth;
	if(temp==1||temp==2)
	{
		temp+=12; year--;
	}
	week=(day+2*temp+3*(temp+1)/5+year+year/4-year/100+year/400)%7;
	return week;
}

void printCalendar(int year,int mouth){
	int i;
	GUI_SetColor(GUI_MAGENTA);
	GUI_SetFont(&GUI_FontHZ12);
	LCD_L0_FillRect(CalendarX, CalendarY, CalendarX+130,CalendarY+15);
	GUI_SetTextMode(GUI_TM_TRANS);
	// GUI_SetTextMode(GUI_TM_NORMAL);
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringAt(" 日 一 二 三 四 五 六", CalendarX,CalendarY+1);  //45,55
	GUI_SetColor(GUI_LIGHTMAGENTA);
	LCD_L0_FillRect(CalendarX, CalendarY+15, CalendarX+130, CalendarY+95);
	GUI_SetColor(GUI_BLACK);
	GUI_SetFont(&GUI_Font13_1);
	GUI_GotoXY(CalendarX,CalendarY+15);
	GUI_SetTextMode(GUI_TM_TRANS);
	//判断当前年当前月1日时是星期几
	for (i = 0; i <=isWeek(c.year,c.mouth,1) ; i++)
	{
		//设置非工作日为1号为灰色
		if((isWeek(c.year,c.mouth,1))==6) 
			GUI_SetColor(GUI_GRAY);
		if(isWeek(c.year,c.mouth,1)!=6)
		{
			GUI_DispString("      ");
		}
	}
	for (i = 1; i <=getMonthDays(c.year,c.mouth) ; i++)
	{
		//设置当前日期为高亮
		if(i==c.day)
		{
			GUI_SetColor(GUI_WHITE);
			GUI_SetBkColor(GUI_BLUE);
			GUI_SetTextMode(GUI_TM_NORMAL);
		}
		//对齐日历
		if(i<10)
		{
			GUI_DispString(" ");		

			GUI_DispDecSpace(i,4);
		}
		else
			GUI_DispDecSpace(i,4);
		GUI_SetColor(GUI_BLACK);
		GUI_SetTextMode(GUI_TM_TRANS);
		//设置非工作日为灰色且换行
		if((isWeek(c.year,c.mouth,i+1))==5) 
			GUI_SetColor(GUI_GRAY);
		if(isWeek(c.year,c.mouth,i+1)==6) 
		{
			GUI_SetColor(GUI_GRAY);
			GUI_DispString("\n");
			GUI_GotoX(CalendarX);
		}
	}
}

void ConWeek(int week)
{
	switch(week)
	{
		case 1:GUI_DispString("一");break;
		case 2:GUI_DispString("二");break;
		case 3:GUI_DispString("三");break;
		case 4:GUI_DispString("四");break;
		case 5:GUI_DispString("五");break;
		case 6:GUI_DispString("六");break;
		case 7:GUI_DispString("日");break;
	}
}
