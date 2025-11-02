#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/sdl_image.h>
#include <SDL3/SDL_ttf.h>
#include <SDL3/SDL_surface.h>
#include <vector>
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
#include "Campire.h"

void RenderText(const std::string& text, float x, float y, float fontLength, TTF_Font* font, SDL_Color colour, int fontSize) //method to reuse when creating text
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), text.length(), colour);
    if (!surface) return;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) { SDL_DestroySurface(surface); return; }

    SDL_FRect rect = { x, y, fontLength * text.length(), fontSize };
    SDL_RenderTexture(renderer, texture, NULL, &rect);

    SDL_DestroySurface(surface);
    SDL_DestroyTexture(texture);
}

void FadeTransition(bool fadeIn, int durationMs)
{
    int startTime = SDL_GetTicks();
    int alpha = fadeIn ? 255 : 0;
    SDL_Surface* surface = SDL_RenderReadPixels(renderer, NULL);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderTexture(renderer, texture, NULL, NULL); //gets a snapshot of the current scene and renders it under the fade transition

    while (true)
    {
        int elapsed = SDL_GetTicks() - startTime;
        float progress = (float)elapsed / durationMs;
        if (progress > 1.0f) //progress cannot be larger than 1
        {
            progress = 1.0f;
        }

        if (fadeIn) //changes transparancy of black square for fade transition
        {
            alpha = (255 * (1.0f - progress)); 
        }
        else
        {
            alpha = (255 * progress);
        }      

        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
        SDL_RenderFillRect(renderer, NULL);
        SDL_RenderPresent(renderer);

        if (elapsed >= durationMs) //once fade transition is complete exit the loop
        {
            break;
        }

        SDL_Delay(16);
    }
    SDL_DestroySurface(surface);
    SDL_DestroyTexture(texture);
}

void CampfireScene() //fades in and out when player rests
{
    Campfire* campfire = new Campfire();
    bool running = true;
    bool fadeIn = true;
    while (running)
    {
        SDL_Event event;
        SDL_RenderPresent(renderer);
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
        campfire->draw();
        if (fadeIn)
        {
            FadeTransition(true, 1500);
            fadeIn = false;
            FadeTransition(false, 1500);
            return;
        }
        SDL_Delay(16);
    }
}


void GameOver(Player* player, bool victory) //victory determines if the player won or died
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

    DungeonRoom* dungeonRoom = new DungeonRoom();

    Box* finalStatsBox = new Box();
    finalStatsBox->srect.y = 0;
    finalStatsBox->drect.x = 340;
    finalStatsBox->drect.y = 30;

    bool running = true;
    std::string stat;
    bool fadeIn = true;

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
                    if (leaveButton->isSelected) //returns to title scene
                    {
                        FadeTransition(false, 800);
                        return;
                    }
                }
            }
        }
        SDL_RenderClear(renderer);
        dungeonRoom->draw();
        finalStatsBox->draw();
        if (!victory) //if player died
        {
            RenderText("YOU HAVE DIED", 410, 120, fontSize, font, textColour, 60);

        }
        else //if player won
        {
            RenderText("YOU HAVE SLAIN", 400, 120, fontSize, font, textColour, 60);
            RenderText("THE DRAGON", 460, 180, fontSize, font, textColour, 60);


        }

        leaveButton->draw();

        RenderText("LEAVE", 757, 582, fontSize/2, font, textColour, 32);

        RenderText("FINAL STATS:", 410, 250, fontSize/2, font, textColour, 32);

        RenderText("CLASS:    " + player->getCharacterClass(), 410, 300, fontSize/2, font, textColour, 32);


        RenderText("LEVEL:    " + std::to_string(player->getLevel()), 410, 350, fontSize/2, font, textColour, 32);

        RenderText("HEALTH:   " + std::to_string(player->getMaxHealth()), 410, 400, fontSize/2, font, textColour, 32);

        RenderText("STRENGTH: " + std::to_string(player->getStrength()), 410, 450, fontSize/2, font, textColour, 32);


        RenderText("AGILITY:  " + std::to_string(player->getAgility()), 410, 500, fontSize/2, font, textColour, 32);


        RenderText("LUCK:     " + std::to_string(player->getLuck()), 410, 550, fontSize/2, font, textColour, 32);

        mouse->draw();
        if (fadeIn)
        {
            FadeTransition(true, 800);
            fadeIn = false;
        }
        SDL_Delay(16);
    }
}


