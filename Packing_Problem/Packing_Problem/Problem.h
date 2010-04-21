#ifndef _L_CLASS_DEF_H_
#define _L_CLASS_DEF_H_

#include "stdafx.h"

/*
   Задача ЦЛП
      f(x)=(c,x)
       Ax<=B;
	   x>=0; 
	  x-целый 
*/

class Problem
{
private:
	matrix<int> A;//матрица ограничений задачи
	int* B;//массив правых частей
	int* C;//коэфициэнты целевой функции
	int size_n;//число переменных задачи
	int size_m;//число ограничений задачи
	int Decimals;//точность для перебора l-классов;

private:
	double Round(double v, int decimals);
	void Round_Vect(double* &x);

	//-------------------------операции с векторами-----------
	bool Lexmax(double* x_1,double* x_2,int size);
	bool Lexmax_Vect(matrix<double> &matr, int j, int k);
	bool Lexmax_Vect_with_zero(matrix<double> &matr, int j);

	//void Minus(double* x_1, double* x_2,int size);
	//void Del_const(double* x, double c,int size);
	//double* cut_col_j(matrix<double> a, int j);
	//void put_col_j(matrix<double> &a, int j, double* x);
	//-------------------------------------ЛДСМ----------------
	bool Check_L_Norm(matrix<double> &matr);
	void Make_L_Norm(matrix<double> &matr);
	int Check_L_Opim(matrix<double> &matr);
	int Select_main_column(matrix<double> &matr,int main_line);
	void Preobrazovanie_Matrix(matrix<double> &matr,int p,int q);
	//---------------------------------------------------------
	bool Check_Int(double* x,double Eps);
	double* LDSM_VSP(int rec,int d, int num, double* x_2,int number_step);
		
public:
	Problem();
	//Problem(char* Filename); 
	~Problem(){};
	int GetSize_n(){return size_n;}
	int GetSize_m(){return size_m;}
	void Set_Decimals(int d) { Decimals = d;}
	matrix<int>* Get_A(){return (&A);}
	int* Get_B(){return B;}
	int* Get_C(){return C;}
	double* LEXMAX_M();//лдсм без целев.
	double* LDSM();//стандартный ЛДСМ, может быть использован в 1м алгоритме Гомори
	int* Go_Over_L_Class_Standart(int d,int &k);//Алгоритм перебора L-классов,стандартный

};

#endif