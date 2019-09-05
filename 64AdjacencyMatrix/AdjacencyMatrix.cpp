#include<iostream>
#include<fstream>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n, m;
    fin >> n >> m;

    int** adjacencyMatrix = new int*[n];
    for (int i = 0; i < n; ++i)
            {
            adjacencyMatrix[i] = new int[n];
            for(int j=0;j<n;++j)
                adjacencyMatrix[i][j]=0;
            }


    int a, b;
    for (int i = 0; i < m; ++i) {
        fin >> a >> b;
        a--;
        b--;
            adjacencyMatrix[a][b] = 1;
            adjacencyMatrix[b][a] = 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fout << adjacencyMatrix[i][j]<<" ";
        }
            fout << endl;
    }

    for (int i = 0; i < n; ++i)
        delete[] adjacencyMatrix[i];
    delete[] adjacencyMatrix;

    fin.close();
    fout.close();
    return 0;
}