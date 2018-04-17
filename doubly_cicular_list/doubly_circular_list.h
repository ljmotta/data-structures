// Copyright [2017] <Luiz Motta>

#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLY_CIRCULAR_LIST_H

#include <stdexcept>
#include <cstdint>

namespace structures {

/*!
 * \brief Implementação de uma lista circular encadeada
 */
template<typename T>
class DoublyCircularList {
 public:
    /*!
     * \brief Destrutor
     */
    ~DoublyCircularList();

    /*!
     * \brief Limpa a lista
     */
    void clear();

    /*!
     * \brief Insere elemento no final da lista
     *
     * @param data dado a ser inserido
     */
    void push_back(const T& data);

    /*!
     * \brief Insere no inicio da lista
     *
     * @param data dado a ser inserido
     */
    void push_front(const T& data);

    /*!
     * \brief Insere na posicao indicada
     *
     * @param data dado a ser inserido
     * @param index posicao de insercao
     */
    void insert(const T& data, std::size_t index);

    /*!
     * \brief Insere elemento em ordem
     *
     * @param data dado a ser inserido
     */
    void insert_sorted(const T& data);

    /*!
     * \brief Retira dado numa posicao especifica
     *
     * @param index
     * @return dado retirado
     */
    T pop(std::size_t index);

    /*!
     * \brief Retira dado no final da fila
     *
     * @return dado retirado
     */
    T pop_back();

    /*!
     * \brief Retira dado no inicio da fila
     *
     * @return dado retirado
     */
    T pop_front();

    /*!
     * \brief Remove dado especifico
     *
     * @param data dado a ser removido
     */
    void remove(const T& data);

    /*!
     * \brief Verifica se a lista esta vazia
     *
     * @return true caso a lista esteja vazia
     */
    bool empty() const;

    /*!
     * \brief Verifica se a lista contem determinado dado
     *
     * @param data a ser verificado
     * @return true caso possua o dado especificado
     */
    bool contains(const T& data) const;

    /*!
     * \brief Acessa dado num indice especifico
     *
     * @param index indice a ser acessado
     * @return dado a ser acessado
     */
    T& at(std::size_t index);

    /*!
     * \brief Acessa dado num indice especifico
     *
     * @param index indice a ser acessado
     * @return dado a ser acessado
     */
    const T& at(std::size_t index) const;

    /*!
     * \brief Posicao de um item na lista
     *
     * @param data dado a ser verificado
     * @return indice do dado especificado
     */
    std::size_t find(const T& data) const;

    /*!
     * \brief Tamanho da lista
     *
     * @return tamanho da lista
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
    DoublyCircularList<T>::~DoublyCircularList() { clear(); }

    template<typename T>
    void DoublyCircularList<T>::clear() {
        while (!empty()) {
            pop_front();
        }
    }

    template<typename T>
    void DoublyCircularList<T>::push_back(const T &data) {
        insert(data, size());
    }

    template<typename T>
    void DoublyCircularList<T>::push_front(const T &data) {
        if (empty()) {
            head = new Node(data);
            head->next(head);
            head->prev(head);
        } else {
            head = new Node(data, head->prev(), head);
            head->prev()->next(head);
            head->next()->prev(head);
        }
        ++size_;
    }

    template<typename T>
    void DoublyCircularList<T>::insert(const T &data, std::size_t index) {
        if (index == 0)
            return push_front(data);
        auto it = nodeAt(index - 1);
        auto new_node = new Node(data, it, it->next());
        it->next()->prev(new_node);
        it->next(new_node);
        ++size_;
    }

    template<typename T>
    void DoublyCircularList<T>::insert_sorted(const T &data) {
        if (empty() || data <= head->data()) {
            return push_front(data);
        }
        auto it = head;
        for (it = head; it->next() != head; it = it->next()) {
            if (data < it->next()->data())
                break;
        }
        auto new_node = new Node(data, it, it->next());
        it->next()->prev(new_node);
        it->next(new_node);
        ++size_;
    }

    template<typename T>
    T DoublyCircularList<T>::pop(std::size_t index) {
        if (index >= size_)
            throw std::out_of_range("INDEX OUT OF BOUNDS");
        if (index == 0)
            return pop_front();
        auto to_delete = nodeAt(index);
        auto data = std::move(to_delete->data());
        to_delete->next()->prev(to_delete->prev());
        to_delete->prev()->next(to_delete->next());
        --size_;
        delete to_delete;
        return data;
    }

    template<typename T>
    T DoublyCircularList<T>::pop_back() { return pop(size() - 1); }

    template<typename T>
    T DoublyCircularList<T>::pop_front() {
        if (empty())
            throw std::out_of_range("EMPTY");
        auto to_delete = head;
        auto data = std::move(to_delete->data());
        head = to_delete->next();
        --size_;
        delete to_delete;
        return data;
    }

    template<typename T>
    void DoublyCircularList<T>::remove(const T &data) {
        auto to_remove = nodeAt(find(data));
        to_remove->next()->prev(to_remove->prev());
        to_remove->prev()->next(to_remove->next());
        delete to_remove;
        --size_;
    }

    template<typename T>
    bool DoublyCircularList<T>::empty() const { return size() == 0u; }

    template<typename T>
    bool DoublyCircularList<T>::contains(const T &data) const {
        return find(data) != size();
    }

    template<typename T>
    T &DoublyCircularList<T>::at(std::size_t index) {
        return nodeAt(index)->data(); }

    template<typename T>
    const T &DoublyCircularList<T>::at(std::size_t index) const {
        return nodeAt(index)->data();
    }

    template<typename T>
    std::size_t DoublyCircularList<T>::find(const T &data) const {
        auto it = head;
        std::size_t index = 0u;
        while (it != nullptr && it->data() != data && index < size()) {
            it = it->next();
            index++;
        }
        if (index > size())
            throw std::out_of_range("NOT FOUND");
        return index;
    }

    template<typename T>
    std::size_t DoublyCircularList<T>::size() const { return size_; }

}  // namespace structures

#endif
