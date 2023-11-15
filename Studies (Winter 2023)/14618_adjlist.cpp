#include <iostream>
#include <queue>
#include <vector>
#include <limits.h>

#define TYPE_A 1
#define TYPE_B 2

using namespace std;

vector<pair<int,int>> graph[5001]; // ���� ����Ʈ ������� ����
priority_queue<int> current_breadth;
int house_type[5001]; // ������ ���� ����
int minimum_route[5001]; // ���� �������� �� ���������� �ּ� �Ÿ��� �����ϴ� �迭

char nearest_house_type = 'N'; // �ѱ��ѱ��� ������ ���� ����
int nearest_distance = INT_MAX; // �ѱ��ѱ��� ������ �������� �ִܰŸ�

int N, M, J, K;

int main() {

	cin >> N >> M; // ���� ��, �����ϴ� ���μ�
	cin >> J; // ������ ���� ����
	cin >> K; // �ѱ��ѱ� , ¦��¦��, A�� ��, B������ ��

	for (int i = 0; i < K; i++) { // ���� AŸ�� ���� ���� ������ ����
		int a_idx;
		cin >> a_idx;
		house_type[a_idx] = TYPE_A;
	}
	for (int i = 0; i < K; i++) { // �״��� BŸ�� ���� ���� ������ ����
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
	// 1. �ʿ��� ���� �Է�

	for (int i = 1; i < N + 1; i++) {
		if (i == J) continue;
		minimum_route[i] = INT_MAX;
	} 
	//2. �ڱ� �ڽ��� ������ ��� ���������� �ּҰ�θ� �ִ밪���� �ʱ�ȭ

	current_breadth.push(J);// �ʱ⿡�� ������ ���� ��������� ��´�
	while (!current_breadth.empty()) {
		int vertex_now = current_breadth.top();
		current_breadth.pop();
		for (pair<int, int>& p : graph[vertex_now]) { // ����� �����鿡 ���� BFS�� ����
			int vertex_next = p.first;
			int weight = p.second;
			if (minimum_route[vertex_next] > minimum_route[vertex_now] + weight) { // �ִ� ��ΰ� ���Ű����ϴٸ�
				minimum_route[vertex_next] = minimum_route[vertex_now] + weight;
				current_breadth.push(vertex_next); // �ִܰ�θ� �����ϰ� ť�� ����ִ´�.
			}
		}
	} 
	// 3. ���ͽ�Ʈ�� �˰����� ���� ������ -> ��� �ٸ� ���������� ���� �ѹ��� ����  

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
	//4. A��, B���� �������� �ִܰ�� ���̵��� ��, ���� ���� ��θ� ���� ������ ã�´�.

	if (nearest_distance == INT_MAX) {
		cout << -1 << "\n";
	}
	else {
		cout << nearest_house_type << "\n";
		cout << nearest_distance << "\n";
	}
	// 5. ���� ���
	return 0;
}