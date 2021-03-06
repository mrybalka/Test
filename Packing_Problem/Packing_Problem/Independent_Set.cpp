#pragma warning disable
#include "stdafx.h"

char* inttostr(int value)
{
	int len=0;
	int val=value;
	int rest=val%10;
	if (value<10) len++;
	if ((value>=10)&&(value<100)) len=2;
	if ((value>=100)&&(value<1000)) len=3;
	if ((value>=1000)&&(value<10000)) len=4;
    if ((value>=10000)&&(value<100000)) len=5;
	if ((value>=100000)&&(value<1000000)) len=6;


	char* s=new char[len];
	for (int i=0; i<len-1;i++)
	{
		int v=value/((int)(pow(10.0,len-1-i)));
		s[i]=CHAR(48+v);
		value=value-v*(int)pow(10.0,len-1-i);
	}
	s[len-1]=CHAR(48+value%10);
	s[len]='\0';
	return s;
}

//---------���������� ������----------------------------------------------------------
Independent_Set_Problem:: Independent_Set_Problem(char* FileName)
{
  Read_Graph_From_File(Graph,FileName,n);
  Read_Graph_A_From_File(Graph_A,FileName,n,m);
  //cout<<Graph;
  //cout<<Graph_A;

}
Independent_Set_Problem::Independent_Set_Problem(matrix<bool> &matr)
{
  n=matr.ret_h();
  Graph=matr;
  m=0;
	 for(int i=0; i<n; i++)
        for (int j=i+1;j<n;j++)
          if (Graph[i][j]==1) m++;

  Graph_A = matrix<bool>(n,m);
  Convert_Graph_To_Graph_A(Graph,Graph_A);

  /*probability=new double[7];
  //for (int i=0; i<n; i++) probability[i]=(double)1/n;
  probability[0]=0.1;
  probability[1]=0.2;
  probability[2]=0.05;
  probability[3]=0.4;
  probability[4]=0.12;
  probability[5]=0.08;
  probability[6]=0.05;*/
}		
void Independent_Set_Problem::Convert_Graph_To_Graph_A(matrix<bool> &G, matrix<bool> &G_A)
//�������� ������ ������� �������� ������
{
	int i,j;
	int k=0;
    for (i=0; i<n; i++)
	{
		for (j=i+1; j<n; j++)
		{
			if (Graph[i][j] == 1)
			{
				Graph_A[k][i]=1;
				Graph_A[k][j]=1;
                k++; 
			}
	    }
	}
}
Independent_Set_Problem::Independent_Set_Problem(int n,/*int m,*/ double p)
{
	 double r;
     int i,j;
     this->n=n;
     Graph = matrix<bool>(n,n);
     //double p1 = p/n;
	 for(i=0; i<n; i++)
     {
       for (j=i;j<n;j++)
       {
	     if (i==j) Graph[j][i]=1;
		 else {
		 r = (((double) rand()) /(double) RAND_MAX);
		 if (r<p) 
		 {
			 Graph[j][i]=1; Graph[i][j]=1; 
		 }else { Graph[j][i]=0; Graph[i][j]=0;}
		 }
       }
     }
	 
	 for(i=0; i<n; i++)//��������� �� ������� �����
	 { 
		int tmp=0;
		for (j=i+1; j<n; j++)
		   if (Graph[i][j]==1) tmp=1;
		if (tmp==0) 
		{
   		  if ((n-i)!=0) j= (int)(((int) rand()) %(n-i)); 
						else j=0;
		  Graph[i][j+i]=1;
		  Graph[j+i][i]=1;
		}
	}

	 m=0;
	 for(i=0; i<n; i++)
        for (j=i+1;j<n;j++)
          if (Graph[i][j]==1) m++;
			 
	 Graph_A = matrix<bool>(n,m);
	 Convert_Graph_To_Graph_A(Graph,Graph_A);
	 //cout<<Graph<<endl;
	 //cout<<Graph_A;
}

