// Copyright [2017] <Luiz Motta>

#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <stdexcept>
#include <cstdint>

namespace structures {


/*!
 * \brief LinkedQueue implementa uma fila encadeada
 */
template<typename T>
class LinkedQueue {
 public:
    /*!
     * \brief Destrutor
     */
    ~LinkedQueue();

    /*!
     * \brief Remove todos os elementos da fila
     */
    void clear();

    /*!
     * \brief Coloca um elemento no inicio da fila
     * 
     * \param data, dado a ser armazenado
     */
    void enqueue(const T& data);

    /*!
     * \brief Retira o elemento que está no final da fila
     *
     * \return uma copia do dado que estava no topo da fila
     */
    T dequeue();

    /*!
     * \brief Passa a referencia do dado que está no incio da fila
     *
     * \return referencia do primeiro dado da fila.
     */
    T& front() const;

    /*!
     * \brief Passa a referencia do dado que está no final da fila
     *
     * \return referencia do ultimo dado da fila.
     */
    T& back() const;

    /*!
     * \brief Verifica se a fila esta vazia
     *
     * \return true caso a fila esteja vazia, caso contrario false
     */
    bool empty() const;

    /*!
     * \brief Passa o tamanho da fila
     *
     * \return tamanho da fila
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

    Node* head{nullptr};
    Node* tail{nullptr};
    std::size_t size_{0u};
};

    template<typename T>
    LinkedQueue<T>::~LinkedQueue() { clear(); }

    template<typename T>
    void LinkedQueue<T>::clear() {
        while (!empty()) {
            dequeue();
        }
    }

    template<typename T>
    void LinkedQueue<T>::enqueue(const T &data) {
        if (empty()) {
            tail = new Node(data);
            head = tail;
        } else {
            auto it = tail;
            it->next(new Node (data, tail->next()));
            tail = it->next();
        }
        ++size_;
    }

    template<typename T>
    T LinkedQueue<T>::dequeue() {
        if (empty())
            throw std::out_of_range("EMPTY");
        if (size() == 1)
            tail = head->next();
        auto to_delete = first();
        auto data = std::move(to_delete->data());
        head = head->next();
        --size_;
        delete to_delete;
        return data;
    }

    template<typename T>
    T& LinkedQueue<T>::front() const {
        if (empty())
            throw std::out_of_range("EMPTY");
        return head->data();
    }

    template<typename T>
    T& LinkedQueue<T>::back() const {
        if (empty())
            throw std::out_of_range("EMPTY");
        return tail->data();
    }

    template<typename T>
    bool LinkedQueue<T>::empty() const { return size() == 0u; }

    template<typename T>
    std::size_t LinkedQueue<T>::size() const { return size_; }

}  // namespace structures

#endif
