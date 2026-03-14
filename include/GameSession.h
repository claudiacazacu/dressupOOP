#pragma once

class GameSession {

private:

    static GameSession* instance;

    GameSession() {}

public:

    static GameSession& getInstance() {

        if(!instance)
            instance = new GameSession();

        return *instance;

    }

};