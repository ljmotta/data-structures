// Copyright [2017] <Luiz Motta>

#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <stdexcept>
#include <cstdint>

namespace structures {

/*!
 * \brief LinkedStack implementa uma pilha encadeada
 */    
template<typename T>
class LinkedStack {
 public:
    /*!
     * \brief Destrutor
     */
    ~LinkedStack();

    /*!
     * \brief Remove todos os elementos da pilha
     */
    void clear();

    /*!
     * \brief Coloca um elemento no topo da pilha
     * 
     * \param data, dado a ser armazenado
     */
    void push(const T& data);

    /*!
     * \brief Retira o elemento que está no topo da lista
     *
     * \return uma copia do dado que estava no topo da lista
     */
    T pop();

    /*!
     * \brief Passa a referencia do dado que está no topo da lista
     *
     * \return referencia do dado do topo da lista.
     */
    T& top() const;

    /*!
     * \brief Verifica se a pilha esta vazia
     *
     * \return true caso a pilha esteja vazia, caso contrario false
     */
    bool empty() const;

    /*!
     * \brief Passa o tamanho da pilha
     *
     * \return tamanho da pilha
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
        top_ = new Node(data, top_);
        ++size_;
    }

    template<typename T>
    T LinkedStack<T>::pop() {
        if (empty())
            throw std::out_of_range("EMPTY");
        auto to_delete = end();
        auto data = std::move(to_delete->data());
        top_ = top_->next();
        --size_;
        delete to_delete;
        return data;
    }

    template<typename T>
    T& LinkedStack<T>::top() const {
        if (empty())
            throw std::out_of_range("EMPTY");
        return top_->data();
    }

    template<typename T>
    bool LinkedStack<T>::empty() const { return size() == 0u; }

    template<typename T>
    std::size_t LinkedStack<T>::size() const { return size_; }

}  // namespace structures

#endif
