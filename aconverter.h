#ifndef ACONVERTER_H
#define ACONVERTER_H
#include <cmath>

//constexpr float PI = 3.1415926;
class  Aconverter{
	public:
	Aconverter() = default;
	Aconverter(float a /*grader*/, float vel, int rel=200) : angle{a*(PI/180)}, velocity{vel}, relation{rel} {
		//std::cout << __func__ << ": angle=" << angle << " velocity=" << velocity << "\n";
	}
	float x_velocity() {
		float x = velocity*cos(angle);
		//std::cout << __func__ << ": x = " << x << "\n";
		return x;
			}
	float y_velocity() {
		float y = velocity*sin(angle)*relation;
		//std::cout << __func__ << ": y = " << y << "\n";	
		return y;
	}
	private:
		float angle{0}; //Radianer
		float velocity{0};
		int relation{200};//Relasjon mellom bevegelse i x- og y-aksen
		
};

#endif//ACONVERTER_H

