
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
,mIsPaused(true)
,mPauseTicks(0)
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
    
    //Create SDL window, renderer, and image
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
    if(IMG_Init(IMG_INIT_PNG) == 0){
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }


    //TODO:　ゲームオブジェクトの初期化、データのロード
    LoadData();

    //Then, start counting ticks
    mTicksCount = SDL_GetTicks();

    return true;

}

//TODO:　初期化したものの終了や、動的メモリの解放
void Game::Shutdown(){
    //TODO: ゲームオブジェクトを消す、メモリ開放
    UnLoadData();

    IMG_Quit();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_QUIT();
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
    //get keyboard state
    Uint32 state* = SDL_GetKeyboardState(NULL);

    //Input for controlling game
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        swith (event){
            case SDL_QUIT:
                mIsRunning = false;
                brerak;
        }
    }

    if(state[SDL_SCANCODE_ESCAPE]){
        mIsRunning = false;
    }
    if(state[SDL_SCANCODE_A]){  //A-key for start/restart game
        mIsPaused = false;
    }
    if(state[SDL_SCANCODE_S]){  //S-key for pause game
        mIsPaused = true;
    }

    //TODO: ゲームオブジェクトへの入力処理

}

//TODO: ゲームワールドの更新
void Game::UpdateGame(){
    //compute delta time
    //Wait until 16 mili seconds hjas passed since last time
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    float deltatime = (SDL_GetTicks() - mTicksCount)/1000.0f;// mili second to second
    if(deltatime > 0.5f){
        deltatime = 0.5f;
    }

    //Update ticks count for next delta time
    mTicksCount = SDL_GetTicks();

    if(mIsPaused){
        mPauseTicks += deltatime * 1000.0f;
        return;
    }

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

SDL_Texture* GetTextures(const std::string& filename){
    SDL_Texture* tex = nullptr;
    //Is the texture already in the map?
    auto iter = mTextures.find(filename);
    if(iter != mTextures.end()){
        tex = iter->second
    }
    else{
        //Load from file
        SDL_Surface* surf = IMG_LOAD(filename.c_str());
        if(!surf){
            SDL_Log("Failed to load texture file %s", filename.c_str());
            return nullptr;
        }

        //Create texture from surface
        tex = SDL_CreateTextureFromSurface(mRenderer, surf);
        SDL_FreeSurface(surface);
        if(!tex){
            SDL_Log("Failed to convert surface to texture for %s", filename.c_str());
        }

        mTextures.emplace(filename, tex);
    }

    return tex;
}