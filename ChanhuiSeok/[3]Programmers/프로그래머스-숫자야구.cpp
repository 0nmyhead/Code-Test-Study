#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> baseball) {
    int strike = 0;
    int ball = 0;
    int find = 1;
    int findSuccess = 0;
    int ballCheck = 0;

    for (int num = 123; num <= 987; num++) {

        find = 1;

        if (to_string(num)[0] == '0' ||
            to_string(num)[1] == '0' ||
            to_string(num)[2] == '0')
            continue;

        if (to_string(num)[0] == to_string(num)[1] ||
            to_string(num)[1] == to_string(num)[2] ||
            to_string(num)[0] == to_string(num)[2])
            continue;


        // �ݺ��� ���� num�̶� ���Ϳ� �ִ� ������ �ڸ��� ��
        for (int i = 0; i < baseball.size(); i++) {
            strike = 0; ball = 0;

            /* ���� �� ���� �ϳ��� �ϴ� ��*/
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    if (to_string(num)[m] == to_string(baseball[i][0])[n] && m == n)
                    {
                        strike++; // ��Ʈ����ũ
                        continue;
                    }
                    // ��Ʈ����ũ�� �ƴϿ��ٸ�, �� üũ
                    if (to_string(num)[m] == to_string(baseball[i][0])[n] && m != n)
                    {
                        ball++; // ball
                    }
                }
            }

            // ���� ��Ʈ����ũ�� �� ���� ��ġ���� �ʾ����� ���� num���� �̵�
            if (baseball[i][1] != strike
                || baseball[i][2] != ball) {
                find = 0;
                break;
            }
        }
        // ���Ϳ� �ִ� ��� ���Ұ� ��ġ���� ���
        if (find == 1) {
            findSuccess++;
        }
    }

    return findSuccess;
}