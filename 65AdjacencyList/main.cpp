#include <iostream>
#include<list>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n, m;
    fin >> n >> m;

    list<int> *graph = new list<int>[n];
    //Using of adjacency matrix will lead to memory overflow
    int a, b;
    for (int i = 0; i < m; ++i) {
        fin >> a >> b;
        graph[a - 1].push_back(b);
        graph[b - 1].push_back(a);
    }

    for (int i = 0; i < n; ++i) {
        fout << graph[i].size() << " ";
        while (!graph[i].empty()) {
            fout << graph[i].back() << " ";
            graph[i].pop_back();
        }
        fout << endl;
    }


    delete[] graph;
    fin.close();
    fout.close();
    return 0;
}