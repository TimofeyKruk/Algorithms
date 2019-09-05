#include<iostream>
#include<fstream>

using namespace std;


int findSolution(int s, int *array)
{
	int result = 0;

	//upper-triangle matrix
	int **minMatrix = new int* [s];
	for (int i = 0; i < s; ++i)
		minMatrix[i] = new int[s];

	int min;
	int temp;
	//will fill this matrix by diagonals
	for (int diagonal = 0; diagonal < s; ++diagonal)
	{
		for (int i = 0, j = diagonal; (i < s && j < s); ++i, ++j)
		{
			if (i == j) minMatrix[i][j] = 0;
			else
			{
				min =INT_MAX;
				for (int k = i; k < j; ++k)
				{
					temp = minMatrix[i][k] + minMatrix[k + 1][j];
					//Array length = (s+1); so matrix Ai has sizes: array[i]*array[i+1]
					temp += array[i] * array[k+1] * array[j+1];

					if (temp < min)
						min = temp;
				}

				minMatrix[i][j] = min;
			}
		}
	}

	//Saving result
	result = minMatrix[0][s - 1];

	//Deletion of matrix
	for (int i = 0; i < s; ++i)
		delete [] minMatrix[i];
	delete [] minMatrix;

	return result;
}

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int s;//Quantity of matrix
	fin >> s;

	int* matrixSizes = new int[s+1];
	int size;

	//Matrix Ai has size array[i-1]*array[i]
	for (int i = 0; i < s; ++i)
	{
		fin >> size;
		matrixSizes[i] = size;
		fin >> size;	//It will be still duplicated in next line (ignoring it here)
	}
	matrixSizes[s] = size;	//For last one that won't be duplicated

	//Here we find the answer
	int result = findSolution(s,matrixSizes);

	fout << result;

	delete[] matrixSizes;

	fin.close();
	fout.close();
	return 0;
}