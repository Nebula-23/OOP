#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include "horse.h"
#include "training.h"
#include "race.h"
#include "UI.h"

const int MAX_MONTH = 72;
const int startStat = 100.0;

using namespace std;

horse select_horse();
void print_basic(int month, horse* player, training& trainer);

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    init_console_size();  // �ܼ� ũ�� �ʱ�ȭ

    int menuChoice = menuDraw(); // ���� ȭ�� �޴� ǥ��
    if (menuChoice == 3) {
        cout << "������ �����մϴ�." << endl;
        return 0;
    }

    horse player = select_horse();
    training trainer(player);

    Sleep(500);
    system("cls");
    //6�� ������ ���̽�, ������ CPU���� Ƽ� ���
    for (int month = 0; month < MAX_MONTH; month++) {
        if (month != 0 && month % 6 == 0) {
            cout << "\n=== ���̽��� ���۵˴ϴ�! ===\n";

            int tier = 1; // �⺻��
            if (month <= 12)        tier = 6;
            else if (month <= 24)   tier = 5;
            else if (month <= 36)   tier = 4;
            else if (month <= 48)   tier = 3;
            else if (month <= 60)   tier = 2;
            else  tier = 1;

            Race race(player, tier);
            race.start();
        }

        print_basic(month + 1, &player, trainer);
        Sleep(1000);
        system("cls");
    }

    //�������̽�
    cout << "\n=== ���� ���̽��� ���۵˴ϴ�! ===\n";
    Race race(player, 1);
    race.start();

    //���� ����
    cout << "\n[ ������ ����Ǿ����ϴ� ]\n";
    return 0;
}
 //������
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

//���� ���� UI
void print_basic(int month, horse* player, training& trainer) {
    //���� , D-Day, ��ǰ�� ǥ�� �Լ�
    int display_year = (month % 24 == 0 && month != 0) ? month / 24 : month / 24 + 1;
    
    int d_day = (month % 6 == 0) ? 0 : 6 - (month % 6);
    
    string breed_str;
    switch (player->get_breed()) {
    case 0: breed_str = "���ָ�"; break;
    case 1: breed_str = "���ึ"; break;
    case 2: breed_str = "���Ը�"; break;
    case 3: breed_str = "���Ը�"; break;
    default: breed_str = "�� �� ����"; break;
    }

    

    cout << "[ " << display_year << "���� ]" << endl;
    cout << "===============================================\n"
        << player->get_name() << " | " << breed_str << " | " << month << " turn |" << " ���̽� D-" << d_day << "\n"
        << "===============================================\n";
    cout << "���ǵ�: " << player->get_spd() << "  �Ŀ�: " << player->get_pow()<<"\n";
    cout << "�ټ�: " << player->get_guts() << " ������: " << player->get_sta() << "\n";
   

    cout <<"ä��: "<< trainer.get_hp() << "  �λ�Ȯ�� : " << trainer.injury_percent(*player) << "%\n\n";

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
