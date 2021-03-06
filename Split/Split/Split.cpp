// Split.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<GL/glut.h>
using namespace std;

//其实还是自己设定的四个点
int p1[] = { 150, 100 };
int p2[] = { 100, 100 };
int p3[] = { 200, 200 };
int p4[] = { 150, 250 };

//定义显示画板，也就是背景大小
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);//RGB均为1，说明是白色
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 250, 0.0, 250);//会形成一个正方形
}

//定义切割函数，输入任意四边形顶点分割为2个三角形//本函数直接包括绘制与切割
void Cut(const GLint*v1, const GLint*v2, const GLint*v3, const GLint*v4)
{
	glColor3f(1.0f, 2.0f, 0.0f);    //设置绘图颜色，本次作业设置为黄色
	glBegin(GL_TRIANGLE_STRIP);//画一个四边形（两个三角形条带就是四边形了）
	glVertex2iv(v1);
	glVertex2iv(v2);
	glVertex2iv(v4);
	glVertex2iv(v3);
	glEnd();
	//////////////////////////////////////////////////////////
	glColor3f(0.0f, 1.0f, 2.0f);    //设置绘图颜色
									//第一个三角形 n=1 顺序为 v1 v2 v4
	glBegin(GL_LINE_LOOP);
	glVertex2iv(v1);
	glVertex2iv(v2);
	glVertex2iv(v4);
	glEnd();

	//第二个三角形 n=2 顺序为 v4 v3 v2
	glBegin(GL_LINE_LOOP);
	glVertex2iv(v4);
	glVertex2iv(v3);
	glVertex2iv(v2);
	glEnd();
}

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);   //清空颜色缓冲池
	Cut(p1, p2, p3, p4);			//执行剪切指令
	glFlush();						//执行OpenGL指令列表中的指令
}

int _tmain(int argc, _TCHAR* argv[])
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    //设置显示模式
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glutInitWindowSize(500, 500); //设置窗口大小
	glutInitWindowPosition(200, 200);   //设置窗口在屏幕上的位置
	glutCreateWindow("201809第二次计算机图形学A作业程序-分解四边形Split");		//创建窗口并给出标题

	init();//绘制画布
	glutDisplayFunc(renderScene);	 //注册显示窗口时回调函数renderScene
	glutMainLoop();					 //循环，测试得出，如果注释掉会闪退
	return 0;
}

