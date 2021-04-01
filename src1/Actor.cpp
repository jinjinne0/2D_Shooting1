

//---------------------------------
//include
//---------------------------------
#include "Actor.hpp"
#include "Game.hpp"
#include "Component.hpp"
#include <algorithm>

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

Actor::Actor(Game* game)
:mState(EActive)
//TODO: initialize coordinate
,mScale(1.0f)
,mRotation(0.0f)
,mGame(game)
//TODO: Initialize additional menbers
{
    mGame->AddActor(this);
}

Actor::~Actor(){
    mGame->RemoveActor(this);
    //Need to delete components
    //Because ~Component calls RemoveComponent, need a different style loop
    while(!mComponents.empty()){
        delete mComponents.back();
    }
}

void Actor::Update(float deltatime){
    if(mState == EActive){
        UpdateComponents(deltatime);
        UpdateActor(deltatime);
    }
}

void Actor::UpdateComponents(float deltatime){
    for(auto comp : mComponents){
        comp->Update(deltatime);
    }
}

void Actor::UpdateActor(float deltatime){}

void Actor::AddComponent(Component* component){
    //Find the insertion point int the sorted vector
    //(The first element with a order higher than me)
    int my_order = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for(;
        iter != mComponents.end();
        ++iter){
            if(my_order < (*iter)->GetUpdateOrder()){
                break;
            }
    }

    //Inserts element before position of iterator
    mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component){
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if(iter != mComponents.end()){
        mComponents.erase(iter);
    }
}

//TODO: 追加したメンバ関数の定義