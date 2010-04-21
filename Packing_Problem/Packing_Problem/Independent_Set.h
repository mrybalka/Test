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
	int m; //���������� �����
	matrix<bool> Graph;//������� ����������� �����
	//------------------------------------------------		
	    struct A
		{
		int Number;
		bool zapret;//0-if vertex is not in independent set,so we can use it
					//1-if vertex is not free
		};

		int* Answer;//������ � ������� �������������(������������ �� �����) ������� ���.���.��-��
		//� ������� ��������� ������ ������ � �����, ������� ������ � ���.����.
		int* Solution;//������ �������, solution[0]-������� �������, �� ���� ���������� 
		//������ � ���.���.����., solution[i]=0 ��� 1, ������ �� ������� � ������� i
		//� ��������� ����.���.��������, ������ ������� n+1
		A* Vertex_Graph; // ������ �������� - (�������, ���������/��������)
	//-------------------------------------------------
    double* probability;	
	//-------------------------------------------------
		
private:
	    void Read_Graph_From_File(matrix<bool> &matr, char* FileName,int &n);    
	    void Read_Graph_A_From_File(matrix<bool> &Graph_A,char* FileName,int &n, int &m);
		void Convert_Graph_To_Graph_A(matrix<bool> &G, matrix<bool> &G_A);
		//-----------------��������������� ��������� ������� ���������-------
		int Function ();//����� ������� ����������� �������
		int * Vertex_Min_Incedence(int &length);//���������� ������ ������ � ��� �����, ����������� ������� ���.�������
		void Add_Elem (int Number);
		void Update_Zapret(int Number);
		bool Stop_Criteria();
		void Sort_Answer();
		bool Check_Result(int k, matrix<bool> matr);
		//---------------��������������� ��������� �������������� ���������---
		void Update_Probability(int len_limit);
		//----------��������������� ��������� ���������� ��������� ���������---
		int* FindPath(int NUM_VERTICES, matrix<int> c_f, matrix<int> c, matrix<int> &f, int source, int target); 
		int* MaxFlow(/*matrix<bool> org_graph,*/ int NUM_VERTICES, matrix<int> c, int source, int target); 
		int* find_local_connectivity(/*matrix<bool> org_graph, */matrix<int> c, /*int n_, */int s2, int t1);
		int len(int* _array, int n);
		int find_connected_components (matrix<bool> g, int n);
		matrix<bool> delete_vertex_from_graph(matrix<bool> graph, int n, int* vertex_connectivity);
		matrix<bool> evristic_algorithm(int count_vertex_in_block, bool* &common_cols);
public:
	    matrix<bool> Graph_A;
public:
		//---------------------------------
	    Independent_Set_Problem (){}
	    Independent_Set_Problem(char* FileName);//��������� �� ���� ����� ��� MIS
		Independent_Set_Problem(matrix<bool> &matr);//����������� �� ������� ����������
		Independent_Set_Problem(int n,/*int m,*/ double p);//��������� ������!
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
		//Packing_Problem* Get_Equivalent_MSP();//���������� ����������� ��-�� ������������ ������������������ �������������� ������
		//---------------------------------
		void Print_Answer();
		int* Greedy_Algorithm();//������ ��������-������ ������ ����� ������ � MIS
		//����������� ������������� ��������!
		int* Probability_Algorithm(int number_iteration, int len_limit=16);
        
		//------------����� ��������� ��������� �����--------------
		int* find_vertex_connectivity();
		//���������� ����� ������, ������� ����� ������� � �����, ����� �� �������� ���� �������
		matrix<bool> del_vertex_and_find_components(int* vertex_connectivity);
		//���������� �������, � ������� ������ ��� ���������� ���������,
		//�������� ������ ��� ������ ������ �������� � ��� ����������
};

#endif