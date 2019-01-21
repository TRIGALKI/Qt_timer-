#ifndef QUEUE_H
#define QUEUE_H
#include"command.h"
#include "commandmove.h"
#include "commandturn.h"
#include <cassert>
using namespace std;
struct CommandMoveNode{
    Command *object;
    CommandMoveNode *next;
};
class Queue
{
private:
   // CommandMove *queuePtr;
    const int size;                 // максимальное количество элементов в очереди
     CommandMoveNode *head,        // начало очереди
        *tail;                     // конец очереди
    int _length;                  // счетчик элементов
public:
    class Iterator
    {
    public:
        friend Queue;
        Iterator();
        Iterator(Iterator&);
        Iterator(CommandMoveNode*);
        ~Iterator();
        Iterator& operator ++();
        Iterator& operator++(int);
        bool operator == (Iterator const &) const;
        bool operator != (Iterator const &);
        Command* operator *();
    private:
        CommandMoveNode *node;
    };
    friend Iterator;
    Queue();                                         // конструктор по умолчанию
    ~Queue();                                       // деструктор
    void addNode(CommandMove& existing);
    void addNode(CommandTurn& existing);// добавить элемент в очередь
    Command* deleteNode();
    CommandMoveNode* getHead() const;
    CommandMoveNode* getTail() const;
    void deleteQueue();
    Iterator begin();
    Iterator end() const;
    int getLength();
    bool isEqual(Queue &existingList);
    void writeInFile(std::string fileName);
    void readFromFile(std::string fileName);
    void cordinatCalc(float Time);

};

#endif // QUEUE_H
