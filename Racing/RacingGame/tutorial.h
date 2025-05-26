#pragma once
#include <iostream>
#include <windows.h>
using namespace std;

// 튜토리얼 함수

/*
🎯 게임 목표
🗂️ 레이스 구조 한눈에 보기
📊 레이스 구간별 중요 능력치
🐎 말의 유형(주행 스타일)
💪 훈련 시스템
🏁 레이스 진행 방법
🏆 성장과 보상
💡 요약 TIP
*/

void goals();			// 게임 목표
void race_structure();	// 레이스 구조 한눈에 보기
void important_stat();	// 레이스 구간별 중요 능력치
void horse_breed();		// 말의 유형(주행 스타일)
void training_info();	// 훈련 시스템
void race_info();		// 레이스 진행 방법
void grow_and_reward();	// 성장과 보상
void tip();				// 요약 TIP

void tutorial() {
	int n = 0;
	bool is_game_over = false;

	while (!is_game_over)
	{
		system("cls");
		cout << "\t튜토리얼 목록\n"
			<< "\t\t0. 튜토리얼 종료\n"
			<< "\t\t1. 🎯 게임 목표\n"
			<< "\t\t2. 📋 레이스 구조 한눈에 보기\n"
			<< "\t\t3. 📊 레이스 구간별 중요 능력치\n"
			<< "\t\t4. 🐎 말의 유형(주행 스타일)\n"
			<< "\t\t5. 💪 훈련 시스템\n"
			<< "\t\t6. 🏁 레이스 진행 방법\n"
			<< "\t\t7. 🏆 성장과 보상\n"
			<< "\t\t8. 💡 요약 TIP\n"
			<< "\t\t\t튜토리얼 번호를 입력하세요(0: 종료) : ";

		cin >> n;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "숫자만 입력해 주세요.";
			Sleep(500);
			continue;
		}

		std::cin.ignore(); // 버퍼 비우기

		system("cls");
		switch (n)
		{
		case 1:
			goals();
			getchar();
			break;
		case 2:
			race_structure();
			getchar();
			break;
		case 3:
			important_stat();
			getchar();
			break;
		case 4:
			horse_breed();
			getchar();
			break;
		case 5:
			training_info();
			getchar();
			break;
		case 6:
			race_info();
			getchar();
			break;
		case 7:
			grow_and_reward();
			getchar();
			break;
		case 8:
			tip();
			getchar();
			break;
		case 0:
			is_game_over = true;
			break;
		default:
			cout << "잘못된 번호입니다. 다시 입력해주세요.\n";
			Sleep(500);
			break;
		}
	}
}

void goals() { // 게임 목표
	cout << "🎯 게임 목표" << endl;
	cout << "목표: 자신만의 말을 훈련시켜 성장시키고, 각 레이스에서 3위 안에 들어 최종 결승까지 진출하세요!" << endl;
	cout << "진행: 3년 동안 총 9번의 레이스를 치릅니다." << endl;
	cout << "(각 년도마다 3번의 레이스)" << endl;
	cout << endl;
}	

void race_structure() { // 레이스 구조 한눈에 보기
	cout << "📋 레이스 구조 한눈에 보기" << endl;
	cout << "총 3년차까지 진행되며, 각 년도마다 3번의 레이스가 있습니다." << endl;
	cout << "1년차: 아카데미 지역리그 - 아카데미 플레이오프 - 아카데미 파이널" << endl;
	cout << "2년차: 컨퍼런스 그룹 스테이지 - 컨퍼런스 녹아웃 스테이지 - 컨퍼런스 챔피언십" << endl;
	cout << "3년차: 챔피언스 디비전 - 챔피언스 세미파이널 - 챔피언스 결승" << endl;
	cout << "각 레이스에서 3위 안에 들어야 다음 단계로 진출합니다." << endl;
	cout << endl;

}	

void important_stat() { // 레이스 구간별 중요 능력치
	cout << "📊 레이스 구간별 중요 능력치" << endl;
	cout << "초반: 스피드, 힘" << endl;
	cout << "중반: 스피드, 지구력" << endl;
	cout << "후반: 스피드, 근성" << endl;
	cout << "TIP" << endl;
	cout << "말의 유형(주행 스타일)에 따라 구간별 능력치 보정이 다르니," << endl;
	cout << "말 설명을 꼭 확인하고 알맞게 육성하세요!" << endl;
	cout << endl;
}	

