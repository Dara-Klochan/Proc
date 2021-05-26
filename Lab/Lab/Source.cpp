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
        ofst << "Sum of matrix elements = " << Sum_Matrix(Temp->Cont);
        ofst << endl << endl;
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

void Sort(Container* Head) {
    if (Head->Len > 1) {
        Container* First = Head;
        Container* Second = Head->Next;

        Container* Temp = new Container;

        for (int i = 0; i < Head->Len - 1; i++) {
            for (int j = 0; j < Head->Len - i - 1; j++) {
                if (Compare(First->Cont, Second->Cont)) {
                    Temp->Cont = First->Cont;
                    First->Cont = Second->Cont;
                    Second->Cont = Temp->Cont;
                }

                Second = Second->Next;
            }

            First = First->Next;
            Second = First->Next;
        }
    }
}

Matrix* In_Matrix(ifstream& ifst) {
    Matrix* M = NULL; //Создаем указатель на матрицу
    int K;

    ifst >> K; //Считываем идентификатор матрицы

    if (K == 1) {
        M = new Matrix(); //Выделяем память под матрицу
        M->K = TWO_DIMENSIONAL_ARRAY; //Записываем тип матрицы

        int K_Out = 0;

        ifst >> K_Out; //Считываем способ вывода матрицы

        if (K_Out == 1) {
            M->K_O = BY_LINE;
        }
        else if (K_Out == 2) {
            M->K_O = BY_COLUMN;
        }
        else if (K_Out == 3) {
            M->K_O = ONE_DIMENSIONAL;
        }

        ifst >> M->N; //Считываем размерность матрицы

        M->Obj = In_Two_dimensional_array(M->N, ifst); //Считываем матрицу
    }
    else if (K == 2) {
        M = new Matrix(); //Выделяем память под матрицу
        M->K = DIAGONAL_MATRIX; //Записываем тип матрицы

        int K_Out = 0;

        ifst >> K_Out; //Считываем способ вывода матрицы

        if (K_Out == 1) {
            M->K_O = BY_LINE;
        }
        else if (K_Out == 2) {
            M->K_O = BY_COLUMN;
        }
        else if (K_Out == 3) {
            M->K_O = ONE_DIMENSIONAL;
        }

        ifst >> M->N; //Считываем размерность матрицы

        M->Obj = In_Diagonal_matrix(M->N, ifst); //Считываем матрицу
    }
    else if (K == 3) {
        M = new Matrix(); //Выделяем память под матрицу
        M->K = TRIANGULAR_MATRIX; //Записываем тип матрицы

        int K_Out = 0;

        ifst >> K_Out; //Считываем способ вывода матрицы

        if (K_Out == 1) {
            M->K_O = BY_LINE;
        }
        else if (K_Out == 2) {
            M->K_O = BY_COLUMN;
        }
        else if (K_Out == 3) {
            M->K_O = ONE_DIMENSIONAL;
        }

        ifst >> M->N; //Считываем размерность матрицы

        M->Obj = In_Triangular_matrix(M->N, ifst); //Считываем матрицу
    }
    else {
        return 0;
    }

    return M;
}

void Out_Matrix(Matrix* M, ofstream& ofst) {
    if (M->K == TWO_DIMENSIONAL_ARRAY) {
        Out_Two_dimensional_array(M->N, M->K_O, (Two_dimensional_array*)M->Obj, ofst); //Выводим обычный двумерный массив
    }
    else if (M->K == DIAGONAL_MATRIX) {
        Out_Diagonal_matrix(M->N, M->K_O, (Diagonal_matrix*)M->Obj, ofst); //Выводим диагональную матрицу
    }
    else if (M->K == TRIANGULAR_MATRIX) {
        Out_Triangular_matrix(M->N, M->K_O, (Triangular_matrix*)M->Obj, ofst); //Выводим треугольную матрицу
    }
    else {
        ofst << "Incorrect element!" << endl;
    }
}

int Sum_Matrix(Matrix* M) {
    if (M->K == TWO_DIMENSIONAL_ARRAY) {
        return Sum_Two_dimensional_array(M->N, (Two_dimensional_array*)M->Obj); //Подсчет суммы элементов обычного двумерного массива
    }
    else if (M->K == DIAGONAL_MATRIX) {
        return Sum_Diagonal_matrix(M->N, (Diagonal_matrix*)M->Obj); //Подсчет суммы элементов диагональной матрицы
    }
    else if (M->K == TRIANGULAR_MATRIX) {
        return Sum_Triangular_matrix(M->N, (Triangular_matrix*)M->Obj); //Подсчет суммы элементов треугольной матрицы
    }
    else {
        return -1;
    }
}

