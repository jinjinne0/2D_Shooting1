
//---------------------------------
//include
//---------------------------------
#include "Game.hpp"
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
const int kWindowWidth = 1024;
const int kWindowHeight = 768;


//---------------------------------
//function definition
//---------------------------------

//TODO:　外部ライブラリなど、別枠のエラーが出る可能性がある初期化より前の簡単な初期化を書く。
Game::Game()
:mIsRunning(true)
,mUpdatingActors(false)
,mWindow(nullptr)
,mRenderer(nullptr)
//TODO: その他新しく書いたもの
{}

bool Game::Initialize(){
    //TODO:外部ライブラリなどの機能で初期化が必要なものの初期化
    //Initialize SDL
    int is_sdl_init = SDL_Init(SDL_INIT_VIDEO);
    if(is_sdl_init != 0){
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    
    //Create SDL window and renderer
    mWindow = SDL_CreateWindow(
        "2D_Shooting1",
        100,           //top left x-coordinate of the window
        100,           //top left y-coordinate of the window
        kWindowWidth,  //widht of window
        kWindowHeight,  //height of window
        0
    );
    if(!mWindow){
        SDL_Log("Failed to create SDL window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(
        mWindow,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if(!mRenderer){
        SDL_Log("Failed to create SDL renderer: %s", SDL_GetError());
        return false;
    }


    //TODO:　ゲームオブジェクトの初期化、データのロード
    LoadData();

    //Then, start counting ticks
    mTicksCount = 0;

    return true;

}

//TODO:　初期化したものの終了や、動的メモリの解放
void Game::Shutdown(){
    //TODO: ゲームオブジェクトを消す、メモリ開放
    UnLoadData();

    //TODO: Initialize()で初期化した外部ライブラリの機能などの終了
}

void Game::RunLoop(){
    if(mIsRunning){
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
    //TODO: 得点表示などゲーム終了後に必要な処理があれば
}

//TODO:　入力処理
void Game::ProcessInput(){
    //TODO: ゲーム自体への入力処理

    //TODO: ゲームオブジェクトへの入力処理

}

//TODO: ゲームワールドの更新
void Game::UpdateGame(){
    //TODO: デルタタイムの計算
    float deltatime ;
    //短すぎたり、長すぎたりにならないように調節する

    //TODO: mTicksCountの更新

    //Update all actors
    mUpdatingActors = true;
    for(auto actor : mActors){
        actor->Update(deltatime);
    }
    mUpdatingActors = false;

    //Move any pending actors to mActors
    for(auto pending : mPendingActors){
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();
    
    //Add any dead actors to a temp vector
    std::vector<Actor*> deadActors;
    for(auto actor : mActors){
        if(actor->GetState() == Actor::EDead){
            deadActors.emplace_back(actor);
        }
    }

    //Delete dead actors (which removes them from mActors)
    for(auto actor : deadActors){
        delete actor;
    }

}

//TODO: 出力の生成
void Game::GenerateOutput(){
    //TODO: 出力するデータの生成と、ハード機器に対する操作
}

//TODO:　ゲームオブジェクトの初期化、データのロード
void Game::LoadData(){}

//TODO: ゲームオブジェクトを消す、メモリ開放
void Game::UnLoadData(){

    //Delete actors
    //これにより、コンポーネントのメモリも開放される→そしてGameクラスのコンポーネントの配列もなくなる
    while(!mActors.empty()){
        delete mActors.back();
    }

    //TODO: Delete other memory and clear members
}

void Game::AddActor(Actor* actor){
	// If we're updating actors, need to add to pending
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}

}

//Actorのメモリ開放が起こると、mGame->RemoveActorとこれが呼び出せれて、
//mActorsの配列からも自然に削除されるようにActor()のディストラクタを実装してある
void Game::RemoveActor(Actor* actor){
    //Is it in pending actors?
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if(iter != mPendingActors.end()){
        //Swap to end of vector and pop off(avoid erase copies)
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }

    //Is it in actors?
    iter = std::find(mActors.begin(), mActors.end(), actor);
    if(iter != mActors.end()){
        //Swap to end of vector and pop off(avoid erase copies)
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }

}

//TODO: ヘッダファイルの方で追加したメンバ関数の定義