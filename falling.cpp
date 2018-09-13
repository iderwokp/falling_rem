#include <SDL.h>
#include <iostream>
//#include <fstream>
#include <vector>
#include <cmath>
//#include <widget.h>
//#include "ffgenerator.h"
#include "sdl_wrap.h"
#include "free_fall_widget.h"
#include "aconverter.h"


void EventHandler(SDL_Event event, bool& quit, int ww, int wh) {
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT){
        quit = true;
    }    
//    if(event.type == SDL_MOUSEBUTTONDOWN) {
//        int x{0};
//        int y{0};
//        SDL_GetMouseState( &x, &y );
//        check_mouse_click(x, y, w, ww, wh);
//        
//    }
}
int main(int argc, char** argv) {
	
	SDL_Event event;
	bool quit{false};
    const int windows_width {1300};
    const int windows_height {700};
    SDL_Init(SDL_INIT_VIDEO);
    
    Sdl_wrap sdlwrap{std::string{"Falling"}, windows_width, windows_height};
    SDL_Window* window = sdlwrap.window();
    SDL_Renderer* renderer = sdlwrap.renderer();
    
    //std::vector<Free_fall_widget> ffws(8);
    SDL_Delay(500);   
    Aconverter ac{0, 0.0f};
//    Aconverter ac2{120, 10.0f};
//    Aconverter ac3{70, 12.0f};
//    Aconverter ac4{100, 20.0f};
//    Aconverter ac5{250, 7.0f};
//    Aconverter ac6{340, 7.0f};
//    double aks{9.81f};
//    ffws.push_back(Free_fall_widget{"ball.bmp", renderer, windows_height, windows_width, 200, Point{0,windows_height-126}, 30, 20, ac.x_velocity(), -ac.y_velocity(), 0.8, true});
//    ffws.push_back(Free_fall_widget{"ball.bmp", renderer, windows_height, windows_width, 200, Point{windows_width-30,windows_height-26}, 30, 20, ac2.x_velocity(), -ac2.y_velocity(), 0.8, true});
//    ffws.push_back(Free_fall_widget{"ball.bmp", renderer, windows_height, windows_width, 200, Point{windows_width-300,windows_height-26}, 30, 20, ac3.x_velocity(), -ac3.y_velocity(), 0.8, true});         
//	ffws.push_back(Free_fall_widget{"ball.bmp", renderer, windows_height, windows_width, 200, Point{300,windows_height-26}, 30, 20, ac4.x_velocity(), -ac4.y_velocity(), 0.8, true});
//	ffws.push_back(Free_fall_widget{"ball.bmp", renderer, windows_height, windows_width, 200, Point{50,windows_height-26}, 30, 20, ac.x_velocity(), -ac.y_velocity(), 0.8, true});
//    ffws.push_back(Free_fall_widget{"ball.bmp", renderer, windows_height, windows_width, 200, Point{0,0}, 30, 20, ac6.x_velocity(), -ac6.y_velocity(), 0.8, true});
//    ffws.push_back(Free_fall_widget{"ball.bmp", renderer, windows_height, windows_width, 200, Point{windows_width-100,windows_height-260}, 30, 20, ac3.x_velocity(), -ac3.y_velocity(), 0.8, true});         
//	ffws.push_back(Free_fall_widget{"ball.bmp", renderer, windows_height, windows_width, 200, Point{500,windows_height-100}, 30, 20, ac4.x_velocity(), -ac4.y_velocity(), 0.8, true});

    
    Free_fall_widget ffw{"ball.bmp", renderer, windows_height, windows_width, 1000, Point{200,200}, 30, 20, ac.x_velocity(), ac.y_velocity(), 0.8, true};
    //ffw.set_aksellerasjon(0.981f,0.981f); 
    //ffw.set_aksellerasjon(0.981f,90);
     
//    for(auto& ff: ffws) {
//        	ff.set_aksellerasjon(aks);
//        }
    int index{3010}; 
    const double midwinX = windows_width/2;
    const double midwinY = windows_height/2;
    //std::cout << "midwinX = " << midwinX << "  midwinY = " << midwinY << "\n"; 
	//while(!quit) {
	//const double storK {1000000};
	while(index >=0 && !quit) {
	
        EventHandler(event, quit, windows_width, windows_height);
        //ffw.updateXY(windows_width);
        auto [x, y] = ffw.current_coords();
        //std::cout << "x = " << x << "  y = " << y << "\n"; 
        double vecX = midwinX - x;//static_cast<double>(x);
        double vecY = midwinY - y;//static_cast<double>(y);
        //if(vecY <= 0 || vecX <= 0) { std::cout << "Nådd null: index = " << index << "\n";break;}
        //std::cout << "vecX = " << vecX << " x = " << x << "  vecY = " << vecY << " y = " <<  y << "\n"; 
         
        double vecXY = sqrt(vecX*vecX + vecY*vecY);
//        vecX*=storK;
//        vecY*=storK;
//        vecXY*=storK;
        double radangl{};
        double ekspr = (vecX*vecX+vecY*0)/(vecXY*vecX);
        if(ekspr< -1.0 || ekspr > 1.0) {std::cout << "Overflow: ekspr = " << ekspr << "\n";}
        radangl = acos(ekspr);
//        if (vecY >= 0)  radangl = acos(vecX/vecXY);
//        else {
//        	 radangl = asin(vecY/vecXY);
//        	if(vecX > 0) radangl = -radangl;
//        }
//        
        float angle_ = (radangl*(180.0/3.1415926));
        angle_ = (angle_); 
        ffw.set_aksellerasjon(0.981,angle_, true); 
        //std::cout << "vecXY = " << vecXY << "  angle_ = " << angle_ << "  vecX/vecXY  " << vecX/vecXY << "\n\n"; 
        
//        for(auto& ff: ffws) {
//        	ff.updateXY(windows_width);
//        }
        //std::cout << "index = " << index << "\n";
		--index;
//		if(index == 0) {
//			ffw = ffw_copy;
//			index = 400;	
//			ffw.set_aksellerasjon(aks); 
//		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		//SDL_RenderClear(renderer); 
	    
	    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        
			SDL_RenderDrawLine(renderer, 0,midwinY, windows_width,midwinY);
			SDL_RenderDrawLine(renderer, midwinX,0, midwinX, windows_height);
			ffw.updateXY(windows_width);
			SDL_RenderPresent(renderer);
		SDL_Delay(5);   
    }

    SDL_Quit();
}