void horse_breed() { // 말의 유형(주행 스타일)
	cout << "🐎 말의 유형(주행 스타일)" << endl;
	cout << "도주마" << endl;
	cout << "\"출발 신호와 동시에 누구보다 빠르게 앞으로 치고 나가, 레이스 내내 선두를 지키려는 말." << endl;
	cout << "강한 추진력과 초반의 폭발적인 힘이 승부의 열쇠가 된다." << endl;
	cout << "하지만 뒤쫓는 말들의 압박을 끝까지 버텨야 한다.\"" << endl;
	cout << endl;

	cout << "선행마" << endl;
	cout << "\"도주마의 그림자를 바짝 쫓으며, 선두권에서 기회를 엿보는 말." << endl;
	cout << "레이스 초반부터 중반까지 안정적으로 앞자리를 지키며," << endl;
	cout << "마지막 순간에 선두를 노린다." << endl;
	cout << "오랜 시간 페이스를 유지하는 능력이 필요하다.\"" << endl;
	cout << endl;

	cout << "선입마" << endl;
	cout << "\"중간 그룹에서 조용히 기회를 노리다가," << endl;
	cout << "레이스가 무르익을 때쯤 서서히 속도를 올리는 말." << endl;
	cout << "후반에 강한 뒷심을 발휘해 선두권에 도전한다." << endl;
	cout << "꾸준한 페이스와 마지막 스퍼트가 중요하다.\"" << endl;
	cout << endl;

	cout << "추입마" << endl;
	cout << "\"출발은 느리지만, 레이스가 끝나갈 무렵" << endl;
	cout << "누구보다 빠르게 속도를 끌어올려" << endl;
	cout << "앞서 달리던 말들을 한 번에 추월하는 말." << endl;
	cout << "마지막 순간의 폭발력과 포기하지 않는 근성이 승부를 가른다.\"" << endl;
	cout << endl;

	cout << "말마다 레이스에서 빛나는 순간이 다릅니다." << endl;
	cout << "각 말의 설명을 꼼꼼히 읽고, 말에게 필요한 능력치를 찾아 육성해보세요!" << endl;
	cout << endl;

}		

void training_info() { // 훈련 시스템
	cout << "💪 훈련 시스템" << endl;
	cout << "훈련 효과:" << endl;
	cout << "선택한 능력치와 부가 능력치가 증가" << endl;
	cout << "매 훈련 시 체력 -10" << endl;
	cout << "피로 누적 시 부상 위험! (부상 시 전체 능력치 10% 감소, 체력 100으로 회복)" << endl << endl;
	cout << "훈련 종류:" << endl;
	cout << "스피드 훈련: 스피드 +30 ~ +60" << endl;
	cout << "힘 훈련: 힘 +30 ~ +50, 지구력 +5 ~ +15" << endl;
	cout << "지구력 훈련: 지구력 +30 ~ +50, 근성 +5 ~ +15" << endl;
	cout << "근성 훈련: 근성 +30 ~ +50, 힘 +5 ~ +15" << endl;
	cout << "휴식: 체력 50 ~ 80% 회복" << endl << endl;
	cout << "TIP" << endl;
	cout << "말의 스타일과 목표 레이스에 맞는 능력치를 집중적으로 키우세요." << endl;
	cout << "체력이 낮으면 부상확률이 높아집니다!" << endl;
	cout << endl;

}	

void race_info() { // 레이스 진행 방법
	cout << "🏁 레이스 진행 방법" << endl;
	cout << "훈련 6회 → 레이스 참가" << endl;
	cout << "레이스 전, 다른 말들의 정보를 확인해 전략을 세우세요." << endl;
	cout << "Enter를 눌러 경기를 수동으로 진행합니다." << endl;
	cout << "결승선 동시 도착 시, 더 멀리 이동한 말이 더 높은 순위!" << endl;
	cout << "동석차 판단 예시" << endl;
	cout << "A: 61.33m, B: 65.92m, C: 63.24m → 1등: B, 2등: C, 3등: A" << endl;
	cout << endl;
}		

void grow_and_reward() { // 성장과 보상
	cout << "🏆 성장과 보상" << endl;
	cout << "훈련/레이스 등수에 따라 능력치와 보상 획득" << endl;
	cout << "효율적인 훈련이 성장의 핵심!" << endl;
	cout << "특정 이스터에그로 감소된 능력치 복구 가능" << endl;
	cout << endl;
}	

void tip() { // 요약 TIP
	cout << "💡 요약 TIP" << endl;
	cout << "말의 스타일에 맞는 훈련을 선택하세요." << endl;
	cout << "체력 관리와 휴식도 중요합니다." << endl;
	cout << "각 레이스의 구간별 중요 능력치를 기억하세요." << endl;
	cout << "3위 안에 들어야 다음 단계로 진출할 수 있습니다!" << endl;
	cout << "당신의 선택이 승부를 바꿉니다" << endl;
}				