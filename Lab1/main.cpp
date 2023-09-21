#include <iostream>
using namespace std;

class RandomNumberGenerator
{
private:
    long int seed;
    long int a;
    long int c;
    long int m;

public:
    RandomNumberGenerator(long int seed) : seed(seed)
    {
        a = 1125;
        c = 6658;
        m = 9395;
    }

    long int getNextRandomNumber()
    {
        seed = (a * seed + c) % m;

        return seed;
    }
};

template <typename T>

class MATRIX
{
private:
    T** M;
    unsigned int str;
    unsigned int col;

public:
    MATRIX()
    {
        str = col = 0;
        M = nullptr;
    }

    
    MATRIX(unsigned int str_new, unsigned int col_new)
    {
        str = str_new;
        col = col_new;

        M = (T**) new T * [str];

        for (int i = 0; i < str; i++)
            M[i] = (T*)new T * [col];

        for (int i = 0; i < str; i++)
            for (int j = 0; j < col; j++)
                M[i][j] = 0;
    }
    
    void MatrixResize(unsigned int str_new, unsigned int col_new)
    {
        str = str_new;
        col = col_new;

        M = (T**) new T * [str];

        for (int i = 0; i < str; i++)
            M[i] = (T*)new T * [col];

        for (int i = 0; i < str; i++)
            for (int j = 0; j < col; j++)
                M[i][j] = 0;
    }

    T GetMij(unsigned int i, unsigned int j)
    {
        if ((i > str) || (j > col))
            return 0;

        if ((str > 0) && (col > 0))
            return M[i][j];
        else
            return 0;
    }

    void SetMij(unsigned int i, unsigned int j, T value)
    {
        if ((i < 0) || (i >= str))
            return;

        if ((j < 0) || (j >= col))
            return;

        M[i][j] = value;
    }

    void Print(const char* MatrName)
    {
        cout << "Matrix: " << MatrName << endl;

        for (int i = 0; i < str; i++)
        {
            for (int j = 0; j < col; j++)
                cout << M[i][j] << "\t";

            cout << endl;
        }

        cout << "---------------------" << endl;
    }

    void FillMatr(char* Line)
    {
        unsigned int pnt = 0;
        long int tmp = 0;
        int p = 0, cnt = 0;
        
        for (int i = 0; i < str; i++)
            for (int j = 0; j < col; j++)
            {
                tmp = 0;

                if ((cnt < str * col) && (p == 0))
                {
                    while (Line[pnt] != ' ')
                    {
                        if (Line[pnt] == '\0')
                        {
                            p = 1;
                            break;
                        }

                        tmp = tmp * 10 + (static_cast<long int>(Line[pnt]) - 48);
                        pnt++;
                    }
                    pnt++;
                    cnt++;
                }

                M[i][j] = tmp;
            }
    }

    void MatrPlusMatr(MATRIX& M1, MATRIX& M2)
    {
        if ((M1.str != M2.str) || (M1.col != M2.col) || (col != M1.col) || (str != M1.str))
        {
            cout << "MatrMinusMatr: Incorret matix sizes" << endl;
            return;
        }

        for (int i = 0; i < str; i++)
            for (int j = 0; j < col; j++)
                M[i][j] = M1.GetMij(i, j) + M2.GetMij(i, j);
    }

    void MatrMinusMatr(MATRIX& M1, MATRIX& M2)
    {
        if ((M1.str != M2.str) || (M1.col != M2.col) || (col != M1.col) || (str != M1.str))
        {
            cout << "MatrMinusMatr: Incorret matix sizes" << endl;
            return;
        }

        for (int i = 0; i < str; i++)
            for (int j = 0; j < col; j++)
                M[i][j] = M1.GetMij(i, j) - M2.GetMij(i, j);
    }

    void MatrMulVal(T value)
    {
        for (int i = 0; i < str; i++)
            for (int j = 0; j < col; j++)
                M[i][j] *= value;
    }

    void ColMulVal(MATRIX& M1, T value, unsigned int set_col)
    {
        for (int i = 0; i < M1.str; i++)
            M[i][0] += M1.GetMij(i, set_col) * value;
    }

    void MatrMulMatr(MATRIX& M1, MATRIX& M2)
    {
        if ((M1.col != M2.str) || (str != M1.str) || (col != M2.col))
        {
            cout << "MatrMulMatr: Incorrect matrix sizes" << endl;
            return;
        }

        MATRIX<long int> tmp(M1.str, 1);
        
        for (int j = 0; j < col; j++)
        {
            for (int i = 0; i < M1.str; i++)
                tmp.SetMij(i, 0, 0);

            for (int k = 0; k < M1.col; k++)
                tmp.ColMulVal(M1, M2.GetMij(k, j), k);

            for (int i = 0; i < M1.str; i++)
                M[i][j] = tmp.GetMij(i, 0);
        }
    }

    void SubMatr(MATRIX& M1, unsigned int str_new, unsigned int col_new)
    {
        if ((str > str_new) || (col > col_new) || (str_new == 0) || (col_new == 0))
        {
            cout << "SubMatr: Incorrect sizes" << endl;
            return;
        }

        if (col > 0)
            for (int i = 0; i < str; i++)
                delete[] M[i];

        if (str > 0)
            delete[] M;

        str = str_new;
        col = col_new;

        M = (T**) new T * [str];
        for (int i = 0; i < str; i++)
            M[i] = (T*) new T[col];

        for (int i = 0; i < str; i++)
            for (int j = 0; j < col; j++)
                M[i][j] = M1.GetMij(i, j);
    }

    void RandVal(long int seed)
    {
        RandomNumberGenerator rng(seed);

        for (int i = 0; i < str; i++)
            for (int j = 0; j < col; j++)
                M[i][j] = rng.getNextRandomNumber();
    }

