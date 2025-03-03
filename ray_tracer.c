#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

#define WIDTH 900
#define HEIGHT 700
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_GREY 0xefefefef
#define RAYS_NUMBER 100

struct Circle{
	double x, y, radius;
};

struct Ray{
	double x_s, y_s, angle, x_e, y_e;
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

void make_rays(struct Circle circle, struct Ray ray_arr[RAYS_NUMBER]){
	for(int i=0; i<RAYS_NUMBER; i++){
		double angle = ((double) i / RAYS_NUMBER) * 2 * M_PI;
		struct Ray ray = {circle.x, circle.y, angle, 0, 0};
		ray_arr[i] = ray;
	}
}

void FillRays(SDL_Surface* surface, struct Ray rays[RAYS_NUMBER], Uint32 color){
	for(int i=0; i<RAYS_NUMBER;i++){
		struct Ray ray = rays[i];
		int end_of_screen = 0, object_hit = 0;
		double step = 1;
		double x_draw = ray.x_s, y_draw = ray.y_s;
		while(!end_of_screen && !object_hit){
			x_draw += step*cos(ray.angle);
			y_draw += step*sin(ray.angle);
			SDL_Rect pxl = (SDL_Rect) {x_draw, y_draw, 1, 1};
			SDL_FillRect(surface, &pxl, color);
			if(x_draw<0 || x_draw>WIDTH || y_draw<0 || y_draw>HEIGHT){
				end_of_screen = 1;
			}
		}
	}
}

int main(){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("RayTracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	struct Circle circle = {200, 200, 80};
	struct Circle shadow_circle = {750, 300, 140};
	SDL_Rect erase_rect = {0, 0, WIDTH, HEIGHT};
	struct Ray rays[RAYS_NUMBER];
	int simulation = 1;
	SDL_Event event;
	while(simulation == 1){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				simulation = 0;
			}
			if(event.type == SDL_MOUSEMOTION && event.motion.state != 0){
				circle.x = event.motion.x;
				circle.y = event.motion.y;
				make_rays(circle, rays);
			}
		}
		SDL_FillRect(surface, &erase_rect, COLOR_BLACK);
		FillCircle(surface, circle, COLOR_WHITE);
		FillCircle(surface, shadow_circle, COLOR_WHITE);
		FillRays(surface, rays, COLOR_WHITE);
		SDL_UpdateWindowSurface(window);
		SDL_Delay(10);
	}
	return 0;
}
