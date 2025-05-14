#pragma once
#ifndef CANVAS_H
#define CANVAS_H
#include <iostream>
#include <algorithm>
#include <random>
#include<string>

const std::string h_mark_arr[10] = { "+","@","#","8","&","¥","$","%","§","¶" };
class Canvas {
private:
	static const int WIDTH = 61; // 마지막에 결승선 경기장 크기는 60*7
	static const int HEIGHT = 7;
	int map[HEIGHT][WIDTH];
	std::string h_mark[HEIGHT]; // 말 문자 

public:
	Canvas() {
		for (int y = 0; y < HEIGHT; ++y)
			for (int x = 0; x < WIDTH; ++x)
			{
				map[y][x] = 0; // 맵을 모두 초기화
			}
		for (int i = 0; i < HEIGHT; ++i)
		{
			map[i][60] = -1;
		}
		// 배열 복사 및 셔플
		std::string temp[10];
		std::copy(std::begin(h_mark_arr), std::end(h_mark_arr), temp);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::shuffle(std::begin(temp), std::end(temp), gen);

		for (int i = 0; i < HEIGHT; ++i)
			h_mark[i] = temp[i];
	}

	void set_player(int p_index) { //레이스 클래스에서 사용 
		h_mark[p_index] = "★";//플레이어 말 기호
	}


	void set_tile(int y, int x, int posX) {
		map[y][posX] = 0; // 현재 위치 0으로 초기화
		map[y][x] = y + 1;
	}

	void printMap() // 맵출력함수
	{
		for (int h = 0; h < HEIGHT; h++) {
			bool isH = false;
			for (int w = 0; w < WIDTH; w++)
			{
				if (map[h][w] == -1)std::cout << '|';
				else if (map[h][w] != 0)
				{
					std::cout << h_mark[h]; isH = true;
				}
				else if (!isH)std::cout << '.';
				else std::cout << ' ';
			}
			std::cout << '\n';
		}
	}
};
#endif // !CANVAS_H

