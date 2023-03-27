#include <iostream>
using namespace std;

int N;           // ������� ��
int tree[100000]; // ���� ����
int sum = 0;     // ���� ��
int twocnt = 0; // /2 ����


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> tree[i];
		sum += tree[i];
		twocnt += tree[i] / 2;
	}

	if (sum % 3 != 0 || twocnt < sum / 3) {
		cout << "NO";
		return 0;
	}
	cout << "YES";

	return 0;
}