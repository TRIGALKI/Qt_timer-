#ifndef COMMAND_H
#define COMMAND_H

class Command
{
public:
    Command();
    Command(float time);
    virtual ~Command();
    virtual bool isEqual(Command const &)=0;
    virtual bool isUnequal(Command const &)=0;
    void setTime(float time);
    float getTime() const;
    virtual bool whichClass()=0;
protected:
    float _time;
};
#endif // COMMAND_H
