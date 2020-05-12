// liandianqi.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<string>
using namespace std;
int wait1 = 10, wait2 = 90;
float speed = 10;
string B = "左键", mode = "按住";

void menu();
void FAQ();
void help();
bool set();
void click();

int main()
{
	menu();

	//高位为1 表示键按下 值为负
	while (GetKeyState(VK_END) == 0)//end键==0 表示未按下进入死循环 直到按下end键结束循环
	{
		if (GetKeyState(VK_MBUTTON) && mode == "切换"){//鼠标中键
			click();
			continue; 
		}
		if (GetKeyState(VK_MBUTTON)<0 && mode == "按住") {
			click(); 
			continue;
		}
		if (GetKeyState(VK_LEFT)<0 && B != "左键") {//按下了左键 切换为左键
			B = "左键";
			menu(); 
		}
		if (GetKeyState(VK_RIGHT)<0 && B != "右键") {
			B = "右键"; 
			menu(); 
		}
		if (GetKeyState(VK_F1)<0)
			help();
		if (GetKeyState(VK_F2)<0) 
			FAQ();
		if (GetKeyState(VK_RSHIFT)<0) 
			while (set());//while用于输入错误后重新输入 
		if (GetKeyState(VK_RCONTROL)<0)//切换控制模式 
		{
			if (mode == "按住") 
				mode = "切换";
			else
				mode = "按住";
			while (GetKeyState(VK_RCONTROL)<0) 
				Sleep(10);
			menu();
		}
		if (GetKeyState(VK_RMENU))//暂停程序 
		{
			system("cls");
			cout << "程序已暂停，按[右ALT]继续...";
			while (GetKeyState(VK_RMENU))
				Sleep(10);
			menu();
		}
		Sleep(1);//防止循环太快
	}
}


void menu()//主要信息页面 
{
	system("cls");//清屏 
	cout << "查看操作说明请按[F1],常见问题请按[F2]" << endl << endl;
	cout << "当前控制模式：" << mode << endl << "当前控制按键：" << B << endl << "当前连点速度：" << speed << "次/s" << endl;
}
void FAQ()//常见问题 
{
	system("cls");
	cout << "为什么显示的点击速度和输入的点击速度不一样？" << endl;
	cout << "——该程序控制点击速度的时间单位为ms，因此请以显示速度为参考" << endl << endl;
	cout << "为什么实际点击速度和显示的点击速度不一样？" << endl;
	cout << "——受限于电脑硬件的处理速度影响，程序显示速度与实际速度有偏差为正常现象" << endl << endl;
	cout << "为什么使用起来会卡顿" << endl;
	cout << "——连点速度过快会大量消耗CPU资源，如有此现象建议降低点击速度" << endl << endl;
	cout << endl << "其他问题请在bilibili私信Alan7am" << endl << endl;
	Sleep(1000);
	system("PAUSE");//暂停程序 按任意键继续 
	menu();
}
void help()//操作说明 
{
	system("cls");
	cout << "[鼠标中键]：开始/暂停 连点" << endl << "[方向键←]：控制鼠标左键" << endl << "[方向键→]：控制鼠标右键" << endl;
	cout << "[右Ctrl]：切换控制模式" << endl << "[右Shift]：设置每秒连点次数" << endl << "[右Alt]：暂停程序" << endl << "[End]：中止程序" << endl << endl;
	Sleep(1000);
	system("PAUSE");
	menu();
}
bool set()//设置每秒连点次数(此处使用bool是因为有返回值) 
{
	cin.clear();//重置cin的错误状态 
	cin.sync();//清空cin的缓存数据，与cin.clear()搭配避免输入错误导致死循环 
	system("cls");
	cout << "请输入每秒点击次数：";
	cin >> speed;
	system("cls");
	if (speed<0) speed = speed*-1;
	if (speed<0.0001)//判断是否赋值过小或输入错误 
	{
		cout << "输入错误！";
		Sleep(1500);
		return 1;//返回值为1继续循环 
	}
	if (speed>1000)//若使用Sleep控制延时则speed不能大于1000，否则延时为0 
	{
		cout << "警告！大于1000次/秒的连点速度不可控，可能会导致电脑卡顿！" << endl;
		cout << "是否继续当前设定？" << endl << "1:是,保留设定         任意键:否,重新设定";
		_getch();//等待按下键盘 
		//if (GetKeyState(49)<0 || GetKeyState(97)<0) 
		//	speed = 9999;//该赋值无意义，只是告诉使用者速度达到极限 
		if(GetKeyState(VK_NUMPAD1)<0)
			speed = 9999;
		else 
			return 1;//返回值为1继续循环
	}

	wait1 = 500 / speed;
	if (wait1>10)
		wait1 = 10;
	wait2 = 1000 / speed - wait1;
	if (speed != 9999) 
		speed = (float)1000 / (wait1 + wait2);//计算理论速度，供使用者参考 

	menu();
	return 0;//返回值为0终止while循环
}
void click()//点击命令 
{
	if (B == "左键")
	{
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		Sleep(wait1);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		Sleep(wait2);
	}
	else
	{
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
		Sleep(wait1);
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		Sleep(wait2);
	}
}

