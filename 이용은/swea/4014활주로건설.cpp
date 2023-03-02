#include <iostream>
using namespace std;
int ans;
int N, X;
int MAP[20][20];
int MAPx[20][20];
int visited[20];
void reset() {
    ans = 0;
}
void resetV() {
    for (int x = 0; x < 20; x++) {
        visited[x] = 0;
    }
}

void input() {
    cin >> N >> X;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cin >> MAP[y][x];
            MAPx[x][y] = MAP[y][x];//��ġ��� �����
        }
    }
}
//���� ��ġ �������� Ȯ��
// left : type ==0
// right: type == 1
//idx: ���� index, end :���� idx, arr: Ȯ���� ��(�Ǵ¿�)
bool check(int idx, int type,int end, int arr[20]) {
    int tmp = arr[idx];//�����ε��� ����
    if (type == 1) {//������ Ȯ��
        if (end >= N) return false;//1.���� �ʰ��� ����
        for (int x = idx; x <= end; x++) {
            if (arr[x] != tmp) return false;//2.���� �ٸ��� ����
            if (visited[x] == 1)return false;//3. ��ġ�� ��� ����
            visited[x] = 1;//��ġ�� �ʰ� �湮ó��
        }
    }
    else {//����Ȯ��
        if (end < 0) return false;
        for (int x = idx; x >= end; x--) {
            if (arr[x] != tmp) return false;
            if (visited[x] == 1)return false;
            visited[x] = 1;
        }
        
    }
    //���� ������ 
    return true;

}

void sol(int arr[20]) {
    int flag = 0;
    for (int i = 0; i < N-1; i++) {
        if (arr[i] == arr[i + 1]) continue;//#1.�յ� �������
        else if (arr[i] - arr[i + 1] == 1) {//#2. ��>�� �ΰ�� ->������ Ȯ��
            if (!check(i+1, 1,i+X, arr)) {
                flag = 1;
                break;
            }
        }
        else if (arr[i] - arr[i + 1] == -1) {
            if (!check(i, 0,i-X+1, arr)) {//#3. ��<�� �ΰ�� ->���� Ȯ��
                flag = 1;
                break;
            }
        }
        else {//#4. �յ� �������̰� 1�� �ƴѰ�� ->�Ǽ��Ұ�
            flag = 1;
            break;
        }
    }

    if (flag == 0)ans++;
}


int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        reset();
        input();
        for (int i = 0; i < N; i++) {
            resetV();//visited�ʱ�ȭ
            sol(MAP[i]);//�� Ȯ��
            resetV();//visited�ʱ�ȭ
            sol(MAPx[i]);//�� Ȯ��
        }



        cout << "#" << tc << " " << ans << endl;
    }

    return 0;
}