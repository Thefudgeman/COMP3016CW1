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
#include "Enemy.h"
#include "Entrance.h"
#include "DungeonRoom.h"



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


void Battle(Player* player, Enemy* enemy)
{
    float fontSize = 28;
    Mouse* mouse = new Mouse();
    TTF_Font* font = TTF_OpenFont("images/font.ttf", 60);
    SDL_Color textColour = { 255,255,255,255 };
    SDL_Color healthTextColour = { 255, 0, 0, 255 };

    DungeonRoom* dungeonRoom = new DungeonRoom();

    ActionsBox* actionsBox = new ActionsBox();
    actionsBox->srect.y = 0;
    actionsBox->drect.x = 10;
    actionsBox->drect.y = 500;
    actionsBox->drect.w = 1260;
    actionsBox->drect.h = 220;

    GameButtons* attackButton = new GameButtons();
    attackButton->srect.y = 0;
    attackButton->drect.x = 170;
    attackButton->drect.y = 550;

    GameButtons* itemButton = new GameButtons();
    itemButton->srect.y = 0;
    itemButton->drect.x = 475;
    itemButton->drect.y = 550;

    GameButtons* runButton = new GameButtons();
    runButton->srect.y = 0;
    runButton->drect.x = 780;
    runButton->drect.y = 550;

    bool running = true;
    bool entered = false;
    std::string health;
   

    while (running)
    {
        SDL_Event event;
        SDL_RenderPresent(renderer);

        mouse->update();
        attackButton->update(*mouse);
        itemButton->update(*mouse);
        runButton->update(*mouse);
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

                    if (attackButton->isSelected)
                    {
                        enemy->setHealth(enemy->getHealth() - player->getStrength());
                        std::cout << enemy->getHealth() << enemy->getName() << currentFloor << std::endl;
                        if (enemy->getHealth() <= 0)
                        {
                            return;
                        }
                        else if (player->getHealth() <= 0)
                        {
                            GameOver(player);
                        }
                    }
                    if (itemButton->isSelected)
                    {

                    }
                    if (runButton->isSelected)
                    {
                        int random = rand() % 3;
                        if (random == 0)
                        {

                        }
                        else
                        {
                            return;
                        }
                    }
                   
                }
            }
        }
        SDL_RenderClear(renderer);
        dungeonRoom->draw();
        enemy->draw();
        actionsBox->draw();

        attackButton->draw();
        SDL_Surface* surfaceFight = TTF_RenderText_Solid(font, "ATTACK", 7, textColour);
        SDL_Texture* textureFight = SDL_CreateTextureFromSurface(renderer, surfaceFight);
        SDL_FRect textRectFight = { 225,575,fontSize * 7,60 };
        SDL_RenderTexture(renderer, textureFight, NULL, &textRectFight);
        SDL_DestroySurface(surfaceFight);
        SDL_DestroyTexture(textureFight);

        itemButton->draw();
        SDL_Surface* surfaceRun = TTF_RenderText_Solid(font, "ITEM", 4, textColour);
        SDL_Texture* textureRun = SDL_CreateTextureFromSurface(renderer, surfaceRun);
        SDL_FRect textRectRun = { 570,575,fontSize * 4,60 };
        SDL_RenderTexture(renderer, textureRun, NULL, &textRectRun);
        SDL_DestroySurface(surfaceRun);
        SDL_DestroyTexture(textureRun);

        runButton->draw();
        SDL_Surface* surfaceRest = TTF_RenderText_Solid(font, "RUN", 3, textColour);
        SDL_Texture* textureRest = SDL_CreateTextureFromSurface(renderer, surfaceRest);
        SDL_FRect textRectRest = { 890,575,fontSize * 3,60 };
        SDL_RenderTexture(renderer, textureRest, NULL, &textRectRest);
        SDL_DestroySurface(surfaceRest);
        SDL_DestroyTexture(textureRest);

        health = std::to_string(player->getHealth()) + "/" + std::to_string(player->getMaxHealth());
        SDL_Surface* surfacePlayerHealth = TTF_RenderText_Solid(font, health.c_str(), health.length(), healthTextColour);
        SDL_Texture* texturePlayerHealth = SDL_CreateTextureFromSurface(renderer, surfacePlayerHealth);
        SDL_FRect textRectPlayerHealth = { 225,275,fontSize * health.length()/2,32};
        SDL_RenderTexture(renderer, texturePlayerHealth, NULL, &textRectPlayerHealth);
        SDL_DestroySurface(surfacePlayerHealth);
        SDL_DestroyTexture(texturePlayerHealth);

        health = std::to_string(enemy->getHealth()) + "/" + std::to_string(enemy->getMaxHealth());
        SDL_Surface* surfaceEnemyHealth = TTF_RenderText_Solid(font, health.c_str(), health.length(), healthTextColour);
        SDL_Texture* textureEnemyHealth = SDL_CreateTextureFromSurface(renderer, surfaceEnemyHealth);
        SDL_FRect textRectEnemyHealth = { 225,100,fontSize * health.length() / 2,32 };
        SDL_RenderTexture(renderer, textureEnemyHealth, NULL, &textRectEnemyHealth);
        SDL_DestroySurface(surfaceEnemyHealth);
        SDL_DestroyTexture(textureEnemyHealth);

        mouse->draw();

    }
}

