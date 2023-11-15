#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <unordered_map>

using namespace std;

unordered_map<string, int> map; // ���ڿ��� ������ ����Ʈ �̸��� �ش��ϴ� �ε����� �ٲ۴�. 
vector<int> graph[1250]; // 1���� DFS�� �� �׷��� 
vector<int> graphT[1250]; // 2���� DFS�� �� ��ġ�׷���
vector<int> graphT_without_SCC[1250]; //SCC�� ������ ���ŵ� ��ġ�׷���
bool visited[1250]{ false }; // ù DFS������ �湮����
bool visitedT[1250]{ false }; // �ι��� DFS������ �湮����
bool visitedT_without_SCC[1250]{ false }; // SCC�� ������ ���ŵ� ��ġ�׷����� �湮����

long long scores[1250]; // ������ ���� ����
int scc_gids[1250]; // �������� �ҼӵǾ��ִ� scc�׷��� ������� �����ϴ� �迭

stack<int> dfs_order;
int vertexNo = 0; // ����Ʈ �̸��� ���� ���� ��ȣ

int getVertexNo(unordered_map<string, int>& map, string key); // ��Ʈ������ �� ����Ʈ �̸��� ���������� �ٲ���
void DFSfirst(int idx, stack<int>& order); // �׷����� DFS�����ν� �������� ������ ������ ���ؿ� ����
void DFSSecond(int startVertex, int curVertex); // ���������������� ���ÿ��� ���������� ������� ��ġ�׷����� DFS, SCC�� Ȯ�� 
void scoring(int vertexNo); // ��͸� ���鼭 top-down ������ score���� ����Ѵ�. 

int main() {
	int N; cin >> N;

	for (int i = 0; i < N; i++) {
		int dstVertexNo, srcVertexNo; // ��ȯ�� �������� ������� ������ȣ
		string dst; int edges;
		cin >> dst >> edges;
		dstVertexNo = getVertexNo(map, dst); // ��Ʈ���� Ű������ ������ȣ�� �Ҵ��ϰ� ����
		for (int i = 0; i < edges; i++) {
			string src;// ���� ����
			cin >> src;
			srcVertexNo = getVertexNo(map, src);
			graph[srcVertexNo].push_back(dstVertexNo);
			graphT[dstVertexNo].push_back(srcVertexNo);
		}
	}
	// �׷����� ��ġ�׷��� ���� ��

	int vertices = map.size(); //�������� �� ������ ���Ѵ�
	for (int i = 0; i < vertices; i++) { // �������� �⺻ ������ 1�� �ʱ�ȭ
		scores[i] = 1;
	}

	for (int i = 0; i < vertices; i++) {
		DFSfirst(i, dfs_order); // ��� ������ ���ؼ� DFS�� ����. 
	}

	while (!dfs_order.empty()) {
		int scc_leader = dfs_order.top(); // �ڱ��ڽ��� scc�� ������� �̷��� �׷��� ������� ��������
		dfs_order.pop();
		DFSSecond(scc_leader, scc_leader); 
	}
	// ��ġ�׷����� ���ؼ� �ѹ� �� DFS�� �����ؼ� scc���� �����Ѵ�. 

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < graph[i].size(); j++) {
			int dstVertex = graph[i][j];
			if (scc_gids[i] != scc_gids[dstVertex]) { // ���� scc �׷� �ȿ� ���� ����
				graphT_without_SCC[dstVertex].push_back(i); //SCC�� ���� ��ġ�׷����� �����Ѵ�.
			}
		}
	}
	// scc�� �������� �ʴ� �׷����� �����. 

	for (int i = 0; i < vertices; i++) {
		scoring(i);
	}
	// ��ġ �׷����� ��ȸ�ϸ鼭 �� ������ ����س�����. (DP ����)

	string target; // ������ ã�����ϴ� Ÿ��
	cin >> target;
	int targetNo = map[target]; // Ÿ�� ���ý��� ��ȣ

	cout << scores[targetNo]; // �̸� ����ص� ����� ����Ѵ�. 

	return 0;
}


int getVertexNo(unordered_map<string, int>& map, string key) {
	// ��Ʈ������ �� ����Ʈ �̸��� ���������� �ٲ���
	if (map.find(key) == map.end()) {
		map[key] = vertexNo++;
	}
	int res = map[key];
	return res;
}

void DFSfirst(int vertexNo, stack<int>& order) {
	if (!visited[vertexNo]) {
		visited[vertexNo] = true;
		for (auto a : graph[vertexNo]) {
			DFSfirst(a, order);
		}
		order.push(vertexNo); // ���� ���� ������ ���ÿ� ���� �ִ´�
	}
}

void DFSSecond(int startVertex, int curVertex) {
	if (!visitedT[curVertex]) {
		visitedT[curVertex] = true;
		for (auto a : graphT[curVertex]) {
			DFSSecond(startVertex, a);
		}
		scc_gids[curVertex] = startVertex; // ��ġ�׷����� ��ȸ �������� ������ �ȴٸ� 
	}
}

void scoring(int vertexNo) {
	vector<int> adjVertice; 
	if (!visitedT_without_SCC[vertexNo]) { 
		visitedT_without_SCC[vertexNo] = true;
		for (auto a : graphT_without_SCC[vertexNo]) {
			adjVertice.push_back(a);// ����Ǿ��ִ� �������� ����Ѵ�. 
			scoring(a);
		}
		long long currentScore = 0;
		for (auto a : adjVertice) { // ����� �������� ������ �����Ѵ�.
			currentScore += scores[a];
		}
		scores[vertexNo] += currentScore; //  scores �迭�� ������ ����Ѵ�.
	}
} // ������ ����: �⺻���� + ���� ����� ���� �������� ������ ��, ���� �Ųٷ� �����ϸ� �̸� ������·� Ǯ�� ����