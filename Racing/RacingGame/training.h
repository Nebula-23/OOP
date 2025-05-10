#ifndef TRAINING_H
#define TRAINING_H

#include<iostream>
#include "horse.h"

#define TRAINING_MHP 10 //�Ʒú� ���̳ʽ� ü��
#define MIRACLE 10 //ü�� �̶�Ŭ ��ġ �ؿ��� �Ʒ� ������ �߰�
#define MAX_STAT 1400 //�ƽ� ���� 

class training {
    horse& h;
    int training_hp = 0; //100 �ִ� 
    bool isInjury = 0; //�� �λ�, ���� ��λ� 
    int m_sta[4] = { 0 }; //�λ�� ���̳ʽ� ���� �����

    void training_bass(bool& isInjury, int& m, int& s) { //Ʈ���̴� ���̽� M< ������������, S<���� ��������
        if (rand() % 101 < injury_percent(h)) { //�λ�� ���ɷ�ġ ����
            isInjury = true;
            m_sta[0] = static_cast<int>(h.get_spd() * 0.1);
            m_sta[1] = static_cast<int>(h.get_sta() * 0.1);
            m_sta[2] = static_cast<int>(h.get_pow() * 0.1);
            m_sta[3] = static_cast<int>(h.get_guts() * 0.1);
            h.set_spd(-m_sta[0]);
            h.set_sta(-m_sta[1]);
            h.set_pow(-m_sta[2]);
            h.set_guts(-m_sta[3]);
            std::cout << "�λ�! \t�� �ɷ�ġ - 10%" << std::endl;
            training_hp = 100;
            return;
        }
        else {
            if (training_hp <= MIRACLE) { //ü��10�� �������� 
                m = 200;
                s = (rand() % 11 + 30) * 2;
                std::cout << "���� ����!\n";
            }
            else { //����ϰ� �Ʒ��ϴ°� 
                m = 100;
                s = rand() % 11 + 30;
                std::cout << "����� �Ʒ�!\n";
            }
            training_hp -= TRAINING_MHP;
            if (training_hp < 0)training_hp = 0;
            isInjury = false;
        }
    }
public:
    training(horse& horse) : h(horse), training_hp(100), isInjury(false) {}

    void training_speed(horse& h) { //�� ���� �Ʒ� 
        int m, s;
        training_bass(isInjury, m, s);
        int spd = h.get_spd();
        int pow = h.get_pow();
        if (spd + m > MAX_STAT) {
            m -= spd + m - MAX_STAT;
        }
        if (pow + s > MAX_STAT) {
            s -= pow + s - MAX_STAT;
        }
            
        if (!isInjury) {
            std::cout << "���ǵ� + " << m << " | �Ŀ� + " << s << std::endl;
            h.set_spd(m);
            h.set_pow(s);
        }
    }

    void training_endurance(horse& h) {
        int m, s;
        training_bass(isInjury, m, s);
        if (!isInjury) {
            int sta = h.get_sta();
            int guts = h.get_guts();
            if (sta + m > MAX_STAT) {
                m -= sta + m - MAX_STAT;
            }
            if (guts + s > MAX_STAT) {
                s -= guts + s - MAX_STAT;
            }
            std::cout << "������ + " << m << " | �ټ� + " << s << std::endl;
            h.set_sta(m);
            h.set_guts(s);
        }
    }

    void training_power(horse& h) {
        int m, s;
        training_bass(isInjury, m, s);
        if (!isInjury) {
            int pow = h.get_pow();
            int spd = h.get_spd();
            if (pow + m > MAX_STAT) {
                m -= pow + m - MAX_STAT;
            }
            if (spd + s > MAX_STAT) {
                s -= spd + s - MAX_STAT;
            }
            std::cout << "�Ŀ� + " << m << " | ���ǵ� + " << s << std::endl;
            h.set_pow(m);
            h.set_spd(s);
        }
    }

    void training_perseverance(horse& h) {
        int m, s;
        training_bass(isInjury, m, s);
        if (!isInjury) {
            int guts = h.get_guts();
            int sta = h.get_sta();
            if (guts + m > MAX_STAT) {
                m -= guts + m - MAX_STAT;
            }
            if (sta + s > MAX_STAT) {
                s -= sta + s - MAX_STAT;
            }
            std::cout << "�ټ� + " << m << " | ������ + " << s << std::endl;
            h.set_guts(m);
            h.set_sta(s);
        }
    }

    int injury_percent(horse& h) { //�Ʒ� hp�� �λ� Ȯ�� 
        if (training_hp <= 0) { return 70; }
        else if (training_hp <= 10) { return 60; }
        else if (training_hp <= 20) { return 50; }
        else if (training_hp <= 30) { return 30; }
        else if (training_hp <= 40) { return 20; }
        else { return 0; }
    }

    void rest(horse& h) {//�Ʒ� hp ȸ��
        if (isInjury) { //�λ��Ծ����� �Ʒ��ϸ� �������� �ٽ� ȸ������
            double rcv_pct = (static_cast<double>(rand() % 51 + 50)) / 100; //50~100��
            isInjury = false;
            h.set_spd(static_cast<int>(m_sta[0] * rcv_pct));
            h.set_sta(static_cast<int>(m_sta[1] * rcv_pct));
            h.set_pow(static_cast<int>(m_sta[2] * rcv_pct));
            h.set_guts(static_cast<int>(m_sta[3] * rcv_pct));
            std::cout << "�λ��� ȸ�� ���� ���� " << rcv_pct * 100 << "% ȸ��!";
            return;
        }
        int rest_hp = rand() % 41 + 30; // �ּ� 30~70
        training_hp += rest_hp;
        if (training_hp > 100) {
            rest_hp -= training_hp - 100;
            training_hp = 100;
        }
        std::cout << "ȸ���� ü��: " << rest_hp << std::endl;
    }
    //�÷��̾� hp ǥ�ÿ� ����? �߰�
    int get_hp()  {
        return training_hp;
    }

};

#endif // !TRAINING_H
