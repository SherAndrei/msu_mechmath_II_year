#ifndef LIST_H
#define LIST_H
#include <iostream>

struct ListNode {
 public:
    explicit ListNode(int val);
    ~ListNode();

 private:
    ListNode(const ListNode& other) = delete;
    ListNode& operator=(const ListNode& other) = delete;

 public:
    int value;
    ListNode* next;
};

class List {
 public:
    List();
    ~List();

 private:
    List(const List& other) = delete;
    List& operator=(const List& other) = delete;

 public:
    void PushFront(int);
    void RemoveFront();

 public:
    ListNode* head();
    const ListNode* head() const;

    size_t size() const;

 private:
    ListNode* head_;
    size_t size_;
};

ListNode* DetectCycle(ListNode* head);
std::istream& operator>>(std::istream& is, List& l);
std::ostream& operator<<(std::ostream& is, const List& l);

#endif  // LIST_H
