// Copyright [2017] <Luiz Motta>

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {
/*!
* \brief implementação de lista feita com vetor
*/
template<typename T>
class ArrayList {
 public:
    /*!
    * \brief Construtor do ArrayList
    */
    ArrayList();

    /*!
    * \brief Contrutor do ArrayList com tamanho especifico
    *
    * \param max_size
    */
    explicit ArrayList(std::size_t max_size);

    /*!
    * \brief Destrutor do ArrayList
    */
    ~ArrayList();

    /*!
    * \brief Limpa o ArrayList.
    */
    void clear();

    /*!
    * \brief Adiciona elemento no final.
    *
    * \param data
    */
    void push_back(const T& data);

    /*!
    * \brief Adiciona elemento no inicio.
    *
    * \param data
    */
    void push_front(const T& data);

    /*!
    * \brief Adiciona elemento na posicao.
    *
    * \param data, index
    */
    void insert(const T& data, std::size_t index);

    /*!
    * \brief Adiciona elemento na ordem.
    *
    * \param data
    */
    void insert_sorted(const T& data);

    /*!
    * \brief Remove um elemento na posicao.
    *
    * \param index
    *
    * \return elemento do index.
    */
    T pop(std::size_t index);

    /*!
    * \brief Remove um elemento do final.
    *
    * \return ultimo elemento.
    */
    T pop_back();

    /*!
    * \brief Remove um elemento do inicio.
    *
    * \return primeiro elemento.
    */
    T pop_front();

    /*!
    * \brief Remove um elemento especifico.
    *
    * \param data
    */
    void remove(const T& data);

    /*!
    * \brief Testa se o arraylist esta vazio.
    *
    * \return true se estiver vazio, false se tiver elemento
    */
    bool empty() const;

    /*!
    * \brief Testa se o arraylist esta cheio.
    *
    * \return true se estiver cheio, false se tiver espaço
    */
    bool full() const;

    /*!
    * \brief Testa se o arraylist contem um dado especifico.
    *
    * \param data
    *
    * \return true se possui o elemento data
    */
    bool contains(const T& data) const;

    /*!
    * \brief Retorna o index de um determinado dado.
    *
    * \param data
    *
    * \return index do elemento data
    */
    std::size_t find(const T& data) const;

    /*!
    * \brief Retorna o tamanho do arraylist.
    *
    * \return tamanho do arraylist
    */
    std::size_t size();

    /*!
    * \brief Retorna o tamanho maximo do arraylist.
    *
    * \return tamanho maximo do arraylist
    */
    std::size_t max_size();

    /*!
    * \brief Retorna o elemento na posição desejada.
    *
    * \param index
    *
    * \return elemento da posicao index
    */
    T& at(std::size_t index);

    /*!
    * \brief Introduz o operador []
    *
    * \param index
    *
    * \return operador[]
    */
    T& operator[](std::size_t index);

    /*!
    * \brief Retorna o elemento na posição desejada.
    *
    * \param index
    *
    * \return elemento da posicao index
    */
    const T& at(std::size_t index) const;

    /*!
    * \brief Introduz o operador []
    *
    * \param index
    *
    * \return operador[]
    */
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    int _size;
    std::size_t _max_size;

    static const auto DEFAULT_MAX = 10u;
};

    template <class T>
    ArrayList<T>::ArrayList() : ArrayList(DEFAULT_MAX) {}

    template <class T>
    ArrayList<T>::ArrayList(std::size_t max) {
        _size = -1;
        _max_size = max;
        contents = new T[max];
    }

    template <class T>
    ArrayList<T>::~ArrayList() {
        delete[] contents;
    }

    template <class T>
    void ArrayList<T>::clear() {
        _size = -1;
    }

    template <class T>
    void ArrayList<T>::push_back(const T& data) {
        insert(data, size());
    }

    template <class T>
    void ArrayList<T>::push_front(const T& data) {
        insert(data, 0);
    }

    template <class T>
    void ArrayList<T>::insert(const T& data, std::size_t index) {
        if (full()) {
            throw std::out_of_range("FULL");
        } else {
            ++_size;
            if (index > _size+1 || index < 0) {
                throw std::out_of_range("INDEX_OUT_OF_BOUNDS");
            }
            int atual = _size;
            while (atual > index) {
                contents[atual] = contents[atual-1];
                --atual;
            }
            contents[index] = data;
        }
    }

    template <class T>
    void ArrayList<T>::insert_sorted(const T& data) {
        int atual;
        if (full()) {
            throw std::out_of_range("FULL");
        } else {
            atual = 0;
            while (atual <= _size && data > contents[atual]) {
                atual++;
            }
            if ((_size+1) == 0) {
                push_back(data);
            } else {
                insert(data, atual);
            }
        }
    }

    template <class T>
    T ArrayList<T>::pop(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("EMPTY");
        } else if (index > _size || index >= -1) {
            throw std::out_of_range("INDEX_OUT_OF_BOUNDS");
        }
        auto data = contents[index];
        --_size;
        for (auto i = index; i < size(); i++) {
            contents[i] = contents[i+1];
        }
        return data;
    }

    template <class T>
    T ArrayList<T>::pop_back() {
        return pop(_size);
    }

    template <class T>
    T ArrayList<T>::pop_front() {
        return pop(0);
    }

    template <class T>
    void ArrayList<T>::remove(const T& data) {
        if (empty()) {
            std::out_of_range("EMPTY");
        } else if (!contains(data)) {
            std::out_of_range("DO NOT CONTAIN");
        } else {
            for (auto i = 0; i < _size-1; i++) {
                if (contents[i] == data) {
                    contents[i] = contents[i+1];
                    break;
                }
            }
            --_size;
        }
    }

    template <class T>
    bool ArrayList<T>::full() const {
        return _size == _max_size-1;
    }

    template <class T>
    bool ArrayList<T>::empty() const {
        return _size == -1;
    }

    template <class T>
    bool ArrayList<T>::contains(const T& data) const {
        return find(data) < _size;
    }

    template <class T>
    std::size_t ArrayList<T>::find(const T &data) const {
        std::size_t index;
        if (empty()) {
            throw std::out_of_range("EMPTY");
        } else {
            for (index = 0; index < _size+1; index++) {
                if (contents[index] == data) {
                    break;
                }
            }
        }
        return index;
    }

    template <class T>
    std::size_t ArrayList<T>::size() {
        return _size+1;
    }

    template <class T>
    std::size_t ArrayList<T>::max_size() {
        return _max_size;
    }

    template <class T>
    T& ArrayList<T>::at(std::size_t index) {
        if (index < 0 || index >= -1) {
            throw std::out_of_range("INDEX_OUT_OF_BOUNDS");
        }
        return contents[index];
    }

    template <class T>
    T& ArrayList<T>::operator[](std::size_t index) {
        return at(index);
    }

    template <class T>
    const T& ArrayList<T>::at(std::size_t index) const {
        if (index < 0 || index >= -1) {
            throw std::out_of_range("INDEX_OUT_OF_BOUNDS");
        }
        return contents[index];
    }

    template <class T>
    const T& ArrayList<T>::operator[](std::size_t index) const {
        return at(index);
    }

}  // namespace structures

#endif
