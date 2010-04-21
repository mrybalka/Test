#include "stdafx.h"
#pragma warning disable

Problem:: Problem()
{
	size_m=3;
	size_n=2;
	C=new int[2];
	C[0]=1;
	C[1]=3;
	B=new int[3];
	B[0]=7;
	B[1]=9;
	B[2]=5;
	A = matrix<int>(size_n,size_m);
	A[0][0]=-2;
	A[0][1]=4;
	A[1][0]=3;
	A[1][1]=4;
	A[2][0]=2;
	A[2][1]=-4;
	Decimals=5;//по умолчанию
}

bool Problem::Lexmax(double* x_1,double* x_2,int size)
//Проверяет больше ли первый вектор второго
{
	double EPS=0.000000001;
		for(int i=0; i<size; i++)
		{
			if (abs(x_1[i]-x_2[i])<EPS) continue;
			else
			{
			if (x_1[i]>x_2[i]) return true;
			if (x_1[i]<x_2[i]) return false;
			}
		}
		return true;
}


bool Problem::Lexmax_Vect(matrix<double> &matr, int j, int k)
//сравнивает j и k столбец в матрице matr
{
      double EPS=pow(10.0, -Decimals+1);
		for(int i=0; i<matr.ret_h(); i++)
		{
			if (abs(matr[i][j]-matr[i][k])<EPS) continue;
			else
			{
			if (matr[i][j]>matr[i][k]) return true;
			if (matr[i][j]<matr[i][k]) return false;
			}
		}
		return true;
}
bool Problem::Lexmax_Vect_with_zero(matrix<double> &matr, int j)
//сравнивает j столбец в матрице matr c нулем
//истина если лексикографически больше нуля
{
      double EPS=pow(10.0, -Decimals+1);
		for(int i=0; i<matr.ret_h(); i++)
		{
			if (abs(matr[i][j]-0.0)<EPS) continue;
			else
			{
			if (matr[i][j]>0.0) return true;
			if (matr[i][j]<0.0) return false;
			}
		}
		return true;
}

bool Problem::Check_L_Norm(matrix<double> &matr)
{
	for(int j=0; j<matr.ret_w(); j++)
	  if (Lexmax_Vect_with_zero(matr,j)==false)
	    return false;
	 return true;
}

void Problem:: Make_L_Norm(matrix<double> &matr)
{
	int M=size_n;
	int q=0;
	//cout<<"Print before Make L- norm"<<matr;
	if (Check_L_Norm(matr)==false)
	{
		matr[matr.ret_h()-1][0]=M;
		for(int j=1; j<matr.ret_w(); j++)
			matr[matr.ret_h()-1][j]=1;
	
		for(int j=1; j<matr.ret_w();j++)
    		if (Lexmax_Vect_with_zero(matr,j)==false)//лексикографически меньше 0
	        {
			   if (q==0) q=j; else if (Lexmax_Vect(matr,q,j)) q=j; 
		    }
			//cout<<"Main Line "<<(matr.ret_h()-1)<<endl;
			//cout<<"Main col "<<q<<endl;
			Preobrazovanie_Matrix(matr,(matr.ret_h()-1),q);
			//cout<<"After make L-norm"<<matr;	  
	}//if
}
int Problem::Check_L_Opim(matrix<double> &matr)
//проверяем является ли таблица прямодопустимой, если нет то возвращеться 
//номер строки в которой допустимость нарушается, то есть номер след.вед.строки
{
	for(int i=1;i<(matr.ret_h()-1);i++)
		if (matr[i][0]<0) return i;
	return -1;
}
int Problem::Select_main_column(matrix<double> &matr,int main_line)
//ищем номер ведущего столбца
{
	int result=0;
	int k;
	double EPS=pow(10.0, -Decimals+1);

	for(int j=1; j<matr.ret_w();j++)
	{
       if (matr[main_line][j]<0) 
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
	}//for
			   
return result;
}