bool Independent_Set_Problem::Save_MIS_In_File(char* Filename)
{
  ofstream OutFile;
  OutFile.open(Filename);
  if (!OutFile) {cerr<<"�� ���� �������"; OutFile.close(); return 0;} 
    else
     {
      OutFile<<"p edge "<<n<<" "<<m<<endl;
      for(int i=0; i<m; i++)
      {
       OutFile<<"e "; 
       for (int j=0;j<n;j++)
       {
       if (Graph_A[i][j]==1) OutFile<<(j+1)<<" "; 
       }
      OutFile<<endl;
      }
    OutFile.close();
    }
 return true;
}
void Independent_Set_Problem::Make_Gams_File(char* Filename)
{
/*$Setglobal m 4
$Setglobal n 4
Sets
i /i1*i%m%/
j /j1*j%n%/
Table a(i,j)
   j1 j2 j3 j4
i1  1  0  1  1
i2  1  1  0  0
i3  0  0  0  1
i4  0  1  0  1;

Variables
z
x(j)
Binary variable x;
Equations
cost
supply(i);
cost.. z=e=sum(j, x(j));
supply(i)..sum(j, a(i,j)*x(j)) =l= 1;
Model packing /all/;
solve packing using mip maximizing z;
display x.l;*/
  ofstream OutFile;
  int len_i=0;
  int len_j=0;
  OutFile.open(Filename);
  if (!OutFile) {cerr<<"�� ���� �������"; OutFile.close();} 
  else
  {
     OutFile<<"$Setglobal m "<<m<<endl;
	 OutFile<<"$Setglobal n "<<n<<endl;
     OutFile<<"Sets"<<endl;
	 OutFile<<"i /i1*i%m%/"<<endl;
     OutFile<<"j /j1*j%n%/"<<endl;
	 OutFile<<"Table a(i,j)"<<endl;
	 
	 if (m<10) len_i++;
	 if ((m>=10)&&(m<100)) len_i=2;
	 if ((m>=100)&&(m<1000)) len_i=3;
	 if ((m>=1000)&&(m<10000)) len_i=4;
	 if ((m>=10000)&&(m<100000)) len_i=5;
	 if ((m>=100000)&&(m<1000000)) len_i=6;
	 if ((m>=1000000)&&(m<10000000)) len_i=7;
	 
	 if (n<10) len_j++;
	 if ((n>=10)&&(n<100)) len_j=2;
	 if ((n>=100)&&(n<1000)) len_j=3;
	 if ((n>=1000)&&(n<10000)) len_j=4;
	 
	 len_i=len_i+2;
	 len_j=len_j+2;
	 
	 for (int k=0; k<len_i; k++) OutFile<<" ";
	 for (int j=0;j<n;j++) 
	 {
		 int par=0;
		 int kol=0;
		 if ((j+1)<10) kol++;
		 if ((j+1>=10)&&(j+1<100)) kol=2;
		 if ((j+1>=100)&&(j+1<1000)) kol=3;
		 if ((j+1>=1000)&&(j+1<10000)) kol=4;
		 OutFile<<"j"<<inttostr(j+1);
		 par=len_j-1-kol;
         for (int k=0; k<par; k++) OutFile<<" ";
	 }
	 OutFile<<endl;
	 
	 for(int i=0; i<m; i++)
	 {
		 int par=0;
		 int kol=0;
		 if ((i+1)<10) kol++;
		 if ((i+1>=10)&&(i+1<100)) kol=2;
		 if ((i+1>=100)&&(i+1<1000)) kol=3;
		 if ((i+1>=1000)&&(i+1<10000)) kol=4;
		 if ((i+1>=10000)&&(i+1<100000)) kol=5;
		 if ((i+1>=100000)&&(i+1<1000000)) kol=6;

		 OutFile<<"i"<<inttostr(i+1);
		 par=len_i-1-kol;
         for (int k=0; k<par; k++) OutFile<<" ";
		 
		 for (int j=0;j<n;j++) 
		 {
			 OutFile<<Graph_A[i][j];
             par=len_j-1;
             for (int k=0; k<par; k++) OutFile<<" ";
		 }
		 OutFile<<endl;
	 }
	 OutFile<<"Variables"<<endl;
	 OutFile<<"z"<<endl;
	 OutFile<<"x(j)"<<endl;
	 OutFile<<"Binary variable x;"<<endl;
	 OutFile<<"Equations"<<endl;
	 OutFile<<"cost"<<endl;
	 OutFile<<"supply(i);"<<endl;
	 OutFile<<"cost.. z=e=sum(j, x(j));"<<endl;
	 OutFile<<"supply(i)..sum(j, a(i,j)*x(j)) =l= 1;"<<endl;
	 OutFile<<"Model packing /all/;"<<endl;
	 OutFile<<"packing.optcr=0;"<<endl;
	 OutFile<<"packing.reslim=3600;"<<endl;
	 OutFile<<"solve packing using mip maximizing z;"<<endl;
	 OutFile<<"display x.l;"<<endl;
	 OutFile<<"display z.l;"<<endl;
	 OutFile<<"display packing.modelstat;"<<endl;
	 OutFile<<"display packing.resusd;"<<endl;
	 OutFile.close();
   }
}
void Independent_Set_Problem::Read_Graph_From_File(matrix<bool> &matr, char* FileName,int &n)
		//��������� ������� �� ����� ������������ ����, � ����������� � ������� ����������� �����
		//��� �����
		/*The graphs are specified in the DIMACS format. For a graph with say 64 nodes and 543 edges, the first line of the file would read: 
		p edge 64 543 

		followed by 543 lines like 
		e 1 2 
		e 1 3 
		e 1 20 
		... 
		indicating that there are edges from node 1 to 2, from node 1 to 3, from node 1 to 20, etc. 
		*/
		{
		ifstream InFile;
		char* str,*str1;
		str = new char[100];
		int Number_Edge,size;
		InFile.open(FileName,ios::_Nocreate);
		if (!InFile) {cerr<<"��� ������ �����!";  InFile.close(); return;} else
		{
			//������ 1 ����� � ������� ������� ������ �������
			//������ 2 ����� � �� ���� ����� ������ ����
			InFile.getline(str,100);
			int i=0;
			str1 =  new char[10];
			while ((int(str[i])<48)||(int(str[i])>57))
			i++;
			int j=0;
			while ((int(str[i])>=48)&&(int(str[i])<=57))
			{ str1[j]=str[i]; j++; i++; }
			str1[j]='\0';
			int k=0;
			while ((int(str1[k])>=48)&&(int(str1[k])<=57)) k++;
			size=0;
			size=str1[k-1]-48;
			for (j=1;j<k;j++) 
			{   
				int deg=1;
				for (int h=1;h<=j;h++) {deg = deg*10;}
				size=size+(str1[k-j-1]-48)*deg;
			} 
			delete[] str1;
			//cout<<size;
			n=size;
			matr = matrix<bool>(size,size);
			for(int l=0;l<size; l++) 
				for(int p=0;p<size; p++) 
				if (l==p) matr[l][p]=1; else matr[l][p]=0;

			while ((int(str[i])<48)||(int(str[i])>57))
			i++;
			j=0;
			str1 =  new char[10];
			while ((int(str[i])>=48)&&(int(str[i])<=57))
			{ str1[j]=str[i]; j++; i++; }
			str1[j]='\0';
			k=0;
			while ((int(str1[k])>=48)&&(int(str1[k])<=57)) k++;
			Number_Edge=0;
			Number_Edge=str1[k-1]-48;
			for (j=1;j<k;j++) 
			{   
				int deg=1;
				for (int h=1;h<=j;h++) {deg = deg*10;}
				Number_Edge=Number_Edge+(str1[k-j-1]-48)*deg;
			} 
            delete[]str1;
		   for ( int l=0; l<Number_Edge;l++)
		   { 
			   //������� 1 ����� 2 ����� � � ������� �������� �� ��� ����� 1
			  InFile.getline(str,100);
			  ////////
			  str1 =  new char[10];
			  for(int l=0;l<10; l++)
			  {
				  str1[l]=' ';
			  }
			  int i=0;
			  while ((int(str[i])<48)||(int(str[i])>57)) i++;
			  int j=0;
			  while ((int(str[i])>=48)&&(int(str[i])<=57))
			  { str1[j]=str[i]; j++; i++; }
			  str1[j]='\0';
			  int k=0;
			  while ((int(str1[k])>=48)&&(int(str1[k])<=57)) k++;
			  int first=0;
			  first=str1[k-1]-48;
			  for (j=1;j<k;j++) 
			  {   
				int deg=1;
				for (int h=1;h<=j;h++) {deg = deg*10;}
				first=first+(str1[k-j-1]-48)*deg;
			 } 
			 delete[] str1;
			  str1 =  new char[10];
			while ((int(str[i])<48)||(int(str[i])>57)) i++;
			j=0;
			for(int l=0;l<10; l++)
			  {
				  str1[l]=' ';
			  }
			while ((int(str[i])>=48)&&(int(str[i])<=57))
			{ str1[j]=str[i]; j++; i++; }
			str1[j]='\0';
			
			k=0;
			while ((int(str1[k])>=48)&&(int(str1[k])<=57)) k++;
			int second=0;
			second=str1[k-1]-48;
			for (j=1;j<k;j++) 
			{   
				int deg=1;
				for (int h=1;h<=j;h++) {deg = deg*10;}
				second=second+(str1[k-j-1]-48)*deg;
			} 
			 /////////
			delete[] str1;
			matr[first-1][second-1]=1;
			matr[second-1][first-1]=1;
		   }
         InFile.close();
		}
		}
