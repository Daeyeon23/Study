#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
struct Node {
	int x, y,Bomb;
};

int MAP[15][15];
int Copy[15][15];
int N, W, H;
int blockCnt;
int removeCnt;//�ִ� ����
int path[5];
int flag;

void reset() {
	blockCnt = 0;
	removeCnt = 0;
	flag = 0;
}


void input() {
	cin >> N >> W >> H;
	for (int y = H-1; y >= 0; y--) {
		for (int x = 0; x < W; x++) {
			cin >> MAP[x][y];
			if (MAP[x][y] != 0) blockCnt++;//ó�� ��� �� ����
		}
	}
}

int findBead(int COPY[15]) {
	for (int y = H - 1; y >= 0; y--) {
		if (COPY[y] != 0) return y;
	}
	return -1;
}

void pullBlock() {
	for (int x = 0; x < W; x++) {
		int height = 0;//0���� ���ʴ�� �׾� �ø���
		for (int y = 0; y < H; y++) {
			if (Copy[x][y] != 0) {
				int tmp = Copy[x][y];
				Copy[x][y] = 0;
				Copy[x][height] = tmp;
				height++;//������ ���� ��ġ�� �̵�
			}
		}
	}
}

void check(int arr[5]) {
	int Cnt = 0;

	memcpy(Copy, MAP, sizeof(MAP));

	//��� ��� ���ֱ�
	for (int  k= 0; k < N; k++) {
		if (Cnt == blockCnt) {
			flag = 1;//�� ���ŵ� ���, �� �غ��ʿ� ����
			break;
		}
		int stX = path[k];

		int stY = findBead(Copy[stX]);//���� ���� ã�Ƽ� queue�� �־��ֱ�
		if (stY == -1) break;//������ġ�� ������ ���°�� >> �Ұ�!

		queue<Node>q;
		q.push({ stX, stY, Copy[stX][stY] });

		Copy[stX][stY] = 0;
		Cnt++;

		int ydir[] = { 1,-1,0,0 };
		int xdir[] = { 0,0,-1,1 };
		

		while (!q.empty()) {
			Node now = q.front();
			q.pop();
			
			int Bomb = now.Bomb;
			if (Bomb == 1) {
				continue;
			}

			for (int j = 1; j <= Bomb - 1; j++) {
				for (int i = 0; i < 4; i++) {
					int nx = now.x + xdir[i] * j;
					int ny = now.y + ydir[i] * j;
					if (nx >= W || nx < 0 || ny >= H || ny < 0) continue;
					if (Copy[nx][ny] == 0) continue;


					//2�̻��� ��� , �� �غ���
					if (Copy[nx][ny] >= 2) {
						q.push({ nx, ny, Copy[nx][ny] });
					}
					


					Copy[nx][ny] = 0;
					Cnt++;

				}
			}
			
		}

		//��ó�� >> ��� ��ƴ���
		pullBlock();

	}


	removeCnt = max(removeCnt, Cnt);
	
}

void DFS(int now) {
	if (flag == 1) return;
	if (now == N) {
		check(path);
		return;
	}

	for (int i = 0; i < W; i++) {
		path[now] = i;
		DFS(now+1);
	}

}


int main() {
	//freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		reset();
		input();
		DFS(0);

		cout <<"#"<<tc<<" "<<blockCnt - removeCnt << endl;
	}

	
	return 0;
}