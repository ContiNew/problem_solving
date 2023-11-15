#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define VISITED 1
#define NOT_VISITED 0


struct Edge {
    Edge(int src, int dest) {
        this->src = src;
        this->dest = dest;
    }
    int src, dest; // 시작점과 도착점
};

class Graph
{
public:
    vector<vector<int>> edgeList;
    Graph(vector<Edge> const& edges, int n)
    {
        edgeList.resize(n+1); // n개의 공간 만큼 할당한다.
        for (auto& edge : edges)
        {
            edgeList[edge.src].push_back(edge.dest); // 시작 부분에 대해서 끝부분을 push 
            edgeList[edge.dest].push_back(edge.src); // 끝 부분에 대해서 시작부분을 push
        }
    }
    void addEdge(const Edge edge) {
        edgeList[edge.src].push_back(edge.dest); // 시작 부분에 대해서 끝부분을 push 
        edgeList[edge.dest].push_back(edge.src); // 끝 부분에 대해서 시작부분을 push
    }
    void DFS_start(int src) {
        vector<int> visit_check(edgeList.size(), NOT_VISITED);
        DFS(visit_check, src);
        cout << endl;
    }
    void DFS(vector<int>& visit_check, int src) {
        cout << src << " ";
        visit_check[src] = VISITED;
        for (int a : edgeList[src]) {
            if (visit_check[a] == NOT_VISITED) {
                visit_check[a] = VISITED;
                DFS(visit_check, a);
            }
        }
    }
    void BFS(int src) {
        vector<int> visit_check(edgeList.size(), NOT_VISITED);
        queue<int> current_layer;
        current_layer.push(src);
        cout << src << " ";
        visit_check[src] = VISITED;
        while (!current_layer.empty()) {
            int vn = current_layer.front();
            for (int a : edgeList[vn]) {
                if (visit_check[a] == NOT_VISITED) {
                    visit_check[a] = VISITED;
                    cout << a << " ";
                    current_layer.push(a);
                }
            }
            current_layer.pop();
        }
        cout << endl;
    }
};

bool edgecmp(Edge a, Edge b) {
    if (a.src == b.src) {
        return a.dest < b.dest;
    }
    else {
        return a.src < b.src;
    }
}

int main() {
    vector<Edge> el;// 간선을 담은 리스트 
	int vn, en, sn; // 정점의 수, 간선의 수, 탐색을 시작할 정점의 번호
	cin >> vn >> en >> sn; 
    for (int i = 0; i < en; i++) {
        int src, dest;
        cin >> src >> dest;
        if (src > dest) { // 정렬을 위해 순서를 통일한다. 
            int tmp = dest;
            dest = src;
            src = tmp;
        }
        Edge tmp(src, dest);
        el.push_back(tmp);
    }
    sort(el.begin(), el.end(), edgecmp);
    Graph g(el, vn);
    g.DFS_start(sn);
    g.BFS(sn);
	return 0; 
}