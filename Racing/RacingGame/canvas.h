#ifndef CANVAS_H
#define CANVAS_H
#include <iostream>

class Canvas {
private:
    static const int WIDTH = 61; // 마지막에 | 결승선임 (경기장 크기는 60)
    static const int HEIGHT = 7;
    int map[HEIGHT][WIDTH];

public:
    Canvas() {
        for (int y = 0; y < HEIGHT; ++y)
            for (int x = 0; x < WIDTH; ++x){
                map[y][x] = 0;  // 맵을 모두 초기화
            }
        for (int i = 0; i < HEIGHT; ++i) {
            map[i][60] = -1;
        }
    }

    void setTile(int y, int x, int posX) { // y는 말이 달리는 라인, x는 이동할 위치, posX는 현재위치
        map[y][posX] = 0; // 현재위치 0으로 초기화
        map[y][x] = y+1;  // 말이 이동한 위치 설정
    }

    void printMap() {
        for (int h = 0; h < HEIGHT; h++) {
            bool isH = false;
            for (int w = 0; w < WIDTH; w++) {
                if (map[h][w] == -1)std::cout << '|';
                else if (map[h][w] != 0) {
                    std::cout << map[h][w]; isH = true;
                }
<<<<<<< HEAD
                else if (!isH)std::cout << '.';
=======
                else if (!isH)std::cout << 'ㆍ';
>>>>>>> 4bafeb84af563646d56599ba00c2c249b2053710
                else std::cout << ' ';
            }
            std::cout << '\n'; 
        }
    } // 맵 출력 함수
};
#endif //CANVAS_H

// canvas.h 파일에 있는 canvas 클래스에서 현재 위치를 받아오고, 갱신함. 함수는 canvas참조. 필요한데 없으면 추가. 필요없으면 삭제.
// 뭐 추가 삭제 했는지 꼭 각주로 적어주세요! 두팀 같이 작업하는거라 충돌납니다!

// 현재 위치를 계속 저장할 필요가 있을듯? -> 위의 클래스 멤버변수로 선언해야할수도?
//  ㄴ while문 한번 돌때마다 7마리 이동 후 렌더링 할거라서, move 함수를 매번 호출해야하니 멤버변수에 현재위치 추가해야합니다.
//   ㄴ 생각해보니 player팀은 모르겠네요. cpu팀은 추가했어요

// ★주의사항★: 이전위치는 '0' 으로 초기화, 현재위치는 lane 값으로 변경.
// 이동로직: 누적 소수점 + (spd / 1000) × 기본 이동 칸수(2.5~3.5) + statMod[품종][구간] x {(구간 중요 능력치 / 1000) x breedMod[품종][구간]}
