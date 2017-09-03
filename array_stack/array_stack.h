// Copyright [2017] <Luiz Motta>

#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>
#include <stdexcept>

namespace structures {

/*!
 *  \brief A classe ArrayStack eh uma implementacao de uma pilha(LIFO)
 *
 *  \sa ArrayStack(), ArrayStack(std::size_t max), ~ArrayStack(),
 *  \sa push(const T& data), pop(), top(), clear(), size(),
 *  \sa maz_size(), empty() and full().
 */

template<class T>
class ArrayStack {
 public:
    /*!
    *  \brief Construtor da pilha com tamanho especificado.
    */
    ArrayStack();

    /*!
    *  \brief Construtor da fila com tamanho desejado.
    *
    *  \param max tamanho maximo permitido da fila.
    */
    explicit ArrayStack(std::size_t max);

    /*!
    *  \brief Destrutor da pilha.
    */
    ~ArrayStack();

    /*!
    *  \brief push adiciona um novo elemento tipo T ao final da pilha.
    *
    *  \param data dado a ser armazenado na pilha.
    */
    void push(const T& data);

    /*!
    *  \brief pop remove o primeiro elemento da pilha.
    *
    *  \return o primeiro elemento da pilha.
    */
    T pop();

    /*!
    *  \brief O metodo top retorna o ultimo elemento da pilha.
    *
    *  \return a referencia do ultimo elemento.
    */
    T& top();

    /*!
    *  \brief O metodo clear limpa a pilha.
    */
    void clear();

    /*!
    *  \brief O metodo size mostra o a quantidade de elementos da pilha.
    *
    *  \return quantidade de elementos da pilha.
    */
    std::size_t size();

    /*!
    *  \brief O metodo max_size mostra a maior quantidade de elementos
    *  possiveis da pilha.
    *
    *  \return tamanho da pilha.
    */
    std::size_t max_size();

    /*!
    *  \brief O metodo empty mostra se a pilha esta vazia.
    *
    *  \return true se a pilha estiver vazia, false se possuir algum elemento.
    */
    bool empty();

    /*!
    *  \brief O metodo full mostra se a pilha esta cheia.
    *
    *  \return true se a pilha estiver cheia, false se nao estiver.
    */
    bool full();

 private:
    T* contents;
    int _top;
    std::size_t _max_size;

    static const auto DEFAULT_SIZE = 10u;
};

template <class T>
ArrayStack<T>::ArrayStack() : ArrayStack(DEFAULT_SIZE) {}

template <class T>
ArrayStack<T>::ArrayStack(std::size_t max) {
    _max_size = max;
    _top = -1;
    contents = new T[_max_size];
}

template <class T>
ArrayStack<T>::~ArrayStack() {
    delete[] contents;
}

template <class T>
void ArrayStack<T>::push(const T& data) {
    if (full())
        throw std::out_of_range("ArrayStack<>::push(T& data): full ArrayStack");
    contents[++_top] = data;
}

template <class T>
T ArrayStack<T>::pop() {
    if (empty())
        throw std::out_of_range("ArrayStack<>::pop(): empty ArrayStack");
    return contents[--_top + 1];
}

template <class T>
T& ArrayStack<T>::top() {
    if (empty())
        throw std::out_of_range("ArrayStack<>::top(): empty ArrayStack");
    return contents[_top];
}

template <class T>
void ArrayStack<T>::clear() {
    _top = -1;
}

template <class T>
std::size_t ArrayStack<T>::size() {
    return _top + 1;
}

template <class T>
std::size_t ArrayStack<T>::max_size() {
    return _max_size;
}

template <class T>
bool ArrayStack<T>::empty() {
    return _top == -1;
}

template <class T>
bool ArrayStack<T>::full() {
    return _top == max_size() - 1;
}

}  // namespace structures

#endif
