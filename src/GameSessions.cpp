#include "GameSession.h"

GameSession* GameSession::instance = nullptr;

GameSession& GameSession::getInstance() {

    if(instance == nullptr)
        instance = new GameSession();

    return *instance;

}