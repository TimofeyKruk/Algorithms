#include<iostream>
#include<fstream>

struct pair {
    int value;
    int currentlyAddedValue;

    pair() {
        value = 0;
        currentlyAddedValue = 0;
    }
};

long long findSolution(int n, int m, int n1, int m1, int k, int **screen) {
    long long count = 0;

    //Additional memory, where quantity will be stored
    pair **help = new pair *[n1 + n];
    for (int i = 0; i < n1 + n; ++i) {
        help[i] = new pair[m1 + m];//Already initialized with zeros
    }

    //Forming the matrix
    for (int i = 0; i < (n - (n1 - 1)); ++i) {
        for (int j = 0; j < (m - (m1 - 1)); ++j) {
            help[i + n1][j + m1].value = help[i + n1 - 1][j + m1].value - help[i][j + m1].currentlyAddedValue
                                         + help[i + n1][j + m1 - 1].value - help[i + n1][j].currentlyAddedValue
                                         - help[i + n1 - 1][j + m1 - 1].value + help[i][j].currentlyAddedValue;

            int rest = (screen[i][j] + help[i + n1][j + m1].value) % k;
            help[i + n1][j + m1].currentlyAddedValue = ((rest != 0) ? (k - rest) : 0);

            help[i + n1][j + m1].value += help[i + n1][j + m1].currentlyAddedValue;
            count += help[i + n1][j + m1].currentlyAddedValue;
        }
    }

    //Forming the rest of matrix, where we don't need to add new values(simultaneously checking if it was possible to solve the task)
    for (int i = 0; i < n - (n1 - 1); ++i) {
        for (int j = m - (m1 - 1); j < m; ++j) {
            help[i + n1][j + m1].value = help[i + n1 - 1][j + m1].value - help[i][j + m1].currentlyAddedValue
                                         + help[i + n1][j + m1 - 1].value - help[i + n1][j].currentlyAddedValue
                                         - help[i + n1 - 1][j + m1 - 1].value + help[i][j].currentlyAddedValue;

            if (((screen[i][j] + help[i + n1][j + m1].value) % k) != 0)
                return -1;
        }
    }

    for (int i = n - (n1 - 1); i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            help[i + n1][j + m1].value = help[i + n1 - 1][j + m1].value - help[i][j + m1].currentlyAddedValue
                                         + help[i + n1][j + m1 - 1].value - help[i + n1][j].currentlyAddedValue
                                         - help[i + n1 - 1][j + m1 - 1].value + help[i][j].currentlyAddedValue;

            if (((screen[i][j] + help[i + n1][j + m1].value) % k) != 0)
                return -1;
        }
    }

    for (int i = 0; i < n1 + n; ++i)
        delete[] help[i];
    delete[] help;

    return count;
}

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int n, m, n1, m1, k;
    fin >> n >> m >> n1 >> m1 >> k;

    int **screen = new int *[n];
    for (int i = 0; i < n; ++i) {
        screen[i] = new int[m];
        for (int j = 0; j < m; ++j) {
            fin >> screen[i][j];
        }
    }

    long long result = findSolution(n, m, n1, m1, k, screen);

    if (result == -1)
        fout << "impossible";
    else
        fout << result;

    for (int i = 0; i < n; ++i)
        delete[] screen[i];
    delete[] screen;

    fin.close();
    fout.close();
    return 0;
}