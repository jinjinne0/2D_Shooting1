

#pragma once

//---------------------------------
//include
//---------------------------------
#include "Actor.hpp";

//---------------------------------
//Macro definition
//---------------------------------


//---------------------------------
//Type definition
//---------------------------------

class Component{
public:
    //Constructor
    //(the lower the update order, the earlier the component updates)
    Component(class Actor* owner, int update_order = 100);
    //Destructor
    virtual ~Component();
    //Update this component by delta time
    virtual void Update(float deltatime);

    //Getter
    int GetUpdateOrder() const {return mUpdateOrder;}
    Actor* GetOwner() const {return mOwner;}

private:
    //Owning actor
    class Actor* mOwner;
    //Update order of component
    int mUpdateOrder;

};

//---------------------------------
//Prototype definition
//---------------------------------

