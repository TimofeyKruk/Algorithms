#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct point {
    int value;
    int x;
    int y;

    point(const int v, const int x1, const int y1) {
        this->value = v;
        this->x = x1;
        this->y = y1;
    }

    point(int x1, int y1) {
        this->value = 0;
        this->x = x1;
        this->y = y1;
    }
};

class BinaryHeap {
private:
    vector<point> heapArray;
    int size;
    int lastIndex;

public:
    BinaryHeap(int size, vector<point> data)    //And creation with O(n)
    {
        lastIndex = 0;
        this->size = size;
        point defaultPoint(0, 0, 0);
        heapArray.resize(size, defaultPoint);

        while (lastIndex != data.size()) {
            point p = data[lastIndex];
            heapArray[lastIndex] = p;
            lastIndex++;
        }

        creation(); // working for O(n)
    }

    void creation() {
        int startIndex = lastIndex / 2;
        for (int i = startIndex; i >= 0; --i)
            moveDown(i);
    }

    point getMinElement() {
        if (!empty()) {
            point minPoint = heapArray[0];//always in the beginning

            //deleting and moving down
            swap(0, lastIndex - 1);
            --lastIndex;//kind of deleting the element

            moveDown(0);

            return minPoint;
        }

        point p(-1, 0, 0);//else
        return p;
    }

    void addElement(point newPoint) {
        heapArray[lastIndex] = newPoint;
        lastIndex++;
        moveUP(lastIndex - 1);
    }

    void moveUP(int currentIndex) {
        if (currentIndex == 0) //root
            return;

        int father = (currentIndex - 1) / 2;

        if (heapArray[father].value > heapArray[currentIndex].value) {
            swap(father, currentIndex);
            moveUP(father);
        }
    }

    void moveDown(int currentIndex) {
        int childLeft = 2 * currentIndex + 1;
        int childRight = 2 * currentIndex + 2;
        int whatIsSmaller = heapArray[currentIndex].value;
        bool isItRight = false;
        bool isSwapNeeded = false;

        if (childLeft < lastIndex) //exists
        {
            if (heapArray[childLeft].value < whatIsSmaller) {
                whatIsSmaller = heapArray[childLeft].value;
                isSwapNeeded = true;
            }
        }
        if (childRight < lastIndex) //exists
        {
            if (heapArray[childRight].value <= whatIsSmaller) {
                isItRight = true;
                isSwapNeeded = true;
            }
        }

        if (isSwapNeeded) {
            if (isItRight) {
                swap(currentIndex, childRight);
                moveDown(childRight);
            } else {
                swap(currentIndex, childLeft);   //left
                moveDown(childLeft);
            }
        }
    }

    void swap(int xIndex, int yIndex) {
        point temp = heapArray[xIndex];
        heapArray[xIndex] = heapArray[yIndex];
        heapArray[yIndex] = temp;
    }

    bool empty() {
        return lastIndex == 0;
    }
};


