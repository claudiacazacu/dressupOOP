#pragma once
#include <string>

class GameSession
{
    std::string evenimentCurent_;
    std::string sezonPreferat_;

    GameSession();

public:
    GameSession(const GameSession &) = delete;
    GameSession &operator=(const GameSession &) = delete;

    static GameSession &Instance();

    void SetEvenimentCurent(const std::string &eveniment);
    void SetSezonPreferat(const std::string &sezon);

    const std::string &GetEvenimentCurent() const noexcept;
    const std::string &GetSezonPreferat() const noexcept;
};