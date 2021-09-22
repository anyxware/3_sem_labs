#ifndef LINE_H
#define LINE_H
/*
* ¬ариант 7.  ардиоида
–азработать класс, определ€ющий кривую Ц кардиоиду.
1) ќпределить состо€ние класса.
2) –азработать необходимые конструкторы и методы получени€ и изменени€ параметров, определ€ющих кривую.
3) ¬ернуть рассто€ние до центра в пол€рной системе координат в зависимости от угла дл€ точки принадлежащей кардиоиде.
4) ¬ернуть координаты наиболее удаленных от оси кардиоиды точек.
5) ¬ернуть радиуса кривизны в характерных точках кардиоиды.
6) ¬ернуть площадь описываемую кардиоидой.
7) ¬ернуть длину дуги кардиоиды в зависимости от угла пол€рного радиуса.
–азработать диалоговую программу дл€ тестировани€ класса.
*/

typedef struct Coords{
	double x;
	double y;
} Coords;

class Line
{
private:
	double radius;
public:
	Line(double input_radius = 1);

	double get_radius() const { return radius; }
	void set_radius(double input_radius = 1);

	double distance(double phi) const;
	void farthest_points(Coords& coords1, Coords& coords2) const;
	double curvature(double phi) const;
	double area(double phi1, double phi2) const;
	double length(double phi1, double phi2) const;
};

#endif // LINE_H



