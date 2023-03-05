#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
int MAP[20][20];
int Copy[20][20];
int D, W, K;
int minCnt;

void reset() {
	minCnt = 21e8;
	
}
void input() {
	cin >> D >> W >> K;
	for (int y = 0; y < D; y++) {
		for (int x = 0; x < W; x++) {
			cin >> MAP[y][x];
		}
	}
	memcpy(Copy, MAP, sizeof(MAP));
}

bool check() {
	int DAT[20] = { 0, };//���ӵ� ���� ����

	for (int x = 0; x < W; x++) {
		int tmp = 1;
		DAT[x] = 1;
		for (int y = 0; y < D - 1; y++) {
			if (Copy[y][x] != Copy[y+1][x]) {
				tmp = 1;//�ʱ�ȭ
			}
			else if (Copy[y][x]== Copy[y+1][x]) {
				tmp++;
				DAT[x] = max(DAT[x], tmp);
			}
			
			
		}
		if (DAT[x] < K) return false;//��� �� �˻縦 ���ƴµ� ����� ���Ѱ��
	}
	//��� ���� ����� ���
	return true;
}

void injectDrug(int row, int drug) {
	for (int x = 0; x < W; x++) {
		Copy[row][x] = drug;
	}
}

void DFS(int now, int drugCnt) {
	//base
	if (drugCnt >= minCnt) return;
	if (check()) {//�̹�  ��� ������ ���>> ���غ� �ʿ� ����
		minCnt = min(minCnt, drugCnt);
		return;
	}
	if (now == D) {
		return;
	}
	

	//recursive >> ��ǰó�� �ϰų�(1 0 ) ���ϰų� 2


	DFS(now + 1, drugCnt);
	
	for (int i = 0; i < 2; i++) {
		
		injectDrug(now, i);
		DFS(now + 1, drugCnt + 1);
		memcpy(Copy[now], MAP[now], sizeof(MAP[now]));
	}

}

int main() {
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		reset();
		input();
		DFS(0, 0);
		cout << "#" << tc << " " << minCnt << endl;
	}
	return 0;
}