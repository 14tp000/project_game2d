//
// Created by Jeremi on 28.05.2024.
//

#ifndef PROJECT_GAME2D_ATTACKMOVE_H
#define PROJECT_GAME2D_ATTACKMOVE_H
#include "renderManager.h"


class attackMove {
    attackMove* next;
public:
    float duration;
    float counter = 0;
    bool finished = false;
    renderManager *rM;

    virtual void attackPlayer() =0;

    attackMove(attackMove *nxt, float dur, renderManager *renderM) {
        next = nxt;
        duration = dur;
        rM = renderM;
    }

    attackMove *getNext() { return next; }

    void setNext(attackMove *atk) { next = atk; }

    void Reset() {
        counter = 0;
        finished = false;
    }

    virtual void Render() =0;
};


#endif //PROJECT_GAME2D_ATTACKMOVE_H
