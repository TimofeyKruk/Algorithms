#include <iostream>
#include <stack>

using namespace std;

int main() {
    FILE *fileIn = fopen("input.txt", "r");
    FILE *fileOut = fopen("output.txt", "w");

    int n;
    fscanf(fileIn, "%d", &n);

    int counter = 0;
    int whatIsUp;
    double x, y;
    int previous;
    stack<int> intersections;


    //if odd then stop, it is impossible
    if (n % 2 != 0) {
        fprintf(fileOut, "%s", "No");
    } else {
        for (int i = 0; i < n; ++i) {
            fscanf(fileIn, "%f %f %d", &x, &y, &whatIsUp);

            if (!intersections.empty()) {
                previous = intersections.top();
                intersections.pop();

                if (previous != whatIsUp) {
                intersections.push(previous);
                intersections.push(whatIsUp);
                }
            } else
                intersections.push(whatIsUp);

        }

        if(intersections.empty())
            fprintf(fileOut, "%s", "Yes");
        else
            fprintf(fileOut, "%s", "No");

    }



    fclose(fileIn);
    fclose(fileOut);
    return 0;
}