#ifndef AKSELLERASJON_H
#define AKSELLERASJON_H
#include <cmath>
#include <utility>  //std::pair()
class Aksellerasjon {
	public:
		Aksellerasjon() = default;
		Aksellerasjon(float x, float y) : X{x}, Y{y} {}
		Aksellerasjon(float h, float a): hyp{z}, angle{a} {}
	private:
		float X{};
		float Y{};
		float angle{};
		float hyp{};
		calc_XY();
		calc_hyp_a();
		const float PI{3.1415926};
	
};

Aksellerasjon::Aksellerasjon(float x, float y) : X{x}, Y{y} {
	//Regne ut angle og hyp
	calc_hyp_a();

}

Aksellerasjon::Aksellerasjon(float z, float a): XY{z}, angle{a} {
	//Regne ut X og Y
	calc_XY();

}

Aksellerasjon::calc_XY(){
	float rad = angle*(PI/180.0f);
	X = hyp*sin(rad);
	Y = hyp*cos(rad);
}
	
Aksellerasjon::calc_hyp_a(){//TODO: Sjekke om denne matematikken holder mål
	hyp = sqrt(X*X + Y*Y);
	float radangl = asin(X/hyp);
	angl = radangl/(PI/180);
}
#endif

