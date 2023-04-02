#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;

// �°�����ŭ while�� �ݺ�
// �� �°��� �������� ���������� �̵���Ű��, �Ҹ��� ���� ���� �ι谡 ����
// �̵��ϴ� ���� ���ᰡ �ٴڳ��� �̵�����
// �������� �̵���Ų ���ÿ� ���� �ٴڳ��� ���� ������

struct yx {
    int y;
    int x;
};

int MAP[21][21];
int visited[21][21] = { 0 };
int N, M, first_fuel;
int start_y, start_x;

int ydir[4] = { -1,1,0,0 };
int xdir[4] = { 0,0,-1,1 };

vector<yx>guest_vect;
vector<yx>dest_vect;

void bfs(int y, int x) {

    while (M--) {

        // �Ÿ��� ���� ����� �°� ã�Ƽ� �̵��ϱ�
        memset(visited, 0, sizeof(visited));

        queue<yx>q;
        q.push({ y,x });
        visited[y][x] = 1;

        while (!q.empty()) {
            yx now = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int ny = now.y + ydir[i];
                int nx = now.x + xdir[i];

                if (ny<1 || nx<1 || ny>N || nx>N)continue;
                if (MAP[ny][nx] == 1)continue;
                if (visited[ny][nx] > 0)continue;

                visited[ny][nx] = visited[now.y][now.x] + 1;

                q.push({ ny,nx });

            }
        }

        int min_dist = 9999; //�ּҰŸ� ã��
        int move_y = 0; // �̵��� ��ǥ ���ϱ�
        int move_x = 0;
        int g_index = 0; // �������� �մ��� index

        int gvect_size = guest_vect.size();
        for (int i = 0; i < gvect_size; i++) {

            // �̵��Ÿ��� �ּ��� �°� ã��
            if (min_dist > visited[guest_vect[i].y][guest_vect[i].x]) {
                min_dist = visited[guest_vect[i].y][guest_vect[i].x];
                move_y = guest_vect[i].y;
                move_x = guest_vect[i].x;
                g_index = i;
            } //���� �̵��Ÿ��� ������ ��쿡
            else if (min_dist == visited[guest_vect[i].y][guest_vect[i].x]) {
                // �� ��ȣ�� ���� ���� �°�
                if (move_y > guest_vect[i].y) {
                    move_y = guest_vect[i].y;
                    move_x = guest_vect[i].x;
                    g_index = i;
                } // �� ��ȣ�� ������ �� ��ȣ�� ���� ���� �°�
                else if (move_y == guest_vect[i].y && move_x > guest_vect[i].x) {
                    move_y = guest_vect[i].y;
                    move_x = guest_vect[i].x;
                    g_index = i;
                }

            }
        }
        // �̵��� �°��� ���� ���� vect���� �����ֱ�
        guest_vect.erase(guest_vect.begin() + g_index);
        first_fuel = first_fuel - (visited[move_y][move_x] - 1); // ���� ���

        // ���� �°����� �������� ���߰ų� ���ᰡ �ٴڳ��� -1�� ���ְ� ������
        if (visited[move_y][move_x] == 0 || first_fuel <= 0) {
            first_fuel = -1;
            break;
        }


        // �°��� �¿�� �� �°��� �������� �ش��ϴ� �� ���� �̵�
        memset(visited, 0, sizeof(visited));

        queue<yx>q1;
        q1.push({ move_y,move_x });
        visited[move_y][move_x] = 1;

        while (!q1.empty()) {
            yx now = q1.front();
            q1.pop();

            for (int i = 0; i < 4; i++) {
                int ny = now.y + ydir[i];
                int nx = now.x + xdir[i];

                if (ny<1 || nx<1 || ny>N || nx>N)continue;
                if (MAP[ny][nx] == 1)continue;
                if (visited[ny][nx] > 0)continue;

                visited[ny][nx] = visited[now.y][now.x] + 1;

                q1.push({ ny,nx });

            }
        }

        // �°� index�� �̿��ؼ� ������ ��ǥ 
        int dest_y = dest_vect[g_index].y;
        int dest_x = dest_vect[g_index].x;

        // �̵��� �������� ���� ������ �����ֱ�
        dest_vect.erase(dest_vect.begin() + g_index);
        first_fuel = first_fuel - (visited[dest_y][dest_x] - 1);

        //�������� �̵����� ���߰ų� �������� �������� �� ���ᰡ 0���� �۾����� ������
        if (visited[dest_y][dest_x] == 0 || first_fuel < 0) {
            first_fuel = -1;
            break;
        }
        // ���� ���а� �ƴ϶�� �°��� �¿�� �������� �̵��� ��ŭ�� 2�� ���� ä���ֱ�
        first_fuel = first_fuel + (visited[dest_y][dest_x] - 1) * 2;

        // ���� ���� ���ؼ� ���� ��ǥ ����
        y = dest_y;
        x = dest_x;
    }
}


int main() {
    // N, M, �ʱ� ������ ��
    // N���� �ٿ� ���� ����
    // ������ ������ �����ϴ� ĭ�� ��,����ȣ -> ������ �����ϴ� ĭ�� ��ĭ
    // M���� �ٿ� ���� �°��� ������� ��, ����ȣ/ �������� ��, ����ȣ

    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M >> first_fuel;

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> MAP[i][j];
        }
    }

    cin >> start_y >> start_x;

    for (int i = 0; i < M; ++i) {
        int g_y, g_x, d_y, d_x;
        cin >> g_y >> g_x >> d_y >> d_x;
        guest_vect.push_back({ g_y,g_x }); // �մ� ��ǥ ���Ϳ� ���
        dest_vect.push_back({ d_y,d_x }); // ������ ��ǥ ���Ϳ� ���
    }

    bfs(start_y, start_x);

    cout << first_fuel;

    return 0;
}