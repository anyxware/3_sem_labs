namespace prog1{
	struct Matrix{
		int m;
		int* numbers;
		int* column_indexes;
		int* raw_indexes;
		int* sizes;
	};

	template <class T>
	int getNum(T &a)
	{
		std::cin >> a;
		if (!std::cin.good())
			return -1;
		return 1;
	}

	
	char isWrongMatrix(Matrix matrix);
	Matrix read();
	void output(Matrix matrix);
	Matrix read();
	void output(Matrix matrix);
	Matrix change(Matrix matrix);
	void remove(Matrix matrix);
}