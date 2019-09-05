#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

//  isTree checks for connectivity
bool isTree(int n, int **adjacencyMatrix, bool *visited) {
    queue<int> queueBFS;
    int currentVertex;
    //This cycle is for all connectivity components
    for (int k = 0; k < n; ++k) {
        if (!visited[k])//then it is a new connectivity component
        {
            if (k != 0)//It is second connectivity component, so no connectivity
                return false;

            visited[k] = true;
            queueBFS.push(k);

            while (!queueBFS.empty()) {
                currentVertex = queueBFS.front();
                queueBFS.pop();
                for (int j = 0; j < n; ++j) {
                    if (adjacencyMatrix[currentVertex][j] == 1 && !visited[j]) {
                        visited[j] = true;
                        queueBFS.push(j);
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n;
    fin >> n;
    
    bool *visited = new bool[n];

    int **adjacencyMatrix = new int *[n];
    int edgeCount = 0;

    for (int i = 0; i < n; ++i) {
        adjacencyMatrix[i] = new int[n];
        visited[i] = false;

        for (int j = 0; j < n; ++j) {
            fin >> adjacencyMatrix[i][j];
            if (adjacencyMatrix[i][j] == 1)
                edgeCount++;
        }
    }

    bool answerConnectivity = isTree(n, adjacencyMatrix, visited);
    bool answerEdge = true;

    //As one edge was counted twice
    edgeCount /= 2;
    if (n != (edgeCount + 1)) {
        answerEdge = false;
    }

    if (answerConnectivity && answerEdge)
        fout << "Yes";
    else fout << "No";


    for (int i = 0; i < n; ++i)
        delete[] adjacencyMatrix[i];
    delete[] adjacencyMatrix;
    delete[] visited;

    fin.close();
    fout.close();
    return 0;
}