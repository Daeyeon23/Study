/*
parametric search�� �̿��Ͽ� �ذ��Ͽ���.

st = ���̺��� �ִ밪
en = ���̺� ������� �հ�

mid���� �����ϰ� �� ���� ���� �ʴ� ������ ������ ������ �� ���� ���� ������ cnt��� �� ��

cnt<=T �� ��(���� ���ų� �����ϰ� ��������� ���) mid���� ���亸�� ũ�ų� ���� ��� => right = mid -1

cnt > T �� �� (���� ���� ��������� ���) mid���� ���亸�� ���� ��� => left = mid+1

st���� en������ �� �� cnt�� ���� ���ϴ� ���鿡���� ��(mid)�� �츮�� ���ϴ� ����
*/

#include <iostream>
#include <cstring>
using namespace std;

int n, t;

int table[1001];

// ��� ���̽��� ���� ���� ������ ����
// ��, cnt <= t�� �����ϴ� ��찡 �� ������ ������ true�� ��ȯ
// false�� ���� ��� ���̽��� ���ؼ� cnt > T�� ���
bool condition(int now)
{
	for (int i = 0; i < n; ++i)
	{
		int tmp = 0;
		int cnt = 0;
		for (int j = i; j < i + n; ++j)
		{
			tmp += table[j];

			if (tmp > now)
			{
				tmp = table[j];
				cnt++;
			}

			if (cnt >= t) break;
		}
		cnt++;

		if (cnt <= t)
			return true;
	}
	return false;
}


int psearch(int left, int right)
{
	int mid;
	int ans;
	while (left <= right)
	{
		mid = (left + right) / 2;

		if (condition(mid))
		{
			// condition�� true�� ���� mid���� �����̹Ƿ� mid�� ���� ���� ans�� �����صд�.
			ans = mid;
			right = mid - 1;
		}

		else
			left = mid + 1;
	}
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n >> t;
	
	int st = -21e8;
	int en = 0;

	for (int i = 0; i < n; ++i)
	{
		cin >> table[i];
		table[i + n] = table[i];

		st = max(st, table[i]);
		en += table[i];
	}
	cout << psearch(st, en);

	return 0;
}