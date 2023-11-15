#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct truth_table {
	vector<vector<int>> table;
	truth_table(int n) {
		table.resize(n+1);
	}
};

vector<pair<int, int>> bit_sums;

int main() {
	int N, M;
	cin >> N >> M;
	for (int c = 0; c < M; c++) {
		int i, j;
		cin >> i >> j;
		bit_sums.push_back({ i,j });
	}
	truth_table t(N);
	pair <int, int> one_of_sum = bit_sums.front();

	
	
	
}

