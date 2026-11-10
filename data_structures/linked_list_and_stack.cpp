#include <iostream>
#include <stdexcept>
#include <cassert>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* head;
    size_t list_size;

public:
    LinkedList() : head(nullptr), list_size(0) {}

    ~LinkedList() {
        clear();
    }

    void push_front(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        list_size++;
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        list_size++;
    }

    bool remove(const T& value) {
        if (!head) return false;

        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            list_size--;
            return true;
        }

        Node* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }

        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            list_size--;
            return true;
        }

        return false;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    bool empty() const {
        return head == nullptr;
    }

    size_t size() const {
        return list_size;
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        list_size = 0;
    }

    void print() const {
        Node* temp = head;
        while (temp) {
            std::cout << temp->data << (temp->next ? " -> " : "");
            temp = temp->next;
        }
        std::cout << "\n";
    }
};

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* topNode;
    size_t stack_size;

public:
    Stack() : topNode(nullptr), stack_size(0) {}

    ~Stack() {
        clear();
    }

    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        stack_size++;
    }

    void pop() {
        if (empty()) {
            throw std::underflow_error("Stack underflow");
        }
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        stack_size--;
    }

    const T& top() const {
        if (empty()) {
            throw std::underflow_error("Stack empty");
        }
        return topNode->data;
    }

    bool empty() const {
        return topNode == nullptr;
    }

    size_t size() const {
        return stack_size;
    }

    void clear() {
        while (topNode) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
        stack_size = 0;
    }
};

int main() {
    std::cout << "--- Testing Singly Linked List ---\n";
    LinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_front(5);

    std::cout << "Original List: ";
    list.print();
    assert(list.size() == 4);

    std::cout << "Reversing List...\n";
    list.reverse();
    std::cout << "Reversed List: ";
    list.print();

    std::cout << "Removing 20...\n";
    bool removed = list.remove(20);
    assert(removed);
    std::cout << "List after deletion: ";
    list.print();
    assert(list.size() == 3);

    std::cout << "\n--- Testing Stack (LIFO) ---\n";
    Stack<int> stack;
    stack.push(100);
    stack.push(200);
    stack.push(300);

    std::cout << "Stack top: " << stack.top() << "\n";
    assert(stack.top() == 300);
    assert(stack.size() == 3);

    std::cout << "Popping top element...\n";
    stack.pop();
    std::cout << "New stack top: " << stack.top() << "\n";
    assert(stack.top() == 200);

    std::cout << "All tests passed successfully!\n";
    return 0;
}