Enemy* GetEnemy(Enemy* enemy)
{
    int random = rand() % 10;
    SDL_DestroyTexture(enemy->texture);
    switch (currentFloor) //optimise later
    {
    case 1:
        if (random < 5)
        {
            enemy = new Enemy(2, 1, 1, 1, 50, "Slime");

        }
        else if (random > 4 && random < 8)
        {
            enemy = new Enemy(3, 3, 1, 1, 100, "Zombie");
        }
        else
        {
            enemy = new Enemy(4, 3, 2, 2, 150, "Skeleton");
        }
        break;
    case 2:
        if (random < 5)
        {
            enemy = new Enemy(3, 3, 1, 1, 100, "Zombie");
        }
        else if (random > 4 && random < 8)
        {
            enemy = new Enemy(4, 3, 2, 2, 150, "Skeleton");
        }
        else
        {
            enemy = new Enemy(4, 5, 5, 4, 250, "Goblin");
        }
        break;
    case 3:
        if (random < 5)
        {
            enemy = new Enemy(4, 3, 2, 2, 150, "Skeleton");
        }
        else if (random > 4 && random < 8)
        {
            enemy = new Enemy(4, 5, 5, 4, 250, "Goblin");
        }
        else
        {
            enemy = new Enemy(7, 5, 2, 4, 350, "Ogre");
        }
        break;
    case 4:
        if (random < 5)
        {
            enemy = new Enemy(4, 5, 5, 4, 250, "Goblin");
        }
        else if (random > 4 && random < 8)
        {
            enemy = new Enemy(7, 5, 2, 4, 350, "Ogre");
        }
        else
        {
            enemy = new Enemy(13, 12, 7, 6, 500, "Minotaur");
        }
        break;
    case 5:
        if (random < 5)
        {
            enemy = new Enemy(7, 5, 2, 4, 350, "Ogre");
        }
        else if (random > 4 && random < 8)
        {
            enemy = new Enemy(13, 12, 7, 6, 500, "Minotaur");
        }
        else
        {
            enemy = new Enemy(10, 10, 15, 9, 600, "Griffin");
        }
        break;
    case 6:
        if (random < 5)
        {
            enemy = new Enemy(13, 12, 7, 6, 500, "Minotaur");
        }
        else if (random > 4 && random < 8)
        {
            enemy = new Enemy(10, 10, 15, 9, 600, "Griffin");
        }
        else
        {
            enemy = new Enemy(12, 13, 13, 8, 800, "Wraith");
        }
        break;
    case 7:
        if (random < 5)
        {
            enemy = new Enemy(10, 10, 15, 9, 600, "Griffin");
        }
        else if (random > 4 && random < 8)
        {
            enemy = new Enemy(12, 13, 13, 8, 800, "Wraith");
        }
        else
        {
            enemy = new Enemy(16, 19, 13, 10, 1000, "Vampire");
        }
        break;
    case 8:
        if (random < 5)
        {
            enemy = new Enemy(12, 13, 13, 8, 800, "Wraith");
        }
        else if (random > 4 && random < 8)
        {
            enemy = new Enemy(16, 19, 13, 10, 1000, "Vampire");
        }
        else
        {
            enemy = new Enemy(25, 15, 7, 11, 1300, "Golem");
        }
        break;
    case 9:
        if (random < 5)
        {
            enemy = new Enemy(16, 19, 13, 10, 1000, "Vampire");
        }
        else if (random > 4 && random < 8)
        {
            enemy = new Enemy(25, 15, 7, 11, 1300, "Golem");
        }
        else
        {
            enemy = new Enemy(25, 21, 19, 17, 1800, "Demon");
        }
        break;
    case 10:
        if (random < 5)
        {
            enemy = new Enemy(25, 15, 7, 11, 1300, "Golem");
        }
        else if (random > 4 && random < 8)
        {
            enemy = new Enemy(25, 21, 19, 17, 1800, "Demon");
        }
        else
        {
            enemy = new Enemy(40, 33, 21, 20, 1800, "Dragon");
        }
        break;
    }
    return enemy;
}


