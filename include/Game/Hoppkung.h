#ifndef HOPPKUNG_H
#define HOPPKUNG_H

#include "Game/Amongus.h"
#include <vector>
#include "jEngine//GameEngine.h"

namespace jengine {
    class HoppKung : public Amongus {
    public:

        static HoppKung* getInstance(int x, int y, int w, int h, std::vector<std::vector<Sprite *>>& lvls, GameEngine& session) {
            return new HoppKung(x, y, w, h, lvls, session);
        }

        void spaceDown()override;

        void spaceUp() override;

        void leftDown() override;

        void rightDown() override;

        void leftUp() override;

        void rightUp() override;


        void tick() override;

        int getCurrentLevel() const {
            return currentLevel;
        }

    protected:
        HoppKung(int x, int y, int w, int h, std::vector<std::vector<Sprite *>>& lvls, GameEngine& session);

    private:

        std::vector<std::vector<Sprite *>>& levels;
        GameEngine& ses;

        static const int MAX_PLAYER_HORIZONTAL_CHARGE_VELOCITY = 10;
        static const int INITIAL_HORIZONTAL_CHARGE_VELOCITY = 2;
        static const int INITIAL_VERTICAL_CHARGE_VELOCITY = 10;
        static const int INITIAL_JUMP_MOVEMENT = 15;
        static const int MAX_PLAYER_VERTICAL_CHARGE_VELOCITY = 25;
        constexpr static const double PLAYER_HORIZONTAL_CHARGE_GROWTH = 0.5;
        constexpr static const double PLAYER_VERTICAL_CHARGE_GROWTH = 0.5;
        static const int HORIZONTAL_MOVEMENT = 20;

        int currentLevel = 0;
        bool chargingJump;
        double horizontalCounter;
        double verticalCounter;

    };
}


#endif
