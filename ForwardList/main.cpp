#include <sstream>
#include "list.h"

int main() {
    List l;
    std::istringstream is("1 2 3");
    is >> l;
    std::cout << l;
    l.head()->next->next->next = l.head();
    ListNode* pos = DetectCycle(l.head());
    if (pos) {
        std::cout << pos->value << '\n';
    } else {
        std::cout << "No cycles!\n";
    }
}