void Independent_Set_Problem::Read_Graph_A_From_File(matrix<bool> &Graph_A,char* FileName,int &n, int &m)
{
 //��������� �� ����� ������������ ����,� ������� ������ ��������,��������������� ������ � ������.���.���������
 //��� �����
 /*The graphs are specified in the DIMACS format. For a graph with say 64 nodes and 543 edges, the first line of the file would read: 
	p edge 64 543 
	followed by 543 lines like 
	e 1 2 
	e 1 3 
	e 1 20 
	... 
	indicating that there are edges from node 1 to 2, from node 1 to 3, from node 1 to 20, etc. 
*/
	ifstream InFile;
	char* str,*str1;
	str = new char[100];
	//str1 =  new char[10];
	int Number_Edge,size;
	

	InFile.open(FileName,ios::_Nocreate);
	if (!InFile) {cerr<<"��� ������ �����!";InFile.close(); return;} else
	{
		//������ 1 ����� � ������� ������� ������ �������
		//������ 2 ����� � �� ���� ����� ������ ����
		InFile.getline(str,100);
		int i=0;
		while ((int(str[i])<48)||(int(str[i])>57))
		i++;
		int j=0;
		str1 =  new char[10];
		while ((int(str[i])>=48)&&(int(str[i])<=57))
		{ str1[j]=str[i]; j++; i++; }
		str1[j]='\0';
		int k=0;
		while ((int(str1[k])>=48)&&(int(str1[k])<=57)) k++;
		size=0;
		size=str1[k-1]-48;
		for (j=1;j<k;j++) 
		{   
			int deg=1;
			for (int h=1;h<=j;h++) {deg = deg*10;}
			size=size+(str1[k-j-1]-48)*deg;
		} 
		delete[]str1;
		//cout<<size;
		//----------------------------
		
		//----------------------------
        
		while ((int(str[i])<48)||(int(str[i])>57))
		i++;
		j=0;
		str1 =  new char[10];
		while ((int(str[i])>=48)&&(int(str[i])<=57))
		{ str1[j]=str[i]; j++; i++; }
		str1[j]='\0';
		k=0;
		while ((int(str1[k])>=48)&&(int(str1[k])<=57)) k++;
		Number_Edge=0;
		Number_Edge=str1[k-1]-48;
		for (j=1;j<k;j++) 
		{   
			int deg=1;
			for (int h=1;h<=j;h++) {deg = deg*10;}
			Number_Edge=Number_Edge+(str1[k-j-1]-48)*deg;
		} 
        delete [] str1;
		//------------------ �������� �������---------------
		n=size;
		m=Number_Edge;
		Graph_A = matrix<bool>(n,m);
		for(int l=0;l<n; l++) 
		  for(int p=0;p<m; p++) 
		    Graph_A[p][l]=0;
		int Decimals=5;//�������� ��� �������� l-�������;
       //---------------------------------------------------

	   for ( int l=0; l<Number_Edge;l++)
	   { 
		   //������� 1 ����� 2 ����� � � ������� �������� �� ��� ����� 1
		  InFile.getline(str,100);
		  ////////
		  str1 =  new char[10];
		  for(int l=0;l<10; l++)
	       {
				  str1[l]=' ';
		   }
		  int i=0;
		  while ((int(str[i])<48)||(int(str[i])>57)) i++;
		  int j=0;
		  while ((int(str[i])>=48)&&(int(str[i])<=57))
		  { str1[j]=str[i]; j++; i++; }
		  str1[j]='\0';
		  int k=0;
		  while ((int(str1[k])>=48)&&(int(str1[k])<=57)) k++;
		  int first=0;
		  first=str1[k-1]-48;
		  for (j=1;j<k;j++) 
		  {   
			int deg=1;
			for (int h=1;h<=j;h++) {deg = deg*10;}
			first=first+(str1[k-j-1]-48)*deg;
		   } 
		  delete[] str1;
		  	str1 =  new char[10];
		 while ((int(str[i])<48)||(int(str[i])>57)) i++;
		 j=0;
		 for(int l=0;l<10; l++)
		  {
			  str1[l]=' ';
		  }
		 while ((int(str[i])>=48)&&(int(str[i])<=57))
		 { str1[j]=str[i]; j++; i++; }
		 str1[j]='\0';
		
		 k=0;
		 while ((int(str1[k])>=48)&&(int(str1[k])<=57)) k++;
		 int second=0;
		 second=str1[k-1]-48;
		 for (j=1;j<k;j++) 
		 {   
			int deg=1;
			for (int h=1;h<=j;h++) {deg = deg*10;}
			second=second+(str1[k-j-1]-48)*deg;
		} 
	     delete[] str1;  
		Graph_A[l][first-1]=1;
		Graph_A[l][second-1]=1;
  
	}// for ( int l=0; l<Number_Edge;l++)
	   InFile.close();
}//if
}

