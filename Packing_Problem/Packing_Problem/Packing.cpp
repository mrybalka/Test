#pragma warning disable
#include "stdafx.h"

char* inttostr1(int value)
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

Packing_Problem::Packing_Problem()
{
	shuffle=0;
	flag_shuffle=false;
	size_m=15;
	size_n=7;
	A = matrix<bool>(size_n,size_m);
	
	res_n=size_n+1;
	res_m=size_n+size_m+2;
	matr = matrix<double>(res_n,res_m);

	A[0][0]=1;
	A[0][1]=1;
	A[1][0]=1;
	A[1][2]=1;
	A[2][0]=1;
	A[2][3]=1;
	A[3][1]=1;
	A[3][4]=1;
	A[4][1]=1;
	A[4][5]=1;
	A[5][1]=1;
	A[5][6]=1;
	A[6][2]=1;
	A[6][4]=1;
	A[7][2]=1;
	A[7][5]=1;
	A[8][2]=1;
	A[8][6]=1;
	A[9][3]=1;
	A[9][4]=1;
	A[10][3]=1;
	A[10][5]=1;
	A[11][3]=1;
	A[11][6]=1;
	A[12][4]=1;
	A[12][5]=1;
	A[13][4]=1;
	A[13][6]=1;
	A[14][5]=1;
	A[14][6]=1;
	Decimals=5;//точность для перебора l-классов;
	Matrix_Block_Param =0;
	//cout<<A;
}
Packing_Problem::Packing_Problem(int n, int m, double p, bool IsZeroColAndRow)
//p-вероятность появления 1
{
    double r;
	int i,j;
	bool tmp;
	size_m=m;
	size_n=n;
	shuffle=0;
	flag_shuffle=false;
	
	res_n=size_n+1;
	res_m=size_n+size_m+2;
	matr = matrix<double>(res_n,res_m);

	Matrix_Block_Param =0;
	A = matrix<bool>(size_n,size_m);
	for(i=0; i<size_n; i++)
	{
		for (j=0;j<size_m;j++)
		{
			r = (((double) rand()) /(double) RAND_MAX);
			if (r<p) A[j][i]=1; else A[j][i]=0;
		}
	}
	if (IsZeroColAndRow==false)
	{
		//Проверка корректности
		for(i=0; i<size_m; i++)//избавлемс от нулевых строк
		{
			tmp=0;
			for (j=0;j<size_n;j++)
				if (A[i][j]==1) tmp=1;
			if (tmp==0) 
			{
				if (size_n==1) j=1;
				else 
				{
					if (size_n!=1) j= (int)(((int) rand()) %(size_n-1)); 
					else j=0;
				}
				A[i][j]=1;
			}
		}

		for(j=0; j<size_n; j++)//избавлемс от нулевых столбцов
		{
			tmp=0;
			for (i=0;i<size_m;i++)
				if (A[i][j]==1) tmp=1;
			if (tmp==0) 
			{
				if (size_m==1) i=1;
				if (size_m!=1) i= (int)(((int) rand()) %(size_m-1));
				else i=0;
				A[i][j]=1;
			}
		}
	}

 //cout<<A;
}
Packing_Problem::Packing_Problem(int k, int kol, double p, int t)
{
	 double r;
	int i,j;
	bool tmp;
	size_m=k+(kol-1)*(k-1);
	size_n=k+(kol-1)*(k-1);
	shuffle=0;
	flag_shuffle=false;
	
	res_n=size_n+1;
	res_m=size_n+size_m+2;
	matr = matrix<double>(res_n,res_m);

	Matrix_Block_Param =0;
	
	A = matrix<bool>(size_n,size_m);
	
	/*for(i=0; i<k; i++)
	{
		for (j=0;j<k;j++)
		{
			r = (((double) rand()) /(double) RAND_MAX);
			if (r<p) A[j][i]=1; else A[j][i]=0;
		}
	}*/
	for(i=0; i<k; i++)
	{
		for (j=0;j<k;j++)
		{
			if (j==k-i-1) A[j][i]=0; else A[j][i]=1;
		}
	}
	/*for(i=0; i<k; i++)
	{
		for (j=0;j<k;j++)
		{
			if (j==i) A[j][i]=0; else A[j][i]=1;
		}
	}*/

	//Проверка корректности
		for(i=0; i<k; i++)//избавлемс от нулевых строк
		{
			tmp=0;
			for (j=0;j<k;j++)
				if (A[i][j]==1) tmp=1;
			if (tmp==0) 
			{
				if (k==1) j=1;
				else 
				{
					if (k!=1) j= (int)(((int) rand()) %(k-1)); 
					else j=0;
				}
				A[i][j]=1;
			}
		}

		for(j=0; j<k; j++)//избавлемс от нулевых столбцов
		{
			tmp=0;
			for (i=0;i<k;i++)
				if (A[i][j]==1) tmp=1;
			if (tmp==0) 
			{
				if (k==1) i=1;
				if (k!=1) i= (int)(((int) rand()) %(k-1));
				else i=0;
				A[i][j]=1;
			}
		}
	
 //теперь этот блок надо скопировать
 for(int h=1; h<kol; h++)
 {
	 for(i=h*(k-1); i<k+h*(k-1); i++)
	   for(j=h*(k-1); j<k+h*(k-1);j++)
		   A[i][j]=A[i-k*h+h][j-k*h+h];
 }
cout<<A;

}
void Packing_Problem::Add_Elem_To_Matrix_Block_Param(int n, int m)
{
	Block* vsp;
	vsp = Matrix_Block_Param;
	Block* temp = new Block;
	temp->r =vsp->r;
	temp->block_kol =vsp->block_kol+1;
	temp->Blocks = new Block_size[temp->block_kol];
	for (int i=0; i<temp->block_kol-1; i++)
	{
          temp->Blocks[i].n_size=vsp->Blocks[i].n_size;
		  temp->Blocks[i].m_size=vsp->Blocks[i].m_size;
	}
	temp->Blocks[temp->block_kol-1].n_size= n;
	temp->Blocks[temp->block_kol-1].m_size= m;
    Matrix_Block_Param = temp;
	delete vsp;
}
Packing_Problem::Packing_Problem(int n, int m, double p, int r, int block_size, bool randomy)
{
    double Rd;
	int i,j;
	bool tmp;
	//--------------------
	size_m=m;
	size_n=n;
	shuffle=0;
	flag_shuffle=false;
	//---------------------
	A = matrix<bool>(size_n,size_m);
	//---------------------
	res_n=size_n+1;
	res_m=size_n+size_m+2;
	matr = matrix<double>(res_n,res_m);

	//---------------------
	Matrix_Block_Param =new Block;
	Matrix_Block_Param->r = r;

	//генерируем первые r столбцов
	for(i=0; i< r; i++)
	{
		for (j=0;j<size_m;j++)
		{
			Rd = (((double) rand()) /(double) RAND_MAX);
			if (Rd<p) A[j][i]=1; else A[j][i]=0;
		}
	}
	if (r!=0)
	{
			//Проверка корректности
			//---------------------
			for(i=0; i<size_m; i++)//избавлемс от нулевых строк
			{
				tmp=0;
				for (j=0; j<r; j++)
					if (A[i][j]==1) tmp=1;
				if (tmp==0) 
				{
					j= (int)(((int) rand()) %(r-1));
					A[i][j]=1;
				}
			}
			//----------------------
			for(j=0; j<r; j++)//избавлемс от нулевых столбцов
			{
				tmp=0;
				for (i=0;i<size_m;i++)
					if (A[i][j]==1) tmp=1;
				if (tmp==0) 
				{
					i= (int)(((int) rand()) %(size_m-1));
					A[i][j]=1;
				}
			}
	}
	//---------------------
	//генерируем блоки
	int m_size=0;
    int n_size_last=0;
	int m_size_last=0;
	int n_size = block_size;
	int block_kol;
    //заполняем количество и размеры размеры блоков
	if (randomy==true)
	{
		int vsp_n,vsp_m;
		vsp_n = size_n - r;
		vsp_m = size_m;
		double Rd;
		int bs_cur_n,bs_cur_m;
		int block_size_n,block_size_m;
		int block_kol = (int)((size_n - r)/(block_size));
		if (((size_n - r)%(block_size))!=0) block_kol++;
		block_size_n = block_size;
		block_size_m = (int)(size_m / (block_kol));
		Matrix_Block_Param->block_kol=0;
		while ((vsp_n > block_size_n)&&(vsp_m > block_size_m ))
		{
			Rd = (((double) rand()) /(double) RAND_MAX);
			bs_cur_n = (int)(Rd*block_size_n);
			Rd = (((double) rand()) /(double) RAND_MAX);
			bs_cur_m = (int)(Rd*block_size_m);
			if ((bs_cur_n!=0)&&(bs_cur_m!=0))
			{
				Add_Elem_To_Matrix_Block_Param(bs_cur_n ,bs_cur_m); 
				vsp_n = vsp_n -bs_cur_n;
				vsp_m = vsp_m -bs_cur_m;
			}
		}
		if ((vsp_n!=0)&&(vsp_m!=0))
			Add_Elem_To_Matrix_Block_Param(vsp_n ,vsp_m); 
	}
	else
	{	
	//-----------------------------------------------------------------------
	block_kol = (int)((size_n - r)/(block_size));//количество целых блоков
	Matrix_Block_Param->block_kol=block_kol;

	if ( (size_n - r)%(block_size)!= 0)//остался один не полный блок
	{
		m_size = (int)(size_m / (block_kol+1));//размер блока в строчках 
		n_size_last = (size_n - r)%(block_size);
		m_size_last = size_m - m_size*(block_kol);//(size_m) % (block_kol+1);
		Matrix_Block_Param->block_kol++;
		block_kol++;
	}
	else
	{
	  if (block_kol!=0)
	  {
		  m_size = (int)(size_m / block_kol);//размер блока в строчках
	     if (size_m % block_kol !=0)
	     {
		  m_size_last =size_m % block_kol;
	      n_size_last=0;
	     }
	  }
	}
	//------------------------------------------------------------------------
	
	Matrix_Block_Param->Blocks = new Block_size[block_kol];
	if ((n_size_last!=0)&&(m_size_last!=0))
	{
		for(i=0; i<block_kol-1; i++)
		{
           Matrix_Block_Param->Blocks[i].n_size = n_size;
		   Matrix_Block_Param->Blocks[i].m_size = m_size;
		}
		Matrix_Block_Param->Blocks[block_kol-1].n_size = n_size_last;
		Matrix_Block_Param->Blocks[block_kol-1].m_size = m_size_last;
 	}
	else
	{
		if  ((m_size_last!=0)&&(n_size_last==0))
		{
		   for(i=0; i<block_kol-1; i++)
		   {
            Matrix_Block_Param->Blocks[i].n_size = n_size;
		    Matrix_Block_Param->Blocks[i].m_size = m_size;
		   }
		   Matrix_Block_Param->Blocks[block_kol-1].n_size = n_size;
		   Matrix_Block_Param->Blocks[block_kol-1].m_size = m_size+m_size_last;
		}
		else
		{
		  for(i=0; i<block_kol; i++)
	 	  { 
           Matrix_Block_Param->Blocks[i].n_size = n_size;
		   Matrix_Block_Param->Blocks[i].m_size = m_size;
		  }
		}
	}
	}
    //------------------------------------------------------------------------
	int j_1,i_1;

	for (int k=0; k< Matrix_Block_Param->block_kol; k++)
	{
		n_size= Matrix_Block_Param->Blocks[k].n_size; 
		m_size= Matrix_Block_Param->Blocks[k].m_size; 
		
		Packing_Problem* vsp;
		vsp=new Packing_Problem(n_size,m_size,p);
        
		i_1=k*m_size;
		j_1=r+k*n_size;
        int sum=0;
		   for (j=0; j<k; j++) 
			   sum = sum + Matrix_Block_Param->Blocks[j].n_size;
		   j_1 = r + sum;
		   sum=0;
		   for (j=0; j<k; j++) 
			   sum = sum + Matrix_Block_Param->Blocks[j].m_size;
		   i_1=sum;
			
        for (i=0; i<m_size; i++)
			for(j=0; j<n_size; j++)
			{
			    A[i_1+i][j_1+j] = vsp->A[i][j];
			}
		//delete vsp;
	}
  /*cout<<A;	
  cout<<"r = "<<Matrix_Block_Param->r<<endl;
  cout<<"kol = "<<Matrix_Block_Param->block_kol<<endl;;
  for(i=0; i<Matrix_Block_Param->block_kol; i++)
  {
	  cout<<endl;
      cout<<"n= "<< Matrix_Block_Param->Blocks[i].n_size<<" ";
	  cout<<"m= "<< Matrix_Block_Param->Blocks[i].m_size;
  }
  cout<<endl;*/
}

Packing_Problem::Packing_Problem(matrix<bool> &matrx)
{
	size_n=matrx.ret_w();
	size_m=matrx.ret_h();
	A = matrix<bool>(size_n,size_m);
	for(int i=0; i<size_m; i++)
		for (int j=0;j<size_n;j++)
		   A [i][j]=matrx[i][j];
    res_n=size_n+1;
	res_m=size_n+size_m+2;
	matr = matrix<double>(res_n,res_m);
	shuffle=0;
	flag_shuffle=false;
	Matrix_Block_Param=0;
}

void Packing_Problem::Read_MIS_From_File(char* FileName)
{
 //Считывает из файла специального вида,в матрицу задачи упаковки,соответствующей задаче о максим.нез.множестве
 //Вид файла
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
	int Number_Edge,size;

	InFile.open(FileName,ios::_Nocreate);
	if (!InFile) {cerr<<"Not existing file!";InFile.close(); return;} else
	{
		//узнать 1 число и создать матрицу такого размера
		//узнать 2 число и по нему будет второй цикл
		InFile.getline(str,100);
		int i=0;
			str1 =  new char[10];
		while ((int(str[i])<48)||(int(str[i])>57)) i++;
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
	    //----
		//cout<<size;
		//----------------------------
		
		//----------------------------
        str1 =  new char[10];
		while ((int(str[i])<48)||(int(str[i])>57))
		i++;
		j=0;
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
        	delete[] str1;
		//------------------ Создание матрицы---------------
		size_n=size;
		size_m=Number_Edge;
		A = matrix<bool>(size_n,size_m);
		for(int l=0;l<size_n; l++) 
		  for(int p=0;p<size_m; p++) 
		    A[p][l]=0;
		int Decimals=5;//точность для перебора l-классов;
       //---------------------------------------------------

	   for ( int l=0; l<Number_Edge;l++)
	   { 
		   //считать 1 цифру 2 цифру и в матрицу записать на это место 1
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
		 while ((int(str[i])<48)||(int(str[i])>57)) i++;
		 j=0;
		 	str1 =  new char[10];
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
		A[l][first-1]=1;
		A[l][second-1]=1;
  
	}// for ( int l=0; l<Number_Edge;l++)
	   InFile.close();
}//if
	

}

void Packing_Problem::Read_MSP_From_File(char* FileName)
{
	/*
	There is a line with the form "p set U S",
	where U and S are  respectively the number of elements in the universe (denoted by natural numbers) and the number of subsets in the collection. 
    The remaining of the file is a list of lines starting with s which 
	indicate the subsets in the collection (e.g. the line
	"s 1 2 4" indicates that there is a subset with three elements which are 1, 2 and 4).
	*/
	
	ifstream InFile;
	char* str,*str1;
	str = new char[1000];
	
	int Number_Sets,size;
	
	InFile.open(FileName,ios::_Nocreate);
	if (!InFile) {cerr<<"Нет такого файла!"; InFile.close(); return;} else
	{
		//узнать 1 число и создать матрицу такого размера
		//узнать 2 число и по нему будет второй цикл
		InFile.getline(str,1000);
		str1 =  new char[10];
		int i=0;
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
		//----------------------------
		
		//----------------------------

		str1 =  new char[10];
		for(int l=0;l<10; l++)
	       str1[l]=' ';
		
		while ((int(str[i])<48)||(int(str[i])>57))
		i++;
		j=0;
		
		while ((int(str[i])>=48)&&(int(str[i])<=57))
		{ str1[j]=str[i]; j++; i++; }
		str1[j]='\0';
		k=0;
		while ((int(str1[k])>=48)&&(int(str1[k])<=57)) k++;
		Number_Sets=0;
		Number_Sets=str1[k-1]-48;
		for (j=1;j<k;j++) 
		{   
			int deg=1;
			for (int h=1;h<=j;h++) {deg = deg*10;}
			Number_Sets=Number_Sets+(str1[k-j-1]-48)*deg;
		} 
        delete[] str1;
		//------------------ Создание матрицы---------------
		
		size_n=Number_Sets;
		size_m=size;
		A = matrix<bool>(size_n,size_m);
		//cout<<size_n<<" "<<size_m<<endl;
		for(int l=0;l<size_n; l++) 
		  for(int p=0;p<size_m; p++) 
		    A[p][l]=0;
		Decimals=5;//точность для перебора l-классов;
	    //---------------------------------------------------

	   for ( int l=0; l<Number_Sets;l++)
	   { 
		   //считать 1 цифру 2 цифру и в матрицу записать на это место 1
		   InFile.getline(str,1000);
		   int i=0;
		   
		   while(i<strlen(str))
		   {
				   ////////
			   	 str1 =  new char[10];
			     for(int tmp=0;tmp<10; tmp++)
				 	  str1[tmp]=' ';
				 			 
				  while (((int(str[i])<48)||(int(str[i])>57))&&(i<strlen(str))) i++;
				  if (i==strlen(str)) break;
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
				  A[first-1][l]=1;
		   }//while
  	}// for ( int l=0; l<Number_Sets;l++)
	 //cout<<"File is successfully read!";
	//cout<<A;
	  InFile.close();
	}//if
	 

}

