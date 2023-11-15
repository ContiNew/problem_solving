#include <iostream>
#include <queue>
#include <vector>
#include <limits.h>

#define TYPE_A 1
#define TYPE_B 2

using namespace std;

vector<pair<int,int>> graph[5001]; // 인접 리스트 방법으로 구현
priority_queue<int> current_breadth;
int house_type[5001]; // 정점의 종류 정보
int minimum_route[5001]; // 시작 정점부터 각 정점까지의 최소 거리를 저장하는 배열

char nearest_house_type = 'N'; // 총깡총깡이 들어가야할 집의 종류
int nearest_distance = INT_MAX; // 총깡총깡이 들어가야할 집까지의 최단거리

int N, M, J, K;

int main() {

	cin >> N >> M; // 집의 수, 연결하는 도로수
	cin >> J; // 진서네 집의 정점
	cin >> K; // 총깡총깡 , 짝폴짝폴, A형 집, B형집의 수

	for (int i = 0; i < K; i++) { // 먼저 A타입 집에 대한 정보를 저장
		int a_idx;
		cin >> a_idx;
		house_type[a_idx] = TYPE_A;
	}
	for (int i = 0; i < K; i++) { // 그다음 B타입 집에 대한 정보를 저장
		int b_idx;
		cin >> b_idx;
		house_type[b_idx] = TYPE_B;
	}
	for (int i = 0; i < M; i++) {
		int src, dst; int distance;
		cin >> src >> dst >> distance;
		graph[src].push_back(make_pair(dst, distance));
		graph[dst].push_back(make_pair(src, distance));
	}
	// 1. 필요한 정보 입력

	for (int i = 1; i < N + 1; i++) {
		if (i == J) continue;
		minimum_route[i] = INT_MAX;
	} 
	//2. 자기 자신을 제외한 모든 정점으로의 최소경로를 최대값으로 초기화

	current_breadth.push(J);// 초기에는 진서네 집을 출발점으로 잡는다
	while (!current_breadth.empty()) {
		int vertex_now = current_breadth.top();
		current_breadth.pop();
		for (pair<int, int>& p : graph[vertex_now]) { // 연결된 간선들에 대해 BFS를 수행
			int vertex_next = p.first;
			int weight = p.second;
			if (minimum_route[vertex_next] > minimum_route[vertex_now] + weight) { // 최단 경로가 갱신가능하다면
				minimum_route[vertex_next] = minimum_route[vertex_now] + weight;
				current_breadth.push(vertex_next); // 최단경로를 갱신하고 큐에 집어넣는다.
			}
		}
	} 
	// 3. 다익스트라 알고리즘을 통해 진서네 -> 모든 다른 정점까지의 길을 한번에 구함  

	for (int i = 1; i < 5001; i++) {
		if (house_type[i] == TYPE_A) {
			if (nearest_distance >= minimum_route[i]) {
				nearest_distance = minimum_route[i];
				nearest_house_type = 'A';
			}
		}
		else if (house_type[i] == TYPE_B) {
			if (nearest_distance > minimum_route[i]) {
				nearest_distance = minimum_route[i];
				nearest_house_type = 'B';
			}
		}
	}
	//4. A형, B형인 정점들의 최단경로 길이들을 비교, 가장 작은 경로를 가진 정점을 찾는다.

	if (nearest_distance == INT_MAX) {
		cout << -1 << "\n";
	}
	else {
		cout << nearest_house_type << "\n";
		cout << nearest_distance << "\n";
	}
	// 5. 정답 출력
	return 0;
}