//---------������ ��������, ������������� ��������-------------------------------------
int Independent_Set_Problem::Function ()
		//���������� ����� ������ �� ������� ����������� ����������� ����� ��������� ������ �������
		//�� ���� ����� ������� ������� ���������� ��� ����� �����
		//������������ ������ �� ����������� �������
{
	int sum=100000;
	int sum_new;
	int i,j;
	int Number=0;
	for (i=0 ; i< Graph.ret_h() ; i++)
	{
		if (Vertex_Graph[i].zapret==0)
		{
		  sum_new=0;
		  for (j=0 ; j< Graph.ret_w(); j++)
			if (Vertex_Graph[j].zapret==0) sum_new=sum_new+Graph[i][j];   
		  if (sum_new < sum) 
		  {
			sum=sum_new;
			Number=i;
		}
		}
	}
	return Number;
}
void Independent_Set_Problem::Add_Elem (int Number)
//���������� � ����� ������� ������� ����������� � ������������ ���������
{
	int i ;
	for (i=0; i<n; i++)
	{
		if (Answer[i]== -1) {Answer[i]=Number; return;}
	}
	return;
}
void Independent_Set_Problem::Update_Zapret(int Number)
//��������� ������� ������� ����������� ����� ������ ��� ����������� ������� � ���.���.��.
{
	int j;
	for (j=0; j<Graph.ret_w(); j++)
		if (Graph[Number][j]==1) Vertex_Graph[j].zapret=1;
	Vertex_Graph[Number].zapret=1;
}
bool Independent_Set_Problem::Stop_Criteria()
//�������� �������� ���������, ���� ��� ������� �� ���. �������� ���������, �� �����.
{
	for (int i=0; i<n ; i++)
	{
		if (Vertex_Graph[i].zapret==0) return false;
	}
  return true;
}
void Independent_Set_Problem::Print_Answer()
//�������� �����, � ��������� ���������� ��������� � ��������� ���������.
{
	Sort_Answer();
	int k=0;
	for (int i=0; i<n; i++)
		if (Answer[i]!=-1) {cout<<" "; cout<<Answer[i]; k++;}
		cout<<endl<<"Account="<<k<<" ";
}
void Independent_Set_Problem::Sort_Answer()
//��������� ������ � ��������� �� ����������� �� �������
{
	int tmp;
	for(int k=n-1; k>=0; k--)
	{
	for (int i=0; i<k; i++)
	{
		if (Answer[i]>Answer[i+1]) 
		{
			tmp=Answer[i+1];
			Answer[i+1]=Answer[i];
			Answer[i]=tmp;

		}
	}
	}
}
bool Independent_Set_Problem::Check_Result(int k,matrix<bool> matr)
{
	//������� ���������� ��������� �� ����� � �������� �������� ������� ��������������� ��������
	//����������� ������������ ���������, ���� ������� ����������, �� ��� ������ ���� ���������
	matrix<bool> matr_new;
	matr_new=matrix<bool>(k,k);
	int deadline=0;
	for (int i=0; i<n; i++)
		if (Answer[i]!=-1) {deadline=i; break;}
	
	for(int i=0; i<k; i++)
	 for (int j=0; j<k; j++)
	 {  int s=Answer[deadline+i];
		int t=Answer[deadline+j];
		matr_new[i][j]=matr[s][t];
	}
	for(int i=0; i<k; i++)
	 for (int j=0; j<k; j++)
	 { 
		if ((i==j)&&(matr_new[i][j]!=1)) return false;
		if ((i!=j)&&(matr_new[i][j]!=0)) return false;
		 // cout<<" ";
		// cout<< matr_new[i][j];
	 }
	return true;
}
int* Independent_Set_Problem::Vertex_Min_Incedence(int &length)
//�������� �� ���� ������� ����������� ����� � ���� � ��� �������, 
//������� ����������� ��� ���� ������.
{
	int sum=100000;
	int sum_new;
	int i,j;
	int Number=0;
	length=0;
	int* Array = new int [Graph.ret_h()];
	for (i=0 ; i< Graph.ret_h() ; i++)
	{
		  sum_new=0;
		  for (j=0 ; j< Graph.ret_w(); j++)
				sum_new=sum_new+Graph[i][j];   
		  if (sum_new < sum)
		  {
			sum=sum_new;
			Number=i;
		  }
	}

	//����� ������ ��� ����� , ���� �������� ��� � ������ ����� �������
	Array[length]=Number;
	length++;

	for (i=0 ; i< Graph.ret_h() ; i++)
	{
		  sum_new=0;
		  for (j=0 ; j< Graph.ret_w(); j++)
				sum_new=sum_new+Graph[i][j];   
		  if ((sum_new == sum)&&(i!=Number))
		  {
		   //�������� i � ������ ���
			  Array[length]=i;
			  length++;
		  }		  
		  
	}
	return Array;//������ ���;
}

