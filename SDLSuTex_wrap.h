#ifndef SDLSUTEX_WRAP_H
#define SDLSUTEX_WRAP_H
#include <SDL.h>

class  SDLSuTexWrap {
	   SDL_Surface* surface;
 	   SDL_Texture* texture;
 	   SDL_Renderer* renderer_;
 	   std::string filename
 	   
 	   	void init() {
	    //std::cout << "init()\n";
	  	  surface = SDL_LoadBMP(filename.c_str());
	  	  texture = SDL_CreateTextureFromSurface(renderer, surface);
		}
		
		void destroy() {
      	  SDL_DestroyTexture(texture);
      	  SDL_FreeSurface(surface);
		}
		
    public:
    	SDLSuTexWrap(std::string fn, SDL_Renderer* r) : filename{fn}, renderer_{r} {
			init();
		}
		SDLSuTexWrap(const SDLSuTexWrap& rhs) : filename{rhs.filename}, renderer_{rhs.renderer_} {
			init();
		}
		SDLSuTexWrap& operator=(const SDLSuTexWrap& rhs) {
			filename = rhs.filename;
			renderer_.rhs.renderer_;
			destroy(); //slette gamle texture og surface
			init(); //Lage ny texture og surface
			return *this;
		}
    	~SDLSuTexWrap() {
    		destroy();
    	}
	
	
};

#endif //SDLSUTEX_WRAP_H

