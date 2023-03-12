#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

int N, L, R; //ũ��, ���� ����, ����
int pop[50][50];
int visited[50][50];
int dir[4][2] = { -1,0,1,0,0,-1,0,1 };
int flag;
struct node {
	int y;
	int x;
};

void run(int y, int x) {
	if (visited[y][x] == 1) return;
	queue<node> q; //Ž����
	vector<node> v; //y, x�� ����
	q.push({ y,x });
	v.push_back({ y,x });
	visited[y][x] = 1;
	int sum = pop[y][x];
	int cnt = 1;
	while (!q.empty()) {
		node now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dir[i][0];
			int nx = now.x + dir[i][1];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			if (visited[ny][nx] == 1) continue;
			int diff = abs(pop[now.y][now.x] - pop[ny][nx]);
			if (diff<L || diff>R) continue; //L�� 1�̻��̶� ������ ���վȵ�
			visited[ny][nx] = 1;
			q.push({ ny,nx });
			v.push_back({ ny,nx });
			cnt++;
			sum += pop[ny][nx];
		}
	}
	//�������� �� flag(�Ϸ����) ����, �α��� ��ȭ
	if (cnt != 1) {
		flag++;
		for (int i = 0; i < v.size(); i++) {
			pop[v[i].y][v[i].x] = sum / cnt;
		}
	}
}
void move() {
	//�Ϸ縶�� visited �ʱ�ȭ
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			run(i, j);
		}
	}
}
int main() {
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> pop[i][j];
		}
	}
	int day = 0;
	while (true) {
		flag = 0;
		move();
		if (flag == 0) break;
		day++;
	}
	cout << day;
	return 0;
}