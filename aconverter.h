#ifndef ACONVERTER_H
#define ACONVERTER_H
#include <cmath>

//constexpr double PI = 3.1415926;
class  Aconverter{
	public:
	Aconverter() = default;
	Aconverter(double a /*grader*/, double vel, int rel=200) : angle{a*(PI/180.0)}, velocity{vel}, relation{rel} {}
	double x_velocity() {
		return velocity*cos(angle);
	}
	double y_velocity() {
		return velocity*sin(angle)*relation;
	}
	private:
		double angle{0}; //Radianer
		double velocity{0};
		int relation{200};//Relasjon mellom bevegelse i x- og y-aksen
		
};

#endif//ACONVERTER_H

