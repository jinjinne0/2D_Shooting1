
#pragma once

//---------------------------------
//include
//---------------------------------
#include <vector>
#include <string>
#include <unordered_map>
#include "Actor.hpp"
#include "SpriteComponent.hpp"
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"

//---------------------------------
//Macro definition
//---------------------------------


//---------------------------------
//Type definition
//---------------------------------

class Game{
public:
    Game();

    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    //TODO: 入力処理と出力生成のためのコンポーネントのAddとRemove関数
    void AddSprite(SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);

    SDL_Texture* GetTexture(const std::string& filename);

private:
    //Helper functions for game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnLoadData();

    //WindowとRenderer
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    //Should we continue the game?
    bool mIsRunning;
    //Ticks count while game
    unsigned int mTicksCount;
    //Track if we`re updating actors right now
    bool mUpdatingActors;

    // Map of textures loaded
    std::unordered_map<std::string, SDL_Texture*> mTextures;

    //All the actors in the game
    std::vector<Actor*> mActors;
    //Any pending actors
    std::vector<Actor*> mPendingActors;

    //TODO: 入力処理のと出力生成のためのコンポーネントを入れておくコンテナ(vector)
    std::vector<SpriteComponent*> mSprites;

    //TODO: このゲーム特有でゲーム実行の間は常にあるメンバ変数、オブジェクト
    bool mIsPaused;
    unsigned int mPauseTicks;

};


//---------------------------------
//Prototype definition
//---------------------------------

