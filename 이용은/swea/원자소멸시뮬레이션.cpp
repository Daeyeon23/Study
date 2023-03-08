#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
struct Atom {
	int x, y, dir, K;
};
struct Collision {
	int i, j, dist;//
};
vector<Atom>v;
int N;
int totalE;
int visited[1000];
vector<Collision>col;;//�浹�� ���ɼ� �ִ� ���� �� ����
//�Ÿ��� �ּڰ� ����
// isAlive�� 1�� �ٲپ��ֱ�
//�Ÿ��� ���� ��� ������ ���ڰ� �浹 �� �� ����

bool cmp(Collision left, Collision right) {
	if (left.dist < right.dist)
		return true;
	if (left.dist > right.dist)
		return false;
	return false;

}


void reset() {
	totalE = 0;
	v = vector<Atom>();
	col = vector<Collision>();
	memset(visited, 0, sizeof(visited));
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int x, y, dir, K;
		cin >> x >> y >> dir >> K;
		v.push_back({ x,y,dir,K });
	}
}

int getDist(int x1, int x2) {
	if (x1 - x2 < 0) return x2 - x1;
	return x1 - x2;
}

bool dircheck(int dir1, int dir2) {
	if (dir1 % 2 == 0) dir1 += 1;
	else dir1 -= 1;

	if (dir1 == dir2)return true;
	return false;

}

void findcol() {

	for (int i = 0; i < N; i++) {
		Atom atom1 = v[i];
		for (int j = i + 1; j < N; j++) {
			Atom atom2 = v[j];
			//#1 �ΰ��� ������ ������ >> ������ ����
			if (atom1.dir == atom2.dir) continue;

			//#2 �ΰ��� ���� �ݴ�� >> ���� ��/���� �ִ��� check
			else if (dircheck(atom1.dir, atom2.dir)) {
				if (atom1.dir == 0) {//���̸�
					if (atom1.x == atom2.x && atom1.y < atom2.y) {
						int dist = getDist(atom1.y, atom2.y);
						col.push_back({ i,j,dist });
					}
				}
				else if (atom1.dir == 1) {//���̸�
					if (atom1.x == atom2.x && atom1.y > atom2.y) {
						int dist = getDist(atom1.y, atom2.y);
						col.push_back({ i,j,dist });
					}
				}
				else if (atom1.dir == 2) {//���� �࿡ �ִ��� Ȯ��
					if (atom1.y == atom2.y && atom1.x > atom2.x) {
						int dist = getDist(atom1.x, atom2.x);
						col.push_back({ i,j,dist });
					}
				}
				else if (atom1.dir == 3) {//���� �࿡ �ִ��� Ȯ��
					if (atom1.y == atom2.y && atom1.x < atom2.x) {
						int dist = getDist(atom1.x, atom2.x);
						col.push_back({ i,j,dist });
					}
				}

			}

			//���� ������ ���
			else {
				if (atom1.x - atom2.x == 0) continue;
				//���Ⱑ 1 �� ���
				if ((atom1.y - atom2.y) == (atom1.x - atom2.x))
				{
					if (atom1.x > atom2.x) {
						Atom tmp = atom1;
						atom1 = atom2;
						atom2 = tmp;
					}

					if ((atom1.dir == 3 && atom2.dir == 1)) {
						int dist = getDist(atom1.y, atom2.y);
						col.push_back({ i,j,dist * 2 });
					}
					if ((atom1.dir == 0 && atom2.dir == 2)) {
						int dist = getDist(atom1.y, atom2.y);
						col.push_back({ i,j,dist * 2 });
					}

				}

				//���Ⱑ -1�ΰ��
				else if ((atom1.y - atom2.y) == -(atom1.x - atom2.x)) {
					if (atom1.x > atom2.x) {
						Atom tmp = atom1;
						atom1 = atom2;
						atom2 = tmp;
					}
					if ((atom1.dir == 3 && atom2.dir == 0)) {
						int dist = getDist(atom1.y, atom2.y);
						col.push_back({ i,j,dist * 2 });
					}
					else if ((atom1.dir == 1 && atom2.dir == 2)) {
						int dist = getDist(atom1.y, atom2.y);
						col.push_back({ i,j,dist * 2 });
					}

					
				}

			}

			atom1 = v[i];//atom1 ����
		}
	}
}

void Colcheck() {

	int colsize = col.size();
	if (colsize == 0) {
		return;
	}

	sort(col.begin(), col.end(), cmp);//dist ��������

	for (int x = 0; x < colsize; x++) {
		Collision now = col[x];
		int A = now.i;
		int B = now.j;
		if (visited[B] != 0 && visited[A] != 0) continue;

		else if (visited[B] == 0 && visited[A] == now.dist) {
			visited[B] = now.dist;
			totalE += v[B].K;
		}
		else if (visited[A] == 0 && visited[B] == now.dist) {
			visited[A] = now.dist;
			totalE += v[A].K;
		}

		//ó���浹
		else if (visited[A] == 0 && visited[B] == 0) {
			visited[A] = now.dist;
			visited[B] = now.dist;
			totalE += v[A].K;
			totalE += v[B].K;
		}

	}
}

int main() {

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		reset();
		input();
		findcol();
		Colcheck();
		cout << "#" << tc << " " << totalE << endl;
	}

	return 0;
}