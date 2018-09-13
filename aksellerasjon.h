#ifndef AKSELLERASJON_H
#define AKSELLERASJON_H
#include <iostream>
#include <cmath>
#include <utility>  //std::pair()
class Aksellerasjon {
	public:
		Aksellerasjon() = default;
		Aksellerasjon(double x, double y);
		Aksellerasjon(double h, int a);
		
		double X() {return X_;}
		double Y() {return Y_;}
		double hyp() {return hyp_;}
		int angle() {return angle_;}
		void X(double x) {X_ = x;}
		void Y(double y) {Y_ = y;}
		void hyp(double h) {hyp_ = h;}
		void angle(int a) {angle_ = a;}
		
		calc_XY();
		calc_hyp_a();
	private:
		double X_{};
		double Y_{};
		int angle_{};
		double hyp_{};
		
		double PI{3.1415926};
	
};

Aksellerasjon::Aksellerasjon(double x, double y) : X_{x}, Y_{y} {
	//Regne ut angle og hyp
	
	calc_hyp_a();

}

Aksellerasjon::Aksellerasjon(double z, int a): hyp_{z}, angle_{a} {
	//Regne ut X og Y
	calc_XY();

}

Aksellerasjon::calc_XY(){
	double rad = (angle_)*(PI/180.0);// angle_+90 pga y har 0 p� toppen av koordinatsystemet
	X_ = hyp_*cos(rad);
	Y_ = hyp_*sin(rad);
	
	//std::cout << "calc_XY(): X_ = " << X_ << "  Y_ = " << Y_ << "\n";
}
	
Aksellerasjon::calc_hyp_a(){//TODO: Sjekke om denne matematikken holder m�l
	hyp_ = sqrt(X_*X_ + Y_*Y_);
	double radangl = acos(X_/hyp_);
	angle_ = static_cast<int>(radangl/(PI/180.0));
}

//Aksellerasjon& Aksellerasjon::operator=(const Aksellerasjon& rhs) {
//	
//}
#endif

