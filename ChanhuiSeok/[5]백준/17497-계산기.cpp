#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <string>
#include <set>
#include <bitset>
#include <map>

using namespace std;

#define PLUS 0
#define MINUS 1
#define MUL 2
#define DIV 3

string oper[4] = { "[+]","[-]","[*]","[/]" };
// ����, ����, ����, ������

long long N;
// N���� �����ؼ� 0�� �� ������ �� ����

vector<string> answer;

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    // N�� �̷�� ��� 1���� 0���� �ٲٴ� ���� ��ǥ
    // �׷��� ������ *2, /2, +2, -2 ���� �͹ۿ� �����Ƿ�
    // ù��° ��Ʈ�� �ι�° ��Ʈ ������ ��ƾ� ��
    while (N) {
        if (N & 1) { // N�� Ȧ���� ���, �������� ������ �� ������ ����������
            answer.push_back(oper[DIV]);
            N *= 2; // �ι� �� ���ƾ�, / �������� ��ǥ�� ���� ����
        }
        else if (N & (1LL << 1)) { // 1�� ��Ʈ(�ι�° ��Ʈ)�� 2�� ����� ����
            answer.push_back(oper[PLUS]);
            N -= 2;
        }
        else {
            answer.push_back(oper[MUL]);
            N /= 2;
        }
    }
    if (answer.size() > 99) cout << -1;
    else {
        cout << answer.size() << '\n';
        for (int i = answer.size() - 1; i >= 0; i--) {
            cout << answer[i] << " ";
        }
    }

}
