#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

bool visit[1001];
vector<int> edge[1001];

void dfs(int n) {
	if (visit[n])return;
	cout << n << " ";
	visit[n] = true;
	for (int i = 0; i < edge[n].size(); i++)
		if (!visit[edge[n][i]])dfs(edge[n][i]);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int N, M, V; cin >> N >> M >> V;
	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	for (int i = 1; i <= N; i++) {
		sort(edge[i].begin(), edge[i].end());
	}
	dfs(V); cout << "\n";

	queue<int>q;
	q.push(V);
	visit[V] = false;
	while (!q.empty()) {
		int s = q.front();
		cout << s << " ";
		q.pop();
		for (int i = 0; i < edge[s].size(); i++)
			if (visit[edge[s][i]] == true) {
				visit[edge[s][i]] = false;
				q.push(edge[s][i]);
			}
	}
	cout << "\n";
}