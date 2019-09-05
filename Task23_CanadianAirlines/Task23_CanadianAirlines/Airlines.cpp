#include<iostream>
#include<fstream>

using namespace std;

int getIndex(char** cityNames,int n, char* city)
{
	for (int i = 0; i < n; ++i)
		if (strcmp(cityNames[i], city) == 0)
			return i;

	return -1;
}

int findSolution(int n, int** flights)
{
	int maxCitiesVisited;

	//This matrix is symmetrical
	int** maxRoutes = new int*[n];
	for (int i = 0; i < n; ++i)
	{
		maxRoutes[i] = new int[n];
		for (int j = 0; j < n; ++j)
			maxRoutes[i][j] = 0;
	}
	int temp;
	//Starting from the end
	maxRoutes[n - 1][n - 1] = 1;
	//____MAIN PART OF ALGORITHM____
	for (int i = n - 2; i >= 0; --i)
	{
		for (int j = n - 1; j > i; --j)
		{
			temp = -1;//-1 means  that way is impossible
			for (int k = i + 1; k < n; ++k)
				if (flights[i][k] == 1 && (k != j || j==n-1))
				{
					//finding max posiible route
					if (k <= j)
					{
						//maxRoutes is symmetrical. Initialized on;y upper part of matrix,
						//so the following clause must be
						if (maxRoutes[k][j] > temp)
							temp = maxRoutes[k][j];
					}
					else
					{	
						if (maxRoutes[j][k] > temp)
							temp = maxRoutes[j][k];
					}								
				}
			
			if (temp == -1)
				maxRoutes[i][j] = -1;
			else
				maxRoutes[i][j] = temp + 1;
		}
	}
	//Separately for route (0city, 0city) <--it will be answer
	temp = -1;
	for (int k = 1; k < n; ++k)
		if (flights[0][k] == 1)		
				if (maxRoutes[0][k] > temp) 
					temp = maxRoutes[0][k];//Here we don't have to add 1, as first city must be counted only once 
					//Logically, here should be maxRoutes[k][0], 
					//but by the current realization(upper triangle matrix) indexes were reflected 
	maxRoutes[0][0] = temp;//<- ANSWER, if =-1 then no solution
	
	maxCitiesVisited = maxRoutes[0][0];

	for (int i = 0; i < n; ++i)
		delete[] maxRoutes[i];
	delete[] maxRoutes;

	return maxCitiesVisited;
}


int main()
{
	ifstream fin("in.txt");
	ofstream fout("out.txt");

	int n, m;
	fin >> n;//quantity of cities
	fin >> m;//quantity of direct flights
	
	//Initialization of cityNames array
	char** cityNames = new char*[n];
	for (int i = 0; i < n; ++i)
	{
		cityNames[i] = new char[15];
		fin >> cityNames[i];
	}


	//Flights matrix
	int** flights = new int*[n];
	for (int i = 0; i < n; ++i)
	{
		flights[i] = new int[n];
		for (int j = 0; j < n; ++j)
			flights[i][j] = 0;
	}

	for (int i = 0; i < m; ++i)
	{
		char cityA[15], cityB[15];
		fin >> cityA >> cityB;
		int a = getIndex(cityNames, n, cityA);
		int b = getIndex(cityNames, n, cityB);
		if (a < b)
			flights[a][b] = 1;
		else
			flights[b][a] = 1;

	}
	
		
	//Finding solution
	int answer = findSolution(n, flights);
	//Output to file
	if (answer != -1)
		fout << answer;
	else
		fout << "No solution";

	//Deleting 
	for (int i = 0; i < n; ++i)
		delete[] cityNames[i];
	delete[] cityNames;

	for (int i = 0; i < n; ++i)
		delete[] flights[i];
	delete[] flights;

	fin.close();
	fout.close();
	return 0;
}