#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

class Horse_name {
private:
    std::vector<std::vector<std::string>> names;  // ǰ���� �̸���
    std::mt19937 gen;  // ���� ������

public:
    Horse_name() : gen(std::random_device{}()) {
        // ǰ���� �̸��� �ʱ�ȭ
        names = {
            {"Ʈ�� �ͺ�", "��ȣ �� �θ���", "����� ����ſ�", "������ �ĸ�", "����Ʈ ����", 
            "���ĳ� ��Ű", "���̿� ��ī��", "���̳׽� ����", "��ũ�����"},  // ���ָ�
            {"Ÿ��Ű ��Ʋ", "�� �ܵ��� �Ļ�", "�ø��콺 �ɺ���", "�伾 ����", "����� ��ũ", 
            "���� ũ��", "��ġī�� źȣ����", "���� ���", "������ �Ƹ���"},  // ���ึ
            {"��ī�� ���̿�", "�ɺ��� �絹��", "���̿� ��Į��", "�׷��� ����", "���̽� ����ó", 
            "���� Ƽ��", "���� �׷��", "����Ÿ ����̾�", "����� ���̾Ƹ��"},  // ���Ը�
            {"���� �Ƹ���", "����Ÿ Ÿ�̽�", "Ÿ���� ũ�ν�", "��帶�̾� ����", "�̳��� ��", 
            "������ �����Ʈ", "������긣", "�෣��", "�帲 ����"}  // ���Ը�
        };

    }

    std::string get_name(int breed) {
        // ǰ�� ��ȣ üũ
        if (breed < 0 || breed >= names.size()) return "InvalidBreed";

        auto& pool = names[breed];
        if (pool.empty()) return "NoName";

        // �̸��� ���� ������ �̸��� ����
        std::shuffle(pool.begin(), pool.end(), gen);
        std::string name = pool.back();
        pool.pop_back();  // �ߺ� ����
        return name;
    }
};
