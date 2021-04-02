

#pragma once

//---------------------------------
//include
//---------------------------------
#include <vector>
#include "Actor.hpp"
#include "SpriteComponent.hpp"
#include "SDL/SDL.h"

//---------------------------------
//Macro definition
//---------------------------------

//---------------------------------
//Type definition
//---------------------------------

class AnimSpriteComponent : public SpriteComponent{
public:
    AnimSpriteComponent(class Actor* owner, int draw_oreder = 100);
    //Update animation every frame (override from component)
    void Update(float deltatime) override;
    //Set the textures used for animation
    void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
    //Set/get the animation in FPS
    float GetAnimFPS() const {return mAnimFPS;}
    void SetAnimFPS(float fps){mAnimFPS = fps;}

private:
    //All textures in the animation
    std::vector<SDL_Texture*> mAnimTextures;
    //Current frame displayed
    float mCurrFrame;
    //Animation Frame rate
    float mAnimFPS;

};

//---------------------------------
//Prototype definition
//---------------------------------

