#include <iostream>

import DequeBasedOnBidirectionalCyclicLinkedList;

int main()
{
    DequeNamespace::DequeBasedOnBidirectionalCyclicLinkedList<double> deque1;
    DequeNamespace::DequeBasedOnBidirectionalCyclicLinkedList<int> deque2(10);
    DequeNamespace::DequeBasedOnBidirectionalCyclicLinkedList<int> deque3(deque2);

    deque1.PushBack(1.2);
    deque1.PushBack(3.4);
    deque1.PushBack(5.6);
    deque1.PushBack(3.2);
    deque1.PushFront(1.3);

    std::cout << std::endl << "Elements of deque1: ";
    for (auto i = 0; i < deque1.GetSize(); i++)
        std::cout << deque1[i] << '\t';
    std::cout << std::endl;

    double temp;
    std::cout << std::endl << "Elements of deque1: ";
    for (auto i = 0; i < deque1.GetSize(); i++)
        std::cout << deque1[i] << '\t';
    std::cout << std::endl;

    temp = deque1.PeekBack();
    std::cout << std::endl << "PeekBacked element: " << temp << std::endl;
    temp = deque1.PeekFront();
    std::cout << std::endl << "PeekFronted element: " << temp << std::endl;
    temp = deque1.PopBack();
    std::cout << std::endl << "PopBacked element: " << temp << std::endl;
    temp = deque1.PopFront();
    std::cout << std::endl << "PopFronte element: " << temp << std::endl;
    std::cout << std::endl << "Elements of deque1: ";
    for (auto i = 0; i < deque1.GetSize(); i++)
        std::cout << deque1[i] << '\t';
    std::cout << std::endl;
    DequeNamespace::DequeBasedOnBidirectionalCyclicLinkedList<char> deque4 = { 'M', 'e', 'd', 'v', 'e', 'd', 'e', 'v'};
    std::cout << std::endl << "Elements of deque4: ";
    for (auto i = 0; i < deque4.GetSize(); i++)
        std::cout << deque4[i] << ' ';
    std::cout << std::endl;

    return 0;
}
