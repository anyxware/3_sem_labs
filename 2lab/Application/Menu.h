#include "../Library/Line.h"

class Menu
{
private:
	Line line;

	bool case_1();
	bool case_2();
	bool case_3();
	bool case_4();
	bool case_5();
	bool case_6();
public:
	void output();
	int get_answer();
	bool execute(int answer);
};

