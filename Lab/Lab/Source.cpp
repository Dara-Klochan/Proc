#include "Header.h"

void Init_Container(Container* Head) {
    Head->Cont = NULL;
    Head->Len = 0;
    Head->Next = Head->Prev = Head;
}

void In_Container(Container* Head, ifstream& ifst) {
    Container* Inserted, * Curr;
    Curr = Inserted = NULL;
    int Len = 0;

    while (!ifst.eof()) {
        Inserted = new Container();
        if ((Inserted->Cont = In_Matrix(ifst))) {
            if (!Len) {
                Head->Cont = Inserted->Cont;
            }
            else {
                Curr = Head->Next;
                Head->Next = Inserted;
                Inserted->Next = Curr;
                Inserted->Prev = Head;
                Curr->Prev = Inserted;
                Head = Inserted;
            }

            Len++;
        }
    }

    Head = Head->Next;

    for (int i = 0; i < Len; i++) {
        Head->Len = Len;
        Head = Head->Next;
    }
}

void Out_Container(Container* Head, ofstream& ofst) {
    ofst << "Container contains " << Head->Len
        << " elements." << endl << endl;

    Container* Temp = Head;

    for (int i = 0; i < Head->Len; i++) {
        ofst << i << ": ";
        Out_Matrix(Temp->Cont, ofst);
        ofst << endl;
        Temp = Temp->Next;
    }
}

void Clear_Container(Container* Head) {
    for (int i = 0; i < Head->Len; i++) {
        free(Head->Cont);
        Head->Len = 0; 
        Head = Head->Next; 
    }
}

void Out_Only_Two_Dim(Container* Head, ofstream& ofst) {
    ofst << "Only Two Dimensional arrays." << endl << endl;

    Container* Temp = Head;

    for (int i = 0; i < Head->Len; i++) {
        if (Temp->Cont->K == TWO_DIMENSIONAL_ARRAY) { //Проверка того, что матрица - обычный думерный массив
            ofst << i << ": ";
            Out_Matrix(Temp->Cont, ofst);
            ofst << endl;
        }

        Temp = Temp->Next;
    }
}

Matrix* In_Matrix(ifstream& ifst) {
    Matrix* M = NULL; //Создаем указатель на матрицу
    int K;

    ifst >> K; //Считываем идентификатор матрицы

    if (K == 1) {
        M = new Matrix(); //Выделяем память под матрицу
        M->K = TWO_DIMENSIONAL_ARRAY; //Записываем тип матрицы

        ifst >> M->N; //Считываем размерность матрицы

        M->Obj = In_Two_dimensional_array(M->N, ifst); //Считываем матрицу
    }
    else if (K == 2) {
        M = new Matrix(); //Выделяем память под матрицу
        M->K = DIAGONAL_MATRIX; //Записываем тип матрицы

        ifst >> M->N; //Считываем размерность матрицы

        M->Obj = In_Diagonal_matrix(M->N, ifst); //Считываем матрицу
    }
    else {
        return 0;
    }

    return M;
}

void Out_Matrix(Matrix* M, ofstream& ofst) {
    if (M->K == TWO_DIMENSIONAL_ARRAY) {
        Out_Two_dimensional_array(M->N, (Two_dimensional_array*)M->Obj, ofst); //Выводим обычный двумерный массив
    }
    else if (M->K == DIAGONAL_MATRIX) {
        Out_Diagonal_matrix(M->N, (Diagonal_matrix*)M->Obj, ofst); //Выводим диагональную матрицу
    }
    else {
        ofst << "Incorrect element!" << endl;
    }
}

Two_dimensional_array* In_Two_dimensional_array(int N, ifstream& ifst) {
    Two_dimensional_array* T_d_a = new Two_dimensional_array();

    T_d_a->Array = new int* [N]; //Выделение памяти под массив

    for (int i = 0; i < N; i++) {
        T_d_a->Array[i] = new int[N]; //Выделение памяти под массив
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ifst >> T_d_a->Array[i][j]; //Ввод элемента массива
        }
    }

    return T_d_a;
}

void Out_Two_dimensional_array(int N, Two_dimensional_array* T_d_a, ofstream& ofst) {
    ofst << "It's two dimensional matrix with dimension = " << N << endl; //Выводим размерность массива

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ofst << T_d_a->Array[i][j] << " "; //Выводим элементы массива
        }

        ofst << endl;
    }
}

Diagonal_matrix* In_Diagonal_matrix(int N, ifstream& ifst)
{
    Diagonal_matrix* D_m = new Diagonal_matrix();

    D_m->Array = new int[N]; //Выделяем память для диагональной матрицы

    for (int i = 0; i < N; i++) {
        ifst >> D_m->Array[i]; //Записываем новый элемент в матрицу
    }

    return D_m;
}

void Out_Diagonal_matrix(int N, Diagonal_matrix* D_m, ofstream& ofst) {
    ofst << "It's diagonal matrix with dimension = " << N << endl; //Выводим размерность матрицы

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                ofst << D_m->Array[i] << " "; //Выводим элемент матрицы; (i == j) -> только по диагонали
            }
            else {
                ofst << "0 "; //(i != j) -> не диагональ, выводим нули
            }
        }

        ofst << endl;
    }
}