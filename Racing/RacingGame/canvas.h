#pragma once
#ifndef CANVAS_H
#define CANVAS_H
#include <iostream>

class Canvas {
private:
	static const int WIDTH = 61; // �������� ��¼� ����� ũ��� 60*7
	static const int HEIGHT = 7;
	int map[HEIGHT][WIDTH];

public:
	Canvas() {
		for (int y = 0; y < HEIGHT; ++y)
			for (int x = 0; x < WIDTH; ++x)
			{
				map[y][x] = 0; // ���� ��� �ʱ�ȭ
			}
		for (int i = 0; i < HEIGHT; ++i)
		{
			map[i][60] = -1;
		}
	}


<<<<<<< HEAD
    void printMap() {
        for (int h = 0; h < HEIGHT; h++) {
            bool isH = false;
            for (int w = 0; w < WIDTH; w++) {
                if (map[h][w] == -1)std::cout << '|';
                else if (map[h][w] != 0) {
                    std::cout << map[h][w]; isH = true;
                }
<<<<<<< HEAD
                else if (!isH)std::cout << '.';
=======
                else if (!isH)std::cout << 'ㆍ';
>>>>>>> 4bafeb84af563646d56599ba00c2c249b2053710
                else std::cout << ' ';
            }
            std::cout << '\n'; 
        }
    } // 맵 출력 함수
=======
	void set_tile(int y, int x, int posX) {
		map[y][posX] = 0; // ���� ��ġ 0���� �ʱ�ȭ
		map[y][x] = y + 1;
	}

	void printMap() // ������Լ�
	{
		for (int h = 0; h < HEIGHT; h++) {
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
>>>>>>> 44d409c5cec3d7f0421b565d05fc0f17b2d1fc6d
};
#endif // !CANVAS_H

