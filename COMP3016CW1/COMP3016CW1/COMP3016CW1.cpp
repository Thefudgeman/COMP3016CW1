#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/sdl_image.h>
#include <SDL3/SDL_ttf.h>
#include <SDL3/SDL_surface.h>
#include "Player.h"
#include "Button.h"
#include "Box.h"
#include "PlusStatButton.h"
#include "MinusStatButton.h"
#include "GameButtons.h"
#include "ActionsBox.h"


void GameOver(Player* player)
{
    float fontSize = 33;
    Mouse* mouse = new Mouse();
    TTF_Font* font = TTF_OpenFont("images/font.ttf", 60);
    SDL_Color textColour = { 255,255,255,255 };

    Button* leaveButton = new Button();
    leaveButton->srect.y = 0;
    leaveButton->drect.x = 730;
    leaveButton->drect.y = 570;
    leaveButton->drect.h = 52;
    leaveButton->drect.w = 150;

    Box* finalStatsBox = new Box();
    finalStatsBox->srect.y = 0;
    finalStatsBox->drect.x = 340;
    finalStatsBox->drect.y = 30;

    bool running = true;
    std::string stat;

    while (running)
    {
        SDL_Event event;
        SDL_RenderPresent(renderer);

        mouse->update();
        leaveButton->update(*mouse);
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
                    if (leaveButton->isSelected)
                    {
                        return;
                    }
                }
            }
        }
        SDL_RenderClear(renderer);

        finalStatsBox->draw();

        SDL_Surface* surfaceDied = TTF_RenderText_Solid(font, "YOU HAVE DIED", 14, textColour);
        SDL_Texture* textureDied = SDL_CreateTextureFromSurface(renderer, surfaceDied);
        SDL_FRect textRectDied = { 410,120,fontSize * 14,60 };
        SDL_RenderTexture(renderer, textureDied, NULL, &textRectDied);
        SDL_DestroySurface(surfaceDied);
        SDL_DestroyTexture(textureDied);

        leaveButton->draw();
        SDL_Surface* surfaceLeave = TTF_RenderText_Solid(font, "LEAVE", 6, textColour);
        SDL_Texture* textureLeave = SDL_CreateTextureFromSurface(renderer, surfaceLeave);
        SDL_FRect textRectLeave = { 757,582,fontSize * 3,32 };
        SDL_RenderTexture(renderer, textureLeave, NULL, &textRectLeave);
        SDL_DestroySurface(surfaceLeave);
        SDL_DestroyTexture(textureLeave);

        stat = "FINAL STATS:";
        SDL_Surface* surfacePointsRemaining = TTF_RenderText_Solid(font, stat.c_str(), stat.length(), textColour);
        SDL_Texture* texturePointsRemaining = SDL_CreateTextureFromSurface(renderer, surfacePointsRemaining);
        SDL_FRect textRectPointsRemaining = { 410,250,fontSize * stat.length() / 2,32 };
        SDL_RenderTexture(renderer, texturePointsRemaining, NULL, &textRectPointsRemaining);
        SDL_DestroySurface(surfacePointsRemaining);
        SDL_DestroyTexture(texturePointsRemaining);

        stat = "CLASS:    " + player->getCharacterClass();
        SDL_Surface* surfaceClass = TTF_RenderText_Solid(font, stat.c_str(), stat.length(), textColour);
        SDL_Texture* textureClass = SDL_CreateTextureFromSurface(renderer, surfaceClass);
        SDL_FRect textRectClass = { 410,300,fontSize * stat.length() / 2,32 };
        SDL_RenderTexture(renderer, textureClass, NULL, &textRectClass);
        SDL_DestroySurface(surfaceClass);
        SDL_DestroyTexture(textureClass);

        stat = "HEALTH:   " + std::to_string(player->getMaxHealth());
        SDL_Surface* surfaceHealth = TTF_RenderText_Solid(font, stat.c_str(), stat.length(), textColour);
        SDL_Texture* textureHealth = SDL_CreateTextureFromSurface(renderer, surfaceHealth);
        SDL_FRect textRectHealth = { 410,350,fontSize * stat.length() / 2,32 };
        SDL_RenderTexture(renderer, textureHealth, NULL, &textRectHealth);
        SDL_DestroySurface(surfaceHealth);
        SDL_DestroyTexture(textureHealth);


        stat = "STRENGTH: " + std::to_string(player->getStrength());
        SDL_Surface* surfaceStrength = TTF_RenderText_Solid(font, stat.c_str(), stat.length(), textColour);
        SDL_Texture* textureStrength = SDL_CreateTextureFromSurface(renderer, surfaceStrength);
        SDL_FRect textRectStrength = { 410,400,fontSize * stat.length() / 2,32 };
        SDL_RenderTexture(renderer, textureStrength, NULL, &textRectStrength);
        SDL_DestroySurface(surfaceStrength);
        SDL_DestroyTexture(textureStrength);


        stat = "AGILITY:  " + std::to_string(player->getAgility());
        SDL_Surface* surfaceAgility = TTF_RenderText_Solid(font, stat.c_str(), stat.length(), textColour);
        SDL_Texture* textureAgility = SDL_CreateTextureFromSurface(renderer, surfaceAgility);
        SDL_FRect textRectAgility = { 410,450,fontSize * stat.length() / 2,32 };
        SDL_RenderTexture(renderer, textureAgility, NULL, &textRectAgility);
        SDL_DestroySurface(surfaceAgility);
        SDL_DestroyTexture(textureAgility);


        stat = "LUCK:     " + std::to_string(player->getLuck());
        SDL_Surface* surfaceLuck = TTF_RenderText_Solid(font, stat.c_str(), stat.length(), textColour);
        SDL_Texture* textureLuck = SDL_CreateTextureFromSurface(renderer, surfaceLuck);
        SDL_FRect textRectLuck = { 410,500,fontSize * stat.length() / 2,32 };
        SDL_RenderTexture(renderer, textureLuck, NULL, &textRectLuck);
        SDL_DestroySurface(surfaceLuck);
        SDL_DestroyTexture(textureLuck);

        mouse->draw();

    }
}


