#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int N; // �� ũ��
int people; //��� �ο� ��
int ans; //��
int maxnum;
int MAP[11][11];

struct yx
{
	int y, x;
};

vector<yx> stairs; //��� ��ǥ
vector<int> stai; //��� 2���� ���� ����� ��
vector<yx> peo; //��� ��ǥ

int simulation(int s)
{
	vector<int> vect; //������� ��ܱ����� �Ÿ� ���

	for (int i = 0; i < people; i++) //����ؼ� ���Ϳ� �ֱ�
	{
		if (stai[i] == s)
		{
			vect.push_back(abs(peo[i].x - stairs[s].x) + abs(peo[i].y - stairs[s].y));
		}
	}

	if (vect.size() == 0) //���� s��° ��ܿ� �� ����� ������ ����
		return 0;

	int time = 0; //�ð����
	int stairpeo = 0;	//��ܿ� �ö��ִ� ����� ��
	int st[3] = { 0 }; //3�� ����
	int leng = MAP[stairs[s].y][stairs[s].x]; //����� ����

	while (1)
	{
		time++;

		for (int i = 0; i < vect.size(); i++) //�ð��� ������� ��� �Ÿ� �ٿ��ֱ�
		{
			vect[i]--;
			if (vect[i] == 0) //���� ��ܿ� �����ߴٸ� ��ܿ� �ö��ִ� ��� ����
				stairpeo++;
		}

		if (stairpeo != 0) //��ܿ� ������ ����� ������
		{
			for (int i = 0; i < 3; i++) 
			{
				if (st[i] == 0) //3���� �� ��á����
				{
					st[i] = leng; //��� ���̸�ŭ�� �־��ְ�
					stairpeo--; // ��� �Ѹ� �ٿ��ֱ�
					if (stairpeo == 0) // ����� ���̻� ������ break;
						break;
				}
			}
		}

		for (int i = 0; i < 3; i++)
		{
			if (st[i] > 0) {
				st[i]--; //�ð��� ��� ��ĭ�� ��������
			}
		}

		int checkvect = 1; // ��ܿ��� ��������� �Ÿ� �� ������ üũ
		int checkst = 1; // ��� �� ���������� üũ

		for (int i = 0; i < vect.size(); i++)
		{
			if (vect[i] > 0) //���� �� ��ܱ��� ������������ 
			{
				checkvect = 0;
				break;
			}
		}

		for (int i = 0; i < 3; i++)
		{
			if (st[i] > 0) //���� ��ܿ� ����� ������
			{
				checkst = 0;
				break;
			}
		}

		if (checkvect == 1 && checkst == 1 && stairpeo == 0) //��ܱ���,��ܿ�, ��� ��� ���� ��쿡 break
			break;
	}
	return time + 1; // ��ܿ� �����ϰ� �ٷ� �������� �����߱� ������ +1

}

void dfs(int k) //��� ������ ����� ��
{
	if (k == people)
	{

		int stair1 = simulation(0);
		int stair2 = simulation(1);

		//�� �߿� �� ū �ð����� �������
		maxnum = max(stair1, stair2);

		//�ּ� �� ����
		ans = min(maxnum, ans);

		return;
	}

	for (int i = 0; i < 2; i++)
	{
		stai.push_back(i);
		dfs(k + 1);
		stai.pop_back();
	}
}


int main(void)
{
	int test;
	cin >> test;

	for (int te = 1; te <= test; te++)
	{
		cin >> N;
		ans = 21e8;
		maxnum = 0;
		stairs.clear();
		stai.clear();
		peo.clear();

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> MAP[i][j];
				if (MAP[i][j] == 1)
				{
					peo.push_back({ i,j }); //��� ��ǥ
				}
				if (MAP[i][j] >= 2 && MAP[i][j] <= 10)
				{
					stairs.push_back({ i,j }); //��� ��ǥ
				}
			}
		}

		people = peo.size(); //��� ��
		dfs(0);

		cout << "#" << te << " " << ans << endl;
	}
}