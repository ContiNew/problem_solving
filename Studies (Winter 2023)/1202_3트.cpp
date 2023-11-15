#include <iostream>
#include <queue>
#include <functional>
#include <algorithm>

#define MAX 300001
using namespace std;

bool jcmp (pair<int, int> j1, pair<int, int> j2) {
	if (j1.first == j2.first) return (j1.second > j2.second); // ���԰� ������ ��ġ�� �� ���� �־��� ����
	else return (j1.first < j2.first); // ���԰� �� ������ ���� �켱�� �ȴ�.
}

bool desc(int a, int b) {
	return a > b;
}

pair<int, int> jewels[MAX];
int bags[MAX];

int main() {
	int n, k; // n�� ������ ����, k�� ������ ����
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

	sort(bags, bags+k); // ���Ը� �������� ������
	sort(jewels, jewels + n, jcmp); // ���Ը� �������� ������ 

	priority_queue<int, vector<int>, less<int>> pq; // max heap
	int jdx = 0; // �ʱ� ���� Ž��
	for (int i = 0; i < k; i++) { //������ ���� ���� �̻����� ������ ����
		while(jdx < n && bags[i] >= jewels[jdx].first) { // �񱳸� �ϸ鼭 ���� ������ �����ϴ� ��쿡��
			pq.push(jewels[jdx].second); // �켱���� ť�� ��´�.
			jdx++; // �־��� ������� ���� ���Ҹ� ��ȸ�Ѵ�.
		} //* �̹� �ѹ��� �� �������� pq�� ���빰���� pop�ϸ� �ȴ�.
		if (!pq.empty()) { // �Ǵ� ���ҵ��� �� �������
			sum += (long long)pq.top(); // ���� �̻����� ���� ���Ѵ�.
			pq.pop(); // ���� ���Ҹ� ť���� �����Ѵ�.
		}
	}
	cout << sum;
	return 0;
}