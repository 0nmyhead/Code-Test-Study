#include <string>
#include <vector>
#include <algorithm>

using namespace std;
int sizes;

/* �̺� Ž������ Ư�� ���ǿ� ���� ������ ���ϱ� */
/* �ܼ��� �迭���� Ư�� ���Ҹ� ã�� ���� �ƴϰ�, Ư�� ������ �� �ִ� Ȥ�� �ּҸ� */
/* ���ϴ� ������ ���� �� �ִ�. */

int solution(vector<int> budgets, int M) {

    sort(budgets.begin(), budgets.end()); // �������� ����

    int average = M / sizes;
    // ������ average�� ������ �Ǿ� �ִ�.
    // valid(x)�� x<=ANSWER �� ���� true ��, x>ANSWER�� �� false�̴�.

    // average���ٴ� ũ���� ���� ���� ���Ҹ� ã�´�...
    int left = 0, right = budgets[budgets.size() - 1];
    int answer = 0;

    while (left <= right) {
        int num = 0;
        int k = (left + right) / 2; // �ʱ� - 75

        for (auto i : budgets) {
            if (k > i) { // budgets�� ��Ұ� k(����)���� ������, ������� �� ��Ҹ� ���Ѵ�.
                num += i;
            }
            else {
                num += k; // ���Ѻ��� ũ��, k���� ���Ѵ�.
            }
        }

        // �� ���Ѱ� num(��, ã���� �ϴ� ��)�� M���� ������ ū�� �ľ��ؾ� �Ѵ�.
        if (num > M) { // M���� ������, ������ ���� �ʿ䰡 �ִ�.
            right = k - 1;
        }
        else {
            left = k + 1; // ������ �ø��� ����
            answer = k; // �� �ø��� �� ���ɼ� �ִ� ���
        }
    }

    return answer;
}