void Packing_Problem::Read_MSP_BLOCK_From_File(char* FileName)
{
	/*
	There is a line with the form "p set U S",
	where U and S are  respectively the number of elements in the universe (denoted by natural numbers) and the number of subsets in the collection. 
    The remaining of the file is a list of lines starting with s which 
	indicate the subsets in the collection (e.g. the line
	"s 1 2 4" indicates that there is a subset with three elements which are 1, 2 and 4).
	p set m n r block_kol size_n size_m...
	*/
	
	ifstream InFile;
	char* str,*str1;
	str = new char[1000];
	
	int Number_Sets,size,r,block_kol,m_size,n_size;
	
	InFile.open(FileName,ios::_Nocreate);
	if (!InFile) {cerr<<"Нет такого файла!"; InFile.close(); return;} else
	{
		//узнать 1 число и создать матрицу такого размера
		//узнать 2 число и по нему будет второй цикл
		InFile.getline(str,1000);
		str1 =  new char[10];
		int i=0;
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
		//cout<<"elements"<<size;
		//----------------------------
		
		//----------------------------

		str1 =  new char[10];
		for(int l=0;l<10; l++)
	       str1[l]=' ';
		
		while ((int(str[i])<48)||(int(str[i])>57))
		i++;
		j=0;
		
		while ((int(str[i])>=48)&&(int(str[i])<=57))
		{ str1[j]=str[i]; j++; i++; }
		str1[j]='\0';
		k=0;
		while ((int(str1[k])>=48)&&(int(str1[k])<=57)) k++;
		Number_Sets=0;
		Number_Sets=str1[k-1]-48;
		for (j=1;j<k;j++) 
		{   
			int deg=1;
			for (int h=1;h<=j;h++) {deg = deg*10;}
			Number_Sets=Number_Sets+(str1[k-j-1]-48)*deg;
		} 
        delete[] str1;
		//cout<<"subsets"<<Number_Sets;
        //----------число общих переменных---------
		str1 =  new char[10];
		for(int l=0;l<10; l++)
	       str1[l]=' ';
		
		while ((int(str[i])<48)||(int(str[i])>57))
		i++;
		j=0;
		
		while ((int(str[i])>=48)&&(int(str[i])<=57))
		{ str1[j]=str[i]; j++; i++; }
		str1[j]='\0';
		k=0;
		while ((int(str1[k])>=48)&&(int(str1[k])<=57)) k++;
		r=0;
		r=str1[k-1]-48;
		for (j=1;j<k;j++) 
		{   
			int deg=1;
			for (int h=1;h<=j;h++) {deg = deg*10;}
			r=r+(str1[k-j-1]-48)*deg;
		} 
        delete[] str1;
		//cout<<"comon"<<r;
        //-----------количество блоков-------------
		str1 =  new char[10];
		for(int l=0;l<10; l++)
	       str1[l]=' ';
		
		while ((int(str[i])<48)||(int(str[i])>57))
		i++;
		j=0;
		
		while ((int(str[i])>=48)&&(int(str[i])<=57))
		{ str1[j]=str[i]; j++; i++; }
		str1[j]='\0';
		k=0;
		while ((int(str1[k])>=48)&&(int(str1[k])<=57)) k++;
		block_kol=0;
		block_kol=str1[k-1]-48;
		for (j=1;j<k;j++) 
		{   
			int deg=1;
			for (int h=1;h<=j;h++) {deg = deg*10;}
			block_kol=block_kol+(str1[k-j-1]-48)*deg;
		} 
        delete[] str1;
		//cout<<"kol blockov"<<block_kol;
        //------------------ Создание матрицы---------------
		
		size_n=Number_Sets;
		size_m=size;
		A = matrix<bool>(size_n,size_m);
		//cout<<size_n<<" "<<size_m<<endl;
		for(int l=0;l<size_n; l++) 
		  for(int p=0;p<size_m; p++) 
		    A[p][l]=0;
		Matrix_Block_Param=new Block;
		Matrix_Block_Param->r=r;
		Matrix_Block_Param->block_kol=block_kol;
		Matrix_Block_Param->Blocks=new Block_size[block_kol];
		Decimals=5;//точность для перебора l-классов;
	    //---------------------------------------------------
		//---------размеры блоков---------------------------- 
		for(int l=0;l<block_kol; l++)
		{
			int vsp;

			str1 =  new char[10];
		    for(int p=0;p<10; p++) str1[p]=' ';
  		
 			while ((int(str[i])<48)||(int(str[i])>57))
			i++;
			j=0;
		
			while ((int(str[i])>=48)&&(int(str[i])<=57))
			{ str1[j]=str[i]; j++; i++; }
			str1[j]='\0';
			k=0;
			while ((int(str1[k])>=48)&&(int(str1[k])<=57)) k++;
			vsp=0;
			vsp=str1[k-1]-48;
			for (j=1;j<k;j++) 
			{   
				int deg=1;
				for (int h=1;h<=j;h++) {deg = deg*10;}
				vsp=vsp+(str1[k-j-1]-48)*deg;
			} 
			delete[] str1;
			//cout<<"m_size="<<vsp<<" ";

			Matrix_Block_Param->Blocks[l].m_size=vsp;
			
			str1 =  new char[10];
		    for(int p=0;p<10; p++) str1[p]=' ';
  		    
			//cout<<str[124]<<endl;
			//cout<<str[125]<<endl;
			//cout<<str[126]<<endl;
  			while ((int(str[i])<48)||(int(str[i])>57))
			i++;
			j=0;
		
			while ((int(str[i])>=48)&&(int(str[i])<=57))
			{ str1[j]=str[i]; j++; i++; }
			str1[j]='\0';
			k=0;
			while ((int(str1[k])>=48)&&(int(str1[k])<=57)) k++;
			vsp=0;
			vsp=str1[k-1]-48;
			for (j=1;j<k;j++) 
			{   
				int deg=1;
				for (int h=1;h<=j;h++) {deg = deg*10;}
				vsp=vsp+(str1[k-j-1]-48)*deg;
			} 
			delete[] str1;
			//cout<<"n_size="<<vsp<<" ";

			Matrix_Block_Param->Blocks[l].n_size=vsp;
     	}
 
        //----------матрица---------------------------------		  
		for ( int l=0; l<Number_Sets;l++)
		   { 
		   //считать 1 цифру 2 цифру и в матрицу записать на это место 1
		   InFile.getline(str,1000);
		   int i=0;
		   
		   while(i<strlen(str))
		   {
				   ////////
			     for(int tmp=0;tmp<10; tmp++)
				 	  str1[tmp]=' ';
				 			 
				  while (((int(str[i])<48)||(int(str[i])>57))&&(i<strlen(str))) i++;
				  if (i==strlen(str)) break;
				  int j=0;
				  while ((int(str[i])>=48)&&(int(str[i])<=57))
				  { str1[j]=str[i]; j++; i++; }
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
				 			        
				  A[first-1][l]=1;
		   }//while
  	}// for ( int l=0; l<Number_Sets;l++)
	//cout<<"File is successfully read!";
	//cout<<A;
	  InFile.close();
	}//if
	 

}

Packing_Problem::Packing_Problem(char* FileName, bool MSP,bool block)
{
	shuffle=0;
	flag_shuffle=0;
	/*if (MSP==true) Read_MSP_From_File(FileName); 
	else Read_MIS_From_File(FileName); 
	Matrix_Block_Param=0;*/
	if (MSP==true) 
	{
		if (block==true)Read_MSP_BLOCK_From_File(FileName);
		else 
		{
			Read_MSP_From_File(FileName); 
			Matrix_Block_Param=0;
		}
	}
	else 
	{
		Read_MIS_From_File(FileName); 
	    Matrix_Block_Param=0;
	}
	/*res_n=size_n+1;
	res_m=size_n+size_m+2;
	matr = matrix<double>(res_n,res_m);*/

}
bool Packing_Problem::Save_MSP_In_File(char* Filename)
{
	ofstream OutFile;

	OutFile.open(Filename);
	if (!OutFile) {cerr<<"Не могу открыть"; OutFile.close(); return 0;} 
	else
	{
     OutFile<<"p set "<<size_m<<" "<<size_n<<endl;
	 for(int i=0; i<size_n; i++)
	 {
		OutFile<<"s "; 
		for (int j=0;j<size_m;j++)
		{
          if (A[j][i]==1) OutFile<<(j+1)<<" "; 
		}
		OutFile<<endl;
	 }
	 OutFile.close();
	}
	return true;
}
bool Packing_Problem::Save_MSP_BLOCK_In_File(char* Filename)
{
	ofstream OutFile;
	OutFile.open(Filename);
	if (!OutFile) {cerr<<"Не могу открыть"; OutFile.close(); return 0;} 
	else
	{
     OutFile<<"p set "<<size_m<<" "<<size_n<<" "<<Matrix_Block_Param->r<<" "<<Matrix_Block_Param->block_kol;
	 for (int i=0; i<Matrix_Block_Param->block_kol; i++)
	 {
		 OutFile<<" ";
		 OutFile<<Matrix_Block_Param->Blocks[i].m_size<<" ";
	     OutFile<<Matrix_Block_Param->Blocks[i].n_size;
     }
	 OutFile<<endl;
	 for(int i=0; i<size_n; i++)
	 {
		OutFile<<"s "; 
		for (int j=0;j<size_m;j++)
		{
          if (A[j][i]==1) OutFile<<(j+1)<<" "; 
		}
		OutFile<<endl;
	 }
	 OutFile.close();
	}
	return true;
}

Independent_Set_Problem Packing_Problem::Get_Equivalent_MIS()
{
    //matrix<bool> GI(size_n,size_n);
	matrix<bool> GI;
	MatrixA_To_Graph_Incendence(GI);
	Independent_Set_Problem P(GI);
	//cout<<GI<<endl;
	return P;
}
//-----------------------------------------------------------------------------
int* Packing_Problem::Complete_Enumeration()
{
	int dec;
	int k;
	int j;
	bool flag;
	int rec=0;
	int sum;

	int* x=new int[size_n+1];//решение
    int* vsp=new int[size_n];
 
	int kol = (int)pow((double)2,size_n);
    for (int i=1 ; i< kol ; i++)
	{
		//------------------------------------
		//i нужно перевести в двоичную систему
		for (j=0; j<size_n; j++) vsp[j]=0;
	 	
		dec = i;
		j=0;
	     while (dec > 1)
		  {
		   k = dec/2;
		   vsp[j] = dec- k*2;
		   j++;
		   dec = k;
		  }
		vsp[j]=1;
 		//------------------------------------
        /*cout<<endl;
		cout<<i<<" = ";
		for (int t=0; t<size_n; t++) cout<<vsp[t]<<" ";*/
		//-------------------------------------
		flag=false; 
		for (int t=0; t<size_m; t++)
		{
			sum=0;
			for(j=0; j<size_n; j++)
			 sum= sum+ A[t][j]*vsp[j];
			if (sum > 1) flag=true;
		}
		//if (flag) cout<<"no"; else cout<<"yes! ";
		if (flag==false)//нашли допустимое решение
		{
			sum=0;
			for(j=0; j<size_n; j++) sum = sum+vsp[j];
			if (sum > rec) 
			{ 
				rec = sum;
			    for(j=0; j<size_n; j++) x[j+1]=vsp[j];
				x[0]=rec;
				//cout<<rec;
			}
		}
	
	}
	delete[] vsp;
	return x;
}
//------------------------------------------------------
bool Packing_Problem::Lexmax(double* x_1,double* x_2,int size)
//Проверяет больше ли первый вектор второго
{
	  double EPS=pow(10.0, -Decimals+1);
		for(int i=0; i<size; i++)
		{
			if (abs(x_1[i]-x_2[i])<EPS) continue;
			else
			if (x_1[i]>x_2[i]) return true;
			if (x_1[i]<x_2[i]) return false;
		}
		return true;
}
bool Packing_Problem::Lexmax_Vect(/*matrix<double> &matr,*/ int j, int k)
//сравнивает j и k столбец в матрице matr
{
      double EPS=pow(10.0, -Decimals+1);
		//for(int i=0; i<matr.ret_h(); i++)
	  for(int i=0; i<res_m; i++)
		{
			if (abs(matr[i][j]-matr[i][k])<EPS) continue;
			else
			{
			if (matr[i][j]-matr[i][k]>EPS) return true;
			if (matr[i][j]-matr[i][k]<-EPS) return false;
			}
		}
		return true;
}
bool Packing_Problem::Lexmax_Vect_with_zero(/*matrix<double> &matr,*/ int j)
//сравнивает j столбец в матрице matr c нулем
//истина если лексикографически больше нуля
{
      double EPS=pow(10.0, -Decimals+1);
		//for(int i=0; i<matr.ret_h(); i++)
		for(int i=0; i<res_m; i++)
		{
			if (abs(matr[i][j]-0.0)<EPS) continue;
			else
			{
			if (matr[i][j]>EPS) return true;
			if (matr[i][j]<-EPS) return false;
			}
		}
		return true;
}
int Packing_Problem::Num_First_Notzero_Coord(/*matrix<double> &matr,*/ int j)
{
	double EPS=pow(10.0, -Decimals+1);
	  //for(int i=0; i<matr.ret_w()-1; i++)
		for(int i=0; i<res_n-1; i++)
		{
			if (abs(matr[i][j]-0.0)<EPS) continue;
			return i;			
		}
	return -1;
}

bool Packing_Problem::Check_L_Norm(/*matrix<double> &matr*/)
{
	//for(int j=0; j<matr.ret_w(); j++)
	 // if (Lexmax_Vect_with_zero(matr,j)==false)
	 for(int j=0; j<res_n; j++)
	  if (Lexmax_Vect_with_zero(/*matr,*/j)==false)
	    return false;
	 return true;
}

void Packing_Problem:: Make_L_Norm(/*matrix<double> &matr*/)
{
	int M=size_n;
	//int M=res_n-1;;

	int q=0;
	//cout<<"Print before Make L- norm"<<matr;
	if (Check_L_Norm(/*matr*/)==false)
	{
		//matr[matr.ret_h()-1][0]=M;
		//for(int j=1; j<matr.ret_w(); j++)
		//	matr[matr.ret_h()-1][j]=1.0;
	
		matr[res_m-1][0]=M;
		for(int j=1; j<res_n; j++)
			matr[res_m-1][j]=1.0;
	
		//for(int j=1; j<matr.ret_w();j++)
    	//	if (Lexmax_Vect_with_zero(matr,j)==false)//лексикографически меньше 0
	     //   {
		//	   if (q==0) q=j; else if (Lexmax_Vect(matr,q,j)) q=j; 
		  //  }
			//cout<<"Main Line "<<(matr.ret_h()-1)<<endl;
			//cout<<"Main col "<<q<<endl;
			//Preobrazovanie_Matrix(matr,(matr.ret_h()-1),q);
			//cout<<"After make L-norm"<<matr;	  
		
		for(int j=1; j<res_n;j++)
    		if (Lexmax_Vect_with_zero(/*matr,*/j)==false)//лексикографически меньше 0
	        {
			   if (q==0) q=j; else if (Lexmax_Vect(/*matr,*/q,j)) q=j; 
		    }
			//cout<<"Main Line "<<(matr.ret_h()-1)<<endl;
			//cout<<"Main col "<<q<<endl;
			Preobrazovanie_Matrix(/*matr,*/(res_m-1),q);
			//cout<<"After make L-norm"<<matr;	  
	}//if
}

int Packing_Problem::Check_L_Opim(/*matrix<double> &matr*/)
//проверяем является ли таблица прямодопустимой, если нет то возвращеться 
//номер строки в которой допустимость нарушается, то есть номер след.вед.строки
{
	double EPS=pow(10.0, -Decimals+1);
	int main_row=-1;
	double vsp=0.0;
	
	/*for(int i=1;i<(matr.ret_h()-1);i++)
	{
	//	cout<<matr;
		if (matr[i][0]<-EPS) return i;
	}
	return -1;
	*/
	/*for(int i=1;i<(matr.ret_h()-1);i++)
	{
		if ((matr[i][0]<-EPS) && (matr[i][0]<vsp))
		{
			main_row=i;
            vsp=matr[i][0];
		}
	}*/
	for(int i=1;i<(res_m-1);i++)
	{
		if ((matr[i][0]<-EPS) && (matr[i][0]<vsp))
		{
			main_row=i;
            vsp=matr[i][0];
		}
	}
	return main_row;
	
}
int Packing_Problem::Select_main_column(/*matrix<double> &matr,*/int main_line)
//ищем номер ведущего столбца
{
	int result=0;
	int k;
	double EPS=pow(10.0, -Decimals+1);

	/*for(int j=1; j<matr.ret_w();j++)
	{
       if (matr[main_line][j]<-EPS) 
	   {
		   if (result==0) result=j;
			   else 
			   {
				   k=j;
	               bool flag=false;
				   for(int i=0; i<matr.ret_h(); i++)
					{
						if (flag==false)
						{
							double temp=matr[main_line][j];
							double temp_2=matr[main_line][result];
							if (abs(matr[i][k]/temp-matr[i][result]/temp_2)<EPS) continue;
							else
							 if (matr[i][k]/temp > matr[i][result]/temp_2) 	 result=k;
							flag=true;
										 
						}
					}
			
			   }
	   }//if
	}//for*/
	
	for(int j=1; j<res_n;j++)
	{
       if (matr[main_line][j]<-EPS) 
	   {
		   if (result==0) result=j;
			   else 
			   {
				   k=j;
	               bool flag=false;
				   for(int i=0; i<res_m; i++)
					{
						if (flag==false)
						{
							double temp=matr[main_line][j];
							double temp_2=matr[main_line][result];
							if (abs(matr[i][k]/temp-matr[i][result]/temp_2)<EPS) continue;
							else
							 if (matr[i][k]/temp > matr[i][result]/temp_2) 	 result=k;
							flag=true;
										 
						}
					}
			
			   }
	   }//if
	}//for
			   
return result;
}
void Packing_Problem::Preobrazovanie_Matrix(/*matrix<double> &matr,*/int p,int q)
//Одно преобразование симплексной таблицы
{
	int i,j;
	double EPS=pow(10.0, -Decimals+1);

	/*for (i=0; i<matr.ret_h(); i++)
	{
		for (j=0; j<matr.ret_w(); j++)
		{
			if ((i!=p)&&(j!=q)) matr[i][j]=matr[i][j]-matr[i][q]*matr[p][j]/matr[p][q];
		}
	}*/ 
   
	/*for (j=0; j<matr.ret_w(); j++)
	{
	  //if (fabs(matr[p][j])<EPS) continue;
	  //if ((matr[p][j]>-EPS)&& (matr[p][j]<EPS)) continue;
	  //if (matr[p][j]==0.0) continue;
	  for (i=0; i<matr.ret_h(); i++)
	    {
			//if (fabs(matr[p][j])<EPS) continue;
			///if (matr[i][q]==0.0) continue;
			//if ((matr[i][q]>-EPS)&& (matr[i][q]<EPS)) continue;
			if ((i!=p)&&(j!=q)) matr[i][j]=matr[i][j]-matr[i][q]*matr[p][j]/matr[p][q];
		}
	}
	for (i=0; i<matr.ret_h(); i++)
	  if (i!=p) matr[i][q]=-matr[i][q]/matr[p][q];
	for (j=0; j<matr.ret_w(); j++)
		if (j!=q) matr[p][j]=0.0;
	matr[p][q]=-1;*/
	
	for (j=0; j<res_n; j++)
	{
	  //if (fabs(matr[p][j])<EPS) continue;
	  //if ((matr[p][j]>-EPS)&& (matr[p][j]<EPS)) continue;
	  if (matr[p][j]==0.0) continue;
	  for (i=0; i<res_m; i++)
	    {
			//if (fabs(matr[p][j])<EPS) continue;
			if (matr[i][q]==0.0) continue;
			//if ((matr[i][q]>-EPS)&& (matr[i][q]<EPS)) continue;
			if ((i!=p)&&(j!=q)) matr[i][j]=matr[i][j]-matr[i][q]*matr[p][j]/matr[p][q];
		}
	}
	for (i=0; i<res_m; i++)
	  if (i!=p) matr[i][q]=-matr[i][q]/matr[p][q];
	for (j=0; j<res_n; j++)
		if (j!=q) matr[p][j]=0.0;
	matr[p][q]=-1;
	
}

