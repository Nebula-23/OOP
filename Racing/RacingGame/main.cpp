#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include "horse.h"
#include "training.h"
#include "race.h"
#include "UI.h"

const int startStat = 100.0;

using namespace std;

horse select_horse();
//void print_basic(int month, horse* player, training& trainer);
void print_stat(int month, horse* player, training& trainer);

int main() { //cols ���� , lines ���� cols=140 lines=30
    int start_format;
    init_console_size(); // �ܼ� ũ�� �ʱ�ȭ
    //init_game_ui(); // UI �ʱ�ȭ
    start_format = menuDraw();
    if (start_format == 1)
    {
        system("cls");
    }
    else if (start_format == 2) {
        //save&load
    }
    else
        exit(1);




    srand(static_cast<unsigned>(time(nullptr)));

    horse player = select_horse();
    // Ʈ���̳� ��ü ����
    training trainer(player);

    Sleep(500);
    system("cls");




    for (int i = 0; i < MAX_MONTH; i++) {
        //���̽� �Լ� ������ ���� Ƽ� ������ 1����(6,5Ƽ��) 2����(4,3Ƽ��) 3���� (2,1Ƽ��)
        if (i != 0 && i % 6 == 0) {
            cout << "\n=== ���̽��� ���۵˴ϴ�! ===\n";

            int tier = 1; // �⺻��
            if (i <= 12)        tier = 6;
            else if (i <= 24)   tier = 5;
            else if (i <= 36)   tier = 4;
            else if (i <= 48)   tier = 3;
            else if (i <= 60)   tier = 2;
            else  tier = 1;

            Race race(player, tier);
            race.start();
        }

        print_stat(i + 1, &player, trainer);
        Sleep(500);
        system("cls");
    }
    //�������̽�
    cout << "\n=== ���� ���̽��� ���۵˴ϴ�! ===\n";
    Race race(player, 1);
    race.start();
    return 0;
}

horse select_horse() {
    int x = 46;

    gotoxy(x, 15);
    cout << "1. ���ָ� ���Ϸ��� ����ī\n";
    gotoxy(x, 17);
    cout << "2. ���ึ ���߳� ž��\n";
    gotoxy(x, 19);
    cout << "3. ���Ը� ������ ĸ\n";
    gotoxy(x, 21);
    cout << "4. ���Ը� ��� ��\n";
    gotoxy(x, 23);
    cout << "���۸��� ���ÿ� (1 ~ 4): ";

    while (true) {
        int n;
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "���ڸ� �Է����ּ���: ";
            continue;
        }
        switch (n) {
        case 1: return horse("���Ϸ��� ����ī", 0, startStat, startStat, startStat, startStat);
        case 2: return horse("���߳� ž��", 1, startStat, startStat, startStat, startStat);
        case 3: return horse("������ ĸ", 2, startStat, startStat, startStat, startStat);
        case 4: return horse("��� ��", 3, startStat, startStat, startStat, startStat);
        default:
            cout << "�߸��� �����Դϴ�. �ٽ� �Է����ּ���: ";
        }
    }
}

void print_stat(int month, horse* player, training& trainer);