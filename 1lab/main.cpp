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

	output(matrix);

	Matrix new_matrix = change(matrix);

	output(new_matrix);
	remove(matrix);
	remove(new_matrix);
	}

	return 0;
}