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
    
    cout << "Enter seed for first matrix:";
    cin >> seed;
    
    M1.RandVal(seed);
        
    cout << "Enter seed for second matrix:";
    cin >> seed;
    cout << endl;

    M2.RandVal(seed);
    
    /*
    cin.ignore();
    cin.getline(Line, 100);
    M1.FillMatr(Line);
    cin.getline(Line, 100);
    M2.FillMatr(Line);
    */

    start = clock();
    M3.MatrMulMatr(M1, M2);
    time = clock() - start;
    
    /*
    M1.Print("M1");
    M2.Print("M2");
    M3.Print("M3");
    */
    
    cout << time << endl;
}