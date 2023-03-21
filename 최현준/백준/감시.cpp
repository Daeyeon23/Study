/*
�迭�� �����Ͽ� �繫���� ������ �ް�
dfs�� �̿��Ͽ� �ذ��Ѵ�
������ cctv�� ���� ���� while���� ���� ������ �� �ִ� ĭ�� ���� -1�� �����ϰ�
dfs return�� �� 0(�簢����)�� ������ ���� ans���� �����Ѵ�.
*/


#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int n, m ,Size, ans;

int office[9][9];

int ydir[4] = { -1,0,1,0 };
int xdir[4] = { 0,1,0,-1 };

struct node {
	int y;
	int x;
	int value;
};

vector<node>cctv;


//level:cctv index, new_office:�繫�� ����
void dfs(int level, int new_office [][9])
{
	if (level == Size)
	{
		int cnt = 0;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				if (new_office[i][j] == 0)
					cnt++;
			}
		}
		ans = min(ans, cnt);
		return;
	}
	
	//temp��� �ӽù迭�� �����Ͽ� office�� ���� �����Ͽ� �ް�
	//���� dfs�� �����Ѵ�.
	int temp[9][9];
	copy(&new_office[0][0], &new_office[0][0] + 9 * 9, &temp[0][0]);
	//memcpy(temp, new_office, sizeof(new_office));

	int num = cctv[level].value;


	//1�� cctv
	if (num == 1)
	{
		for (int i = 0; i < 4; ++i)
		{
			int y = cctv[level].y;
			int x = cctv[level].x;
			while (1)
			{
				int ny = y + ydir[i];
				int nx = x + xdir[i];
				if (ny < 0 || nx < 0 || ny >= n || nx >= m) break;
				if (temp[ny][nx] == 6) break;
				if (temp[ny][nx] == 0) temp[ny][nx] = -1;
				y = ny; x = nx;
			}
			//������ ���⿡ ���� dfs�� �ϰ� copy������ �����迭�� ��������.
			dfs(level + 1, temp);
			copy(&new_office[0][0], &new_office[0][0] + 9 * 9, &temp[0][0]);
		}
	}
	
	//2�� cctv
	else if (num == 2)
	{
		//��,�Ʒ� �����ϴ� ���
		for (int i = 0; i < 4; i += 2)
		{
			int y = cctv[level].y;
			int x = cctv[level].x;
			while (1)
			{
				int ny = y + ydir[i];
				int nx = x + xdir[i];
				if (ny < 0 || nx < 0 || ny >= n || nx >= m) break;
				if (temp[ny][nx] == 6) break;
				if (temp[ny][nx] == 0) temp[ny][nx] = -1;
				y = ny; x = nx;
			}
		}
		dfs(level + 1, temp);
		copy(&new_office[0][0], &new_office[0][0] + 9 * 9, &temp[0][0]);


		//����, ������ �����ϴ� ���
		for (int i = 1; i < 4; i += 2)
		{
			int y = cctv[level].y;
			int x = cctv[level].x;
			while (1)
			{
				int ny = y + ydir[i];
				int nx = x + xdir[i];
				if (ny < 0 || nx < 0 || ny >= n || nx >= m) break;
				if (temp[ny][nx] == 6) break;
				if (temp[ny][nx] == 0) temp[ny][nx] = -1;
				y = ny; x = nx;
			}
		}
		dfs(level + 1, temp);
		copy(&new_office[0][0], &new_office[0][0] + 9 * 9, &temp[0][0]);
	}
	
	//3�� cctv
	else if (num == 3)
	{
		for (int i = 0; i < 4; ++i)
		{
			//2���� ���ø� ���� for��
			for (int j = 0; j < 2; ++j) 
			{
				int y = cctv[level].y;
				int x = cctv[level].x;
				while (1)
				{
					int ny = y + ydir[(i+j)%4];
					int nx = x + xdir[(i+j)%4];
					if (ny < 0 || nx < 0 || ny >= n || nx >= m) break;
					if (temp[ny][nx] == 6) break;
					if (temp[ny][nx] == 0) temp[ny][nx] = -1;
					y = ny; x = nx;
				}
			}
			dfs(level + 1, temp);
			copy(&new_office[0][0], &new_office[0][0] + 9 * 9, &temp[0][0]);
		}
	}

	//4�� cctv
	else if (num == 4)
	{
		for (int i = 0; i < 4; ++i)
		{
			//3���� ���ø� ���� for��
			for (int j = 0; j < 3; ++j)
			{
				int y = cctv[level].y;
				int x = cctv[level].x;
				while (1)
				{
					int ny = y + ydir[(i + j) % 4];
					int nx = x + xdir[(i + j) % 4];
					if (ny < 0 || nx < 0 || ny >= n || nx >= m) break;
					if (temp[ny][nx] == 6) break;
					if (temp[ny][nx] == 0) temp[ny][nx] = -1;
					y = ny; x = nx;
				}
			}
			dfs(level + 1, temp);
			copy(&new_office[0][0], &new_office[0][0] + 9 * 9, &temp[0][0]);
		}
	}

	//5�� cctv
	else if (num == 5)
	{
		for (int i = 0; i < 4; ++i)
		{
			int y = cctv[level].y;
			int x = cctv[level].x;
			while (1)
			{
				int ny = y + ydir[i];
				int nx = x + xdir[i];
				if (ny < 0 || nx < 0 || ny >= n || nx >= m) break;
				if (temp[ny][nx] == 6) break;
				if (temp[ny][nx] == 0) temp[ny][nx] = -1;
				y = ny; x = nx;
			}
		}
		dfs(level + 1, temp);
		copy(&new_office[0][0], &new_office[0][0] + 9 * 9, &temp[0][0]);
	}
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//vector capacity ����
	cctv.reserve(81);

	cin >> n >> m;

	ans = 21e8;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cin >> office[i][j];
			if (office[i][j] >= 1 && office[i][j] <= 5)
				cctv.push_back({ i,j,office[i][j] });
		}
	}

	//cctv ����
	Size = cctv.size();

	dfs(0, office);

	if (ans == 21e8)
		cout << "0";
	else
		cout << ans;
}