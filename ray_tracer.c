#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

#define WIDTH 900
#define HEIGHT 700
#define COLOR_WHITE 0xffffffff

struct Circle{
	double x;
	double y;
	double radius;
};

void FillCircle(SDL_Surface* surface, struct Circle circle, Uint32 color){
	double radius_sqrd = pow(circle.radius, 2);
	for(double x = circle.x - circle.radius; x <= circle.x + circle.radius; x++){
		for(double y = circle.y - circle.radius; y <= circle.y + circle.radius; y++){
			double distance_sqrd = pow(x - circle.x, 2) + pow(y - circle.y, 2);
			if(distance_sqrd < radius_sqrd){
				SDL_Rect pxl = (SDL_Rect) {x,y,1,1};
				SDL_FillRect(surface, &pxl, color);
			}
		}
	}
}

int main(){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("RayTracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_Rect rect = (SDL_Rect) { 200, 200, 200, 200};
//	SDL_FillRect(surface, &rect, COLOR_WHITE);
	struct Circle circle = {200, 200, 75};
	FillCircle(surface, circle, COLOR_WHITE);
	SDL_UpdateWindowSurface(window);
	SDL_Delay(5000);
	return 0;
}
