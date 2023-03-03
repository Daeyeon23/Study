#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <cstdio>
using namespace std;
int Cnt = 1;//�����ִ� ��ġ��
struct Node {
	int y, x;
};
vector<int>v[8];
int flag;
int ydir[] = { -1,1,0,0 };
int xdir[] = { 0,0,-1,1 };
int visited[55][55];
int N, M, sy, sx, L;
int MAP[55][55];
void reset() {
	Cnt = 1;
	for (int y = 0; y < 55; y++) {
		for (int x = 0; x < 55; x++) {
			visited[y][x] = 0;
			MAP[y][x] = 0;
		}
	}
}

void input() {
	cin >> N >> M >> sy >> sx >> L;
	//0���� �ѷ��α�
	sy++;
	sx++;
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= M; x++) {
			cin >> MAP[y][x];
		}
	}
}

void vecSet() {
	flag = 1;//�ѹ��� ����
	v[1] = { 0,1,2,3 };
	v[2] = { 0,1 };//����
	v[3] = { 2,3 };//�¿�
	v[4] = { 0,3 };//���
	v[5] = { 1,3 };//�Ͽ�
	v[6] = { 1,2 };//����
	v[7] = { 0,2 };//����
}

bool check(int dir, int num) {
	//���� �ٲٱ�
	int tmp = dir;
	if (tmp % 2 == 0) tmp++;
	else tmp--;

	int sizeV = v[num].size();
	for (int y = 0; y < sizeV; y++) {
		if (v[num][y] == tmp) {
			return true;
		}
	}
	return false;

}

void Flood() {
	//queue
	queue<Node>q;
	q.push({ sy,sx });
	//visited
	visited[sy][sx] = 1;
	//variables
	
	int Time = 0;//�ܰ躰 flood
	while (!q.empty()) {
		Time++;
		if (Time == L)
			return;

		int cursize = q.size();

		for (int x = 0; x < cursize; x++) {
			Node now = q.front();
			q.pop();

			int nowT = MAP[now.y][now.x];
			int size = v[nowT].size();
			if (size == 0) continue;
			for (int i = 0; i < size; i++) {
				int ny = now.y + ydir[v[nowT][i]];
				int nx = now.x + xdir[v[nowT][i]];
				if (MAP[ny][nx] == 0) continue;
				if (visited[ny][nx] != 0) continue;
				//���� ������ ���� �����ִ���Ȯ��
				if (check(v[nowT][i], MAP[ny][nx])==false) continue;

				visited[ny][nx] = 1;
				Cnt++;
				q.push({ ny,nx });
			}
		}

	}


}

int main() {
	
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		reset();
		input();
		if (flag == 0) {
			vecSet();
		}
		Flood();
		cout << "#" << tc << " " << Cnt<< endl;
	}
	return 0;
}