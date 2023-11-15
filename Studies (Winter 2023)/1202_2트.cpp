#include <iostream>
#include <queue>
#include <functional>
#include <algorithm>
#define ll long long
#define MAX 300001

using namespace std;

pair<ll, ll> jewels[MAX];
ll bags[MAX];

bool jcmp(pair<ll, ll> a, pair<ll, ll> b) {
	if (a.first == b.first) return (a.second > b.second); 
	else return (a.first < b.first); 
}

int main() {
	int n, k; // 보석의 수와 가방의 수
	priority_queue<ll, vector<ll>, less<ll>> pq;
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int m, v;
		cin >> m >> v;
		jewels[i] = make_pair(m, v);
	}
	for (int i = 0; i < k; i++) {
		int c;
		cin >> c;
		bags[i] = c;
	}
	sort(jewels, jewels + n, jcmp);
	sort(bags, bags + k);

	int idx = 0;
	for (int i = 0; i < k; i++) {
		while (idx < n && bags[i] >= jewels[idx].first) {
			pq.push(jewels[idx].second);
			idx++;
		}
		
	}
	
	
}