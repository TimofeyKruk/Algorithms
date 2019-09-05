#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <list>
#include <set>

using namespace std;

int main() {
    FILE *fileIn = fopen("input.txt", "r");
    FILE *fileOut = fopen("output.txt", "w");

    int n, m;
    fscanf(fileIn, "%d %d", &n, &m);

    int startVertex, endVertex, weight;

    //0 will be super source
    vector<vector<int>> adjacencyMatrix(n + 1);
    for (int i = 0; i < n + 1; ++i) {
        adjacencyMatrix[i].reserve(n + 1);
        adjacencyMatrix[i].assign(n + 1, -1);

    }
    vector<vector<int>> network;

    map<pair<int, int>, int> mapOfEdges;
    set<int> numbersOfDeletedEdges;

    int tempMin, tempMax;

    for (int i = 0; i < m; ++i) {
        fscanf(fileIn, " %d %d %d", &startVertex, &endVertex, &weight);
        adjacencyMatrix[startVertex][endVertex] = weight;
        adjacencyMatrix[endVertex][startVertex] = weight;

        tempMin = std::min(startVertex, endVertex);
        tempMax = std::max(startVertex, endVertex);

        mapOfEdges[make_pair(tempMin, tempMax)] = i + 1;
    }

    int k;
    fscanf(fileIn, "%d", &k);

    vector<int> fixedVertexesArray(k);
    for (int i = 0; i < k; ++i) {
        fscanf(fileIn, "%d", &fixedVertexesArray[i]);
    }

    //_______Main part of algorithm__________
    //preparing residual graph(adding fixed vertexes to super source)
    int whereToGo;
    int superSourceInd = 0;

    for (int i = 0; i < k; ++i) {
        whereToGo = fixedVertexesArray[i];
        adjacencyMatrix[superSourceInd][whereToGo] = INT_MAX;
        adjacencyMatrix[whereToGo][superSourceInd] = 0;
    }

    int currentSink;
    int currentVertex;
    int parent, son;
    int maxValueInPath;
    long long totalWeight = 0;
    int indexOfEdge;
    vector<int> parents(n + 1);
    vector<bool> isVisited(n + 1);


    //Cycle for working with every fixed vertex as sink
    for (int i = 0; i < k; ++i) {
        network = adjacencyMatrix;

        currentSink = fixedVertexesArray[i];

        //deleting edge to currentSink
        network[superSourceInd][currentSink] = -1;
        network[currentSink][superSourceInd] = -1;

        //_____*** MAX FLOW ***_____
        bool augmentingPathFound = true;

        parents[superSourceInd] = -1;
        queue<int> queueNetwork;

        while (augmentingPathFound) {
            augmentingPathFound = false;

            //Cleaning
            while (!queueNetwork.empty())
                queueNetwork.pop();

            isVisited.assign(n + 1, false);

            queueNetwork.push(superSourceInd);
            isVisited[superSourceInd] = true;

            //  BFS
            while (!queueNetwork.empty()) {
                currentVertex = queueNetwork.front();
                queueNetwork.pop();

                for (int j = 0; j < n + 1; ++j) {
                    if (network[currentVertex][j] > 0 && !isVisited[j]) {
                        parents[j] = currentVertex;
                        if (j == currentSink) {
                            augmentingPathFound = true;
                        }
                        isVisited[j] = true;
                        queueNetwork.push(j);
                    }
                }

            }

            if (augmentingPathFound) {
                //Searching for minimum possible flow in this augmenting path
                maxValueInPath = INT_MAX;

                parent = parents[currentSink];
                son = currentSink;
                while (parent != -1) {

                    if (network[parent][son] < maxValueInPath) {
                        maxValueInPath = network[parent][son];
                    }
                    son = parent;
                    parent = parents[parent];
                }
                //By the theorem, total weight of edges to delete is equal to max flow value
                totalWeight += maxValueInPath;

                //part 2: _______changing path__________
                parent = parents[currentSink];
                son = currentSink;
                while (parent != -1) {
                    network[parent][son] -= maxValueInPath;
                    network[son][parent] += maxValueInPath;

                    son = parent;
                    parent = parents[parent];
                }
            }
        }

        //______________Now searching for edges that needs to be deleted_______________
        //BFS
        //Cleaning
        while (!queueNetwork.empty())
            queueNetwork.pop();

        isVisited.assign(n + 1, false);

        queueNetwork.push(superSourceInd);
        isVisited[superSourceInd] = true;

        //  BFS main part again
        while (!queueNetwork.empty()) {
            currentVertex = queueNetwork.front();
            queueNetwork.pop();

            for (int j = 0; j < n + 1; ++j) {
                if (network[currentVertex][j] > 0 && !isVisited[j]) {
                    isVisited[j] = true;
                    queueNetwork.push(j);
                }
            }
        }

        //looking through all edges
        for (int u = 1; u < n + 1; ++u) {
            for (int v = 1; v < n + 1; ++v) {
                if (adjacencyMatrix[u][v] != -1 && isVisited[u] && !isVisited[v]) {
                    indexOfEdge = mapOfEdges[make_pair(std::min(u, v), std::max(u, v))];
                    if(indexOfEdge>=1 &&indexOfEdge<=m)
                    numbersOfDeletedEdges.insert(indexOfEdge);
                    adjacencyMatrix[u][v] = -1;
                    adjacencyMatrix[v][u] = -1;
                }
            }
        }
    }

    //  OUTPUT
    fprintf(fileOut, "%lld\n", totalWeight);
    fprintf(fileOut, "%d\n", numbersOfDeletedEdges.size());

    for (auto numb:numbersOfDeletedEdges)
        fprintf(fileOut, "%d\n", numb);


    fclose(fileIn);
    fclose(fileOut);
    return 0;
}