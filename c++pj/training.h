#ifndef TRAINING_H
#define TRAINING_H

#include<iostream>
#include "horse.h"

#define TRAINING_MHP 10 //훈련별 마이너스 체력
#define INJRTYSTATS 100// 부상시 깍이는 스탯 
#define MIRACLE 10 //체력 미라클 수치 밑에서 훈련 성공시 추가

class training {
    horse& h;
    int training_hp; //100 최대 
    bool isInjury; //참 부상, 거짓 노부상 

    void training_bass(bool& isInjury, int& m, int& s) { //트레이닝 베이스 M< 메인증가스탯, S<서브 증가스탯
        if (rand() % 101 < injury_percent(h)) { //부상시 모든능력치 감소
            isInjury = true;
            h.set_spd(-INJRTYSTATS);
            h.set_sta(-INJRTYSTATS);
            h.set_pow(-INJRTYSTATS);
            h.set_guts(-INJRTYSTATS);
            std::cout << "부상! \t전 능력치 - " << INJRTYSTATS << std::endl;
            return;
        }
        else {
            if (isInjury) { //부상이있는데 훈련할경우 부상이풀리지만 스탯획득에 -디버프
                m = 90;
                s = (rand() % 11 + 30) * 0.9;
                isInjury = false;
                std::cout << "부상 직후 ...\n";
            }
            else if (training_hp <= MIRACLE) { //체력10밑 극적성공 
                m = 200;
                s = (rand() % 11 + 30) * 2;
                std::cout << "극적 성공!\n";
            }
            else { //평범하게 훈련하는것 
                m = 100;
                s = rand() % 11 + 30;
                std::cout << "평범한 훈련!\n";
            }
            training_hp -= TRAINING_MHP;
        }
    }
public:
    training(horse& horse) : h(horse), training_hp(100), isInjury(false) {}

    void training_speed(horse& h) { //각 스탯 훈련 
        int m, s;
        training_bass(isInjury, m, s);
        if (!isInjury) {
            std::cout << "스피드 + " << m << " | 파워 + " << s << std::endl;
            h.set_spd(m);
            h.set_pow(s);
        }
    }

    void training_endurance(horse& h) {
        int m, s;
        training_bass(isInjury, m, s);
        if (!isInjury) {
            std::cout << "지구력 + " << m << " | 근성 + " << s << std::endl;
            h.set_sta(m);
            h.set_guts(s);
        }
    }

    void training_power(horse& h) {
        int m, s;
        training_bass(isInjury, m, s);
        if (!isInjury) {
            std::cout << "파워 + " << m << " | 스피드 + " << s << std::endl;
            h.set_pow(m);
            h.set_spd(s);
        }
    }

    void training_perseverance(horse& h) { 
        int m, s;
        training_bass(isInjury, m, s);
        if (!isInjury) {
            std::cout << "근성 + " << m << " | 지구력 + " << s << std::endl;
            h.set_guts(m);
            h.set_sta(s);
        }
    }

    int injury_percent(horse& h) { //훈련 hp별 부상 확률 
        if (training_hp <= 0) { return 70; }
        else if (training_hp <= 10) { return 60; }
        else if (training_hp <= 20) { return 50; }
        else if (training_hp <= 30) { return 30; }
        else if (training_hp <= 40) { return 20; }
        else { return 0; }
    }

    void rest(horse& h) {//훈련 hp 회복
        if (isInjury) { //부상입었을때 훈련하면 잃은스탯 다시 회복해줌
            isInjury = false;
            h.set_spd(INJRTYSTATS);
            h.set_sta(INJRTYSTATS);
            h.set_pow(INJRTYSTATS);
            h.set_guts(INJRTYSTATS);
            std::cout << "부상후 회복 잃은 스탯 회복!\t";
        }
        int rest_hp = rand() % 41 + 30; // 최소 30~70
        training_hp += rest_hp;
        if (training_hp > 100) {
            rest_hp -= training_hp - 100;
            training_hp = 100;
        }
        std::cout << "회복된 체력: " << rest_hp << std::endl;
    }

    int get_hp() { return training_hp;};
};

#endif // !TRAINING_H
