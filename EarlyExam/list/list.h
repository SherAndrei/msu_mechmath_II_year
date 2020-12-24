#ifndef LIST_H
#define LIST_H
#include <iostream>

struct ListNode {
    explicit ListNode(int val);
    ~ListNode();

    int value;
    ListNode* next;
};

class List {
 public:
    List();
    ~List();

    void PushFront(int);
    bool RemoveFront();

    ListNode* head();
    ListNode* const head() const;
 private:
    ListNode* head_;
};

ListNode* DetectCycle(ListNode* head);
std::istream& operator>>(std::istream& is, List& l);
std::ostream& operator<<(std::ostream& is, const List& l);

#endif  // LIST_H
