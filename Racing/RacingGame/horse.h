#ifndef HORSE_H
#define HORSE_H
#include<iostream>
#include<string>
#include<cmath>

#define BASELINE 1000 // ���� ����ġ(�̵����� ��� ���)

class horse_p {
protected:
    double spd;     //���ǵ�
    double pow;     //�Ŀ�
    double guts;    //�ټ�
    double sta; //������

    double breedMod[3]; // Ư�� ����ġ 0 �� 1 �� 2 ��
    double statMod[3];//���� ����ġ 0�� 1�� 2��

    int index_L; //�ε�����
    int index_N; //�ε��� ��
    double decimal_Point; //�޸��� ������ ���̴� �Ҽ��� ����� 
 
    std::string name; // ���̸� 
    std::string type; //������
public: 
    horse_p(double spd, double pow, double guts, double sta)
        : spd(spd), pow(pow), guts(guts), sta(sta),
        index_L(0),index_N(0), decimal_Point(0) {
        breedMod[0] = 0; breedMod[1] = 0; breedMod[2] = 0;
        statMod[0] = 0; statMod[1] = 0; statMod[2] = 0;
        name = "�⺻";
        type = "�⺻";
    }

    double get_spd() { return spd; }
    double get_guts() { return guts; }
    double get_pow() { return pow; }
    double get_sta() { return sta; }
    std::string get_name() { return name; }
    int get_index_L() { return index_L; }
    int get_index_N() { return index_N; }
    void set_spd(double spd) { this->spd += spd; }
    void set_guts(double guts) { this->guts += guts; }
    void set_pow(double pow) { this->pow += pow; }
    void set_sta(double sta) { this->sta += pow; }

    int location_where() {//���� �߹� �Ĺ� ��� ���ϰ� 1�� 2�� 3�� 
        if (index_N <= 20) return 0;
        else if (index_N <= 40)return 1;
        else return 2;
    } 
    void move() {
        double sM[3] = { statMod[0] * pow, statMod[1] * sta, statMod[2] * guts };
        int n = location_where();
        double distance = (spd / BASELINE) * (2.5 + (rand() % 11) / 10) + breedMod[n] * ( sM[n]/BASELINE) + decimal_Point;
        decimal_Point = fmod(distance, 1);
        index_L = index_N;
        index_N += static_cast<int>(distance);
    }
};


class front_Runner :public horse_p { //���ָ�
public:
    front_Runner(double spd, double pow, double guts, double sta) : horse_p(spd, pow, guts, sta) {
        breedMod[0] = 1.5; breedMod[1] = 1.3; breedMod[2] = 1.2;
        statMod[0] = 1.9; statMod[1] = 1.7; statMod[2] = 1.4;
        name = "��ũ���׸���";
        type = "���ָ�";
    }
};
class early_Speed :public horse_p { // ���ึ
public:
    early_Speed(double spd, double pow, double guts, double sta) : horse_p(spd, pow, guts, sta) {
        breedMod[0] = 1.4; breedMod[1] = 1.4; breedMod[2] = 1.2;
        statMod[0] = 1.8; statMod[1] = 1.8; statMod[2] = 1.6;
        name = "Ʈ���� ũ���";
        type = "���ึ";
    }
};
class stalker :public horse_p { // ���Ը�
public:
    stalker(double spd, double pow, double guts, double sta) : horse_p(spd, pow, guts, sta) {
        breedMod[0] = 1.3; breedMod[1] = 1.4; breedMod[2] = 1.3;
        statMod[0] = 1.6; statMod[1] = 1.8; statMod[2] = 1.8;
        name = "������긣";
        type = "���Ը�";
    }
};

class closer :public horse_p { // ���Ը�
public:
    closer(double spd, double pow, double guts, double sta) : horse_p(spd, pow, guts, sta) {
        breedMod[0] = 1.2; breedMod[1] = 1.3; breedMod[2] = 1.5;
        statMod[0] = 1.4; statMod[1] = 1.7; statMod[2] = 1.9;
        name = "��� ��";
        type = "���Ը�";
    }
};

#endif // !HORSE_H
