#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include "horse.h"
#include "training.h"
#include "race.h"

const int MAX_MONTH = 36;
const int startStat = 100.0;

using namespace std;

horse select_horse();
void print_basic(int month, horse* player, training& trainer);

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    horse player = select_horse();
    training trainer(player);

    Sleep(500);
    system("cls");

    for (int month = 0; month < MAX_MONTH; month++) {
        cout << "[ " << month + 1 << "������ ���� ��... ]" << endl;

        // 6�������� ���̽�
        if ((month + 1) % 6 == 0) {
            cout << "\n===  ���̽��� ���۵˴ϴ�!  ===\n";
            Race race(player, 1); // tier�� 1�� ����
            race.start();
            Sleep(1000);
            system("cls");
        }

        // �Ʒ� ��ƾ
        print_basic(month + 1, &player, trainer);
        Sleep(1000);
        system("cls");
    }

    cout << "\n[  36���� ���� �Ʒ� �� ���ְ� ����Ǿ����ϴ�! �����ϼ̽��ϴ�  ]\n";
    return 0;
}

horse select_horse() {
    cout << "1. ���ָ� ���Ϸ��� ����ī\n"
        << "2. ���ึ ���߳� ž��\n"
        << "3. ���Ը� ������ ĸ\n"
        << "4. ���Ը� ��� ��\n"
        << "���۸��� ���ÿ� (1 ~ 4): ";

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
            continue;
        }
    }
}

void print_basic(int month, horse* player, training& trainer) {
    cout << "=============================================\n"
        << "Month " << month << " / " << MAX_MONTH << "\n"
        << "=============================================\n\n";

    cout << "�λ�Ȯ�� : " << trainer.injury_percent(*player) << "%\n\n";

    cout << "1) ���ǵ� �Ʒ�\t2) �Ŀ� �Ʒ�\t3) �ټ� �Ʒ�\t4) ������ �Ʒ�\t5) �޽�\n";
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
        case 1: trainer.training_speed(*player);        return;
        case 2: trainer.training_power(*player);        return;
        case 3: trainer.training_perseverance(*player); return;
        case 4: trainer.training_endurance(*player);    return;
        case 5: trainer.rest(*player);                  return;
        default:
            cout << "�߸��� �����Դϴ�. �ٽ� �Է����ּ���: ";
            continue;
        }
    }
}
