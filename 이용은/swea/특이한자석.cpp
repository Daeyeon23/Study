#include <iostream>
#include <vector>
using namespace std;
struct rot {
	int num, type;
};
int K;
int magnet[4][8];
vector<rot>v;
int isRotate[4] = { 0, };//index: �ڼ����� // value : -1�ݽð�, 1�ð�, 0�״��

void reset() {
	v = vector<rot>();
}


void input() {
	cin >> K;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 8; x++) {
			cin >> magnet[y][x];
		}
	}
	for (int i = 0; i < K; i++) {
		int num, type;
		cin >> num >> type;
		num -= 1;
		v.push_back({ num, type });
	}
	
}
// type -1 >> �ݽð�(����) 
// type 1 >> ������
// type 0 >> ȸ�� X
// num : magnet��ȣ0~3
void rotate(int num, int type) {
	if (type == 0) return;//�״��
	//�ð�
	if (type == 1) {
		int tmp = magnet[num][7];
		for (int i = 6; i >= 0; i--) {
			magnet[num][i + 1] = magnet[num][i];
		}
		magnet[num][0] = tmp;
	}
	//�ݽð�
	else if (type == -1) {
		int tmp = magnet[num][0];
		for (int i = 1; i < 8; i++) {
			magnet[num][i - 1] = magnet[num][i];
		}
		magnet[num][7] = tmp;
	}
}

//���ư��� �ڼ� Ȯ��
void check(int num, int type) {
	
	isRotate[num] = type;//������ ���ư�
	
	//�� ������ ���� �ִ��� Ȯ���ϱ�
	int ntype =type;//���� ��ȯ��
	
	int i = 0;
	//#1�翷�� �ڼ��� ���ų�
	//#2ȸ������ ���������� �ݺ�
	while (true) {
		i++;//�� ��Ȯ��
		int flag = 0;
		
		//ȸ������ ��ȯ
		if (ntype == 1) ntype = -1;
		else ntype = 1;

		if (num - i >= 0) {//���� �ڼ�Ȯ��(���� �Ѿ�� �ʴ°�츸)
			if (magnet[num - i][2] == magnet[num-i+1][6]) {
				if (isRotate[num - i + 1] != 0) {//������ �ڼ��� ȸ���ϴ� ��쿡�� ��ȿ
					flag = 1;
					isRotate[num - i] = ntype;
				}
			}
		}

		if (num + i <= 3) {//������ �ڼ� Ȯ��
			if (magnet[num + i-1][2] == magnet[num+i][6]) {
				if (isRotate[num + i - 1] != 0) {
					flag = 1;
					isRotate[num + i] = ntype;
				}
			}
		}
		//�������� -> ȸ���� �ڼ��� ���°��
		if (flag == 0) break;
	}

	//�ڼ��� ȸ������ ��� ������
	//��� ������
	for (int x = 0; x < 4; x++) {
		rotate(x, isRotate[x]);
	}
	
}

void resetR() {
	for (int j = 0; j < 4; j++) {
		isRotate[j] = 0;
	}
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {

		reset();
		input();
		int sizeV = v.size();
		for (int i = 0; i < sizeV; i++) {
			resetR();
			check(v[i].num, v[i].type);
		}

		int result = 0;
		for (int i = 0; i < 4; i++) {
			int tmp = magnet[i][0] << i;
			result += tmp;
		}
		cout << "#" << tc << " " << result << endl;

	}
	return 0;
}