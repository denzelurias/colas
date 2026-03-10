
#include <iostream>

//****************************************************************************
template <typename T> cola<T>::cola() : _numElem(0), _frente(nullptr),_fondo(nullptr) {}

//****************************************************************************
template <typename T> cola<T>::~cola() { vaciar(); }

//****************************************************************************
template <typename T>
cola<T>::cola(const cola<T> &s) : _numElem(0), _frente(nullptr), _fondo(nullptr) {
    *this = s;
}

//****************************************************************************
template <typename T> cola<T> &cola<T>::operator=(const cola<T> &c) {
    if (this == &c) return *this;
    vaciar();

    elemento *visitado = c._frente;
    while (visitado != nullptr) {
        agregar(visitado->_valor);
        visitado = visitado->_siguiente;
    }
    return *this;
}

//****************************************************************************
template <typename T> void cola<T>::agregar(T valor) {
    try {
        elemento *nuevo = new elemento(valor);
        if (estaVacia()) _frente = nuevo;
        else _fondo->_siguiente = nuevo;

        _fondo = nuevo;
        ++_numElem;
    } catch (std::bad_alloc &) {
        throw std::runtime_error("No es posible agregar el elemento a la cola");
    }
}

//****************************************************************************
template <typename T> void cola<T>::eliminar() {
    if (estaVacia()) throw std::runtime_error("La cola está vacía");

    elemento *porBorrar = _frente;
    _frente = _frente->_siguiente;

    if(_numElem == 1) _fondo = nullptr;
    delete porBorrar;
    --_numElem;
}

//****************************************************************************
template <typename T> void cola<T>::vaciar() {
    while (!estaVacia())
        eliminar();
}

//****************************************************************************
template <typename T> T cola<T>::frente() const {
    if (estaVacia()) throw std::runtime_error("Error: La cola está vacía.");

    return _frente->_valor;
}

//****************************************************************************
template <typename T> T cola<T>::fondo() const {
    if (estaVacia()) throw std::runtime_error("Error: La cola está vacía.");

    return _fondo->_valor;
}

//****************************************************************************
template <typename T> int cola<T>::tamano() const { return _numElem; }

//****************************************************************************
template <typename T> bool cola<T>::estaVacia() const { return _numElem == 0; }

//****************************************************************************
template <typename T> void cola<T>::imprimir() const {
    if (estaVacia()) throw std::runtime_error("La cola está vacía");

    elemento *aux = _frente;
    while (aux != nullptr) {
        std::cout << aux->_valor << std::endl;
        aux = aux->_siguiente;
    }
}

//****************************************************************************
template <typename T>
cola<T>::elemento::elemento(T valor, cola<T>::elemento *siguiente): _valor(valor), _siguiente(siguiente) {}
//****************************************************************************