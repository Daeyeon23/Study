#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
using namespace std;

// no_virus : ��ĭ�� ����, result : ������ ���̽��� ���� ��
//ans: ���� ��, Size: virus�� ���� 
int n, m, no_virus, result, ans, Size;

int lab[51][51];
int visited[51][51];

int ydir[4] = { -1,0,1,0 };
int xdir[4] = { 0,-1,0,1 };

struct node {
	int y;
	int x;
};

struct info {
	int y;
	int x;
	int time;
};

vector<node>virus;
vector<node>target_virus;
queue<info>q;

void infection()
{
	//cnt�� �� ����
	int cnt = no_virus;

	//queue �ʱ�ȭ
	while (!q.empty())
		q.pop();


	//target_virus���� ��� ���̷����� queue�� �߰�
	for (int i = 0; i < m; ++i)
	{
		int y = target_virus[i].y; int x = target_virus[i].x;
		q.push({ y,x,0 });
		visited[y][x] = 1;
	}

	result = 0;



	while (!q.empty())
	{
		info now = q.front(); q.pop();

		//����ġ��
		if (result >= ans) return;

		for (int i = 0; i < 4; ++i)
		{
			//��ĭ�� ���� ��� ans �� ���� �� return
			if (cnt == 0)
			{
				ans = min(ans, result);
				return;
			}

			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			int ntime = now.time + 1;
			result = ntime;

			if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
			if (visited[ny][nx]) continue;
			if (lab[ny][nx] == 1) continue; // ���� ���� ��

			if (lab[ny][nx] == 0) cnt--; //��ĭ�� ������ �� cnt ����
			visited[ny][nx] = ntime;
			q.push({ ny,nx,ntime });
		}


	}
	return;
}

//�������� ���̷��� ����
void choose_virus(int level, int now)
{
	if (level == m)
	{
		memset(visited, 0, sizeof(visited));
		infection();
		return;
	}

	for (int i = now; i < Size; ++i)
	{
		target_virus.push_back({ virus[i].y, virus[i].x });
		choose_virus(level + 1, i + 1);
		target_virus.pop_back();
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;

	virus.reserve(11);
	target_virus.reserve(11);

	no_virus = 0;
	ans = 21e8;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> lab[i][j];
			if (lab[i][j] == 0)
				no_virus++;
			if (lab[i][j] == 2)
				virus.push_back({ i,j });
		}
	}

	Size = virus.size();
	choose_virus(0, 0);

	if (ans == 21e8)
		cout << "-1";
	else
		cout << ans;
}