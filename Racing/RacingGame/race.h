#pragma once
#include"canvas.h"
#include"horse.h"
#include <array>
#include <algorithm>
#include <random>

class Race {
private:
    static const int HORSE_COUNT = 7;

    // canvas ����
    canvas canvas;

    int lane = rand() % HORSE_COUNT; // �÷��̾� ���� ��÷;
    std::array<int, 6> cpu_type = { 0, 1, 1, 2, 2, 3 }; //cpu Ư�� �迭(���� ����� ���� ���)

    horse horses[HORSE_COUNT];       // �� �� �迭 ����
    bool finished[HORSE_COUNT] = {}; // ���� ��¼��� �������� Ȯ��
    int rank[HORSE_COUNT] = {};      // ���� ���� ����

public:
    Race(const horse& player, int tier) { // �÷��̾� �� �Է�, ���� ���̽� Ƽ�� �Է�

        // CPU Ÿ�� ����
        std::mt19937 g(std::random_device{}());
        std::shuffle(cpu_type.begin(), cpu_type.end(), g);

        horses[lane] = player; // �÷��̾� �� ����

        for (int i = 0, j = 0; i < HORSE_COUNT; i++) { // �� ����
            if (i != lane)
                horses[i] = horse("", cpu_type[j++], tier);
        }
    }

    void tie_breaker() { // ������ �˻�
        
    }

    void start() {
        int finished_count = 0;

        while (finished_count < HORSE_COUNT) {
            int tie_count = 0; // ������ ���
            
            for (int i = 0; i < HORSE_COUNT; ++i) {
                if (finished[i]) continue;

                horses[i].move(); // �� �̵�

                int prev_pos = horses[i].get_prev_pos();
                int curr_pos = horses[i].get_position();

                if (curr_pos >= 60) {
                    canvas.set_tile(i, 60, prev_pos); // ��¼��� ������ �� ��ġ ����
                    finished[i] = true;
                    ++finished_count;
                    ++tie_count;
                }
                else {
                    canvas.set_tile(i, curr_pos, prev_pos); // �Ϲ� �̵� ó��
                }
            }

            if (tie_count >= 2) {
                tie_breaker();
            }

        }


    }

 
    // ��ü ������
    // �� ��� ���
    // ������ ����
};
