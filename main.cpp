#include <iostream>

#include "tester/tester.h"

int main() {
    //Tester::execute();
    Matrix<int> matriz(4,3);
    matriz.set(0,0,1);
    cout<<"inserte 0 0"<<endl;
    matriz.set(0,1,2);
    cout<<"inserte 0 1"<<endl;
    matriz.set(1,0,3);
    cout<<"inserte 1 0"<<endl;
    matriz.set(1,1,4);
    cout<<"inserte 1 1"<<endl;
    matriz.set(2,0,5);
    cout<<"inserte 2 0"<<endl;
    matriz.set(2,1,6);
    cout<<"inserte 2 1"<<endl;
    matriz.print();
    Matrix<int> matriz2(3,4);
    matriz2.set(0,0,1);
    cout<<"inserte 0 0"<<endl;
    matriz2.set(0,1,2);
    cout<<"inserte 0 1"<<endl;
    matriz2.set(1,0,3);
    cout<<"inserte 1 0"<<endl;
    matriz2.set(1,1,4);
    cout<<"inserte 1 1"<<endl;
    matriz2.set(2,0,5);
    cout<<"inserte 2 0"<<endl;
    matriz2.set(2,1,6);
    cout<<"inserte 2 1"<<endl;
    matriz2.print();
    cout<<"MULTIPLICACION "<<endl;
    matriz*matriz2;


    return EXIT_SUCCESS;
}