void Game(Player* player)
{
    float fontSize = 33;
    Mouse* mouse = new Mouse();
    TTF_Font* font = TTF_OpenFont("images/font.ttf", 60);
    SDL_Color textColour = { 255,255,255,255 };

    Entrance* entranceImg = new Entrance();

    DungeonRoom* dungeonRoom = new DungeonRoom();

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

    Button* quitButton = new Button();
    quitButton->srect.y = 0;
    quitButton->drect.x = 20;
    quitButton->drect.y = 20;
    quitButton->drect.h = 52;
    quitButton->drect.w = 150;

    Button* previousFloorButton = new Button();
    previousFloorButton->srect.y = 0;
    previousFloorButton->drect.x = 200;
    previousFloorButton->drect.y = 20;
    previousFloorButton->drect.h = 52;
    previousFloorButton->drect.w = 180;

    Button* nextFloorButton = new Button();
    nextFloorButton->srect.y = 0;
    nextFloorButton->drect.x = 400;
    nextFloorButton->drect.y = 20;
    nextFloorButton->drect.h = 52;
    nextFloorButton->drect.w = 180;
        
    Enemy* enemy = new Enemy();
    enemy->srect.y = 0;

    enemy = GetEnemy(enemy);

    

    bool running = true;
    bool entered = false;
    bool canGoToFloor = false;

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
        quitButton->update(*mouse);

        if (actionsOnFloorTaken >= 7)
        {
            canGoToFloor = true;
        }
        if (canGoToFloor || currentFloor < highestFloor)
        {
            nextFloorButton->update(*mouse);
        }
        if (currentFloor > 1)
        {
            previousFloorButton->update(*mouse);
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
                            Battle(player, enemy);
                            if (player->getHealth() <= 0)
                            {
                                return;
                            }
                            actionsOnFloorTaken++;
                            enemy = GetEnemy(enemy);
                            std::cout << enemy->getName() << std::endl;
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
                            actionsOnFloorTaken++;
                            enemy = GetEnemy(enemy);
                        }
                        if (restButton->isSelected)
                        {
                            player->setHealth(player->getMaxHealth());
                            actionsOnFloorTaken++;
                            std::cout << actionsOnFloorTaken << std::endl;
                            enemy = GetEnemy(enemy);
                        }
                    }
                    if (quitButton->isSelected)
                    {
                        return;
                    }
                    if (nextFloorButton->isSelected)
                    {
                        currentFloor++;
                        actionsOnFloorTaken = 0;
                        std::cout << actionsOnFloorTaken << std::endl;
                        nextFloorButton->isSelected = false;
                        if (highestFloor < currentFloor)
                        {
                            highestFloor = currentFloor;
                            canGoToFloor = false;
                        }
                    }
                    if (previousFloorButton->isSelected)
                    {
                        currentFloor--;
                        actionsOnFloorTaken = 0;
                        previousFloorButton->isSelected = false;
                    }
                }
            }
        }
        SDL_RenderClear(renderer);

        if (!entered)
        {
            entranceImg->draw();
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
            dungeonRoom->draw();
            enemy->draw();

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

            if (currentFloor > 1)
            {
                previousFloorButton->draw();
                SDL_Surface* surfacePreviousFloor = TTF_RenderText_Solid(font, "PREVIOUS FLOOR", 15, textColour);
                SDL_Texture* texturePreviousFloor = SDL_CreateTextureFromSurface(renderer, surfacePreviousFloor);
                SDL_FRect textRectPreviousFloor = { 230,40,fontSize * 15 / 4, 16 };
                SDL_RenderTexture(renderer, texturePreviousFloor, NULL, &textRectPreviousFloor);
                SDL_DestroySurface(surfacePreviousFloor);
                SDL_DestroyTexture(texturePreviousFloor);
            }
            if (canGoToFloor || currentFloor < highestFloor)
            {
                nextFloorButton->draw();
                SDL_Surface* surfaceNextFloor = TTF_RenderText_Solid(font, "NEXT FLOOR", 10, textColour);
                SDL_Texture* textureNextFloor = SDL_CreateTextureFromSurface(renderer, surfaceNextFloor);
                SDL_FRect textRectNextFloor = { 435,35,fontSize * 10 / 3, 24 };
                SDL_RenderTexture(renderer, textureNextFloor, NULL, &textRectNextFloor);
                SDL_DestroySurface(surfaceNextFloor);
                SDL_DestroyTexture(textureNextFloor);
            }
        }
        quitButton->draw();
        SDL_Surface* surfaceQuit = TTF_RenderText_Solid(font, "QUIT", 4, textColour);
        SDL_Texture* textureQuit = SDL_CreateTextureFromSurface(renderer, surfaceQuit);
        SDL_FRect textRectQuit = { 65,32,fontSize * 2,32 };
        SDL_RenderTexture(renderer, textureQuit, NULL, &textRectQuit);
        SDL_DestroySurface(surfaceQuit);
        SDL_DestroyTexture(textureQuit);
        mouse->draw();

    }
}

void CreateCharacterScreen()
{
    TTF_Font* font = TTF_OpenFont("images/font.ttf", 60);
    SDL_Color textColour = { 255,255,255,255 };
    bool allocatePoints = false;
    Player* player = new Player();

    Entrance* entranceImg = new Entrance();

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
        entranceImg->draw();
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

    Entrance* entranceImg = new Entrance();

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
        entranceImg->draw();
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