void Battle(Player* player)
{
    float fontSize = 33;
    Mouse* mouse = new Mouse();
    TTF_Font* font = TTF_OpenFont("images/font.ttf", 60);
    SDL_Color textColour = { 255,255,255,255 };
    bool running = true;
    bool entered = false;

    while (running)
    {
        SDL_Event event;
        SDL_RenderPresent(renderer);

        mouse->update();
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

                   
                }
            }
        }
        SDL_RenderClear(renderer);


        mouse->draw();

    }
}


void Game(Player* player)
{
    float fontSize = 33;
    Mouse* mouse = new Mouse();
    TTF_Font* font = TTF_OpenFont("images/font.ttf", 60);
    SDL_Color textColour = { 255,255,255,255 };

    Button* enterButton = new Button();
    enterButton->srect.y = 0;
    enterButton->drect.x = 490;
    enterButton->drect.y = 600;

    ActionsBox* actionsBox = new ActionsBox();
    actionsBox->srect.y = 0;
    actionsBox->drect.x = 10;
    actionsBox->drect.y = 500;
    actionsBox->drect.w = 1260;
    actionsBox->drect.h = 220;

    GameButtons* fightButton = new GameButtons();
    fightButton->srect.y = 0;
    fightButton->drect.x = 170;
    fightButton->drect.y = 550;

    GameButtons* runButton = new GameButtons();
    runButton->srect.y = 0;
    runButton->drect.x = 475;
    runButton->drect.y = 550;

    GameButtons* restButton = new GameButtons();
    restButton->srect.y = 0;
    restButton->drect.x = 780;
    restButton->drect.y = 550;

    bool running = true;
    bool entered = false;

    while (running)
    {
        SDL_Event event;
        SDL_RenderPresent(renderer);

        mouse->update();
        if (!entered)
        {
            enterButton->update(*mouse);
        }
        else
        {
            fightButton->update(*mouse);
            runButton->update(*mouse);
            restButton->update(*mouse);
        }
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
                    if (!entered)
                    {
                        if (enterButton->isSelected)
                        {
                            entered = true;
                        }
                    }
                    else
                    {
                        if (fightButton->isSelected)
                        {
                            std::cout << "fight" << std::endl;
                            Battle(player);
                            if (player->getHealth() <= 0)
                            {
                                return;
                            }
                        }
                        if (runButton->isSelected)
                        {
                            int random = rand() % 3;
                            if (random == 0)
                            {
                                player->setHealth(player->getHealth() - player->getHealth() * 0.15);

                                if (player->getHealth() <= 0)
                                {
                                    std::cout << "dead" << std::endl;

                                    GameOver(player);
                                    return;
                                }
                            }
                        }
                        if (restButton->isSelected)
                        {
                            player->setHealth(player->getMaxHealth());
                        }
                    }
                }
            }
        }
        SDL_RenderClear(renderer);
        if (!entered)
        {
            enterButton->draw();
            SDL_Surface* surfaceEnter = TTF_RenderText_Solid(font, "ENTER", 5, textColour);
            SDL_Texture* textureEnter = SDL_CreateTextureFromSurface(renderer, surfaceEnter);
            SDL_FRect textRectEnter = { 560,625,fontSize * 5,60 };
            SDL_RenderTexture(renderer, textureEnter, NULL, &textRectEnter);
            SDL_DestroySurface(surfaceEnter);
            SDL_DestroyTexture(textureEnter);
        }
        else
        {
            actionsBox->draw();

            fightButton->draw();
            SDL_Surface* surfaceFight = TTF_RenderText_Solid(font, "FIGHT", 5, textColour);
            SDL_Texture* textureFight = SDL_CreateTextureFromSurface(renderer, surfaceFight);
            SDL_FRect textRectFight = { 245,575,fontSize * 5,60 };
            SDL_RenderTexture(renderer, textureFight, NULL, &textRectFight);
            SDL_DestroySurface(surfaceFight);
            SDL_DestroyTexture(textureFight);

            runButton->draw();
            SDL_Surface* surfaceRun = TTF_RenderText_Solid(font, "RUN", 3, textColour);
            SDL_Texture* textureRun = SDL_CreateTextureFromSurface(renderer, surfaceRun);
            SDL_FRect textRectRun = { 580,575,fontSize * 3,60 };
            SDL_RenderTexture(renderer, textureRun, NULL, &textRectRun);
            SDL_DestroySurface(surfaceRun);
            SDL_DestroyTexture(textureRun);

            restButton->draw();
            SDL_Surface* surfaceRest = TTF_RenderText_Solid(font, "REST", 4, textColour);
            SDL_Texture* textureRest = SDL_CreateTextureFromSurface(renderer, surfaceRest);
            SDL_FRect textRectRest = { 870,575,fontSize * 4,60 };
            SDL_RenderTexture(renderer, textureRest, NULL, &textRectRest);
            SDL_DestroySurface(surfaceRest);
            SDL_DestroyTexture(textureRest);
        }
        mouse->draw();

    }
}

