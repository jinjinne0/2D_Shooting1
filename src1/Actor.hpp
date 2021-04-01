

#pragma once

//---------------------------------
//include
//---------------------------------
#include <vector>
#include "Math.hpp"

//---------------------------------
//Macro definition
//---------------------------------


//---------------------------------
//Type definition
//---------------------------------
class Actor{
public:
    enum State{
        EActive,
        EPaused,
        EDead
    };

    Actor(class Game* game);
    virtual ~Actor();

    //Update function called from Game (not overridable)
    void Update(float deltatime);
    //Updates all the components attached to the actor (not overridable)
    void UpdateComponents(float deltatime);
    //Any actor-specific update code (overridable)
    virtual void UpdateActor(float deltatime);

    //Getters/setters
    //TODO: function to get the coordinate
    //TODO: function to set the coordinate
    float GetScale(){return mScale;}
    void SetScale(float scale){mScale = scale;}
    float GetRotation(){return mRotation;}
    void SetRotation(float rotation){mRotation = rotation;}

    State GetState() const {return mState;}
    void SetState(State state) {mState = state;}

    class Game* GetGame(){return mGame;}

    // Add/remove components
    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);

private:
    //Actor`s sttate
    State mState;

    //Transform
    //TODO: Coordinate of the center
    float mScale;    //1.0f for default
    float mRotation; //0.0f for default

    std::vector<class Component*> mComponents;
    class Game* mGame;

};

//---------------------------------
//Prototype definition
//---------------------------------

