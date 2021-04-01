

//---------------------------------
//include
//---------------------------------
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

Component::Component(Actor* owner, int update_order)
:mOwner(owner)
,mUpdateOrder(update_order)
{
    mOwner->AddComponent(this);
}

Component::~Component(){
    mOwner->RemoveComponent(this);
}

void Component::Update(float deltatime){}
