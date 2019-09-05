#include <iostream>
#include <fstream>

using namespace std;

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");



    fclose(inputFile);
    fclose(outputFile);
    return 0;
}