//-------------------------------------------------------
double* Packing_Problem::LEXMAX_M()
//ЛДСМ без цел.функии
{
	int i,j;
	double EPS=pow(10.0, -Decimals+1);
	//matrix<double> matr(size_n+1,size_n+size_m+1);
	res_n=size_n+1;
    res_m=size_n+size_m+1;
	for(i=0;i<res_m;i++)
		for(j=0;j<res_n;j++) matr[i][j]=0;
    //-----------------заполняем начальную таблицу-----------------------
	//matr[0][0]=0;
	//for (j=1; j<size_n+1; j++) matr[0][j]=-1;
	for(i=0; i<size_n; i++)
		{
			matr[i][0]=0;
			for (j=1; j<size_n+1; j++)
              if (i+1==j)	matr[i][j]=-1; else matr[i][j]=0; 
			
		}
	for(i=size_n; i<size_n+size_m; i++)
		{
			for (j=0; j<size_n+1; j++)
              if (j==0)	matr[i][j]=1; else matr[i][j]= A[i-size_n][j-1]; 
			
		}
    for (j=0; j<size_n+1; j++) matr[size_n+size_m][j]=0;
	//------------------------------------------------------------------
    // В общем случае надо проверить чтобы начальная таблица была двойственно допустимой
	//то есть чтобы все столбцы были lex больше 0;
    //cout<<matr;
	Make_L_Norm(/*matr*/);
    //cout<<matr;
	int p;//номер ведущей строки
	int q;//номер ведущего столбца

	while (true)
	{
	  p=Check_L_Opim(/*matr*/);
	  if (p==-1)//нашли решение
	  {	
	     double* x;
	     x=new double[size_n];//нету значение ц.ф
	     for(int i=0; i<size_n; i++)
		 	 x[i]=matr[i][0];
		
		 // for(int i=0; i<size_n; i++)
	    // cout<<x[i]<<" ";
		//  cout<<matr;
	     return x;
      }
	  //проверка разрешимости !!!!! переделать! неверно!
	  bool flag=0;
	  for(j=1;j<size_n+1;j++)
		 if (matr[p][j]<-EPS) flag=1;
	
	  if (flag==1)
		 {
	       //ищем номер ведущего столбца
		   q = Select_main_column(/*matr,*/p);
		   //выполняем преобразование таблицы
		   //cout<<"Main line "<<p<<endl;
	       //cout<<"Main col "<<q<<endl;
		   Preobrazovanie_Matrix(/*matr,*/p,q);
		   //cout<<matr;
		 }
		 else//то есть matr[p][j]>=0 то задача не разрешима
			 return 0;
	}
		
	//return 0;
}
double* Packing_Problem::LEXMAX_M_WITH_INFO(int &row_number)
//ЛДСМ без цел.функии выдает информацию из оптимальной симплексной таблицы
{
	int i,j;
	double EPS=pow(10.0, -Decimals+1);
	//matrix<double> matr(size_n+1,size_n+size_m+1);
	res_n=size_n+1;
	res_m=size_n+size_m+1;
	for(i=0;i<res_m;i++)
		for(j=0;j<res_n;j++) matr[i][j]=0;
    

	row_number = size_n;
    //-----------------заполняем начальную таблицу-----------------------
	
	for(i=0; i<size_n; i++)
		{
			matr[i][0]=0;
			for (j=1; j<size_n+1; j++)
              if (i+1==j)	matr[i][j]=-1; else matr[i][j]=0; 
			
		}
	for(i=size_n; i<size_n+size_m; i++)
		{
			for (j=0; j<size_n+1; j++)
              if (j==0)	matr[i][j]=1; else matr[i][j]= A[i-size_n][j-1]; 
			
		}
    for (j=0; j<size_n+1; j++) matr[size_n+size_m][j]=0;
	//------------------------------------------------------------------
    // В общем случае надо проверить чтобы начальная таблица была двойственно допустимой
	//то есть чтобы все столбцы были lex больше 0;

	Make_L_Norm(/*matr*/);
    //cout<<matr;
	int p;//номер ведущей строки
	int q;//номер ведущего столбца

	while (true)
	{
	  p=Check_L_Opim(/*matr*/);
	  if (p==-1)//нашли решение
	  {	
	     double* x;
	     x=new double[size_n];//нету значение ц.ф
	     for(int i=0; i<size_n; i++)
	     x[i]=matr[i][0];
         //------------------------
         // Попытка использовать информацию из оптимальной таблицы
		 int max=0;
		 int vsp;
		 for (int t=1; t < /*matr.ret_w()*/res_n; t++)
		 {
			 vsp =  Num_First_Notzero_Coord(/*matr,*/t);
		     if ((vsp!=-1) &&(vsp > max)) max = vsp;
		 }
		 for(int i=max; i</*matr.ret_w()*/ res_n; i++)
		 {
			  if (Round(matr[i][0],Decimals)==1.0) 
			  {
				  row_number = i;
				  break;
			  }
		 }
         //------------------------
		 //cout<<matr;
		 //cout<<row_number;
	     return x;
      }
	  //проверка разрешимости !!!!! переделать! неверно!
	   bool flag=0;
	  for(j=1;j<size_n+1;j++)
		 if (matr[p][j]<-EPS) flag=1;
	
	  if (flag==1)
		 {
	       //ищем номер ведущего столбца
		   q = Select_main_column(/*matr,*/p);
		   //выполняем преобразование таблицы
		   //cout<<"Main line "<<p<<endl;
	       //cout<<"Main col "<<q<<endl;
		   Preobrazovanie_Matrix(/*matr,*/p,q);
		   //cout<<matr;
		 }
		 else//то есть matr[p][j]>=0 то задача не разрешима
			 return 0;
	}
	
	return 0;
}
double* Packing_Problem::LDSM()
//Решение задачи ЛП на максимум целев.ункции
{
	int i,j;
	double EPS=pow(10.0, -Decimals+1);
	
	//matrix<double> matr(size_n+1,size_n+size_m+2);
	res_n=size_n+1;
	res_m=size_n+size_m+2;
	for(i=0;i<res_m;i++)
		for(j=0;j<res_n;j++) matr[i][j]=0;
    	
	//-----------------заполняем начальную таблицу-----------------------
	matr[0][0]=0;
	for (j=1; j<size_n+1; j++) matr[0][j]=-1;
	for(i=1; i<=size_n; i++)
		{
			for (j=0; j<size_n+1; j++)
              if (i==j)	matr[i][j]=-1; else matr[i][j]=0; 
			
		}
	/*for(j=size_n+1; j<=size_n+size_m; j++) matr[j][0]=1;
	for(i=size_n+1; i<=size_n+size_m; i++)
		{
			for (j=1; j<size_n+1; j++)
              if ((i-size_n)==j)	matr[i][j]=1; else matr[i][j]=0; 
			
		}*/
	for(i=size_n+1; i<size_n+size_m+1; i++)
		{
			for (j=0; j<size_n+1; j++)
              if (j==0)	matr[i][j]=1; else matr[i][j]= A[i-size_n-1][j-1]; 
			
		}
    for (j=0; j<size_n+1; j++) matr[size_n+size_m+1][j]=0;
	//------------------------------------------------------------------
    // В общем случае надо проверить чтобы начальная таблица была двойственно допустимой
	//то есть чтобы все столбцы были lex больше 0;
	//cout<<matr;
	
	Make_L_Norm(/*matr*/);
    //cout<<matr;
	int p;//номер ведущей строки
	int q;//номер ведущего столбца

	while (true)
	{
	  p=Check_L_Opim(/*matr*/);
	  if (p==-1)//нашли решение
	  {	
	     double* x;
	     x=new double[size_n+1];//x0=значение ц.ф
	     for(int i=0; i<size_n+1; i++)
	     x[i]=matr[i][0];
	     return x;
      }
	  //проверка разрешимости 
  	  bool flag=0;
	  for(j=1;j<size_n+1;j++)
		 if (matr[p][j]< -EPS) flag=1;
	
	  if (flag==1)
		 {
	       //ищем номер ведущего столбца
		   q = Select_main_column(/*matr,*/p);
		   //выполняем преобразование таблицы
		   //cout<<"Main line "<<p<<endl;
	       //cout<<"Main col "<<q<<endl;
		   Preobrazovanie_Matrix(/*matr,*/p,q);
		   //cout<<matr;
		 }
		 else//то есть matr[p][j]>=0 то задача не разрешима
			 return 0;
	}
		
	return 0;
}
double* Packing_Problem::LDSM_VSP(int rec,int d, int num, double* x_2,int number_step)
//num- это номер первой дробной координаты вектора x_2(в алгоритме обозн p)
//Function_Line шагаем мы по линиям уровня и на них перебираем L-классы, 
//или перебираем L-классы во всем множестве. от этого зависит сколько строк будет в матрице
//точнее останеться ли первай строка с целевой функцией
{
	int i,j;
	int n,m;
	int i_1,j_1,i_2,j_2;
	double EPS=pow(10.0, -Decimals+1);
	/*i_1,j_1 - для строк и столбцов исходной матрицы, значит 0<=i_1<=size_m
		0<=j_1<=size_n
	i_2,j_2 -для строк и столбцов новой строящейся матрицы, 0<=i_2<=m
		0<=j_2<=n*/
	//x[0]=x_2[0],x[1]=x_2[1],...x[num-1]=x_2[num-1],x[num]=0,остальные в таблицу на оптиум
	//число столбцов size_n-1-num, и еще 1 столбец на правые части
	n = size_n-num;   
	m = size_n-num-1+size_m+2;
	//matrix<double> matr(n,m);
	res_n=n;
	res_m=m;
	for(i=0;i<res_m;i++)
		for(j=0;j<res_n;j++) matr[i][j]=0;
    
    
    for(i_2=0; i_2 < n-1; i_2++)
	{
	  matr[i_2][0]=0;
	    for (j_2 = 1; j_2 < n; j_2++)
		 if (i_2+1==j_2)	matr[i_2][j_2]=-1; else matr[i_2][j_2]=0; 
	}
	
	for(i_2 = n-1; i_2< m-2; i_2++)
	{
		for (j_2=0; j_2 < n; j_2++)
		  if (j_2==0)	
		  {
            double s=0;
			i_1= i_2-n+1;
	        for(j_1 = 0; j_1 <num; j_1++)
			   s=s+A[i_1][j_1]*Round(x_2[j_1],Decimals);
	           
			matr[i_2][j_2]=1-s;
		  }
		  else
		  { 
		    i_1= i_2-n+1;
			j_1= j_2+num;
		    matr[i_2][j_2]= A[i_1][j_1]; 
		  }
	}
	for (j_2=0; j_2<n; j_2++) 
	{
	  if (j_2==0) 
	  {   
	    int tmp=0;
		 for(int t=0; t<num; t++)
			tmp=tmp+Round(x_2[t],Decimals);
		 matr[m-2][0]=-(rec+d)+tmp;
	  }
	  else matr[m-2][j_2]=-1;
	}
    for (j_2=0; j_2<n; j_2++) matr[m-1][j_2]=0;
	//cout<<matr;
	
	//------------------------------------------------------------------
    // В общем случае надо проверить чтобы начальная таблица была двойственно допустимой
	//то есть чтобы все столбцы были lex больше 0;
	
	//чиcло переменных n-num+1, num-1 переменная фиксированная ее в конце надо скопировать
	//из x_2
	//cout<<matr;
	Make_L_Norm(/*matr*/);
    

	int p;//номер ведущей строки
	int q;//номер ведущего столбца
    int u=0;
	while (true)
	{
	  p=Check_L_Opim(/*matr*/);
	  if (p==-1)//нашли решение
	  {	
	     double* x;
	     x=new double[/*matr.ret_w()-1*/res_n-1];
	     for(int i=0; i</*matr.ret_w()-1*/res_n-1; i++)
	     x[i]=matr[i][0];
	     
		 double* tmp=new double[size_n];
		 for (int t=0; t<num; t++) tmp[t]=x_2[t];
		 tmp[num]=0;
		 for (int t=num+1; t<size_n; t++) tmp[t]=x[t-num-1];
		 return tmp;
		 //return x;
      }
	  //проверка разрешимости !!!!! 
	  bool flag=0;
	  for(j=1;j</*matr.ret_w()*/res_n;j++)
	  {
		  if (matr[p][j]<-EPS) flag=1;
	  }
	  
	  if (flag==1)
		 {
	       //ищем номер ведущего столбца
		   q = Select_main_column(/*matr,*/p);
		   //выполняем преобразование таблицы
		   //cout<<"Main line "<<p<<endl;
	       //cout<<"Main col "<<q<<endl;
		   Preobrazovanie_Matrix(/*matr,*/p,q);
		   //cout<<matr;
		 }
		 else//то есть matr[p][j]>=0 то задача не разрешима
			 return 0;
	}
		
	return 0;
}
double* Packing_Problem::LDSM_VSP_SECOND(int rec,int d, int num, double* x_2,bool* arr_inc,int number_step)
//num- это номер первой дробной координаты вектора x_2(в алгоритме обозн p)
//Function_Line шагаем мы по линиям уровня и на них перебираем L-классы, 
//или перебираем L-классы во всем множестве. от этого зависит сколько строк будет в матрице
//точнее останеться ли первай строка с целевой функцией
{
	int i,j;
	int n,m;
	int i_1,j_1,i_2,j_2;
	int j_1_1=0;
	double EPS=pow(10.0, -Decimals+1);
	/*i_1,j_1 - для строк и столбцов исходной матрицы, значит 0<=i_1<=size_m
		0<=j_1<=size_n
	i_2,j_2 -для строк и столбцов новой строящейся матрицы, 0<=i_2<=m
		0<=j_2<=n*/
	//x[0]=x_2[0],x[1]=x_2[1],...x[num-1]=x_2[num-1],x[num]=0,остальные в таблицу на оптиум
	//число столбцов size_n-1-num, и еще 1 столбец на правые части
	//matrix<double> matr;

	int len=0;//количество фиксированных координат
	for (int i=num+1; i<size_n; i++) if (arr_inc[i]==0) len++;
			
	n = size_n-num-len;   //количество оптимизируемых координат
	m = size_n-num-1+size_m+2-len;
	if (n==1) return 0;
	//matr = matrix<double>(n,m);
	res_m=m;
	res_n=n;
	for(i=0;i<res_m;i++)
		for(j=0;j<res_n;j++) matr[i][j]=0;
    

    for(i_2=0; i_2 < n-1; i_2++)
			{
			  matr[i_2][0]=0;
				for (j_2 = 1; j_2 < n; j_2++)
				 if (i_2+1==j_2)
					 matr[i_2][j_2]=-1; else matr[i_2][j_2]=0; 
			}
			
			for(i_2 = n-1; i_2< m-2; i_2++)
			{
			   double s=0;
			   i_1= i_2-n+1;
			   for(j_1 = 0; j_1 <num; j_1++)
				   s=s+A[i_1][j_1]*Round(x_2[j_1],Decimals);
			   matr[i_2][0]=1-s;
			}
			
			int j_start=num;
            for (j_2=1; j_2 < n; j_2++)
			{
			   j_1_1=1;
			   while (arr_inc[j_start+j_1_1]==0) j_1_1++;
			   j_1=j_start +j_1_1;
			   j_start=j_1;
			   for(i_2 = n-1; i_2< m-2; i_2++)
			   {
				   i_1=i_2-n+1;
				   matr[i_2][j_2]=A[i_1][j_1];
			   }
			 
			}
		
		
			for (j_2=0; j_2<n; j_2++) 
			{
			  if (j_2==0) 
			  {   
				int tmp=0;
				 for(int t=0; t<num; t++)
					tmp=tmp+Round(x_2[t],Decimals);
			
				 matr[m-2][0]=-(rec+d)+tmp;
			  }
			  else matr[m-2][j_2]=-1;
			}
			for (j_2=0; j_2<n; j_2++) matr[m-1][j_2]=0;

	//cout<<matr;
	
	//------------------------------------------------------------------
    // В общем случае надо проверить чтобы начальная таблица была двойственно допустимой
	//то есть чтобы все столбцы были lex больше 0;
	
	//чиcло переменных n-num+1, num-1 переменная фиксированная ее в конце надо скопировать
	//из x_2
	//cout<<matr;
	Make_L_Norm(/*matr*/);
    

	int p;//номер ведущей строки
	int q;//номер ведущего столбца

	while (true)
	{
	  p=Check_L_Opim(/*matr*/);
	  if (p==-1)//нашли решение
	  {	
	     double* x;
	     x=new double[/*matr.ret_w()-1*/res_n-1];
	     for(int i=0; i</*matr.ret_w()-1*/res_n-1; i++)
	     x[i]=matr[i][0];
	     
		 double* tmp=new double[size_n];
		 for (int t=0; t<num; t++) tmp[t]=x_2[t];
		 tmp[num]=0;
		 
		 int r=0;
		 for (int t=num+1; t<size_n; t++) //tmp[t]=x[t-num-1];
		 {
			 if (arr_inc[t]==0) tmp[t]=0.0;
			 else 
			 {
				 tmp[t]=x[r];
				 r++;
			 }
		 
		 }
		 return tmp;
		 //return x;
      }
	  //проверка разрешимости !!!!! 
	  bool flag=0;
	  for(j=1;j</*matr.ret_w()*/res_n;j++)
	  {
		  if (matr[p][j]<-EPS) flag=1;
	  }
	  
	  if (flag==1)
		 {
	       //ищем номер ведущего столбца
		   q = Select_main_column(/*matr,*/p);
		   //выполняем преобразование таблицы
		   //cout<<"Main line "<<p<<endl;
	       //cout<<"Main col "<<q<<endl;
		   Preobrazovanie_Matrix(/*matr,*/p,q);
		   //cout<<matr;
		 }
		 else//то есть matr[p][j]>=0 то задача не разрешима
			 return 0;
	}
		
	return 0;
}
double* Packing_Problem::LDSM_VSP_FULL(int rec,int d, int num, double* x_2,bool* arr_inc,int number_step, int& row_number)
//num- это номер первой дробной координаты вектора x_2(в алгоритме обозн p)
//если arr_inc == 0 значит занулять переменные не надо
{
	int i,j;
	int n,m;
	int i_1,j_1,i_2,j_2;
	int j_1_1=0;
	int i_1_1=0;
	double EPS=pow(10.0, -Decimals+1);
	//i_1,j_1 - для строк и столбцов исходной матрицы, значит 0<=i_1<=size_m
	//	0<=j_1<=size_n
	//i_2,j_2 -для строк и столбцов новой строящейся матрицы, 0<=i_2<=m
	//	0<=j_2<=n
	//x[0]=x_2[0],x[1]=x_2[1],...x[num-1]=x_2[num-1],x[num]=0,остальные в таблицу на оптиум
	//число столбцов size_n-1-num, и еще 1 столбец на правые части
	row_number=size_n;
	//matrix<double> matr;
	
		
	if (arr_inc!=0)
	{
			int len=0;//количество фиксированных координат
			for (int i=num+1; i<size_n; i++) 
				if (arr_inc[i]==0) len++;
			
			int len_m=0;
			int* B= new int[size_m];
			for (i=0; i<size_m; i++) B[i]=1;
		
			/*for(j=0; j<num; j++)
			{
				if (x_2[j]==1)
				{
					for (i=0; i<size_m; i++)
					  if (A[i][j]==1) { B[i]=0; len_m++;}
         		}
			}*/
			for(i=0; i<size_m; i++)
			{
				bool flag=false;
				for (j=num+1; j<size_n; j++)
						if ((A[i][j]==1)&&(arr_inc[j]!=0)) flag=true;
		        if (flag==false)
				{
				B[i]=0; 
				len_m++;
				}
			}
			//for(i = 0; i< size_m; i++) cout<<B[i]<<" ";
			//cout<<endl;
		
			n = size_n-num-len;   //количество оптимизируемых координат
			//m = size_n-num-len-1+size_m+2;
			m = size_n-num-len-1+size_m-len_m+2;
			if (n==1) return 0;

			res_n=n;
	        res_m=m;
			for(i=0;i<res_m;i++)
	    	for(j=0;j<res_n;j++) matr[i][j]=0;
            //matr = matrix<double>(n,m);
					    
			///-----------
			unsigned *pIndex=new unsigned[n-1];
			
			for (j_2=0,j_1=num+1; j_2<n-1; j_1++, j_2++)
			{
				for(;arr_inc[j_1]==0; j_1++);
				pIndex[j_2]=j_1;
			}
			//cout<<num<<" ";
			//for (i=0; i<n-1; i++) cout<<pIndex[i]<<" ";

			for(i_2=0; i_2<n-1; i_2++)
			{
				memset((void*)matr[i_2],0,n*sizeof(double));
				matr[i_2][i_2+1]=-1.0;
			}
			
			for(i_1=0; i_2<m-2; i_1++, i_2++)
			{
				//for(; B[i_1]==0; i_1++);
				while (B[i_1]==0) i_1++;
				double *pmatrRow=matr[i_2];
				const bool *pARow=A[i_1];
				pmatrRow[0]=1.0;
				for(j_2=1; j_2<n; j_2++)
					pmatrRow[j_2]=pARow[pIndex[j_2-1]];
			}
			delete[] pIndex;

			//------------
			/*for(i_2=0; i_2 < n-1; i_2++)
			{
			  matr[i_2][0]=0;
				for (j_2 = 1; j_2 < n; j_2++)
				 if (i_2+1==j_2)	matr[i_2][j_2]=-1; else matr[i_2][j_2]=0; 
			}
			
			for(i_2 = n-1; i_2< m-2; i_2++)
			{
			
			   matr[i_2][0]=1;
			}
			
			int j_start=num;
            for (j_2=1; j_2 < n; j_2++)
			{
			   j_1_1=1;
			   while (arr_inc[j_start+j_1_1]==0) j_1_1++;
			   j_1=j_start +j_1_1;
			   j_start=j_1;
			   
			   int i_start=0;
			   for(i_2 = n-1; i_2< m-2; i_2++)
			   {
				   i_1_1=0;
				   while (B[i_start+i_1_1]==0) i_1_1++;
				   i_1=i_start +i_1_1;
				   i_start=i_1+1;
                   //i_1=i_2-n+1+i_1;
				   matr[i_2][j_2]=A[i_1][j_1];
			   }
		    }*/
			
			for (j_2=0; j_2<n; j_2++) 
			{
			  if (j_2==0) 
			  {   
				int tmp=0;
				 for(int t=0; t<num; t++)
					tmp=tmp+Round(x_2[t],Decimals);
				 
				 //for(int t=num+1; t<size_n; t++)
					//if (arr_inc[t]==0) tmp=tmp+Round(x_2[t],8);

				 matr[m-2][0]=-(rec+d)+tmp;
			  }
			  else matr[m-2][j_2]=-1;
			}
			for (j_2=0; j_2<n; j_2++) matr[m-1][j_2]=0;
			//cout<<matr;
			delete[] B;
	}//if
	else //не используем зануление переменных
	{
			n = size_n-num;   
			m = size_n-num-1+size_m+2;
			//for(i=0;i<m;i++)
			//	for(j=0;j<n;j++) matr[i][j]=0;
			//matr=matrix<double>(n,m);
			res_n=n;
			res_m=m;
			for(i=0;i<res_m;i++)
		      for(j=0;j<res_n;j++) matr[i][j]=0;
    
    
			for(i_2=0; i_2 < n-1; i_2++)
			{
			  matr[i_2][0]=0;
				for (j_2 = 1; j_2 < n; j_2++)
				 if (i_2+1==j_2)	matr[i_2][j_2]=-1; else matr[i_2][j_2]=0; 
			}
			
			for(i_2 = n-1; i_2< m-2; i_2++)
			{
				for (j_2=0; j_2 < n; j_2++)
				  if (j_2==0)	
				  {
					double s=0;
					i_1= i_2-n+1;
					for(j_1 = 0; j_1 <num; j_1++)
					   s=s+A[i_1][j_1]*Round(x_2[j_1],Decimals);
			           
					matr[i_2][j_2]=1-s;
				  }
				  else
				  { 
					i_1= i_2-n+1;
					j_1= j_2+num;
					matr[i_2][j_2]= A[i_1][j_1]; 
				  }
			}
			for (j_2=0; j_2<n; j_2++) 
			{
			  if (j_2==0) 
			  {   
				int tmp=0;
				 for(int t=0; t<num; t++)
					tmp=tmp+Round(x_2[t],Decimals);
				 matr[m-2][0]=-(rec+d)+tmp;
			  }
			  else matr[m-2][j_2]=-1;
			}
			for (j_2=0; j_2<n; j_2++) matr[m-1][j_2]=0;
			//cout<<matr;
	}
	//cout<<matr;
	
	//------------------------------------------------------------------
    // В общем случае надо проверить чтобы начальная таблица была двойственно допустимой
	//то есть чтобы все столбцы были lex больше 0;
	
	//чиcло переменных n-num+1, num-1 переменная фиксированная ее в конце надо скопировать
	//из x_2
	//cout<<matr;
	Make_L_Norm(/*matr*/);
    

	int p;//номер ведущей строки
	int q;//номер ведущего столбца

	clock_t start,finish; 
	double sec;
	start=clock();
	while (true)
	{
		finish=clock();
		sec = ((double)(finish - start) / CLOCKS_PER_SEC);
		if (sec>=3600) return 0;
	//while (true)
	//{
	  p=Check_L_Opim(/*matr*/);
	  if (p==-1)//нашли решение
	  {	
	     double* x;
	     x=new double[/*matr.ret_w()-1*/res_n-1];
	     for(int i=0; i</*matr.ret_w()-1*/res_n-1; i++)
	     x[i]=matr[i][0];
	     
		 double* tmp=new double[size_n];
		 for (int t=0; t<num; t++) tmp[t]=x_2[t];
		 tmp[num]=0.0;
		 	 
		 if (arr_inc!=0)
		 {
			  int r=0;
			 for (int t=num+1; t<size_n; t++) //tmp[t]=x[t-num-1];
			 {
				 if (arr_inc[t]==0) tmp[t]=0.0;
				 else 
				 {
					 tmp[t]=x[r];
					 r++;
				 }
			  }
		 }
		 else 
		 { for (int t=num+1; t<size_n; t++) tmp[t]=x[t-num-1];}
		 
		 
		 //-------------------------------------------------------
		 // Попытка использовать информацию из оптимальной таблицы
		 int max=0;
		 int vsp;
		 for (int t=1; t < /*matr.ret_w()*/res_n; t++)
		 {
			 vsp =  Num_First_Notzero_Coord(/*matr,*/t);
		     if ((vsp!=-1) &&(vsp > max)) max = vsp;
		 }
		 if (max < size_n)
		 {
		 for(int i=max; i</*matr.ret_w()-1*/res_n-1; i++)
		 {
			  if (Round(matr[i][0],Decimals)==1.0) 
			  {
				  row_number = i;
				  break;
			  }
		 }
		 }
		 //получили номер в текущей симплексной таблице, 
		 //а какой же это номер переменой в исходном решении???
		 if (arr_inc!=0)
		 {
			int kol=0;
            for (int i=num+1; i<row_number; i++) if (arr_inc[i]==0) kol++;
			row_number = row_number + num +1+kol;
		 }
		 else 
		 { 
			 row_number = row_number + num +1;
			 if (row_number > size_n) row_number= size_n;
		 }
		 
		 //-----------------------------------------------------------
		 if (x) delete[]x;
		 
		 return tmp;
		
      }
	  //проверка разрешимости !!!!! 
	  bool flag=0;
	  for(j=1;j</*matr.ret_w()*/res_n;j++)
	  {
		  if (matr[p][j]<-EPS) flag=1;
	  }
	  
	  if (flag==1)
		 {
	       //ищем номер ведущего столбца
		   q = Select_main_column(/*matr,*/p);
		   //выполняем преобразование таблицы
		   //cout<<"Main line "<<p<<endl;
	       //cout<<"Main col "<<q<<endl;
		   Preobrazovanie_Matrix(/*matr,*/p,q);
		   //cout<<matr;
		 }
		 else//то есть matr[p][j]>=0 то задача не разрешима
			 return 0;
	}
		       
	return 0;
}
/*double* Packing_Problem::LDSM_VSP_FULL(int rec,int d, int num, double* x_2,bool* arr_inc,int number_step, int& row_number)
//num- это номер первой дробной координаты вектора x_2(в алгоритме обозн p)
//если arr_inc == 0 значит занулять переменные не надо
{
	int i,j;
	int n,m;
	int i_1,j_1,i_2,j_2;
	int j_1_1=0;
	double EPS=pow(10.0, -Decimals+1);
	//i_1,j_1 - для строк и столбцов исходной матрицы, значит 0<=i_1<=size_m
	//	0<=j_1<=size_n
	//i_2,j_2 -для строк и столбцов новой строящейся матрицы, 0<=i_2<=m
	//	0<=j_2<=n
	//x[0]=x_2[0],x[1]=x_2[1],...x[num-1]=x_2[num-1],x[num]=0,остальные в таблицу на оптиум
	//число столбцов size_n-1-num, и еще 1 столбец на правые части
	row_number=size_n;
	matrix<double> matr;
	
	if (arr_inc!=0)
	{
			int len=0;//количество фиксированных координат
			for (int i=num+1; i<size_n; i++) if (arr_inc[i]==0) len++;
			
			n = size_n-num-len;   //количество оптимизируемых координат
			m = size_n-num-1+size_m+2-len;
			if (n==1) return 0;

			matr = matrix<double>(n,m);
					    
			for(i_2=0; i_2 < n-1; i_2++)
			{
			  matr[i_2][0]=0;
				for (j_2 = 1; j_2 < n; j_2++)
				 if (i_2+1==j_2)	matr[i_2][j_2]=-1; else matr[i_2][j_2]=0; 
			}
			
			for(i_2 = n-1; i_2< m-2; i_2++)
			{
			   double s=0;
			   i_1= i_2-n+1;
			   for(j_1 = 0; j_1 <num; j_1++)
				   s=s+A[i_1][j_1]*Round(x_2[j_1],Decimals);
			   matr[i_2][0]=1-s;
			}
			
			int j_start=num;
            for (j_2=1; j_2 < n; j_2++)
			{
			   j_1_1=1;
			   while (arr_inc[j_start+j_1_1]==0) j_1_1++;
			   j_1=j_start +j_1_1;
			   j_start=j_1;
			   for(i_2 = n-1; i_2< m-2; i_2++)
			   {
				   i_1=i_2-n+1;
				   matr[i_2][j_2]=A[i_1][j_1];
			   }
			 
			}
		
		
			for (j_2=0; j_2<n; j_2++) 
			{
			  if (j_2==0) 
			  {   
				int tmp=0;
				 for(int t=0; t<num; t++)
					tmp=tmp+Round(x_2[t],Decimals);
				 
				 //for(int t=num+1; t<size_n; t++)
					//if (arr_inc[t]==0) tmp=tmp+Round(x_2[t],8);

				 matr[m-2][0]=-(rec+d)+tmp;
			  }
			  else matr[m-2][j_2]=-1;
			}
			for (j_2=0; j_2<n; j_2++) matr[m-1][j_2]=0;
			//cout<<matr;
	}//if
	else //не используем зануление переменных
	{
			n = size_n-num;   
			m = size_n-num-1+size_m+2;
			matr=matrix<double>(n,m);
    
			for(i_2=0; i_2 < n-1; i_2++)
			{
			  matr[i_2][0]=0;
				for (j_2 = 1; j_2 < n; j_2++)
				 if (i_2+1==j_2)	matr[i_2][j_2]=-1; else matr[i_2][j_2]=0; 
			}
			
			for(i_2 = n-1; i_2< m-2; i_2++)
			{
				for (j_2=0; j_2 < n; j_2++)
				  if (j_2==0)	
				  {
					double s=0;
					i_1= i_2-n+1;
					for(j_1 = 0; j_1 <num; j_1++)
					   s=s+A[i_1][j_1]*Round(x_2[j_1],Decimals);
			           
					matr[i_2][j_2]=1-s;
				  }
				  else
				  { 
					i_1= i_2-n+1;
					j_1= j_2+num;
					matr[i_2][j_2]= A[i_1][j_1]; 
				  }
			}
			for (j_2=0; j_2<n; j_2++) 
			{
			  if (j_2==0) 
			  {   
				int tmp=0;
				 for(int t=0; t<num; t++)
					tmp=tmp+Round(x_2[t],Decimals);
				 matr[m-2][0]=-(rec+d)+tmp;
			  }
			  else matr[m-2][j_2]=-1;
			}
			for (j_2=0; j_2<n; j_2++) matr[m-1][j_2]=0;
	}
	//cout<<matr;
	
	//------------------------------------------------------------------
    // В общем случае надо проверить чтобы начальная таблица была двойственно допустимой
	//то есть чтобы все столбцы были lex больше 0;
	
	//чиcло переменных n-num+1, num-1 переменная фиксированная ее в конце надо скопировать
	//из x_2
	//cout<<matr;
	Make_L_Norm(matr);
    

	int p;//номер ведущей строки
	int q;//номер ведущего столбца

	while (true)
	{
	  p=Check_L_Opim(matr);
	  if (p==-1)//нашли решение
	  {	
	     double* x;
	     x=new double[matr.ret_w()-1];
	     for(int i=0; i<matr.ret_w()-1; i++)
	     x[i]=matr[i][0];
	     
		 double* tmp=new double[size_n];
		 for (int t=0; t<num; t++) tmp[t]=x_2[t];
		 tmp[num]=0.0;
		 	 
		 if (arr_inc!=0)
		 {
			  int r=0;
			 for (int t=num+1; t<size_n; t++) //tmp[t]=x[t-num-1];
			 {
				 if (arr_inc[t]==0) tmp[t]=0.0;
				 else 
				 {
					 tmp[t]=x[r];
					 r++;
				 }
			  }
		 }
		 else 
		 { for (int t=num+1; t<size_n; t++) tmp[t]=x[t-num-1];}
		 //-------------------------------------------------------
		 // Попытка использовать информацию из оптимальной таблицы
		 int max=0;
		 int vsp;
		 for (int t=1; t < matr.ret_w(); t++)
		 {
			 vsp =  Num_First_Notzero_Coord(matr,t);
		     if ((vsp!=-1) &&(vsp > max)) max = vsp;
		 }
		 if (max < size_n)
		 {
		 for(int i=max; i<matr.ret_w()-1; i++)
		 {
			  if (Round(matr[i][0],Decimals)==1.0) 
			  {
				  row_number = i;
				  break;
			  }
		 }
		 }
		 //получили номер в текущей симплексной таблице, 
		 //а какой же это номер переменой в исходном решении???
		 if (arr_inc!=0)
		 {
			int kol=0;
            for (int i=num+1; i<row_number; i++) if (arr_inc[i]==0) kol++;
			row_number = row_number + num +1+kol;
		 }
		 else 
		 { 
			 row_number = row_number + num +1;
			 if (row_number > size_n) row_number= size_n;
		 }
		 
		 //-----------------------------------------------------------
		 if (x) delete[]x;
		 
		 return tmp;
		
      }
	  //проверка разрешимости !!!!! 
	  bool flag=0;
	  for(j=1;j<matr.ret_w();j++)
	  {
		  if (matr[p][j]<-EPS) flag=1;
	  }
	  
	  if (flag==1)
		 {
	       //ищем номер ведущего столбца
		   q = Select_main_column(matr,p);
		   //выполняем преобразование таблицы
		   //cout<<"Main line "<<p<<endl;
	       //cout<<"Main col "<<q<<endl;
		   Preobrazovanie_Matrix(matr,p,q);
		   //cout<<matr;
		 }
		 else//то есть matr[p][j]>=0 то задача не разрешима
			 return 0;
	}
		       
	return 0;
}*/
//-----------------------------------------------------------
void Packing_Problem::Make_Gams_File(char* Filename)
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
  int n=size_n;
  int m=size_m;
  if (!OutFile) {cerr<<"Не могу открыть"; OutFile.close();} 
  else
  {
     OutFile<<"$Setglobal m "<<size_m<<endl;
	 OutFile<<"$Setglobal n "<<size_n<<endl;
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
		 OutFile<<"j"<<inttostr1(j+1);
		 par=len_j-1-kol;
         for (int k=0; k<par; k++) OutFile<<" ";
	 }
	 OutFile<<endl;
	 
	 for(int i=0; i<size_m; i++)
	 {
		 int par=0;
		 int kol=0;
		 if ((i+1)<10) kol++;
		 if ((i+1>=10)&&(i+1<100)) kol=2;
		 if ((i+1>=100)&&(i+1<1000)) kol=3;
		 if ((i+1>=1000)&&(i+1<10000)) kol=4;
		 if ((i+1>=10000)&&(i+1<100000)) kol=5;
		 if ((i+1>=100000)&&(i+1<1000000)) kol=6;

		 OutFile<<"i"<<inttostr1(i+1);
		 par=len_i-1-kol;
         for (int k=0; k<par; k++) OutFile<<" ";
		 
		 for (int j=0;j<size_n;j++) 
		 {
			 OutFile<<A[i][j];
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
bool Packing_Problem::Check_Int(double* x, double Eps)
{
	bool flag=1;
	for (int i=0; i<size_n; i++)
    	if (fabs(x[i]-int(x[i]+0.5))>Eps) flag=0;
	return flag;
}
bool Packing_Problem::Check_Int_LDSM(double* x,double Eps)
{
    bool flag=1;
 	for (int i=1; i<size_n+1; i++)
    	if (fabs(x[i]-int(x[i]+0.5))>Eps) flag=0;
	return flag;
}
void Packing_Problem::Round_Vect(double* &x)
{
	for(int i=0; i<size_n; i++)
	x[i]=Round(x[i],Decimals);

}
double Packing_Problem::Round(double v, int decimals)
{
	int sgn =v/fabs(v);
	double eps = sgn*pow(10.0,(-decimals));
	double rmr = fmod( v, eps );
	v -= rmr;
	if( sgn*rmr - sgn*(eps / 2)>=DBL_EPSILON )
		v += eps;
	return v;
}//double Round(double v, int decimals)

int* Packing_Problem::Go_Over_L_Class(int d, int &k, bool start_rec, bool colzero, bool opt_table_inf)
{
	int p=size_n;//номер первой дробной координаты
    k=0;//номер итерации;
	int rec=-100;//рекорд целевой функции
	int rec_start=-100;
	int Number_Step;
	int* x=0;//наилучшее решение в данный момент,соответствующие рекорду
	double* x_1;
	double* x_2;
	bool* arr_inc;
	int row_number=size_n;
	Independent_Set_Problem I;
	clock_t start, finish;
	double sec;
    if (colzero==true) arr_inc= new bool[size_n]; else arr_inc=0;
	
    Set_Decimals(8);
    double Eps=pow(10.0,-Decimals+1);//точность из за ошибок округления страдает, 
	//и вектора отличающиеся на Eps считаються равными
    
	if ((start_rec==true)||(colzero==true))  I=Get_Equivalent_MIS();
	
	if (start_rec==true)//ищем начальный рекорд с помощью эвристики
	{
	  x=I.Greedy_Algorithm();
	  if (x!=0){
		  rec_start=x[0];
		  // cout<<"Greedy = ";
		  //for (int i=0; i<size_n+1;i++) cout<<x[i]<<" ";
		  //cout<<endl;
	  }else return 0;
	}
	res_n=size_n+1;
	res_m=size_n+size_m+2;
	matr = matrix<double>(res_n,res_m);
	
	x_1=LDSM();//решаем задачу ЛП
    // cout<<"LP = ";
	//for (int i=0; i<size_n+1;i++) cout<<x_1[i]<<" ";
	//cout<<endl;
	if (x_1!=0)
	{
		Round_Vect(x_1);
		if (Check_Int_LDSM(x_1,Eps)==1) 
		{
		   rec=0;
		   for (int i=1; i<size_n+1; i++) rec=rec+x_1[i];
		   if (rec>=rec_start)
		   {
		   if (x==0) x= new int[size_n+1];
		   for(int i =1; i<size_n+1; i++)
				   x[i]=int(x_1[i]);
		   x[0]=rec;
		
		   return x;
		   }
		}
	}
	delete [] x_1;
	if (opt_table_inf==true) x_1=LEXMAX_M_WITH_INFO(row_number);
	else x_1=LEXMAX_M();
    //cout<<"RoW Number = "<<row_number<<endl;	
	if (x_1==0) return x;
	//for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
	//cout<<endl;
		
	Round_Vect(x_1);
	if (Check_Int(x_1,Eps)==1) 
	{
	 rec=0;
	 for (int i=0; i<size_n; i++) rec=rec+x_1[i];
	 if (rec>=rec_start)
	   { 
		  if (x==0) x= new int[size_n+1];
		  for(int i =1; i<size_n+1; i++)
			   x[i]=int(x_1[i-1]);
		  x[0]=rec;
	   } else rec=rec_start;
	 x_2=x_1;
	 Number_Step=3;
	 //переход на шаг3
	}
	else Number_Step=2;//переход на шаг2
    
	start=clock();
	while (true)
	{
		finish=clock();
		sec = ((double)(finish - start) / CLOCKS_PER_SEC);
		if (sec>=3600) 
		{
			if ((colzero==true)&&(arr_inc)) delete[] arr_inc;
			return x;
		}
		switch (Number_Step)
		{
		case 2:
			{
				k++;
				delete[] x_2;
				x_2=x_1;
			
				for (int i=0; i < size_n; i++)
				{
				  if ((fabs(x_2[i]-int(x_2[i]+0.5)))>Eps) 
				  { 
                    p=i;
					break;
				  }
				}
				
				if ((opt_table_inf==true)&&(p >row_number))
					p = row_number;

				if (colzero==true)//используем зануление переменных
				{
				  for(int t=0; t< size_n; t++) arr_inc[t]=1;
				  for(int i=0; i<p ;i++) 
					  if (Round(x_2[i],Decimals)==1)
					{
						for (int j=p+1; j<size_n; j++)
							if (I.Get(i,j)==1) arr_inc[j]=0;
					}
				}
				x_1=LDSM_VSP_FULL(rec,d,p,x_2,arr_inc,2,row_number);
				//cout<<"RoW Number = "<<row_number<<endl;								
				//if (x_1!=0) Round_Vect(x_1);
                //if (x_1!=0)	for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
				//else cout<<"No solution ";
				//cout<<"After check iteration number "<<k<<"Record = "<<rec<<endl;
					
				if ((x_1==0)&&(p==0)) {Number_Step=4; continue;}
				if ((x_1==0)&&(p>0)) {Number_Step=3; continue;}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==1)) 
				 {
					 int s=0;
					 for (int tmp=0; tmp<size_n; tmp++) s=s+x_1[tmp];
					 if (s > rec) 
					 {
						 rec=s;
						 if (x==0) x=new int[size_n+1];
					   	 for(int i =1; i<size_n+1; i++)
			             x[i]=int(x_1[i-1]);
						 x[0]=rec;
					 }
					 p=size_n;
					 delete[] x_2;
					 x_2=x_1;
					 Number_Step=3; 
					 continue;
				}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==0)) {Number_Step=2; continue;}
			break;
			}
		case 3:
			{
				k++;
			    int f=-1;
			    for(int i=0; i<p ; i++) 
				  if ((x_2[i]>0)&&(i>f)) f=i;
			    if(f==-1) {Number_Step=4; continue;} 
                
				if ((opt_table_inf==true)&&(f >row_number))
					f = row_number;

				if (colzero==true)//используем зануление переменных
				{
				for(int t=0; t< size_n; t++) arr_inc[t]=1;
				for(int i=0; i<f ;i++) 
					if (Round(x_2[i],Decimals)==1)
					{
						for (int j=f+1; j<size_n; j++)
							if (I.Get(i,j)==1) arr_inc[j]=0;
					}
				}
               // if (arr_inc!=0) for (int i=0; i<size_n;i++) cout<<arr_inc[i]<<" ";
				x_1=LDSM_VSP_FULL(rec,d,f,x_2,arr_inc,3,row_number);
				//cout<<"RoW Number = "<<row_number<<endl;
				if (x_1!=0) Round_Vect(x_1);
                //if (x_1!=0)	for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
				//else cout<<"No solution ";
				//cout<<"After check iteration number "<<k<<"Record = "<<rec<<endl;
				//cout<<"After check iteration number "<<k<<endl;
								
				if ((x_1==0)&&(f==0)) {Number_Step=4; continue;}
				if ((x_1==0)&&(p>0)) { p=f; Number_Step=3; continue;}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==1)) 
				 {
					 int s=0;
					 for (int tmp=0; tmp<size_n; tmp++) s=s+x_1[tmp];
					 if (s > rec) 
					 {
						 rec=s;
						 if (x==0) x=new int[size_n+1];
					   	 for(int i =1; i<size_n+1; i++)
			             x[i]=int(x_1[i-1]);
						 x[0]=rec;
					 }
					 p=size_n;
					 delete[] x_2;
					 x_2=x_1;
					 Number_Step=3; 
					 continue;
				}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==0)) {Number_Step=2; continue;} 
			break;
			}
		case 4:
			{
				if ((colzero==true)&&(arr_inc)) delete[] arr_inc;
				return x;
			}
		}
	}
	if ((colzero==true)&&(arr_inc)) delete[] arr_inc;
	return 0;			
}

