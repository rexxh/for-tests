#ifndef Matrix_hpp
#define Matrix_hpp

#pragma once
#include <fstream>
#include <iostream>

using namespace std;

ofstream fout;
ifstream fin;

template <typename T>
class Matrix
{
	int stroki;
	int stolbs;
	T **e;
	void fill(T **e);
public:
	Matrix() : stroki(0), stolbs(0), e(nullptr) {};
	Matrix(int n, int m) : stroki(n), stolbs(m)
	{
		e = new T*[n];
		for (int i = 0; i < n; i++)
			e[i] = new T[m];
	};
	Matrix(const Matrix &M) : stroki(M.stroki), stolbs(M.stolbs)
	{ //Êîíñòðóêòîð êîïèðîâàíèÿ
		e = new T*[stroki];
		for (int i = 0; i < stroki; i++)
		{
			e[i] = new T [stolbs];
		}
		for (int i = 0; i < stroki; i++)
		{
			for (int j = 0; j < stolbs; j++)
			{
				e[i][j] = M.e[i][j];
			}
		}

	};
	~Matrix(){
		{
			if (e != nullptr)
			{
				for (int i = 0; i < stroki; i++)
				{
					delete[] e[i];
				}
				delete[] e;
			}
		}
	};
	void Set(char *path)
	{ //Çàïèñü â ôàéë
		fout.open(path);
		for (int i = 0; i < stroki; i++)
		{
			for (int j = 0; j < stolbs; j++)
			{
				cin >> e[i][j];
				fout << " " << e[i][j];
			}
			fout << "\n";
		}
		fout.close();
	};
	int STR() {  return stroki; };
	int STOLB(){ return stolbs; };
	int print()
	{ //Âûâîä íà ýêðàí
		for (int i = 0; i < stroki; i++)
		{
			for (int j = 0; j < stolbs; j++)
			{
				cout << e[i][j] << " ";
			}
			cout << "\n";
		}
		return 0;
	};

	Matrix operator + ( const Matrix &M2)
	{ //Îïåðàòîð ñëîæåíèÿ 2óõ ìàòðèö
		Matrix M3(M2.stroki, M2.stolbs);
		for (int i = 0; i < M2.stroki; i++)
		for (int j = 0; j < M2.stolbs; j++)
			M3.e[i][j] = e[i][j] + M2.e[i][j];
		cout << "Ìàòðèöà 1 + Ìàòðèöà 2=\n"; M3.print();
		return M3;
	};

	Matrix operator * ( const Matrix &M2)
	{ //Îïåðàòîð óìíîæåíèÿ 2óõ ìàòðèö
		Matrix M3(stroki, M2.stolbs);
		int k = 0;
		for (int i = 0; i < stroki; i++)
		{
			for (int j = 0; j < M2.stolbs; j++)
			{
				M3.e[i][j] = 0;
				for (int k = 0; k <= M2.stolbs; k++)
				{
					M3.e[i][j] += (e[i][k] * M2.e[k][j]);
				}
			}
		}
		cout << "Ìàòðèöà 1 * Ìàòðèöà 2  =\n"; M3.print();
		return M3;
	}

	T * operator [] (int k)
	{
		T* stroka = new T [stolbs];
		for (int j = 0; j < stolbs; j++)
		{
			stroka[j] = e[k - 1][j];
		}
		return stroka;
	};
	
	void swap(Matrix & M2) 
    {
        // обмен всех членов с M2
        std::swap(stroki, M2.stroki);
        std::swap(stolbs, M2.stolbs);
        std::swap(e, M2.e);
    };

	Matrix & operator = (Matrix M2)
	{
        // обмен this с M2
	  swap(M2);
          return *this;
          //M2 уничтожается, освобождая память
	}

};

template <typename T>
void Matrix<T>::fill(T **e)
{
    e = new T *[stroki];
    for (unsigned int i = 0; i < stroki; ++i) {
        e[i] = new T[stolbs];
        for (unsigned int j = 0; j < stolbs; ++j) {
            e[i][j] = e ? e[i][j] : 0;
        }
    }
}
