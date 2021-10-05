#pragma once
#include "../Library/Vector.h"

namespace Static {
	class Menu
	{
	private:
		Vector v1;
		Vector v2;
		bool case1();
		bool case2();
		bool case3();
		bool case4();
		bool case5();
		bool case6();
	public:
		void output();
		int getAnswer();
		bool execute(int answer);
	};
}

namespace Dynamic {
	class Menu
	{
	private:
		Vector v1;
		Vector v2;
		bool case1();
		bool case2();
		bool case3();
		bool case4();
		bool case5();
		bool case6();
	public:
		void output();
		int getAnswer();
		bool execute(int answer);
	};
}


