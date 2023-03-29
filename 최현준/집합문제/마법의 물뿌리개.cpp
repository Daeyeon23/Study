/*
	������ �ִ� ���̸� max_height�� ������ �Ŀ�
	�� ������ �ִ� ���� ������ �Ÿ��� value�� ������ �� 
	odd, even�� �ʿ��� Ȧ�� �� ��,¦�� �� ���� �����Ͽ���.
	odd = value%2, even = value/2
	�̶� odd�� �ݵ�� �ʿ��� Ȧ�� �� ���̴�.
	���� ans��� �Լ��� ���ؼ� �ּ� ��¥ ���� ���Ͽ���.


*/

#include <iostream>
#include <cstring>
using namespace std;

int T, n;

int tree[101];


// �ּ� ��¥ �� ���ϱ�
int ans(int odd, int even)
{
	if (odd > even) //Ȧ�� > ¦��
		return 2 * odd - 1;

	else if (odd == even) // ���� ��
		return 2 * odd;

	else // ¦�� > Ȧ��
	{
		while (even - odd > 1) // ¦���� Ȧ������ 1�� �� Ŭ ���� Ȧ���� ��ȯ�ϸ� ������ �� ����
		{
			even -= 1;
			odd += 2;
		}

		if (even >= odd)
			return 2 * even;
		else
			return 2 * odd - 1;
	}

}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> T;
	for (int tc = 1; tc <= T; ++tc)
	{
		int max_height = 0;
		int odd = 0;
		int even = 0;

		cin >> n;

		for (int i = 0; i < n; ++i)
		{
			cin >> tree[i];
			max_height = max(max_height, tree[i]);
		}

		for (int i = 0; i < n; ++i)
		{
			int value = max_height - tree[i];
			even += value / 2;
			odd += value % 2;
		}

		cout << "#" << tc << " " << ans(odd, even) << '\n';

	}
	return 0;
}
