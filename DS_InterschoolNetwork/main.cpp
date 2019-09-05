#include <iostream>
#include<fstream>
#include <stack>
#include<algorithm>
#include <queue>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n;
    fin >> n;

    int **adjacencyMatrix = new int *[n];
    int *firstLabel = new int[n];
    int *secondLabel = new int[n];
    int *lastStopped = new int[n];
    bool *visited = new bool[n];

    for (int i = 0; i < n; ++i) {
        visited[i] = false;
        lastStopped[i] = 0;
        adjacencyMatrix[i] = new int[n];
        for (int j = 0; j < n; ++j)
            adjacencyMatrix[i][j] = 0;//Initializing with 0
    }

    int a;
    int b;
    for (int i = 0; i < n; ++i) {
        fin >> a;
        while (a != 0) {
            adjacencyMatrix[i][a - 1] = 1;
            fin >> a;
        }
    }

    int counter = 1;
    int currentVertex;
    stack<int> stackDFS;
    stack<int> timeOutSorted;


    bool allAlreadyLabelled;
    for (int k = 0; k < n; ++k) {
        if (!visited[k]) {
            firstLabel[k] = counter++;
            visited[k] = true;
            stackDFS.push(k);

            while (!stackDFS.empty()) {
                currentVertex = stackDFS.top();

                allAlreadyLabelled = true;
                for (int j = lastStopped[currentVertex]; j < n; ++j) {
                    if (adjacencyMatrix[currentVertex][j] == 1 && !visited[j]) {
                        visited[j] = true;
                        firstLabel[j] = counter++;
                        stackDFS.push(j);
                        lastStopped[currentVertex] = j + 1;
                        allAlreadyLabelled = false;
                        break;
                    }
                }
                if (allAlreadyLabelled) {
                    secondLabel[currentVertex] = counter++;
                    timeOutSorted.push(currentVertex);
                    stackDFS.pop();
                }
            }
        }
    }

    //Now transpose graph, remember second labels,all vertexes are not visited
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
        lastStopped[i] = 0;
    }

    //Repeating DFS with transposed matrix
    //All vertexes that will be labeled by one DSU are in one strongly-connected component
    int connectivityNumber = 0;
    int k;
    queue<int> representativesQueue;
    //Now in first label will be stored DSU(what component representative  does the vertex belong)
    while (!timeOutSorted.empty()) {
        k = timeOutSorted.top();
        timeOutSorted.pop();

        if (!visited[k]) {
            firstLabel[k] = connectivityNumber;
            representativesQueue.push(k + 1);

            visited[k] = true;
            stackDFS.push(k);

            while (!stackDFS.empty()) {
                currentVertex = stackDFS.top();

                allAlreadyLabelled = true;
                for (int j = lastStopped[currentVertex]; j < n; ++j) {
                    if (adjacencyMatrix[j][currentVertex] == 1 && !visited[j]) {
                        visited[j] = true;
                        firstLabel[j] = connectivityNumber;
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
            connectivityNumber++;
        }
    }
    //+++++++++++++++++++++++++++++++++++++++
    //Representatives array for simplifying
    int *representatives = new int[connectivityNumber];
    //New adjacency matrix for graph condensation
    int **condensation = new int *[connectivityNumber];

    for (int i = 0; i < connectivityNumber; ++i) {
        representatives[i] = representativesQueue.front();
        representativesQueue.pop();

        condensation[i] = new int[connectivityNumber];
        for (int j = 0; j < connectivityNumber; ++j) {
            condensation[i][j] = 0;
        }
    }

    int x, y;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                //It is find() for DSU
                x = firstLabel[i];
                y = firstLabel[j];
                //It is important not to have loops in the graph condensation
                if (x != y)
                    condensation[x][y] = 1;
            }
        }
    }

    //CLASSIFICATION
    int source = 0, sink = 0, isolated = 0;
    int *type = new int[connectivityNumber];
    //Searching for sinks
    bool isSink;
    for (int i = 0; i < connectivityNumber; ++i) {
        isSink = true;
        type[i] = 0;//Not classified
        for (int j = 0; j < connectivityNumber; ++j) {
            if (condensation[i][j] == 1) {
                isSink = false;
                break;
            }
        }

        if (isSink) {
            sink++;
            type[i] = 1;//is sink
        }
    }

    //Searching for sources and isolated
    queue<int> isolatedQ;
    bool isSource;
    bool *wasAddedSink = new bool[connectivityNumber];

    for (int j = 0; j < connectivityNumber; ++j) {
        isSource = true;
        wasAddedSink[j] = false;
        for (int i = 0; i < connectivityNumber; ++i) {
            if (condensation[i][j] == 1) {
                isSource = false;
                break;
            }
        }

        if (isSource) {
            if (type[j] == 1) {
                isolated++;
                sink--;
                type[j] = 3;//is isolated
                isolatedQ.push(j);
            } else {
                source++;
                type[j] = 2;//is source
            }
        }
    }

    //Task A is a quantity of sources+isolated
    fout << source + isolated << "\n";

    int taskB = std::max(source, sink);
    if (taskB != 0)
        taskB += isolated;
    else if (isolated != 1)
        taskB += isolated;

    fout << taskB << "\n";