int* Independent_Set_Problem::Greedy_Algorithm()
{
		/* ��������! 
   ���� �� �������� �������� ��������� 
   "��� ������� ���������" bool Stop_Criteria(Vertex_Graph)
   ������
   1. int(Number) Function (Matrix ,Vertex_Graph)
	  ���� ����� �� ����������� ��������� �� �� ����������� ������� �������
	  ���� ����� ���� ���������� � ���������� ����� ������ �� ������� ��������� �������
   2. Function Add_Elem ��������� ��� ������� � ������������ ���������, �� ���� � ������ ������
   3. Function Update_Zapret(Vertex_Graph,Matrix)��������� �� � ����������� �� �������
---------------
   ������� �����
*/
	
	int Number;
	//----------������������� ��������--------------------------------------
	Vertex_Graph = new A[n];
	for (int i=0; i<n; i++)
	{
		Vertex_Graph[i].Number=i;
		Vertex_Graph[i].zapret=0;
	}
	
	Answer = new int[n]; for (int i=0; i<n; i++) Answer[i]=-1;
	//---------------------------------------------------------------------- 
	
	int size_Graph=n;
	int length;
	int* Array_Number;

	//----------------��������------------------------------- 
	//����� � ������ �������
	while (!Stop_Criteria()) 
	{
		Number = Function ();
		Add_Elem(Number);
		Update_Zapret(Number);
	}

	//--------------------------------------------------------
	int i;
	int k=0;
	for (i=0; i<n; i++)
		if (Answer[i]!=-1) k++;
		
	Solution=new int[n+1];
	for (i=0; i<n+1; i++)
	{
		if (i==0) Solution[i]=k; 
		else Solution[i]=0;
	}
	int temp;
	for (i=0; i<n; i++)
	{
		temp=Answer[i];
		if (temp!=-1) Solution[temp+1]=1;
	}
	//--------------------------------------------------------
	
	return Solution;
}
void Independent_Set_Problem::Update_Probability(int len_limit)
{
	//������������� �����������
	//!!!!!!!!!!!!!!!!!
	//��� ����������� ������ ����� � ������� ������ ����������� 0
	//������� ��������� ��������� ������ ����� �������� ���� �� ����������� ������
	//���� ������� �� ��������� ������� ����� �� ������ 1
	//����� ���� ����� �� ������, ����� ����� � ������ 0
	int i,j;
	double s,k=0;
	double norm=1;
	int len=0;
	double sum, proiz;
	//-------------------------------------
	//������� ���������� �� ����������� ������
	for (i=0; i<n; i++)
	   if (Vertex_Graph[i].zapret!=1) len++;

	struct elem
	{
		  int number;
		  int degree;
	};
	elem* incident=new elem[len];
	  
	//int * incident = new int [len];//������ �������� ������
	
	   i=0;
	   s=0;
	   //���������� ������������ �� ����������� ������
	   //������� ��� ������� ���� ���� �����������
    
	   for (int t=0; t<n; t++)	
	      if (Vertex_Graph[t].zapret!=1)
		   {
              s=0;
			  for (j=0; j<n; j++)
			      if ((Vertex_Graph[j].zapret!=1)&&(Graph[t][j]==1)) s++;
		      //���� ������� �� ��������� �� � �����, �� �� ������� 1 ,� ����� 
              //������������� ������������ ��� (0,0,0,0,1,0,0,0) 1 �� ����� �������, ������� �� ��������� �� � ����� ������
              if (s==1)
			  {
				  probability[t]=1;
				  for (int i=0; i<n; i++) 
			       if (i!=t) probability[i]=0;
	 		  	  delete[] incident;
				  return;
			  }
			  incident[i].degree=s; 
			  incident[i].number=t;
			  i++;
		   }
     
	//cout<<"array of incindent"<<endl;  
	//for (j=0; j<len; j++) cout<<incident[j]<<endl;
	//-------------------------------------
    if (len<=len_limit)
	{
		//------������� ������������� ���������---
		proiz=1;
		for (i=0; i<len; i++) 
			proiz=proiz*incident[i].degree;
		sum=0;
		  for (j=0; j<len; j++)
		  {
			  k=1;
			  for (i=0; i<len; i++) 
		  			  if (i!=j) k=k*incident[i].degree;
			  sum=sum+k;
		  }
		if (s!=0) norm=proiz/sum;
		//----------------------------------------
		for (i=0; i<n; i++)
		{
			if (Vertex_Graph[i].zapret!=1)
			   {
				  /*s=0;
				  for (j=0; j<n; j++)
				      if ((Vertex_Graph[j].zapret!=1)&&(Graph[i][j]==1)) s++;*/
			      for (j=0; j<len; j++)
					  if (incident[j].number==i) s=incident[j].degree;
				  probability[i]=(double)norm/s;
	 		   }
			else probability[i]=0;
		}
	}
	else//���������� ������
	{
      /*int* vsp=new int[100];//�������� ����. ������� 100 ������, � �� ��� 50 � ������ ��������
	  int R;
	  for (i=0; i<100; i++)
	  {
		  R = (((double) rand()) /(double) RAND_MAX);
		  int index = (int)R*len;
		  vsp[i]=incident[index];

	  }*/
	  //����������
	  for(i=0; i<len; i++)
	  {
		for(j=len-1; j>=i; j--)
		 {
           if (incident[i].degree>incident[j].degree)
		   {
			  int temp;
			  temp = incident[i].degree;
			  incident[i].degree=incident[j].degree;
			  incident[j].degree=temp;
              temp = incident[i].number;
			  incident[i].number=incident[j].number;
			  incident[j].number=temp;

		  }
		}
	   }
	  //for(i=0; i<len; i++) cout<<incident[i].degree<<" "<<incident[i].number<<endl; 
	  //------������� ������������� ���������---
	  //���������� len_limit ������ ��������	
	  proiz=1;
		for (i=0; i<len_limit; i++) 
			proiz=proiz*incident[i].degree;
		sum=0;
		  for (j=0; j<len_limit; j++)
		  {
			  k=1;
			  for (i=0; i<len_limit; i++) 
		  			  if (i!=j) k=k*incident[i].degree;
			  sum=sum+k;
		  }
		if (s!=0) norm=proiz/sum;
		//----------------------------------------
		for (i=0; i<n; i++)
		{
			if (Vertex_Graph[i].zapret!=1)
			 {
				 bool flag=0;
				 for (j=0; j<len_limit; j++)
					if (incident[j].number==i) 
					{
						s=incident[j].degree;
				 	    probability[i]=(double)norm/s;
						flag=1;
						break;
				    }
				 if (flag==0) probability[i]=0;
			}
			else probability[i]=0;
		}
	}
	//for(int i=0; i<n; i++) cout<<probability[i]<<" ";
	if (incident!=0) delete [] incident;
}
int Independent_Set_Problem::Select_Vertex()
{
	int number=0;
	int len=0;
	double s=0;
	double* vsp;
	int j,i;
	double r;
    struct PB
	{
		int num_vertex;
		double prob;
	};
	PB* temp;
	for(i=0;i<n;i++) 
	{ 
		double v;
		v=probability[i];
		if (v!=0.0) len++;
		if (v==1) return i;
	} 
	if (len!=0)	temp=new PB[len]; else return -1;
	
	 j=0;
	 for( i=0; i<n; i++)
	  {
		if (probability[i]!=0.0)
		{
			temp[j].num_vertex=i;
			temp[j].prob=probability[i];
			j++;
		}
	 }
    
    vsp=new double[len];

    for(i=0; i<len; i++)
	{
	  s=0;
	  for(j=0; j<=i; j++) s=s+temp[j].prob;
	  vsp[i]=s;
	}
	
    r = (((double) rand()) /(double) RAND_MAX);
	
	for(i=0; i<len; i++)
		if (r<=vsp[i]) 
		{ 
		 number=temp[i].num_vertex;
		 break;
		}
	
	if (vsp!=0) 
		delete[] vsp;
	if (temp!=0)
		delete[] temp;
	return number;
}
int* Independent_Set_Problem::Probability_Algorithm(int number_iteration,int len_limit)
{
	int Number;
	int i,k=0;
	int rec=0;
	//double* Prob;//������ ������������		
			
	Vertex_Graph = new A[n];
	Answer = new int[n]; 
	probability=new double[n];
	//Prob=new double[n];
	
	int* x_best=new int[n+1];//������ ������� �� �������� ���������� ��������
	for (i=0;i<n+1;i++) x_best[i]=0;

	//cout<<Graph;
	
	while (k<number_iteration)
	{
		/*if (k<=1000) len_limit=16;
		if ((k>1000)&&(k<=2000)) len_limit=12;
		if ((k>2000)&&(k<=3000)) len_limit=8;
		if ((k>3000)&&(k<=4000)) len_limit=4;
		if ((k>4000)&&(k<5000)) len_limit=2;*/
		//������������� ��������-------------------- 
            for (int i=0; i<n; i++)
			{
				Vertex_Graph[i].Number=i;
				Vertex_Graph[i].zapret=0;
			}
			for (int i=0; i<n; i++) Answer[i]=-1;
       //-------------------------------------------
		while (!Stop_Criteria()) 
			{
				Update_Probability(len_limit);
			    Number = Select_Vertex();
				//cout<<Number<<endl;
				Add_Elem(Number);
				Update_Zapret(Number);
				//for (i=0; i<n; i++) cout<<Vertex_Graph[i].zapret<<" ";
				///cout<<endl;
				
			}
		rec=0;
		for (i=0; i<n; i++) if (Answer[i]!=-1) rec++;
		if (rec>x_best[0])//������������� ������ �������
		{
			if (Check_Result(rec,Graph)==false)	break;
			for (i=0; i<n+1; i++)
				{
					if (i==0) x_best[i]=rec; 
					else x_best[i]=0;
				}
				int temp;
				for (i=0; i<n; i++)
				{
					temp=Answer[i];
					if (temp!=-1) x_best[temp+1]=1;
				}
                //cout<<x_best[0]<<" ";
		}//if
		k++;
		//Print_Answer();
	}//while
	delete [] Vertex_Graph;
	delete [] probability;
return x_best;	  
	
}



