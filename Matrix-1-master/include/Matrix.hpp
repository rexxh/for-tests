#ifndef Matrix_hpp
#define Matrix_hpp

#pragma once
#include <fstream>
#include <iostream>

using namespace std;

ofstream fout;
ifstream fin;

template <typename T>
class Matrix;

template <typename T>
std::ostream & operator<<(std::ostream & output, const Matrix <T> & matrix)
{
	for (unsigned int i = 0; i < matrix.stroki; ++i) {
		output << std::endl;
		for (unsigned int j = 0; j < matrix.stolbs; ++j) {
			output << matrix.e[i][j] << "\t";
		}
	}

	return output;
}

template <typename T>
std::istream & operator>>(std::istream & input, Matrix <T> & matrix)
{
	for (unsigned int i = 0; i < matrix.stroki; ++i) {
		for (unsigned int j = 0; j < matrix.stolbs; ++j) {
			if (!(input >> matrix.e[i][j])) {
				throw "exception in fill matrix";
			}
		}
	}

	return input;
}

template <typename T>
class Matrix
{
	int stroki;
	int stolbs;
	T **e;
	
public:
	friend std::ostream & operator<< <>(std::ostream & output, const Matrix &);
	friend std::istream & operator>> <>(std::istream & input, Matrix &);

	Matrix() : stroki(0), stolbs(0), e(nullptr) {};
	Matrix(int n, int m) : stroki(n), stolbs(m)
	{
		e = new T*[n];
		for (int i = 0; i < n; i++)
			e[i] = new T[m];
	};
	Matrix(const Matrix &M) : stroki(M.stroki), stolbs(M.stolbs)
	{ //Конструктор копирования
		e = new T*[stroki];
		for (int i = 0; i < stroki; i++)
		{
			e[i] = new T[stolbs];
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
	{ //Запись в файл
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
	{ //Вывод на экран
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
	{ //Оператор сложения 2ух матриц
		Matrix M3(M2.stroki, M2.stolbs);
		for (int i = 0; i < M2.stroki; i++)
		for (int j = 0; j < M2.stolbs; j++)
			M3.e[i][j] = e[i][j] + M2.e[i][j];
		cout << "Матрица 1 + Матрица 2=\n"; M3.print();
		return M3;
	};

	Matrix operator * ( const Matrix &M2)
	{ //Оператор умножения 2ух матриц
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
		cout << "Матрица 1 * Матрица 2  =\n"; M3.print();
		return M3;
	}

	T * operator [] (int k)
	{
		double* stroka = new double[stolbs];
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

	void filltest(char *path)
	{
		char* number;
		fin.open(path);
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				fin >> e[i][j];
				cout << e[i][j] << " ";
			}
			cout << endl;
		}
	}

	
};

#endif;
