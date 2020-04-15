#include <string>
#include <vector>

using namespace std;

vector<int> numbers;
int temp_target;
int answer;

void dfs(int depth, int sum, int cnt, vector<int> numbers, int target) {

    // �ȿ� �ִ� ���� ������ �������� Ȯ��
    if (depth >= numbers.size()) {
        if (sum == target) {
            answer++;
        }
        return;
    }

    dfs(depth + 1, sum + numbers[cnt], cnt + 1, numbers, target);
    dfs(depth + 1, sum - numbers[cnt], cnt + 1, numbers, target);

}

int solution(vector<int> numbers, int target) {

    int depth = 0;
    dfs(depth, 0, 0, numbers, target);

    return answer;
}