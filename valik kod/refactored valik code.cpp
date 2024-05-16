#include <iostream>
#include <initializer_list>
#include <functional>
#include <memory>
#include <stdexcept>

template <typename T>
class Linked_List {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;

        Node(const T& data) : data(data), next(nullptr) {}
    };

    std::unique_ptr<Node> head;
    size_t size_;

public:
    Linked_List() : head(nullptr), size_(0) {}

    Linked_List(std::initializer_list<T> list) : Linked_List() {
        auto it = list.end();
        while (it != list.begin()) {
            --it;
            push_front(*it);
        }
    }

    Linked_List(Linked_List&& other) noexcept : head(std::move(other.head)), size_(other.size_) {
        other.size_ = 0;
    }

    Linked_List& operator=(Linked_List&& other) noexcept {
        if (this != &other) {
            head = std::move(other.head);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }

    ~Linked_List() = default;

    void push_front(const T& value) {
        auto new_Node = std::make_unique<Node>(value);
        new_Node->next = std::move(head);
        head = std::move(new_Node);
        ++size_;
    }

    void push_front(T&& value) {
        auto new_Node = std::make_unique<Node>(std::move(value));
        new_Node->next = std::move(head);
        head = std::move(new_Node);
        ++size_;
    }

    size_t size() const {
        return size_;
    }

    void clear() {
        while (head) {
            head = std::move(head->next);
        }
        size_ = 0;
    }

    Linked_List<T> split_when(std::function<bool(const T&)> condition) {
        Linked_List<T> result;
        if (!head)
            return result;

        size_t tail_size = 0;

        auto* current = head.get();
        if (condition(current->data)) {
            result = std::move(*this);
            clear();
            return result;
        }
        while (current->next && !condition(current->next->data)) {
            current = current->next.get();
            ++tail_size;
        }
        if (!current->next)
            return result;

        result.head = std::move(current->next);
        result.size_ = size_ - tail_size - 1;

        current->next = nullptr;
        size_ -= result.size_;

        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Linked_List& list) {
        auto* current = list.head.get();
        while (current) {
            os << current->data << " ";
            current = current->next.get();
        }
        return os;
    }
};

int main() {
    try {
        Linked_List<int> original = { 1, 25, 42, 3, 5, 9, 8, 13, 10, 9 };

        Linked_List<int> empty_list;
        if (empty_list.size() != 0) {
            throw std::runtime_error("Default constructor failed!");
        }

        std::cout << "Original list: " << original << std::endl;

        auto tail = original.split_when([](const int& value) { return value == 9; });

        std::cout << "Original list size after split: " << original.size() << std::endl;
        std::cout << "Tail list size: " << tail.size() << std::endl;

        std::cout << "Original list after split: " << original << std::endl;
        std::cout << "Tail list: " << tail << std::endl;

        original.clear();
        if (original.size() != 0) {
            throw std::runtime_error("Clear method failed!");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