//-----------------------------------------------------------------------------------------------------------------------
//Algorithm of solving augmentation problem(finding edges)
//Searching of max bipartite matching by using max flow

    if (source != 0)   //if source = 0, then sink also = 0
    {
        int superSourceInd = connectivityNumber;
        int superSinkInd = connectivityNumber + 1;
        int bipartiteNumber = connectivityNumber + 2;

        int **bipartiteNetwork = new int *[bipartiteNumber];
        for (int i = 0; i < bipartiteNumber; ++i) {
            bipartiteNetwork[i] = new int[bipartiteNumber];
            for (int j = 0; j < bipartiteNumber; ++j) {
                bipartiteNetwork[i][j] = -1;//We will need 0
            }
        }

        queue<int> sourceAllQ;
        queue<int> sinkAllQ;
        queue<int> queuebipartiteNetwork;
        bool *usedForPrint = new bool[connectivityNumber];
        bool *visitedWhileMatching = new bool[connectivityNumber];

        //Preparing bipartiteNetwork graph
        for (int i = 0; i < connectivityNumber; ++i) {
            usedForPrint[i] = false;//initialisation
            //We will use bfs to make bipartiteNetwork graph
            if (type[i] == 2)//source
            {
                for (int z = 0; z < connectivityNumber; ++z)
                    visitedWhileMatching[z] = false;
                sourceAllQ.push(i);// collecting all sources
                bipartiteNetwork[superSourceInd][i] = 1;
                bipartiteNetwork[i][superSourceInd] = 0;

                queuebipartiteNetwork.push(i);
                visitedWhileMatching[i]=true;

                while (!queuebipartiteNetwork.empty()) {
                    currentVertex = queuebipartiteNetwork.front();
                    queuebipartiteNetwork.pop();

                    for (int j = 0; j < connectivityNumber; ++j) {
                        if (condensation[currentVertex][j] == 1 && !visitedWhileMatching[j]) {
                            if (type[j] == 1)//sink
                            {
                                if (!wasAddedSink[j]) {
                                    sinkAllQ.push(j);//collecting all sinks
                                    wasAddedSink[j] = true;
                                }
                                bipartiteNetwork[i][j] = 1;
                                //Adding reverse
                                bipartiteNetwork[j][i] = 0;
                                //Adding to supersink
                                bipartiteNetwork[j][superSinkInd] = 1;
                                bipartiteNetwork[superSinkInd][j] = 0;

                            } else {
                                queuebipartiteNetwork.push(j);
                            }
                            visitedWhileMatching[j] = true;
                        }
                    }
                }
            }
        }

        //      MAX FLOW
        bool augmentingPathFound = true;//For first iteration
        int *parents = new int[bipartiteNumber];
        bool *visitedNetwork = new bool[bipartiteNumber];
        parents[superSourceInd] = -1;//-1 will be as stopper

        //Finding all augmenting paths and changing graph
        while (augmentingPathFound) {
            augmentingPathFound = false;
            //Cleaning
            while (!queuebipartiteNetwork.empty())
                queuebipartiteNetwork.pop();
            for (int i = 0; i < bipartiteNumber; ++i)
                visitedNetwork[i] = false;

            queuebipartiteNetwork.push(superSourceInd);
            visitedNetwork[superSourceInd] = true;

            while (!queuebipartiteNetwork.empty()) {
                currentVertex = queuebipartiteNetwork.front();
                queuebipartiteNetwork.pop();
                for (int j = 0; j < bipartiteNumber; ++j) {
                    if (bipartiteNetwork[currentVertex][j] == 1 && !visitedNetwork[j]) {
                        parents[j] = currentVertex;
                        if (j == superSinkInd) {
                            augmentingPathFound = true;
                            break;
                        }
                        visitedNetwork[j] = true;
                        queuebipartiteNetwork.push(j);
                    }
                }
                if (augmentingPathFound) {
                    a = parents[superSinkInd];
                    b = superSinkInd;
                    while (a != -1) { //stopper
                        bipartiteNetwork[a][b] = 0;
                        bipartiteNetwork[b][a] = 1;
                        b = a;
                        a = parents[b];
                    }
                    break;
                }
            }
        }


        //Getting max matching
        queue<int> queueSource;
        queue<int> queueSink;
        for (int i = 0; i < connectivityNumber; ++i) {
            if (type[i] == 2)//source
            {
                for (int j = 0; j < connectivityNumber; ++j) {
                    if (bipartiteNetwork[i][j] == 0)   //We are searching for the only 0 in row
                    {
                        queueSource.push(i);
                        queueSink.push(j);
                        break;
                    }
                }
            }
        }


        int sourceStart = queueSource.front();
        queueSource.pop();
        usedForPrint[sourceStart] = true;

        int sinkStart = queueSink.front();
        int matchingSinks = queueSink.size();

        while (!queueSource.empty()) {
            a = queueSink.front();
            b = queueSource.front();
            usedForPrint[a] = true;
            usedForPrint[b] = true;

            queueSink.pop();
            queueSource.pop();
            fout << representatives[a] << ' ' << representatives[b] << '\n';
        }

        int sinkLast = queueSink.front();
        queueSink.pop();
        usedForPrint[sinkLast] = true;

        //now i need to connect  sink with isolated
        a = sinkLast;
        while (!isolatedQ.empty()) {
            b = isolatedQ.front();
            isolatedQ.pop();
            fout << representatives[a] << ' ' << representatives[b] << '\n';
            a = b;
        }
        b = sourceStart;
        fout << representatives[a] << ' ' << representatives[b] << '\n';

        int minimumOfSS = std::min(source, sink) - matchingSinks;

        for (int i = 0; i < minimumOfSS; ++i) {
            //sinks
            while (!sinkAllQ.empty()) {
                a = sinkAllQ.front();
                sinkAllQ.pop();
                if (!usedForPrint[a])//If false;
                    break;
            }

            //sources
            while (!sourceAllQ.empty()) {
                b = sourceAllQ.front();
                sourceAllQ.pop();
                if (!usedForPrint[b])
                    break;
            }
            fout << representatives[a] << ' ' << representatives[b] << '\n';
        }

        //If there is more sources
        while (!sourceAllQ.empty()) {
            b = sourceAllQ.front();
            sourceAllQ.pop();
            if (!usedForPrint[b])
                fout << representatives[sinkStart] << ' ' << representatives[b] << '\n';
        }

        //If there is more sinks
        while (!sinkAllQ.empty()) {
            a = sinkAllQ.front();
            sinkAllQ.pop();
            if (!usedForPrint[a])
                fout << representatives[a] << ' ' << representatives[sourceStart] << '\n';
        }

        for (int i = 0; i < bipartiteNumber; ++i)
            delete[] bipartiteNetwork[i];
        delete[] bipartiteNetwork;
        delete[] usedForPrint;
        delete[] parents;
        delete[] visitedNetwork;
    } else    //******** IF THERE IS ONLY ISOLATED  **********
    {
        //In such situation at least one isolated exist (by the task)
        int isolatedStart = isolatedQ.front();
        a = isolatedStart;
        isolatedQ.pop();

        while (!isolatedQ.empty()) {
            b = isolatedQ.front();
            isolatedQ.pop();
            fout << representatives[a] << ' ' << representatives[b] << '\n';
            a = b;
        }
        if (a != isolatedStart)//if there is more than one isolated
        {
            b = isolatedStart;
            fout << representatives[a] << ' ' << representatives[b] << '\n';
        }
    }

    //+++++++++++++++++++++++++++++++++++++++
    for (int i = 0; i < connectivityNumber; ++i)
        delete[] condensation[i];
    delete[] condensation;
    for (int i = 0; i < n; ++i)
        delete[] adjacencyMatrix[i];
    delete[] adjacencyMatrix;

    delete[] visited;
    delete[] firstLabel;
    delete[] representatives;
    delete[] secondLabel;
    delete[] lastStopped;
    delete[] type;
    delete[] wasAddedSink;

    fin.close();
    fout.close();
    return 0;
}