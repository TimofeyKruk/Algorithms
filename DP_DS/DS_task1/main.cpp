#include <iostream>
#include <fstream>
#include<queue>

using namespace std;


struct myPair {
    int x;
    int y;

    myPair(int x1, int y1) {
        x = x1;
        y = y1;
    }
};

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");

    queue<myPair> myQueue;

    int m, n;
    fin >> m >> n;

    int **matrix = new int *[m];
    bool **used = new bool *[m];
    for (int i = 0; i < m; ++i) {
        matrix[i] = new int[n];
        used[i] = new bool[n];
        for (int j = 0; j < n; ++j) {
            used[i][j] = false;
            fin >> matrix[i][j];

        }
    }




//    for (int i = 0; i < m; ++i) {
//        cout<<"\n";
//        for (int j = 0; j < n; ++j) {
//            cout<<matrix[i][j]<<" ";
//        }
//    }


    int totalCount = 0;

    myPair f = myPair(0, 0);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == 0)
                if (!used[i][j]) {
                    totalCount++;
                    f.x = i;
                    f.y = j;
                    myQueue.push(f);

                    used[i][j] = true;
                    while (!myQueue.empty()) {
                        f = myQueue.front();
                        myQueue.pop();
                        myPair g = myPair(0, 0);
                        //DOWN
                        if (f.x - 1 < 0) {
                            if (!used[m - 1][f.y] && matrix[m - 1][f.y] == 0) {
                                g.x = m - 1;
                                g.y = f.y;
                                myQueue.push(g);
                                used[g.x][g.y] = true;
                            }
                        } else if (!used[f.x - 1][f.y] && matrix[f.x - 1][f.y] == 0) {
                            g.x = f.x - 1;
                            g.y = f.y;
                            myQueue.push(g);
                            used[f.x - 1][f.y] = true;
                        }

                        //UP
                        if (f.x + 1 >= m) {
                            if (!used[0][f.y] && matrix[0][f.y] == 0) {
                                g.x = 0;
                                g.y = f.y;
                                myQueue.push(g);
                                used[g.x][g.y] = true;
                            }
                        } else if (!used[f.x + 1][f.y] && matrix[f.x + 1][f.y] == 0) {
                            g.x = f.x + 1;
                            g.y = f.y;
                            myQueue.push(g);
                            used[g.x][g.y] = true;
                        }

                        //LEFT
                        if (f.y - 1 >= 0)
                            if (!used[f.x][f.y - 1] && matrix[f.x][f.y - 1] == 0) {
                                g.x = f.x;
                                g.y = f.y - 1;
                                myQueue.push(g);
                                used[g.x][g.y] = true;
                            }

                        //RIGHT
                        if (f.y + 1 <= n - 1)
                            if (!used[f.x][f.y + 1] && matrix[f.x][f.y + 1] == 0) {
                                g.x = f.x;
                                g.y = f.y + 1;
                                myQueue.push(g);
                                used[g.x][g.y] = true;
                            }
                    }
                }
        }
    }

    fout << totalCount;

    for (int i = 0; i < m; ++i) {
        delete[] matrix[i];
        delete[] used[i];
    }
    delete[] matrix;
    delete[] used;
    fin.close();
    fout.close();
    return 0;
}