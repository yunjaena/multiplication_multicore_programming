#include<iostream>
#include<omp.h>
#define GAME_MODE 0
#define CALCULATE_MODE 1
#define EXIT 2
#pragma warning(disable:4996)
using namespace std;

int main() {
	int menu;

	while (true) {
		printf("모드를 선택해주세요. 게임 : 0 , 계산기 : 1, 종료 2\n");
		scanf("%d", &menu);
		switch (menu)
		{
		case GAME_MODE:
			break;
		case CALCULATE_MODE:
			break;
		case EXIT:
			printf("프로그램을 종료합니다.");
			return 0;
			break;
		default:
			break;
		}
	}
	return 0;
}