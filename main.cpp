#include <stdio.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <SDL2/SDL.h>
#ifdef __MINGW32__
#undef main
#endif

using namespace std;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Rect serpentcorps[200];
bool eatApple = false;
const int Cell_Size = 16;
const int Grid_Size = 16;
const int start_size = 5;
int x = serpentcorps[0].x;
int y = serpentcorps[0].y;
int dir;
int serpentSize = start_size;
int serpentX = (Cell_Size*Grid_Size)/2, serpentY = (Cell_Size*Grid_Size)/2;
int random(int min, int max){
    return rand() % (max-min+1)+min;
}

SDL_Rect drawSquare(SDL_Renderer* renderer,  int x, int y, int w, Uint8 r, Uint8 g, Uint8 b){
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_Rect carre;
    carre.x = x;
    carre.y = y;
    carre.h = w;
    carre.w = w;
    SDL_RenderFillRect(renderer, &carre);
    return carre;
}

SDL_Rect placeApple(int x, int y){

    SDL_Rect carre;
    carre = drawSquare(renderer, x, y, Cell_Size, 255, 0, 0);
    return carre;
}


void moveSerpent(SDL_Event q, int g, int d, int h, int b){
    if(q.key.keysym.sym == SDLK_w)
        g -= 1;
    else if(q.key.keysym.sym == SDLK_a)
        d -= 1;
    else if(q.key.keysym.sym == SDLK_s)
        h += 1;
    else if(q.key.keysym.sym == SDLK_d)
        b += 1;
  }
clock_t avantClock = 0;
//main
int main()
{
    int appleX = random(0, Grid_Size-1);
    int appleY = random(0, Grid_Size-1);
    window = SDL_CreateWindow("serpent", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,Cell_Size * Grid_Size,Cell_Size * Grid_Size, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    srand(time(0));
    int loop = 1;
    SDL_Event q;
    while(loop)
    {
        while(SDL_PollEvent(&q))
        {
            if(q.type == SDL_KEYDOWN)
              {
                if(q.key.keysym.sym == SDLK_ESCAPE)
                    loop = 0;
                else if(q.key.keysym.sym == SDLK_w){

                }
                else if(q.key.keysym.sym == SDLK_a){

                }
                else if(q.key.keysym.sym == SDLK_s){

                }
                else if(q.key.keysym.sym == SDLK_d){

                }
              }
            else if(q.type == SDL_QUIT)
            {
            loop = 0;
            }
         if(serpentX == (appleX*Cell_Size) && serpentY == (appleY*Cell_Size)){
             eatApple = true;
             if(eatApple == true)
                 appleX = random(0, Grid_Size-1);
                 appleY = random(0, Grid_Size-1);
           }
        }
        clock_t nowClock = clock();
        clock_t ecouleClock = nowClock - avantClock;
        float tempssecond = float(ecouleClock) / float(CLOCKS_PER_SEC);
        if(tempssecond >= 1){
            if(q.key.keysym.sym == SDLK_w){
            serpentY-= Cell_Size;
            }
            if(q.key.keysym.sym == SDLK_a){
            serpentX-= Cell_Size;
            }
            if(q.key.keysym.sym == SDLK_s){
            serpentY+= Cell_Size;
            }
            if(q.key.keysym.sym == SDLK_d){
            serpentX+= Cell_Size;
            }
            avantClock = nowClock;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0 ,0, 255);
        SDL_RenderClear(renderer);
        //pomme
        placeApple(appleX*Cell_Size, appleY*Cell_Size);
        //serpent
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        serpentcorps[0].x = serpentX;
        serpentcorps[0].y = serpentY;
        serpentcorps[0].w = Cell_Size;
        serpentcorps[0].h = Cell_Size;
        SDL_RenderFillRect(renderer, &serpentcorps[0]);
        SDL_RenderPresent(renderer);
    }
    return EXIT_SUCCESS;
}
