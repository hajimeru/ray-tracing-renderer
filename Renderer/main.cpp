// Renderer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <ctime>

#include "Local_illumination.h"

int main()
{
	clock_t start, finish;
	double duration;
	start = clock();


	MoreAndMoreLight();


	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f seconds\n", duration);
}


