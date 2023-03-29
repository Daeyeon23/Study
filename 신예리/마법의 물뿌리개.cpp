#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int N;
int tree[101];
int ans;
int bigtree;

// ���� ū ������ �ٸ� �������� ���̰� %2�� 1 ���Ѹ���(Ȧ��)
// /2�� 2 ���Ѹ����� ���(¦��)
// Ȧ���� ¦���� �� �߿� �� ū ���� �������� ��¥ �� ����
// ¦���� ���� Ȧ�� ��Ʋ�� �������ָ鼭 ¦���� ���� 0���� �۾����� while�� ������

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int test;
    cin >> test;

    for (int te= 1; te <= test; te++) {

        memset(tree, 0, sizeof(tree));
        ans = 21e8;
        bigtree = -21e8;

        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> tree[i];
            bigtree = max(bigtree, tree[i]);
        }

        int oddcnt = 0; // Ȧ�� ��¥ �� 
        int evencnt = 0; // ¦�� ��¥ �� 

        for (int i = 0; i < N; i++) {
            int diff = bigtree - tree[i];
            oddcnt += diff % 2;
            evencnt += diff / 2;
        }

        while (evencnt >= 0) {

            //Ȧ���� ���� �� 
            int oddday = oddcnt * 2 - 1;
            //¦���� ���� ��
            int evenday = evencnt * 2;

            int maxday;
             maxday = max(oddday, evenday);

             oddcnt = oddcnt + 2; // ¦�� �Ϸ縦 Ȧ�� ��Ʋ�� �ٲٱ�
             evencnt--; 

             ans = min(ans, maxday); 
            
        }

        cout << "#" << te << " " << ans << '\n';
    }
}