int* Packing_Problem::Go_Over_L_Class_Standart(int d, int &k)
//d-параметр алгоритма, 1-точное решение, 2-приближенное решение
{
 //решить задачу ЛП, проверить если решение целочисленное то вернуть его, если нет то
 //весь следующий текст
	int p=size_n;//номер первой дробной координаты
    k=0;//номер итерации;
	int rec=-100;//рекорд целевой функции
	int rec_start=-100;
	int Number_Step;
	int* x=0;//наилучшее решение в данный момент,соответствующие рекорду
	double* x_1;
	double* x_2;
	
    Set_Decimals(8);
    double Eps=pow(10.0,-Decimals+1);//точность из за ошибок округления страдает, 
	//и вектора отличающиеся на Eps считаються равными
    
	//ищем начальный рекорд с помощью эвристики
	/*Independent_Set_Problem P;
	P=Get_Equivalent_MIS();
	x=P.Greedy_Algorithm();
	if (x!=0) rec_start=x[0]; else return 0;*/
	///////////////////
    //if (x!=0)	for (int i=0; i<size_n+1;i++) cout<<x[i]<<" ";
    
	x_1=LDSM();//решаем задачу ЛП
   
		
	if (Check_Int_LDSM(x_1,Eps)==1) 
	{
	   rec=0;
	   for (int i=1; i<size_n+1; i++) rec=rec+x_1[i];
	   if (x==0) x= new int[size_n+1];
	   for(int i =1; i<size_n+1; i++)
			   x[i]=int(x_1[i]);
	   x[0]=rec;
	   return x;
	}

	x_1=LEXMAX_M();
	if (x_1==0) return x;
	for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
	cout<<endl;
		
	Round_Vect(x_1);
	if (Check_Int(x_1,Eps)==1) 
	{
	 rec=0;
	 for (int i=0; i<size_n; i++) rec=rec+x_1[i];
	 if (rec>=rec_start)
	   { 
		  if (x==0) x= new int[size_n+1];
		  for(int i =1; i<size_n+1; i++)
			   x[i]=int(x_1[i-1]);
		  x[0]=rec;
	   } else rec=rec_start;
	 x_2=x_1;
	 Number_Step=3;
	 //переход на шаг3
	}
	else Number_Step=2;//переход на шаг2
    
	while (k<3000)
	{
		switch (Number_Step)
		{
		case 2:
			{
				k++;
				x_2=x_1;
			
				for (int i=0; i < size_n; i++)
				{
				  if ((fabs(x_2[i]-int(x_2[i]+0.5)))>Eps) 
				  { 
                    p=i;
					break;
				  }
				}
				x_1=LDSM_VSP(rec,d,p,x_2,2);
				if (x_1!=0) Round_Vect(x_1);
                if (x_1!=0)	for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
				else cout<<"No solution ";
				cout<<"After check iteration number "<<k<<"Record = "<<rec<<endl;
					
				if ((x_1==0)&&(p==0)) {Number_Step=4; continue;}
				if ((x_1==0)&&(p>0)) {Number_Step=3; continue;}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==1)) 
				 {
					 int s=0;
					 for (int tmp=0; tmp<size_n; tmp++) s=s+x_1[tmp];
					 if (s > rec) 
					 {
						 rec=s;
						 if (x==0) x=new int[size_n+1];
					   	 for(int i =1; i<size_n+1; i++)
			             x[i]=int(x_1[i-1]);
						 x[0]=rec;
					 }
					 p=size_n;
					 x_2=x_1;
					 Number_Step=3; 
					 continue;
				}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==0)) {Number_Step=2; continue;}
			break;
			}
		case 3:
			{
				k++;
			    int f=-1;
			    for(int i=0; i<p ; i++) 
				  if ((x_2[i]>0)&&(i>f)) f=i;
			    if(f==-1) {Number_Step=4; continue;} 
                
				x_1=LDSM_VSP(rec,d,f,x_2,3);
				if (x_1!=0) Round_Vect(x_1);
                if (x_1!=0)	for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
				else cout<<"No solution ";
				cout<<"After check iteration number "<<k<<"Record = "<<rec<<endl;
				//cout<<"After check iteration number "<<k<<endl;
								
				if ((x_1==0)&&(f==0)) {Number_Step=4; continue;}
				if ((x_1==0)&&(p>0)) { p=f; Number_Step=3; continue;}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==1)) 
				 {
					 int s=0;
					 for (int tmp=0; tmp<size_n; tmp++) s=s+x_1[tmp];
					 if (s > rec) 
					 {
						 rec=s;
						 if (x==0) x=new int[size_n+1];
					   	 for(int i =1; i<size_n+1; i++)
			             x[i]=int(x_1[i-1]);
						 x[0]=rec;
					 }
					 p=size_n;
					 x_2=x_1;
					 Number_Step=3; 
					 continue;
				}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==0)) {Number_Step=2; continue;} 
			break;
			}
		case 4:
			{
				return x;
			}
		}
	}
	
	return x;			
}

