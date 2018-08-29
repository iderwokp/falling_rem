

#ifndef FFGENERATOR_H
#define FFGENERATOR_H
#include <fstream>
#include <iostream>
#include "widget.h"
#include "virt_coord_converter.h"

struct Velocity {
	double v0_{0}; //Startfart
	double va_{0};
	double vtot_{0};
	double vmax{0};	
};

//class Vc_conv;
class FFGenerator {// Frittfall Generator
	
	
	public:
		FFGenerator() {std::cout << "FFGenerator() \n";} //= default;
			//	FFGenerator(Widget& wid, int bound, int scale, double lo = 1,double akslr = g_, double v0 = 0, double s0 = 0): widget{wid}, loss_{lo}, aksellerasjon_{akslr}, boundary_{bound}, scale_{scale}, v0_{v0}, s0_{s0} {
		FFGenerator(Widget* wid, int bound, int wbound, int scale, double v0 = 0, double s0 = 0): widget{wid}, boundary_{bound}, wall_boundary{wbound}, scale_{scale},  s0_{s0}// {velocity.v0_= v0;	}
		//FFGenerator(std::unique_ptr<Widget> wid, int bound, int wbound, int scale, double v0 = 0, double s0 = 0): widget{std::move(wid)}, boundary_{bound}, wall_boundary{wbound}, scale_{scale},  s0_{s0} {
		{
			if(!widget) std::cout << "FFGenerator::FFGenerator(): widget == nullptr\n";
			velocity.v0_= v0; 
			std::cout << "FFGenerator(........) \n";
		}
		FFGenerator( const FFGenerator& rhs):
						loss_{rhs.loss_},
						aksellerasjon_{rhs.aksellerasjon_},
						boundary_{rhs.boundary_},
						wall_boundary{rhs.wall_boundary},
						scale_{rhs.scale_},
						velocity{rhs.velocity},
						s0_{rhs.s0_},
						tid_{rhs.tid_},
						boost_{rhs.boost_},
						startY{rhs.startY},
						nedover{rhs.nedover},
					//	widget{std::move(rhs.widget)}
						widget{rhs.widget}
					
		{
			if(!widget) std::cout << "widget i FFGenerator(FFGenerator& rhs) == nullptr\n";
			std::cout << "FFGenerator(const FFGenerator& rhs) \n";
		}
		FFGenerator& operator=(const FFGenerator& rhs) {
			std::cout << "FFGenerator& oerator=(const FFGenerator& rhs) \n";
				loss_ = rhs.loss_;
				aksellerasjon_ = rhs.aksellerasjon_;
				boundary_ = rhs.boundary_;
				wall_boundary = rhs.wall_boundary;
				scale_ = rhs.scale_;
				velocity = rhs.velocity;
				s0_ = rhs.s0_;
				tid_ = rhs.tid_;
				boost_ = rhs.boost_;
				startY = rhs.startY;
				nedover = rhs.nedover;
				//widget = std::move(rhs.widget);
				delete widget;
				widget = rhs.widget;
				if(!widget) std::cout << "widget i FFGenerator& operator=(const FFGenerator& rhs) == nullptr\n";
			
		}
		FFGenerator(FFGenerator&& rhs):
						loss_{rhs.loss_},
						aksellerasjon_{rhs.aksellerasjon_},
						boundary_{rhs.boundary_},
						wall_boundary{rhs.wall_boundary},
						scale_{rhs.scale_},
						velocity{rhs.velocity},
						s0_{rhs.s0_},
						tid_{rhs.tid_},
						boost_{rhs.boost_},
						startY{rhs.startY},
						nedover{rhs.nedover},
					//	widget{std::move(rhs.widget)}
						widget{rhs.widget}
						
						
		{
			std::cout << "FFGenerator(FFGenerator&& rhs) \n";
			if(!widget) std::cout << "widget i FFGenerator(FFGenerator&& rhs) == nullptr\n";
			rhs.widget = nullptr;
		}
		FFGenerator& operator=(FFGenerator&& rhs) {
			std::cout << "FFGenerator& operator=(FFGenerator&& rhs) \n";
				loss_ = rhs.loss_;
				aksellerasjon_ = rhs.aksellerasjon_;
				boundary_ = rhs.boundary_;
				wall_boundary = rhs.wall_boundary;
				scale_ = rhs.scale_;
				velocity = rhs.velocity;
				s0_ = rhs.s0_;
				tid_ = rhs.tid_;
				boost_ = rhs.boost_;
				startY = rhs.startY;
				nedover = rhs.nedover;
				//widget = std::move(rhs.widget);
				delete widget;
				widget = rhs.widget;
					if(!widget) std::cout << "widget i FFGenerator& operator=(const FFGenerator&& rhs) == nullptr\n";
				rhs.widget = nullptr;
			
		}
		
