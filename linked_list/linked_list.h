// Copyright [2017] <Luiz Motta>

#ifndef STRUCTURES_LINKED_LINKED_H
#define STRUCTURES_LINKED_LINKED_H

#include <stdexcept>
#include <cstdint>

namespace structures {
/*!
 *
 * TODO: DOCUMENTATION!
 *
 *
 */
template<typename T>
class LinkedList {
 public:
    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    ~LinkedList();

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
    void push_back(const T& data);

    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    void push_front(const T& data);

    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    void insert(const T& data, std::size_t index);

    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    void insert_sorted(const T& data);

    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    T& at(std::size_t index);

    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    T pop(std::size_t index);

    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    T pop_back();

    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    T pop_front();

    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    void remove(const T& data);

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
    bool contains(const T& data) const;

    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    std::size_t find(const T& data) const;

    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    std::size_t size() const;

    /*!
     *
     * TODO: DOCUMENTATION!
     *
     *
     */
    T& operator[](std::size_t index);

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

    Node* end() { return nodeAt(size_); }

    Node* nodeAt(std::size_t index) {
        if (index >= size_)
            throw std::out_of_range("INDEX OUT OF BOUNDS AT");
        auto it = head;
        for (auto i = 0u; i < index; ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

    template<class T>
    LinkedList<T>::~LinkedList() { clear(); }

    template<class T>
    void LinkedList<T>::clear() {
        while (!empty()) {
            pop_front();
        }
    }

    template<class T>
    void LinkedList<T>::push_back(const T &data) { insert(data, size_); }

    template<class T>
    void LinkedList<T>::push_front(const T &data) {
        head = new Node(data, head);
        ++size_;
    }

    template<class T>
    void LinkedList<T>::insert(const T &data, std::size_t index) {
        if (index == 0)
            return push_front(data);
        auto it = nodeAt(index-1);
        it->next(new Node(data, it->next()));
        ++size_;
    }

    template<class T>
    void LinkedList<T>::insert_sorted(const T &data) {
        if (empty() || data <= head->data()) {
            return push_front(data);
        }
        auto it = head;
        for (it = head; it->next() != nullptr; it = it->next()) {
            if (data < it->next()->data())
                break;
        }
        it->next(new Node(data, it->next()));
        ++size_;
    }

    template<class T>
    T &LinkedList<T>::at(std::size_t index) { return nodeAt(index)->data(); }

    template<class T>
    T LinkedList<T>::pop(std::size_t index) {
        if (index >= size_)
            throw std::out_of_range("INDEX OUT OF BOUNDS POP");
        if (index == 0)
            return pop_front();
        auto it = nodeAt(index-1);
        auto to_delete = it->next();
        auto data = std::move(to_delete->data());
        it->next(to_delete->next());
        --size_;
        delete to_delete;
        return data;
    }

    template<class T>
    T LinkedList<T>::pop_back() { return pop(size_-1); }

    template<class T>
    T LinkedList<T>::pop_front() {
        if (empty())
            throw std::out_of_range("EMPTY");
        auto old_head = head;
        auto data = std::move(head->data());
        head = head->next();
        delete old_head;
        --size_;
        return data;
    }

    template<class T>
    void LinkedList<T>::remove(const T &data) {
        auto it = nodeAt(find(data)-1);
        auto to_delete = it->next();
        it->next(to_delete->next());
        delete to_delete;
        --size_;
    }

    template<class T>
    bool LinkedList<T>::empty() const { return size() == 0u; }

    template<class T>
    bool LinkedList<T>::contains(const T &data) const {
        return find(data) != size_;
    }

    template<class T>
    std::size_t LinkedList<T>::find(const T &data) const {
        auto it = head;
        std::size_t index = 0u;
        while (it != nullptr && it->data() != data) {
            it = it->next();
            index++;
        }
        return index;
    }

    template<class T>
    std::size_t LinkedList<T>::size() const { return size_; }

    template<class T>
    T& LinkedList<T>::operator[](std::size_t index) { return at(index); }

}  // namespace structures

#endif
