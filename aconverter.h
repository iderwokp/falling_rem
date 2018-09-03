#ifndef ACONVERTER_H
#define ACONVERTER_H
#include <cmath>

//constexpr float PI = 3.1415926;
class  Aconverter{
	public:
	Aconverter() = default;
	Aconverter(float a /*grader*/, float vel, int rel=200) : angle{a*(PI/180)}, velocity{vel}, relation{rel} {}
	float x_velocity() {
		return velocity*cos(angle);
	}
	float y_velocity() {
		return velocity*sin(angle)*relation;
	}
	private:
		float angle{0}; //Radianer
		float velocity{0};
		int relation{200};//Relasjon mellom bevegelse i x- og y-aksen
		
};

#endif//ACONVERTER_H

