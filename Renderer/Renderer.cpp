// Renderer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include "tgaimage.h"


const char* IMAGE_URL = "test.tga";


int main()
{
	TGAImage image(255, 255, TGAImage::RGB);
	for (int i = 0; i < image.get_width(); ++i) {
		for (int j = 0; j < image.get_height(); ++j) {
			image.set(i, j, TGAColor(i, j, 0));
		}
	}
	image.write_tga_file(IMAGE_URL);
	
}


