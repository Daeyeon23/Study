#include <iostream>
#include <algorithm>
using namespace std;

int N, T;
int arr[501];
int totalsum = 0;
int maxval = -21e8;

int make_team(int val_mid) {

	int sum = 0;
	int cnt = 0;

	for (int i = 0; i < N; i++) {
		sum = 0;
		cnt = 1;
		for (int j = i; j < i + N; j++) {
			if (sum + arr[j % N] > val_mid) {
				sum = arr[j % N];
				cnt++; //���߰�
			}
			else {
				sum += arr[j % N];
			}
		}
		if (cnt <= T) {
			return 1;
		}
	}

	return 0;
}

int binary() {

	// left�� T=N�� ���� ��, right�� T=1�϶� ��
	int left = maxval;
	int right = totalsum;
	int result = 0;

	while (left <= right) {
		int mid = (left + right) / 2; // ���� �ɷ�ġ ���ذ�
		
		if (make_team(mid)==1) {
			right = mid - 1;
			result = mid;
		}
		else {
			left = mid + 1;
		}
	}

	return result;
}


int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> T; //N�� ����� T�� ���� �� 

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		maxval = max(maxval, arr[i]); // ���� ū ���� ��ü ��
		totalsum += arr[i];
	}
	
	int ans = binary();
	cout << ans;

	return 0;
}