//---��������� ���������-------------------------------------------------------------
int* Independent_Set_Problem::FindPath(int NUM_VERTICES, matrix<int> c_f, matrix<int> c, matrix<int> &f, int source, int target) 
// ����� ����, �� �������� �������� ������� �����. �������� ������ ����� � ������.
// ������� ���� ���� �� ������ � ���� �� �������� ��� ����� ������� ����� 
// �� ��������������� ����, ��� ���������� ����������� ������ �������� c_f, 
// �������� �������(������� f)��������� � ��������� �������� ����� � ������ ������ 2*n. 
//matrix<int> c_f -- ���������� ����������� ����� � ��������������� ����
//matrix<int> c -- ���������� ����������� ����� � �������������� ����
//matrix<int> f -- ����� � �������������� ����
//NUM_VERTICES - ���������� ������ ���� = 2*n
//source -��������, target -����
{
   const int INFINITY = 1000; // �������� ����� ������������ �������������
   // ����� ��������������� ���������� ������������ �������� FindPath - ������ � ������
   int* Link;
   // Link ������������ ��� ���������� ���������� ����
   // Link[i] ������ ����� ���������� ������ �� ���� i -> �����
   int* Queue; // ������� ������ ��� ���������
   int* Flow;  // Flow - �������� ������ ����� ������ ������� �� ������ ���� ������
   int QP, QC; // QP - ��������� ������ ������� � QC - ����� ��-��� � �������
      
		Flow = new int[NUM_VERTICES];
		Link = new int[NUM_VERTICES];
		Queue = new int[NUM_VERTICES];
		memset(Queue, -1 , sizeof(int)*NUM_VERTICES); 

        QP = 0; QC = 1; Queue[0] = source;
        Link[target] = -1; // ������ ����� ��� �����
        int i;
        int CurVertex;
        memset(Flow, 0, sizeof(int)*NUM_VERTICES); // � ������ �� ���� ������ ����� ������ ����� 0
        Flow[source] = INFINITY; // � �� ������ ����� ������ ������� ������
        while (Link[target] == -1 && QP < QC)
        {
                // ������� ����� ������� ����� ���� ���������� �� ������ �������
                CurVertex = Queue[QP];
                for (i=0; i<NUM_VERTICES; i++)
                // ��������� ����� �� �� ������� ����� �� ����� (CurVertex,i):
                if (c_f[CurVertex][i]>0 && Flow[i] == 0) 
                {
                        // ���� �����, �� ��������� i � ����� �������
                        Queue[QC] = i; QC++;
                        Link[i] = CurVertex; // ���������, ��� � i ��������� �� CurVertex
                        // � ������� �������� ������ ������� ����� ������� i
                        if (c_f[CurVertex][i] < Flow[CurVertex])
                             Flow[i] = c_f[CurVertex][i];
                        else
                             Flow[i] = Flow[CurVertex];
                }
            QP++;// ��������� � ��������� � ������� �������
        }
        // �������� ����� ����
		int* res = new int[NUM_VERTICES+1];
		for (int i=0; i<NUM_VERTICES+1; i++)
				res[i]=0;

		if (Link[target] == -1) {
			res[0]=0;
			for (int i=1; i<NUM_VERTICES+1; i++)
				res[i]=Queue[i-1];
			//res[0] -�������� ������������� ������, ����� ������������� ������� ��������� W
			// �� ���� ������ ������ ���������� �� ����� �� ��������� ��������, �����
			// ������ �������� -1.
			delete [] Flow; 
		    delete [] Link; 
		    delete [] Queue; 
					
			return res; // �� ��� �� ������� ���� � �������
		}
        // ��� �������:
        // ����� Flow[target] ����� ����� ������ ������� "�����" �� ������� ���� �� ������ � ����
        // ����� �������� �������� ������� f ���  ������� ���� �� �������� Flow[target]
        //--------------------------FLOW-----------------------------------------------
		CurVertex = target;
        while (CurVertex != source) // ���� �� ����� � ����� �� ��������������� � ������� ������� Link
        {
                //� ��������������� ���� ������ ����, � ����� �� ����������� � ���� ���� � ������� ���� 
			//flow ������ ��� ��������������� ����,� ����� f ���������� ��� ��������� ����� 
			//Note: ���� ������ ����� � �������� ����, �� ����� �� ������ �������� ������ 
			//����������� ��������(�� ���� ��������������� � ����������������� ����)
			//����� �� ��������� ��������������� ���� � � ��� ������ ������� ����, ���������
			//������ �� ��������������� ���, ��������� ����������� ������� ��� �������� � 
			//���� ���������� ����������� ��������.
			if (c[Link[CurVertex]][CurVertex] - f[Link[CurVertex]][CurVertex]>= Flow[target])
				f[Link[CurVertex]][CurVertex] +=Flow[target];
			else
			{
                f[Link[CurVertex]][CurVertex] = c[Link[CurVertex]][CurVertex];
                f[CurVertex][Link[CurVertex]] -=Flow[target]-(c[Link[CurVertex]][CurVertex] - f[Link[CurVertex]][CurVertex]);
			}
                CurVertex = Link[CurVertex];
        }
		
		res[0]=Flow[target];
		delete [] Flow; 
		delete [] Link; 
		delete [] Queue; 
		return res; 
}

int* Independent_Set_Problem::MaxFlow(/*matrix<bool> org_graph, */int NUM_VERTICES, matrix<int> c, int source, int target) 
//�������� ������� ������ ������������� ������
//source - �����, target - ����
//������� ���������� ������ ������ NUM_VERTICES+1, ������� ���������� ��� �������� 
//������������� ������, ����� ���� ������ ������, ������� ��������� �� �����, ����� 
//������ �������� -1
{
    matrix<int> f; // f - ������ ���������� ������� �������� ������
	f = matrix<int>(NUM_VERTICES, NUM_VERTICES); // f[i][j] - ����� ������� �� ������� i � j
	// �������������� ����������:
	for(int i=0; i<NUM_VERTICES; i++){
		for (int j=0; j<NUM_VERTICES; j++){
			 f[i][j]=0; // �� ����� ������ �� �����
		}
	}
        int MaxFlow =0; // ��������� �������� ������
        int* AddFlow;
		matrix<int> c_f;
		c_f = matrix<int>(NUM_VERTICES, NUM_VERTICES);
        while (true)
        {
			// ������ �������� ���� ����-���� ������� ���� �� ������ � ����
            // � ����� ��� ����� ����� ���� ����� �� ����� ����
            
			//����������� c_f ��� ��������������� ����    
			for(int i=0; i<NUM_VERTICES; i++){
	        	for (int j=0; j<NUM_VERTICES; j++){
	                if ((c[i][j]>0 && f[i][j]<c[i][j])||(c[j][i]>0 && f[j][i]!=0))
						c_f[i][j] = c[i][j] - f[i][j] + f[j][i];
					else
						c_f[i][j] = 0;
				}
			}
			//cout<<c_f;
			AddFlow = FindPath(NUM_VERTICES, c_f, c, f, source, target);
			if (AddFlow[0] != 0){
				MaxFlow += AddFlow[0];
				delete[] AddFlow;
	
			}
			else{
				AddFlow[0] = MaxFlow;
				return AddFlow;
			}
	    } // ��������� ���� ���� ����� �������������
        
}

