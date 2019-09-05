#include <iostream>
#include <fstream>

using namespace std;

//******* DP BACK *********
int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m;
    fin >> n >> m;
    int **twoRows = new int *[2];
    twoRows[0] = new int[m+1];
    twoRows[1] = new int[m+1];

    int first = 0;
    int second = 1;
    //adding left border in order not to make extra if clause
    twoRows[first][0]=0;
    twoRows[second][0]=0;

    //Basis of DP
    for (int j = 1; j < m+1; ++j)
        twoRows[first][j] = 1;

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m+1; ++j) {
            twoRows[second][j] = twoRows[first][j]+twoRows[second][j - 1];

            if(twoRows[second][j]>=1000000007)
            twoRows[second][j] -=1000000007;
        }
        swap(first, second);//Now in second stores info that is needed to count next row(first in our definition)
    }

    //As we have swapped in the end of cycle, so answer is stored in the end of first
    fout << twoRows[first][m];

    delete[] twoRows[0];
    delete[] twoRows[1];
    delete[] twoRows;

    fin.close();
    fout.close();
    return 0;
}