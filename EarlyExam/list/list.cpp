#include "list.h"

ListNode::ListNode(int val)
    : value(val), next(nullptr) {}

ListNode::~ListNode() {
    next = nullptr;
}

List::List()
    : head_{nullptr} {}

List::~List() {
    while (RemoveFront()) {}
}

void List::PushFront(int value) {
    ListNode* new_n = new ListNode(value);
    new_n->next = head_;
    head_ = new_n;
}

bool List::RemoveFront() {
    if (head_ == nullptr)
        return false;
    ListNode* pos = head_;
    head_ = head_->next;
    delete pos;
    return true;
}

ListNode* List::head() {
    return head_;
}

ListNode* const List::head() const {
    return head_;
}

ListNode* DetectCycle(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (slow != nullptr &&
           fast != nullptr &&
           fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return slow;
        }
    }
    return nullptr;
}

std::istream& operator>>(std::istream& is, List& l) {
    int value;
    while (is >> value) {
        l.PushFront(value);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const List& l) {
    for (ListNode* cur = l.head(); cur != nullptr; cur = cur->next) {
        os << cur->value << (cur->next != nullptr ? " -> " : "\n");
    }
    return os;
}
