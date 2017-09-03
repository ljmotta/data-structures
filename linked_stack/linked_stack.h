// Copyright [2017] <Luiz Motta>

#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <stdexcept>
#include <cstdint>

namespace structures {

template<typename T>

/*!
 *
 * TODO: DOCUMENTATION!
 *
 *
 */
class LinkedStack {
 public:
    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    ~LinkedStack();

    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    void clear();

    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    void push(const T& data);

    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    T pop();

    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    T& top() const;

    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    bool empty() const;

    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    std::size_t size() const;

 private:
    class Node {
     public:
        explicit Node(const T& data): data_{data} {}

        Node(const T& data, Node* next): data_{data}, next_{next} {}

        T& data() { return data_; }

        const T& data() const { return data_; }

        Node* next() { return next_; }

        const Node* next() const { return next_; }

        void next(Node* node) { next_ = node; }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() { return top_; }

    Node* top_{nullptr};
    std::size_t size_{0u};
};

    template<typename T>
    LinkedStack<T>::~LinkedStack() { clear(); }

    template<typename T>
    void LinkedStack<T>::clear() {
        while (!empty()) {
            pop();
        }
    }

    template<typename T>
    void LinkedStack<T>::push(const T &data) {
        if (empty) {
            top_->next(new Node(data, nullptr));
        } else {
            top_->next(new Node(data, top_->next()));
        }
        ++size_;
    }

    template<typename T>
    T LinkedStack<T>::pop() {
        if (empty()) {
            std::out_of_range("EMPTY");
        }
        auto to_delete = end();
        top_->next(to_delete->next());
        --size_;
        delete to_delete;
        return top_->next()->data();
    }

    template<typename T>
    T& LinkedStack<T>::top() const {
        return top_->next()->data();
    }

    template<typename T>
    bool LinkedStack<T>::empty() const { return size() == 0u; }

    template<typename T>
    std::size_t LinkedStack<T>::size() const { return size_; }

}  // namespace structures

#endif
