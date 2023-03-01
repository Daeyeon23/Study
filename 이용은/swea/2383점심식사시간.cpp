#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct MAN {
	int y, x;
	int dist0, dist1;
};
struct Stair {
	int y, x;
	int time;//�������µ� �ɸ��� �ð�
};
int MinTime =21e8;
int N;
int manCnt;
vector<MAN>v;
vector<Stair>stair;
vector<int>path0;
vector<int>path1;
int visited[11];


void reset() {
	v = vector<MAN>();
	stair = vector<Stair>();
	MinTime = 21e8;
	for (int i = 0; i < 11; i++) {
		visited[i] = 0;
	}
}

void input() {
	cin >> N;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int tmp;
			cin >> tmp;
			if (tmp == 1) v.push_back({ y,x,0,0 });
			else if (tmp != 0) stair.push_back({ y,x,tmp });
		}
	}
	manCnt = v.size();//�����
}



int getDist(int y1, int x1, int y2, int x2) {
	int ny, nx;
	if (y1 - y2 < 0) ny = y2 - y1;
	else ny = y1 - y2;
	if (x1 - x2 < 0) nx = x2 - x1;
	else nx = x1 - x2;
	return ny + nx;
}

//�Ÿ� ���ϱ�
void findDist() {
	
	for (int i = 0; i < 2; i++) {
		Stair stairnow = stair[i];
		for (int j = 0; j < manCnt; j++) {
			//j��° ����� i�� ��ܱ��� �Ÿ� ���ϱ�
			MAN now = v[j];
			if (i == 0) {
				v[j].dist0 = getDist(now.y, now.x, stairnow.y, stairnow.x);
			}
			else if (i == 1) {
				v[j].dist1 = getDist(now.y, now.x, stairnow.y, stairnow.x);
			}
			
		}
	}
}
//type ==0 >> path0
int findMinTime( vector<int>stair0, vector<int>stair1) {
	int size0 = stair0.size();
	int size1 = stair1.size();
	int tmp0=0, tmp1=0;
	//���� ������ ������� ����
	sort(stair0.begin(), stair0.end());
	sort(stair1.begin(), stair1.end());

	//size0 ��ŭ�� ����� stair0�տ� �����
	for (int i = 0; i < size0; i++) {
		if (i < 3) continue;//3��° ���Ϸ� ������ ����� ���ð� =�����ð�
		if (i >= 3) {//3���̻� ������̸�
			//3��° �տ� ������ ����� �ð���  ��
			//���ð� > �����ð��̸�, ���ð����� �ٲپ���
			if (stair0[i - 3] + stair[0].time > stair0[i]) {
				stair0[i] = stair0[i - 3] + stair[0].time;
			}
		}
	}

	//���� ����
	for (int i = 0; i < size1; i++) {
		if (i < 3) continue;
		if (i >= 3) {
			if (stair1[i - 3] + stair[1].time > stair1[i]) {
				stair1[i] = stair1[i - 3] + stair[1].time;
			}
		}
	}
	//���������� ��� �������� ����� �ɸ��ð� ���ϱ�
	if (size0 != 0)
		tmp0 = stair0[size0 - 1] + stair[0].time;
	else tmp0 = 0;

	if (size1 != 0)
		tmp1 = stair1[size1 - 1] + stair[1].time;
	else tmp1 = 0;
	
	//���߿� �����ɸ� �ð� return
	return max(tmp1, tmp0);
}


void DFS(int now) {
	if (now == manCnt) { //��� ����� ������ ����� ����������
		//�������µ� �ɸ� �ð� �ּڰ� ����
		int result = findMinTime(path0,path1);
		MinTime = min(MinTime, result);
		return;
	}
	//recursive
	MAN nowMan = v[now];
	for (int i = 0; i < 2; i++) {
		if (i == 1) {
			path1.push_back(nowMan.dist1);//1����ܾտ��� ���
			visited[now] = 1;//������
			DFS(now + 1);
			visited[now] = 0;
			path1.pop_back();
		}
		else if (i == 0) {
			path0.push_back(nowMan.dist0);//0����� �տ��� ���
			DFS(now + 1);
			path0.pop_back();
		}
		
	}
}

int main() {
	int T; 
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		reset();
		input();
		findDist();
		DFS(0);
		cout << "#" << tc << " " << MinTime+1 << endl;
	}
	return 0;
}