float SmoothStep(float t) {
    return t * t * (3 - 2 * t);
}

float Lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

void RenderHealthBar(SDL_Renderer* renderer, int x, int y, int w, int h, float displayHP, float maxHP)
{
    if (!renderer || maxHP <= 0) return;

    float healthRatio = displayHP / maxHP;
    if (healthRatio < 0.0f) healthRatio = 0.0f;
    if (healthRatio > 1.0f) healthRatio = 1.0f;

    SDL_FRect border{ x - 2, y - 2, w + 4, h + 4 };
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderFillRect(renderer, &border);

    SDL_FRect empty{ x, y, w, h };
    SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
    SDL_RenderFillRect(renderer, &empty);

    Uint8 r, g, b;
    if (healthRatio > 0.5f) {
        float t = (healthRatio - 0.5f) / 0.5f;
        r = static_cast<Uint8>(255 * (1.0f - t));
        g = 255;
        b = 0;
    }
    else {
        float t = healthRatio / 0.5f;
        r = 255;
        g = static_cast<Uint8>(255 * t);
        b = 0;
    }

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_FRect fill{ x, y, static_cast<int>(w * healthRatio), h };
    SDL_RenderFillRect(renderer, &fill);
}

void Battle(Player* player, Enemy* enemy)
{
    float fontSize = 28;
    Mouse* mouse = new Mouse();
    TTF_Font* font = TTF_OpenFont("images/font.ttf", 60);
    SDL_Color textColour = { 255,255,255,255 };

    DungeonRoom* dungeonRoom = new DungeonRoom();

    ActionsBox* actionsBox = new ActionsBox();
    actionsBox->drect.x = 10;
    actionsBox->drect.y = 500;
    actionsBox->drect.w = 1260;
    actionsBox->drect.h = 220;

    GameButtons* attackButton = new GameButtons();
    attackButton->drect.x = 170;
    attackButton->drect.y = 550;

    GameButtons* itemButton = new GameButtons();
    itemButton->drect.x = 475;
    itemButton->drect.y = 550;

    GameButtons* runButton = new GameButtons();
    runButton->drect.x = 780;
    runButton->drect.y = 550;

    bool running = true;
    bool fadeIn = true;
    bool enemyDefeated = false;


    float displayPlayerHP = player->getHealthPoints();
    float displayEnemyHP = enemy->getHealthPoints();


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
                if (event.button.button == SDL_BUTTON_LEFT && !enemyDefeated)
                {
                    if (attackButton->isSelected)
                    {
                        srand(time(NULL)); //stops random numbers appearing in same order when reloading game
                        int dodge = rand() % 100;
                        int critHit = rand() % 100;
                        if (dodge > enemy->getAgility())
                        {
                            float damage = player->getStrengthPoints();
                            if (critHit < player->getLuck())
                            {
                                damage *= 1.7f;
                            }
                            enemy->setHealthPoints(enemy->getHealthPoints() - damage);
                        }


                        if (enemy->getHealthPoints() <= 0)
                        {
                            enemy->setHealthPoints(0);
                            enemyDefeated = true; 
                        }


                        if (!enemyDefeated)
                        {
                            dodge = rand() % 100;
                            critHit = rand() % 100;
                            if (dodge > player->getAgility())
                            {
                                float damage = enemy->getStrengthPoints();
                                if (critHit < enemy->getLuck())
                                {
                                    damage *= 1.7f;
                                }
                                player->setHealthPoints(player->getHealthPoints() - damage);
                            }


                            if (player->getHealthPoints() <= 0)
                            {
                                FadeTransition(false, 800);
                                GameOver(player, false);
                                return;
                            }
                        }
                    }
                }
            }
        }

        float t = 0.1f; 
        float easedT = SmoothStep(t);
        displayPlayerHP = Lerp(displayPlayerHP, player->getHealthPoints(), easedT);
        displayEnemyHP = Lerp(displayEnemyHP, enemy->getHealthPoints(), easedT);

        SDL_RenderClear(renderer);
        dungeonRoom->draw();
        enemy->draw();
        actionsBox->draw();

        attackButton->draw();
        RenderText("ATTACK", 225, 575, fontSize, font, textColour, 60);
        itemButton->draw();
        RenderText("ITEM", 570, 575, fontSize, font, textColour, 60);
        runButton->draw();
        RenderText("RUN", 890, 575, fontSize, font, textColour, 60);

        RenderText("YOU: " + std::to_string((int)player->getHealthPoints()) + "/" + std::to_string((int)player->getMaxHealthPoints()), 110, 400, fontSize / 2, font, textColour, 32);
        RenderHealthBar(renderer, 110, 435, 300, 20, displayPlayerHP, player->getMaxHealthPoints());


        RenderText(enemy->getName() + ": " + std::to_string((int)enemy->getHealthPoints()) + "/" + std::to_string((int)enemy->getMaxHealthPoints()), 920, 400, fontSize / 2, font, textColour, 32);
        RenderHealthBar(renderer, 920, 435, 300, 20, displayEnemyHP, enemy->getMaxHealthPoints());
        mouse->draw();

        if (fadeIn)
        {
            FadeTransition(true, 800);
            fadeIn = false;
        }

        if (enemyDefeated && displayEnemyHP <= 0.5f)
        {
            player->gainXp(enemy->getGiveXp());
            FadeTransition(false, 800);
            if (enemy->getName() == "Dragon")
            {
                gameVictory = true;
                GameOver(player, true);
            }
            
            return;
        }

        SDL_Delay(16);
    }
}

