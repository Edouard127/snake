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
int c = 0;
int r = 0;
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
    drawSquare(renderer, c, r, Cell_Size, 0, 0, 255);
    return carre;
}



clock_t avantClock = 0;
void drawCell(int colonne, int range){

    c = colonne*Cell_Size;
    r = range*Cell_Size;

    drawSquare(renderer, c, r, Cell_Size, 0, 0, 255);
}
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
                    dir = 0;
                }
                else if(q.key.keysym.sym == SDLK_a){
                    dir = 1;
                }
                else if(q.key.keysym.sym == SDLK_s){
                    dir = 2;
                }
                else if(q.key.keysym.sym == SDLK_d){
                    dir = 3;
                }
            }
            else if(q.type == SDL_QUIT)
            {
                loop = 0;
            }

        }

        clock_t nowClock = clock();
        clock_t ecouleClock = nowClock - avantClock;
        float tempssecond = float(ecouleClock) / float(CLOCKS_PER_SEC);
        if(tempssecond >= 0.4){
            if(dir == 0){
                serpentY-= Cell_Size;
            }
            else if(dir == 1){
                serpentX-= Cell_Size;
            }
            else if(dir == 2){
                serpentY+= Cell_Size;
            }
            else if(dir == 3){
                serpentX+= Cell_Size;
            }
            avantClock = nowClock;
        }
        if(serpentX == (appleX*Cell_Size) && serpentY == (appleY*Cell_Size)){
            drawSquare(renderer, c, r, Cell_Size, 0, 0, 255);
            c = serpentX;
            r = serpentY;

            appleX = random(0, Grid_Size-1);
            appleY = random(0, Grid_Size-1);


        }
        if(((serpentX < -16+1 or serpentY > 256-1)|| serpentY < -16+1 or serpentX > 256-1)){
            loop = 0;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0 ,0, 255);
        SDL_RenderClear(renderer);
        //pomme
        placeApple(appleX*Cell_Size, appleY*Cell_Size);
        //serpent

        serpentcorps[0].x = serpentX;
        serpentcorps[0].y = serpentY;
        serpentcorps[0].w = Cell_Size;
        serpentcorps[0].h = Cell_Size;
        SDL_RenderFillRect(renderer, &serpentcorps[0]);
        SDL_RenderPresent(renderer);
    }
    return EXIT_SUCCESS;
}

