#define VIRT_COORD_CONVERTER_H
#ifndef VIRT_COORD_CONVERTER_H

enum class Grav_heading {down, up, right, left};
class Vc_conv {
	public:
		Vc_conv() = default;
		convert_from_virtual(Grav_heading, double, double);
	private:
		Grav_heading gravh {Grav_heading::down};
		
		std::pair<double, double> grav_down(double, double);
		std::pair<double, double> grav_up(double, double);
		std::pair<double, double> grav_right(double, double);
		std::pair<double, double> grav_left(double, double);
};

std::pair<double, double> Vc_conv::grav_down(double, double) {
	
}

std::pair<double, double> Vc_conv::grav_up(double, double) {
	
}

std::pair<double, double> Vc_conv::grav_right(double, double) {
	
}

std::pair<double, double> Vc_conv::grav_left(double, double) {
	
}

#endif//VIRT_COORD_CONVERTER_H



