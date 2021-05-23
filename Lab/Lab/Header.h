#ifndef HEADER_H
#define HEADER_H

#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

//������������� �������
enum Key {
    DIAGONAL_MATRIX, //������������ �������
    TWO_DIMENSIONAL_ARRAY, //��������� ������
    TRIANGULAR_MATRIX //����������� �������
};

//��������� "�������"
struct Matrix {
    Key K; //������������� ������� - ������������ ��� ������� ��������� ������
    void* Obj; //��������� �� ���������� �������
    int N; //����� �������
};

//������� ����� �������
Matrix* In_Matrix(ifstream& ifst);

//������� ������ �������
void Out_Matrix(Matrix* M, ofstream& ofst);

//���������
struct Container {
    Container* Next, * Prev; //��������� �� ����. � ����. �������� ����������
    Matrix* Cont; //��������� �� �������
    int Len; //����� ��������� ����������
};

//������� ������������� ����������
void Init_Container(Container* Head);

//������� ����� ��������� � ���������
void In_Container(Container* Head, ifstream& ifst);

//������� ������ �������� ����������
void Out_Container(Container* Head, ofstream& ofst);

//������� ������� ����������
void Clear_Container(Container* Head);

//��������� ���������� �������
struct Two_dimensional_array {
    int** Array;
};

//������� ����� ���������� �������
Two_dimensional_array* In_Two_dimensional_array(int N, ifstream& ifst);

//������� ������ ���������� �������
void Out_Two_dimensional_array(int N, Two_dimensional_array* T_d_a, ofstream& ofst);

//��������� ������������ �������
struct Diagonal_matrix {
    int* Array;
};

//������� ����� ������������ �������
Diagonal_matrix* In_Diagonal_matrix(int N, ifstream& ifst);

//������� ������ ������������ �������
void Out_Diagonal_matrix(int N, Diagonal_matrix* D_m, ofstream& ofst);

//��������� ����������� �������
struct Triangular_matrix {
    int* Array;
};

//������� ����� ����������� �������
Triangular_matrix* In_Triangular_matrix(int N, ifstream& ifst);

//������� ������ ����������� �������
void Out_Triangular_matrix(int N, Triangular_matrix* T_m, ofstream& ofst);

#endif //HEADER_H