#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include "node.h"
#include <vector>
#include <iostream>
using namespace std;

template <typename T>
class Matrix {
private:
    vector<Header<T>> rootx;
    vector<Header<T>> rooty;

public:
    Matrix(unsigned rows, unsigned columns){
        rootx.resize(rows);
        rooty.resize(columns);

    };

    unsigned int get_rows(){ return rootx.size();}
    unsigned int get_columns(){ return rooty.size();}
    

    // Tu código no está muy límpio, hay bastantes cosas que pudiste sacar a funciones privadas
    void set(unsigned x, unsigned y, T c){

        //what happend if you do out of range
        if (x>=rootx.size() || y>=rooty.size()){
            throw out_of_range("OUT OF RANGE");
            return;
        }

        if (c==0){
            //remove
            Header<T>* tempx=&rootx[x];
            Header<T>* tempy=&rooty[y];
            Node<T> *temporal=nullptr;
            if (tempx->next==nullptr){
                //if there is nothing in a row, then the value does not exist;
                return;
            }else{
                //cout<<"GOT HERE1"<<endl;
                //cout<<rootx[0].next->posx<<" "<<rootx[0].next->posy<<endl;
                //cout<<tempx->next->posy<<endl;
                if(tempx->next->posy==y){
                    //cout<<"GOT HERE4"<<endl;
                    temporal=tempx->next; 
                    tempx->next=temporal->next;
                }else{
                    //cout<<"GOT HERE2"<<endl;

                    Node<T>* it1=tempx->next;
                    Node<T>* it2=it1->next;
                    if (it1->posy>y){
                        //if the first element has an y value bigger than the one we want, then it does not works
                        return;
                    }
                    while (it2!=nullptr && it2->posy<y){
                        it1=it2;
                        it2=it1->next;
                    }
                    if (it2==nullptr){
                        //cout<<"LLEGO AL ULTIMO Y NO ENCONTRO"<<endl;
                        return;
                    }
                    if (it2->posy==y){
                        temporal=it2;
                        it1->next=it2->next;
                    }else{
                        //it just simply does not exists
                        //cout<<"no existe ese bloque"<<endl;
                        return;
                    }
                }
            }
            if (!tempy->next){
                cout<<"NANI"<<endl;
            }
            if (tempy->next==temporal){
                tempy->next=tempy->next->down;
            }else{
                
                Node<T>* it1=tempy->next;
                Node<T>* it2=it1->down;
                while (it2!=nullptr && it2->posx<x){
                    it1=it2;
                    it2=it1->down;
                }
                if (it2==nullptr){
                    //cout<<"LLEGO AL ULTIMO Y NO ENCONTRO"<<endl;
                    return;
                }
                if (it2->posx==x){
                    temporal=it2;
                    it1->down=it2->down;
                }else{
                    //it just simply does not exists
                    cout<<"no existe ese bloque"<<endl;
                    return;
                }
                delete temporal; 

            }


        //insert
        }else{
                
            
            Header<T>* tempx=&rootx[x];
            Header<T>* tempy=&rooty[y];
            Node<T> *temporal=nullptr;
            if (tempx->next==nullptr){
                tempx->next=new Node<T>(x,y,c);
                temporal=tempx->next;
                //cout<<tempx->next->value<<endl;
            }else{
                //check if the first y value is higher or equal than the thing we wanna put
                if (tempx->next->posy==y){
                    tempx->next->value=c;
                    return; 
                }else{
                    if (tempx->next->posy>y ){
                        auto temporal2=tempx->next;
                        tempx->next=nullptr;
                        tempx->next=new Node<T>(x,y,c);
                        tempx->next->next=temporal2;
                        temporal=tempx->next;
                        return;
                    }else{
                        //while loop if is less than the thing we wanna put
                        Node<T>* iterador1=tempx->next;
                        Node<T>* iterador2=iterador1->next;
                        while (iterador2!=nullptr && iterador2->posy<y){
                            iterador1=iterador2;
                            iterador2=iterador1->next;
                        }//go to the position
                        if (iterador2==nullptr ){
                            iterador1->next=new Node<T>(x,y,c);
                            temporal=iterador1->next;
                        }else{
                            if (iterador2->posy==y){
                                iterador2->value=c;
                            }else{
                                //if exists 4 and 6 and you wanna put 5 you get iterator1 as 4 and iterator2 as 6
                                iterador1->next=nullptr;
                                iterador1->next=new Node<T>(x,y,c);
                                temporal=iterador1->next;
                                temporal->next=iterador2;
                            }
                        }
                    }
                }
            }
            //cout<<"passed"<<endl;
            if (tempy->next==nullptr){
                tempy->next=temporal;
                //cout<<"FIRST THING IN THIS COLUMN "<<y<<endl;
                return;
            }else{
                //check if the first y value is higher or equal than the thing we wanna put
                if (tempy->next->posx==x){
                    tempy->next->value=c;
                    return; 
                }else{

                    if (tempy->next->posx>x ){
                        auto temporal2=tempy->next; //wtf
                        tempy->next=nullptr;
                        tempy->next=temporal;
                        tempy->next->down=temporal2;
                        return;
                    }else{
                        //while loop if is less than the thing we wanna put
                        Node<T>* iterador1=tempy->next;
                        Node<T>* iterador2=iterador1->down;
                        while (iterador2!=nullptr && iterador2->posx<x){
                            iterador1=iterador2;
                            iterador2=iterador1->down;
                        }//go to the position
                        if (iterador2==nullptr){
                            iterador1->down=temporal;
                            //cout<<"se inserto nodo debajo del nodo con x y"<<iterador1->posx<<" "<<iterador1->posy<<endl;
                            //cout<<"el nodo insertado tiene valor x y"<<temporal->posx<<" "<<temporal->posy<<endl;
                            temporal=iterador1->down;
                        }else{
                            if (iterador2->posx==x){
                                iterador2->value=c;
                            }else{
                                //if exists 4 and 6 and you wanna put 5 you get iterator1 as 4 and iterator2 as 6
                                iterador1->down=nullptr;
                                iterador1->down=temporal;
                                temporal=iterador1->down;
                                temporal->down=iterador2;
                            }
                        }
                    }
                }
            }
            
            

        }
    };
    T operator()(unsigned x , unsigned y ){
        Header<T>* temp1=nullptr; 
        if (x>y){
            temp1=&rootx[x];
            Node<T>* temp2=temp1->next;
            while (temp2!=nullptr){
                if (temp2->posy<y){
                    temp2=temp2->next; 
                }else{
                    break;
                }

            }
            if (temp2==nullptr){
                return 0;
            }else{
                if (temp2->posy==y){
                    return temp2->value;
                }else{
                    return 0;
                }
            }

        }else{
            temp1=&rooty[y];
            Node<T>* temp2=temp1->next;
            while (temp2!=nullptr){
                if (temp2->posx<x){
                    temp2=temp2->down; 
                }else{
                    break;
                }

            }
            if (temp2==nullptr){
                return 0;
            }else{
                if (temp2->posx==x){
                    return temp2->value;
                }else{
                    return 0;
                }
            }
        }


    }
    Matrix<T> operator*(T scalar) {
        Matrix<T> nuevo(rootx.size(),rooty.size());
        for (int i=0;i<rootx.size();i++){
            for (int j=0;j<rooty.size();j++){
                nuevo.set(i,j,this->operator()(i,j)*scalar);
            }
        }
        nuevo.print();
        return nuevo; 
    }
    
    
    // Al utilizar los operadores estás haciendo que tus operaciones sean más lentas
    Matrix<T> operator*(  Matrix<T> matriz2){
        Matrix<T> temp(this->rootx.size(),matriz2.rooty.size());
        if(this->rooty.size()== matriz2.rootx.size()) {
            for (int i = 0; i < this->rootx.size(); i++) {
                for (int j = 0; j < matriz2.rooty.size(); j++){
                    T valor_temporal=0;
                    for (int z = 0; z < matriz2.rootx.size(); z++) {
                        valor_temporal+=this->operator()(i,z)*matriz2(z,j);
                    }
                    temp.set(i,j,valor_temporal);
                }
            }
            cout<<"DONE"<<endl;
            temp.print();

            //falta retornar
        }
        else{
            cout<<"las filas y columnas que se ingresaron fueron diferentes"<<endl;
            return temp;
        }

    }








