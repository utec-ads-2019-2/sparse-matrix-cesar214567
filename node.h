#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
class Node {
protected:
    Node<T> *next, *down;
    T value;
    unsigned int posx,posy;
public:
    Node (unsigned int posx, unsigned int posy,T value):value(value),next(nullptr),down(nullptr),posx(posx),posy(posy){};
    void set_down(Node<T> nodo){
        down=nodo;
    }
    void set_next(Node<T> nodo){
        down=nodo;
    }
    friend class Matrix<T>;

};

template<typename T>
struct Header{
    Node<T> *next;
    Header():next(nullptr){};

};


#endif //SPARSE_MATRIX_NODE_H
