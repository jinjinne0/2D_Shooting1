

//---------------------------------
//include
//---------------------------------
#include "AnimSpriteComponent.hpp"
#include "Math.hpp"

//---------------------------------
//Macro definition(not revealed)
//---------------------------------

//---------------------------------
//Type definition(not revealed)
//---------------------------------

//---------------------------------
//global variable definition
//---------------------------------
const float kAnimFps = 24.0f;


//---------------------------------
//function definition
//---------------------------------

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int draw_order)
:SpriteComponent(owner, draw_order)
,mCurrFrame(0.0f)
,mAnimFPS(kAnimFps)
{
}

void AnimSpriteComponent::Update(float deltatime){

    SpriteComponent::Update(deltatime);

    if(mAnimTextures.size() > 0){
        //Update the current frame
        mCurrFrame += deltatime * mAnimFPS;

        //Wrap current frame if needed
        while(mCurrFrame >= mAnimTextures.size()){
            mCurrFrame -= mAnimTextures.size();
        }

        //Set the current texture
        SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);

    }
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& tex){
    mAnimTextures = tex;
    if(mAnimTextures.size() > 0){
        //Set the active textures to first frame
        mCurrFrame = 0.0f;
        SetTexture(mAnimTextures[0]);
    }
}