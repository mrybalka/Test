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
Задача:
		x1+x2+x3+...+xn->max
		Ax<=1
		x={0,1}
*/
class Packing_Problem
{
private:
	matrix<bool> A;//матрица ограничений задачи
	int size_n;//число переменных задачи
	int size_m;//число ограничений задачи
	int Decimals;//точность для перебора l-классов;
	//-------------------------------
	//дополнительная матрица для пересчетов
	matrix<double> matr;
	int res_n;//размеры ресурса
	int res_m;
	//-------------------------------
    struct Block_size//размеры блока
	{
		int n_size;
		int m_size;
	};
 	struct Block
	{
		int r;//число переменных в левой части матрицы
		int block_kol;//количество блоков
		Block_size* Blocks;//массив длины block_kol,хранящий размеры блоков
		
		/*int n_size;//размеры стандартных блоков
		int m_size;
		int n_size_last;//размеры последнего не полного блока
		int m_size_last;*/
	};
public:
	Block* Matrix_Block_Param;
	
private:
	void Add_Elem_To_Matrix_Block_Param(int n, int m);
	//---------------Чтение из файла-----------------------------
	void Read_MIS_From_File(char* Filename);
	void Read_MSP_From_File(char* Filename);
	//---------------Округление----------------------------------
	double Round(double v, int decimals);
	void Round_Vect(double* &x);
	//---------------Операции с векторами------------------------
	bool Lexmax(double* x_1,double* x_2,int size);
	bool Lexmax_Vect(/*matrix<double> &matr, */int j, int k);
	bool Lexmax_Vect_with_zero(/*matrix<double> &matr,*/ int j);
	int Num_First_Notzero_Coord(/*matrix<double> &matr,*/ int j);
	//---------Вспомагательные функции для приведения матрицы к блочному виду-----
	void Shuffle_matrix_coloms(int* array_vertex, matrix<bool> matr_component);
	//Вспомогательная функция для ConvertMatrix_to_BlockMatrix()
	//Переупорядочить столбцы матрицы, в соответствии с компонентами связности
    void Shuffle_matrix_lines_and_fill_mbp(int* array_vertex, matrix<bool> matr_component);	
	//Вспомогательная функция для ConvertMatrix_to_BlockMatrix()
	//Переупорядочить строки матрицы, в соответствии с компонентами связности,
	//чтобы четко выделялись блоки
    //----------------ЛДСМ---------------------------------------
	bool Check_L_Norm(/*matrix<double> &matr*/);
	void Make_L_Norm(/*matrix<double> &matr*/);
	int Check_L_Opim(/*matrix<double> &matr*/);
	int Select_main_column(/*matrix<double> &matr,*/int main_line);
	void Preobrazovanie_Matrix(/*matrix<double> &matr,*/int p,int q);
	//-----------------------------------------------------------
	bool Check_Int(double* x,double Eps);
	bool Check_Int_LDSM(double* x,double Eps);
	double* LDSM_VSP(int rec,int d, int num, double* x_2,int number_step);
	//при фиксированных переменных оптимизирует оставшиеся
	double* LDSM_VSP_BLOCK(int rec,int d, int num, double* x_2,int number_step,int kol_full_enum, bool start_rec=false,bool colzero=false,bool opt_table_inf=false);
	//работает с блочной структурой
	double* LDSM_VSP_SECOND(int rec,int d, int num, double* x_2,bool* arr_inc,int number_step);
	//реализует зануление переменных вместе с остальными фиксированными
	double* LDSM_VSP_FULL(int rec,int d, int num, double* x_2,bool* arr_inc,int number_step, int& row_number);
	int Scal_Proiz(int i, int j);
	//void MatrixA_To_Graph_Incendence(matrix<bool> &GI);

public:
	int* shuffle;
	bool flag_shuffle;

public:
	Packing_Problem();
	//------------------------------------------------------
	Packing_Problem(int n, int m, double p, bool IsZeroColAndRow=false);//генератор
	Packing_Problem(int n, int m, double p, int r, int block_size, bool randomy = false);//генератор блочных матриц
	Packing_Problem(int k, int kol, double p, int t);
	Packing_Problem(matrix<bool> &matr);
	Packing_Problem(char* Filename,bool MSP,bool Block);//MSP=1 -читаем из файла структуры "MSP", иначе из файла структуры "MIS"
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
	void Shuffle_Dec();//переупор. столбцы по убыванию степени
	void Shuffle_Inc();//переупор. столбцы по возрастанию степени
	void Shuffle_According_Greedy();//в начало ставим столбцы найденные жадным алгоритмом
	void Undo_Shuffle();//отмена переупор. столбцы 
	//-----------------------------------------------------------------
	double* LDSM();	//стандартный ЛДСМ c целевой функцией, просто решает задачу ЛП
	double* LEXMAX_M();//ЛДСМ без целелевой функции, ищет лекс.мах. на множестве, фиксированных переменных нет
	double* LEXMAX_M_WITH_INFO(int &row_number);//тоже что и LEXMAX_M, плюс возвращем информацию об оптимальной симплексной таблице
	int* Complete_Enumeration();//решает задачу полным перебором
	//-----------------------------------------------------------------
	int* Go_Over_L_Class(int d, int &k, bool start_rec=false, bool colzero=false, bool opt_table_inf=false);
	//содержит в себе 3 метода, объедененных в одной функции
	//Использует LDSM,LEXMAX_M_WITH_INFO,LEXMAX_M,LDSM_VSP_FULL
	int* Go_Over_L_Class_Block(int d, int &k , bool start_rec=false, bool colzero=false,bool opt_table_inf=false, int kol_full_enum_block=5, int kol_full_enum_r=0);
	//-----------------------------------------------------------------
	int* Go_Over_L_Class_Standart(int d, int &k); //Алгоритм перебора L-классов,стандартный
	int* Go_Over_L_Class_Modified_First(int d, int &k);//с использованием рекорда по цел. функции
    int* Go_Over_L_Class_Modified_Second(int d, int &k);//с использованием рекорда и инцидентных вершин
	int* Go_Over_L_Class_Kuz(int d, int &k, int &kol_sol, int &kol_after_update, double* &x_lp, bool start_rec, bool colzero, bool opt_table_inf, int rec_st=0);
    //----------------------------------------------------------
    //----------Приведение любой матрицы к блочному виду---------
	void ConvertMatrix_to_BlockMatrix();
	//Есть задача с матрицей А, изменить матрицу A и заполнить 
	//блочную структуру	
};

#endif