    Matrix<T> operator+(Matrix<T> other) {
        if (other.rootx.size()!=this->rootx.size() && other.rooty.size()!=this->rooty.size()){
            throw out_of_range("out of range ");
        }else{
            Matrix<T> nuevo(rootx.size(),rooty.size());
            for (int i=0;i<rootx.size();i++){
                for (int j=0;j<rooty.size();j++){
                    nuevo.set(i,j,this->operator()(i,j)+other(i,j));
                }
            }
            nuevo.print();
            return nuevo;
        }
    }
    Matrix<T> operator-(Matrix<T> other){
        if (other.rootx.size()!=this->rootx.size() && other.rooty.size()!=this->rooty.size()){
            throw out_of_range("out of range ");
        }else{
            Matrix<T> nuevo(rootx.size(),rooty.size());
            for (int i=0;i<rootx.size();i++){
                for (int j=0;j<rooty.size();j++){
                    nuevo.set(i,j,this->operator()(i,j)-other(i,j));
                }
            }
        nuevo.print();
            return nuevo;
        }
    }
    void transpose(){
        cout<<endl;
        vector<Node<T>> temporal;
        for(int i=0;i<rootx.size();i++){
            for (int j=0;j<rooty.size();j++){
                double nodo=this->operator()(i,j);
                if (nodo!=0){
                    temporal.emplace_back(Node<T>(j,i,nodo));
                }
            }
        }
        
        this->clear();
        int x=rootx.size();
        rootx.resize(rooty.size());
        rooty.resize(x);
        for (auto it:temporal){
            
            this->set(it.posx,it.posy,it.value);
        }
        this->print();

    }
    
    
    void clear(){
        for(int i=0;i<rootx.size();i++){
            for (int j=0;j<rooty.size();j++){
                this->set(i,j,0);
            }
        }
    }
    
    
    void print(){
        int contador2=0;
        for (auto it:rootx){
            auto temporal=it.next;
            if (temporal==nullptr){
                //cout<<"LOOOOP2"<<endl;
                for (int i=0;i<rooty.size();i++){
                    cout<<"0 ";
                }
                cout<<endl;
                contador2++;
                continue;
            }
            int contador=0;
            while (temporal!=nullptr){
                for (int i=contador;i<temporal->posy;i++){
                    cout<<0<<" ";
                    //cout<<"LOOP"<<endl;
                }
                //cout<<"got here"<<endl;
                cout<<temporal->value<<" ";
                contador=temporal->posy+1;
                temporal=temporal->next;
            }
            //cout<<"contador"<<contador<<endl;
            for (int i=contador;i<rooty.size();i++){
                cout<<"0 ";
            }
            cout<<endl;
            contador2++;
        }
        
    }

    ~Matrix(){
        clear();
    }

};

#endif //SPARSE_MATRIX_MATRIX_H