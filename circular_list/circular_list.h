// Copyright [2017] <Luiz Motta>

#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <stdexcept>
#include <cstdint>

namespace structures {

/*!
 * \brief Implementação de uma lista circular
 */
template<typename T>
class CircularList {
 public:
    /*!
     * \brief Destrutor
     */
    ~CircularList();

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

        T& data() { return data_; }

        const T& data() const { return data_; }

        Node* next() { return next_; }

        const Node* next() const { return next_; }

        void next(Node* node) { next_ = node; }

     private:
        T data_;
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
    CircularList<T>::~CircularList() { clear(); }

    template<typename T>
    void CircularList<T>::clear() {
        while (!empty()) {
            pop_front();
        }
    }

    template<typename T>
    void CircularList<T>::push_back(const T &data) { insert(data, size()); }

    template<typename T>
    void CircularList<T>::push_front(const T &data) {
        if (empty())
            head = new Node(data);
        else
            head = new Node(data, head);
        ++size_;
        nodeAt(size() - 1)->next(head);
    }

    template<typename T>
    void CircularList<T>::insert(const T &data, std::size_t index) {
        if (index == 0)
            return push_front(data);
        auto it = nodeAt(index - 1);
        it->next(new Node(data, it->next()));
        ++size_;
    }

    template<typename T>
    void CircularList<T>::insert_sorted(const T &data) {
        if (empty() || data <= head->data()) {
            return push_front(data);
        }
        auto it = head;
        for (it = head; it->next() != head; it = it->next()) {
            if (data < it->next()->data())
                break;
        }
        it->next(new Node(data, it->next()));
        ++size_;
    }

    template<typename T>
    T &CircularList<T>::at(std::size_t index) {
        return nodeAt(index)->data(); }

    template<typename T>
    const T &CircularList<T>::at(std::size_t index) const {
        return nodeAt(index)->data();
    }

    template<typename T>
    T CircularList<T>::pop(std::size_t index) {
        if (index >= size_)
            throw std::out_of_range("INDEX OUT OF BOUNDS");
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

    template<typename T>
    T CircularList<T>::pop_back() { return pop(size() - 1); }

    template<typename T>
    T CircularList<T>::pop_front() {
        if (empty())
            throw std::out_of_range("EMPTY");
        auto to_delete = head;
        auto data = std::move(head->data());
        head = head->next();
        --size_;
        delete to_delete;
        return data;
    }

    template<typename T>
    void CircularList<T>::remove(const T &data) {
        auto it = nodeAt(find(data)-1);
        auto to_delete = it->next();
        it->next(to_delete->next());
        delete to_delete;
        --size_;
    }

    template<typename T>
    bool CircularList<T>::empty() const { return size() == 0u; }

    template<typename T>
    bool CircularList<T>::contains(const T &data) const {
        return find(data) != size();
    }

    template<typename T>
    std::size_t CircularList<T>::find(const T &data) const {
        auto it = head;
        std::size_t index = 0u;
        while (it != nullptr && it->data() != data && index < size()) {
            it = it->next();
            index++;
        }
        return index;
    }

    template<typename T>
    std::size_t CircularList<T>::size() const { return size_; }

}  // namespace structures

#endif
