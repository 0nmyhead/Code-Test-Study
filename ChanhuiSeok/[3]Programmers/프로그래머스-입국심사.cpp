#define _CRT_SECURE_NO_WARNINGS

#define pb push_back

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;
int sizes, M;

bool valid(int x, vector<int> budgets) {
    int sum = 0;
    for (int i = 0; i < budgets.size(); i++) {
        if (budgets[i] <= x)
            sum += budgets[i];
        else
            sum += x;
    }
    if (sum <= M)
        return true;
    else
        return false;
}

int main() {
    
    long long answer = 0;
    int n = 6;
    vector<int> times = { 7,10 };

    sort(times.begin(), times.end());

    // ó���ؾ� �ϴ� �۾��� ���� -> ����� �� -> n

    long long left, right;
    left = 1;
    right = times[times.size() - 1] * n;
    // 1�к���, ���� ���� �ɻ���� ��� ����� �˻��ϴµ� �ɸ��� �ð��� �� ��������
    // �̺� Ž�� ����

    while (left <= right) {

        long long sum = 0;
        long long k = (left + right) / 2;

        for (int i = 0; i < times.size(); i++) {
            sum += k / times[i];
            // k ��ŭ�� �ð����� �ɻ�� i�� �˻��� �� �ִ� ����� �� -> k / times[i]
        }

        // �� ����, �˻��ؾ� �ϴ� ����� �� n���� �۴ٸ�
        // left ���� k + 1�� �ٲ۴�.
        if (sum < n) {
            left = k + 1;
        }
        else {
            answer = k;
            right = k - 1;
        }
    }
    


    return 0;
}