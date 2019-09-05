#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n;
    fin >> n;


    int **adjacencyMatrix = new int *[n];
    int *label = new int[n];
    int *lastStopped = new int[n];
    bool *visited = new bool[n];

    for (int i = 0; i < n; ++i) {
        visited[i] = false;
        lastStopped[i] = 0;
        adjacencyMatrix[i] = new int[n];
        for (int j = 0; j < n; ++j)
            fin >> adjacencyMatrix[i][j];
    }

    int counter = 1;
    int currentVertex;
    stack<int> stackDFS;

    bool allAlreadyLabelled;
    for (int k = 0; k < n; ++k) {
        if (!visited[k]) {
            label[k] = counter++;
            visited[k] = true;
            stackDFS.push(k);

            while (!stackDFS.empty()) {
                currentVertex = stackDFS.top();

                allAlreadyLabelled = true;
                for (int j = lastStopped[currentVertex]; j < n; ++j) {
                    if (adjacencyMatrix[currentVertex][j] == 1 && !visited[j]) {
                        visited[j] = true;
                        label[j] = counter++;
                        stackDFS.push(j);
                        lastStopped[currentVertex] = j + 1;
                        allAlreadyLabelled = false;
                        break;
                    }
                }

                if (allAlreadyLabelled) {
                    stackDFS.pop();
                }
            }

        }
    }

    for (int i = 0; i < n; ++i)
        fout << label[i] << " ";

    for (int i = 0; i < n; ++i)
        delete[] adjacencyMatrix[i];
    delete[] adjacencyMatrix;
    delete[] visited;
    delete[] label;
    delete[] lastStopped;

    fin.close();
    fout.close();
    return 0;
}