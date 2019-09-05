#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	ifstream fin("input.txt");
	FILE* output = fopen("output.txt", "w");
	bool isHeap=true;
	
	int n;
	fin >> n;

	int* array = new int[n];
	int temp;
	for (int i = 0; i < n; ++i)
	{
		fin >> temp;
		array[i] = temp;
	}
		
	int sonOne;
	int sonTwo;
	for (int i = 1; i <= n; ++i)
	{
		if (2 * i <= n)
		{
			sonOne = array[2 * i-1];
			if (sonOne < array[i-1])
			{
				isHeap = false;
				break;
			}
		}
		else break;

		if ((2 * i + 1) <= n)
		{
			sonTwo = array[2 * i + 1-1];
			if (sonTwo < array[i-1])
			{
				isHeap = false;
				break;
			}
		}
	}

	//results
	if (isHeap)
		fprintf(output, "%s", "Yes");
	else
		fprintf(output, "%s", "No");

	delete[] array;
	fin.close();
	fclose(output);
	return 0;
}