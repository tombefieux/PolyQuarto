#ifndef AI_H
#define AI_H

#include "Player.h"


class AI : public Player
{
    public:
        AI();
        ~AI();
        AI(string, int);
        int getDepth() const;
        string getType() const;

    protected:

    private:
        int depth;
};

#endif // AI_H
