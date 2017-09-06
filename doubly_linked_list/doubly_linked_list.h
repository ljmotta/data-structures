// Copyright [2017] <Luiz Motta>

#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <stdexcept>
#include <cstdint>

namespace structures {

/*!
 * \brief A classe DoublyLinkedList implementa uma lista duplamente encadeada 
 */
template<typename T>
class DoublyLinkedList {
 public:
    /*!
     * \brief Destrutor
     */
    ~DoublyLinkedList();

    /*!
     * \brief Remove todos os elementos da lista
     */
    void clear();

    /*!
     * \brief Insere um dado ao final da lista
     */
    void push_back(const T& data);

    /*!
     * \brief Insere um dado no inicio da lista
     */
    void push_front(const T& data);

    /*!
     * \brief Insere um dado num determinado index
     */
    void insert(const T& data, std::size_t index);

    /*!
     * \brief Insere numa ordem especifica
     */
    void insert_sorted(const T& data);

    /*!
     * \brief Remove um dado de um determinado index
     *
     * \param index posicao a ser acessada na lista
     *
     * \return elemento no index especificado
     */
    T pop(std::size_t index);

    /*!
     * \brief Remove um dado do final da lista
     *
     * \return ultimo elemento da lista
     */
    T pop_back();

    /*!
     * \brief Remove um dado do inicio da lista
     *
     * \return primeiro elemento da lista
     */
    T pop_front();

    /*!
     * \brief Remove um dado em especifico
     *
     * \param data dado a ser removido
     */
    void remove(const T& data);

    /*!
     * \brief Verifica se a lista esta vazia
     *
     * \return true caso esteja vazia, caso contrario false
     */
    bool empty() const;

    /*!
     * \brief Verifica se a lista possui um determinado elemento
     *
     * \param data elemento a ser procurado
     *
     * \return caso possua o elemento retorna true, caso contrario false
     */
    bool contains(const T& data) const;

    /*!
     * \brief Getter
     *
     * \param index posicao do elemento que deseja
     *
     * \return elemento desejado
     */
    T& at(std::size_t index);

    /*!
     * \brief Getter
     *
     * \param index posicao do elemento que deseja
     *
     * \return elemento desejado
     */
    const T& at(std::size_t index) const;

    /*!
     * \brief Index de um determinado elemento
     *
     * \param data dado que deseja saber o index
     *
     * \return index do elemento
     */
    std::size_t find(const T& data) const;

    /*!
     * \brief Tamanho da lista
     *
     * \return tamanho da lista
     */
    std::size_t size() const;

 private:
    class Node {
     public:
        explicit Node(const T& data): data_{data} {}

        Node(const T& data, Node* next): data_{data}, next{next} {}

        Node(const T& data, Node* prev, Node* next): 
            data_{data}, prev{prev}, next{next} {}

        T& data() { return data_; }

        const T& data() const { return data_; }

        Node* prev() { return prev; }

        const Node* prev() const { return prev; }

        void prev(Node* node) { prev = node; }

        Node* next() { return next; }

        const Node* next() const { return next; }

        void next(Node* node) { next = node; }

     private:
        Node* nodeAt(std::size_t index) {
            if (index >= size_)
                throw std::out_of_range("INDEX OUT OF BOUNDS");
            if (index >= size_/2) {
                auto it = tail;
                for (std::size_t i = index; i < size_; i++) {
                    it = it->prev();
                }
            }
            else {
                auto it = head;
                for (std::size_t i = 0u; i < index; i++) {
                    it = it->next();
                }
            }
            return it;
        }

        T data_;
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

    Node* head{nullptr};
    Node* tail{nullptr};
    std::size_t size_{0u};
};

    template<typename T>
    DoublyLinkedList<T>::~DoublyLinkedList() { clear(); }

    template<typename T>
    void DoublyLinkedList<T>::clear() {
        while (!empty()) {
            pop_front();
        }
    }

    template<typename T>
    void DoublyLinkedList<T>::push_back(const T& data) {
        return insert(data, size());
    }

    // to implement
    template<typename T>
    void DoublyLinkedList<T>::push_front(const T& data) {
        head = new Node(data, head->prev(), head);
        ++size_;
    }

    // to implement
    template<typename T>
    void DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
        if (index == 0)
            return push_front(data);
        auto it_prev = nodeAt(index-1);
        it_prev->next(new Node(data, it_prev, it_prev->next()));
        ++size_;
    }

    // to implement
    template<typename T>
    void DoublyLinkedList<T>::insert_sorted(const T& data) {
    }

    // to implement
    template<typename T>
    T DoublyLinkedList<T>::pop(std::size_t index) {
        if (empty())
            throw std::out_of_range("EMPTY");
        if (index == 0)
            return pop_front();
        auto to_delete =
    }

    template<typename T>
    T DoublyLinkedList<T>::pop_back() { return pop(size()-1); }

    // to implement
    template<typename T>
    T DoublyLinkedList<T>::pop_front() { 
        if (empty())
            throw std::out_of_range("EMPTY");
    }

    // to implement
    template<typename T>
    void DoublyLinkedList<T>::remove(const T& data) {
    }

    template<typename T>
    bool DoublyLinkedList<T>::empty() const { return size() == 0u; }

    // to implement
    template<typename T>
    bool DoublyLinkedList<T>::contains(const T& data) const {
        return true;
    }

    template<typename T>
    T& DoublyLinkedList<T>::at(std::size_t index) {
        return nodeAt(index)->data();
    }

    template<typename T>
    const T& DoublyLinkedList<T>::at(std::size_t index) const {
        return nodeAt(index)->data();
    }

    // to implement
    template<typename T>
    std::size_t DoublyLinkedList<T>::find(const T& data) const {
        return size_;
    }

    template<typename T>
    std::size_t DoublyLinkedList<T>::size() const { return size_;}

}  // namespace structures

#endif