int main() {
    FILE *fileIn = fopen("in.txt", "r");
    FILE *fileOut = fopen("out.txt", "w");

    int n, m, iStart, jStart, givenVolume;
    fscanf(fileIn, "%d %d", &n, &m);
    fscanf(fileIn, "%d %d %d", &iStart, &jStart, &givenVolume);
    iStart--;
    jStart--;

    int **form = new int *[n];
    int **waterLevelForm = new int *[n];
    bool **isVisited = new bool *[n];
    bool **isVisitedSecondly = new bool *[n];

    for (int i = 0; i < n; ++i) {
        form[i] = new int[m];
        waterLevelForm[i] = new int[m];
        isVisited[i] = new bool[m];
        isVisitedSecondly[i] = new bool[m];

        for (int j = 0; j < m; ++j) {
            fscanf(fileIn, "%d", &form[i][j]);
            waterLevelForm[i][j] = INT_MAX;
            isVisited[i][j] = false;
            isVisitedSecondly[i][j] = false;
        }

    }


    vector<point> data;
    //Putting all border points in priority queue with the priority(water level) equals to the point height
    for (int i = 0; i < n; ++i) {
        waterLevelForm[i][0] = form[i][0];
        point p1(waterLevelForm[i][0], i, 0);
        data.push_back(p1);

        waterLevelForm[i][m - 1] = form[i][m - 1];
        point p2(waterLevelForm[i][m - 1], i, m - 1);
        data.push_back(p2);
    }
    for (int j = 1; j < m - 1; ++j) {
        waterLevelForm[0][j] = form[0][j];
        point p3(waterLevelForm[0][j], 0, j);
        data.push_back(p3);

        waterLevelForm[n - 1][j] = form[n - 1][j];
        point p4(waterLevelForm[n - 1][j], n - 1, j);
        data.push_back(p4);
    }



    //Binary HEAP as priority queue
    BinaryHeap binaryHeap(4 * n * m, data);

    int currentPriority, newPriority, currentX, currentY;


    //Main part of algorithm solving form with immersion
    while (!binaryHeap.empty()) {
        point currentPoint = binaryHeap.getMinElement();

        currentPriority = currentPoint.value;
        currentX = currentPoint.x;
        currentY = currentPoint.y;

        if (!isVisited[currentX][currentY])  //else ignore
        {
            waterLevelForm[currentX][currentY] = currentPriority;
            isVisited[currentX][currentY] = true;

            //Working with neighbours
            //LEFT
            if (currentY - 1 >= 0) {
                if (waterLevelForm[currentX][currentY - 1] > waterLevelForm[currentX][currentY]) //else ignore
                {
                    newPriority = std::max(waterLevelForm[currentX][currentY], form[currentX][currentY - 1]);
                    point p(newPriority, currentX, currentY - 1);
                    binaryHeap.addElement(p);
                }
            }
            //RIGHT
            if (currentY + 1 < m) {
                if (waterLevelForm[currentX][currentY + 1] > waterLevelForm[currentX][currentY]) //else ignore
                {
                    newPriority = std::max(waterLevelForm[currentX][currentY], form[currentX][currentY + 1]);
                    point p(newPriority, currentX, currentY + 1);
                    binaryHeap.addElement(p);
                }
            }
            //UP
            if (currentX - 1 >= 0) {
                if (waterLevelForm[currentX - 1][currentY] > waterLevelForm[currentX][currentY]) //else ignore
                {
                    newPriority = std::max(waterLevelForm[currentX][currentY], form[currentX - 1][currentY]);
                    point p(newPriority, currentX - 1, currentY);
                    binaryHeap.addElement(p);
                }
            }
            //DOWN
            if (currentX + 1 < n) {
                if (waterLevelForm[currentX + 1][currentY] > waterLevelForm[currentX][currentY]) //else ignore
                {
                    newPriority = std::max(waterLevelForm[currentX][currentY], form[currentX + 1][currentY]);
                    point p(newPriority, currentX + 1, currentY);
                    binaryHeap.addElement(p);
                }
            }
        }
    }

    int waterPossiblyLeft = 0;

    //NOW SOLVING TASK FORM WITHOUT IMMERSION
    //Checking how much water will be left if we start to pour from iStart, jStart
    queue<point *> pouringQueue;
    pouringQueue.push(new point(iStart, jStart));
    //visited
    isVisitedSecondly[iStart][jStart] = true;

    point *pointPouring;
    while (!pouringQueue.empty()) {
        pointPouring = pouringQueue.front();
        currentX = pointPouring->x;
        currentY = pointPouring->y;

        pouringQueue.pop();

        waterPossiblyLeft += waterLevelForm[currentX][currentY] - form[currentX][currentY];

        //Working with neighbours
        //LEFT
        if (currentY - 1 >= 0 && !isVisitedSecondly[currentX][currentY - 1]) {
            if (waterLevelForm[currentX][currentY - 1] <= waterLevelForm[currentX][currentY]) //else ignore
            {
                isVisitedSecondly[currentX][currentY - 1] = true;
                pouringQueue.push(new point(currentX, currentY - 1));
            }
        }
        //RIGHT
        if (currentY + 1 < m && !isVisitedSecondly[currentX][currentY + 1]) {
            if (waterLevelForm[currentX][currentY + 1] <= waterLevelForm[currentX][currentY]) //else ignore
            {
                isVisitedSecondly[currentX][currentY + 1] = true;
                pouringQueue.push(new point(currentX, currentY + 1));
            }
        } //UP
        if (currentX - 1 >= 0 && !isVisitedSecondly[currentX - 1][currentY]) {
            if (waterLevelForm[currentX - 1][currentY] <= waterLevelForm[currentX][currentY]) //else ignore
            {
                isVisitedSecondly[currentX - 1][currentY] = true;
                pouringQueue.push(new point(currentX - 1, currentY));
            }
        }
        //DOWN
        if (currentX + 1 < n && !isVisitedSecondly[currentX + 1][currentY]) {
            if (waterLevelForm[currentX + 1][currentY] <= waterLevelForm[currentX][currentY]) //else ignore
            {
                isVisitedSecondly[currentX + 1][currentY] = true;
                pouringQueue.push(new point(currentX + 1, currentY));
            }
        }

    }

    //ANSWER
    fprintf(fileOut, "%d", std::min(waterPossiblyLeft, givenVolume));
    //Deleting
    for (int i = 0; i < n; ++i) {
        delete[] form[i];
        delete[] waterLevelForm[i];
        delete[] isVisited[i];
        delete[] isVisitedSecondly[i];
    }
    delete[] form;
    delete[] waterLevelForm;
    delete[] isVisited;
    delete[] isVisitedSecondly;

    fclose(fileIn);
    fclose(fileOut);
    return 0;
}