int Packing_Problem::Scal_Proiz(int i, int j)
{
	int sum=0;
	for(int k=0; k<A.ret_h(); k++)
		sum=sum+A[k][i]*A[k][j];
	return sum;
}
void Packing_Problem::MatrixA_To_Graph_Incendence(matrix<bool> &GI)
{
	//по матрице задачи упаковки строим матрицу инцинденций графа пересечений
	GI=matrix<bool>(size_n,size_n);
	for(int i=0; i<size_n; i++)
	  for (int j=i; j<size_n; j++)
	  {
		  if (Scal_Proiz(i,j)>=1) 
		  {
			  GI[i][j]=1;
			  GI[j][i]=1;
		  } else
		  { 
			  GI[i][j]=0;
			  GI[j][i]=0;
		  }
	  }
}

void Packing_Problem::MatrixA_To_Graph_A(matrix<bool> &GI)
{
	//по матрице задачи упаковки строим матрицу инцинденций графа пересечений
	int m=0;
	for(int i=0; i<size_n; i++)
	  for (int j=i; j<size_n; j++)
		  if (Scal_Proiz(i,j)>=1) m++;
	
	GI=matrix<bool>(size_n, m);
	
	int k=0;
	for(int i=0; i<size_n; i++)
	  for (int j=i; j<size_n; j++)
	  {
		  if (Scal_Proiz(i,j)>=1) 
		  {
			  GI[k][i]=1;
			  GI[k][j]=1;
			  k++;
		  } 
	  }
}
int* Packing_Problem::Go_Over_L_Class_Modified_First(int d, int &k)
//d-параметр алгоритма, 1-точное решение, 2-приближенное решение
{
 //решить задачу ЛП, проверить если решение целочисленное то вернуть его, если нет то
 //весь следующий текст
	int p=size_n;//номер первой дробной координаты
    k=0;//номер итерации;
	int rec=-100;//рекорд целевой функции
	int rec_start=-100;
	int Number_Step;
	int* x=0;//наилучшее решение в данный момент,соответствующие рекорду
	double* x_1;
	double* x_2;
	
    Set_Decimals(8);
    double Eps=pow(10.0,-Decimals+1);//точность из за ошибок округления страдает, 
	//и вектора отличающиеся на Eps считаються равными
    
	x_1=LDSM();//решаем задачу ЛП
    if (x_1!=0)
	{
		if (Check_Int_LDSM(x_1,Eps)==1) 
		{
		   rec=0;
		   for (int i=1; i<size_n+1; i++) rec=rec+x_1[i];
		   if (x==0) x= new int[size_n+1];
		   for(int i =1; i<size_n+1; i++)
				   x[i]=int(x_1[i]);
		   x[0]=rec;
		   return x;
		}
	for (int i=0; i<size_n+1;i++) cout<<x_1[i]<<" ";
	cout<<endl;
	}

	//ищем начальный рекорд с помощью эвристики
	Independent_Set_Problem P;
	P=Get_Equivalent_MIS();
	x=P.Greedy_Algorithm();
	if (x!=0) rec_start=x[0]; else return 0;
	///////////////////
    if (x!=0)	for (int i=0; i<size_n+1;i++) cout<<x[i]<<" ";
	cout<<endl;
 
	x_1=LEXMAX_M();//что если здесь не будет решения!
	if (x_1==0) return x;
	
	for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
	cout<<endl;
		
	Round_Vect(x_1);
	if (Check_Int(x_1,Eps)==1) 
	{
	 rec=0;
	 for (int i=0; i<size_n; i++) rec=rec+x_1[i];
	 if (rec>=rec_start)
	   { 
		  if (x==0) x= new int[size_n+1];
		  for(int i =1; i<size_n+1; i++)
			   x[i]=int(x_1[i-1]);
		  x[0]=rec;
	   } else rec=rec_start;
	 x_2=x_1;
	 Number_Step=3;
	 //переход на шаг3
	}
	else Number_Step=2;//переход на шаг2
    
	while (true)
	{
		switch (Number_Step)
		{
		case 2:
			{
				k++;
				x_2=x_1;
			
				for (int i=0; i < size_n; i++)
				{
				  if ((fabs(x_2[i]-int(x_2[i]+0.5)))>Eps) 
				  { 
                    p=i;
					break;
				  }
				}
				x_1=LDSM_VSP(rec,d,p,x_2,2);
				if (x_1!=0) Round_Vect(x_1);
                /*if (x_1!=0)	for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
				else cout<<"No solution ";
				cout<<"After check"<<endl;*/
				 if (x_1!=0)	for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
				else cout<<"No solution ";
				cout<<"After check iteration number "<<k<<"Record = "<<rec<<endl;
					
				if ((x_1==0)&&(p==0)) {Number_Step=4; continue;}
				if ((x_1==0)&&(p>0)) {Number_Step=3; continue;}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==1)) 
				 {
					 int s=0;
					 for (int tmp=0; tmp<size_n; tmp++) s=s+x_1[tmp];
					 if (s >= rec) 
					 {
						 rec=s;
						 if (x==0) x=new int[size_n+1];
					   	 for(int i =1; i<size_n+1; i++)
			             x[i]=int(x_1[i-1]);
						 x[0]=rec;
					 }
					 p=size_n;
					 x_2=x_1;
					 Number_Step=3; 
					 continue;
				}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==0)) {Number_Step=2; continue;}
			break;
			}
		case 3:
			{
				k++;
			    int f=-1;
			    for(int i=0; i<p ; i++) 
				  if ((x_2[i]>0)&&(i>f)) f=i;
			    if(f==-1) {Number_Step=4; continue;} 
                
				x_1=LDSM_VSP(rec,d,f,x_2,3);
				if (x_1!=0) Round_Vect(x_1);
                /*if (x_1!=0)	for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
				else cout<<"No solution ";
				cout<<"After check"<<endl;*/
				 if (x_1!=0)	for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
				else cout<<"No solution ";
				cout<<"After check iteration number "<<k<<"Record = "<<rec<<endl;
								
				if ((x_1==0)&&(f==0)) {Number_Step=4; continue;}
				if ((x_1==0)&&(p>0)) { p=f; Number_Step=3; continue;}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==1)) 
				 {
					 int s=0;
					 for (int tmp=0; tmp<size_n; tmp++) s=s+x_1[tmp];
					 if (s >= rec) 
					 {
						 rec=s;
						 if (x==0) x=new int[size_n+1];
					   	 for(int i =1; i<size_n+1; i++)
			             x[i]=int(x_1[i-1]);
						 x[0]=rec;
					 }
					 p=size_n;
					 x_2=x_1;
					 Number_Step=3; 
					 continue;
				}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==0)) {Number_Step=2; continue;} 
			break;
			}
		case 4:
			{
				return x;
			}
		}
	}
}

