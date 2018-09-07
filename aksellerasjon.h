#ifndef AKSELLERASJON_H
#define AKSELLERASJON_H
#include <iostream>
#include <cmath>
#include <utility>  //std::pair()
class Aksellerasjon {
	public:
		Aksellerasjon() = default;
		Aksellerasjon(float x, float y);
		Aksellerasjon(float h, int a);
		//Aksellerasjon& operator=(const Aksellerasjon& rhs);// = default;
		float X() {return X_;}
		float Y() {return Y_;}
		float hyp() {return hyp_;}
		int angle() {return angle_;}
		void X(float x) {X_ = x;}
		void Y(float y) {Y_ = y;}
		void hyp(float h) {hyp_ = h;}
		void angle(int a) {angle_ = a;}
		
		calc_XY();
		calc_hyp_a();
	private:
		float X_{};
		float Y_{};
		int angle_{};
		float hyp_{};
		
		float PI{3.1415926};
	
};

Aksellerasjon::Aksellerasjon(float x, float y) : X_{x}, Y_{y} {
	//Regne ut angle og hyp
	calc_hyp_a();

}

Aksellerasjon::Aksellerasjon(float z, int a): hyp_{z}, angle_{a} {
	//Regne ut X og Y
	calc_XY();

}

Aksellerasjon::calc_XY(){
	float rad = (angle_+90)*(PI/180.0f);// angle_-90 pga y har 0 på toppen av koordinatsystemet
	X_ = hyp_*sin(rad);
	Y_ = hyp_*cos(rad);
	std::cout << "calc_XY(): X_ = " << X_ << "  Y_ = " << Y_ << "\n";
}
	
Aksellerasjon::calc_hyp_a(){//TODO: Sjekke om denne matematikken holder mål
	hyp_ = sqrt(X_*X_ + Y_*Y_);
	float radangl = asin(X_/hyp_);
	angle_ = static_cast<int>(radangl/(PI/180));
}

//Aksellerasjon& Aksellerasjon::operator=(const Aksellerasjon& rhs) {
//	
//}
#endif