Enemy* GetEnemy(Enemy* oldEnemy)
{
    if (oldEnemy && oldEnemy->texture)
    {
        SDL_DestroyTexture(oldEnemy->texture);
    }

    struct EnemyTemplate {
        int hp, strength, agility, luck, xp;
        const char* name;
    };

    static const std::vector<std::vector<EnemyTemplate>> floorEnemies = {
        // Floor 1
        { {2,1,1,1,50,"Slime"}, {3,3,1,1,100,"Zombie"}, {4,3,2,2,150,"Skeleton"} },
        // Floor 2
        { {3,3,1,1,100,"Zombie"}, {4,3,2,2,150,"Skeleton"}, {4,5,5,4,250,"Goblin"} },
        // Floor 3
        { {4,3,2,2,150,"Skeleton"}, {4,5,5,4,250,"Goblin"}, {7,5,2,4,350,"Ogre"} },
        // Floor 4
        { {4,5,5,4,250,"Goblin"}, {7,5,2,4,350,"Ogre"}, {13,12,7,6,500,"Minotaur"} },
        // Floor 5
        { {7,5,2,4,350,"Ogre"}, {13,12,7,6,500,"Minotaur"}, {10,10,15,9,600,"Griffin"} },
        // Floor 6
        { {13,12,7,6,500,"Minotaur"}, {10,10,15,9,600,"Griffin"}, {12,13,13,8,800,"Wraith"} },
        // Floor 7
        { {10,10,15,9,600,"Griffin"}, {12,13,13,8,800,"Wraith"}, {16,19,13,10,1000,"Vampire"} },
        // Floor 8
        { {12,13,13,8,800,"Wraith"}, {16,19,13,10,1000,"Vampire"}, {25,15,7,11,1300,"Golem"} },
        // Floor 9
        { {16,19,13,10,1000,"Vampire"}, {25,15,7,11,1300,"Golem"}, {25,21,19,17,1800,"Demon"} },
        // Floor 10
        { {25,15,7,11,1300,"Golem"}, {25,21,19,17,1800,"Demon"}, {40,33,21,20,2500,"Dragon"} }
    };

    int floorIndex = currentFloor - 1;
    if (floorIndex < 0)
    {
        floorIndex = 0;
    }
    if (floorIndex >= (int)floorEnemies.size())
    {
        floorIndex = (int)floorEnemies.size() - 1;
    }
    srand(time(NULL)); //stops random numbers appearing in same order when reloading game
    int random = rand() % 10;
    int index;
    if (random < 5)
    {
        index = 0;
    }
    else if (random < 8)
    {
        index = 1;
    }
    else
    {
        index = 2;
    }

    const EnemyTemplate nextEnemy = floorEnemies[floorIndex][index];

    Enemy* enemy = new Enemy(nextEnemy.hp, nextEnemy.strength, nextEnemy.agility, nextEnemy.luck, nextEnemy.xp, nextEnemy.name);
    enemy->setMaxHealthPoints(enemy->getMaxHealth());
    enemy->setHealthPoints(enemy->getMaxHealthPoints());
    enemy->setStrengthPoints(enemy->getStrength());

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

    Button* showCurrentFloor = new Button();
    showCurrentFloor->srect.y = 0;
    showCurrentFloor->drect.x = 20;
    showCurrentFloor->drect.y = 100;
    showCurrentFloor->drect.h = 52;
    showCurrentFloor->drect.w = 180;

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
        
    Box* box = new Box();
    box->srect.y = 0;
    box->drect.x = 200;
    box->drect.y = 10;

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
    struct
    {
        int maxHealth;
        int strength;
        int agility;
        int luck;
    }originalStats;
    originalStats.agility = player->getAgility();
    originalStats.luck = player->getLuck();
    originalStats.maxHealth = player->getMaxHealth();
    originalStats.strength = player->getStrength();
    bool pointsShown = false;
    std::string statPoints;
    std::string stat;
    std::string currentFloorText;

    Enemy* enemy = new Enemy();
    enemy->srect.y = 0;

    enemy = GetEnemy(enemy);

    bool fadeIn = true;

    

    bool running = true;
    bool entered = false;
    bool canGoToFloor = false;
    float displayPlayerHP = player->getHealthPoints();

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
            if (player->getStatPoints() > 0)
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
            else if (player->getStatPoints() == 0)
            {
                fightButton->update(*mouse);
                runButton->update(*mouse);
                restButton->update(*mouse);
            }

        }
        quitButton->update(*mouse);

        if (actionsOnFloorTaken >= 7)
        {
            canGoToFloor = true;
        }
        if (canGoToFloor || currentFloor < highestFloor) //only let the player go to the next floor if they have met the correct conditions
        {
            nextFloorButton->update(*mouse);
        }
        if (currentFloor > 1) //player can go to previous floor at any time unless they are on floor 1 as there is no floor 0
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
                            FadeTransition(false, 800);
                            entered = true;
                            fadeIn = true;
                        }
                    }
                    else
                    {
                        if (player->getStatPoints() == 0) //if player has no stat points to allocate then continue with game
                        {
                            if (fightButton->isSelected) // player enters combat
                            {
                                std::cout << "fight" << std::endl;
                                FadeTransition(false, 800);
                                Battle(player, enemy);
                                if (player->getHealthPoints() <= 0)
                                {
                                    return;
                                }
                                fadeIn = true;
                                actionsOnFloorTaken++;
                                enemy = GetEnemy(enemy);
                                std::cout << enemy->getName() << std::endl;
                            }
                            if (runButton->isSelected) // player has a chance to take 15% of health as damage if they run from an enemy
                            {
                                int random = rand() % 3;
                                if (random == 0)
                                {
                                    player->setHealthPoints(player->getHealthPoints() - player->getMaxHealthPoints() * 0.15);

                                    if (player->getHealth() <= 0)
                                    {
                                        std::cout << "dead" << std::endl;

                                        FadeTransition(false, 800);
                                        GameOver(player, false);
                                        return;
                                    }
                                }
                                actionsOnFloorTaken++;
                                enemy = GetEnemy(enemy);
                            }
                            if (restButton->isSelected) //the player can rest to fully heal their character
                            {
                                player->setHealthPoints(player->getMaxHealthPoints());
                                FadeTransition(false, 800);
                                CampfireScene();
                                fadeIn = true;
                                actionsOnFloorTaken++;
                                std::cout << actionsOnFloorTaken << std::endl;
                                enemy = GetEnemy(enemy);
                            }
                        }
                        else //make player allocate remaining stat points when they level up
                        {
                            if (plusHealth->isSelected && player->getStatPoints() > 0)
                            {
                                player->setMaxHealth(player->getMaxHealth() + 1);
                                player->setStatPoints(player->getStatPoints() - 1);
                                player->setMaxHealthPoints(player->getMaxHealth());
                                std::cout << player->getStatPoints() << std::endl;
                            }
                            if (minusHealth->isSelected && originalStats.maxHealth < player->getMaxHealth())
                            {
                                player->setMaxHealth(player->getMaxHealth() - 1);
                                player->setStatPoints(player->getStatPoints() + 1);
                                player->setMaxHealthPoints(player->getMaxHealth());
                                std::cout << player->getStatPoints() << std::endl;
                            }

                            if (plusStrength->isSelected && player->getStatPoints() > 0)
                            {
                                player->setStrength(player->getStrength() + 1);
                                player->setStatPoints(player->getStatPoints() - 1);
                                player->setStrengthPoints(player->getStrength());
                                std::cout << player->getStatPoints() << std::endl;
                            }
                            if (minusStrength->isSelected && originalStats.strength < player->getStrength())
                            {
                                player->setStrength(player->getStrength() - 1);
                                player->setStatPoints(player->getStatPoints() + 1);
                                player->setStrengthPoints(player->getStrength());
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
                      

                       
                    }
                    if (quitButton->isSelected)
                    {
                        canGoToFloor = false;
                        actionsOnFloorTaken = 0;
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
                        enemy = GetEnemy(enemy);
                    }
                    if (previousFloorButton->isSelected)
                    {
                        currentFloor--;
                        actionsOnFloorTaken = 0;
                        previousFloorButton->isSelected = false;
                        enemy = GetEnemy(enemy);
                    }
                }
            }
        }
        SDL_RenderClear(renderer);
        if (gameVictory)
        {
            gameVictory = false;
            canGoToFloor = false;
            actionsOnFloorTaken = 0;
            return;
        }
        else if (!entered)
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

            if (player->getStatPoints() > 0) //only show when player has stat points to allocate
            {
                box->draw();
                done->draw();

                RenderText("DONE", 580, 547, fontSize - 1, font, textColour, 48);


                RenderText("ALLOCATE POINTS", 250, 100, fontSize - 1, font, textColour, 60);


                RenderText("REMAINING POINTS: " + std::to_string(player->getStatPoints()), 250, 300, fontSize / 2, font, textColour, 32);

                RenderText("HEALTH:   " + std::to_string(player->getMaxHealth()), 250, 350, fontSize / 2, font, textColour, 32);

                plusHealth->draw();
                minusHealth->draw();

                RenderText("STRENGTH: " + std::to_string(player->getStrength()), 250, 400, fontSize / 2, font, textColour, 32);

                plusStrength->draw();
                minusStrength->draw();

                RenderText("AGILITY:  " + std::to_string(player->getAgility()), 250, 450, fontSize / 2, font, textColour, 32);

                plusAgility->draw();
                minusAgility->draw();

                RenderText("LUCK:     " + std::to_string(player->getLuck()), 250, 500, fontSize / 2, font, textColour, 32);

                plusLuck->draw();
                minusLuck->draw();
            }
            else //show when player has no stat points to allocate
            {
                float t = 0.1f;
                float easedT = SmoothStep(t);
                displayPlayerHP = Lerp(displayPlayerHP, player->getHealthPoints(), easedT);

                enemy->draw();

                actionsBox->draw();

                fightButton->draw();
                RenderText("FIGHT", 245, 575, fontSize, font, textColour, 60);


                runButton->draw();
                RenderText("RUN", 580, 575, fontSize, font, textColour, 60);


                restButton->draw();
                RenderText("REST", 870, 575, fontSize, font, textColour, 60);

                showCurrentFloor->draw();
                RenderText("CURRENT FLOOR: " + std::to_string(currentFloor), 45, 120, fontSize/4, font, textColour, 16);

                if (currentFloor > 1)
                {
                    previousFloorButton->draw();
                    RenderText("PREVIOUS FLOOR", 230, 40, fontSize/4, font, textColour, 16);

                }
                if (canGoToFloor || currentFloor < highestFloor)
                {
                    nextFloorButton->draw();
                    RenderText("NEXT FLOOR", 435, 35, fontSize/3, font, textColour, 24);

                }


                RenderText("YOU: " + std::to_string((int)player->getHealthPoints()) + "/" + std::to_string((int)player->getMaxHealthPoints()), 110, 400, fontSize / 2, font, textColour, 32);
                RenderHealthBar(renderer, 110, 435, 300, 20, displayPlayerHP, player->getMaxHealthPoints());
            }
            quitButton->draw();
            RenderText("QUIT", 65, 32, fontSize/2, font, textColour, 32);


            if (fadeIn)
            {
                FadeTransition(true, 800);
                fadeIn = false;
            }
            }
        mouse->draw();
        SDL_Delay(16);
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

    bool fadeIn = true;

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
                    if (!allocatePoints) //sets the players stat points when they choose a class also stops checking if the button is pressed when they aren't being rendered
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
                            player->setMaxHealthPoints(player->getMaxHealth());
                            player->setHealthPoints(player->getMaxHealthPoints());
                            player->setStrengthPoints(player->getStrength());
                            FadeTransition(false, 800);
                            currentFloor = 1;
                            highestFloor = 1; //if player quits or dies they restart from floor 1
                            Game(player);
                            return;
                        }

                        if (plusHealth->isSelected && player->getStatPoints() > 0) 
                        {
                            player->setMaxHealth(player->getMaxHealth() + 1);
                            player->setStatPoints(player->getStatPoints() - 1);
                            std::cout << player->getStatPoints() << std::endl;
                        }
                        if (minusHealth->isSelected && originalStats.maxHealth < player->getMaxHealth()) //player can't decrease their stats below what they were when allocating new stat points
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
                        FadeTransition(false, 800);
                        running = false;
                    }
                  
                 
                }
            }
        }
        SDL_RenderClear(renderer);
        entranceImg->draw();
        box->draw();
        back->draw();

        RenderText("BACK", 970, 575, fontSize, font, textColour,60);
        if (!allocatePoints) //once the player has chosen a class do not render this
        {

            RenderText("CHOOSE A CLASS", 250, 100, fontSize, font, textColour,60);


            knight->draw();
            RenderText("KNIGHT", 400, 225, fontSize, font, textColour,60);

            archer->draw();
            RenderText("ARCHER", 400, 325, fontSize, font, textColour,60);

            fighter->draw();
            RenderText("FIGHTER", 385, 425, fontSize, font, textColour,60);

        }
        else //only render this once the player has chosen a class
        {
            done->draw();

            RenderText("DONE", 580, 547, fontSize-1, font, textColour,48);


            RenderText("ALLOCATE POINTS", 250, 100, fontSize-1, font, textColour,60);


            RenderText("REMAINING POINTS: " + std::to_string(player->getStatPoints()), 250, 300, fontSize/2, font, textColour,32);

            RenderText("HEALTH:   " + std::to_string(player->getMaxHealth()), 250, 350, fontSize/2, font, textColour,32);

            plusHealth->draw();
            minusHealth->draw();

            RenderText("STRENGTH: " + std::to_string(player->getStrength()), 250, 400, fontSize/2, font, textColour,32);

            plusStrength->draw();
            minusStrength->draw();

            RenderText("AGILITY:  " + std::to_string(player->getAgility()), 250, 450, fontSize/2, font, textColour,32);

            plusAgility->draw();
            minusAgility->draw();

            RenderText("LUCK:     " + std::to_string(player->getLuck()), 250, 500, fontSize/2, font, textColour,32);

            plusLuck->draw();
            minusLuck->draw();
        }
        
        mouse->draw();


        if (fadeIn)
        {
            FadeTransition(true, 800);
            fadeIn = false;
        }
        SDL_Delay(16);
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
    if (!TTF_Init())
    {
        std::cout << "Error opening TTF" << std::endl;
        return false;
    }
    TTF_Font* font = TTF_OpenFont("images/font.ttf", 60);
    SDL_Color textColour = { 255,255,255,255 };


    bool fadeIn = true;

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
                        FadeTransition(false, 800);
                        CreateCharacterScreen();
                        
                        fadeIn = true;
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

        RenderText("START", 170, 535, fontSize, font, textColour,60);
        RenderText("OPTIONS", 525, 535, fontSize, font, textColour,60);
        RenderText("QUIT", 970, 535, fontSize, font, textColour,60);

        mouse->draw();
        if (fadeIn)
        {
            FadeTransition(true, 800);
            fadeIn = false;
        }
        SDL_Delay(16); //limit the game to 60fps
    }
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}