void CreateCharacterScreen()
{
    TTF_Font* font = TTF_OpenFont("images/font.ttf", 60);
    SDL_Color textColour = { 255,255,255,255 };
    bool allocatePoints = false;
    Player* player = new Player();

    Mouse* mouse = new Mouse();
    Button* back = new Button();
    back->srect.y = 0;
    back->drect.x = 880;
    back->drect.y = 550;
    Box* box = new Box();
    box->srect.y = 0;
    box->drect.x = 200;
    box->drect.y = 10;
    Button* knight = new Button();
    knight->srect.y = 0;
    knight->drect.x = 350;
    knight->drect.y = 200;

    Button* archer = new Button();
    archer->srect.y = 0;
    archer->drect.x = 350;
    archer->drect.y = 300;

    Button* fighter = new Button();
    fighter->srect.y = 0;
    fighter->drect.x = 350;
    fighter->drect.y = 400;

    PlusStatButton* plusHealth = new PlusStatButton();
    plusHealth->srect.y = 0;
    plusHealth->drect.x = 450;
    plusHealth->drect.y = 350;

    MinusStatButton* minusHealth = new MinusStatButton();
    minusHealth->srect.y = 0;
    minusHealth->drect.x = 498;
    minusHealth->drect.y = 350;

    PlusStatButton* plusStrength = new PlusStatButton();
    plusStrength->srect.y = 0;
    plusStrength->drect.x = 450;
    plusStrength->drect.y = 400;
    MinusStatButton* minusStrength = new MinusStatButton();
    minusStrength->srect.y = 0;
    minusStrength->drect.x = 498;
    minusStrength->drect.y = 400;

    PlusStatButton* plusAgility = new PlusStatButton();
    plusAgility->srect.y = 0;
    plusAgility->drect.x = 450;
    plusAgility->drect.y = 450;
    MinusStatButton* minusAgility = new MinusStatButton();
    minusAgility->srect.y = 0;
    minusAgility->drect.x = 498;
    minusAgility->drect.y = 450;

    PlusStatButton* plusLuck = new PlusStatButton();
    plusLuck->srect.y = 0;
    plusLuck->drect.x = 450;
    plusLuck->drect.y = 500;
    MinusStatButton* minusLuck = new MinusStatButton();
    minusLuck->srect.y = 0;
    minusLuck->drect.x = 498;
    minusLuck->drect.y = 500;

    Button* done = new Button();
    done->srect.y = 0;
    done->drect.x = 530;
    done->drect.y = 530;
    done->drect.w = 225;
    done->drect.h = 75;

    float fontSize = 33;
    bool running = true;
    bool pointsShown = false;
    std::string statPoints;
    std::string stat;

    struct
    {
        int maxHealth;
        int strength;
        int agility;
        int luck;
    }originalStats;

    while (running)
    {
        SDL_Event event;
        SDL_RenderPresent(renderer);
        mouse->update();
        back->update(*mouse);
        if (!allocatePoints)
        {
            knight->update(*mouse);
            archer->update(*mouse);
            fighter->update(*mouse);
        }
        else
        {
            plusHealth->update(*mouse);
            minusHealth->update(*mouse);

            plusStrength->update(*mouse);
            minusStrength->update(*mouse);

            plusAgility->update(*mouse);
            minusAgility->update(*mouse);

            plusLuck->update(*mouse);
            minusLuck->update(*mouse);

            done->update(*mouse);
        }

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
                    if (!allocatePoints)
                    {
                        if (knight->isSelected)
                        {
                            allocatePoints = true;
                            player = new Player(11, 5, 2, 4);
                            originalStats.maxHealth = 11;
                            originalStats.strength = 5;
                            originalStats.agility = 2;
                            originalStats.luck = 4;
                            player->setCharacterClass("KNIGHT");
                        }
                        else if (archer->isSelected)
                        {
                            allocatePoints = true;
                            player = new Player(4, 3, 7, 8);
                            originalStats.maxHealth = 4;
                            originalStats.strength = 3;
                            originalStats.agility = 7;
                            originalStats.luck = 8;
                            player->setCharacterClass("ARCHER");
                        }
                        else if (fighter->isSelected)
                        {
                            allocatePoints = true;
                            player = new Player(5, 12, 3, 2);
                            originalStats.maxHealth = 5;
                            originalStats.strength = 12;
                            originalStats.agility = 3;
                            originalStats.luck = 2;
                            player->setCharacterClass("FIGHTER");
                        }

                    }
                    else
                    {
                        if (done->isSelected)
                        {
                            Game(player);
                            return;
                        }

                        if (plusHealth->isSelected && player->getStatPoints() > 0)
                        {
                            player->setMaxHealth(player->getMaxHealth() + 1);
                            player->setStatPoints(player->getStatPoints() - 1);
                            std::cout << player->getStatPoints() << std::endl;
                        }
                        if (minusHealth->isSelected && originalStats.maxHealth < player->getMaxHealth())
                        {
                            player->setMaxHealth(player->getMaxHealth() - 1);
                            player->setStatPoints(player->getStatPoints() + 1);
                            std::cout << player->getStatPoints() << std::endl;
                        }

                        if (plusStrength->isSelected && player->getStatPoints() > 0)
                        {
                            player->setStrength(player->getStrength() + 1);
                            player->setStatPoints(player->getStatPoints() - 1);
                            std::cout << player->getStatPoints() << std::endl;
                        }
                        if (minusStrength->isSelected && originalStats.strength < player->getStrength())
                        {
                            player->setStrength(player->getStrength() - 1);
                            player->setStatPoints(player->getStatPoints() + 1);
                            std::cout << player->getStatPoints() << std::endl;
                        }

                        if (plusAgility->isSelected && player->getStatPoints() > 0)
                        {
                            player->setAgility(player->getAgility() + 1);
                            player->setStatPoints(player->getStatPoints() - 1);
                            std::cout << player->getStatPoints() << std::endl;
                        }
                        if (minusAgility->isSelected && originalStats.agility < player->getAgility())
                        {
                            player->setAgility(player->getAgility() - 1);
                            player->setStatPoints(player->getStatPoints() + 1);
                            std::cout << player->getStatPoints() << std::endl;
                        }

                        if (plusLuck->isSelected && player->getStatPoints() > 0)
                        {
                            player->setLuck(player->getLuck() + 1);
                            player->setStatPoints(player->getStatPoints() - 1);
                            std::cout << player->getStatPoints() << std::endl;
                        }
                        if (minusLuck->isSelected && originalStats.luck < player->getLuck())
                        {
                            player->setLuck(player->getLuck() - 1);
                            player->setStatPoints(player->getStatPoints() + 1);
                            std::cout << player->getStatPoints() << std::endl;
                        }
                    }
                    if (back->isSelected)
                    {
                        running = false;
                    }
                  
                 
                }
            }
        }
        SDL_RenderClear(renderer);
        box->draw();
        back->draw();
        SDL_Surface* surfaceQuit = TTF_RenderText_Solid(font, "BACK", 4, textColour);
        SDL_Texture* textureQuit = SDL_CreateTextureFromSurface(renderer, surfaceQuit);
        SDL_FRect textRectQuit = { 970,575,fontSize * 4,60 };
        SDL_RenderTexture(renderer, textureQuit, NULL, &textRectQuit);
        SDL_DestroySurface(surfaceQuit);
        SDL_DestroyTexture(textureQuit);
        if (!allocatePoints)
        {
            SDL_Surface* surfaceChooseClass = TTF_RenderText_Solid(font, "CHOOSE A CLASS", 15, textColour);
            SDL_Texture* textureChooseClass = SDL_CreateTextureFromSurface(renderer, surfaceChooseClass);
            SDL_FRect textRectChooseClass = { 250,100,fontSize * 15,60 };
            SDL_RenderTexture(renderer, textureChooseClass, NULL, &textRectChooseClass);
            SDL_DestroySurface(surfaceChooseClass);
            SDL_DestroyTexture(textureChooseClass);

            knight->draw();
            SDL_Surface* surfaceKnight = TTF_RenderText_Solid(font, "KNIGHT", 6, textColour);
            SDL_Texture* textureKnight = SDL_CreateTextureFromSurface(renderer, surfaceKnight);
            SDL_FRect textRectKnight = { 400,225,fontSize * 6,60 };
            SDL_RenderTexture(renderer, textureKnight, NULL, &textRectKnight);
            SDL_DestroySurface(surfaceKnight);
            SDL_DestroyTexture(textureKnight);

            archer->draw();
            SDL_Surface* surfaceArcher = TTF_RenderText_Solid(font, "ARCHER", 6, textColour);
            SDL_Texture* textureArcher = SDL_CreateTextureFromSurface(renderer, surfaceArcher);
            SDL_FRect textRectArcher = { 400,325,fontSize * 6,60 };
            SDL_RenderTexture(renderer, textureArcher, NULL, &textRectArcher);
            SDL_DestroySurface(surfaceArcher);
            SDL_DestroyTexture(textureArcher);

            fighter->draw();
            SDL_Surface* surfaceBerserker = TTF_RenderText_Solid(font, "FIGHTER", 7, textColour);
            SDL_Texture* textureBerserker = SDL_CreateTextureFromSurface(renderer, surfaceBerserker);
            SDL_FRect textRectBerserker = { 385,425,fontSize * 7,60 };
            SDL_RenderTexture(renderer, textureBerserker, NULL, &textRectBerserker);
            SDL_DestroySurface(surfaceBerserker);
            SDL_DestroyTexture(textureBerserker);
        }
        else
        {
            done->draw();
            SDL_Surface* surfaceDone = TTF_RenderText_Solid(font, "DONE", 4, textColour);
            SDL_Texture* textureDone = SDL_CreateTextureFromSurface(renderer, surfaceDone);
            SDL_FRect textRectDone = { 595,547,fontSize * 3,48 };
            SDL_RenderTexture(renderer, textureDone, NULL, &textRectDone);
            SDL_DestroySurface(surfaceDone);
            SDL_DestroyTexture(textureDone);

            SDL_Surface* surfaceAllocatePoints = TTF_RenderText_Solid(font, "ALLOCATE POINTS", 16, textColour);
            SDL_Texture* textureAllocatePoints = SDL_CreateTextureFromSurface(renderer, surfaceAllocatePoints);
            SDL_FRect textRectAllocatePoints = { 250,100,fontSize * 15,60 };
            SDL_RenderTexture(renderer, textureAllocatePoints, NULL, &textRectAllocatePoints);
            SDL_DestroySurface(surfaceAllocatePoints);
            SDL_DestroyTexture(textureAllocatePoints);

            statPoints = "REMAINING POINTS: " + std::to_string(player->getStatPoints());
            SDL_Surface* surfacePointsRemaining = TTF_RenderText_Solid(font, statPoints.c_str(), statPoints.length(), textColour);
            SDL_Texture* texturePointsRemaining = SDL_CreateTextureFromSurface(renderer, surfacePointsRemaining);
            SDL_FRect textRectPointsRemaining = { 250,300,fontSize * statPoints.length() /2,32 };
            SDL_RenderTexture(renderer, texturePointsRemaining, NULL, &textRectPointsRemaining);
            SDL_DestroySurface(surfacePointsRemaining);
            SDL_DestroyTexture(texturePointsRemaining);

            stat = "HEALTH:   " + std::to_string(player->getMaxHealth());
            SDL_Surface* surfaceHealth = TTF_RenderText_Solid(font, stat.c_str(), stat.length(), textColour);
            SDL_Texture* textureHealth = SDL_CreateTextureFromSurface(renderer, surfaceHealth);
            SDL_FRect textRectHealth = { 250,350,fontSize * stat.length() / 2,32 };
            SDL_RenderTexture(renderer, textureHealth, NULL, &textRectHealth);
            SDL_DestroySurface(surfaceHealth);
            SDL_DestroyTexture(textureHealth);
            plusHealth->draw();
            minusHealth->draw();

            stat = "STRENGTH: " + std::to_string(player->getStrength());
            SDL_Surface* surfaceStrength = TTF_RenderText_Solid(font, stat.c_str(), stat.length(), textColour);
            SDL_Texture* textureStrength = SDL_CreateTextureFromSurface(renderer, surfaceStrength);
            SDL_FRect textRectStrength = { 250,400,fontSize * stat.length() / 2,32 };
            SDL_RenderTexture(renderer, textureStrength, NULL, &textRectStrength);
            SDL_DestroySurface(surfaceStrength);
            SDL_DestroyTexture(textureStrength);
            plusStrength->draw();
            minusStrength->draw();

            stat = "AGILITY:  " + std::to_string(player->getAgility());
            SDL_Surface* surfaceAgility = TTF_RenderText_Solid(font, stat.c_str(), stat.length(), textColour);
            SDL_Texture* textureAgility = SDL_CreateTextureFromSurface(renderer, surfaceAgility);
            SDL_FRect textRectAgility = { 250,450,fontSize * stat.length() / 2,32 };
            SDL_RenderTexture(renderer, textureAgility, NULL, &textRectAgility);
            SDL_DestroySurface(surfaceAgility);
            SDL_DestroyTexture(textureAgility);
            plusAgility->draw();
            minusAgility->draw();

            stat = "LUCK:     " + std::to_string(player->getLuck());
            SDL_Surface* surfaceLuck = TTF_RenderText_Solid(font, stat.c_str(), stat.length(), textColour);
            SDL_Texture* textureLuck = SDL_CreateTextureFromSurface(renderer, surfaceLuck);
            SDL_FRect textRectLuck = { 250,500,fontSize * stat.length() / 2,32 };
            SDL_RenderTexture(renderer, textureLuck, NULL, &textRectLuck);
            SDL_DestroySurface(surfaceLuck);
            SDL_DestroyTexture(textureLuck);
            plusLuck->draw();
            minusLuck->draw();
        }
        
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


