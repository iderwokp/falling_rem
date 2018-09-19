

#ifndef FFGENERATOR_H
#define FFGENERATOR_H
#include <fstream>
#include <iostream>
#include "widget.h"
#include "virt_coord_converter.h"
#include "aksellerasjon.h"

struct Velocity {
	double vx0_{0}; //Startfart
	double vy0_{0}; //Startfart
	double va_{0};
	double vtot_{0};
	double vmax{0};	
};


//class Vc_conv;
class FFGenerator {// Frittfall Generator
	
	
	public:
		FFGenerator() {/*std::cout << "FFGenerator() \n";*/} //= default;
			//	FFGenerator(Widget& wid, int bound, int scale, double lo = 1,double akslr = g_, double v0 = 0, double s0 = 0): widget{wid}, loss_{lo}, aksellerasjon_{akslr}, boundary_{bound}, scale_{scale}, v0_{v0}, s0_{s0} {
			//FFGenerator(Widget* wid, int bound, int wbound, int scale, double v0 = 0, double s0 = 0): widget{wid}, boundary_{bound}, wall_boundary{wbound}, scale_{scale},  s0_{s0} {velocity.v0_= v0;	}
		FFGenerator(std::shared_ptr<Widget> wid, int bound, int wbound, int scale, double vx0 = 0, double vy0 = 0, double sx0 = 0, double sy0 = 0): widget{std::move(wid)}, boundary_{bound}, wall_boundary{wbound}, scale_{scale}, sx0_{sx0}, sy0_{sy0} {
		velocity.vx0_= vx0; 
		velocity.vy0_= vy0; 
		std::cout << "FFGenerator(........) \n" << velocity.vx0_ << ", " << velocity.vy0_ << "\n";
		}
		
		~FFGenerator() { /*std::cout << "~FFGenerator(destruct) \n";*/}
		//FFGenerator(Widget& widget, double akslr, double v0, double s0): aksellerasjon_{akslr}, v0_{v0}, s0_{s0} {}
		double next_distance(); //I en loop, vil denne gi neste Y-koordinat
		double next_step();
		void set_widget_xy();
		bool& boost() {return boost_;}
		double& loss() { return loss_;}
		void set_starthd(double y) { sy0_ = y;}
		void set_aksellerasjon(float, float);
		void set_aksellerasjon(float h, int a);
	private:
		//std::ofstream of {"dbg.txt"};
//		double retning_nedover();
//		double retning_oppover();
		double next_Y();
		double next_X();
		static constexpr double g_ = 9.81;
		
		double loss_{};
		Aksellerasjon aksellerasjon_{0.0f, 0.0f};
		int boundary_{};
		int wall_boundary{};
		int scale_{};
		Velocity velocity{0, 0, 0, 0, 0};
	
		double sx0_{0};
		double sy0_{0};
		int tid_{1};
	
		bool boost_{false};
		double startY{0};
		bool nedover{true};
		std::shared_ptr<Widget> widget;
		
	
	
	
	
};

void FFGenerator::set_aksellerasjon(float x, float y) {
	aksellerasjon_.X(x);
	aksellerasjon_.Y(y);
	
}
void FFGenerator::set_aksellerasjon(float h, int a) {
	aksellerasjon_.angle(a);
	aksellerasjon_.hyp(h);
	aksellerasjon_.calc_XY();
	
}
void FFGenerator::set_widget_xy() {
	//std::cout << "x = " << x << "\n";
	Vc_conv vc(Grav_heading::down, wall_boundary, boundary_);
	
	//double y = next_distance();
	double y = next_Y();
	double x = next_X();
	++tid_;
	//std::cout << "x = " << x << "   y = " << y << "\n";
	auto [xx, yy] = vc.convert_from_virtual(x, y);
	//std::cout << "xx = " << xx << "   yy = " << yy << "\n\n";
	widget->moveTo(xx,yy);
	
}