void Problem::Preobrazovanie_Matrix(matrix<double> &matr,int p,int q)
//Одно преобразование симплексной таблицы
{
	for (int i=0; i<matr.ret_h(); i++)
		for (int j=0; j<matr.ret_w(); j++)
		{
			if ((i!=p)&&(j!=q)) matr[i][j]=matr[i][j]-matr[i][q]*matr[p][j]/matr[p][q];
		}
	for (int i=0; i<matr.ret_h(); i++)
	  if (i!=p) matr[i][q]=-matr[i][q]/matr[p][q];
	for (int j=0; j<matr.ret_w(); j++)
		if (j!=q) matr[p][j]=0;
	matr[p][q]=-1;
	
}

double* Problem::LDSM()
{
	int i,j;
	matrix<double> matr(size_n+1,size_n+size_m+2);
    //-----------------заполняем начальную таблицу-----------------------
	matr[0][0]=0;
	for (j=1; j<size_n+1; j++) matr[0][j]=-C[j-1];
	for(i=1; i<=size_n; i++)
		{
			for (j=0; j<size_n+1; j++)
              if (i==j)	matr[i][j]=-1; else matr[i][j]=0; 
			
		}
	for(i=size_n+1; i<size_n+size_m+1; i++)
		{
			for (j=0; j<size_n+1; j++)
              if (j==0)	matr[i][j]=B[i-size_n-1]; else matr[i][j]= A[i-size_n-1][j-1]; 
			
		}
    for (j=0; j<size_n+1; j++) matr[size_n+size_m+1][j]=0;
	//------------------------------------------------------------------
    // В общем случае надо проверить чтобы начальная таблица была двойственно допустимой
	//то есть чтобы все столбцы были lex больше 0;
	//cout<<matr;
	Make_L_Norm(matr);
    //cout<<matr;
	int p;//номер ведущей строки
	int q;//номер ведущего столбца

	while (true)
	{
	  p=Check_L_Opim(matr);
	  if (p==-1)//нашли решение
	  {	
	     double* x;
	     x=new double[size_n+1];//x0=значение ц.ф
	     for(int i=0; i<size_n+1; i++)
	     x[i]=matr[i][0];
	     return x;
      }
	  //проверка разрешимости !!!!! переделать! неверно!
	   bool flag=0;
	  for(j=1;j<size_n+1;j++)
		 if (matr[p][j]<0) flag=1;
	
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
//return 0;
}

double* Problem::LEXMAX_M()
//ЛДСМ без цел.функии
{
	int i,j;
	matrix<double> matr(size_n+1,size_n+size_m+1);
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
              if (j==0)	matr[i][j]=B[i-size_n]; else matr[i][j]= A[i-size_n][j-1]; 
		}
    for (j=0; j<size_n+1; j++) matr[size_n+size_m][j]=0;
	//------------------------------------------------------------------
    // В общем случае надо проверить чтобы начальная таблица была двойственно допустимой
	//то есть чтобы все столбцы были lex больше 0;

	Make_L_Norm(matr);
    //cout<<matr;
	int p;//номер ведущей строки
	int q;//номер ведущего столбца

	while (true)
	{
	  p=Check_L_Opim(matr);
	  if (p==-1)//нашли решение
	  {	
	     double* x;
	     x=new double[size_n];//нету значение ц.ф
	     for(int i=0; i<size_n; i++)
	     x[i]=matr[i][0];
	     return x;
      }
	  //проверка разрешимости !!!!! переделать! неверно!
	   bool flag=0;
	  for(j=1;j<size_n+1;j++)
		 if (matr[p][j]<0) flag=1;
	
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
	
	//return 0;
}
double* Problem::LDSM_VSP(int rec,int d, int num, double* x_2,int number_step)
//num- это номер первой дробной координаты вектора x_2(в алгоритме обозн p)
//Function_Line шагаем мы по линиям уровня и на них перебираем L-классы, 
//или перебираем L-классы во всем множестве. от этого зависит сколько строк будет в матрице
//точнее останеться ли первай строка с целевой функцией
{
	int i,j;
	int n,m;
	
	m=size_n-num+1+size_m+4;
	//else m=size_n-num+1+size_m+3;
	
	matrix<double> matr(size_n-num+2,m);
		
	switch (number_step) 
	{
	  case 2:
		  {		
			 //-----------------заполняем начальную таблицу-----------------------
				matr[0][0]=0;
				for (j=1; j<size_n-num+2; j++) matr[0][j]=-C[j-2+num];
				for(i=1; i<=size_n-num+1; i++)
					{
						for (j=0; j<size_n-num+2; j++)
						  if (i==j)	matr[i][j]=-1; else matr[i][j]=0; 
						
					}
				
				for(i=size_n-num+2; i<size_n-num+1+size_m+1; i++)
					{
						for (j=0; j<size_n-num+2; j++)
						  if (j==0)	
						  {
                             int s=0;
							 for(int t=0; t<num-1;t++)
							   s=s+A[i-size_n+num-2][t]*Round(x_2[t+1],8);
							 
                             matr[i][j]=B[i-size_n+num-2]-s;
						  }
						  else
						   matr[i][j]= A[i-size_n+num-2][j+num-2]; 
				  
					}
				for (j=0; j<size_n-num+2; j++) 
				{
					if (j==0) matr[size_n-num+1+size_m+1][j]=int(x_2[num]);
					if (j==1) matr[size_n-num+1+size_m+1][j]=1;
					if ((j!=0)&&(j!=1)) matr[size_n-num+1+size_m+1][j]=0;
				}
				
				//ограничение по рекорду
             	for (j=0; j<size_n-num+2; j++) 
				{
					if (j==0) 
				 {   
					 int tmp=0;
					 for(int t=0; t<num-1;t++)
						tmp=tmp+C[t+1]*Round(x_2[t+1],8);
					 matr[size_n-num+1+size_m+2][j]=-(rec+d)+tmp;
				 }
					else 
					{
				   	matr[size_n-num+1+size_m+2][j]=-C[j-2+num];
				    }
				}

				for (j=0; j<size_n-num+2; j++) matr[size_n-num+1+size_m+3][j]=0;
				//пустая строка для того чтобы сделать таблицу l-нормальной
				//----------------------------------------------------------------
			    //cout<<matr;
			   break;
			  }
		  case 3:
		  {
			  	//-----------------заполняем начальную таблицу-----------------------
				matr[0][0]=0;
				for (j=1; j<size_n-num+2; j++) matr[0][j]=-C[j-2+num];
				for(i=1; i<=size_n-num+1; i++)
					{
						for (j=0; j<size_n-num+2; j++)
						  if (i==j)	matr[i][j]=-1; else matr[i][j]=0; 
						
					}
				
				for(i=size_n-num+2; i<size_n-num+1+size_m+1; i++)
					{
						for (j=0; j<size_n-num+2; j++)
						  if (j==0)	
						  {
                             int s=0;
							 for(int t=0; t<num-1;t++)
							   s=s+A[i-size_n+num-2][t]*Round(x_2[t+1],8);
							 
                             matr[i][j]=B[i-size_n+num-2]-s;
						  }
						  else
						    matr[i][j]= A[i-size_n+num-2][j+num-2]; 
				  	}
				for (j=0; j<size_n-num+2; j++) 
				{
					if (j==0) matr[size_n-num+1+size_m+1][j]=(x_2[num]-1);
					if (j==1) matr[size_n-num+1+size_m+1][j]=1;
					if ((j!=0)&&(j!=1)) matr[size_n-num+1+size_m+1][j]=0;
				}
				
				//ограничение по рекорду
               	for (j=0; j<size_n-num+2; j++) 
				{
					if (j==0) 
				 {   
					 int tmp=0;
					 for(int t=0; t<num-1;t++)
						tmp=tmp+C[t+1]*Round(x_2[t+1],8);
					 matr[size_n-num+1+size_m+2][j]=-(rec+d)+tmp;
				 }
					else 
					{
				   	matr[size_n-num+1+size_m+2][j]=-C[j-2+num];
				    }
				}

				for (j=0; j<size_n-num+2; j++) matr[size_n-num+1+size_m+3][j]=0;
				//пустая строка для того чтобы сделать таблицу l-нормальной
			// cout<<matr;
			break;
		  }
	}
	
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
	     x=new double[matr.ret_w()];//x0=значение ц.ф
	     for(int i=0; i<matr.ret_w(); i++)
	     x[i]=matr[i][0];
	     
		 double* tmp=new double[size_n+1];
		 tmp[0]=x[0];
		 for (int t=1; t<num; t++) tmp[t]=x_2[t];
		 for (int t=num; t<size_n+1; t++) tmp[t]=x[t-num+1];
		 return tmp;
		 //return x;
      }
	  //проверка разрешимости !!!!! 
	  bool flag=0;
	  for(j=1;j<matr.ret_w();j++)
	  {
		  if (matr[p][j]<0) flag=1;
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
}
bool Problem::Check_Int(double* x, double Eps)
{
	bool flag=1;
	for (int i=0; i<size_n; i++)
    	if (fabs(x[i]-int(x[i]+0.5))>Eps) flag=0;
	return flag;
}
void Problem::Round_Vect(double* &x)
{
	for(int i=0; i<size_n; i++)
	x[i]=Round(x[i],Decimals);

}
double Problem::Round(double v, int decimals)
{
	int sgn =v/fabs(v);
	double eps = sgn*pow(10.0,(-decimals));
	double rmr = fmod( v, eps );
	v -= rmr;
	if( sgn*rmr - sgn*(eps / 2)>=DBL_EPSILON )
		v += eps;
	return v;
}//double Round(double v, int decimals)

int* Problem::Go_Over_L_Class_Standart(int d, int &k)
//d-параметр алгоритма, 1-точное решение, 2-приближенное решение
{
 //решить задачу ЛП, проверить если решение целочисленное то вернуть его, если нет то
 //весь следующий текст
	int p=-1;//номер первой дробной координаты
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

	x_1=LDSM();//что если здесь не будет решения!
	if (x_1==0) return 0;
	Round_Vect(x_1);
	if (Check_Int(x_1,Eps)==1) 
	{
	 rec=x_1[0];
	 if (rec>rec_start)
	   { 
		  if (x==0) x= new int[size_n+1];
		  for(int i =0; i<size_n+1; i++)
			   x[i]=int(x_1[i]);
	   } else rec=rec_start;
	 Number_Step=3;
	 //переход на шаг3
	}
	else Number_Step=2;//переход на шаг2
    
	while (k<10)
	{
		switch (Number_Step)
		{
		case 2:
			{
				k++;
				x_2=x_1;
			
				for (int i=1; i<size_n+1; i++)
				{
				  if ((fabs(x_2[i]-int(x_2[i]+0.5)))>Eps) 
				  { 
                    p=i;
					break;
				  }
				}
				x_1=LDSM_VSP(rec,d,p,x_2,2);
				if (x_1!=0) Round_Vect(x_1);
                if (x_1!=0)	for (int i=0; i<size_n+1;i++) cout<<x_1[i]<<" ";
				else cout<<"No solution ";
				cout<<"After check"<<endl;
								
				if ((x_1==0)&&(p==1)) {Number_Step=4; continue;}
				if ((x_1==0)&&(p>1)) {Number_Step=3; continue;}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==1)) 
				 {
					 int s=0;
					 for (int tmp=0; tmp<p-1; tmp++) 
						  s=s+C[tmp]*x_1[tmp+1];
					 rec=x_1[0]+s;
					 
                     if (x==0) x=new int[size_n+1];
					 x[0]=rec;
					 for(int i =1; i<size_n+1; i++)
			         x[i]=int(x_1[i]);
					 p=size_n+1;
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
			    int f=0;
			    for(int i=1; i<p ; i++) 
				  if ((x_2[i]>0)&&(i>f)) f=i;
			    if(f==0) {Number_Step=4; continue;} 
                
				x_1=LDSM_VSP(rec,d,f,x_2,3);
				if (x_1!=0) Round_Vect(x_1);
                if (x_1!=0)	for (int i=0; i<size_n+1;i++) cout<<x_1[i]<<" ";
				else cout<<"No solution ";
				cout<<"After check"<<endl;
								
				if ((x_1==0)&&(f==1)) {Number_Step=4; continue;}
				if ((x_1==0)&&(p>1)) { p=f; Number_Step=3; continue;}
				if ((x_1!=0)&&(Check_Int(x_1,Eps)==1)) 
				 {
					  int s=0;
					 for (int tmp=0; tmp<p; tmp++) s=s+C[tmp]*x_2[tmp+1];
					 rec=x_1[0]+s;
					 if (x==0) x=new int[size_n+1];
					 x[0]=rec;
					 for(int i =1; i<size_n+1; i++)
			         x[i]=int(x_1[i]);
					 p=size_n+1;
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
/*
int Problem::Select_main_column(matrix<double> matr,int main_line)
//ищем номер ведущего столбца
{
	double* x_1=0;
	double* x_2=0;
	int result;
	for(int j=1; j<matr.ret_w();j++)
	{
       if (matr[main_line][j]<0) 
	   {
		   if (x_1==0)
		   { 
			   x_1 = cut_col_j(matr,j);
			   result=j;
		   }
		   else 
		   {
			   x_2=cut_col_j(matr,j);
			   Del_const(x_2,matr[main_line][j],matr.ret_h());
               Del_const(x_1,matr[main_line][j],matr.ret_h());
			   if (Lexmax(x_2,x_1,matr.ret_h())) 
			   {
				   x_1=x_2;
				   result=j;
			   }
	       }
	   }
	}
	return result;
}*/
/*void Problem:: Make_L_Norm(matrix<double> &matr)
{
	int M=30;
	int q;
	//cout<<"Print before Make L- norm"<<matr;
	if (Check_L_Norm(matr)==false)
	{
		matr[matr.ret_h()-1][0]=M;
		for(int j=1; j<matr.ret_w(); j++)
			matr[matr.ret_h()-1][j]=1;
	
			double* x_1=0;
			double* x_2=0;
			double* zero=new double[matr.ret_h()];
			for(int i=0; i<matr.ret_h();i++) zero[i]=0;

			for(int j=1; j<matr.ret_w();j++)
			{
			   x_1=cut_col_j(matr,j);
			   if (Lexmax(zero,x_1,(matr.ret_h()-1)))
			   {
				   if (x_2==0) 
				   { x_2=x_1; q=j;}
				   else 
					 if (Lexmax(x_1,x_2,matr.ret_h()-1)) {x_2=x_1; q=j;}
			   }
			   //delete[] x_1;
			  
			}
			if (x_2!=x_1) delete[] x_2;
			delete[] zero;
			
			//cout<<"Main Line "<<(matr.ret_h()-1)<<endl;
			//cout<<"Main col "<<q<<endl;
			Preobrazovanie_Matrix(matr,(matr.ret_h()-1),q);
			//cout<<"After make L-norm"<<matr;	  
	}
	
}
*/
/*void Problem::Minus(double* x_1, double* x_2,int size)
//Вычитает из первого вектора второй и записывает в первый вектор
{
   for(int i=0; i<size; i++)
		x_1[i]= x_1[i]-x_2[i];
}*/
/*void Problem::Del_const(double* x, double c,int size)
//Делим вектор на число
{
	for(int i=0; i<size; i++)
		x[i]= x[i]/c;
}*/
/*double* Problem::cut_col_j(matrix<double> a, int j)
//Вырезаем из данной матрицы столбец j
{
	if (j>=a.ret_w()||j<0) return 0;
	else
	{
		double* x;
		int s=a.ret_h();
		x=new double[s];
		  for(int i=0; i<s; i++)
		  x[i]= a[i][j];
		return x;
	}
}*/

/*void Problem::put_col_j(matrix<double> &a, int j, double* x)
//Обновить в матрице а столбец с номером j
{
	if (j<a.ret_w()||j>=0) 
	{
		int s=a.ret_h();
		 for(int i=0; i<s; i++)
		  a[i][j]=x[i];
	}
}*/
/*bool Problem::Check_L_Norm(matrix<double> matr)
{
	double* x=new double[matr.ret_h()-1];
	for (int i=0; i<matr.ret_h()-1; i++) x[i]=0;

	double* y;
	for(int j=0; j<matr.ret_w(); j++)
	{
      y=cut_col_j(matr,j);
	  if (Lexmax(x,y,matr.ret_h()-1))
	  {
		  delete[] y;
		  return false;
	  }
	  delete[] y;
	  
	}
	delete[]x;
	return true;
}
*/
/*else//если ищем lexmax на множестве, а не по целевой функции
								   {
									//-----------------заполняем начальную таблицу-----------------------
										for(i=0; i<=size_n-num; i++)
								        {
											for (j=0; j<size_n-num+2; j++)
														  if (i==j)	matr[i][j]=-1; else matr[i][j]=0; 
														
													}
												
												for(i=size_n-num+1; i<size_n-num+1+size_m; i++)
													{
														for (j=0; j<size_n-num+2; j++)
														  if (j==0)	
														  {
															 int s=0;
															 for(int t=0; t<num-1;t++)
															   s=s+A[i-size_n+num-1][t]*Round(x_2[t+1],8);
															 
															 matr[i][j]=B[i-size_n+num-1]-s;
														  }
														  else
														   matr[i][j]= A[i-size_n+num-1][j+num-2]; 
												  
													}
												for (j=0; j<size_n-num+2; j++) 
												{
													if (j==0) matr[size_n-num+1+size_m][j]=int(x_2[num]);
													if (j==1) matr[size_n-num+1+size_m][j]=1;
													if ((j!=0)&&(j!=1)) matr[size_n-num+1+size_m][j]=0;
												}
												
												//ограничение по рекорду
             									for (j=0; j<size_n-num+2; j++) 
												{
													if (j==0) 
												 {   
													 int tmp=0;
													 for(int t=0; t<num-1;t++)
														tmp=tmp+C[t+1]*Round(x_2[t+1],8);
													 matr[size_n-num+1+size_m+1][j]=-(rec+d)+tmp;
												 }
													else 
													{
				   									matr[size_n-num+1+size_m+1][j]=-C[j-2+num];
													}
												}

												for (j=0; j<size_n-num+2; j++) matr[size_n-num+1+size_m+2][j]=0;
									//пустая строка для того чтобы сделать таблицу l-нормальной
									//----------------------------------------------------------------
								   }
								   */
/*else
			 {
                //-----------------заполняем начальную таблицу-----------------------
						for(i=0; i<=size_n-num; i++)
							{
								for (j=0; j<size_n-num+2; j++)
								  if (i==j)	matr[i][j]=-1; else matr[i][j]=0; 
								
							}
						
						for(i=size_n-num+1; i<size_n-num+1+size_m; i++)
							{
								for (j=0; j<size_n-num+2; j++)
								  if (j==0)	
								  {
									 int s=0;
									 for(int t=0; t<num-1;t++)
									   s=s+A[i-size_n+num-1][t]*Round(x_2[t+1],8);
									 
									 matr[i][j]=B[i-size_n+num-1]-s;
								  }
								  else
									matr[i][j]= A[i-size_n+num-1][j+num-2]; 
				  			}
						for (j=0; j<size_n-num+2; j++) 
						{
							if (j==0) matr[size_n-num+1+size_m][j]=(x_2[num]-1);
							if (j==1) matr[size_n-num+1+size_m][j]=1;
							if ((j!=0)&&(j!=1)) matr[size_n-num+1+size_m][j]=0;
						}
						
						//ограничение по рекорду
               			for (j=0; j<size_n-num+2; j++) 
						{
							if (j==0) 
						 {   
							 int tmp=0;
							 for(int t=0; t<num-1;t++)
								tmp=tmp+C[t+1]*Round(x_2[t+1],8);
							 matr[size_n-num+1+size_m+1][j]=-(rec+d)+tmp;
						 }
							else 
							{
				   			matr[size_n-num+1+size_m+1][j]=-C[j-2+num];
							}
						}

						for (j=0; j<size_n-num+2; j++) matr[size_n-num+1+size_m+2][j]=0;
				//пустая строка для того чтобы сделать таблицу l-нормальной
			 }*/
