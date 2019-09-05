#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

bool isOdd(int x) {
    return x & 1;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m, a, b;
    fin >> n >> m;

    vector<vector<int>> adjacencyList(n);

    for (int i = 0; i < m; ++i) {
        fin >> a >> b;
        a--;
        b--;
        adjacencyList[a].emplace_back(b);
        adjacencyList[b].emplace_back(a);
    }

    vector<int> minEven(n, INT_MAX);
    vector<int> minOdd(n, INT_MAX);

    vector<bool> isEvenBlocked(n, false);
    vector<bool> isOddBlocked(n, false);

    queue<pair<int, bool>> queueBFS;

    queueBFS.push(make_pair(0,
                            true));   //pushing start vertex, true means that it is even path(so in the following it must be odd(false))
    minEven[0] = 0;//Zero length of path
    isEvenBlocked[0] = true;

    //We will start from odd length of path
    bool isEvenTurn;

    int currentVertex;
    bool currentParity;
    int currentMin;
    int vertex;
    while (!queueBFS.empty()) {
        currentVertex = queueBFS.front().first;
        currentParity = queueBFS.front().second;

        queueBFS.pop();

        if (currentParity) //if it is even
            currentMin = minEven[currentVertex];
        else    //odd turn
            currentMin = minOdd[currentVertex];


        isEvenTurn = !currentParity;

        if (isEvenTurn) {
            for (int j = 0; j < adjacencyList[currentVertex].size(); ++j) {
                vertex = adjacencyList[currentVertex][j];

                if (!isEvenBlocked[vertex]) {
                    isEvenBlocked[vertex] = true;
                    minEven[vertex] = currentMin + 1;
                    queueBFS.push(make_pair(vertex, true));//true means that it is even path
                }
            }
        } else    //ODD turn
        {
            for (int j = 0; j < adjacencyList[currentVertex].size(); ++j) {
                vertex = adjacencyList[currentVertex][j];

                if (!isOddBlocked[vertex]) {
                    isOddBlocked[vertex] = true;
                    minOdd[vertex] = currentMin + 1;
                    queueBFS.push(make_pair(vertex, false));//false means that it is odd path
                }
            }
        }
    }

    //Working with requests
    int requestQuantity, v, k;
    fin >> requestQuantity;

    for (int i = 0; i < requestQuantity; ++i) {
        fin >> v >> k;
        v--;

        if (v == 0 && adjacencyList[0].empty())//first vertex
        {
            if (k == 0)//only possible situation
                fout << "Yes\n";
            else
                fout << "No\n";

        } else {
            if (isOdd(k)) {//is odd
                if (minOdd[v] <= k)
                    fout << "Yes\n";
                else
                    fout << "No\n";

            } else {//is even
                if (minEven[v] <= k)
                    fout << "Yes\n";
                else
                    fout << "No\n";

            }
        }
    }


    fin.close();
    fout.close();
    return 0;
}