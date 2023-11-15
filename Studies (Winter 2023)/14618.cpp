#include <iostream>
#include <queue>
#include <vector>
#include <limits.h>

using namespace std;

int graph[5001][5001]; // 인접 행렬 방법으로 구현
priority_queue<int> current_breadth;

int houseA[5000]; // A형집 인 정점의 정보
int houseB[5000]; // B형집 인 정점의 정보
int minimum_route[5001]; // 시작 정점부터 각 정점까지의 최소 거리를 저장하는 배열

char nearest_house_type = 'N';
int nearest_distance = INT_MAX;

int N, M, J, K;

int main() {
	
	cin >> N >> M; // 집의 수, 연결하는 도로수
	cin >> J; // 진서네 집의 정점
	cin >> K; // 총깡총깡 , 짝폴짝폴, A형 집, B형집의 수
	
	for (int i = 0; i < K; i++) {
		cin >> houseA[i];
	}
	for (int i = 0; i < K; i++) {
		cin >> houseB[i];
	}
	for (int i = 0; i < M; i++) {
		int src, dst; int distance;
		cin >> src >> dst >> distance;
		graph[src][dst] = distance;
		graph[dst][src] = distance;
	}
	current_breadth.push(J); 
	// 입력

	for (int i = 1; i < N+1; i++) {
		if (i == J) continue;
		minimum_route[i] = INT_MAX;
	} // 자기 자신을 제외한 모든 정점으로의 길을 최대값으로 초기화

	while (!current_breadth.empty()) {
		int vertex_now = current_breadth.top();
		current_breadth.pop();
		for (int dst = 1; dst < 5001; dst++) {
			if (graph[vertex_now][dst] != 0) { // 간선이 있으면
				if (minimum_route[dst] > minimum_route[vertex_now] + graph[vertex_now][dst]) {
					minimum_route[dst] = minimum_route[vertex_now] + graph[vertex_now][dst]; // 최단경로임을 확인 하고 갱신
					current_breadth.push(dst); // 최단경로 일때만 다음 BFS에서 수행
				} 
			}
		}
	} // 다익스트라


	for (int i = 0; i < K; i++) {
		int candidate = houseA[i];
		if (nearest_distance >= minimum_route[candidate]) {
			nearest_distance = minimum_route[candidate];
			nearest_house_type = 'A';
		}
	} // A형 집에 대한 거리 체크
	for (int i = 0; i < K; i++) {
		int candidate = houseB[i];
		if (nearest_distance > minimum_route[candidate]){
			nearest_distance = minimum_route[candidate];
			nearest_house_type = 'B';
		}
	} // B형 집에 대한 거리 체크 

	if (nearest_distance == INT_MAX) {
		cout << -1 << "\n";
	}
	else {
		cout << nearest_house_type << "\n";
		cout << nearest_distance << "\n";
	}

	return 0;
}