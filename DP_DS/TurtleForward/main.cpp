#include <iostream>
#include <fstream>

using namespace std;
//      F   O   R   W   A   R   D

//*******! DP FORWARD !*********
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
    //at last column we will have unnecessary info, in order not to make if clause for right border

    //Initializing with 0
    for(int j=0;j<m+1;++j)
    {
        twoRows[first][j]=0;
    }
    //Basis of DP
        twoRows[first][0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {

            if(twoRows[first][j]>=1000000007)
                twoRows[first][j] -=1000000007;

            twoRows[first][j+1]+=twoRows[first][j];
            twoRows[second][j]=twoRows[first][j];

        }
        swap(first, second);//Now in second stores info that is needed to count next row(first in our definition)
    }

    //As we have swapped in the end of cycle, so answer is stored in the end of SECOND
    fout << twoRows[second][m-1];

    delete[] twoRows[0];
    delete[] twoRows[1];
    delete[] twoRows;

    fin.close();
    fout.close();
    return 0;
}