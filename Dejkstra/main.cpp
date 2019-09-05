#include <iostream>
#include<fstream>
#include<set>
#include<vector>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m, u, v, w;
    fin >> n >> m;

    vector<vector<pair<int, int>>> adjacencyList(n);

    for (int i = 0; i < m; ++i) {
        fin >> u >> v >> w;
        adjacencyList[u - 1].emplace_back(make_pair(v - 1, w));
        adjacencyList[v - 1].emplace_back(make_pair(u - 1, w));
    }

    vector<long long> pathLength = vector<long long>(n, LLONG_MAX);
    // First length, second vertex
    set<pair<long long, int>> set;
    set.insert(make_pair(0, 0));//start vertex
    pathLength[0] = 0;

    int currentVertex;
    int vertex;
    int weight;
    long long currentLength;
    while (!set.empty()) {
        currentLength = set.begin()->first;
        currentVertex = set.begin()->second;
        set.erase(set.begin());

        //Instead of if(), we can make .erase before successful relaxation
        if (currentLength == pathLength[currentVertex])//As one vertex can appear more than one time
            for (int j = 0; j < adjacencyList[currentVertex].size(); ++j) {
                vertex = adjacencyList[currentVertex].at(j).first;
                weight = adjacencyList[currentVertex].at(j).second;
                if (pathLength[vertex] > currentLength + weight) {
                    pathLength[vertex] = currentLength + weight;
                    set.insert(make_pair(pathLength[vertex], vertex));
                }
            }
    }
    fout << pathLength[n - 1];

    fin.close();
    fout.close();
    return 0;
}