// if(avstand/2000 > windows_height-30 && notbottom == true) {
//        	of << "\nBottom************************************************************************************\n";
//			nedover = false;
//			tid = 0; 
//			v0 = vtot;
//			s0 = avstand; 
//			notbottom = false;
//			nottop = true;
//		}
//		if(avstand/2000 < 0 && nottop == true) {
//			of << "\nTop******************************************************************************************\n";
//			nedover = true; 
//			tid = 0; 
//			s0 = avstand;
//			nottop = false;
//			notbottom = true;
//		}
//		if(vtot <= 0 && nedover == false) {
//			
//			of << "\nTop  ( vtot == 0?) ***********************************************************************************************\n";
//			nedover = true; 
//			tid = 0; 
//			s0 = avstand;
//			nottop = false;
//			notbottom = true;
//		}
//        if(nedover) {
//        	vg = g*tid;
//        	vtot = v0 + vg + 1;
//        	s = vtot*tid;
//        	avstand = s0 + s;
//        	ball.moveTo(500,avstand/2000);
//        	
//        }
//        else if(!nedover)  {
//        	
//        	vg = g*tid;
//        	vtot = v0 - vg;
//        	s = vtot*tid;
//        	avstand = s0 - s;
//        	ball.moveTo(500,avstand/2000);
//        	//if(vtot <= 0) {nedover = true; notbottom = true;of << "Top ( vtot == 0?)\n";}
//		}
//        ++tid;
//        //if(s/2000<=(windows_height-60)) ++t;
//        
//        of << "nedover = " << nedover << "  Nottop = " << nottop << "  notbottom = " << notbottom << "  avstand/2000 = " << avstand/2000 << "\ttid = " << tid << "  ";
//        of << "vtot = " << vtot << "  v0 = " << v0 << "\tvg = " << vg << "\n\n";
//        
