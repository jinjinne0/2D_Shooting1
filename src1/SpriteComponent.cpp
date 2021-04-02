

//---------------------------------
//include
//---------------------------------
#include "Game.hpp"
#include "SpriteComponent.hpp"
#include "Component.hpp"
#include "Actor.hpp"

//---------------------------------
//Macro definition(not revealed)
//---------------------------------

//---------------------------------
//Type definition(not revealed)
//---------------------------------

//---------------------------------
//global variable definition
//---------------------------------


//---------------------------------
//function definition
//---------------------------------

SpriteComponent::SpriteComponent(class Actor* owner, int draw_order)
:Component(owner)
,mTexture(nullptr)
,mDrawOrder(draw_order)
,mTexWidth(0)
,mTexHeight(0)
{
    GetOwner()->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent(){
    GetOwner()->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer){
    if(mTexture){
        SDL_Rect r;
        //Scale the width/height by owner`s scale
        r.w = static_cast<int>(mTexWidth * GetOwner()->GetScale());
        r.h = static_cast<int>(mTexHeight * GetOwner()->GetScale());
        //Center the rectangle around the position of the owner
        r.x = static_cast<int>(GetOwner()->GetPosition().x - r.w/2);
        r.y = static_cast<int>(GetOwner()->GetPosition().y - r.y/2);

        //Draw (have to convert angle from radians to degrees, and clockwise to counter)
        SDL_RenderCopyEx(renderer,
        mTexture,
        nullptr,
        &r,
        -Math::ToDegrees(GetOwner()->GetRotation()),
        nullptr,
        SDL_FLIP_NONE);
    }
}

void SpriteComponent::SetTexture(SDL_Texture* tex){
    mTexture = tex;
    //set width/height
    SDL_QueryTexture(tex, nullptr, nullptr, &mTexWidth, &mTexHeight);
}