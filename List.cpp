#include <iostream>
#include "LinkedList.h"


LinkedList<int> f()
{
    LinkedList<int> list{ 100, 200, 300 };
    return list;
}

int main()
{
    LinkedList<int> list{ 1, 2, 3, 4, 5 };
    std::cout << "size list = " << list.getSize() << "\n";
    list.print();
    LinkedList<int> list1;
    list1 = list;
    list1.addTail(30).addHead(40).addHead(50);
    std::cout << "size list1 = " << list1.getSize() << "\n";
    list1.print();

    LinkedList<int> list2(list1);
    list2.deleteHead();
    list2.deleteTail();
    std::cout << "size list2 = " << list2.getSize() << "\n";
    list2.print();

    LinkedList<int> list3(f());
    std::cout << "size list3 = " << list3.getSize() << "\n";
    list3.print();
    for (size_t i = 0; i < list3.getSize(); ++i)
    {
        list3[i] = list3[i] / 2;
    }
    list3.print();
    std::cout << "\n";
    LinkedList<int> list4 = list2;
    bool b1 = (list1 == list2);
    bool b2 = (list2 == list4);
    bool b3 = (list3 == list4);
    std::cout << b1 << " " << b2 << " " << b3;


    //std::cout << "list: \n";
    //list.print();
    //
    //list.insert(25, 2);
    //list.print();
    //std::cout << "\n";
    



    return 0;
}