//double FFGenerator::next_distance() {
//	if(nedover) return retning_nedover();
//	else return retning_oppover();
//	
//}
double FFGenerator::next_Y() {
	//std::cout << "next_Y(): velocity.vy0_ = " << velocity.vy0_ << "\n";
	velocity.va_ = aksellerasjon_.Y() * tid_;
	int s00 = sy0_*scale_;
	double s = s00 + velocity.vy0_*tid_ + velocity.va_*tid_/2;
	velocity.vtot_ = velocity.vy0_ + velocity.va_;
	
	if (s/scale_ > boundary_-25) { 
		std::cout << __func__ << "(): s = " << s << "  s/scale_ = " << s/scale_ << " velocity.vy0_ = " << velocity.vy0_ << "  velocity.vtot_ = " << velocity.vtot_ << "\n"; 	
		s = (boundary_-25)*scale_;
		//s = 13000;
		velocity.vy0_ = -velocity.vtot_;
		std::cout << __func__ << "() slutt: s = " << s << "  s/scale_ = " << s/scale_ << " velocity.vy0_ = " << velocity.vy0_ << "  velocity.vtot_ = " << velocity.vtot_ << "\n\n"; 	
	}
	return s/scale_;
}
double FFGenerator::next_X() {
	//std::cout << "next_X(): velocity.vx0_ = " << velocity.vx0_ << "\n";
	velocity.va_ = aksellerasjon_.X() * tid_;
	int s00 = sx0_*scale_;
	double s = s00 + velocity.vx0_*tid_ + velocity.va_*tid_/2; 
	velocity.vtot_ = velocity.vx0_ + velocity.va_;
	
	if (s/scale_ > boundary_-25) {
		std::cout  << __func__ << "(): s = " << s << "  s/scale_ = " << s/scale_ << " boundary_-25 = " << boundary_-25 << "\n"; 
		s = (boundary_-25)*scale_;
		velocity.vx0_ = -velocity.vtot_;
	}
	return s/scale_;
}
//double FFGenerator::retning_nedover() {
//	//s = v0*tid + (aksellerasjon_*tid*tid)/2
//
//	velocity.va_ = aksellerasjon_ * tid_;
//	int s00 = s0_*scale_;
//	double s = s00 + velocity.v0_*tid_ + velocity.va_*tid_/2;
//	//	std::cout << "Nedover s0_ = " << s0_ << "   s = " << s << "\n";
//	velocity.vtot_ = velocity.v0_ + velocity.va_;
//	if(velocity.vmax<velocity.vtot_) velocity.vmax = velocity.vtot_;
//	if (s/scale_ >= boundary_-25) {//TODO: Denne sjekken stemmer vel ikke helt?
//	//	of << "\n";
//		nedover = false;
//		velocity.v0_ = velocity.vtot_*loss_;
//		if(boost_) {
//			
//			if (velocity.v0_<20) {
//				std::cout << "retning_nedover(): velocity.v0_ = " << velocity.v0_ << "\n"; 
//				velocity.v0_ = velocity.vmax;
//			}
//	  	}
//		tid_ = 0;
//		s0_ = s/scale_;
//	}
//	if(s <= 0 ) {
//		//of << "\n";
//		s=0;
//		velocity.v0_ = -velocity.v0_ *loss_;
//		tid_= 0;
//		s0_ = s/scale_;
//	}
//	
//	++tid_;
//	//of << "retning_nedover(): " << "s/scale_=" << s/scale_ << "\t  s=" << s << "\t\ts0_=" << s0_ << "\t\tnedover=" << nedover << "\t\tvtot_=" << vtot_ << "\ttid_=" << tid_ << "\t\tv0_=" << v0_ << "\t\tva_=" << va_ << "\n";
//	return s/scale_;
//}
//
//double FFGenerator::retning_oppover() {
//
//	velocity.va_ = aksellerasjon_ * tid_;
//	int s00 = s0_*scale_;
//	double s = s00 - velocity.v0_*tid_ + velocity.va_*tid_/2;
//	//std::cout << "Oppover s0_ = " << s0_ << "   s = " << s <<  "\n";
//	velocity.vtot_ = velocity.v0_ - velocity.va_;
//	
//	if(velocity.vtot_ <= 0 ) {
//		//of << "\n";
//		nedover = true;
//		velocity.v0_ = 0;
//		tid_= 0;
//		s0_ = s/scale_;
//	}
//	if(s <= 0 ) {
//		//of << "\n";
//		s=0;
//		nedover = true;
//		velocity.v0_ = -velocity.v0_ *loss_;
//		std::cout << "retning_oppover(): abs(velocity.v0_) = " << abs(velocity.v0_) << "\n"; 
// 		if(boost_) {
//			
//			if (abs(velocity.v0_)<20) {
//				std::cout << "retning_oppover(): abs(velocity.v0_) = " << abs(velocity.v0_) << "\n"; 
//				velocity.v0_ = velocity.vmax;
//			}
// 		}
//		tid_= 0;
//		s0_ = s/scale_;
//	}
//	
//	++tid_;
////	of << "retning_oppover(): " << "s/scale_=" << s/scale_ <<  "\ts=" << s << "\t\ts0_=" << s0_ << "\t\tnedover=" << nedover << "\t\tvtot_=" << vtot_ << "\t\ttid_=" << tid_ << "\t\tv0_=" << v0_ << "\t\tva_=" << va_ <<  "\n";
//	return s/scale_;
//}


#endif
