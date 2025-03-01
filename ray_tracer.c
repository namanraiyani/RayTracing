#include <stdio.h>
#include<SDL2/SDL.h>

#define WIDTH 900
#define HEIGHT 700
#define COLOR_WHITE 0xffffffff
int main(){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("RayTracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_Rect rect = (SDL_Rect) { 200, 200, 200, 200};
	SDL_FillRect(surface, &rect, COLOR_WHITE);
	SDL_UpdateWindowSurface(window);
	SDL_Delay(5000);
	return 0;
}
