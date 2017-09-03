// Copyright [2017] <Luiz Motta>

#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>
#include <stdexcept>

namespace structures {

/*!
 *  \brief A classe ArrayQueue eh uma implementacao de uma fila(FIFO)
 *
 *  \sa ArrayQueue(), ArrayQueue(std::size_t max), ~ArrayQueue(), 
 *  \sa enqueue(const T& data), dequeue(), back(), clear(), size(), 
 *  \sa maz_size(), empty() and full().
 */

template<class T>
class ArrayQueue {
 public:
    /*!
     *  \brief Construtor da fila com tamanho especificado.
     */
    ArrayQueue();

    /*!
     *  \brief Construtor da fila com tamanho desejado.
     *
     *  \param max tamanho maximo permitido da fila.
     */
    explicit ArrayQueue(std::size_t max);

    /*!
     *  \brief Destrutor da fila.
     */
    ~ArrayQueue();

    /*!
     *  \brief enqueue adiciona um novo elemento tipo T ao final da fila.
     *
     *  \param data dado a ser armazenado na fila.
     */
    void enqueue(const T& data);

    /*!
     *  \brief dequeue remove o primeiro elemento da fila.
     *
     *  \return o primeiro elemento da fila.
     */
    T dequeue();

    /*!
     *  \brief O metodo back retorna o ultimo elemento da fila.
     *
     *  \return a referencia do ultimo elemento.
     */
    T& back();

    /*!
     *  \brief O metodo clear limpa a fila
     *
     */
    void clear();

    /*!
     *  \brief O metodo size mostra o a quantidade de elementos da fila.
     *
     *  \return quantidade de elementos da fila.
     */
    std::size_t size();

    /*!
     *  \brief O metodo max_size mostra a maior quantidade de elementos 
     *  possiveis
     *
     *  \return tamanho da fila.
     */
    std::size_t max_size();

    /*!
     *  \brief O metodo empty mostra se a fila esta vazia.
     *
     *  \return true se a fila estiver vazia, false se possuir algum elemento.
     */
    bool empty();

    /*!
     *  \brief O metodo full mostra se a fila esta cheia.
     *
     *  \return true se a fila estiver cheia, false se nao estiver.
     */
    bool full();

 private:
    T* contents;
    std::size_t _size;
    std::size_t _max_size;

    static const auto DEFAULT_SIZE = 10u;
};

template <class T>
ArrayQueue<T>::ArrayQueue() : ArrayQueue(DEFAULT_SIZE) {}

template <class T>
ArrayQueue<T>::ArrayQueue(std::size_t max) {
    _max_size = max;
    _size = -1;
    contents = new T[_max_size];
}

template <class T>
ArrayQueue<T>::~ArrayQueue() {
    delete[] contents;
}

template <class T>
void ArrayQueue<T>::enqueue(const T& data) {
    if (full())
        throw std::out_of_range("full ArrayQueue");
    contents[++_size] = data;
}

template <class T>
T ArrayQueue<T>::dequeue() {
    if (empty())
        throw std::out_of_range("empty ArrayQueue");
    auto data = contents[0];
    for (int i = 0; i < _max_size - 1; i++) {
        contents[i] = contents[i+1];
    }
    _size--;
    return data;
}

template <class T>
T& ArrayQueue<T>::back() {
    if (empty())
        throw std::out_of_range("empty ArrayQueue");
    return contents[_size];
}

template <class T>
void ArrayQueue<T>::clear() {
    _size = -1;
}

template <class T>
std::size_t ArrayQueue<T>::size() {
    return _size + 1;
}

template <class T>
std::size_t ArrayQueue<T>::max_size() {
    return _max_size;
}

template <class T>
bool ArrayQueue<T>::empty() {
    return _size == -1;
}

template <class T>
bool ArrayQueue<T>::full() {
    return _size == max_size() - 1;
}

}  // namespace structures

#endif