int* Packing_Problem::Go_Over_L_Class_Modified_Second(int d, int &k)
//d-параметр алгоритма, 1-точное решение, 2-приближенное решение
{
 //решить задачу ЛП, проверить если решение целочисленное то вернуть его, если нет то
 //весь следующий текст
	int p=size_n;//номер первой дробной координаты
    k=0;//номер итерации;
	int rec=-100;//рекорд целевой функции
	int rec_start=-100;
	int Number_Step;
	int* x=0;//наилучшее решение в данный момент,соответствующие рекорду
	double* x_1;
	double* x_2;
	bool* arr_inc= new bool[size_n];
	//for(int t=0; t< size_n; t++) arr_inc[t]=1;
	matrix<bool>* Graph;

    Set_Decimals(8);
    double Eps=pow(10.0,-Decimals+1);//точность из за ошибок округления страдает, 
	//и вектора отличающиеся на Eps считаються равными
    
	x_1=LDSM();//решаем задачу ЛП
    if (x_1!=0)
	{
	if (Check_Int_LDSM(x_1,Eps)==1) 
	{
	   rec=0;
	   for (int i=1; i<size_n+1; i++) rec=rec+x_1[i];
	   if (x==0) x= new int[size_n+1];
	   for(int i =1; i<size_n+1; i++)
			   x[i]=int(x_1[i]);
	   x[0]=rec;
	   return x;
	}
	}
	//ищем начальный рекорд с помощью эвристики
	
	Independent_Set_Problem P;
	P=Get_Equivalent_MIS();
	/*x=P.Greedy_Algorithm();
	if (x!=0) rec_start=x[0]; else return 0;
	//Graph=P.GetGraph();
	///////////////////
    //if (x!=0)	for (int i=0; i<size_n+1;i++) cout<<x[i]<<" ";*/
 
	x_1=LEXMAX_M();//что если здесь не будет решения!
	if (x_1==0) return x;
	for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
	cout<<endl;
		
	Round_Vect(x_1);
	if (Check_Int(x_1,Eps)==1) 
	{
	 rec=0;
	 for (int i=0; i<size_n; i++) rec=rec+x_1[i];
	 if (rec>=rec_start)
	   { 
		  if (x==0) x= new int[size_n+1];
		  for(int i =1; i<size_n+1; i++)
			   x[i]=int(x_1[i-1]);
		  x[0]=rec;
	   } else rec=rec_start;
	 x_2=x_1;
	 Number_Step=3;
	 //переход на шаг3
	}
	else Number_Step=2;//переход на шаг2
    
	while (true)
	{
		switch (Number_Step)
		{
		case 2:
			{
				k++;
				x_2=x_1;
			    
				for (int i=0; i < size_n; i++)
				{
				  if ((fabs(x_2[i]-int(x_2[i]+0.5)))>Eps) 
				  { 
                    p=i;
					break;
				  }
				}
				//заполнить массив инцидентных вершин
				for(int t=0; t< size_n; t++) arr_inc[t]=1;
				for(int i=0; i<p ;i++) 
					if (x_2[i]==1)
					{
						for (int j=p+1; j<size_n; j++)
							if (P.Get(i,j)==1) arr_inc[j]=0;
					}
				x_1=LDSM_VSP_SECOND(rec,d,p,x_2,arr_inc,2);
				
				if (x_1!=0) Round_Vect(x_1);
                if (x_1!=0)	for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
				else cout<<"No solution ";
				cout<<"After check"<<endl;
					
				if ((x_1==0)&&(p==0)) {Number_Step=4; continue;}
				if ((x_1==0)&&(p>0)) {Number_Step=3; continue;}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==1)) 
				 {
					 int s=0;
					 for (int tmp=0; tmp<size_n; tmp++) s=s+x_1[tmp];
					 if (s > rec) 
					 {
						 rec=s;
						 if (x==0) x=new int[size_n+1];
					   	 for(int i =1; i<size_n+1; i++)
			             x[i]=int(x_1[i-1]);
						 x[0]=rec;
					 }
					 p=size_n;
					 x_2=x_1;
					 Number_Step=3; 
					 continue;
				}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==0)) {Number_Step=2; continue;}
			break;
			}
		case 3:
			{
				k++;
			    int f=-1;
			    for(int i=0; i<p ; i++) 
				  if ((x_2[i]>0)&&(i>f)) f=i;
			    if(f==-1) {Number_Step=4; continue;} 
                
				for(int t=0; t< size_n; t++) arr_inc[t]=1;
				for(int i=0; i<f ;i++) 
					if (x_2[i]==1)
					{
						for (int j=f+1; j<size_n; j++)
							if (P.Get(i,j)==1) arr_inc[j]=0;
					}
				x_1=LDSM_VSP_SECOND(rec,d,f,x_2,arr_inc,3);
			
				if (x_1!=0) Round_Vect(x_1);
                if (x_1!=0)	for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
				else cout<<"No solution ";
				cout<<"After check"<<endl;
								
				if ((x_1==0)&&(f==0)) {Number_Step=4; continue;}
				if ((x_1==0)&&(p>0)) { p=f; Number_Step=3; continue;}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==1)) 
				 {
					 int s=0;
					 for (int tmp=0; tmp<size_n; tmp++) s=s+x_1[tmp];
					 if (s > rec) 
					 {
						 rec=s;
						 if (x==0) x=new int[size_n+1];
					   	 for(int i =1; i<size_n+1; i++)
			             x[i]=int(x_1[i-1]);
						 x[0]=rec;
					 }
					 p=size_n;
					 x_2=x_1;
					 Number_Step=3; 
					 continue;
				}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==0)) {Number_Step=2; continue;} 
			break;
			}
		case 4:
			{
				return x;
			}
		}
	}
}

double* Packing_Problem::LDSM_VSP_BLOCK(int rec,int d, int num, double* x_2,int number_step, int kol_full_enum, bool start_rec,bool colzero,bool opt_table_inf)
//считаем что наша задача имеет блочную структуру
{
	//У нас есть!
	int r = Matrix_Block_Param->r;//число переменных в левой части матрицы (0,r-1)
	int block_kol = Matrix_Block_Param->block_kol;//количество блоков
	int n_size; 
	int m_size;
	//-----------
	int max_block;
	int i,j,k,t;
	//Packing_Problem* vsp;
	//matrix<bool>* temp;
	double* x;
	int block_start=0;
	
	//cout<<"Check1";
	Independent_Set_Problem IP;
	//cout<<"Check2";
	IP=Get_Equivalent_MIS();
	//cout<<"Check3";

	x = new double[size_n];
    for (t=0; t<num; t++) x[t]=x_2[t];
	x[num]=0;
	//for (int t=num+1; t<size_n; t++) x[t]=?;
	//фиксируется num+1 координат [0,num]
	
	if (num < r-1)//первый вариант схемы с пересекающимисы переменными
	{
	   int dec;
	   int rec_cur=0;
	   int sum;
	   int n_size,m_size; 
	   int i,j,k,t;
	   int block_kol;
	   //cout<<"LDSM_BLOCK_Start1"<<endl;
	   int* x_vsp=new int[size_n-num-1];//решение
       int* vs=new int[r-num-1];//чило переменных полного перебора в общей части
       int* inced=new int [size_n-r];//1-переменная остаеться как есть, 0- переменная не входит к решение
	   //Independent_Set_Problem IP;
	   //IP=Get_Equivalent_MIS();
	   //Independent_Set_Problem IP = this->Get_Equivalent_MIS();
	   int* block_sol;
	   bool flag;
       
	   int kol = (int)pow((double)2,(r-num-1));
	   for (int i=0; i< kol ; i++)
	   {
			//i нужно перевести в двоичную систему
			for (j=0; j<r-num-1; j++) vs[j]=0;
		 	
				dec = i;
				j=0;
				while (dec > 1)
				{
				   k = dec/2;
				   vs[j] = dec- k*2;
				   j++;
				   dec = k;
				}
				if (i>0) vs[j]=1;
			 //--проверка на совместимость решения//--------------
				
				flag=false; 
		        for (int t=0; t<size_m; t++)
		        {
					sum=0;
					for(j=0; j<r-num-1; j++)
					 sum= sum+ A[t][j+num+1]*vs[j];
					if (sum > 1) 
					{
						flag=true;
						break;
					}
				}
		 
		     if (flag==true) continue;//это vs не подходит ищем следующее
		 
			 //--------------------------------		   
			for (j=0; j<r-num-1; j++) x_vsp[j] = vs[j];
		   //для каждого i надо решить задачу на блоках и запомнить рекорд в x_vsp
           //----------------------------------------
				
			  for(k=0; k<size_n-r; k++)	inced[k]=1;
			  for (j=0; j<num; j++)
			  {
			 	if (x_2[j]==1)
				{
			     for(k=0; k<size_n-r; k++)
			     if (IP.Get(j,k+r)==1) inced[k]=0;// else inced[k]=1;
			  	}
			  }  
			  for (j=0; j<r-num-1; j++)
				{
			      if (vs[j]==1)
			      {
			        for(k=0; k<size_n-r; k++)//для всех остальных блоков k другое
			           if (IP.Get(j+num+1,k+r)==1) inced[k]=0;
				  }
				}
		    //------------------------------------
		   //---------------------------------------------------------------------		   
			 block_kol = Matrix_Block_Param->block_kol;//количество блоков
			 for (int b=0 ; b<block_kol; b++)
			 {
				 Packing_Problem* vsp;
	             //matrix<bool>* temp;
				 matrix<bool> temp;
				 
				 n_size = Matrix_Block_Param->Blocks[b].n_size;
				 m_size = Matrix_Block_Param->Blocks[b].m_size;
					  
				 //temp = new matrix<bool>(n_size, m_size);
				 temp = matrix<bool>(n_size, m_size);
				  
				 int i_1,j_1,sum;//смещение блока от границ исходной матрицы
				 sum=0;
				 for (j=0; j<b; j++) 
				 sum = sum + Matrix_Block_Param->Blocks[j].n_size;
				 j_1 = r + sum;
				 
				 sum=0;
				 for (j=0; j<b; j++) 
				  sum = sum + Matrix_Block_Param->Blocks[j].m_size;
				 i_1=sum; 

				 /*for (t=0; t<m_size; t++)
				   for (k=0; k<n_size; k++)
				    temp->matr[t][k]=A[t+i_1][k+j_1];*/

				 for (t=0; t<m_size; t++)
				   for (k=0; k<n_size; k++)
				    temp[t][k]=A[t+i_1][k+j_1];

                 //vsp = new Packing_Problem(*temp);
				 vsp = new Packing_Problem(temp);
                 
				 for (t=j_1-r; t<j_1-r+n_size; t++)
				 {
				  if (inced[t]==0) 
					  for (j=0;j<m_size; j++) vsp->Set(j,t-j_1+r,1);
				 }
			   
				if (n_size<=kol_full_enum)
				block_sol=vsp->Complete_Enumeration();
			    else
			    block_sol = vsp->Go_Over_L_Class(1,k, start_rec, colzero, opt_table_inf);
		            
				for (t=1; t<n_size+1; t++) x_vsp[t-1+j_1-num-1]=block_sol[t];
				
				delete[] block_sol;
				//delete temp;
				delete vsp;
			}
		 //----------------------------------------------------------------------------------
		//получили решение x_vsp	
				sum=0;
				for(j=0; j<size_n-1-num; j++) sum = sum+x_vsp[j];
				if (sum > rec_cur) 
				{ 
					rec_cur = sum;
					for(j=0; j<size_n-1-num; j++) x[num+j+1]=(int)x_vsp[j];
				}
	   }//for
	   
       delete[] x_vsp;
	   delete[] vs;
	   delete[] inced;
	   //IP.~Independent_Set_Problem();
	   
	   //Ограничение по целевой функции
	   int tmp=0;
		for(int t=0; t<num; t++)
			tmp=tmp+Round(x_2[t],8);
		if ((rec_cur+tmp)>rec)
		{
			return x;
			//cout<<"LDSM_BLOCK_Finish"<<endl;
		}
		else 
		{
			return 0;
			//cout<<"LDSM_BLOCK_Finish"<<endl;
		}
	}//if
 	else//второй вариант, здесь нет общих переменных
	{
	  // cout<<"LDSM_BLOCK_Start2"<<endl;
	   int* inced=new int [size_n-num-1];//1-переменная остаеться как есть, 0- переменная не входит к решение
	   //Independent_Set_Problem IP;
	   //IP=Get_Equivalent_MIS();
	    // Independent_Set_Problem IP;
	 //  IP=Get_Equivalent_MIS();
	   
	   //----------------------------------------
	 	for(j=0; j<size_n-num-1; j++) inced[j]=1; 
	    for (j=0; j<num; j++)
		  {
		    if (x_2[j]==1)
			{
			  for(k=0; k<size_n-num-1; k++)//для всех остальных блоков k другое
		      if (IP.Get(j,k+num+1)==1) inced[k]=0;// else inced[k]=1;
			}
		  }
		//cout<<"LDSM_BLOCK_1"<<endl;
		// for(j=0; j<size_n-num-1; j++) cout<<" "<<inced[j];
		 //cout<<endl;
		//------------------------------------ 
	    t=r;
		for (i=0; i< block_kol; i++)
		{		
		  t = t + Matrix_Block_Param->Blocks[i].n_size;
		  if (num < t) 
		  {
			  block_start = i;
			  break;
		  }
		}
		int sum=0;
		//---------остальные блоки-------------------------------------
		for (i=block_start ; i<block_kol; i++)
		{
		//	cout<<"LDSM_BLOCK_2 "<<i<<" "<<block_kol<<endl;
			Packing_Problem* vsp;
	        //matrix<bool>* temp;	
			matrix<bool> temp;	
			
			if (i==block_start)
				{
				   sum=0;
				   for (j=0; j<block_start; j++) 
					   sum = sum + Matrix_Block_Param->Blocks[j].n_size;
					n_size = Matrix_Block_Param->Blocks[block_start].n_size-num+r+sum-1;
				  m_size = Matrix_Block_Param->Blocks[block_start].m_size;
				}
			   else
				{
				  n_size = Matrix_Block_Param->Blocks[i].n_size;
				  m_size = Matrix_Block_Param->Blocks[i].m_size;
				}
			   //temp = new matrix<bool>(n_size, m_size);
			   temp = matrix<bool>(n_size, m_size);
		//	   cout<<n_size<<" "<<m_size<<endl;
			   //--------------------
			   int i_1,j_1;//смещение блока от границ исходной матрицы
			   sum=0;
				   for (j=0; j<i; j++) 
					   sum = sum + Matrix_Block_Param->Blocks[j].n_size;
			   j_1 = r + sum;
			   
			   if (i==block_start)
			   { 
				   sum=0;
				   for (j=0; j<block_start; j++) 
					   sum = sum + Matrix_Block_Param->Blocks[j].n_size;
				   j_1=j_1+num-sum-r+1;
		       }

			   sum=0;
				   for (j=0; j<i; j++) 
					   sum = sum + Matrix_Block_Param->Blocks[j].m_size;
			   i_1=sum;
			   //--------------------
			   /*for (t=0; t<m_size; t++)
				   for (k=0; k<n_size; k++)
					   temp->matr[t][k]=A[t+i_1][k+j_1];
			   vsp = new Packing_Problem(*temp);*/
		//	   cout<<"before zapolnenie"<<endl;
			   for (t=0; t<m_size; t++)
				   for (k=0; k<n_size; k++)
					   temp[t][k]=A[t+i_1][k+j_1];
			   
			   vsp = new Packing_Problem(temp);
		//	   cout<<"matr complete"<<endl;
			   //------------------------------------------
			   for (t=j_1-r; t<j_1-r+n_size; t++)
			   {
	//			  cout<<t<<" "<<j_1-r+n_size<<endl;
	//			  for(int h =0; h<size_n-num-1; h++) cout<<inced[h]<<" ";
				  if (inced[t-j_1+r]==0) 
				   {
	//				  cout<<"0"<<endl;
					   for (j=0;j<m_size; j++) 
					   {
						   vsp->Set(j,t-j_1+r,1);
		//				   cout<<"vspSet complete"<<endl;
					   }
					}
			   }
			   //------------------------------------------
		//	cout<<"before solution"<<endl;
			int* x_vsp;
			if (n_size<=kol_full_enum)
				x_vsp=vsp->Complete_Enumeration();
			else
			    x_vsp = vsp->Go_Over_L_Class(1,k, start_rec, colzero, opt_table_inf);
		//	cout<<"after solution"<<endl;
			//cout<<*temp;
			//записать решение в конечное решение на нужное место
            for (t=1; t<n_size+1; t++) x[t-1+j_1]=x_vsp[t];
	    
			//--------------------------------------------------
			//delete temp;
			delete[] x_vsp;
			delete vsp;
			//cout<<"LDSM_BLOCK_3 "<<i<<" "<<block_kol<<endl;
		}
		//----------------------------------------------
		 delete[] inced;
		 //IP->~Independent_Set_Problem();
	       
      int tmp=0;
		for(int t=0; t<size_n; t++)
			tmp=tmp+Round(x[t],8);
	
	  if (tmp > rec) 
	  {
		  //cout<<"LDSM_BLOCK_Finish"<<endl;
		  return x;
	  }
		  
		else 
		{//cout<<"LDSM_BLOCK_Finish"<<endl;
			return 0;	
	  }
     }
    
    //for (t=0; t<size_n; t++) cout<<x[t]<<" ";
	//cout<<endl;
	//return x;
}

