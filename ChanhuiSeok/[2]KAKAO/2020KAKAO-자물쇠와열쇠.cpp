#include <string>
#include <vector>

using namespace std;

int arr[100][100];

// �ð� �������� ȸ��
vector<vector<int>> clockwise(vector<vector<int>> arr) {
    int rowSize = arr.size();
    vector<vector<int>> copies;
    vector<int> temp;

    for (int i = 0; i < arr.size(); i++) {
        for (int j = arr.size() - 1; j >= 0; j--) {
            temp.push_back(arr[j][i]);
        }
        copies.push_back(temp);
        temp.clear();
    }
    return copies;
}

// ��� ��ġ�� lock�� ��� 1�� �� ���� ���� �� �� �ִ�
bool isAllOne(int startRow, int startCol, int lockSize) {
    for (int i = startRow; i < startRow + lockSize; i++) {
        for (int j = startCol; j < startCol + lockSize; j++) {
            if (arr[i][j] != 1) {
                return false;
            }
        }
    }
    return true;
}

bool isPossible(vector<vector<int>> lock, vector<vector<int>> key, int keySize, int lockSize) {

    int lock_startRow = lockSize - 1;
    int lock_startCol = lockSize - 1;

    // ������� lock �� ��ġ�� ���´�.
    for (int i = lock_startRow; i < lock_startRow + lockSize; i++) {
        for (int j = lock_startCol; j < lock_startCol + lockSize; j++) {
            arr[i][j] = lock[i - lock_startRow][j - lock_startCol];
        }
    }

    // �ϳ��ϳ� ���캻��.
    for (int i = 0; i < lockSize * 2; i++) {
        for (int j = 0; j < lockSize * 2; j++) {

            for (int k = 0; k < key.size(); k++) {
                for (int m = 0; m < key.size(); m++) {
                    arr[i + k][j + m] += key[k][m];
                }
            }

            // lock�� ��� 1�� ���
            if (isAllOne(lock_startRow, lock_startCol, lockSize)) {
                return true;
            }

            for (int k = 0; k < key.size(); k++) {
                for (int m = 0; m < key.size(); m++) {
                    arr[i + k][j + m] -= key[k][m];
                }
            }
        }
    }
    return false;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    bool answer;

    for (int i = 0; i < 4; i++) {
        answer = isPossible(lock, key, key.size(), lock.size());
        if (answer) {
            return true;
        }

        key = clockwise(key);
    }

    return false;
}