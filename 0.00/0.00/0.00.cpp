	#include "stdafx.h"
	#include <iostream>
	#include <set>
	using namespace std;

	int main()
	{
		FILE *input=fopen("input.txt", "r");
		FILE *output=fopen("output.txt","w");
	
		long long summ = 0;

		set<int> base;
		set<int>::iterator it;

		int current;

		while (fscanf(input, "%d", &current) != EOF)
			base.insert(current);

		for (it=base.begin(); it!=base.end(); it++)
			summ += *it;
	
		fprintf(output, "%lld", summ);

		fclose(input);
		fclose(output);
	
		return 0;
	}

