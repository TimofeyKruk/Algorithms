#include <iostream>
#include <fstream>

using namespace std;

int hashFunction(int x, int i, int m, int c) {
    return ((x % m) + c * i) % m;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m, c;
    fin >> m >> c >> n;

    int *hashTable = new int[m];
    for (int i = 0; i < m; ++i) {
        hashTable[i] = -1;
    }

    int currentKey;
    int currentPosition;
    int attempt;
    for (int i = 0; i < n; ++i) {
        fin >> currentKey;
        attempt = 0;
        currentPosition = hashFunction(currentKey, attempt, m, c);
        while (hashTable[currentPosition] != -1) {
            if (hashTable[currentPosition] == currentKey) { break; }
            attempt++;
            currentPosition = hashFunction(currentKey, attempt, m, c);
        }
        hashTable[currentPosition] = currentKey;
    }

    for (int i = 0; i < m; ++i)
        fout << hashTable[i] << " ";

    delete[] hashTable;
    fin.close();
    fout.close();
    return 0;
}