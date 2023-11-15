#include <iostream>
#include <queue>
#include <vector>
#include <limits.h>

using namespace std;

int graph[5001][5001]; // ���� ��� ������� ����
priority_queue<int> current_breadth;

int houseA[5000]; // A���� �� ������ ����
int houseB[5000]; // B���� �� ������ ����
int minimum_route[5001]; // ���� �������� �� ���������� �ּ� �Ÿ��� �����ϴ� �迭

char nearest_house_type = 'N';
int nearest_distance = INT_MAX;

int N, M, J, K;

int main() {
	
	cin >> N >> M; // ���� ��, �����ϴ� ���μ�
	cin >> J; // ������ ���� ����
	cin >> K; // �ѱ��ѱ� , ¦��¦��, A�� ��, B������ ��
	
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
	// �Է�

	for (int i = 1; i < N+1; i++) {
		if (i == J) continue;
		minimum_route[i] = INT_MAX;
	} // �ڱ� �ڽ��� ������ ��� ���������� ���� �ִ밪���� �ʱ�ȭ

	while (!current_breadth.empty()) {
		int vertex_now = current_breadth.top();
		current_breadth.pop();
		for (int dst = 1; dst < 5001; dst++) {
			if (graph[vertex_now][dst] != 0) { // ������ ������
				if (minimum_route[dst] > minimum_route[vertex_now] + graph[vertex_now][dst]) {
					minimum_route[dst] = minimum_route[vertex_now] + graph[vertex_now][dst]; // �ִܰ������ Ȯ�� �ϰ� ����
					current_breadth.push(dst); // �ִܰ�� �϶��� ���� BFS���� ����
				} 
			}
		}
	} // ���ͽ�Ʈ��


	for (int i = 0; i < K; i++) {
		int candidate = houseA[i];
		if (nearest_distance >= minimum_route[candidate]) {
			nearest_distance = minimum_route[candidate];
			nearest_house_type = 'A';
		}
	} // A�� ���� ���� �Ÿ� üũ
	for (int i = 0; i < K; i++) {
		int candidate = houseB[i];
		if (nearest_distance > minimum_route[candidate]){
			nearest_distance = minimum_route[candidate];
			nearest_house_type = 'B';
		}
	} // B�� ���� ���� �Ÿ� üũ 

	if (nearest_distance == INT_MAX) {
		cout << -1 << "\n";
	}
	else {
		cout << nearest_house_type << "\n";
		cout << nearest_distance << "\n";
	}

	return 0;
}