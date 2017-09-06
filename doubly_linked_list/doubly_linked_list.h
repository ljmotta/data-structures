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

        Node(const T& data, Node* next): data_{data}, next_{next} {}

        Node(const T& data, Node* prev, Node* next):
            data_{data}, prev_{prev}, next_{next} {}

        T& data() { return data_; }

        const T& data() const { return data_; }

        Node* prev() { return prev_; }

        const Node* prev() const { return prev_; }

        void prev(Node* node) { prev_ = node; }

        Node* next() { return next_; }

        const Node* next() const { return next_; }

        void next(Node* node) { next_ = node; }

     private:
        T data_;
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

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

    template<typename T>
    void DoublyLinkedList<T>::push_front(const T& data) {
        head = new Node(data, head);
        if (head->next() != nullptr)
            head->next()->prev(head);
        ++size_;
    }

    template<typename T>
    void DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
        if (index == 0)
            return push_front(data);
        auto it = nodeAt(index-1);
        auto new_node = new Node(data, it, it->next());
        if (it->next() != nullptr)
            it->next()->prev(new_node);
        it->next(new_node);
        ++size_;
    }

    template<typename T>
    void DoublyLinkedList<T>::insert_sorted(const T& data) {
        if (empty() || data <= head->data())
            return push_front(data);
        auto it = head;
        while (it->next() != nullptr && data > it->next()->data()) {
            it = it->next();
        }
        auto new_node = new Node(data, it, it->next());
        if (it->next() != nullptr)
            it->next()->prev(new_node);
        it->next(new_node);
        ++size_;
    }

    template<typename T>
    T DoublyLinkedList<T>::pop(std::size_t index) {
        if (index == 0)
            return pop_front();
        auto to_delete = nodeAt(index);
        auto data = std::move(to_delete->data());
        if (to_delete->next() != nullptr)
            to_delete->next()->prev(to_delete->prev());
        to_delete->prev()->next(to_delete->next());
        delete to_delete;
        --size_;
        return data;
    }

    template<typename T>
    T DoublyLinkedList<T>::pop_back() { return pop(size()-1); }

    template<typename T>
    T DoublyLinkedList<T>::pop_front() {
        if (empty())
            throw std::out_of_range("EMPTY");
        auto to_delete = head;
        auto data = std::move(to_delete->data());
        head = to_delete->next();
        if (head != nullptr)
            head->prev(to_delete->prev());
        --size_;
        delete to_delete;
        return data;
    }

    template<typename T>
    void DoublyLinkedList<T>::remove(const T& data) {
        auto to_remove = nodeAt(find(data));
        if (to_remove->next() != nullptr)
            to_remove->next()->prev(to_remove->prev());
        to_remove->prev()->next(to_remove->next());
        delete to_remove;
        --size_;
    }

    template<typename T>
    bool DoublyLinkedList<T>::empty() const { return size() == 0u; }

    template<typename T>
    bool DoublyLinkedList<T>::contains(const T& data) const {
        return find(data) != size();
    }

    template<typename T>
    T& DoublyLinkedList<T>::at(std::size_t index) {
        return nodeAt(index)->data();
    }

    template<typename T>
    const T& DoublyLinkedList<T>::at(std::size_t index) const {
        return nodeAt(index)->data();
    }

    template<typename T>
    std::size_t DoublyLinkedList<T>::find(const T& data) const {
        auto it = head;
        std::size_t index = 0u;
        while (it != nullptr && it->data() != data) {
            it = it->next();
            index++;
        }
        return index;
    }

    template<typename T>
    std::size_t DoublyLinkedList<T>::size() const { return size_;}

}  // namespace structures

#endif
