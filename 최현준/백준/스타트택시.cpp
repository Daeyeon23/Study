/*
�մ��� �¿�� �Լ� driveToCustomer��
�մ��� �¿�� ���������� ���� �Լ� driveToDest �Լ��� �����Ͽ�
�� �Լ��� �����ư��鼭 ����Ͽ� ������� �̾ҽ��ϴ�.
*/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
using namespace std;

// �Լ� ����
void driveToCustomer(int y, int x, int nfuel, int cnt);
void driveToDest(int y, int x, int dest, int nfuel, int cnt);

int n, m, fuel;

int road[22][22];
int visited[22][22] = { 0, };

struct node {
	int y;
	int x;
	int time;
	bool operator<(node next) const {
		if (time > next.time) return true;
		if (time < next.time) return false;
		if (y > next.y) return true;
		if (y < next.y) return false;
		if (x > next.x)return true;
		if (x < next.x)return false;
		return false;
	}
};

struct pos {
	int y;
	int x;
};

//Dest : �� �ο��� ������ ��ǥ�� �����ϴ� ����
vector<pos> Dest;
priority_queue<node>pq;

int ydir[4] = { -1,0,1,0 };
int xdir[4] = { 0,-1,0,1 };

// �����ǥ, ���ᷮ, ���� �մԼ��� ������ ����.
void driveToCustomer(int y, int x, int nfuel, int cnt)
{
	//���� �մԼ��� 0�� ���� ���ᷮ�� ���
	if (cnt == 0)
	{
		cout << nfuel;
		return;
	}

	//pq �ʱ�ȭ �� �ʱ� ����
	while (!pq.empty())
		pq.pop();
	pq.push({ y,x,0 });
	memset(visited, 0, sizeof(visited));
	visited[y][x] = 1;

	//bfs ����
	while (!pq.empty())
	{
		node now = pq.top(); pq.pop();

		int y = now.y;
		int x = now.x;
		int time = now.time;

		// time(������ �Ÿ�)�� ���ᷮ ���� Ŭ �� �Ұ����� ����̱� ������ -1 ���
		if (time > nfuel)
		{
			cout << "-1";
			return;
		}

		//������ road[y][x] >0 �� ���� : 4���� Ž���ϸ� pq�� �߰��ϴ� �������� road ���� 1(��)�� ���� �־����� �ʱ� ������
		if (road[y][x] > 0)
		{
			//main����  road�� 2���� ���� �־���� ������ vector Dest�� index�� ǥ���� ���� 2�� ����
			int dest = road[y][x] - 2;
			road[y][x] = 0;
			driveToDest(y, x, dest, nfuel-time, cnt);
			return;
		}

		for (int i = 0; i < 4; ++i)
		{
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			int ntime = now.time + 1;

			if (visited[ny][nx]) continue;
			if (ny <= 0 || nx <= 0 || ny > n || nx > n) continue;
			if (road[ny][nx] == 1) continue;

			visited[ny][nx] = 1;
			pq.push({ ny,nx,ntime });
		}
	}

	cout << "-1";

}

void driveToDest(int y, int x, int dest, int nfuel, int cnt)
{
	while (!pq.empty())
		pq.pop();
	pq.push({ y,x,0 });
	memset(visited, 0, sizeof(visited));
	visited[y][x] = 1;

	//dest(index)���� �޾� Dest���� �¿� �ο��� ������ ��ǥ ���� �ҷ��´�.
	int dest_y = Dest[dest].y;
	int dest_x = Dest[dest].x;

	while (!pq.empty())
	{
		node now = pq.top(); pq.pop();

		int y = now.y;
		int x = now.x;
		int time = now.time;


		// time(������ �Ÿ�)�� ���ᷮ ���� Ŭ �� �Ұ����� ����̱� ������ -1 ���
		if (time > nfuel)
		{
			cout << "-1";
			return;
		}

		// �������� �������� �� �մ� ���� ���ְ� driveToCustomer �Լ� ȣ��
		if (y == dest_y && x == dest_x)
		{
			driveToCustomer(y, x, nfuel+time, cnt - 1);
			return;
		}

		for (int i = 0; i < 4; ++i)
		{
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];
			int ntime = now.time + 1;

			if (visited[ny][nx]) continue;
			if (ny <= 0 || nx <= 0 || ny > n || nx > n) continue;
			if (road[ny][nx] == 1) continue;

			visited[ny][nx] = 1;
			pq.push({ ny,nx,ntime });
		}
	}

	cout << "-1";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m >> fuel;

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			cin >> road[i][j];
		}
	}

	int driver_y, driver_x;
	cin >> driver_y >> driver_x;

	// ��������� ��ġ�� �ʱ� ������ ���� ������ ����ִ� road �迭�� ���� �������� ��. (1�� ���̱� ������ 2���� m+1���� ���� �־���)
	// ���������� Dest ���Ϳ� �־�����.
	for (int i = 2; i <= m+1; ++i)
	{
		int y, x;
		cin >> y >> x;
		road[y][x] = i;
		cin >> y >> x;
		Dest.push_back({ y,x });
	}

	driveToCustomer(driver_y, driver_x, fuel, m);
	return 0;
}