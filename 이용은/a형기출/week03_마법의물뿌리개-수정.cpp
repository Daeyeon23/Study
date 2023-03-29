#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N;
int Max;//���� �� ���� ����
int tree[101];
/*
1. ���� �������� ����
2. ���� ��� ���� check ->
	Ȧ���� -> Max -2 != �̸� ������ ���ϱ�!
	¦���� -> Max-2>= �̸� ������ ���ϱ�
*/

void input();
int sol();

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		Max = 0;
		input();
		if (tree[0] == Max) {
			cout << "#" << tc << " 0\n";
			continue;
		}
		cout << "#" << tc << " " << sol() << "\n";
	}


	return 0;
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int tmp;
		cin >> tmp;
		tree[i] = tmp;
	}
	sort(tree, tree + N);
	Max = tree[N - 1];

}

int sol() {
	int day = 0;

	while (true) {
		int flagT = 0;
		int flag = 0;
		day++;
		for (int i = N - 1; i >= 0; i--) {
			if (tree[i] == Max) continue;
			flag = 1;//�������� -> ��� ���� ���� == Max
//Ȧ����
			if (day % 2 == 1) {
				if (tree[i] != Max - 2) {
					tree[i]++;
					break;//�Ϸ� ����
				}
				else {
					if (flagT == 0) {
						//ó�� �߰�
						flagT = 1;
					}
					else {//Max-2 �� ������ 2�� �̻��̶�� Ȧ�������� ���Ѵ�!
						flagT = 0;
						tree[i]++;
						break;//�Ϸ� ����
					}
				}
			}
			else {//¦����
				if (tree[i] <= Max - 2) {
					tree[i] += 2;
					break;//�Ϸ� ����
				}
			}

		}
		if (flag == 0) return day - 1;
	}
}