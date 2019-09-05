#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n;
    fin >> n;

    int **adjacencyMatrix = new int *[n];
    int *label = new int[n];
    bool *visited = new bool[n];

    for (int i = 0; i < n; ++i) {
        adjacencyMatrix[i] = new int[n];
        visited[i] = false;

        for (int j = 0; j < n; ++j) {
            fin >> adjacencyMatrix[i][j];
        }
    }

    queue<int> queueBFS;
    int currentStep = 1;
    int currentVertex;
    //This cycle is for all connectivity components
    for (int k = 0; k < n; ++k) {
        if (!visited[k])//then it is a new connectivity component
        {
            visited[k] = true;
            queueBFS.push(k);
            label[k] = currentStep++;

            while (!queueBFS.empty()) {
                currentVertex = queueBFS.front();
                queueBFS.pop();
                for (int j = 0; j < n; ++j) {
                    if (adjacencyMatrix[currentVertex][j] == 1 && !visited[j]) {
                        visited[j] = true;
                        queueBFS.push(j);
                        label[j] = currentStep++;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; ++i)
        fout << label[i] << " ";

    for (int i = 0; i < n; ++i)
        delete[] adjacencyMatrix[i];
    delete[] adjacencyMatrix;
    delete[] label;
    delete[] visited;

    fin.close();
    fout.close();
    return 0;
}