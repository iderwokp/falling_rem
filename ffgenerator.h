
//#include <widget.h>
#ifndef FFGENERATOR_H
#define FFGENERATOR_H
#include <fstream>
#include <iostream>
#include <widget.h>



class FFGenerator {// Frittfall Generator
	
	
	public:
		FFGenerator() = default;
			//	FFGenerator(Widget& wid, int bound, int scale, double lo = 1,double akslr = g_, double v0 = 0, double s0 = 0): widget{wid}, loss_{lo}, aksellerasjon_{akslr}, boundary_{bound}, scale_{scale}, v0_{v0}, s0_{s0} {
			FFGenerator(Widget* wid, int bound, int scale, double v0 = 0, double s0 = 0): widget{wid}, boundary_{bound}, scale_{scale}, v0_{v0}, s0_{s0} {
		
			
		
		}
		
		//FFGenerator(Widget& widget, double akslr, double v0, double s0): aksellerasjon_{akslr}, v0_{v0}, s0_{s0} {}
		double next_distance(); //I en loop, vil denne gi neste Y-koordinat
		void set_widget_xy(int);
		bool& boost() {return boost_;}
		double& loss() { return loss_;}
		void set_starthd(double y) { s0_ = y;}
	private:
		std::ofstream of {"dbg.txt"};
		double retning_nedover();
		double retning_oppover();
		
		static constexpr double g_ = 9.81;
		Widget* widget;
		double loss_{};
		double aksellerasjon_{g_};
		int boundary_{};
		int scale_{};
		double v0_{0}; //Startfart
		double va_{0};
		double vtot_{0};
		double s0_{0};
		int tid_{0};
		double vmax{0};
		bool boost_{false};
		double startY{0};
		bool nedover{true};
		
	
	
	
	
};

void FFGenerator::set_widget_xy(int x) {
	double y = next_distance();
	widget->moveTo(x,y);
	
}

double FFGenerator::next_distance() {
	if(nedover) return retning_nedover();
	else return retning_oppover();
	
}

double FFGenerator::retning_nedover() {
	//s = v0*tid + (aksellerasjon_*tid*tid)/2

	va_ = aksellerasjon_ * tid_;
	int s00 = s0_*scale_;
	double s = s00 + v0_*tid_ + va_*tid_/2;
	//	std::cout << "Nedover s0_ = " << s0_ << "   s = " << s << "\n";
	vtot_ = v0_ + va_;
	if(vmax<vtot_) vmax = vtot_;
	if (s/scale_ >= boundary_-25) {//TODO: Denne sjekken stemmer vel ikke helt?
	//	of << "\n";
		nedover = false;
		v0_ = vtot_*loss_;
		if(boost_) {
			if (v0_<20) v0_ = vmax;
 		}
		tid_ = 0;
		s0_ = s/scale_;
	}
	++tid_;
	//of << "retning_nedover(): " << "s/scale_=" << s/scale_ << "\t  s=" << s << "\t\ts0_=" << s0_ << "\t\tnedover=" << nedover << "\t\tvtot_=" << vtot_ << "\ttid_=" << tid_ << "\t\tv0_=" << v0_ << "\t\tva_=" << va_ << "\n";
	return s/scale_;
}

double FFGenerator::retning_oppover() {

	va_ = aksellerasjon_ * tid_;
	int s00 = s0_*scale_;
	double s = s00 - v0_*tid_ + va_*tid_/2;
	//std::cout << "Oppover s0_ = " << s0_ << "   s = " << s <<  "\n";
	vtot_ = v0_ - va_;
	
	if(vtot_ <= 0) {
		//of << "\n";
		nedover = true;
		v0_ = 0;
		tid_= 0;
		s0_ = s/scale_;
	}
	++tid_;
//	of << "retning_oppover(): " << "s/scale_=" << s/scale_ <<  "\ts=" << s << "\t\ts0_=" << s0_ << "\t\tnedover=" << nedover << "\t\tvtot_=" << vtot_ << "\t\ttid_=" << tid_ << "\t\tv0_=" << v0_ << "\t\tva_=" << va_ <<  "\n";
	return s/scale_;
}


#endif
