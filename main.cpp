#include <iostream>

#include "input-manager/Callback.h"
#include "input-manager/Event.h"

void Hello()
{
    std::cout << "Hello!" << std::endl;
}

void Hello2()
{
    std::cout << "Hello!" << std::endl;
}

class A
{
public:
    void HelloFromA()
    {
        std::cout << "A";
    }
    void HelloFromA2()
    {
        std::cout << "A";
    }
};

class B
{
public:
    void HelloFromB()
    {
        std::cout << "b";
    }
};

int main()
{
    tlr::Event event;
    A a;
    
    A a1;
    
    
    event.UnregisterCallback(&a, &A::HelloFromA2);

    event.Raise();    


    
    return 0;
}