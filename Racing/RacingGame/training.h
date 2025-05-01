#ifndef TRAINING_H
#define TRAINING_H

#include<iostream>
#include "horse.h"

#define TRAINING_MHP 10 //�Ʒú� ���̳ʽ� ü��
#define INJRTYSTATS 100// �λ�� ���̴� ���� 
#define MIRACLE 10 //ü�� �̶�Ŭ ��ġ �ؿ��� �Ʒ� ������ �߰�

class training {
    horse_p& h;

    int training_hp; //100 �ִ� 
    bool isInjury; //�� �λ�, ���� ��λ� 

    void training_bass(bool &isInjury,int &m,int &s) {
        if (rand() % 101 < injury_percent(h)) {
            isInjury = true;
            h.set_spd(-INJRTYSTATS);
            h.set_sta(-INJRTYSTATS);
            h.set_pow(-INJRTYSTATS);
            h.set_guts(-INJRTYSTATS);
            std::cout << "�λ�! \t�� �ɷ�ġ - " << INJRTYSTATS << std::endl;
            return;
        }
        else {
            if (isInjury) {
                m = 90;
                s = (rand() % 11 + 30) * 0.9;
                isInjury = false;
                std::cout << "�λ� ���� ...\n";
            }
            else if (training_hp <= MIRACLE) { //ü��10�� �������� 
                m = 200;
                s = (rand() % 11 + 30) * 2;
                std::cout << "���� ����!\n";
            }
            else {
                m = 100;
                s = rand() % 11 + 30;
                std::cout << "����� �Ʒ�!\n";
            }
            training_hp -= TRAINING_MHP;
        }
    }
public:
    training(horse_p& horse) : h(horse),training_hp(100),isInjury(false) {}

    void training_speed(horse_p& h) {
        int m, s;
        training_bass(isInjury, m, s);
        std::cout << "���ǵ� + " << m << " | �Ŀ� + " << s << std::endl;
        h.set_spd( m);
        h.set_pow( s);
    }

    void training_endurance(horse_p& h) {
        int m, s;
        training_bass(isInjury, m, s);
        std::cout << "������ + " << m << " | �ټ� + " << s << std::endl;
        h.set_sta(m);
        h.set_guts(s);
    }

    void training_power(horse_p& h) {
        int m, s;
        training_bass(isInjury, m, s);
        std::cout << "�Ŀ� + " << m << " | ���ǵ� + " << s << std::endl;
        h.set_pow(m);
        h.set_spd(s);
    }

    void training_perseverance(horse_p& h) {
        int m, s;
        training_bass(isInjury, m, s);
        std::cout << "�ټ� + " << m << " | ������ + " << s << std::endl;
        h.set_guts(m);
        h.set_sta (s);
    }

    int injury_percent(horse_p& h) { //�Ʒ� hp�� �λ� Ȯ��
        if (training_hp <= 0) { return 70; }
        else if (training_hp <= 10) { return 60; }
        else if (training_hp <= 20) { return 50; }
        else if (training_hp <= 30) { return 30; }
        else if (training_hp <= 40) { return 20; }
        else { return 0; }
    }

    void rest(horse_p& h) {//�Ʒ� hp ȸ��
        if (isInjury) {
            isInjury = false;
            h.set_spd(INJRTYSTATS);
            h.set_sta(INJRTYSTATS);
            h.set_pow(INJRTYSTATS);
            h.set_guts(INJRTYSTATS);
            std::cout << "�λ��� ȸ�� ���� ���� ȸ��!\t";
        }
        int rest_hp = rand() % 41 + 30; // �ּ� 30~70
        training_hp += rest_hp;
        if (training_hp > 100) {
            rest_hp -= training_hp - 100;
            training_hp = 100;
        }
        std::cout << "ȸ���� ü��: " << rest_hp << std::endl;
    }
};

#endif // !TRAINING_H
