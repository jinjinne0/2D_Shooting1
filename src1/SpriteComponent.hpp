

#pragma once

//---------------------------------
//include
//---------------------------------
#include "Actor.hpp"
#include "Component.hpp"
#include "SDL/SDL.h"

//---------------------------------
//Macro definition
//---------------------------------


//---------------------------------
//Type definition
//---------------------------------
class SpriteComponent : public Component{
public:
    //(Lower draw order corresponds with further back)
    SpriteComponent(class Actor* owner, int draw_order = 100);
    ~SpriteComponent() override;

    virtual void Draw(SDL_Renderer* renderer);
    virtual void SetTexture(SDL_Texture* texture);

    //Geter
    SDL_Texture* GetTexture() const {return mTexture;}
    int GetDrawOrder() const {return mDrawOrder;}
    int GetTexWidth() const {return mTexWidth;}
    int GetTexHeight() const {return mTexHeight;}

private:
    SDL_Texture* mTexture;
    int mDrawOrder;
    int mTexWidth;
    int mTexHeight;
};

//---------------------------------
//Prototype definition
//---------------------------------