int* Independent_Set_Problem::find_local_connectivity(/*matrix<bool> org_graph,*/ matrix<int> c, /*int n_, */int s2, int t1)
//���������: n_ ���� ������ � �������� �����,
// s2, t1 ������� ����� �������� ������ ��������� ��������� � ���� ������������� org_graph
//������� ���������� ������ ����� n_, array[i]=1 if this vertex need to delete
{
	int* local_connectivity = new int[n];
    for (int i=0; i<n; i++)
       local_connectivity[i] = 0;

    int* W; //W �������� ������ ������ ���������� �� ����� �� ��������� ��������
	W = MaxFlow(/*org_graph,*/ 2*n, c, s2, t1);
	int* W_ = new int[2*n+1]; //����������� ��������� ������ �������
	//������ ����������� ��������� ������
	W_[0] = W[0];
	bool flag;
	int WC=1;
	for (int i=1; i<2*n+1; i++) W_[i]=-1;
	for (int i=0; i<2*n; i++){
		flag = false;
		for (int j=1; j<2*n+1; j++)
			if (W[j]==i){ 
				flag=true;
				break;
			}
		if (flag == false){
			W_[WC]=i;
		    WC++;
		}
	}
	//for (int i=0; i<2*n_+1; i++)
	//	cout<<W_[i]<<" ";
	//���� ��� ���������� �������, ����� ���� ������� �� ����� ���������� � ������
	for(int i=1; i<2*n+1; i++){
		for(int j=1; j<2*n+1; j++)
		   if (W[i]!=-1 && W_[j]!=-1 && c[W[i]][W_[j]]>0 && W[i]+1==W_[j])
			   local_connectivity[W[i]/2]=1;
	}
	//cout<<endl;
	//cout<<"local connectivity =";
	//for(int i=0; i<n_; i++)
	//	cout<<local_connectivity[i]<<" ";
	//cout<<endl;
	delete[] W;
	delete[] W_;
	return local_connectivity;
}
int Independent_Set_Problem::len(int* _array, int n)
//���������� ���������� ������ � �������, �������� �����
{
	int lenght = 0;
	for (int i=0; i<n; i++)
		if (_array[i]==1)
			lenght ++;
	return lenght;
}

int* Independent_Set_Problem::find_vertex_connectivity()
//������� ���������� ������ ������� n, i ������� ������� ����� 1, ���� ������� i �����
//������� �� �����, ����� �� �������� �� ���������� ���������
{
  matrix<int> c;
  //matrix<bool> org_graph;
  int* local_connectivity;
  const int infinity = 1000;
  
  int* global_connectivity;
  global_connectivity = new int[n];
  for (int i=0; i< n-1; i++)
	  global_connectivity[i] = 1;
  global_connectivity[n-1] = 0;
 
  // � - ������ ���������� ���������� �����,
  // �.�. c[i][j] - ������������ �������� ������ ��������� ���� �� ����� (i,j)
  //������ ���������������� ���� � ������������ ��������� , ��������� ������� c
  // c[i][j] = 0 ���� ������� �� ������
  // c[i][j] = 1 or infinity  ���� ������� ������
  c = matrix<int>(2*n, 2*n);
  //org_graph = matrix<bool>(2*n, 2*n);
  
  for (int i=0; i<2*n; ++i)
	  for (int j=0; j<2*n; ++j){ 
		c[i][j]=0;
        //org_graph[i][j]=0;
	  }
  
  //���������� �������� �����
  //i_old --> (2*i_old, 2*i_old+1)
  //(i_old,j_old) --->  (2*i_old, 2*i_old+1)  c=1
  //                    (2*j_old, 2*j_old+1)  c=1
  //                    (2*i_old+1, 2*j_old)  c=infinity
  //                    (2*j_old+1, 2*i_old)  c=infinity
  for (int i_old=0; i_old<n; ++i_old)
  {
	for (int j_old=i_old; j_old<n; ++j_old) 
	{
		if (i_old == j_old) continue;
		if (Graph[i_old][j_old] == 1){
            c[2*i_old][2*i_old+1]=1;
            c[2*j_old][2*j_old+1]=1;
            c[2*i_old+1][2*j_old]=infinity;
			c[2*j_old+1][2*i_old]=infinity;
		    
			/*org_graph[2*i_old][2*i_old+1]=1;
            org_graph[2*j_old][2*j_old+1]=1;
            org_graph[2*i_old+1][2*j_old]=1;
			org_graph[2*j_old+1][2*i_old]=1;*/
		    
		}
	}
  }
    
  //cout<<c<<endl;
  //�������� ������ ��������� ���������
  for (int s=0; s<n; ++s)
	for (int t=s+1; t<n; ++t) 
	{
		if (Graph[s][t])  continue;
		//s1 = 2*s, s2 = 2*s + 1
		//... ������� �������� flow ������������� ������ �� s2 � t1 ...
		//cout<<"s= "<<s*2+1<<endl;
		//cout<<"t= "<<2*t<<endl;
		local_connectivity  = find_local_connectivity(/*org_graph,*/ c, 2*s+1, 2*t);
        if (len(local_connectivity, n) < len(global_connectivity, n))
			for (int i=0; i<n; i++)
				global_connectivity[i] = local_connectivity[i];
		if (len(global_connectivity, n)==1){
            delete [] local_connectivity;
			return global_connectivity;
		}
		delete [] local_connectivity;
		
	}
   return global_connectivity;
}
int Independent_Set_Problem::find_connected_components (matrix<bool> g, int n)
{
	bool* used = new bool[n];
	memset(used, false , sizeof(bool)*n); 
	cout << "Components:\n";
	int count_component=0;
	for (int v=0; v<n; ++v)
		if (!used[v])
		{
			cout << "[ " << v;
			count_component ++;
			int* q=new int[n];
			memset(q, 0 , sizeof(int)*n); 
			int h=0, t=0;
			q[t++] = v;
			used[v] = true;
			while (h < t)
			{
				int cur = q[h++];
				for(int j=0; j<n; j++)
				{
					if ((g[cur][j]==1)&&(!used[j]))
					{
						used[j] = true;
						q[t++] = j;
						cout << ", " << j;
					}
				}
			}
			cout << " ]\n";
		}
		return count_component;
}

matrix<bool> Independent_Set_Problem::delete_vertex_from_graph(matrix<bool> graph, int n, int* vertex_connectivity)
//������� ���������� ����� ���� ��� ��������� ������
{
	matrix<bool> graph_without_VC;//����� ���� � ���������� ��������� �� 
	                              // ��������� ��������� ��������� �����
	int new_n = n - len(vertex_connectivity,n);
	graph_without_VC = matrix<bool>(new_n, new_n);
    
	int start_i =0;
	int start_j =0;
	int str_num, col_num;

	for(int i=0; i<new_n; i++){
		str_num = start_i;
		while (vertex_connectivity[str_num]!= 0){
			str_num ++;
		    start_i = str_num;
		}
		start_j =0;
		for(int j=0; j<new_n; j++){
			col_num = start_j;
			while (vertex_connectivity[col_num]!= 0){
				col_num ++;
				start_j = col_num;
			}
			graph_without_VC[i][j] = graph[str_num][col_num];
			start_j++;
		}
        start_i++;
	}
    return graph_without_VC;
}

