#include <iostream>
#include <queue>
#include <functional>
#include <algorithm>

#define MAX 300001
using namespace std;

bool jcmp (pair<int, int> j1, pair<int, int> j2) {
	if (j1.first == j2.first) return (j1.second > j2.second); // 무게가 같으면 가치가 더 높은 주얼이 좋다
	else return (j1.first < j2.first); // 무게가 더 가벼운 쪽이 우선시 된다.
}

bool desc(int a, int b) {
	return a > b;
}

pair<int, int> jewels[MAX];
int bags[MAX];

int main() {
	int n, k; // n은 보석의 갯수, k는 가방의 갯수
	long long sum = 0;

	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int m, v;
		cin >> m >> v;
		pair<int, int> tmp = make_pair(m, v);
		jewels[i] = tmp;
	}
	for (int i = 0; i < k; i++) {
		int c;
		cin >> c;
		bags[i] = c;
	}

	sort(bags, bags+k); // 무게를 기준으로 오름차
	sort(jewels, jewels + n, jcmp); // 무게를 기준으로 오름차 

	priority_queue<int, vector<int>, less<int>> pq; // max heap
	int jdx = 0; // 초기 보석 탐색
	for (int i = 0; i < k; i++) { //가방이 먼저 가장 이상적인 보석을 고른다
		while(jdx < n && bags[i] >= jewels[jdx].first) { // 비교를 하면서 무게 조건을 만족하는 경우에만
			pq.push(jewels[jdx].second); // 우선순위 큐에 담는다.
			jdx++; // 주얼을 담았으면 다음 원소를 순회한다.
		} //* 이미 한바퀴 다 돌았으면 pq의 내용물만을 pop하면 된다.
		if (!pq.empty()) { // 되는 원소들을 다 담았으면
			sum += (long long)pq.top(); // 가장 이상적인 값을 더한다.
			pq.pop(); // 더한 원소를 큐에서 제거한다.
		}
	}
	cout << sum;
	return 0;
}