#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
struct customer {
	int K,T, N;
	//pq1����
	//1. �����ð� ����
	//2. ����ȣ ����
	bool operator < (customer next) const {
		if (T < next.T)
			return false;
		if (T > next.T)
			return true;
		if (K < next.K)
			return false;
		if (K > next.K)
			return true;
		return false;
	}

};
struct customer2 {
	int K, T, N;
	//pq2����
	//1.�ð� ���� ����
	//2. �̿� ����â�� ����
	bool operator < (customer2 next) const {
		if (T < next.T)
			return false;
		if (T > next.T)
			return true;
		if (N < next.N)
			return false;
		if (N > next.N)
			return true;
		return false;
	}

};

struct desk {
	int K, T,takeT;//takeT:���� �ð�

};
int cust_num_sum;
int N, M, K,A,B;

desk Reception[10];
desk Repair[10];
priority_queue<customer>pq1;
priority_queue<customer2>pq2;

void reset() {
	cust_num_sum = 0;
	memset(Repair, 0, sizeof(Repair));
	memset(Reception, 0, sizeof(Reception));
}

void input() {
	cin >> N >> M >> K >> A >> B;
	for (int i = 1; i <= N; i++) {
		int a;
		cin >>a;
		Reception[i].T = a;
	}
	for (int j = 1; j <= M; j++) {
		int b;
		cin >> b;
		Repair[j].T = b;
	}
	for (int k = 1; k <= K; k++) {
		int tk;
		cin >> tk;
		pq1.push({ k,tk, 0 });
	}

}

void allDeskFull(customer now) {
	int Min = 21e8;
	int Mindesk;
	//1.����â���� �������
	//���� ���� ������ â�� pq2�� �ֱ�
	for (int i = 1; i <= N; i++) {
		if (Reception[i].takeT < Min) {
			Min = Reception[i].takeT;
			Mindesk = i;
		}
	}
		
	int nT = Min + Reception[Mindesk].T;
	Reception[Mindesk].takeT = nT;
	Reception[Mindesk].K = now.K;

	pq2.push({ now.K, nT, Mindesk });
	
}

void allDeskFull2(customer2 now) {
	int Min = 21e8;
	int Mindesk;
	//2.����â���� �������

	for (int i = 1; i <= M; i++) {
		if (Repair[i].takeT < Min) {
			Min = Repair[i].takeT;
			Mindesk = i;
		}
	}
	Repair[Mindesk].K = now.K;
	Repair[Mindesk].takeT = Min+ Repair[Mindesk].T;
	//A â���� B â�� �̿���̸�
	if (now.N == A && Mindesk == B) {
		cust_num_sum += now.K;
		//cout << now.K<<endl;
	}

	
}

void sol() {
	//1. ����â���� �ֱ�
	while (!pq1.empty()) {
		customer now = pq1.top();
		pq1.pop();
		int flag = 0;
		for (int i = 1; i <= N; i++) {
			//1. �� â�� Ȯ��
			desk nowRecep = Reception[i];
			if (nowRecep.K == 0) {//1.ù�湮
				//recep ����
				int nK = now.K;
				int nT = now.T + nowRecep.T;
				Reception[i].K=nK;
				Reception[i].takeT = nT;

				//pq2 �ֱ�
				pq2.push({ now.K, nT, i });
				flag = 1;
				break;
			}
			else if (nowRecep.takeT <= now.T) {//2. �ð��������(�ι��̻� �湮)
				//recep ����
				int nK = now.K;
				int nT = now.T + nowRecep.T;
				Reception[i].K = nK;
				Reception[i].takeT = nT;

				//pq2 �ֱ�
				pq2.push({ now.K, nT, i });
				flag = 1;
				break;
			}
		}
		if (flag == 1) continue;//��â���� �־����� �����ɷ�
		
		//��� á���� , ��â�� ��ٸ���
		allDeskFull(now);


	}
	
	//2. ����â���� �ֱ�
	while (!pq2.empty()) {
		customer2 now = pq2.top();
		pq2.pop();
		int flag = 0;
		for (int i = 1; i <= M; i++) {
			// �� â�� Ȯ��
			desk nowRepa = Repair[i];
			if (nowRepa.K == 0) {//1.ù�湮
				//recep ����
				int nK = now.K;
				int nT = now.T + nowRepa.T;
				Repair[i].K = nK;
				Repair[i].takeT = nT;

				if (now.N == A && i == B) {
					cust_num_sum += now.K;
					//cout << now.K << endl;
				}
				flag = 1;
				break;
			}
			else if (nowRepa.takeT <= now.T) {//2. �ð��� �������
				///recep ����
				int nK = now.K;
				int nT = now.T + nowRepa.T;
				Repair[i].K = nK;
				Repair[i].takeT = nT;

				if (now.N == A && i == B) {
					cust_num_sum += now.K;
					//cout << now.K << endl;
				}
				flag = 1;
				break;
			}
		}

		if (flag == 1) continue;
		allDeskFull2(now);
	}


}

int main() {
	//freopen("input.txt", "r", stdin);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		reset();
		input();
		
		sol();


		if (cust_num_sum == 0) {
			cout << "#" << tc << " " << -1 << endl;
			continue;
		}
		cout << "#" << tc << " " << cust_num_sum << endl;
	}
	return 0;
}

