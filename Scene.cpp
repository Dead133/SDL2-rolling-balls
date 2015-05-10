#include "Scene.h"
//#include <SDL.h>
//#include <stdio.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Scene::Scene() {
    printf("Class Scene construtor called!\n");
    if (!this->init()) {
        printf("Cannot initialize. Halt.\n");
        this->freeResources();
        exit(0);
    }

    bool isQuitRequested = false;

    SDL_Event event;

    while (!isQuitRequested) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                isQuitRequested = true;
            }
        }

        this->draw();
    }
}

Scene::~Scene() {
    printf("Class Scene destrutor called!\n");
    this->freeResources();
}

bool Scene::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!");
    }

    this->window = SDL_CreateWindow("Rolling balls",
                                    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH, SCREEN_HEIGHT,
                                    SDL_WINDOW_SHOWN);

    if (this->window == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (this->renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void Scene::draw() {
    // Clear screen
    SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(this->renderer);

    // Draw rectangle
    SDL_Rect filledRectangleCoords = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderFillRect(this->renderer, &filledRectangleCoords);

    SDL_RenderPresent(this->renderer);
}

void Scene::freeResources() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    this->window = NULL;
    this->renderer = NULL;
    SDL_Quit();
}
