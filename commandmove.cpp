#include "commandmove.h"
#include <string>
float CommandMove::getSpeed() const
{
    return _speed;
}

void CommandMove::setSpeed(float speed)
{

    if(speed >= -50.0F && speed <= 50.0F)
    {
        _speed = speed;
    }
}
bool CommandMove::isEqual(Command const &existing)
{
    const CommandMove *p = static_cast<const CommandMove*>(&existing);
    return((this->getSpeed() == (p->_speed))&&(this->getTime() == (p->_time)));
}
bool CommandMove::isUnequal(Command const &existing)
{
    return !(this->isEqual(existing));
}


