#ifndef _L_CLASS_DEF_H_
#define _L_CLASS_DEF_H_

#include "stdafx.h"

/*
   ������ ���
      f(x)=(c,x)
       Ax<=B;
	   x>=0; 
	  x-����� 
*/

class Problem
{
private:
	matrix<int> A;//������� ����������� ������
	int* B;//������ ������ ������
	int* C;//����������� ������� �������
	int size_n;//����� ���������� ������
	int size_m;//����� ����������� ������
	int Decimals;//�������� ��� �������� l-�������;

private:
	double Round(double v, int decimals);
	void Round_Vect(double* &x);

	//-------------------------�������� � ���������-----------
	bool Lexmax(double* x_1,double* x_2,int size);
	bool Lexmax_Vect(matrix<double> &matr, int j, int k);
	bool Lexmax_Vect_with_zero(matrix<double> &matr, int j);

	//void Minus(double* x_1, double* x_2,int size);
	//void Del_const(double* x, double c,int size);
	//double* cut_col_j(matrix<double> a, int j);
	//void put_col_j(matrix<double> &a, int j, double* x);
	//-------------------------------------����----------------
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
	double* LEXMAX_M();//���� ��� �����.
	double* LDSM();//����������� ����, ����� ���� ����������� � 1� ��������� ������
	int* Go_Over_L_Class_Standart(int d,int &k);//�������� �������� L-�������,�����������

};

#endif