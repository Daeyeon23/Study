#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
// 0�� �� ĭ, 1�� ��, 2�� ���̷���
// M���� Ȱ��ȭ�� ���̷����� dfs�� �̿��ؼ� �������� �̱�
// result_time ���� �ʱⰪ �״�θ� ���̷����� �� ������ ���� ���¶� -1 ���
// �� ���� ��쿡�� �׿� �ش��ϴ� result_time�� ���


struct yx {
	int y;
	int x;
};

int ydir[4] = { -1,1,0,0 };//�����¿�
int xdir[4] = { 0,0,-1,1 };

int N, M; // �� ũ��, Ȱ��ȭ�� ���̷��� ��
int MAP[51][51]; 
int visited[51][51]; //�ð���� �迭
int v_cntsize; //���̷��� ���� ������
vector<yx>v_vect; // ���̷��� ��ǥ ���� ����
vector<yx>active_v; //Ȱ��ȭ�� ���̷��� ��ǥ ���� ����
int result_time = 9999; //��
queue<yx>q;

void bfs() {

	//dfs�� ���� M���� ��ǥ���� ���̷��� ��Ʈ���ֱ�
	while (!q.empty()) { 
		yx now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N)continue;

			if (MAP[ny][nx] != 1 && visited[ny][nx] == -1) {
				visited[ny][nx] = visited[now.y][now.x] + 1;
				q.push({ ny,nx });
			}
		}
	}
	int max_time = 0;
	int checked = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j] == 0) {
				if (visited[i][j] == -1) { //��� ��ĭ�� ���̷����� ���������� ���
					checked = 0;
					break;
				}
				else { 
					max_time = max(max_time, visited[i][j]);
				}
			}
		}
	}
	if (checked == 1) { //��� ��ĭ�� ���̷����� ���� ��쿡 ����� ����
		result_time = min(result_time, max_time);
	}

}


void dfs(int cnt, int ja) {

	//M���� Ȱ��ȭ�� ���̷����� �������� �̾��ֱ�
	if (cnt == M) {

		memset(visited, -1, sizeof(visited));

		int active_cnt = active_v.size(); 
		// Ȱ��ȭ�� ���̷����鿡 ���� ��ǥ ���Ϳ� ����ֱ�
		for (int i = 0; i < active_cnt; i++) {
			q.push({ active_v[i].y, active_v[i].x });
			visited[active_v[i].y][active_v[i].x] = 0;
		}
		bfs(); 
		return;
	}

	for (int i = ja; i < v_cntsize; i++) {
		active_v.push_back({ v_vect[i].y ,v_vect[i].x });
		dfs(cnt + 1, i + 1);
		active_v.pop_back();
	}

}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);


	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 2) {
				v_vect.push_back({ i,j });
			}
		}
	}

	v_cntsize = v_vect.size();

	dfs(0, 0);
	
	if (result_time == 9999) {
		cout << -1 << '\n';
	}
	else {
		cout << result_time << '\n';
	}

	return 0;
}