#ifndef ANGL_COORD_H
#define ANGL_COORD_H
#include <cmath>

constexpr float PI = 3.1415926;

class Angl_coord {
	public:
		Angl_coord(int ww, int wh): windows_width_{ww}, windows_height_{wh} {
			desentrX = windows_width_/2; //Midt i
			desentrY = windows_height_/2; //Midt i
		
		}
		std::pair<double, double> polXY(double x, double y) {
			return 	pol_to_new_xy(xy_to_pol(double x, double y));			
		}
		
	private:
		std::pair<double, double> xy_to_pol(double x, double y) {
			return std::make_pair(x*(360/windows_width_), y);
		}
		std::pair<double, double> pol_to_new_xy(std::pair<double, double> xa) {
			double x = xa.second()*sin(xa.first()*(PI/180)); //TODO: Narrowing
			double y = xa.second()*cos(xa.first()*(PI/180)); //TODO: Narrowing
			return std::make_pair(x/2, y/2); // y/2 og x/2 pga senter ligger midt i skjermen, og ikke i et hj�rne
		}
		
		int windows_width_{0};
		int windows_height_{0};
		double desentrY{0};
		double desentrX{0};
	
	
};

#endif //ANGL_COORD_H
