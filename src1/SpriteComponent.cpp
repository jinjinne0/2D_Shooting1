

//---------------------------------
//include
//---------------------------------
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
    this->GetOwner()->GetGame();
}

