#include <iostream>
#include<fstream>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n;
    fin >> n;

    int **matrix = new int *[n];
    int *canonicalArray = new int[n];
    for (int i = 0; i < n; ++i) {
        canonicalArray[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            fin >> matrix[i][j];
            if (matrix[i][j] == 1) {
                canonicalArray[j] = i + 1;
            }
        }
    }

    for (int i = 0; i < n; ++i)
        fout << canonicalArray[i] << " ";

    for (int i = 0; i < n; ++i)
        delete[] matrix[i];
    delete[] matrix;

    delete[] canonicalArray;

    fin.close();
    fout.close();
    return 0;
}