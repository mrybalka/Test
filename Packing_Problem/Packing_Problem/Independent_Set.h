#ifndef _EVRISTIKA_H_
#define _EVRISTIKA_H_

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <typeinfo>

using namespace std;

class Independent_Set_Problem
{
private:
	int n; //number of vertex
	int m; //количество ребер
	matrix<bool> Graph;//матрица инцинденций графа
	//------------------------------------------------		
	    struct A
		{
		int Number;
		bool zapret;//0-if vertex is not in independent set,so we can use it
					//1-if vertex is not free
		};

		int* Answer;//массив в который записываеться(добавляеться по одной) вершины мак.нез.мн-ва
		//в массиве храняться номера вершин в графе, которые входят в нез.множ.
		int* Solution;//вектор решения, solution[0]-целевая функция, то есть количество 
		//вершин в мак.нез.множ., solution[i]=0 или 1, входит ли вершина с номером i
		//в найденное макс.нез.множетво, размер вектора n+1
		A* Vertex_Graph; // массив структур - (вершина, запрещена/свободна)
	//-------------------------------------------------
    double* probability;	
	//-------------------------------------------------
		
private:
	    void Read_Graph_From_File(matrix<bool> &matr, char* FileName,int &n);    
	    void Read_Graph_A_From_File(matrix<bool> &Graph_A,char* FileName,int &n, int &m);
		void Convert_Graph_To_Graph_A(matrix<bool> &G, matrix<bool> &G_A);
		//-----------------Вспомогательные процедуры жадного алгоритма-------
		int Function ();//номер вершины минимальной степени
		int * Vertex_Min_Incedence(int &length);//возвращает массив вершин и его длину, инцедентных вершине мин.степени
		void Add_Elem (int Number);
		void Update_Zapret(int Number);
		bool Stop_Criteria();
		void Sort_Answer();
		bool Check_Result(int k, matrix<bool> matr);
		//---------------Вспомогательные процедуры вероятностного алгоритма---
		void Update_Probability(int len_limit);
		//----------Вспомогательные процедуры нахождения вершинной связности---
		int* FindPath(int NUM_VERTICES, matrix<int> c_f, matrix<int> c, matrix<int> &f, int source, int target); 
		int* MaxFlow(/*matrix<bool> org_graph,*/ int NUM_VERTICES, matrix<int> c, int source, int target); 
		int* find_local_connectivity(/*matrix<bool> org_graph, */matrix<int> c, /*int n_, */int s2, int t1);
		int len(int* _array, int n);
		int find_connected_components (matrix<bool> g, int n);
		matrix<bool> delete_vertex_from_graph(matrix<bool> graph, int n, int* vertex_connectivity);
		//----------Вспомогательная функция для нахождения точеки сочленения----
		bool* used;
		int timer;
		int* tin;
		int* fup;
    	void dfs (int v, int p = -1);
		//----------------------------------------------------------------------
		
public:
	    matrix<bool> Graph_A;
public:
		//---------------------------------
	    Independent_Set_Problem (){}
	    Independent_Set_Problem(char* FileName);//считывает из спец файла для MIS
		Independent_Set_Problem(matrix<bool> &matr);//конструктор по матрице инциденций
		Independent_Set_Problem(int n,/*int m,*/ double p);//генератор задачи!
		bool Save_MIS_In_File(char* Filename);
		~Independent_Set_Problem(){}
        //---------------------------------
		void Make_Gams_File(char* Filename);
		int Select_Vertex();
		int GetSize_n(){return n;}
		int GetSize_m(){return m;}
		matrix<bool>* GetGraph(){return (&Graph);}
		bool Get(int i,int j ) {return Graph[i][j];}
		//---------------------------------
		//Packing_Problem* Get_Equivalent_MSP();//невозможно реализовать из-за определенной последовательности компилирования файлов
		//---------------------------------
		void Print_Answer();
		int* Greedy_Algorithm();//Жадный алгоритм-нижняя оценка числа вершин в MIS
		//реализовать вероятностный алгоритм!
		int* Probability_Algorithm(int number_iteration, int len_limit=16);
        
		//------------поиск вершинной связности графа--------------
		int* find_vertex_connectivity();
		//возвращает масив вершин, которые нужно удалить в графе, чтобы он перестал быть связным
		matrix<bool> del_vertex_and_find_components(int* vertex_connectivity);
		//возвращаем матрицу, в которой строка это компонента связности,
		//элементы строки это номера вершин входящих в эту компоненту
		matrix<bool> evristic_algorithm(int count_vertex_in_block, int* &common_cols);
        //------------------------------------------------------------
		int* common_cols;		
		void find_articulation_point();

};

#endif