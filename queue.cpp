#include "commandmove.h"
#include "queue.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <float.h>
using namespace std;

Queue::Iterator::Iterator():
    node(nullptr)
{
}

Queue::Iterator::Iterator(Iterator& existing):
    node(existing.node)
{
}

Queue::Iterator::Iterator(CommandMoveNode* existing):
    node(existing)
{
}
Queue::Iterator:: ~Iterator()
{
}

Command* Queue::Iterator::operator*()
{
    return node->object;
}

Queue::Iterator& Queue::Iterator::operator++()
{
    node = node->next;
    return *this;
}
Queue::Iterator& Queue::Iterator::operator++(int)
{
    node = node->next;
    return *this;
}

bool Queue::Iterator::operator == (Iterator const &right) const
{
    return this->node == right.node;
}

bool Queue::Iterator::operator != (Iterator const &right)
{
    return !(this->node == right.node);
}

Queue::Queue():                         //пустая очередь
    head(nullptr),
    tail(nullptr),
    _length(0),
    size(5)
{

}

/*Queue::Queue(const Queue &existing):    //копируем очередь
    head(nullptr),
    tail(nullptr),
    size(existing.size)
{
    CommandMoveNode *newNode, *existingNode = existing.head;
    CommandMove *tempCommandMove;
    _length = 0;
    if(existing._length)
    {
        tempCommandMove = new CommandMove(*(existingNode->object));
        newNode = new CommandMoveNode;
        newNode->object = tempCommandMove;
        existingNode = existingNode->next;
        _length++;
        head = newNode;
        tail = head;
        tail->next = nullptr;
        while(existingNode)
        {
            tempCommandMove = new CommandMove(*(existingNode->object));
            tail = new CommandMoveNode;
            newNode->next = tail;
            tail->next = nullptr;
            tail->object = tempCommandMove;
            existingNode = existingNode->next;
            newNode = tail;
            _length++;
        }
    }

}*/

Queue::~Queue()
{
    while(head)
    {
        tail = head->next;
        delete head;
        head = tail;
    }

}


void Queue::addNode(CommandMove& existing)
{
    CommandMoveNode* curr = new CommandMoveNode;
    curr->object = new CommandMove(existing);
    curr->next=nullptr;
    if (_length==0)
    {
        head = curr;
        tail=head;
    }
    else
    {
        tail->next=curr;
        tail=curr;
    }
    _length++;
}
void Queue::addNode(CommandTurn& existing)
{
    CommandMoveNode* curr = new CommandMoveNode;
    curr->object = new CommandTurn(existing);
    curr->next=nullptr;
    if (_length==0)
    {
        head = curr;
        tail=head;
    }
    else
    {
        tail->next=curr;
        tail=curr;
    }
    _length++;
}
Command* Queue::deleteNode()
{
    Command* curr;
    curr=(head->object);
    head=head->next;
    _length--;
    if(_length==0)
    {
        tail=nullptr;
    }
    return curr;
}


void Queue::deleteQueue()
{
    while(head)
    {
        tail = head->next;
        delete head;
        head = tail;
    }
    head = tail = nullptr;
    _length = 0;
}

int Queue::getLength()
{
    return _length;
}

Queue::Iterator Queue::begin()
{
    Iterator temp(head);
    return temp;
}

Queue::Iterator Queue::end() const
{
    Iterator temp(tail);
    return temp;
}

CommandMoveNode* Queue::getHead() const
{
    return head;
}

CommandMoveNode* Queue::getTail() const
{
    return tail;
}
bool Queue::isEqual(Queue &existingList)
{
    Queue::Iterator firstIterator, secondIterator;
    if( this->getLength() != existingList.getLength())
    {
        return false;
    }
    bool answer = true;
    for(firstIterator = this->begin(), secondIterator = existingList.begin();
        firstIterator != nullptr; firstIterator++, secondIterator++)
    {
        if ((*firstIterator)->whichClass()==(*secondIterator)->whichClass())
        {
            if((*firstIterator)->isUnequal(*(*secondIterator)))
            {
                answer = false;
            }
        }
        else
        {
            answer = false;
        }
    }
    return answer;
}
/*void Queue::cordinatCalc(float Time)
{ float pos,currTime,prevTime ;
    Queue::Iterator iterator;
    iterator=this->begin();
    pos=0;prevTime=0;
    currTime=(*iterator)->getTime();
    while (currTime<=Time)
    {
        pos=pos+((*iterator)->getSpeed())*((*iterator)->getTime());
        prevTime=currTime;
        if ((this->end())!=((iterator++)))
        {
            currTime=currTime+((*iterator)->getTime());
        }
        else

            currTime=Time+1.0F;
    }
    if((prevTime-Time)==0.0F)
    {
        cout<<pos<<endl;
    }
    else
    {
        pos=pos+((*iterator)->getSpeed())*((Time-prevTime));
        cout<<pos<<endl;
    }
}*/
void Queue::writeInFile(std::string fileName)
{
    Queue::Iterator iterator;
    float speed,time,rad;
    int len;
    string type;
    ofstream file(fileName, std::ios::out | std::ios::binary);
    len=this->getLength();
    file.write(reinterpret_cast<char*>(&len),sizeof(len));
    for(iterator=this->begin(); iterator!=nullptr; iterator++)
    {
        if ((*iterator)->whichClass()==true)
        {
            const CommandMove *p = static_cast<const CommandMove*>(*iterator);
            type="Cm";
            speed=p->getSpeed();
            time=p->getTime();
            size_t sizeType=type.size()+1;
            file.write(reinterpret_cast<char*>(&sizeType),sizeof(sizeType));
            file.write(type.c_str(),sizeType);
            file.write(reinterpret_cast <char*> (&speed), sizeof(speed));
            file.write(reinterpret_cast<char*>(&time),sizeof(time));
        }
        else
        {
            const CommandTurn *p = static_cast<const CommandTurn*>(*iterator);
            type="Ct";
            rad=p->getRadius();
            time=p->getTime();
            size_t sizeType=type.size()+1;
            file.write(reinterpret_cast<char*>(&sizeType),sizeof(sizeType));
            file.write(type.c_str(),sizeType);
            file.write(reinterpret_cast <char*> (&rad), sizeof(rad));
            file.write(reinterpret_cast<char*>(&time),sizeof(time));
        }
    }
    file.close();
}

void Queue::readFromFile(std::string fileName)
{
    float speed,time,rad;
    int len,s;
    string type;
    size_t size0;
    ifstream file(fileName,std::ios::out | std::ios::binary);
    s=0;
    file.read(reinterpret_cast<char*>(&len),sizeof(len));
    while (s!=len)
    {
        file.read(reinterpret_cast<char*>(&size0),sizeof(size0));
        char buff_0[size0];
        file.read(reinterpret_cast<char*>(&buff_0), size0);
        type=string(buff_0);
        if (type=="Cm")
        {
            file.read(reinterpret_cast<char*>(&speed), sizeof(speed));
            file.read(reinterpret_cast<char*>(&time),sizeof(time));
            CommandMove NewCommandMove(speed,time);
            this->addNode(NewCommandMove);
            s++;
        }
        else
        {
            file.read(reinterpret_cast<char*>(&rad), sizeof(rad));
            file.read(reinterpret_cast<char*>(&time),sizeof(time));
            CommandTurn NewCommandTurn(rad,time);
            this->addNode(NewCommandTurn);
            s++;
        }
    }
    file.close();
}


