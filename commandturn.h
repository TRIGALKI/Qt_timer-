#ifndef COMMANDTURN_H
#define COMMANDTURN_H
#include "command.h"
class CommandTurn:public Command
{
public:
    CommandTurn():Command()
    {
        _radius=90.0F;
    }
    CommandTurn(float radius, float time):Command(time)
    {
        if (radius >=0)
            _radius=radius;
        else
            _radius=90.0F;

    }
    virtual ~CommandTurn()override;
    float getRadius() const;
    void setRadius(float radius);
    bool isEqual(Command const &)override;
    bool isUnequal(Command const &)override;
    bool whichClass(){return false;}
private:
    float _radius;
};
#endif // COMMANDTURN_H
