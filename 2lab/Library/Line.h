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

typedef struct {
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
	bool set_radius(double input_radius = 1);

	double distance(double phi) const;
	Coords* farthest_points() const;
	double curvature(double phi) const;
	double area(double phi1, double phi2) const;
	double length(double phi1, double phi2) const;
};

#endif // LINE_H



