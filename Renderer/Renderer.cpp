// Renderer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include "tgaimage.h"
#include "Vector3.h"

const char* IMAGE_URL = "test.tga";


int main()
{
	Vector3 t11(2, 2, 2);
	Vector3 t12(3, 3, 3);
	double length = t12.Length();
	std::cout << t11.Dot(t12) << "\n";
	std::cout << t12.Normalize() << "\n";


}


