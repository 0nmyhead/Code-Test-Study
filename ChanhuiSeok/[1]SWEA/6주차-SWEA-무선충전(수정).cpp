#define pb push_back
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct bc {
    int y, x, C, P;
}BC;

bool isPermit(int y, int x) {
    bool flag = true;
    if (y < 1 || y > 10 || x < 1 || x > 10)
        flag = false;
    return flag;
}

pair<int, int> moving(int y, int x, int dir) {
    // �̵� ������ 0:�̵�X, 1:��, 2:��, 3:��, 4:��
    bool flag;
    if (dir == 0) return { y, x };
    if (dir == 1) { // ��
        flag = isPermit(y - 1, x);
        if (flag) return { y - 1,x };
    }
    if (dir == 2) { // ��
        flag = isPermit(y, x + 1);
        if (flag) return { y,x + 1 };
    }
    if (dir == 3) { // ��
        flag = isPermit(y + 1, x);
        if (flag) return { y + 1,x };
    }
    if (dir == 4) { // ��
        flag = isPermit(y, x - 1);
        if (flag) return { y,x - 1 };
    }
}

// Ư�� BC�� �߽��� ��ǥ��, ������� ���� ��ǥ���� �Ÿ��� ���ϴ� �Լ�
int cal_path(int my, int mx, int y, int x) {
    return abs(my - y) + abs(mx - x);
}

bool compare(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second > b.second;
}

