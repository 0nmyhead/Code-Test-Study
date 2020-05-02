#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int minStep = 1000001;
bool meetFlag = false;
map<string, int> visit;

// �� ���ڿ����� �ٸ� ���ĺ��� ������ ���� �Լ�
int compString(string a, string b) {
    int count = 0, jIdx = 0;
    vector<char> aStr;
    vector<char> bStr;

    for (int i = 0; i < a.size(); i++) aStr.push_back(a[i]);
    for (int i = 0; i < b.size(); i++) bStr.push_back(b[i]);
    for (int i = 0; i < aStr.size(); i++) {
        jIdx = 0;
        for (int j = jIdx; j < bStr.size(); j++) {
            if (aStr[i] == bStr[j]) { // ������, bStr[i] erase
                bStr.erase(bStr.begin() + j);
                break;
            }
        }
    }
    return bStr.size();
}

void dfs(string begin, string target, int step, vector<string>words) {

    vector<pair<int, string>> words_comp;

    // target�� ������ ���
    if (begin == target) {
        if (minStep >= step) {
            minStep = step;
            meetFlag = true;
        }
        return;
    }

    //1. begin�� words����� ���� ���� ���� ���
    for (int i = 0; i < words.size(); i++) {
        int comps = 0;
        if (visit[words[i]] != 1)
            comps = compString(begin, words[i]);
        if (comps != 0)
            words_comp.push_back({ comps, words[i] });
    }

    // 2. words_comp�� �������� ����
    sort(words_comp.begin(), words_comp.end());

    // 3. �տ������� ���ʴ�� ������ ���鼭 �ּ� step �� ã��
    bool iterFlag = false;
    for (int i = 0; i < words_comp.size(); i++) {

        if (words_comp[0].first != 1) break; // ù ��°�� 1 ���̰� �ȳ��� �� �ʿ� X
        if (words_comp[i].first == 1) {
            visit[words_comp[i].second] = 1;
            dfs(words_comp[i].second, target, step + 1, words);
            visit[words_comp[i].second] = 0;
        }
    }
}


int solution(string begin, string target, vector<string> words) {
    bool isExistTarget = false;

    for (int i = 0; i < words.size(); i++) {
        if (words[i] == target) {
            isExistTarget = true;
            break;
        }
    }

    if (isExistTarget == false) return 0;
    
    dfs(begin, target, 0, words);

    if (!meetFlag) return 0;   
    if (minStep != -1) return minStep;

}