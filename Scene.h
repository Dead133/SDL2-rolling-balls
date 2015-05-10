#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>

class Scene {
public:
    Scene();
    ~Scene();

private:
    SDL_Window* window = NULL; // The window we'll be rendering to
    SDL_Renderer* renderer = NULL; // The window renderer

    bool init();
    void freeResources();
    void draw();
};


#endif //SCENE_H
