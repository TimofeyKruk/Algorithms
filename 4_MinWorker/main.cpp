#include <iostream>
#include<vector>
#include<set>

using namespace std;

struct descendingComparison {
    template<typename T>
    bool operator()(const T &o1, const T &o2) const {
        return o1 > o2;
    }
};

int main() {
    FILE *fileIn = fopen("input.txt", "r");
    FILE *fileOut = fopen("output.txt", "w");

    int nWorks, mWorkers;
    fscanf(fileIn, "%d %d", &nWorks, &mWorkers);

    set<pair<long long, int>, descendingComparison> worksSet;

    long long temp;
    for (int i = 0; i < nWorks; ++i) {
        fscanf(fileIn, "%lld", &temp);
        worksSet.insert(make_pair(temp, i));
    }

    set<pair<long long, int>> workersSet;

    for (int i = 0; i < mWorkers; ++i) {
        workersSet.insert(make_pair(0, i));
    }

    vector<int> workerForWork(nWorks, 0);

    long long currentTimeOfWork;
    int currentIndexOfWork;

    long long workerTime;
    int workerIndex;

    //Main part of algorithm
    while (!worksSet.empty()) {
        currentTimeOfWork = worksSet.begin()->first;
        currentIndexOfWork = worksSet.begin()->second;

        worksSet.erase(worksSet.begin());

        //Getting the less busy worker
        workerTime = workersSet.begin()->first;
        workerIndex = workersSet.begin()->second;

        workersSet.erase(workersSet.begin());

        workerTime += currentTimeOfWork;
        workerForWork[currentIndexOfWork] = workerIndex + 1;

        workersSet.insert(make_pair(workerTime, workerIndex));
    }

    //The less busy worker will be the first in the set
    fprintf(fileOut, "%lld\n", workersSet.begin()->first);

    workersSet.clear();

    for (int i = 0; i < nWorks; ++i) {
        fprintf(fileOut, "%d\n", workerForWork[i]);
    }

    fclose(fileIn);
    fclose(fileOut);
    return 0;
}