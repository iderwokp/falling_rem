#ifndef SDLSUTEX_WRAP_H
#define SDLSUTEX_WRAP_H
#include <string>
#include <SDL.h>


class  SDLSuTexWrap {
	   SDL_Surface* surface_{nullptr};
 	   SDL_Texture* texture_{nullptr};
 	   SDL_Renderer* renderer_{nullptr};
	
 	   std::string filename{};
 	   
 	   	void init() {
	    //std::cout << "init()\n";
	  	  surface_ = SDL_LoadBMP(filename.c_str());
	  	  texture_ = SDL_CreateTextureFromSurface(renderer_, surface_);
		}
		
		void destroy() {
      	  SDL_DestroyTexture(texture_);
      	  SDL_FreeSurface(surface_);
		}
		
    public:
    	SDLSuTexWrap() = default;
    	SDLSuTexWrap(std::string fn, SDL_Renderer* r) : filename{fn}, renderer_{r} {
			init();
		}
		SDLSuTexWrap(const SDLSuTexWrap& rhs) : filename{rhs.filename}, renderer_{rhs.renderer_} {
			init();
		}
		SDLSuTexWrap& operator=(const SDLSuTexWrap& rhs) {
			filename = rhs.filename;
			renderer_= rhs.renderer_;
			destroy(); //slette gamle texture og surface
			init(); //Lage ny texture og surface
			return *this;
		}
		SDLSuTexWrap(SDLSuTexWrap&& rhs): filename{rhs.filename}, renderer_{rhs.renderer_}, surface_{rhs.surface_}, texture_{rhs.texture_}  {
			rhs.surface_ = nullptr;
			rhs.texture_ = nullptr;
			rhs.renderer_ = nullptr;
			rhs.filename = "";
		}
		SDLSuTexWrap& operator=(SDLSuTexWrap&& rhs) {
			destroy(); //slette gamle texture og surface
			filename = rhs.filename; 
			renderer_ = rhs.renderer_; 
			surface_ = rhs.surface_;
			texture_ = rhs.texture_;
			rhs.surface_ = nullptr;
			rhs.texture_ = nullptr;
			rhs.renderer_ = nullptr; 
			rhs.filename = "";
			return *this;
			
		}
		
		SDL_Surface* surface() { return surface_; }
		void set_surface(SDL_Surface* s) { surface_ = s; }
		
		SDL_Renderer* renderer() { return renderer_; }
		void set_renderer(SDL_Renderer* r) { renderer_ = r; }
		
		SDL_Texture* texture() { return texture_; }
		void set_texture(SDL_Texture* t) { texture_ = t; }
		
		
    	~SDLSuTexWrap() {
    		destroy();
    	}
	
	
};

#endif //SDLSUTEX_WRAP_H

