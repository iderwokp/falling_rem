#ifndef ANGL_COORD_H
#define ANGL_COORD_H
#include <cmath>

constexpr float PI = 3.1415926;

class Angl_coord {
	public:
		Angl_coord(int x, int y, int ww): x_{x}, y_{y}, windows_width_{ww} {}
		
	private:
		std::pair<float, int> xy_to_pol() {
			return std::make_pair(x_*(360/windows_width_), y_);
		}
		std::pair<int, int> pol_to_new_xy(std::pair<float, int> xa) {
			
		}
		int x_{0};
		int y_{0};
		int windows_width_{0};
	
	
};

#endif //ANGL_COORD_H