int* Packing_Problem::Go_Over_L_Class_Block(int d, int &k , bool start_rec,bool colzero,bool opt_table_inf, int kol_full_enum_block, int kol_full_enum_r)
{
//решить задачу ЛП, проверить если решение целочисленное то вернуть его, если нет то
//весь следующий текст
	int p=size_n;//номер первой дробной координаты
    k=0;//номер итерации;
	int rec=-100;//рекорд целевой функции
	int rec_start=-100;
	int Number_Step;
	int* x=0;//наилучшее решение в данный момент,соответствующие рекорду
	double* x_1;
	double* x_2;
	bool* arr_inc;
	clock_t start,finish;
	int row_number=size_n;
	//Independent_Set_Problem* I;
	Independent_Set_Problem I;
	
    if (colzero==true) arr_inc= new bool[size_n]; else arr_inc=0;
	
   	if ((start_rec==true)||(colzero==true)) I=Get_Equivalent_MIS();
	
	
	Set_Decimals(8);
    double Eps=pow(10.0,-Decimals+1);//точность из за ошибок округления страдает, 
	//и вектора отличающиеся на Eps считаються равными
    
	//проверяем имеет ли задача полностью блочную структуру
    if (Matrix_Block_Param->r==0)
	{
       int n_size,m_size; 
	   int i,j,k,t;
	   int rec;
	   Packing_Problem* vsp;
	   matrix<bool>* temp;
	   int* x = new int [size_n+1];
	   int block_kol = Matrix_Block_Param->block_kol;//количество блоков
	   for (int i=0 ; i<block_kol; i++)
		{
			  n_size = Matrix_Block_Param->Blocks[i].n_size;
		      m_size = Matrix_Block_Param->Blocks[i].m_size;
			  
			  temp = new matrix<bool>(n_size, m_size);
			  
			  int i_1,j_1,sum;//смещение блока от границ исходной матрицы
		      sum=0;
			  for (j=0; j<i; j++) 
				   sum = sum + Matrix_Block_Param->Blocks[j].n_size;
		      j_1 = sum;
		      sum=0;
			   for (j=0; j<i; j++) 
				   sum = sum + Matrix_Block_Param->Blocks[j].m_size;
		      i_1=sum; 

				  for (t=0; t<m_size; t++)
				   for (k=0; k<n_size; k++)
					   temp->matr[t][k]=A[t+i_1][k+j_1];
			       vsp = new Packing_Problem(*temp);
			  int* x_vsp;
			  if ((n_size<=5)&&(m_size<=5))
				x_vsp=vsp->Complete_Enumeration();
			  else
			    x_vsp = vsp->Go_Over_L_Class(1,k, start_rec, colzero, opt_table_inf);
            
			  delete temp;
			  for (t=1; t<n_size+1; t++) x[t+j_1]=x_vsp[t];
			  delete vsp;
	   }
	   rec=0;
	   for (t=1; t<size_n+1; t++) 
		   if (x[t]==1) rec++;
	   x[0]=rec;
	   return x;

	}

	if (start_rec==true)//ищем начальный рекорд с помощью эвристики
	{
	  //Independent_Set_Problem I;
	  //I=Get_Equivalent_MIS();
	  x=I.Greedy_Algorithm();
	  if (x!=0) 
	  {
		  rec_start=x[0]; 
		  //cout<<"Greedy = ";
		  //for (int i=0; i<size_n+1;i++) cout<<x[i]<<" ";
		  //cout<<endl;
	  }
	  else return 0;
	}
	
	res_n=size_n+1;
	res_m=size_n+size_m+2;
	matr = matrix<double>(res_n,res_m);
	
	x_1=LDSM();//решаем задачу ЛП
    if (x_1!=0)
	{
		Round_Vect(x_1);
		if (Check_Int_LDSM(x_1,Eps)==1) 
		{
		   rec=0;
		   for (int i=1; i<size_n+1; i++) rec=rec+x_1[i];
		   if (rec >= rec_start)
		   {
		   if (x==0) x= new int[size_n+1];
		   for(int i =1; i<size_n+1; i++)
				   x[i]=int(x_1[i]);
		   x[0]=rec;
		   //if ((start_rec==true)||(colzero==true)) delete I;
		   return x;
		   }
		}
	}
	      
	x_1=LEXMAX_M();
	if (x_1==0) return x;
	//for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
	//cout<<endl;
		
	Round_Vect(x_1);
	if (Check_Int(x_1,Eps)==1) 
	{
	 rec=0;
	 for (int i=0; i<size_n; i++) rec=rec+x_1[i];
	 if (rec>=rec_start)
	   { 
		  if (x==0) x= new int[size_n+1];
		  for(int i =1; i<size_n+1; i++)
			   x[i]=int(x_1[i-1]);
		  x[0]=rec;
	   } else rec=rec_start;
	 x_2=x_1;
	 Number_Step=3;
	 //переход на шаг3
	}
	else Number_Step=2;//переход на шаг2
    
	start=clock();
	double sec;
	while (true)
	{
		if (k%50==0) finish=clock();
		sec = ((double)(finish - start) / CLOCKS_PER_SEC);
		if (sec>=3600) 
		{
			if ((colzero==true)&&(arr_inc)) delete[] arr_inc;
			return x;
		}
		switch (Number_Step)
		{
		case 2:
			{
				k++;
				delete[] x_2;
				x_2=x_1;
			
				for (int i=0; i < size_n; i++)
				{
				  if ((fabs(x_2[i]-int(x_2[i]+0.5)))>Eps) 
				  { 
                    p=i;
					break;
				  }
				}
				if (p >= (Matrix_Block_Param->r-1-kol_full_enum_r))
					x_1=LDSM_VSP_BLOCK(rec,d,p,x_2,2,kol_full_enum_block,start_rec, colzero, opt_table_inf);
				else 
				{
				   if (colzero==true)//используем зануление переменных
				   {
				     for(int t=0; t< size_n; t++) arr_inc[t]=1;
				     for(int i=0; i<p ;i++) 
					 if (Round(x_2[i],Decimals)==1)
					 {
						for (int j=p+1; j<size_n; j++)
							if (I.Get(i,j)==1) arr_inc[j]=0;
					 }
				  	}
			    	x_1=LDSM_VSP_FULL(rec,d,p,x_2,arr_inc,2,row_number);
				}//x_1= LDSM_VSP(rec,d,p,x_2,2);

				if (x_1!=0) Round_Vect(x_1);
               // if (x_1!=0)	for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
			//	else cout<<"No solution ";
		//		cout<<"After check iteration number "<<k<<"Record = "<<rec<<endl;
					
				if ((x_1==0)&&(p==0)) {Number_Step=4; continue;}
				if ((x_1==0)&&(p>0)) {Number_Step=3; continue;}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==1)) 
				 {
					 int s=0;
					 for (int tmp=0; tmp<size_n; tmp++) s=s+x_1[tmp];
					 if (s > rec) 
					 {
						 rec=s;
						 if (x==0) x=new int[size_n+1];
					   	 for(int i =1; i<size_n+1; i++)
			             x[i]=int(x_1[i-1]);
						 x[0]=rec;
					 }
					 p=size_n;
					 delete[] x_2;
					 x_2=x_1;
					 Number_Step=3; 
					 continue;
				}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==0)) {Number_Step=2; continue;}
			break;
			}
		case 3:
			{
				k++;
			    int f=-1;
			    for(int i=0; i<p ; i++) 
				  if ((x_2[i]>0)&&(i>f)) f=i;
			    if(f==-1) {Number_Step=4; continue;} 
                
				if (f >= (Matrix_Block_Param->r-1-kol_full_enum_r))
				x_1=LDSM_VSP_BLOCK(rec,d,f,x_2,3,kol_full_enum_block,start_rec, colzero, opt_table_inf);
				else 
				{
				   if ((opt_table_inf==true)&&(f >row_number))
				   f = row_number;

					if (colzero==true)//используем зануление переменных
					{
					for(int t=0; t< size_n; t++) arr_inc[t]=1;
					for(int i=0; i<f ;i++) 
						if (Round(x_2[i],Decimals)==1)
						{
							for (int j=f+1; j<size_n; j++)
								if (I.Get(i,j)==1) arr_inc[j]=0;
						}
					}
				  x_1=LDSM_VSP_FULL(rec,d,f,x_2,arr_inc,3,row_number);
				}//x_1=LDSM_VSP(rec,d,f,x_2,3);

				if (x_1!=0) Round_Vect(x_1);
               // if (x_1!=0)	for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
			//	else cout<<"No solution ";
			//	cout<<"After check iteration number "<<k<<"Record = "<<rec<<endl;
				//cout<<"After check iteration number "<<k<<endl;
								
				if ((x_1==0)&&(f==0)) {Number_Step=4; continue;}
				if ((x_1==0)&&(p>0)) { p=f; Number_Step=3; continue;}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==1)) 
				 {
					 int s=0;
					 for (int tmp=0; tmp<size_n; tmp++) s=s+x_1[tmp];
					 if (s > rec) 
					 {
						 rec=s;
						 if (x==0) x=new int[size_n+1];
					   	 for(int i =1; i<size_n+1; i++)
			             x[i]=int(x_1[i-1]);
						 x[0]=rec;
					 }
					 p=size_n;
					 delete[] x_2;
					 x_2=x_1;
					 Number_Step=3; 
					 continue;
				}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==0)) {Number_Step=2; continue;} 
			break;
			}
		case 4:
			{
				if ((colzero==true)&&(arr_inc)) delete[] arr_inc;
				//if ((start_rec==true)||(colzero==true)) delete I;
				return x;
			}
		}
	}
	if ((colzero==true)&&(arr_inc)) delete[] arr_inc;
	//if ((start_rec==true)||(colzero==true)) delete I;
	return x;			
}
void Packing_Problem:: Shuffle_Dec()
{
	int i,j,k,sum;
	//bool* vsp=0;
    bool vsp;
	int sum_j_1,sum_j;
	int temp;
	
	if (shuffle==0) shuffle=new int[size_n];
	
	for(k=0; k< size_n; k++) shuffle[k]=k;

	for(i=1; i<size_n; i++)
	{
		for(j=size_n-1; j>=i; j--)
		 {
           sum_j_1=0;
		   for(k=0; k<size_m; k++) sum_j_1=sum_j_1+A[k][j-1];		 
		   
		   sum_j=0;
		   for(k=0; k< size_m; k++) sum_j=sum_j+A[k][j];		 
		   
		   if (sum_j_1>sum_j)
		   {
			  //if (vsp==0) vsp = new bool[size_m];
			  for(k=0; k< size_m; k++) 
			  {
				  /*vsp[k]=A[k][j-1];
			      A[k][j-1]=A[k][j];
			      A[k][j]=vsp[k];*/
				  vsp=A[k][j-1];
			      A[k][j-1]=A[k][j];
			      A[k][j]=vsp;
			  }
			  temp = shuffle[j-1];
			  shuffle[j-1]=shuffle[j];
			  shuffle[j]=temp;
		  }
		}
	}
	//for(k=0; k< size_n; k++) cout<<shuffle[k]<<" ";
    
	//if (vsp!=0) delete [] vsp;
	
	flag_shuffle=true;
	//cout<<A;
}

void Packing_Problem::Shuffle_According_Greedy()
{
    int i,j,k,sum;
	//bool* vsp=0;
	bool vsp;
	int sum_j_1,sum_j;
	int temp;
	int cur;
	
	if (shuffle==0) shuffle=new int[size_n];
	for(k=0; k< size_n; k++) shuffle[k]=k;

  	Independent_Set_Problem I;
	I=Get_Equivalent_MIS();
	int* x=I.Greedy_Algorithm();
    //for (i=1; i<size_n+1 ; i++) cout<<x[i]<<" ";
	//cout<<endl;

	cur=0;
	for (i=1; i<size_n+1 ; i++)
	 if (x[i]==1) 
	 {
		 //меняем местами в матрице i-1 столбец и cur
        //if (vsp==0) vsp = new bool[size_m];
		for(k=0; k< size_m; k++) 
		{
		  vsp=A[k][cur];
		  A[k][cur]=A[k][i-1];
		  A[k][i-1]=vsp;
	    }
		temp = shuffle[i-1];
		shuffle[i-1]=shuffle[cur];
		shuffle[cur]=temp;
		cur++;
	 }

 	for(i=x[0]+1; i<size_n; i++)
	{
		for(j=size_n-1; j>=i; j--)
		 {
           sum_j_1=0;
		   for(k=0; k<size_m; k++) sum_j_1=sum_j_1+A[k][j-1];		 
		   
		   sum_j=0;
		   for(k=0; k< size_m; k++) sum_j=sum_j+A[k][j];		 
		   
		   if (sum_j_1>sum_j)
		   {
			  //if (vsp==0) vsp = new bool[size_m];
			  for(k=0; k< size_m; k++) 
			  {
				  vsp=A[k][j-1];
			      A[k][j-1]=A[k][j];
			      A[k][j]=vsp;
			  }
			  temp = shuffle[j-1];
			  shuffle[j-1]=shuffle[j];
			  shuffle[j]=temp;
		  }
		}
	}
	//for(k=0; k< size_n; k++) cout<<shuffle[k]<<" ";
    
	//if (vsp!=0) delete [] vsp;
	
	flag_shuffle=true;
//	cout<<A;
}
void Packing_Problem:: Shuffle_Inc()
{
	int i,j,k,sum;
	//bool* vsp=0;
	bool vsp;
	int sum_j_1,sum_j;
	int temp;
		
	if (shuffle==0) shuffle=new int[size_n];
	
	for(k=0; k< size_n; k++) shuffle[k]=k;

	for(i=1; i<size_n; i++)
	{
		for(j=size_n-1; j>=i; j--)
		 {
           sum_j_1=0;
		   for(k=0; k<size_m; k++) sum_j_1=sum_j_1+A[k][j-1];		 
		   
		   sum_j=0;
		   for(k=0; k< size_m; k++) sum_j=sum_j+A[k][j];		 
		   
		   if (sum_j_1<sum_j)
		   {
			  //if (vsp==0) vsp = new bool[size_m];
			  for(k=0; k< size_m; k++) 
			  {
				  vsp=A[k][j-1];
			      A[k][j-1]=A[k][j];
			      A[k][j]=vsp;
			  }
			  temp = shuffle[j-1];
			  shuffle[j-1]=shuffle[j];
			  shuffle[j]=temp;
		  }
		}
	}
	   
	//if (vsp!=0) delete [] vsp;
	
	flag_shuffle=true;
	
	//cout<<A;
}

void Packing_Problem:: Undo_Shuffle()
{
  bool* vsp;
  int k,tmp,t;
   if (flag_shuffle==true)
   {
       //matrix<bool> vsp;
	   //vsp=matrix<bool>(size_n,size_m);
       
	   matrix<bool> vsp(size_n,size_m);
	   
	   //matrix<bool>* vsp;
	   //vsp=new matrix<bool>(size_n,size_m);
       

	   for(int t=0; t< size_n; t++)
	   {
	     tmp = shuffle[t];
		 for(k=0; k< size_m; k++) vsp[k][tmp]=A[k][t];
	   }
	   for(int i=0; i<size_n; i++)
		for (int j=0;j<size_m;j++)
			A[j][i]=vsp[j][i];
	   
       flag_shuffle=false;
	   
	   //delete vsp;
	   //cout<<A;
  }
}


