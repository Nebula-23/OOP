#include "MonsterWorld.h"
#include <time.h>

int Monster::count = 0;

void main()
{
	srand((unsigned int)time(NULL));
	int w = 50, h = 7;
	MonsterWorld game(w, h);

	game.add(new Monster("����", "��", rand() % w, rand() % h));
	game.add(new Monster("������", "��", rand() % w, rand() % h));
	game.add(new Monster("���״�", "��", rand() % w, rand() % h));
	game.add(new Monster("��Ʈ", "��", rand() % w, rand() % h));
	game.play(500, 10);
	printf("----------���� ����----------\n");
}