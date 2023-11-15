#include <iostream>
#include <algorithm>
#include <limits.h>

using namespace std;

#define INF INT_MAX
int N, M; // 도시의 수, 버스의 수
int graph[1001][1001];

int main() {
	cin >> N >> M;
	for (int i = 1; i <  N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			if (i == j) graph[i][j] = 0;
			else graph[i][j] = INF;
		}
	}
	for (int i = 0; i < M; i++) {
		int src, dst, cost;
		cin >> src >> dst >> cost;
		if (cost > graph[src][dst])continue;
		graph[src][dst] = cost;
	}
	
	for (int k = 1; k < N + 1; k++) {
		for (int i = 1; i < N + 1; i++) {
			for (int j = 1; j < N + 1; j++) {
				if (graph[i][k] == INF || graph[k][j] == INF) {
					continue;
				}
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
			}
		}
	}

	int src, dst;
	cin >> src >> dst;
	cout << graph[src][dst] << "\n";

	return 0;
	
}