int* Packing_Problem::Go_Over_L_Class_Kuz(int d, int &k, int &kol_sol, int &kol_after_update, double* &x_lp, bool start_rec, bool colzero, bool opt_table_inf, int rec_st)
{
	int p=size_n;//номер первой дробной координаты
    k=0;//номер итерации;
	kol_sol=0;
    kol_after_update=0;
	x_lp=0;

	int rec=-100;//рекорд целевой функции
	int rec_start=-100;
	int Number_Step;
	int* x=0;//наилучшее решение в данный момент,соответствующие рекорду
	double* x_1;
	double* x_2;
	bool* arr_inc;
	int row_number=size_n;
	Independent_Set_Problem I;
	clock_t start, finish;
	double sec;
    if (colzero==true) arr_inc= new bool[size_n]; else arr_inc=0;
	//-----------------------------------------------------------
 /*   int tmp;
	int rec_add=0;//добавочный рекорд
	for(int j=0; j<size_n; j++)//нулевые столбцы
	{
		tmp=0;
		for (int i=0;i<size_m;i++) if (A[i][j]==1) tmp=1;
		if (tmp==0) rec_add++;
	}
	int* numbers=new int[rec_add];
	int q=0;
	for(int j=0; j<size_n; j++)//нулевые столбцы
	{
		tmp=0;
		for (int i=0;i<size_m;i++) if (A[i][j]==1) tmp=1;
		if (tmp==0) { numbers[q]=j; q++; }
	}
    int m,n;
	n=size_n-rec_add;
    matrix<bool> temp(n,size_m);
	int j_1=0;
	for(int j=0; j<n; j++)
	{ 
		bool flag=0;
		for(int h=0;h<rec_add; h++) 
			if (numbers[h]==j) 
			{
				flag=true;
				break;
			}
		if (flag==false)
		{
           for(int i=0; i<size_m; i++)
			  temp[i][j_1]=A[i][j];
		   j_1++;
		}
     }
	 this->A=temp;
	 size_n=n;
*/
	//-----------------------------------------------------------
	Set_Decimals(8);
    double Eps=pow(10.0,-Decimals+1);//точность из за ошибок округления страдает, 
	//и вектора отличающиеся на Eps считаються равными
    
	
	if (colzero==true)  I=Get_Equivalent_MIS();
	/*
	if ((start_rec==true)||(colzero==true))  I=Get_Equivalent_MIS();
	if (start_rec==true)//ищем начальный рекорд с помощью эвристики
	{
	  x=I.Greedy_Algorithm();
	  if (x!=0){
		  rec_start=x[0];
		  // cout<<"Greedy = ";
		  //for (int i=0; i<size_n+1;i++) cout<<x[i]<<" ";
		  //cout<<endl;
	  }else return 0;
	}*/
	if (start_rec==true) rec_start=rec_st;
	
	res_n=size_n+1;
	res_m=size_n+size_m+2;
	matr = matrix<double>(res_n,res_m);

	x_lp=LDSM();//решаем задачу ЛП
    for (int i=0; i<size_n+1;i++) cout<<x_lp[i]<<" ";
	cout<<endl;
	if (x_lp!=0)
	{
		Round_Vect(x_lp);
		if (Check_Int_LDSM(x_lp,Eps)==1) 
		{
		   rec=0;
		   for (int i=1; i<size_n+1; i++) rec=rec+x_lp[i];
		   if (rec>=rec_start)
		   {
		   if (x==0) x= new int[size_n+1];
		   for(int i =1; i<size_n+1; i++)
				   x[i]=int(x_lp[i]);
		   x[0]=rec;
	       return x;
		   }
		}
	}
	
	if (opt_table_inf==true) x_1=LEXMAX_M_WITH_INFO(row_number);
	else x_1=LEXMAX_M();
    //cout<<"RoW Number = "<<row_number<<endl;	
	if (x_1==0) return x;
	//for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
	//cout<<endl;
		
	Round_Vect(x_1);
	if (Check_Int(x_1,Eps)==1) 
	{
	 rec=0;
	 for (int i=0; i<size_n; i++) rec=rec+x_1[i];
	 if (rec>=rec_start)
	   { 
		  if (x==0) x= new int[size_n+1];
		  for(int i =1; i<size_n+1; i++)
			   x[i]=int(x_1[i-1]);
		  x[0]=rec;
	   } else rec=rec_start;
	 x_2=x_1;
	 Number_Step=3;
	 //переход на шаг3
	}
	else Number_Step=2;//переход на шаг2
    
	while (true)
	{
		/*if (k%50==0) finish=clock();
		sec = ((double)(finish - start) / CLOCKS_PER_SEC);
		if (sec>=2000) 
		{
			if ((colzero==true)&&(arr_inc)) delete[] arr_inc;
			return x;
		}*/
		switch (Number_Step)
		{
		case 2:
			{
				k++;
				x_2=x_1;
			
				for (int i=0; i < size_n; i++)
				{
				  if ((fabs(x_2[i]-int(x_2[i]+0.5)))>Eps) 
				  { 
                    p=i;
					break;
				  }
				}
				
				if ((opt_table_inf==true)&&(p >row_number))
					p = row_number;

				if (colzero==true)//используем зануление переменных
				{
				  for(int t=0; t< size_n; t++) arr_inc[t]=1;
				  for(int i=0; i<p ;i++) 
					if (Round(x_2[i],Decimals)==1)
					{
						for (int j=p+1; j<size_n; j++)
							if (I.Get(i,j)==1) arr_inc[j]=0;
					}
				}
				x_1=LDSM_VSP_FULL(rec,d,p,x_2,arr_inc,2,row_number);
				//cout<<"RoW Number = "<<row_number<<endl;								
				//if (x_1!=0) Round_Vect(x_1);
                //if (x_1!=0)	for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
				//else cout<<"No solution ";
				//cout<<"After check iteration number "<<k<<"Record = "<<rec<<endl;
					
				if ((x_1==0)&&(p==0)) {Number_Step=4; continue;}
				if ((x_1==0)&&(p>0)) {Number_Step=3; continue;}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==1)) 
				 {
					 int s=0;
					 for (int tmp=0; tmp<size_n; tmp++) s=s+x_1[tmp];
					 if (s > rec) 
					 {
						 rec=s;
						 if (x==0) x=new int[size_n+1];
					   	 for(int i =1; i<size_n+1; i++)
			             x[i]=int(x_1[i-1]);
						 x[0]=rec;
					 }
					 p=size_n;
					 x_2=x_1;
					 Number_Step=3; 
					 kol_sol++;
					 kol_after_update=0;
					 continue;
				}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==0)) {kol_sol++; kol_after_update++; Number_Step=2; continue;}
			break;
			}
		case 3:
			{
				k++;
			    int f=-1;
			    for(int i=0; i<p ; i++) 
				  if ((x_2[i]>0)&&(i>f)) f=i;
			    if(f==-1) {Number_Step=4; continue;} 
                
				if ((opt_table_inf==true)&&(f >row_number))
					f = row_number;

				if (colzero==true)//используем зануление переменных
				{
				for(int t=0; t< size_n; t++) arr_inc[t]=1;
				for(int i=0; i<f ;i++) 
					if (Round(x_2[i],Decimals)==1)
					{
						for (int j=f+1; j<size_n; j++)
							if (I.Get(i,j)==1) arr_inc[j]=0;
					}
				}
               // if (arr_inc!=0) for (int i=0; i<size_n;i++) cout<<arr_inc[i]<<" ";
				x_1=LDSM_VSP_FULL(rec,d,f,x_2,arr_inc,3,row_number);
				//cout<<"RoW Number = "<<row_number<<endl;
				if (x_1!=0) Round_Vect(x_1);
                //if (x_1!=0)	for (int i=0; i<size_n;i++) cout<<x_1[i]<<" ";
				//else cout<<"No solution ";
				//cout<<"After check iteration number "<<k<<"Record = "<<rec<<endl;
				//cout<<"After check iteration number "<<k<<endl;
								
				if ((x_1==0)&&(f==0)) {Number_Step=4; continue;}
				if ((x_1==0)&&(p>0)) { p=f; Number_Step=3; continue;}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==1)) 
				 {
					 int s=0;
					 for (int tmp=0; tmp<size_n; tmp++) s=s+x_1[tmp];
					 if (s > rec) 
					 {
						 rec=s;
						 if (x==0) x=new int[size_n+1];
					   	 for(int i =1; i<size_n+1; i++)
			             x[i]=int(x_1[i-1]);
						 x[0]=rec;
					 }
					 p=size_n;
					 x_2=x_1;
					 Number_Step=3; 
					 kol_sol++;
					 kol_after_update=0;
					 continue;
				}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==0)) {kol_sol++; kol_after_update++; Number_Step=2; continue;} 
			break;
			}
		case 4:
			{
				/*if (rec_add!=0) 
				{
					x[0]=x[0]+rec_add;
				      for(int i=0;i<rec_add;i++) x[numbers[i]]=1;
				}*/
				if ((colzero==true)&&(arr_inc)) delete[] arr_inc;
				return x;
			}
		}
	}
	/*if (rec_add!=0) 
	{
		x[0]=x[0]+rec_add;
		for(int i=0;i<rec_add;i++)
		x[numbers[i]]=1;
	}*/
	if ((colzero==true)&&(arr_inc)) delete[] arr_inc;
	return 0;			
}


char* its(int value)
{
	int len=0;
	int val=value;
	int rest=val%10;
	if (value<10) len++;
	if ((value>=10)&&(value<100)) len=2;
	if ((value>=100)&&(value<1000)) len=3;
	if ((value>=1000)&&(value<10000)) len=4;

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
int file_number=0;
//-------------------------------------------------------------------------------------------
void Packing_Problem::ConvertMatrix_to_BlockMatrix()
{   /*
	надо перезаписать элементы матрицы А, к этому же
	заполнить структуру matrix_block_param
	
	В главное программе:
	1. создаем задачу по произвольной матрице
	2. вызываем ConvertMatrix_to_BlockMatrix
	3. вызываем перебор l-классов блочный
	*/
	
	/* Дано матрица A и ее размеры
    1. построить граф пересечений для матрицы A
	
	I.find_vertex_connectivity()
	2. найти в графе вершины, которые нужно удалить чтобы он распался
		
	I.del_vertex_and_find_components(array_vertex);
	4. удалить найденные вершины из графа вместе с инцендентными ребрами
	5. в оставшемся графе запустить поиск компонент связности волным алгоритом
	
	Shuffle_matrix_coloms(array_vertex, matr_component);
	6. переупорядочить столбцы матрицы в соответствии с разбиением на компоненты связности
    
	Shuffle_matrix_lines_and_fill_mbp(array_vertex, matr_component);
	7. переупорядочить строки чтобы получились блоки
	3. столбцы матрицы, соответсвующие найденным вершинам отнести к связующему блоку
	8. заполнить matrix_block_param
	*/
    
	Independent_Set_Problem I;
	I=Get_Equivalent_MIS();
	int* array_vertex;
	matrix<bool> matr_component;
	
	//matrix<bool> graph = matrix<bool>(10,10);
	/*for(int i=0; i<10; i++)
		for(int j=0; j<10; j++)
			if (i==j) graph[i][j]=1;
			else graph[i][j]=0;*/
	/*graph[0][1]=1; graph[1][0]=1;
	graph[0][2]=1; graph[2][0]=1;
	graph[1][2]=1; graph[2][1]=1;
	graph[3][4]=1; graph[4][3]=1;
	graph[4][5]=1; graph[5][4]=1;
	graph[3][5]=1; graph[5][3]=1;
	graph[6][8]=1; graph[8][6]=1;
	graph[7][8]=1; graph[8][7]=1;
	graph[6][7]=1; graph[7][6]=1;
	graph[9][2]=1; graph[2][9]=1;
	graph[9][5]=1; graph[5][9]=1;
	graph[9][6]=1; graph[6][9]=1;
	Independent_Set_Problem* I = new Independent_Set_Problem(graph);
	*/
	//-------
	//cout<<*(I.GetGraph());
	//--------------------------------------------------
	I.find_articulation_point();
	array_vertex = I.common_cols;
	
	/*for(int i=0; i<size_n; i++)
		cout<<array_vertex[i]<<" ";*/
	
	//-----поиск задач упаковки с графом пересечений содержащим точку сочленения----
	/*int count=0;
	for(int i=0; i<size_n; i++)
		if (array_vertex[i]==1)
			count++;
	ofstream OutFile;
	OutFile.open("D:\logtest.txt",ios_base::app);
    
	if (count>0) 
	{
		int j;
		char sl=CHAR(92);
		string filename1;
		char* filename;
								
		filename1="";
		filename1=filename1+"d:"+sl+"Test"+sl+"T"+its(file_number)+".txt";
		filename=new char[100];
		int h=0;
		while (filename1[h]){
		  filename[h]=filename1[h];
		  h++;
		}
		filename[h]='\0';
					
		
		Save_MSP_In_File(filename);			 
		OutFile<<"yes"<<" ";
		cout<<"yes"<<" ";
		file_number++;
	}
	else 
	{
		OutFile<<"no "<<" ";
		cout<<"no "<<" ";
	}
	OutFile.close();
    */
	matr_component = I.del_vertex_and_find_components(array_vertex);
	
	/*for(int i=0; i<size_n ; i++)
	{
		cout<<endl;
		for(int j=0; j<size_n; j++)
			cout<<matr_component[i][j]<<" ";
	}*/
	
	//--------------------------------------------------
	//--------------------------------------------------
	//matr_component=I.evristic_algorithm(3, array_vertex);
	///-------------------------------------------------
	//--------------------------------------------------
	//array_vertex = I.find_vertex_connectivity();
	//matr_component = I.del_vertex_and_find_components(array_vertex);
	//--------------------------------------------------
	    
	Shuffle_matrix_coloms(array_vertex, matr_component);
    Shuffle_matrix_lines_and_fill_mbp(array_vertex, matr_component);
}

void Packing_Problem:: Shuffle_matrix_coloms(int* array_vertex, matrix<bool> matr_component)
{
	int i,j,k,sum;
	bool vsp;
	int temp;
	int vertex_number;

	if (shuffle==0) shuffle=new int[size_n];
	for(k=0; k< size_n; k++) shuffle[k]=k;
    
	//перемещаем связующие столбцы в начало
	vertex_number =0;
	for (int i=0; i<size_n; i++)
	{
		if (array_vertex[i]==1)
		{
		   if (i==vertex_number)
		   {
			   vertex_number++;
			   continue;
		   }
		   for(k=0; k< size_m; k++) 
		   {
			  vsp=A[k][vertex_number];
		      A[k][vertex_number]=A[k][i];
		      A[k][i]=vsp;
		   }
		  temp = shuffle[vertex_number];
		  shuffle[vertex_number]=shuffle[i];
		  shuffle[i]=temp;
          vertex_number++;
		  /*for(int i=0; i<size_n; i++)
			  cout<<shuffle[i]<<" ";
		  cout<<endl;*/
		}
	}

    //перемещаем столбцы отвечающие компонентам
    for(int i=0; i<size_n; i++)//цикл по компонентам
	{
		for(int j=0; j< size_n; j++)//цикл по вершинам в компоненте
		{
           if (matr_component[i][j]==1)
		   {
			  int t=0;
			  while (shuffle[t]!=j) t++;
			  //меняем местами столбцы j и vertex_number
			  if (t==vertex_number){
				  vertex_number++;
				  continue;
			  }
			  for(k=0; k< size_m; k++) 
			  {
				  vsp=A[k][t];
				  A[k][t]=A[k][vertex_number];
				  A[k][vertex_number]=vsp;
			  }
			  //int s=0;
			  //while (shuffle[s]!=vertex_number) s++;
			  
			  /*temp = shuffle[t];
			  shuffle[t]=shuffle[s];
			  shuffle[s]=temp;*/
			  temp = shuffle[vertex_number];
			  shuffle[vertex_number]=j;
			  shuffle[t]=temp;
			  		  
			  vertex_number++;
			  
			 /*for(int s=0; s<size_n; s++)
			  cout<<shuffle[s]<<" ";
			  cout<<endl;*/

		   }
		}
	}

	flag_shuffle=true;
	//cout<<"sort cols"<<A;

}
void Packing_Problem:: Shuffle_matrix_lines_and_fill_mbp(int* array_vertex, matrix<bool> matr_component)
{
	int n_size, m_size;
	bool  flag;
	int r = 0;
	for (int i=0; i<size_n; i++)
		if (array_vertex[i]==1) r++;
	
	/*cout<<"array_vertex=";
	for (int i=0; i<size_n; i++)
		cout<<array_vertex[i]<<" ";
	cout<<endl;*/
	
	int block_kol =0;
	for (int i=0; i<size_n; i++)
		for (int j=0; j<size_n; j++)
			if (matr_component[i][j]==1)
			{
				block_kol++;
				break;
			}
   
	/*cout<<"r="<<r<<endl;
	cout<<"block_kol="<<block_kol<<endl;*/
	
	//------------------создание блочной структуры-------------------//
	Matrix_Block_Param=new Block;
	Matrix_Block_Param->r=r;
	Matrix_Block_Param->block_kol=block_kol;
	Matrix_Block_Param->Blocks=new Block_size[block_kol];
	Decimals=5;//точность для перебора l-классов;
	//-----------------------------------------------------------------
	int count;
	int block_number =-1;
	for (int i=0; i<size_n; i++)
	{
		count =0;
		for (int j=0; j<size_n; j++)
			if (matr_component[i][j]==1)
				count++;
        if (count == 0)
			continue;
        block_number ++;
		Matrix_Block_Param->Blocks[block_number].n_size=count; 
		//cout<<"block "<<block_number<<" size="<<count<<endl;
	}
	
	//------сортировка строк и фиксация размеров блоков---------------//
    int line_number =0;
	int vsp,j;
	for(block_number=0; block_number<block_kol; block_number++)
	{
		m_size =0;
		int sum =0;
	    for(int s=0; s<block_number; s++)
		   sum = sum + Matrix_Block_Param->Blocks[s].n_size;
		int left_border = r+ sum;
		int right_border = left_border + Matrix_Block_Param->Blocks[block_number].n_size;
			
	    for(int i=0; i<size_m; i++)
	    {
		    flag = false;
		    for (j=0; j<size_n; j++)
               if ((j>= left_border)&&(j< right_border)&&(A[i][j]==1))
			   {
				   flag=true;
				   break;
			   }
			 if (flag)
			 {	//меняем местами line_number и j
				 if (line_number==i)
				 {
					 m_size++;
					 line_number++;
					 continue;
				 }
				 for(int k=0; k< size_n; k++) 
			     {
				   vsp=A[line_number][k];
				   A[line_number][k]=A[i][k];
				   A[i][k]=vsp;
			     }
				 m_size++;
			     line_number++; 
			 }
	    }
       Matrix_Block_Param->Blocks[block_number].m_size=m_size;
	}
	 
    
}
