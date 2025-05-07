#pragma once
#include <iostream>
#include <windows.h>

#include "conio.h"
#include "training.h"
#define UP 72 // ��
#define DOWN 80 // �Ʒ�
const int MAX_MONTH = 72;

//#define LEFT 2 
//#define RIGHT 3
using namespace std;

void init_console_size() {
    system("mode con:cols=124 lines=35");
}

void init_game_ui() { // ���Ӹ�ó�� ų�� TItle ����� ��� ����

    cout << " ���޸��� ���� " << endl;

}

void gotoxy(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� Ŀ�� �ڵ鰡������
    COORD pos;
    pos.X = x; // x��ǥ
    pos.Y = y; // y��ǥ	
    SetConsoleCursorPosition(consoleHandle, pos); // Ŀ�� ��ġ ����
}



int keyControl() {
    char temp = _getch();

    if (temp == 72) // ��
        return UP;
    else if (temp == 80) // �Ʒ�
        return DOWN;
    else if (temp == 27) // ESC
        return 27;
    else if (temp == 13) // Enter
        return 13;
    else
        return -1; // �߸��� �Է�
}

void drawArrow(int x, int y) {
    gotoxy(x, y);
    printf(">");
}

void clearArrow(int x, int y) {
    gotoxy(x, y);
    printf(" "); // ���� ��ġ�� '>'�� ����
}

int menuDraw() {
    int x = 50;
    int y = 15;
    int arrowX = x + 4; // '>' ��ȣ ��ġ
    int currentY = y + 10; // ���� ���õ� �׸��� y��ǥ

    cout << "===========================================================================================================================\n" << endl;
    gotoxy(x, y);
    printf("�ƹ�ư ���޸��� ������\n");

    gotoxy(x - 4, y + 2);
    cout << "����Ϸ��� �ƹ� Ű�� ��������...";

    gotoxy(x + 4, y + 10);
    printf("  ���ӽ��� ");

    gotoxy(x + 6, y + 12);
    printf("�̾��ϱ� ");

    gotoxy(x + 6, y + 14);
    printf("  ����	\n\n");
    cout << "==========================================================================================================================\n" << endl;

    // ó���� '>' ǥ�ø� �ٷ� �׸���
    drawArrow(arrowX, currentY);

    while (1) {
        int n = keyControl();
        switch (n) {
        case UP:
            if (currentY > y + 10) { // �ּ� ��ġ ����
                clearArrow(arrowX, currentY);
                currentY -= 2; // �� �� ���� �̵�
                drawArrow(arrowX, currentY);
            }
            break;
        case DOWN:
            if (currentY < y + 14) { // �ִ� ��ġ ����
                clearArrow(arrowX, currentY);
                currentY += 2; // �� �� �Ʒ��� �̵�
                drawArrow(arrowX, currentY);
            }
            break;
        case 13: // Enter
            system("cls");
            if (currentY == y + 10) return 1; // ���ӽ���
            else if (currentY == y + 12) return 2; // �̾��ϱ�
            else if (currentY == y + 14) return 3; // ����
            break;
        }
    }
}

void print_stat(int month, horse* player, training& trainer) {
    int display_year = (month % 24 == 0 && month != 0) ? month / 24 : month / 24 + 1;
    int d_day = (month % 6 == 0) ? 0 : 6 - (month % 6);

    string brred_str;
    switch (player->get_breed()) {
    case 0: brred_str = "���ָ�"; break;
    case 1: brred_str = "���ึ"; break;
    case 2: brred_str = "���Ը�"; break;
    case 3: brred_str = "���Ը�"; break;
    default: brred_str = "�� �� ����"; break;
    }

    cout << "===========================================================================================================================\n"
        << "\t\t\t\t\t\t\t" << display_year << "(����)\n\n" //<< month << " / " << MAX_MONTH << "\n\n"
        << "\t\t\t\t\t" << player->get_name() << " | " << brred_str << " | " << month << "turn |" << "���̽� D-" << d_day << "\n";
    cout << "===========================================================================================================================\n\n";
    cout << "\n";//���� �̷��� ����� ���������� ���߿� �� �׸��� ���ؼ� ����� �����̴ϴ�.
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\t\t\t\t �׸��� �� ���� ( �� �ٱ״� �ٱ״� �ƽ�Ű�ڵ�)\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "===========================================================================================================================\n";
    cout << "���ɷ�ġ\n";
    cout << "���ǵ� : " << player->get_spd() << "\t�Ŀ� : " << player->get_pow() << "\t�ټ� : " << player->get_guts() << "\t������ : " << player->get_sta() << "\n";
    cout << "�λ�Ȯ�� : " << trainer.injury_percent(*player) << "%\t" << "ü��: " << trainer.get_hp() << "\n";
    cout << "===========================================================================================================================\n";
    cout << "1) ���ǵ� �Ʒ�\t2) �Ŀ� �Ʒ�\t3) �ټ� �Ʒ�\t4) ������ �Ʒ�\t5) �޽�\n";
    while (true) {
        int n;
        cin >> n;
        switch (n) {
        case 1: trainer.training_speed(*player);      return;
        case 2: trainer.training_power(*player);      return;
        case 3: trainer.training_perseverance(*player); return;
        case 4: trainer.training_endurance(*player);  return;
        case 5: trainer.rest(*player);                return;
        default:
            cout << "�߸��� �����Դϴ�. �ٽ� �Է����ּ���: ";
        }
    }
}

/*
�������Ʈ
https://geundung.dev/14?category=699626 => ȭ�� �޴��� ����
https://geundung.dev/15?category=699626 =>Ű���� �̺�Ʈ ó��
*/