#ifndef FREE_FALL_WIDGET_H
#define FREE_FALL_WIDGET_H
#include <iostream>
#include <memory>
#include "widget.h"
#include "ffgenerator.h"



class  Free_fall_widget{
	
	public:
		Free_fall_widget() {
			std::cout << "Free_fall_widget()\n";
			init();

		}
		Free_fall_widget(const std::string& fn, SDL_Renderer* rend, int bound, int wall_bound, int scale, Point p={0, 0}, int w = 0, int h = 0, int dx = 0, double ls = 0.0, bool bst = false): 
											filename_{fn}, 
											renderer_{rend}, 
											boundary_{bound}, 
											wall_boundary_{wall_bound},
											scale_{scale}, 
											_startpoint{p},                                                                                                                    
                                            _width{w},
                                            _height{h},
                                            _deltaX{dx},
                                            loss_{ls},
                                            boost_{bst}
                                           
											 { 
											 	std::cout << "Free_fall_widget(.....) Constr\n ";// << _startpoint.X << "," << _startpoint.Y << "\n";
											 	init();										 	
											 
											 }
		bool& boost()  {
			return ffgenerator.boost();
		}
		void setXY(int x) {
			return ffgenerator.set_widget_xy(x);
		}
		void setDeltaX(int dx) {
			widget->set_deltaX(dx);	
		}
		
		double& loss() { return ffgenerator.loss();}
		
		//void handle_side_crash(Free_fall_widget&, int);
		int& deltaX()  { return widget->deltaX();}
		
		void updateXY(int windows_width) {
			setXY(xPos);
			handle_side_crash(windows_width);
			xPos += widget->deltaX();						
		}
		Free_fall_widget(const Free_fall_widget& rhs):
		
											filename_{rhs.filename_}, 
											renderer_{rhs.renderer_}, 
											boundary_{rhs.boundary_}, 
											wall_boundary_{rhs.wall_boundary_},
											scale_{rhs.scale_}, 
											_startpoint{rhs._startpoint},                                                                                                                    
                                            _width{rhs._width},
                                            _height{rhs._height},
                                            _deltaX{rhs._deltaX},
                                            loss_{rhs.loss_},
                                            boost_{rhs.boost_}
                                           
											{
													std::cout << "Free_fall_widget(Copy)\n";
												
												init();
											}//Free_fall_widget(const Free_fall_widget& rhs)
												 
		Free_fall_widget& operator=(const Free_fall_widget& rhs) {
			//std::cout << "Free_fall_widget(Operator=)\n";
			filename_ = rhs.filename_; 
			renderer_ = rhs.renderer_;
			boundary_ = rhs.boundary_; 
			wall_boundary_=rhs.wall_boundary_;
			scale_ = rhs.scale_;
			_startpoint = rhs._startpoint;                                                                                                                    
            _width = rhs._width;
            _height = rhs._height;
            _deltaX = rhs._deltaX;
            loss_ = rhs.loss_;
            boost_ = rhs.boost_;
           
			init();
			return *this;
		}//operator=
		
			Free_fall_widget(Free_fall_widget&& rhs) noexcept :
		
											filename_{rhs.filename_}, 
											renderer_{rhs.renderer_}, 
											boundary_{rhs.boundary_}, 
											wall_boundary_{rhs.wall_boundary_},
											scale_{rhs.scale_}, 
											_startpoint{rhs._startpoint},                                                                                                                    
                                            _width{rhs._width},
                                            _height{rhs._height},
                                            _deltaX{rhs._deltaX},
                                            loss_{rhs.loss_},
                                            boost_{rhs.boost_},
                                            widget{std::move(rhs.widget)}
                                            
                                                                                       
											{
													std::cout << "Free_fall_widget(Move)\n";
													ffgenerator = std::move(rhs.ffgenerator); 
													//rhs.widget
													//ffgenerator = FFGenerator(widget, boundary_, wall_boundary_, scale_, 0, static_cast<double>(_startpoint.Y)) ;
											}//Free_fall_widget(Free_fall_widget&& rhs)
											
			Free_fall_widget& operator=(Free_fall_widget&& rhs) {
				std::cout << "Free_fall_widget(Move Operator=)\n";
				filename_ = rhs.filename_; 
				renderer_ = rhs.renderer_;
				boundary_ = rhs.boundary_; 
				wall_boundary_=rhs.wall_boundary_;
				scale_ = rhs.scale_;
				_startpoint = rhs._startpoint;                                                                                                                    
	            _width = rhs._width;
	            _height = rhs._height;
	            _deltaX = rhs._deltaX;
	            loss_ = rhs.loss_;
	            boost_ = rhs.boost_;
	           widget = rhs.widget;
	           ffgenerator = rhs.ffgenerator;
				//init();
				return *this;
		}//Move operator=
											
		~Free_fall_widget() {
			std::cout << "~Free_fall_widget()\n";
			//delete widget;
		}
		
		
	private:
		
		std::string filename_{};
		SDL_Renderer* renderer_;
		int boundary_{};
		int wall_boundary_{};
		int scale_{};
		double xPos{0};
		double yPos{0};
		Point _startpoint{};
		int _height{0};
		int _width{0};
		bool boost_{false};
		double loss_{0};
		int _deltaX{0};
		//Widget* widget{};
		std::shared_ptr<Widget> widget{};
		FFGenerator ffgenerator;
		
		void init() {
			std::cout << "init()\n";
			widget = std::make_shared<Widget>(filename_, renderer_, _startpoint, _width, _height, _deltaX);
	    	 ffgenerator = FFGenerator(widget, boundary_, wall_boundary_, scale_, 0, static_cast<double>(_startpoint.Y)) ;
		  	if(boost_) ffgenerator.boost() = true;
		 	if(loss_ != 0.0) ffgenerator.loss() = loss_;
		 	xPos = _startpoint.X;
			
		}
		
		void handle_side_crash(int);
		
};

void Free_fall_widget::handle_side_crash(int windows_width) {
    if(widget->startpoint().X < 0 || widget->startpoint().X > (windows_width - widget->width())) {
        setDeltaX(-widget->deltaX());
    }
    //std::cout << "ffg.widget.deltaX()=" << ffg.widget.deltaX() << "\n";
}

#endif //FREE_FALL_WIDGET_H

