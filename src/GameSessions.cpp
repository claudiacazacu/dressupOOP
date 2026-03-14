#include "GameSession.h"

GameSession::GameSession()
    : evenimentCurent_("Gala"), sezonPreferat_("Vara")
{
}

GameSession &GameSession::Instance()
{
    static GameSession instance;
    return instance;
}

void GameSession::SetEvenimentCurent(const std::string &eveniment)
{
    evenimentCurent_ = eveniment;
}

void GameSession::SetSezonPreferat(const std::string &sezon)
{
    sezonPreferat_ = sezon;
}

const std::string &GameSession::GetEvenimentCurent() const noexcept
{
    return evenimentCurent_;
}

const std::string &GameSession::GetSezonPreferat() const noexcept
{
    return sezonPreferat_;
}