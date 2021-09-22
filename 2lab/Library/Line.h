#ifndef LINE_H
#define LINE_H
/*
* ������� 7. ���������
����������� �����, ������������ ������ � ���������.
1) ���������� ��������� ������.
2) ����������� ����������� ������������ � ������ ��������� � ��������� ����������, ������������ ������.
3) ������� ���������� �� ������ � �������� ������� ��������� � ����������� �� ���� ��� ����� ������������� ���������.
4) ������� ���������� �������� ��������� �� ��� ��������� �����.
5) ������� ������� �������� � ����������� ������ ���������.
6) ������� ������� ����������� ����������.
7) ������� ����� ���� ��������� � ����������� �� ���� ��������� �������.
����������� ���������� ��������� ��� ������������ ������.
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



