#include<iostream>
#include<fstream>

using namespace std;
//To find solution we will work with binary representation of a number
int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    long long n;
    fin>>n;

    //In binary representation we need indexes of position where 1 stands(these indexes are an answer)
    int indexOfOne=0;
    while(n!=0)
    {
        if(n%2)
            fout<<indexOfOne<<'\n';

        n=n/2;
        ++indexOfOne;
    }

    fin.close();
    fout.close();
    return 0;
}
