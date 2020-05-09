#define _CRT_SECURE_NO_WARNINGS

#define maxHeight 6
#define setup 10
#define ascend 1
#define descend 2

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int arr[21][21];
int test[6][21];
int N, X, T;

bool solve(vector<int> path) {

    bool flag = false;
    vector<int> temp;
    vector<pair<int, int> > point;

    // [0] �� �� ������ ��Ƶα�
    for (int i = 0; i < N; i++) temp.push_back(path[i]);
    
    // [1] ���̿� ���� �׷��� ���� (Fig. 6�� ����)
    for (int i = maxHeight - 1; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            if (path[j] > 0) {
                test[i][j] = 1;
                path[j] -= 1;
            }
        }
    }

    // [2] ���̰� �� ĭ ���̳��� ������ ����ȣ�� ���س��´�.
    // �̿� ����, ���ΰ� ���ʿ��� �� ��ġ���� �ö���� ��������, �� ��ġ���� �������� �������� �Ǵ��� �д�.
    for (int i = 0; i < N - 1; i++) {
        if (temp[i] != temp[i+1]) {
            if (temp[i] < temp[i+1] && ((temp[i+1] - temp[i]) == 1)) {
                point.push_back(make_pair(i, ascend));
            }
            else if (temp[i] > temp[i+1] && ((temp[i] - temp[i+1]) == 1)) {
                point.push_back(make_pair(i+1, descend));
            }
            else if (abs(temp[i+1] - temp[i]) > 1) return false; // ������ ĭ�� ��ĭ �Ѵ� ���� ���̳��� ����
            
        }
    }

    // [3] ���� ����ȣ�� ���� ����(10)�� ���ƺ���. ��, �̹� ���� �ִ� ���� �� ������ �����̴�.
    for (int p = 0; p < point.size(); p++) {
        int row = maxHeight - temp[point[p].first] - 1;
        int col = point[p].first;

        // �ش� ��ġ���� �����Ͽ� ���������� �������� ������ ��
        if (point[p].second == descend) {
            for (int xi = 0; xi < X; xi++) {            
                if (col >= N) return false; // �ö󰡴� ���ΰ� ���� �۱��� ������ �� ��� false
                if (test[row][col] != setup) test[row][col] = setup;
                else if (test[row][col] == setup) return false;  // �̹� ��ġ�Ǿ� ���� ���, �ٷ� ���� return
                col += 1;
            }
        }

        // ���������� �ش� ��ġ���� �ö���� ������ �� (= �ش� ��ġ���� X ���̸�ŭ �������� ������ ��)
        if (point[p].second == ascend) {
            for (int xi = X; xi > 0; xi--) {
                if (col < 0) return false; // ���ΰ� ���� �۱��� ������ �� ��� false
                if (test[row][col] != setup) test[row][col] = setup;
                else if (test[row][col] == setup) return false; // �̹� ��ġ�Ǿ� ���� ���, �ٷ� ���� return
                col -= 1;
            }
        }
    }

    // [4] test�� ������ ��Ȳ�� ����, ���� �ʴ� ���̽��� ��󳽴�.
    for (int i = 0; i < maxHeight; i++) {
        for (int j = 0; j < N; j++) {
            // ��ġ�� ������ �� �ٷ� �ؿ� �� ���ΰ� ���� �����̴�.
            if (test[i][j] == setup && i + 1 < maxHeight) {
                if (test[i + 1][j] == setup) return false;
            }
        }
    }

    return true;
}

void initial_test() {
    for (int i = maxHeight - 1; i >= 0; i--) {
        for (int j = 0; j < N; j++) 
            test[i][j] = 0;       
    }
}

int main() {

    bool flag;
    vector<int> path;
    int OKcnt = 0;

    scanf("%d", &T);

    for (int t = 0; t < T; t++) {
        scanf("%d %d", &N, &X);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                scanf("%d", &arr[i][j]);           
        }
        // ���� ���� ���캸��
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) 
                path.push_back(arr[i][j]);

            flag = solve(path);
            if (flag) OKcnt++;
            path.clear();

            initial_test(); // test �迭 �ʱ�ȭ
        }

        // ���� ���� ���캸��
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) 
                path.push_back(arr[j][i]);
            
            flag = solve(path);
            if (flag) OKcnt++;
            path.clear();

            initial_test(); // test �迭 �ʱ�ȭ
        }

        printf("#%d %d\n", t + 1, OKcnt);
        OKcnt = 0;
    }
    return 0;
}