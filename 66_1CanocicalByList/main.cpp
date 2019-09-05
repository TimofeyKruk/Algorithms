#include <iostream>
#include<fstream>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n;
    fin >> n;

    int *canonicalArray = new int[n];
    for (int i = 0; i < n; ++i)
        canonicalArray[i] = 0;

    int start, finnish;
    for (int i = 0; i < n - 1; ++i) {
        fin >> start >> finnish;
        canonicalArray[finnish - 1] = start;
    }

    for (int i = 0; i < n; ++i)
        fout << canonicalArray[i] << " ";

    delete[] canonicalArray;

    fin.close();
    fout.close();
    return 0;
}