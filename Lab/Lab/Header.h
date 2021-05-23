#ifndef HEADER_H
#define HEADER_H

#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

//Иднетификатор матрицы
enum Key {
    DIAGONAL_MATRIX, //Диагональная матрицы
    TWO_DIMENSIONAL_ARRAY, //Двумерный массив
    TRIANGULAR_MATRIX //Треугольная матрицы
};

//Структура "матрицы"
struct Matrix {
    Key K; //Идентификатор матрицы - диагональная или обычный двумерный массив
    void* Obj; //Указатель на конкретную матрицы
    int N; //Длина массива
};

//Функция ввода матрицы
Matrix* In_Matrix(ifstream& ifst);

//Функция вывода матрица
void Out_Matrix(Matrix* M, ofstream& ofst);

//Контейнер
struct Container {
    Container* Next, * Prev; //Указатели на след. и пред. элементы контейнера
    Matrix* Cont; //Указатель на матрицы
    int Len; //Число элементов контейнера
};

//Функция инициализации контейнера
void Init_Container(Container* Head);

//Функция ввода элементов в контейнер
void In_Container(Container* Head, ifstream& ifst);

//Функция вывода элемента контейнера
void Out_Container(Container* Head, ofstream& ofst);

//Функция очистки контейнера
void Clear_Container(Container* Head);

//Структура двумерного массива
struct Two_dimensional_array {
    int** Array;
};

//Функция ввода двумерного массива
Two_dimensional_array* In_Two_dimensional_array(int N, ifstream& ifst);

//Функция вывода двумерного массива
void Out_Two_dimensional_array(int N, Two_dimensional_array* T_d_a, ofstream& ofst);

//Структура диагональной матрицы
struct Diagonal_matrix {
    int* Array;
};

//Функция ввода диагональной матрицы
Diagonal_matrix* In_Diagonal_matrix(int N, ifstream& ifst);

//Функция вывода диагональной матрицы
void Out_Diagonal_matrix(int N, Diagonal_matrix* D_m, ofstream& ofst);

//Структура треугольной матрицы
struct Triangular_matrix {
    int* Array;
};

//Функция ввода треугольной матрицы
Triangular_matrix* In_Triangular_matrix(int N, ifstream& ifst);

//Функция вывода треугольной матрицы
void Out_Triangular_matrix(int N, Triangular_matrix* T_m, ofstream& ofst);

#endif //HEADER_H