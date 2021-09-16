#include <iostream>
#include "prog1.h"

using namespace std;


int main(int argc, char const *argv[])
{
	{

	using namespace prog1;
	
	Matrix matrix = read();

	if(isWrongMatrix(matrix)){
		printf("Wrong matrix\n");
		return 1;
	}

	/*
	cout << matrix.m << endl;

	for(int i = 0; i < matrix.raw_indexes[matrix.m]; i++){
		cout << matrix.numbers[i] << " ";
	}

	cout << endl;

	for(int i = 0; i < matrix.raw_indexes[matrix.m]; i++){
		cout << matrix.column_indexes[i] << " ";
	}

	cout << endl;

	for(int i = 0; i < matrix.m + 1; i++){
		cout << matrix.raw_indexes[i] << " ";
	}

	cout << endl;
	*/

	output(matrix);

	Matrix new_matrix = change(matrix);

	output(new_matrix);
	remove(matrix);
	remove(new_matrix);
	}

	return 0;
}