bool Compare(Matrix* First, Matrix* Second) {
    return Sum_Matrix(First) > Sum_Matrix(Second);
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

void Out_Two_dimensional_array(int N, Key_Out K_O, Two_dimensional_array* T_d_a, ofstream& ofst) {
    ofst << "It's two dimensional matrix with dimension = " << N << endl; //Выводим размерность массива

    if (K_O == BY_LINE) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                ofst << T_d_a->Array[i][j] << " ";
            }

            ofst << endl;
        }
    }
    else if (K_O == BY_COLUMN) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                ofst << T_d_a->Array[j][i] << " ";
            }

            ofst << endl;
        }
    }
    else if (K_O == ONE_DIMENSIONAL) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                ofst << T_d_a->Array[i][j] << " ";
            }
        }

        ofst << endl;
    }
}

int Sum_Two_dimensional_array(int N, Two_dimensional_array* T_d_a) {
    int Sum = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Sum += T_d_a->Array[i][j];
        }
    }

    return Sum;
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

void Out_Diagonal_matrix(int N, Key_Out K_O, Diagonal_matrix* D_m, ofstream& ofst) {
    ofst << "It's diagonal matrix with dimension = " << N << endl; //Выводим размерность матрицы

    if (K_O == BY_LINE) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) {
                    ofst << D_m->Array[i] << " ";
                }
                else {
                    ofst << "0 ";
                }
            }

            ofst << endl;
        }
    }
    else if (K_O == BY_COLUMN) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) {
                    ofst << D_m->Array[j] << " ";
                }
                else {
                    ofst << "0 ";
                }
            }

            ofst << endl;
        }
    }
    else if (K_O == ONE_DIMENSIONAL) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) {
                    ofst << D_m->Array[i] << " ";
                }
                else {
                    ofst << "0 ";
                }
            }
        }

        ofst << endl;
    }
}

int Sum_Diagonal_matrix(int N, Diagonal_matrix* D_m) {
    int Sum = 0;

    for (int i = 0; i < N; i++) {
        Sum += D_m->Array[i];
    }

    return Sum;
}

Triangular_matrix* In_Triangular_matrix(int N, ifstream& ifst) {
    //Корректируем размер треугольной матрицы
    int Temp_N = N;
    int Array_size = 0;

    while (Temp_N) {
        Array_size += Temp_N;
        Temp_N--;
    }

    Triangular_matrix* T_m = new Triangular_matrix();

    T_m->Array = new int[Array_size];

    for (int i = 0; i < Array_size; i++) {
        ifst >> T_m->Array[i]; //Записываем элементы матрицы
    }

    return T_m;
}

void Out_Triangular_matrix(int N, Key_Out K_O, Triangular_matrix* T_m, ofstream& ofst) {
    ofst << "It's triangular matrix with dimension = " << N << endl;

    int Array_index = 0; //Иднекс для прохода ненулевых элементов матрицы

    int** Temp_array = new int* [N];

    for (int i = 0; i < N; i++) {
        Temp_array[i] = new int[N];
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i >= j) {
                Temp_array[i][j] = T_m->Array[Array_index];
                Array_index++;
            }
            else {
                Temp_array[i][j] = 0;
            }
        }
    }

    if (K_O == BY_LINE) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                ofst << Temp_array[i][j] << " ";
            }

            ofst << endl;
        }
    }
    else if (K_O == BY_COLUMN) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                ofst << Temp_array[j][i] << " ";
            }

            ofst << endl;
        }
    }
    else if (K_O == ONE_DIMENSIONAL) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                ofst << Temp_array[i][j] << " ";
            }
        }

        ofst << endl;
    }
}

int Sum_Triangular_matrix(int N, Triangular_matrix* T_m) {
    int Temp_N = N;
    int Array_size = 0;

    while (Temp_N) {
        Array_size += Temp_N;
        Temp_N--;
    }

    int Sum = 0;

    for (int i = 0; i < Array_size; i++) {
        Sum += T_m->Array[i];
    }

    return Sum;
}
