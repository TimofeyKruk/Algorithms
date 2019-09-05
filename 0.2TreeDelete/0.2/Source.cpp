#include<iostream>
#include<fstream>

//delete for system
#include "Tree.h"

using namespace std;

int main()
{
	FILE* input = fopen("input.txt", "r");
	FILE* output = fopen("output.txt", "w");
	
	Tree binaryTree;
	int toDelete;
	fscanf(input, "%d", &toDelete);

	int newKey;
	while (fscanf(input, "%d", &newKey) != EOF)
		binaryTree.insertVertex(newKey);

	binaryTree.deleteVertex(toDelete);

	binaryTree.printTree(output);

	fclose(input);
	fclose(output);
	return 0;
}