matrix<bool> Independent_Set_Problem::del_vertex_and_find_components(int* vertex_connectivity)
{
matrix<bool> res;
matrix<bool> new_graph;
new_graph = delete_vertex_from_graph(Graph, n, vertex_connectivity);
//����� ���� �� �������� ��������� ������, ��� ����������� ������ �� ����� ����� �������
//cout<<new_graph<<endl;    
res = matrix<bool>(n, n);
for(int i=0; i<n; i++)
  for(int j=0; j<n; j++)
	  res[i][j]=0;
int new_n = new_graph.width;
bool* used = new bool[new_n];
memset(used, false , sizeof(bool)*new_n); 
int component_number =0 ;
int j_old;
for (int v=0; v<new_n; ++v){
     if (!used[v]) {
			int* q=new int[new_n];
			memset(q, 0 , sizeof(int)*new_n); 
			int h=0, t=0;
			q[t++] = v;
			used[v] = true;
            int number_v_zero =-1;
			int i;
			for(i=0; i<n; i++)
			   if (vertex_connectivity[i]==0)
				{   
					number_v_zero++;
					if (number_v_zero == v)
				        break;
			    }
			j_old = i;//v + len(vertex_connectivity, v+1);
			res[component_number][j_old]=1;
			while (h < t)
			{
				int cur = q[h++];
				for(int j=0; j<new_n; j++)
				{
					if ((new_graph[cur][j]==true)&&(!used[j]))
					{
						//j - ��� ����� � ����� �����, ����� � ������, ���������� n ������
						//����� j_old
						// j_old = j + len(vertex_conectivity,j)
						used[j] = true;
						q[t++] = j;
                        number_v_zero =-1;
						for(i=0; i<n; i++)
							if (vertex_connectivity[i]==0)
							{   
								number_v_zero++;
								if (number_v_zero == j)
									 break;
							}
						j_old = i;//v + len(vertex_connectivity, v+1);
						//j_old = j + len(vertex_connectivity, j+1);
						res[component_number][j_old]=1;
						//cout << ", " << j;
					}
				}
			}
	}//if
   component_number++;  
 }
return res;
}
matrix<bool> Independent_Set_Problem::evristic_algorithm(int count_vertex_in_block, int* &common_cols)
//�������� �������� ������� �������(����) ��������� �������, ������� �� ����� ��� �������,
//����������� ���� ���� � ��������� ������, � ������� ������� ��� ���������� ���������
// � ��� ������ ���������� ������, ������� ������ ��������� ����� ������ ����� �������� ��� ������
//������� ���������� ������� ���������, � ����� ������� ����� �������� �������� ����������
{
	//�������� ���������� ��������� �������� ������ ��� ����� count_vertex_in_block
	matrix<bool> components = matrix<bool>(n, n);
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			components[i][j] = 0;
	common_cols = new int[n];
    memset(common_cols, 0 , sizeof(int)*n); 

	bool* used = new bool[n];
	memset(used, false , sizeof(bool)*n); 
	//
	int count;
	int component_number =0;

    for (int v=0; v<n; ++v)
	  {
	   	if (!used[v])
		{
			count = 0;
			int* q=new int[n];
			memset(q, 0 , sizeof(int)*n); 
			int h=0, t=0;
			q[t++] = v;
			used[v] = true;
			count ++;
			components[component_number][v]=1;
			if (count >= count_vertex_in_block)
							break;
			while (h < t)
			{
				int cur = q[h++];
				for(int j=0; j<n; j++)
				{
					if ((Graph[cur][j]==1)&&(!used[j]))
					{
						used[j] = true;
						q[t++] = j;
						//cout << ", " << j;
						count ++;
						components[component_number][j]=1;
						if (count >= count_vertex_in_block)
							break;
					}
				}
				if (count >= count_vertex_in_block)
							break;
			}
    	    //cout << " ]\n";
		//��������� ������� ��������� � ����������� � ������������� � � ����� �������
		for(int j=0; j<n; j++)
			if (components[component_number][j]==true){
				for (int k=0; k<n; k++)
					if ((Graph[j][k]==true)&&(components[component_number][k]==false)){
						used[k]=true;
						common_cols[k]=1;
					}
			}
		component_number++;
		}//if
 
        
	  }//for

//print 
/*cout<<"Common cols: [";
for(int i=0; i<n;i++)
    if (common_cols[i]==1)
        cout<<i<< ", ";
cout<<"]"<<endl;

cout<<"Components: ";
for(int i=0; i<n; i++){
   cout<<"["; 
   for(int j=0; j<n; j++)
	   if (components[i][j]==1)
	        cout<<j<< ", ";
   cout<<"]"<<endl;
}*/
return components; 
}

void Independent_Set_Problem::dfs (int v, int p) 
{
	/*used[v] = true;
	tin[v] = fup[v] = timer++;
	int children = 0;
	
	for (int i=0; i<n; ++i) 
	{
	   if ((v!=i)&&(Graph[v][i]==1))//��� ������ ������� y ������� � v
	   {  
         if (i != p) 
		 {
            if (used[i] == 0) 
			{
              children++;
			  //used[i]=1;
			  dfs(i, v);
              fup[v] = min(fup[v], fup[i]);
            } 
			else 
			{// �������� �����
               fup[v] = min(fup[v], tin[i]);
            }
        }
	   }
	}
    if (tin[v] == fup[v] && (p!= -1 || children >= 2)) {
     // ������� x - ����� ����������
		common_cols[v] = true;
     }
	 */
	used[v] = true;
	tin[v] = fup[v] = timer++;
	int children = 0;

	for (int i=0; i<n; ++i) 
	{
		if ((v!=i)&&(Graph[v][i]==1))
		{
			if (i != p) 
		    {
				int to = i;
				if (used[to])//�������� �����
				{
				 fup[v] = min (fup[v], tin[to]);
				 children++;
				}
				else {
					children++;
					dfs (to, v);
					fup[v] = min (fup[v], fup[to]);
					if (fup[to] >= tin[v])
						common_cols[v] = true;
					//if (fup[to] < tin[v])
					//	common_cols[v] = 0;
				}
			}
		}
	}
	//���� � ����� ������ ���� �����������
	/*if ((p == -1)&&(children > 1))
	{
       bool independent_flag = false;
		for (int i=0; i<n; ++i) 
	       if ((v!=i)&&(Graph[v][i]==1))
              for (int j=0; j<n; ++j) 
        	       if ((v!=j)&&(Graph[v][j]==1)&&(Graph[i][j]==0))
				       independent_flag = true;
	   if (independent_flag == true)
		   common_cols[v] = true;
	   else
		   common_cols[v] = false;
	}*/
	if (p == -1)
		common_cols[v] = false;
	
}

void Independent_Set_Problem::find_articulation_point()
{
used = new bool[n];
memset(used, false , sizeof(bool)*n); 
common_cols = new int[n];
memset(common_cols, 0 , sizeof(int)*n); 
timer=0;
tin = new int[n];
fup = new int[n];
dfs (0);
delete[] tin;
delete[] fup;
delete[] used;

}