int main() {

    int T, input, M, A;
    vector<int> A_path, B_path, A_sum, B_sum;
    pair<int, int>cur_A, cur_B;
    vector<BC> BC_info;

    scanf("%d", &T);
    // ����ڴ� �ʱ� ��ġ(��, 0��)���� ������ �� �ִ�.
    for (int t = 1; t <= T; t++) {
        scanf("%d %d", &M, &A); // M�� �� �̵��ð�, A�� BC�� ����
        for (int i = 0; i < M; i++) {
            scanf("%d", &input);
            A_path.pb(input);
        }
        for (int i = 0; i < M; i++) {
            scanf("%d", &input);
            B_path.pb(input);
        }
        for (int i = 0; i < A; i++) {
            int x, y, c, p; // �� ������ ���� ��ǥ�� (x,y)(�� (��,��)) ���� �Ǿ��ִ�
            scanf("%d %d %d %d", &x, &y, &c, &p);
            BC_info.pb({ y,x,c,p });
        }
        cur_A = { 1, 1 }; // y=1, x=1
        cur_B = { 10, 10 }; // y=10, x=10

        // ����ڸ� �� �̵��ð� ��ŭ ������ ����.
        for (int i = 0; i < M + 1; i++) {
            vector<pair<int, int>> tempA, tempB; // �� pair -> BC�� ��ȣ��, �� ������
            int dirA, dirB;
            if (i == 0) { // �� ó�� ������ ���
                int max_A = 0, max_B = 0;
                for (int j = 0; j < A; j++) {
                    int pathA = cal_path(BC_info[j].y, BC_info[j].x, cur_A.first, cur_A.second);
                    int pathB = cal_path(BC_info[j].y, BC_info[j].x, cur_B.first, cur_B.second);

                    if (pathA <= BC_info[j].C)
                        max_A = max(max_A, BC_info[j].P);
                    if (pathB <= BC_info[j].C)
                        max_B = max(max_B, BC_info[j].P);
                }
                A_sum.push_back(max_A); B_sum.push_back(max_B);
                continue;
            }
            ////////////////////// case 1. A �����
            dirA = A_path[i - 1];
            cur_A = moving(cur_A.first, cur_A.second, dirA);
            for (int i = 0; i < A; i++) {
                int path = cal_path(BC_info[i].y, BC_info[i].x, cur_A.first, cur_A.second);
                if (path <= BC_info[i].C)
                    tempA.push_back({ i, BC_info[i].P });
            }
            sort(tempA.begin(), tempA.end(), compare); // �� �տ� ���� ���� ���� ���� ���Բ� ����

            //////////////////////  case 2. B �����
            dirB = B_path[i - 1];
            cur_B = moving(cur_B.first, cur_B.second, dirB);
            for (int i = 0; i < A; i++) {
                int path = cal_path(BC_info[i].y, BC_info[i].x, cur_B.first, cur_B.second);
                if (path <= BC_info[i].C)
                    tempB.push_back({ i, BC_info[i].P });
            }
            sort(tempB.begin(), tempB.end(), compare);

            // tempA, tempB�� ���� ������ BC���� ����� 1�� �̻� �� ���� ��� ���ǿ� �´� ó��
            if (tempA.size() >= 1 && tempB.size() >= 1) {
                int valA, valB, max_BC_A, max_BC_B, max_tempA, max_tempB;
                max_BC_A = tempA[0].first; // A ������� ���� ������ BC�� ��, �ִ� �������� BC ��ȣ
                max_BC_B = tempB[0].first; // B ������� ���� ������ BC�� ��, �ִ� �������� BC ��ȣ

                // A�� B ������� �ִ� ������ ���� BC��, ���� ��ȣ�� BC�� ���, ���ǿ� ���� �����ؾ� �Ѵ�.
                // ��, �������� ������ ��ȣ�� �ٸ� BC�� ������ ���� �ʿ䰡 ����, �� ���ǹ����� ������ �ȴ�.
                if (max_BC_A == max_BC_B) {
                    max_tempA = tempA[0].second; // A�� �ִ� ������
                    max_tempB = tempB[0].second; // B�� �ִ� ������
                    valA = max_tempA / 2; // �յ�й��Ͽ� ���´�.

                    // BC�� ���� A�� B ��� 1���� ������ �յ� �й�
                    if (tempA.size() == 1 && tempB.size() == 1) {
                        A_sum.push_back(valA); B_sum.push_back(valA);
                    }
                    // A�� ������ BC�� �� �Ѱ� ���̰�, B�� 2�� �̻��� ���
                    else if (tempA.size() == 1) {
                        max_tempA = tempA[0].second; // A�� �ִ� ������
                        max_tempB = tempB[0].second; // B�� �ִ� ������
                        if (max_tempA > max_tempA + tempB[1].second) { // �յ�й��� A�� B�� ���� �� Ŭ ���
                            A_sum.push_back(max_tempA);
                            B_sum.push_back(max_tempA);
                        }
                        else { // A�� �ִ� ������ �ϰ�, B�� �� ���� ���� ������ �� ���� A�� B�� ���� �� Ŭ ���
                            A_sum.push_back(tempA[0].second);
                            B_sum.push_back(tempB[1].second);
                        }
                    }
                    // B�� ������ BC�� �� �Ѱ� ���̰�, A�� 2�� �̻��� ���
                    else if (tempB.size() == 1) {
                        max_tempA = tempA[0].second; // A�� �ִ� ������
                        max_tempB = tempB[0].second; // B�� �ִ� ������
                        if (max_tempA > max_tempB + tempA[1].second) { // �յ�й��� A�� B�� ���� �� Ŭ ���
                            A_sum.push_back(max_tempA);
                            B_sum.push_back(max_tempA);
                        }
                        else { // B�� �ִ� ������ �ϰ�, A�� �� ���� ���� ������ �� ���� A�� B�� ���� �� Ŭ ���
                            A_sum.push_back(tempA[1].second);
                            B_sum.push_back(tempB[0].second);
                        }
                    }
                    // A, B ��� ������ BC�� 2�� �̻��� ���
                    else {
                        max_tempA = tempA[0].second; // A�� �ִ� ������
                        max_tempB = tempB[0].second; // B�� �ִ� ������
                        if (max_tempA > max_tempA + tempB[1].second
                            && max_tempA > max_tempB + tempA[1].second) { // �յ�й��� ���� �� ũ�� �׳� �̰� ����
                            A_sum.push_back(max_tempA);
                            B_sum.push_back(max_tempA);
                        }
                        else if (max_tempA + tempB[1].second > max_tempA
                            && max_tempA + tempB[1].second > max_tempB + tempA[1].second) { // case 2
                            A_sum.push_back(tempA[0].second);
                            B_sum.push_back(tempB[1].second);
                        }
                        else { // case 3
                            A_sum.push_back(tempA[1].second);
                            B_sum.push_back(tempB[0].second);
                        }
                    }
                }
                // ���� BC�� �ƴ϶� ������ ���� �ʿ䰡 �����Ƿ�, �״�� �ִ��� �־��ش�.
                else {
                    A_sum.push_back(tempA[0].second);
                    B_sum.push_back(tempB[0].second);
                }
            }
            // A�� ������ BC�� ������ B�� �־��� ���, B���� �ִ��� �־��ش�.
            else if (tempA.size() == 0 && tempB.size() > 0)
                B_sum.push_back(tempB[0].second);

            // B�� ������ BC�� ������ A�� �־��� ���, A���� �ִ��� �־��ش�.
            else if (tempB.size() == 0 && tempA.size() > 0)
                A_sum.push_back(tempA[0].second);
        }
        int sum_A = 0, sum_B = 0;
        for (int i = 0; i < A_sum.size(); i++) sum_A += A_sum[i];
        for (int i = 0; i < B_sum.size(); i++) sum_B += B_sum[i];
        printf("#%d %d\n", t, sum_A + sum_B);
        A_path.clear(); B_path.clear(), BC_info.clear();
        A_sum.clear(); B_sum.clear();
    }

    return 0;
}