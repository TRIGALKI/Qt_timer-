#include "command.h"
Command::Command()
{
    _time=1.0F;
}
Command::~Command()
{

}
Command::Command(float time):
 _time(time >= 0 ? time : 0.0F)
{
}
void Command::setTime(float time)
{
    if( time >= 0)
    {
        _time = time;
    }
}
float Command::getTime() const
{
    return _time;
}

