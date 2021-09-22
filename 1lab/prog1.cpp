#include <iostream>
#include <cstring>
#include <limits>
#include "prog1.h"

namespace prog1{
	constexpr int BUF_SIZE = 80;

	char isWrongMatrix(const Matrix& matrix){
		if(matrix.m == -1){
			return 1;
		}
		return 0;
	}

	Matrix new_read() {
		Matrix matrix;
		Matrix wrong_matrix;
		wrong_matrix.m = -1;
		const char* pr = "";
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter number of lines: --> ";
			pr = "You are wrong; repeat please!";
			if (getNum(matrix.m) < 0)
				return wrong_matrix;
		} while (matrix.m < 1);

		int k;
		pr = "";
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter number of columns: --> ";
			pr = "You are wrong; repeat please!";
			if (getNum(k) < 0)
				return wrong_matrix;
		} while (k < 1);

		int n;
		pr = "";
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter number of non-zero items: --> ";
			pr = "You are wrong; repeat please!";
			if (getNum(n) < 0)
				return wrong_matrix;
		} while (n < 1);

		try {
			matrix.numbers = new int[n];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			return wrong_matrix;
		}

		try {
			matrix.column_indexes = new int[n];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			delete[] matrix.numbers;
			return wrong_matrix;
		}

		try {
			matrix.raw_indexes = new int[matrix.m + 1];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			delete[] matrix.numbers;
			delete[] matrix.column_indexes;
			return wrong_matrix;
		}


		for (int i = 0; i < matrix.m + 1; i++) matrix.raw_indexes[i] = 0;

		try {
			matrix.sizes = new int[matrix.m];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			delete[] matrix.numbers;
			delete[] matrix.column_indexes;
			delete[] matrix.raw_indexes;
			return wrong_matrix;
		}

		for (int i = 0; i < matrix.m; i++) {
			matrix.sizes[i] = k;
		}

		int token, col_ind = -1, cur_col_ind, raw_ind = -1, cur_raw_ind;
		std::cout << "Enter items from left to right and from up to down\n";
		for (int i = 0; i < n; i++) {
			const char* er = "";
			do {
				std::cout << er << std::endl;
				er = "zero item";
				std::cout << "Enter number: ";
				if (getNum(token) < 0) {
					remove(matrix);
					return wrong_matrix;
				}
			} while (token == 0);
			er = "";
			cur_col_ind = col_ind;
			do {
				std::cout << er << std::endl;
				er = "bad index";
				std::cout << "Enter horizontal index: ";
				if (getNum(col_ind) < 0) {
					remove(matrix);
					return wrong_matrix;
				}
			} while (col_ind < 0 || col_ind >= k);
			cur_raw_ind = raw_ind;
			er = "";
			do {
				std::cout << er << std::endl;
				er = "bad index";
				std::cout << "Enter vertical index: ";
				if (getNum(raw_ind) < 0) {
					remove(matrix);
					return wrong_matrix;
				}
			} while (raw_ind < 0 || raw_ind >= matrix.m);

			if (cur_col_ind != -1 && cur_raw_ind != -1 && (raw_ind * k + col_ind) <= (cur_raw_ind * k + cur_col_ind)) {
				std::cout << "bad position";
				remove(matrix);
				return wrong_matrix;
			}

			matrix.numbers[i] = token;
			matrix.column_indexes[i] = col_ind;
			for (int i = raw_ind + 1; i < matrix.m + 1; i++) matrix.raw_indexes[i]++;

		}
		return matrix;
	}

	void new_output(Matrix matrix) {
		int raw_counter = -1;
		for (int i = 0; i < matrix.raw_indexes[matrix.m]; i++) {
			if (i == matrix.raw_indexes[raw_counter + 1]) raw_counter++;
			std::cout << matrix.numbers[i] << " (" << matrix.column_indexes[i] << ", " << raw_counter << "); " << std::endl;
		}
	}

	void Matrix read1() {
		Matrix matrix;
		Matrix wrong_matrix;
		wrong_matrix.m = -1;
		const char* pr = "";

		do {
			std::cout << pr << std::endl;
			std::cout << "Enter number of lines: --> ";
			pr = "You are wrong; repeat please!";
			if (getNum(matrix.m) < 0)
				return wrong_matrix;
		} while (matrix.m < 1);

		int k;
		pr = "";
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter number of columns: --> ";
			pr = "You are wrong; repeat please!";
			if (getNum(k) < 0)
				return wrong_matrix;
		} while (k < 1);

		int n;
		pr = "";
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter number of items: --> ";
			pr = "You are wrong; repeat please!";
			if (getNum(n) < 0)
				return wrong_matrix;
		} while (n < 1);

		try {
			matrix.numbers = new int[n];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			return wrong_matrix;
		}

		try {
			matrix.column_indexes = new int[n];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			delete[] matrix.numbers;
			return wrong_matrix;
		}

		try {
			matrix.raw_indexes = new int[matrix.m + 1];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			delete[] matrix.numbers;
			delete[] matrix.column_indexes;
			return wrong_matrix;
		}


		matrix.raw_indexes[0] = 0;
		try {
			matrix.sizes = new int[matrix.m];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			delete[] matrix.numbers;
			delete[] matrix.column_indexes;
			delete[] matrix.raw_indexes;
			return wrong_matrix;
		}

		std::cout << "Enter items: -->";

		for (int i = 0; i < n; i++) {
			int token;
			if (getNum(token) < 0) {
				remove(matrix);
				return wrong_matrix;
			}
			matrix.numbers[i] = token;
		}

		std::cout << "Enter column indexes: -->";

		for (int i = 0; i < n; i++) {
			int token;
			if (getNum(token) < 0 || token < 0) {
				remove(matrix);
				return wrong_matrix;
			}
			matrix.column_indexes[i] = token;
		}

		std::cout << "Enter raw's shifts: -->";

		int last_token = 0;
		for (int i = 0; i < matrix.m + 1; i++) {
			int token;
			if (getNum(token) < 0 || token < last_token) {
				remove(matrix);
				return wrong_matrix;
			}
			matrix.raw_indexes[i] = token;
		}
		for (int i = 0; i < matrix.m; i++) {
			matrix.sizes[i] = k;
		}
		return matrix;
	}

	void output1(const Matrix& matrix) {
		std::cout << matrix.raw_indexes[matrix.m] << std::endl;
		for (int i = 0; i < matrix.raw_indexes[matrix.m]; i++) {
			std::cout << matrix.numbers[i] << ", ";
		}
		std::cout << std::endl;
		for (int i = 0; i < matrix.raw_indexes[matrix.m]; i++) {
			std::cout << matrix.column_indexes[i] << ", ";
		}
		std::cout << std::endl;
		for (int i = 0; i < matrix.m + 1; i++) {
			std::cout << matrix.raw_indexes[i] << ", ";
		}
		std::cout << std::endl;
		for (int i = 0; i < matrix.m; i++) {
			std::cout << matrix.sizes[i] << ", ";
		}
		std::cout << std::endl;
	}
	
	Matrix read(){
		const char* pr = "";
		Matrix wrong_matrix;
		wrong_matrix.m = -1;

		Matrix matrix;

		int counter = 0;
		int matrix_size = 0;

		do{
			std::cout << pr << std::endl;
			std::cout << "Enter number of lines: --> ";
			pr = "You are wrong; repeat please!";
			if (getNum(matrix.m) < 0)
				return wrong_matrix;
		}while (matrix.m < 1);

		
		try{
			matrix.numbers = new int[BUF_SIZE];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			return wrong_matrix;
		}

		try {
			matrix.column_indexes = new int[BUF_SIZE];
		}
		catch (std::bad_alloc& ba) {
			std::cout <<  ba.what() << std::endl;
			delete[] matrix.numbers;
			return wrong_matrix;
		}

		try {
			matrix.raw_indexes = new int[matrix.m + 1];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			delete[] matrix.numbers;
			delete[] matrix.column_indexes;
			return wrong_matrix;
		}


		matrix.raw_indexes[0] = 0;
		try {
			matrix.sizes = new int[matrix.m];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			delete[] matrix.numbers;
			delete[] matrix.column_indexes;
			delete[] matrix.raw_indexes;
			return wrong_matrix;
		}
		matrix_size = BUF_SIZE;

		for(int i = 0; i < matrix.m; i++){
			pr = "";
			do{
				std::cout << pr << std::endl;
				std::cout << "Enter number of items in line #" << (i + 1) << " --> ";
				pr = "You are wrong; repeat please!";
				if (getNum(matrix.sizes[i]) < 0){
					remove(matrix);
					return wrong_matrix;
				}
			}while(matrix.sizes[i] < 1);

			std::cout << "Enter items for matrix line #" << (i + 1) << ":";
			
			for(int j = 0; j < matrix.sizes[i]; j++){
				int token;
				if (getNum(token) < 0){
					remove(matrix);
					return wrong_matrix;
				}
				if(token != 0){
					matrix.numbers[counter] = token;
					matrix.column_indexes[counter] = j;
					counter++;

					if(counter == matrix_size){
						matrix_size += BUF_SIZE;
						int* numbers_tmp;
						int* columns_tmp;
						try {
							numbers_tmp = new int[matrix_size];
						}
						catch (std::bad_alloc& ba) {
							std::cout << ba.what() << std::endl;
							remove(matrix);
							return wrong_matrix;
						}
						try {
							columns_tmp = new int[matrix_size];
						}
						catch (std::bad_alloc& ba) {
							std::cout << ba.what() << std::endl;
							delete[] numbers_tmp;
							remove(matrix);
							return wrong_matrix;
						}
						memmove(numbers_tmp, matrix.numbers, (matrix_size - BUF_SIZE) * sizeof(int));
						memmove(columns_tmp, matrix.column_indexes, (matrix_size - BUF_SIZE) * sizeof(int));
						delete[] matrix.numbers;
						delete[] matrix.column_indexes;
						matrix.numbers = numbers_tmp;
						matrix.column_indexes = columns_tmp;
					}
				}
			}

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			matrix.raw_indexes[i + 1] = counter;
		}

		std::cout << std::endl;

		return matrix;
	}

	void output(const Matrix& matrix){
		if(matrix.m == -1){
			std::cout << "Wrong matrix";
			return;
		}
		int counter = 0;

		for(int i = 0; i < matrix.m; i++){
			for(int j = 0; j < matrix.sizes[i]; j++){
				if(matrix.column_indexes[counter] == j && counter < matrix.raw_indexes[i + 1]){
					std::cout << matrix.numbers[counter] << " ";
					counter++;
				}
				else{
					std::cout << "0 ";
				}
			}
			std::cout << std::endl;
		}
	}

	int find_absolute_min_index(int* numbers, int* column_indexes, int first_index, int second_index, int size){
		int counter = first_index;
		int token;

		int min_number = std::numeric_limits<int>::max();
		int min_index = -1;

		for(int i = 0; i < size; i++){
			if(i == second_index - first_index && i != size && 0 < min_number){
				return i;
			}

			if(i == column_indexes[counter]){
				token = numbers[counter];
				counter++;
			}else{
				token = 0;
			}

			if(token < min_number){
				min_number = token;
				min_index = i;
			}
		}

		return min_index;
	}

	int find_relative_min_index(int* column_indexes, int first_index, int second_index, int absolute_min_index){
		int counter;
		for(counter = first_index; counter < second_index; counter++){
			if(column_indexes[counter] >= absolute_min_index){
				break;
			}
		}
		return counter;
	}

	Matrix change(const Matrix& matrix){
		Matrix new_matrix;
		Matrix wrong_matrix;
		wrong_matrix.m = -1;
		try {
			new_matrix.numbers = new int[BUF_SIZE];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			return wrong_matrix;
		}

		try {
			new_matrix.column_indexes = new int[BUF_SIZE];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			delete[] new_matrix.numbers;
			return wrong_matrix;
		}

		try {
			new_matrix.raw_indexes = new int[matrix.m + 1];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			delete[] new_matrix.numbers;
			delete[] new_matrix.column_indexes;
			return wrong_matrix;
		}


		new_matrix.raw_indexes[0] = 0;
		try {
			new_matrix.sizes = new int[matrix.m];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			delete[] new_matrix.numbers;
			delete[] new_matrix.column_indexes;
			delete[] new_matrix.raw_indexes;
			return wrong_matrix;
		}
		int new_matrix_size = BUF_SIZE;
		
		int counter = 0;
		int min_index;


		for(int i = 0; i < matrix.m; i++){
			int first_index = matrix.raw_indexes[i];
			int second_index = matrix.raw_indexes[i + 1];

			int delta = find_absolute_min_index(matrix.numbers, matrix.column_indexes, first_index, second_index, matrix.sizes[i]);

			int relative_min_index = find_relative_min_index(matrix.column_indexes, first_index, second_index, delta);

			for(int j = relative_min_index; j < second_index; j++){
				new_matrix.numbers[counter] = matrix.numbers[j];
				new_matrix.column_indexes[counter] = matrix.column_indexes[j] - delta;
				counter++;

				if(counter == new_matrix_size){
					new_matrix_size += BUF_SIZE;
					int* numbers_tmp;
					int* columns_tmp;
					try {
						numbers_tmp = new int[new_matrix_size];
					}
					catch (std::bad_alloc& ba) {
						std::cout << ba.what() << std::endl;
						remove(new_matrix);
						return wrong_matrix;
					}
					try {
						columns_tmp = new int[new_matrix_size];
					}
					catch (std::bad_alloc& ba) {
						std::cout << ba.what() << std::endl;
						delete[] numbers_tmp;
						remove(new_matrix);
						return wrong_matrix;
					}
					memmove(numbers_tmp, new_matrix.numbers, (new_matrix_size - BUF_SIZE) * sizeof(int));
					memmove(columns_tmp, new_matrix.column_indexes, (new_matrix_size - BUF_SIZE) * sizeof(int));
					delete[] new_matrix.numbers;
					delete[] new_matrix.column_indexes;
					new_matrix.numbers = numbers_tmp;
					new_matrix.column_indexes = columns_tmp;
				}
			}
			new_matrix.raw_indexes[i + 1] = counter;
			new_matrix.sizes[i] = matrix.sizes[i] - delta;
		}
		return new_matrix;
	}

	void remove(Matrix& matrix){
		delete[] matrix.numbers;
		delete[] matrix.column_indexes;
		delete[] matrix.raw_indexes;
		delete[] matrix.sizes;
	}
}