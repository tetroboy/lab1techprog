#include <iostream>
#include <initializer_list>
#include <functional>
#include <memory>
#include <stdexcept>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node(const T& data) : data(data), next(nullptr) {}
    };

    std::unique_ptr<Node> head;
    size_t size_;

public:
    LinkedList() : head(nullptr), size_(0) {}

    LinkedList(std::initializer_list<T> list) : LinkedList() {
        for (auto it = list.end(); it != list.begin(); ) {
            --it;
            push_front(*it);
        }
    }

    LinkedList(LinkedList&& other) noexcept : head(std::move(other.head)), size_(other.size_) {
        other.size_ = 0;
    }

    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            head = std::move(other.head);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }

    ~LinkedList() = default;

    void push_front(const T& value) {
        auto new_node = std::make_unique<Node>(value);
        new_node->next = std::move(head);
        head = std::move(new_node);
        ++size_;
    }

    void push_front(T&& value) {
        auto new_node = std::make_unique<Node>(std::move(value));
        new_node->next = std::move(head);
        head = std::move(new_node);
        ++size_;
    }

    size_t get_size() const {
        return size_;
    }

    void clear_list() {
        while (head) {
            head = std::move(head->next);
        }
        size_ = 0;
    }

    LinkedList<T> split_when(std::function<bool(const T&)> condition) {
        LinkedList<T> result;
        if (!head) return result;

        size_t tail_size = 0;

        auto* current = head.get();
        if (condition(current->data)) {
            result = std::move(*this);
            clear_list();
            return result;
        }

        while (current->next && !condition(current->next->data)) {
            current = current->next.get();
            ++tail_size;
        }

        if (!current->next) return result;

        result.head = std::move(current->next);
        result.size_ = size_ - tail_size - 1;

        current->next = nullptr;
        size_ -= result.size_;

        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list) {
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
        LinkedList<int> original = {1, 25, 42, 3, 5, 9, 8, 13, 10, 9};

        LinkedList<int> empty_list;
        if (empty_list.get_size() != 0) {
            throw std::runtime_error("Default constructor failed!");
        }

        std::cout << "Original list: " << original << std::endl;

        auto tail = original.split_when([](const int& value) { return value == 9; });

        std::cout << "Original list size after split: " << original.get_size() << std::endl;
        std::cout << "Tail list size: " << tail.get_size() << std::endl;

        std::cout << "Original list after split: " << original << std::endl;
        std::cout << "Tail list: " << tail << std::endl;

        original.clear_list();
        if (original.get_size() != 0) {
            throw std::runtime_error("Clear method failed!");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}