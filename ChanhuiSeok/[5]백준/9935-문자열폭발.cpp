#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

bool flag;

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	string input, explode, ans;

	cin >> input;
	cin >> explode;

	int inputSize = input.size();
	int explodeSize = explode.size();

	for (int i = 0; i < input.size(); i++) {
		ans += input[i];

		if (input[i] == explode[explodeSize - 1]
			&& i >= explodeSize - 1) {
			flag = true;
			for (int j = 1; j < explodeSize; j++) {

				// �ٸ��� �ϳ��� �־��� ���
				if (ans[ans.size() - 1 - j] != explode[explodeSize - 1 - j]) {
					flag = false;
					break;
				}
			}
			if (flag) {
				for (int k = 0; k < explodeSize; k++) {
					ans.pop_back();
				}
			}
		}
	}

	if (ans != "")
		cout << ans;
	else
		cout << "FRULA";
}