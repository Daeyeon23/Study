#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

//��Ȧ�� ��ǥ
struct hole {
	int y;
	int x;
};

int starty, startx; //������ġ
int MAP[102][102];

vector<hole>v[11]; //��Ȧ �� ���� ���

int ydir[4] = { -1,1,0,0 }; //�����¿�
int xdir[4] = { 0,0,-1,1 };
int cnt;
int maxscore; //����

void simul(int bally, int ballx, int dir) {

	cnt = 0;

	while (1) {

		bally += ydir[dir];
		ballx += xdir[dir];

		//��Ȧ�̰ų� ���������� �� �ִ밪 ����
		if (MAP[bally][ballx] == -1 || (bally == starty && ballx == startx)) {
			if (cnt > maxscore) {
				maxscore = cnt;
			}
			break;
		}

		if (MAP[bally][ballx] == 0)continue;
		//1�� ����� �� ���� ��ȯ
		if (MAP[bally][ballx] == 1) {
			cnt++;
			if (dir == 0) {
				dir = 1;
			}
			else if (dir == 1) {
				dir = 3;
			}
			else if (dir == 2) {
				dir = 0;
			}
			else if (dir == 3) {
				dir = 2;
			}
		}

		//2�� ����� �� ���� ��ȯ
		if (MAP[bally][ballx] == 2) {
			cnt++;
			if (dir == 0) {
				dir = 3;
			}
			else if (dir == 1) {
				dir = 0;
			}
			else if (dir == 2) {
				dir = 1;
			}
			else if (dir == 3) {
				dir = 2;
			}
		}

		//3�� ����� �� ���� ��ȯ
		if (MAP[bally][ballx] == 3) {
			cnt++;
			if (dir == 0) {
				dir = 2;
			}
			else if (dir == 1) {
				dir = 0;
			}
			else if (dir == 2) {
				dir = 3;
			}
			else if (dir == 3) {
				dir = 1;
			}
		}

		//4�� ����� �� ���� ��ȯ
		if (MAP[bally][ballx] == 4) {
			cnt++;
			if (dir == 0) {
				dir = 1;
			}
			else if (dir == 1) {
				dir = 2;
			}
			else if (dir == 2) {
				dir = 3;
			}
			else if (dir == 3) {
				dir = 0;
			}
		}

		//5�� ����� �� ���� ��ȯ
		if (MAP[bally][ballx] == 5) {
			cnt++;
			if (dir == 0) {
				dir = 1;
			}
			else if (dir == 1) {
				dir = 0;
			}
			else if (dir == 2) {
				dir = 3;
			}
			else if (dir == 3) {
				dir = 2;
			}
		}

		//��Ȧ���� ���� ��ġ�� �ƴ� �ٸ� ��ġ�� �̵�
		if (MAP[bally][ballx] >= 6 && MAP[bally][ballx] <= 10) {
			for (int i = 0; i < v[MAP[bally][ballx]].size(); i++) {
				hole now = v[MAP[bally][ballx]][i];
				if (now.y != bally || now.x != ballx) {
					bally = now.y;
					ballx = now.x;
					break;
				}
			}
		}

	}

}


int main() {

	int test;
	cin >> test;

	for (int te = 1; te <= test; te++) {
		memset(MAP, 0, sizeof(MAP));
		memset(v, 0, sizeof(v));
		maxscore = 0;

		int N;
		cin >> N;

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cin >> MAP[i][j];
				//��Ȧ�� ���� ������ �� ��Ȧ ��ȣ index�� ���Ϳ� �־��ֱ�
				if (MAP[i][j] >= 6 && MAP[i][j] <= 10) {
					v[MAP[i][j]].push_back({ i,j });
				}
			}
		}
		//�����ڸ��� �� ������ֱ�
		for (int i = 0; i <= N + 1; i++) {
			for (int j = 0; j <= N + 1; j++) {
				if (i == 0 || j == 0 || i == N + 1 || j == N + 1) {
					MAP[i][j] = 5;
				}
			}
		}

		//��� ��ġ�� ���� ���� ���Ƿ� �������� -> ������ �������� �׶��� 4���� ���� ������ �� ���ֱ�
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (MAP[i][j] == 0) {
					starty = i;
					startx = j;
					for (int dir = 0; dir < 4; dir++) {
						simul(i, j, dir);
					}
				}
			}
		}


		cout << "#" << te << " " << maxscore << endl;


	}
	return 0;
}