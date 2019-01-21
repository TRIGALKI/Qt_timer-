#include "commandturn.h"

CommandTurn::~CommandTurn()
{

}
float CommandTurn::getRadius() const
{
    return _radius;
}

void CommandTurn::setRadius(float radius)
{

    if(radius >= 0.0F)
    {
        _radius = radius;
    }
}
bool CommandTurn::isEqual(Command const &existing)
{
    const CommandTurn *p = static_cast<const CommandTurn*>(&existing);
    return((this->getRadius() == (p->_radius))&&(this->getTime() == (p->_time)));
}
bool CommandTurn::isUnequal(Command const &existing)
{
    return !(this->isEqual(existing));
}