    ~MATRIX()
    {
        if (col > 0)
            for (int i = 0; i < str; i++)
                delete[] M[i];

        if (str > 0)
            delete[] M;
    }
};

void main()
{
    unsigned int str1, col1, str2, col2;
    long int seed;
    unsigned int start, time;
    char Line[100];
    
    cout << "Enter first matrix size: ";
    cin >> str1 >> col1;
    cout << "Enter second matrix size:";
    cin >> str2 >> col2;

    MATRIX<long int> M1(str1, col1);
    MATRIX<long int> M2(str2, col2);
    MATRIX<long int> M3(str1, col2);
    
    /*
    cout << "Enter seed for first matrix:";
    cin >> seed;
    
    M1.RandVal(seed);
        
    cout << "Enter seed for second matrix:";
    cin >> seed;
    cout << endl;

    M2.RandVal(seed);
    
    
    cin.ignore();
    cin.getline(Line, 100);
    M1.FillMatr(Line);
    cin.getline(Line, 100);
    M2.FillMatr(Line);
    

    start = clock();
    M3.MatrMulMatr(M1, M2);
    time = clock() - start;
    
    
    M1.Print("M1");
    M2.Print("M2");
    M3.Print("M3");
    
    
    cout << time << endl;
    */
    /*
    int key;
    while (true)
    {
        cout << endl;
        cout << "0 - Exit" << endl << "1 - Fill matrix by random value" << endl << "2 - Fill matrix by your value" << endl;
        cout << "3 - Matrix resize" << endl << "4 - Matrix plus matrix" << endl << "5 - Matrix minus matrix" << endl;
        cout << "6 - Matrix multiply by value" << endl << "7 - Matrix multiply by matrix" << endl << "8 - Submatix" << endl << "9 - Print matrix" << endl;
        cout << "Enter the action: ";
        cin >> key;
        cout << endl;

        switch (key)
        {
        case 0:
            return;
            break;
        case 1:
            int key_random_fill;
            
            cout << "0 - Return" << endl << "1 - First matrix" << endl << "2 - Second matrix" << endl;
            cout << "Enter the action: ";
            cin >> key_random_fill;
            cout << endl;

            switch (key_random_fill)
            {
            case 0:
                break;
            case 1:
                cout << "Enter seed for first matrix: ";
                cin >> seed;
                M1.RandVal(seed);
                break;
            case 2:
                cout << "Enter seed for second matrix: ";
                cin >> seed;
                M2.RandVal(seed);
                break;
            default:
                cout << "Incorrect action number" << endl;
                break;
            }
            break;
        case 2:
            int key_line_fill;

            cout << "0 - Return" << endl << "1 - First matrix" << endl << "2 - Second matrix" << endl;
            cout << "Enter the action: ";
            cin >> key_line_fill;
            cout << endl;

            switch (key_line_fill)
            {
            case 0:
                break;
            case 1:
                cout << "Enter values in line for first matrix: ";
                cin.ignore();
                cin.getline(Line, 100);
                M1.FillMatr(Line);
                break;
            case 2:
                cout << "Enter values in line for second matrix: ";
                cin.ignore();
                cin.getline(Line, 100);
                M2.FillMatr(Line);
                break;
            default:
                cout << "Incorrect action number" << endl;
                break;
            }
            break;
        case 3:
            int key_resize;

            cout << "0 - Return" << endl << "1 - First matrix" << endl << "2 - Second matrix" << endl;
            cout << "Enter the action: ";
            cin >> key_resize;
            cout << endl;

            switch (key_resize)
            {
            case 0:
                break;
            case 1:
                cout << "Enter new sizes for first matrix: ";
                cin >> str1 >> col1;
                M1.MatrixResize(str1, col1);
                break;
            case 2:
                cout << "Enter new sizes for second matrix: ";
                cin >> str2 >> col2;
                M2.MatrixResize(str2, col2);
                break;
            default:
                cout << "Incorrect action number" << endl;
                break;
            }
            break;
        case 4:
            M3.MatrixResize(str1, col2);
            M3.MatrPlusMatr(M1, M2);
            break;
        case 5:
            M3.MatrixResize(str1, col2);
            M3.MatrMinusMatr(M1, M2);
            break;
        case 6:
            int key_val_mul;
            long int value;

            cout << "0 - Return" << endl << "1 - First matrix" << endl << "2 - Second matrix" << endl;
            cout << "Enter the action: ";
            cin >> key_val_mul;
            cout << endl;

            switch (key_val_mul)
            {
            case 0:
                break;
            case 1:
                cout << "Enter value: ";
                cin >> value;
                M1.MatrMulVal(value);
                break;
            case 2:
                cout << "Enter value: ";
                cin >> value;
                M2.MatrMulVal(value);
                break;
            default:
                cout << "Incorrect action number" << endl;
                break;
            }
            break;
        case 9:
            int key_print;

            cout << "0 - Return" << endl << "1 - Print first matrix" << endl << "2 - Print second matrix" << endl << "3 - Print result matrix" << endl << "4 - Print all matrix" << endl;
            cout << "Enter the action: ";
            cin >> key_print;
            cout << endl;

            switch (key_print)
            {
            case 0:
                break;
            case 1:
                M1.Print("M1");
                break;
            case 2:
                M2.Print("M2");
                break;
            case 3:
                M3.Print("M3");
                break;
            case 4:
                M1.Print("M1");
                M2.Print("M2");
                M3.Print("M3");
                break;
            default:
                cout << "Incorrect action number" << endl;
                break;
            }
            break;
            break;
        default:
            cout << "Incorrect action number" << endl;
            break;
        }
    }*/
}