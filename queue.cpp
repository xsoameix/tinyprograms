// deque::max_size
#include <iostream>
#include <deque>

int
main() {
    unsigned int i;
    std::deque<int> mydeque;

    std::cout << "Enter number of elements: ";
    std::cin >> i;
    std::cout << "The max queue size: " << mydeque.max_size() << std::endl;

    return 0;
}
