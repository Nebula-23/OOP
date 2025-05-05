#pragma once
#ifndef CANVAS_H
#define CANVAS_H
#include <iostream>

class Canvas {
private:
	static const int WIDTH = 61; // 마지막에 결승선 경기장 크기는 60*7
	static const int HEIGHT = 7;
	int map[HEIGHT][WIDTH];

public:
	Canvas() {
		for (int y= 0; y< HEIGHT; ++y)
			for (int x = 0; x < WIDTH; ++x) 
			{
				map[y][x] = 0; // 맵을 모두 초기화
			}
		for (int i = 0; i < HEIGHT; ++i) 
		{
			map[i][60] = -1;
		}
	}


void setTile(int y, int x, int posX) {
	map[y][posX] = 0; // 현재 위치 0으로 초기화
	map[y][x] = y + 1;
}

void printMap() // 맵출력함수
{
	for (int h = 0; h < WIDTH; h++) {
		bool isH = false;
		for (int w = 0; w < WIDTH; w++)
		{
			if (map[h][w] == -1)std::cout << '|';
			else if (map[h][w] != 0)
			{
				std::cout << map[h][w]; isH = true;
			}
			else if (!isH)std::cout << '.';
			else std::cout << ' ';
		}
		std::cout << '\n';
	}
}
};
#endif // !CANVAS_H

