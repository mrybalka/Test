#ifndef _PACKING_H_
#define _PACKING_H_

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <typeinfo>

using namespace std;

/*
������:
		x1+x2+x3+...+xn->max
		Ax<=1
		x={0,1}
*/
class Packing_Problem
{
private:
	matrix<bool> A;//������� ����������� ������
	int size_n;//����� ���������� ������
	int size_m;//����� ����������� ������
	int Decimals;//�������� ��� �������� l-�������;
	//-------------------------------
	//�������������� ������� ��� ����������
	matrix<double> matr;
	int res_n;//������� �������
	int res_m;
	//-------------------------------
    struct Block_size//������� �����
	{
		int n_size;
		int m_size;
	};
 	struct Block
	{
		int r;//����� ���������� � ����� ����� �������
		int block_kol;//���������� ������
		Block_size* Blocks;//������ ����� block_kol,�������� ������� ������
		
		/*int n_size;//������� ����������� ������
		int m_size;
		int n_size_last;//������� ���������� �� ������� �����
		int m_size_last;*/
	};
public:
	Block* Matrix_Block_Param;
	
private:
	void Add_Elem_To_Matrix_Block_Param(int n, int m);
	//---------------������ �� �����-----------------------------
	void Read_MIS_From_File(char* Filename);
	void Read_MSP_From_File(char* Filename);
	//---------------����������----------------------------------
	double Round(double v, int decimals);
	void Round_Vect(double* &x);
	//---------------�������� � ���������------------------------
	bool Lexmax(double* x_1,double* x_2,int size);
	bool Lexmax_Vect(/*matrix<double> &matr, */int j, int k);
	bool Lexmax_Vect_with_zero(/*matrix<double> &matr,*/ int j);
	int Num_First_Notzero_Coord(/*matrix<double> &matr,*/ int j);
	//---------��������������� ������� ��� ���������� ������� � �������� ����-----
	void Shuffle_matrix_coloms(int* array_vertex, matrix<bool> matr_component);
	//��������������� ������� ��� ConvertMatrix_to_BlockMatrix()
	//��������������� ������� �������, � ������������ � ������������ ���������
    void Shuffle_matrix_lines_and_fill_mbp(int* array_vertex, matrix<bool> matr_component);	
	//��������������� ������� ��� ConvertMatrix_to_BlockMatrix()
	//��������������� ������ �������, � ������������ � ������������ ���������,
	//����� ����� ���������� �����
    //----------------����---------------------------------------
	bool Check_L_Norm(/*matrix<double> &matr*/);
	void Make_L_Norm(/*matrix<double> &matr*/);
	int Check_L_Opim(/*matrix<double> &matr*/);
	int Select_main_column(/*matrix<double> &matr,*/int main_line);
	void Preobrazovanie_Matrix(/*matrix<double> &matr,*/int p,int q);
	//-----------------------------------------------------------
	bool Check_Int(double* x,double Eps);
	bool Check_Int_LDSM(double* x,double Eps);
	double* LDSM_VSP(int rec,int d, int num, double* x_2,int number_step);
	//��� ������������� ���������� ������������ ����������
	double* LDSM_VSP_BLOCK(int rec,int d, int num, double* x_2,int number_step,int kol_full_enum, bool start_rec=false,bool colzero=false,bool opt_table_inf=false);
	//�������� � ������� ����������
	double* LDSM_VSP_SECOND(int rec,int d, int num, double* x_2,bool* arr_inc,int number_step);
	//��������� ��������� ���������� ������ � ���������� ��������������
	double* LDSM_VSP_FULL(int rec,int d, int num, double* x_2,bool* arr_inc,int number_step, int& row_number);
	int Scal_Proiz(int i, int j);
	//void MatrixA_To_Graph_Incendence(matrix<bool> &GI);

public:
	int* shuffle;
	bool flag_shuffle;
public:
	Packing_Problem();
	//------------------------------------------------------
	Packing_Problem(int n, int m, double p, bool IsZeroColAndRow=false);//���������
	Packing_Problem(int n, int m, double p, int r, int block_size, bool randomy = false);//��������� ������� ������
	Packing_Problem(int k, int kol, double p, int t);
	Packing_Problem(matrix<bool> &matr);
	Packing_Problem(char* Filename,bool MSP,bool Block);//MSP=1 -������ �� ����� ��������� "MSP", ����� �� ����� ��������� "MIS"
	Independent_Set_Problem Get_Equivalent_MIS();
	Independent_Set_Problem* Get_Equivalent_MIS_P();
 	//----------------------------------------------------------------
	void Make_Gams_File(char* Filename);
	//-------------------
	void MatrixA_To_Graph_A(matrix<bool> &GI);
	//-------------------
	void MatrixA_To_Graph_Incendence(matrix<bool> &GI);
	//-------------------
	void Read_MSP_BLOCK_From_File(char* Filename);
	bool Save_MSP_In_File(char* Filename);
	bool Save_MSP_BLOCK_In_File(char* Filename);
	~Packing_Problem(){ if (shuffle!=0) delete [] shuffle; };
	int GetSize_n(){return size_n;}
	int GetSize_m(){return size_m;}
	void Set_Decimals(int d) { Decimals = d;}
	void Set(int i,int j, bool value) {if((i<size_m)&&(i>=0)&&(j<size_n)&&(j>=0)) A[i][j]=value;}
	matrix<bool>* GetMatrix(){return (&A);};
	//-----------------------------------------------------------------
	void Shuffle_Dec();//��������. ������� �� �������� �������
	void Shuffle_Inc();//��������. ������� �� ����������� �������
	void Shuffle_According_Greedy();//� ������ ������ ������� ��������� ������ ����������
	void Undo_Shuffle();//������ ��������. ������� 
	//-----------------------------------------------------------------
	double* LDSM();	//����������� ���� c ������� ��������, ������ ������ ������ ��
	double* LEXMAX_M();//���� ��� ��������� �������, ���� ����.���. �� ���������, ������������� ���������� ���
	double* LEXMAX_M_WITH_INFO(int &row_number);//���� ��� � LEXMAX_M, ���� ��������� ���������� �� ����������� ����������� �������
	int* Complete_Enumeration();//������ ������ ������ ���������
	//-----------------------------------------------------------------
	int* Go_Over_L_Class(int d, int &k, bool start_rec=false, bool colzero=false, bool opt_table_inf=false);
	//�������� � ���� 3 ������, ������������ � ����� �������
	//���������� LDSM,LEXMAX_M_WITH_INFO,LEXMAX_M,LDSM_VSP_FULL
	int* Go_Over_L_Class_Block(int d, int &k , bool start_rec=false, bool colzero=false,bool opt_table_inf=false, int kol_full_enum_block=5, int kol_full_enum_r=0);
	//-----------------------------------------------------------------
	int* Go_Over_L_Class_Standart(int d, int &k); //�������� �������� L-�������,�����������
	int* Go_Over_L_Class_Modified_First(int d, int &k);//� �������������� ������� �� ���. �������
    int* Go_Over_L_Class_Modified_Second(int d, int &k);//� �������������� ������� � ����������� ������
	int* Go_Over_L_Class_Kuz(int d, int &k, int &kol_sol, int &kol_after_update, double* &x_lp, bool start_rec, bool colzero, bool opt_table_inf, int rec_st=0);
    //----------------------------------------------------------
    //----------���������� ����� ������� � �������� ����---------
	void ConvertMatrix_to_BlockMatrix();
	//���� ������ � �������� �, �������� ������� A � ��������� 
	//������� ���������	
};

#endif