		~FFGenerator() { std::cout << "~FFGenerator(destruct) \n";}
		//FFGenerator(Widget& widget, double akslr, double v0, double s0): aksellerasjon_{akslr}, v0_{v0}, s0_{s0} {}
		double next_distance(); //I en loop, vil denne gi neste Y-koordinat
		void set_widget_xy(int);
		bool& boost() {return boost_;}
		double& loss() { return loss_;}
		void set_starthd(double y) { s0_ = y;}
	private:
		//std::ofstream of {"dbg.txt"};
		double retning_nedover();
		double retning_oppover();
		
		static constexpr double g_ = 9.81;
		
		double loss_{};
		double aksellerasjon_{g_};
		int boundary_{};
		int wall_boundary{};
		int scale_{};
		Velocity velocity{0, 0, 0, 0};
		//double v0_{0}; //Startfart
//		double va_{0};
//		double vtot_{0};
		double s0_{0};
		int tid_{0};
		//double vmax{0};
		bool boost_{false};
		double startY{0};
		bool nedover{true};
		//std::unique_ptr<Widget> widget;
		Widget* widget = nullptr;
		
	
	
	
	
};

void FFGenerator::set_widget_xy(int x) {
	
	Vc_conv vc(Grav_heading::down, wall_boundary, boundary_);
	
	double y = next_distance();
	auto [xx, yy] = vc.convert_from_virtual(x, y);
	//std::cout << "x = " << x << "   y = " << y << "\n";
	if(widget==nullptr) std::cout << "widget == nullptr!!!\n";
	widget->moveTo(xx,yy);
	
}

double FFGenerator::next_distance() {
	if(nedover) return retning_nedover();
	else return retning_oppover();
	
}

double FFGenerator::retning_nedover() {
	//s = v0*tid + (aksellerasjon_*tid*tid)/2

	velocity.va_ = aksellerasjon_ * tid_;
	int s00 = s0_*scale_;
	double s = s00 + velocity.v0_*tid_ + velocity.va_*tid_/2;
	//	std::cout << "Nedover s0_ = " << s0_ << "   s = " << s << "\n";
	velocity.vtot_ = velocity.v0_ + velocity.va_;
	if(velocity.vmax<velocity.vtot_) velocity.vmax = velocity.vtot_;
	if (s/scale_ >= boundary_-25) {//TODO: Denne sjekken stemmer vel ikke helt?
	//	of << "\n";
		nedover = false;
		velocity.v0_ = velocity.vtot_*loss_;
		if(boost_) {
			if (velocity.v0_<20) velocity.v0_ = velocity.vmax;
 		}
		tid_ = 0;
		s0_ = s/scale_;
	}
	++tid_;
	//of << "retning_nedover(): " << "s/scale_=" << s/scale_ << "\t  s=" << s << "\t\ts0_=" << s0_ << "\t\tnedover=" << nedover << "\t\tvtot_=" << vtot_ << "\ttid_=" << tid_ << "\t\tv0_=" << v0_ << "\t\tva_=" << va_ << "\n";
	return s/scale_;
}

double FFGenerator::retning_oppover() {

	velocity.va_ = aksellerasjon_ * tid_;
	int s00 = s0_*scale_;
	double s = s00 - velocity.v0_*tid_ + velocity.va_*tid_/2;
	//std::cout << "Oppover s0_ = " << s0_ << "   s = " << s <<  "\n";
	velocity.vtot_ = velocity.v0_ - velocity.va_;
	
	if(velocity.vtot_ <= 0) {
		//of << "\n";
		nedover = true;
		velocity.v0_ = 0;
		tid_= 0;
		s0_ = s/scale_;
	}
	++tid_;
//	of << "retning_oppover(): " << "s/scale_=" << s/scale_ <<  "\ts=" << s << "\t\ts0_=" << s0_ << "\t\tnedover=" << nedover << "\t\tvtot_=" << vtot_ << "\t\ttid_=" << tid_ << "\t\tv0_=" << v0_ << "\t\tva_=" << va_ <<  "\n";
	return s/scale_;
}


#endif
