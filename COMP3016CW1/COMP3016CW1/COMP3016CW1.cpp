#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/sdl_image.h>
#include <SDL3/SDL_ttf.h>
#include <SDL3/SDL_surface.h>
#include "Player.h"
#include "Button.h"
#include "CharacterCreateBox.h"



void CreateCharacterScreen()
{
    TTF_Font* font = TTF_OpenFont("images/font.ttf", 60);
    SDL_Color textColour = { 255,255,255,255 };

    Mouse* mouse = new Mouse();
    Button* quit = new Button();
    quit->srect.y = 0;
    quit->drect.x = 880;
    quit->drect.y = 510;
    Box* box = new Box();
    box->srect.y = 0;
    box->drect.x = 200;
    box->drect.y = 10;
    float fontSize = 33;
    bool running = true;

    while (running)
    {
        SDL_Event event;
        SDL_RenderPresent(renderer);
        mouse->update();
        quit->update(*mouse);
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (quit->isSelected)
                    {
                        running = false;
                    }
                }
            }
        }
        SDL_RenderClear(renderer);
        box->draw();
        quit->draw();
        SDL_Surface* surfaceQuit = TTF_RenderText_Solid(font, "QUIT", 4, textColour);
        SDL_Texture* textureQuit = SDL_CreateTextureFromSurface(renderer, surfaceQuit);
        SDL_FRect textRectQuit = { 970,535,fontSize * 4,60 };
        SDL_RenderTexture(renderer, textureQuit, NULL, &textRectQuit);
        SDL_DestroySurface(surfaceQuit);
        SDL_DestroyTexture(textureQuit);
        mouse->draw();

    }
}

int main()
{
    float fontSize = 33;
    Mouse* mouse = new Mouse();

    Button* start = new Button();
    start->srect.y = 0;
    start->drect.x = 100;
    start->drect.y = 510;

    Button* options = new Button();
    options->srect.y = 0;
    options->drect.x = 490;
    options->drect.y = 510;

    Button* quit = new Button();
    quit->srect.y = 0;
    quit->drect.x = 880;
    quit->drect.y = 510;
    bool running = true;
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("images/font.ttf", 60);
    SDL_Color textColour = { 255,255,255,255 };

    while (running)
    {
        SDL_Event event;
        SDL_RenderPresent(renderer);
        mouse->update();
        start->update(*mouse);
        options->update(*mouse);
        quit->update(*mouse);
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (start->isSelected)
                    {
                        std::cout << "Start";
                        CreateCharacterScreen();
                    }
                    else if (options->isSelected)
                    {
                        std::cout << "Options";
                    }
                    else if (quit->isSelected)
                    {
                        running = false;
                    }
                }
            }
        }
        SDL_RenderClear(renderer);
        start->draw();
        options->draw();
        quit->draw();
        SDL_Surface* surfaceStart = TTF_RenderText_Solid(font, "START", 5, textColour);
        SDL_Texture* textureStart = SDL_CreateTextureFromSurface(renderer, surfaceStart);
        SDL_FRect textRectStart = { 170,535,fontSize * 5,60 };
        SDL_RenderTexture(renderer, textureStart, NULL, &textRectStart);
        SDL_DestroySurface(surfaceStart);
        SDL_DestroyTexture(textureStart);
        SDL_Surface* surfaceOptions = TTF_RenderText_Solid(font, "OPTIONS", 7, textColour);
        SDL_Texture* textureOptions = SDL_CreateTextureFromSurface(renderer, surfaceOptions);
        SDL_FRect textRectOptions = { 525,535,fontSize * 7,60 };
        SDL_RenderTexture(renderer, textureOptions, NULL, &textRectOptions);
        SDL_DestroySurface(surfaceOptions);
        SDL_DestroyTexture(textureOptions);
        SDL_Surface* surfaceQuit = TTF_RenderText_Solid(font, "QUIT", 4, textColour);
        SDL_Texture* textureQuit = SDL_CreateTextureFromSurface(renderer, surfaceQuit);
        SDL_FRect textRectQuit = { 970,535,fontSize * 4,60 };
        SDL_RenderTexture(renderer, textureQuit, NULL, &textRectQuit);
        SDL_DestroySurface(surfaceQuit);
        SDL_DestroyTexture(textureQuit);
        mouse->draw();

    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}


