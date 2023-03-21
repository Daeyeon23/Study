#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

// 1. 1���� �� �� ����, 2��(���ιݴ�)/3��(����)�� �� ����, 4���� ������, 5���� �׹���
// 2. �����Ͽ�� ���⺤�� �������ְ� cctv�� ��Ȳ�� ���� ���� ��ȯ
// 3. �� cctv�� ���� ó�� �� �� ������ ���� cctv�� �Ѿ�� �Ȱ��� ����

struct yx {
    int y;
    int x;
};

vector<yx>cctv_vect; //cctv

int MAP[9][9]; //MAP����
int N, M; //����, ����

int ydir[4] = { -1,0,1,0 }; //�� �� �� ��
int xdir[4] = { 0,-1,0,1 };
int blind_result = 9999; //����
int cctv_cnt;

void check(int y, int x, int dir) {

    dir = dir % 4; //0~3�� �Ѿ�� ��쿡 0~3�� ������ ����

    while (1) {
        int ny = y + ydir[dir]; //�ش� dir�� ���� ������ �� ���� ��� Ȯ���ϰ� ����
        int nx = x + xdir[dir];

        y = ny; // ���� ��ǥ�� ���ؼ� y,x�� ���� ny, nx������ ���� 
        x = nx;

        if (ny < 0 || nx < 0 || ny >= N || nx >= M) break; //�� ����� ������
        if (MAP[ny][nx] == 6)break; //�� ������ ������
        if (MAP[ny][nx] != 0)continue; // cctv�� ���� ���� �� ��ǥ�� �Ѿ ���� ��ǥ��
        MAP[ny][nx] = 9;// cctv�� ������ ��ġ�� �� #��� 9�� ��Ÿ���� 

    }
}

void simul(int num) {


    if (num == cctv_cnt) { //��� cctv�� �� ������� ���� �簢������ �κ��� �� �����ֱ�
        int blind_cnt = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (MAP[i][j] == 0) {
                    blind_cnt += 1;
                }
            }
        }
        blind_result = min(blind_result, blind_cnt);
        return;
    }

    yx now = cctv_vect[num];

    int MAP_copy[9][9];

    for (int dir = 0; dir < 4; dir++) {
        memcpy(MAP_copy, MAP, sizeof(MAP));

        if (MAP[now.y][now.x] == 1) {
            check(now.y, now.x, dir);
        }
        else if (MAP[now.y][now.x] == 2) {
            check(now.y, now.x, dir);
            check(now.y, now.x, dir + 2);
        }
        else if (MAP[now.y][now.x] == 3) {
            check(now.y, now.x, dir);
            check(now.y, now.x, dir + 1);
        }
        else if (MAP[now.y][now.x] == 4) {
            check(now.y, now.x, dir);
            check(now.y, now.x, dir + 1);
            check(now.y, now.x, dir + 2);
        }
        else if (MAP[now.y][now.x] == 5) {
            check(now.y, now.x, dir);
            check(now.y, now.x, dir + 1);
            check(now.y, now.x, dir + 2);
            check(now.y, now.x, dir + 3);
        }

        simul(num + 1);

        memcpy(MAP, MAP_copy, sizeof(MAP_copy));
    }


}

int main() {

    ios::sync_with_stdio(false);
    cout.tie(NULL); cin.tie(NULL);

    cin >> N >> M;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> MAP[i][j];
            if (MAP[i][j] >= 1 && MAP[i][j] <= 5) {
                cctv_vect.push_back({ i,j });
            }
        }
    }

    cctv_cnt = cctv_vect.size();

    simul(0);

    cout << blind_result;

    return 0;

}