#ifndef COMMANDMOVE_H
#define COMMANDMOVE_H
#include <string>
#include "command.h"

class CommandMove:public Command
{
public:
    CommandMove():Command()
    {
        _speed=1.0F;
    }
    CommandMove(float speed, float time):Command(time)
    {
        if(speed >= -50.0F && speed <= 50.0F)
        {
            _speed = speed;
        }
        else
        {
            _speed = 0.0F;
        }
    }
    virtual ~CommandMove()override
    {
    }
    float getSpeed() const;
    void setSpeed(float speed);
    bool isEqual(Command const &)override;
    bool whichClass(){return true;}
    bool isUnequal(Command const &)override;
private:
    float _speed;
};

#endif // COMMANDMOVE_H
