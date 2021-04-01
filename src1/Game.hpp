
#pragma once

//---------------------------------
//include
//---------------------------------
#include <vector>
#include "Actor.hpp"
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

    //TODO:　画像データや音声データなどをファイル名から取得し、そのまま出力できる形にしたものを返す関数

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

    //TODO: 一度使った画像データや音声ファイルなどについて
    //そのファイル名をkeyに、使えるようにしたデータを中身にしたmapで管理

    //All the actors in the game
    std::vector<Actor*> mActors;
    //Any pending actors
    std::vector<Actor*> mPendingActors;

    //TODO: 入力処理のと出力生成のためのコンポーネントを入れておくコンテナ(vector)

    //TODO: このゲーム特有でゲーム実行の間は常にあるメンバ変数、オブジェクト

};


//---------------------------------
//Prototype definition
//---------------------------------

