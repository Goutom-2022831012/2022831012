#include <iostream>
#include <SDL2/SDL.h>
#include <cmath> 
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int circleX = SCREEN_WIDTH / 2;
int circleY = SCREEN_HEIGHT / 2;
int circleRadius = 50;
int circleRadiusIncrement = 2;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool initializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow("Expanding Circle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        cerr << "Window could not be created! SDL Error: " << SDL_GetError() <<endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() <<endl;
        return false;
    }

    return true;
}

void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void drawCircle(int x, int y, int radius) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (float angle = 0; angle < 360; angle += 1.0f) {
        float radians = angle * (M_PI / 180.0f);
        int dx = static_cast<int>(radius * cos(radians));
        int dy = static_cast<int>(radius * sin(radians));
        SDL_RenderDrawPoint(renderer, x + dx, y + dy);
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    if (!initializeSDL()) {
        return 1;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        circleRadius += circleRadiusIncrement;

        if (circleX + circleRadius >= SCREEN_WIDTH || circleY + circleRadius >= SCREEN_HEIGHT) {
            circleRadius = 50;
        }

        drawCircle(circleX, circleY, circleRadius);

        SDL_Delay(15);
    }

    closeSDL();
    return 0;
}
