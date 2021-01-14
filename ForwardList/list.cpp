#include "list.h"

ListNode::ListNode(int val)
    : value(val), next(nullptr) {}

ListNode::~ListNode() {
    next = nullptr;
}

List::List()
    : head_{nullptr}, size_(0ul) {}

List::~List() {
    while (size_ > 0ul) {
        RemoveFront();
    }
}

void List::PushFront(int value) {
    ListNode* temp = new ListNode(value);
    temp->next = head_;
    head_ = temp;
    size_++;
}

void List::RemoveFront() {
    if (head_) {
        ListNode* temp = head_->next;
        delete head_;
        head_ = temp;
        size_--;
    }
}

ListNode* List::head() {
    return head_;
}

const ListNode* List::head() const {
    return head_;
}

size_t List::size() const {
    return size_;
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
    for (auto cur = l.head(); cur != nullptr; cur = cur->next) {
        os << cur->value << (cur->next != nullptr ? " -> " : "\n");
    }
    return os;
}
