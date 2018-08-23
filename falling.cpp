#include <SDL.h>
#include <iostream>
//#include <fstream>
#include <vector>
//#include <widget.h>
//#include "ffgenerator.h"
#include "sdl_wrap.h"
#include "free_fall_widget.h"


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
    const int windows_width {1100};
    const int windows_height {700};
    SDL_Init(SDL_INIT_VIDEO);
    
    Sdl_wrap sdlwrap{std::string{"Falling"}, windows_width, windows_height};
    SDL_Window* window = sdlwrap.window();
    SDL_Renderer* renderer = sdlwrap.renderer();
    
    std::vector<Free_fall_widget> ffws(1);
   
    ffws.push_back(Free_fall_widget{"ball.bmp", renderer, windows_height, windows_width, 200, Point{300,100}, 30, 20, 1, 0.9, true});
    ffws.push_back(Free_fall_widget{"ball.bmp", renderer, windows_height, windows_width, 200, Point{1200,0}, 30, 20, -1, 0.9, true});
    ffws.push_back(Free_fall_widget{"ball.bmp", renderer, windows_height, windows_width, 200, Point{100,300}, 30, 20, 1, 0.9, true});
    ffws.push_back(Free_fall_widget{"ball.bmp", renderer, windows_height, windows_width, 200, Point{900,500}, 30, 20, -1, 0.9, true});
    ffws.push_back(Free_fall_widget{"ball.bmp", renderer, windows_height, windows_width, 200, Point{400,100}, 30, 20, -1, 0.9, true});
    ffws.push_back(Free_fall_widget{"ball.bmp", renderer, windows_height, windows_width, 200, Point{1000,0}, 30, 20, -1, 0.9, true});
    ffws.push_back(Free_fall_widget{"ball.bmp", renderer, windows_height, windows_width, 200, Point{150,200}, 30, 20, 1, 0.9, true});
    ffws.push_back(Free_fall_widget{"ball.bmp", renderer, windows_height, windows_width, 200, Point{800,100}, 30, 20, -1, 0.9, true});
   
    
//	int index{400};
	while(!quit) {
	//while(index--) {
        EventHandler(event, quit, windows_width, windows_height);
        for(auto& ff: ffws) {
        	ff.updateXY(windows_width);
        }
        

	    SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);     
		
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
