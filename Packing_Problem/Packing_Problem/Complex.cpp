// Packing_Problem.cpp : Defines the entry point for the console application.
//
#pragma warning disable

#include "stdafx.h"
//#include "Evristika.cpp"
//#include "L_Class.h"

char* int_to_str(int value)
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
double My_Round(double v, int decimals)
{
	int sgn =v/fabs(v);
	double eps = sgn*pow(10.0,(-decimals));
	double rmr = fmod( v, eps );
	v -= rmr;
	if( sgn*rmr - sgn*(eps / 2)>=DBL_EPSILON )
		v += eps;
	return v;
}//double Round(double v, int decimals)

void Generate_Exper()
//k-размер блока, kol-количество блоков
{
	int len_k=1;
	int len_kol=4;
	int len_p=1;
	int* k=new int[len_k];
	int* kol=new int[len_kol];
	double* p=new double[len_p];
    int i,j,l,q;
	Packing_Problem* P;
	Independent_Set_Problem* I;
	string filename1;
	string filename_vsp1;
	char* filename,*filename_vsp;
	char sl=CHAR(92);
   	
	k[0]=3; //k[1]=4; k[2]=5; k[3]=6; k[4]=7;
	kol[0]=40;kol[1]=19;kol[2]=20;kol[3]=22;
	p[0]=0.1; //p[1]=0.12; p[2]=0.15; p[3]=0.18; p[4]=0.2; p[5]=0.3; 

    q=20;
	for (i=0; i<len_k; i++)
		for(j=0; j<len_kol;j++)
		{
           for (int h=0; h<1; h++)
			{
			  // double prob;
			   //if (h%2==0) prob=sqrt(log((double)n[i])/m[j])/3;
			   //else prob=sqrt(log((double)n[i])/m[j])/2;
			   //prob=sqrt(log((double)n[i])/(m[j]))/3;
			   for(l=0;l<len_p;l++)
			  {
            	//double prob=0.02+(((double) rand()) /(double) RAND_MAX)*(0.04-0.02);
			    //int lines=10+(((double) rand()) /(double) RAND_MAX)*5;
			    //P=new Packing_Problem(n[i],lines*n[i],prob);
               //int n= k[i]+(kol[j]-1)*(k[i]-1);
			   P=new Packing_Problem(k[i],kol[j],p[l],1);
			   //I=new Independent_Set_Problem(n[i],p[k]);
			   filename1="";
			   filename_vsp1="";
			   filename1=filename1+"P:"+sl+"Test"+sl+"9"+sl+"K";
			   filename_vsp1=filename_vsp1+filename1+int_to_str(q)+".txt";
			   filename1=filename1+int_to_str(q)+"_V"+".txt";
			   //filename1=filename1+int_to_str(q)+"_V"+int_to_str(n[i])/*+"_M"+"_P"+int_to_str((p[k]*100))*/+".txt";
			   
			   filename=new char[100];
			   filename_vsp=new char[50];
			   int h=0;
			   while (filename1[h])
			   {
				  filename[h]=filename1[h];
				  h++;
			   }
			   filename[h]='\0';
			   
			   h=0;
			   while (filename_vsp1[h])
			   {
				  filename_vsp[h]=filename_vsp1[h];
				  h++;
			   }
			   filename_vsp[h]='\0';
			   
			   //I->Save_MIS_In_File(filename);
			   //I->Save_MIS_In_File(filename_vsp);

			   //P->Save_MSP_In_File(filename);
			   P->Save_MSP_In_File(filename_vsp);
			   delete P;
			   //delete I;
			   q++;
			   delete[] filename;
			   delete[] filename_vsp;
			}
		   }
		}
 
	delete[]k;
	delete[]kol;
	delete[]p;

}
void Generate()
{
	int len_n=1;
	int len_m=1;
	int len_p=4;
	int* n=new int[len_n];
	int* m=new int[len_m];
	double* p=new double[len_p];
	int i,j,k,q;
	Packing_Problem* P;
	Independent_Set_Problem* I;
	string filename1;
	string filename_vsp1;
	char* filename,*filename_vsp;
	char sl=CHAR(92);
	//n[0]=20; n[1]=30; n[2]=40; n[3]=50;	n[4]=60; n[5]=70; n[6]=80; //n[7]=90; n[8]=100; n[9]=150;	
	n[0]=100; //n[1]=100; n[2]=150; n[3]=200; n[4]=250; n[5]=300;  
	//n[0]=40; n[1]=50; n[2]=80; 
	//n[10]=300; n[11]=400; n[12]=500;n[13]=600; n[14]=700; n[15]=800; n[16]=900; n[17]=1000;
	//n[0]=100; n[1]=120;	n[2]=150; n[3]=180; n[4]=200; 
	//n[0]=80; n[1]=90; n[2]=100; n[3]=150; 
	//m[0]=3; m[1]=5; m[2]=10; m[3]=15; m[4]=20;
	//m[0]=10; m[1]=15; 
	m[0]=100; //m[1]=100; m[2]=200; m[3]=300;
	p[0]=0.02; p[1]=0.2; p[2]=0.22; p[3]=0.24; //p[4]=0.18;// p[5]=0.6; p[6]=0.62;
	//p[7]=0.64; p[8]=0.66; p[9]=0.68; p[10]=0.7; p[11]=0.72; 
    q=50;
	for (i=0; i<len_n; i++)
		for(j=0; j<len_m;j++)
		{
		
			/*p[0]=prob;
			p[1]=prob+0.001;
			p[2]=prob+(1-prob)/2;;
			p[3]=prob-0.0001;*/
			for (int h=0; h<10; h++)
			{
			   //double prob;
			   //if (h%2==0) prob=sqrt(log((double)n[i])/m[j])/6;
			   //else prob=sqrt(log((double)n[i])/m[j]);
			   //prob=sqrt(log((double)n[i])/(m[j]));
			   for(k=0;k<len_p;k++)
			  {
            	//double prob=0.02+(((double) rand()) /(double) RAND_MAX)*(0.04-0.02);
			    //int lines=10+(((double) rand()) /(double) RAND_MAX)*5;
			    //P=new Packing_Problem(n[i],lines*n[i],prob);
			   P=new Packing_Problem(n[i],m[j],p[k],false);
			   //I=new Independent_Set_Problem(n[i],p[k]);
			   filename1="";
			   filename_vsp1="";
			   filename1=filename1+"P:"+sl+"L"+sl+"MSP";
			   filename_vsp1=filename_vsp1+filename1+int_to_str(q)+".txt";
			   //filename1=filename1+int_to_str(q)+"_V"+int_to_str(n[i])+"_P"+int_to_str((p[k]*100))+".txt";
			   filename1=filename1+int_to_str(q)+"_V"+int_to_str(n[i])/*+"_M"+"_P"+int_to_str((p[k]*100))*/+".txt";
			   
			   filename=new char[100];
			   filename_vsp=new char[50];
			   int h=0;
			   while (filename1[h])
			   {
				  filename[h]=filename1[h];
				  h++;
			   }
			   filename[h]='\0';
			   
			   h=0;
			   while (filename_vsp1[h])
			   {
				  filename_vsp[h]=filename_vsp1[h];
				  h++;
			   }
			   filename_vsp[h]='\0';
			   
			   //I->Save_MIS_In_File(filename);
			   //I->Save_MIS_In_File(filename_vsp);

			   //P->Save_MSP_In_File(filename);
			   P->Save_MSP_In_File(filename_vsp);
			   delete P;
			   //delete I;
			   q++;
			   delete[] filename;
			   delete[] filename_vsp;
			}
		   }
		}
 
	delete[]n;
	delete[]m;
	delete[]p;
}
void Generate_Block()
{
	int len_n=1;
	int len_m=1;
	int len_p=1;
	int len_r=2;
	int len_k=1;
	int i,j,h,f,g,q;
	//Packing_Problem* P;
	string filename1;
	string filename_vsp1;
	char* filename,*filename_vsp;
	double sec;
	clock_t start,finish;
	int num_iter;
	char sl=CHAR(92);
	int kol_task=5;
	int* n=new int[len_n];
	double* m=new double[len_m];
	double* p=new double[len_p];
	double* r=new double[len_r];
	double* k=new double[len_k];
	n[0]=1000; //n[1]=300; n[2]=400;
	//n[4]=60; n[5]=70; //n[6]=80; n[7]=90; n[8]=100; n[9]=200;
	//n[10]=300; n[11]=400; n[12]=500;n[13]=600; n[14]=700; n[15]=800; n[16]=900; n[17]=1000;
	//n[0]=100; n[1]=120;	n[2]=150; n[3]=180; n[4]=200; 
	//m[05; m[1]=10; m[2]=15;
    m[0]=2000; //m[1]=250; m[2]=500; m[3]=1000;//m[2]=1; m[3]=2; m[4]=3; m[5]=5; m[6]=10; 
	p[0]=sqrt(log((double)n[0])/m[0])/3;
	//p[1]=sqrt(log((double)n[1])/m[1])/2; //p[2]=0.2; p[3]=0.25; p[4]=0.3; 
	r[0]=50; r[1]=100; //r[2]=0.3; r[3]=0.4; //r[4]=0.5;//процент от числа переменных
	k[0]=0.025;//k[1]=0.1; //k[1]=0.15; k[2]=0.2; //k[3]=0.25;//процент от числа (n-r)

    q=0;
	for(int w=0; w<kol_task; w++)
	  for (i=0; i<len_n; i++)
		for(j=0; j<len_m;j++)
			for(h=0;h<len_p;h++)
				for(f=0;f<len_r;f++)
					for(g=0;g<len_k;g++)
			   {
               	ofstream OutFile;
				Packing_Problem* P;
				int l=(int)((double)r[f]*(double)n[i]);
				int s=(int)((double)k[g]*(double)(n[i]-r[f]));
				P=new Packing_Problem(n[i],m[j],p[h],r[f],s);//равномерные блоки
			    
			   filename1="";
			   filename_vsp1="";
			   filename1=filename1+"S:"+sl+"Test_Block3"+sl+"S41"+sl+"B";
			   filename_vsp1=filename_vsp1+filename1+int_to_str(q)+".txt";
			   filename1=filename1+int_to_str(q)+"_V"+int_to_str(n[i])+"_P"+int_to_str((p[h]*100))+".txt";
			   //filename1=filename1+int_to_str(q)+"_V"+int_to_str(n[i])+"_P"+int_to_str((prob*100))+".txt";
			   
			   filename=new char[100];
			   filename_vsp=new char[50];
			   int h=0;
			   while (filename1[h])
			   {
				  filename[h]=filename1[h];
				  h++;
			   }
			   filename[h]='\0';
			   
			   h=0;
			   while (filename_vsp1[h])
			   {
				  filename_vsp[h]=filename_vsp1[h];
				  h++;
			   }
			   filename_vsp[h]='\0';
			   
			   //P->Save_MSP_BLOCK_In_File(filename);
			   P->Save_MSP_BLOCK_In_File(filename_vsp);
			   delete P;
			   q++;
			   delete[] filename;
			   delete[] filename_vsp;
			  }
		
	delete[]n;
	delete[]m;
	delete[]p;
	delete[]r;
	delete[]k;
}
int _tmain(int argc, _TCHAR* argv[])
{
	/*Independent_Set_Problem A("D:\MyFile256.txt");
	A.Greedy_Algorithm();
	A.Print_Answer();
	Independent_Set_Problem B("D:\MyFile256.txt");
	int* x=B.Probability_Algorithm(10000);
	cout<<"The best="<<x[0];*/
    //Packing_Problem P("D:\MyFile64.txt",0);
	
	
    SYSTEMTIME systime;
	SYSTEMTIME systime1;
	int size_n,size_m;
	char t;
	double p;
	int* y;
	int k;
	Packing_Problem* P;
	Independent_Set_Problem* I;
	int h,m,s;
	int r,block_size;
	double sec;
	clock_t start,finish;
    
	while (true)
	{
		cout<<endl;
		cout<<"1. Generate packing problem "<<endl;
		cout<<"2. Standart L-Class "<<endl;
		cout<<"3. TEST"<<endl;
		cout<<"4. Free"<<endl;
		cout<<"5. Test Independent Set "<<endl;
		cout<<"6. shuffle "<<endl;
		cout<<"7. Kuzurin "<<endl;
		cout<<"8. TEST BLOCK "<<endl;
		cout<<"9. Exit"<<endl;
		cout<<"t. Test standart Lclass and block Lclass"<<endl;
        cin>>t;
		switch (t)
		{
		case '1':
			{
             cout<<"Number of subsets = ";
			 //cin>>size_n;
			 cout<<"Number of elements = ";
			 //cin>>size_m;
		 	 cout<<"Probability = ";
			 //cin>>p;

			//Packing_Problem P(40,40,0.2);
			//P=new Packing_Problem(size_n,size_m,p,1);
			 //P=new Packing_Problem(size_n,size_m,p);
			//P->Save_MSP_In_File("d:\MyFile.txt");
			//P->Shuffle_Dec();
			//P->Undo_Shuffle();
			//I=new Independent_Set_Problem(size_n,/*size_m,*/p);
			//I->Save_MIS_In_File("MyFile.txt");
			//Independent_Set_Problem* M;
			//M=new Independent_Set_Problem("MyFile.txt");
			Generate();
			// Generate_Block();
			//Generate_Exper();
			//P=new Packing_Problem("D:\MyFile64.txt",0);
			/*char* str_name=new char[50];
			char sl=CHAR(92);
			string str="";
			str=str+"P:"+sl+"Test"+sl+"9"+sl+"K10";
			str=str+".txt";
			int j;
			for (j=0; j<18; j++)
			str_name[j]=str[j];
			str_name[j]='\0';
			P=new Packing_Problem(str_name,1,0);
			int* y=0;
			int k,kol_sol,kol_af_upd;
			double* x_lp;
			y=P->Go_Over_L_Class_Kuz(1,k,kol_sol,kol_af_upd,x_lp,0,1,0);
			for (int i=0; i<50;i++) cout<<y[i]<<" ";
		    cout<<endl;
			/*P->Save_MSP_In_File("d:\MyFile.txt");
			Packing_Problem* N;
			N=new Packing_Problem("d:\MyFile.txt",1);
			cout<<*N->GetMatrix();*/
			t='9';
			break;
			}
		case 't':
			{
			 ofstream OutFile;
			 //генерируем произвольную задачу упаковки
			 cout<<"Number of subsets = ";
			 cin>>size_n;
			 cout<<"Number of elements = ";
			 cin>>size_m;
		 	 cout<<"Probability = ";
			 cin>>p;
		     for(int i=0; i<15; i++)
			 {
				P=new Packing_Problem(size_n,size_m,p);
			 //решаем стандартным алгоритмом
             OutFile.open("D:\logtest.txt",ios_base::app);
			 start=clock();
		     y=P->Go_Over_L_Class(1,k,1,1,1);
		     finish=clock();
	    	 sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
			 if (y!=0)
				OutFile<<P->GetSize_n()<<'\t'<<P->GetSize_m()<<'\t'<<1<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t'<<endl;
			 else OutFile<<P->GetSize_n()<<'\t'<<P->GetSize_m()<<'\t'<<1<<'\t'<<"Time Out"<<'\t'<<k<<'\t'<<sec<<'\t'<<endl;
			 //OutFile<<str_name<<'\t'<<N.GetSize_n()<<'\t'<<N.GetSize_m()<<'\t'<<1<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
			 //cout<<"standart vertor =";
			 //for(int i=0; i<size_n+1; i++)
			 //	 cout<<y[i]<<" ";
			 //cout<<endl;
			 delete[] y;
			 OutFile.close();
			 cout<<"Standart complete"<<endl;
			 //cout<<*(P->GetMatrix());
			 //--------------
			 // получить блочную задачу
			 P->ConvertMatrix_to_BlockMatrix();
			 //cout<<*(P->GetMatrix());
			  //--------------
			 OutFile.open("D:\logtest.txt",ios_base::app);
			 start=clock();
		     y=P->Go_Over_L_Class_Block(1,k,1,1,1,5,5);
			 finish=clock();
	    	 sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
			 OutFile<<P->GetSize_n()<<'\t'<<P->GetSize_m()<<'\t'<<2<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t'<<endl;
			 /*cout<<"block vertor =";
			 cout<<y[0]<<" ";
			 for(int i=0; i<size_n; i++)
				 cout<<y[P->shuffle[i]+1]<<" ";
			 cout<<endl;*/
			 delete[] y;
			 OutFile.close();
			 cout<<"Block complete"<<endl;
			 }
			break;
			}
		case '8':
			{
            /*bool Rd;
			cout<<"Number of elements = ";
			cin>>size_n;
			cout<<"Number of subsets = ";
			cin>>size_m;
			cout<<"Probability = ";
			cin>>p;
			cout<<"r = ";
			cin>>r;
			cout<<"Block_size= ";
			cin>>block_size;
			cout<<"RANDOM BLOCK SIZE = ";
			cin>>Rd;
            //условие корректности работы
			//размер блока меньеш чем n-r
			// r<n
			P=new Packing_Problem(size_n,size_m,p,r,block_size,Rd);
			cout<<*(P->GetMatrix());
			P->Save_MSP_BLOCK_In_File("d:\MyFile1.txt");
			P->Read_MSP_BLOCK_From_File("d:\MyFile1.txt");
			cout<<*(P->GetMatrix());*/
			Generate_Block();
		
			break;
			}
		case '6':
			   {
				int sh=0;
				int j;
				ofstream OutFile;
				int kol_files=3;
				string s;
				char* str_name=new char[50];
				char sl=CHAR(92);
				string str="";
				char* vsp;
				string filename1;
				char* filename;
								
				for (int i=0; i<kol_files; i++)
				{
					str="";
					vsp=int_to_str(i);
					str=str+"D:"+sl+"Test4"+sl+"T";
					//str=str+"S:"+sl+"Test7"+sl+"MSP";
					str=str+vsp+".txt";
				    int len;
					if (i<10) len=1;
                    if ((i>=10)&&(i<100)) len=2;
	                if ((i>=100)&&(i<1000)) len=3;
	                if ((i>=1000)&&(i<10000)) len=4;
					
					for (j=0; j<14+len; j++)
						str_name[j]=str[j];
					str_name[j]='\0';
					
					filename1="";
			        filename1=filename1+"d:"+sl+"Test4"+sl+"G";
			   	    filename1=filename1+int_to_str(i)+".gms";
			   	   
					   filename=new char[100];
			   		   int h=0;
					   while (filename1[h])
					   {
					   filename[h]=filename1[h];
					   h++;
					   }
					   filename[h]='\0';
					
					Independent_Set_Problem* I;
					I=new Independent_Set_Problem(str_name);
				   	I->Make_Gams_File(filename);
				    delete I;
				}
				break;
			   }
	    case '7':
			   {
				int sh=0;
				int j;
				ofstream OutFile;
				int kol_files=90;
				string s;
				char* str_name=new char[50];
				char sl=CHAR(92);
				string str="";
				char* vsp;
				int* y=0;
				
				//OutFile.open("d:\logtest.txt",ios_base::app);
				
				for (int i=80; i<kol_files; i++)
				{
					str="";
					vsp=int_to_str(i);
					str=str+"P:"+sl+"L"+sl+"MSP";
					//str=str+"P:"+sl+"Test"+sl+"9"+sl+"K";					
					//str=str+"S:"+sl+"TestK"+sl+"MSP";
					str=str+vsp+".txt";
				    int len;
					if (i<10) len=1;
                    if ((i>=10)&&(i<100)) len=2;
	                if ((i>=100)&&(i<1000)) len=3;
	                if ((i>=1000)&&(i<10000)) len=4;
					
					for (j=0; j<12+len; j++)
						str_name[j]=str[j];
					str_name[j]='\0';
					
									
					Packing_Problem* P;
					P=new Packing_Problem(str_name,1,0);
					//P->Make_Gams_File("d:\MyGams1.gms");
					cout<<P->GetSize_n()<<" ";
					cout<<P->GetSize_m()<<endl;
					//cout<<*(P->GetMatrix());
					
					/*OutFile.open("D:\logtest.txt",ios_base::app);
					start=clock();
				    y=P->Go_Over_L_Class(1,k,0,0,0);
				     		finish=clock();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
					if (y!=0)
						OutFile<<str_name<<'\t'<<P->GetSize_n()<<'\t'<<P->GetSize_m()<<'\t'<<1<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
					else OutFile<<str_name<<'\t'<<P->GetSize_n()<<'\t'<<P->GetSize_m()<<'\t'<<1<<'\t'<<"Time Out"<<'\t'<<k<<'\t'<<sec<<'\t';
					//OutFile<<str_name<<'\t'<<N.GetSize_n()<<'\t'<<N.GetSize_m()<<'\t'<<1<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
					delete[] y;
					OutFile.close();
					cout<<"1 complete"<<endl;
										
					OutFile.open("D:\logtest.txt",ios_base::app);
					start=clock();
				    y=P->Go_Over_L_Class(1,k,1,0,0);
                    //y=N.Go_Over_L_Class(1,k,1,0,0); 
               		finish=clock();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
					OutFile<<2<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
					delete[] y;
					OutFile.close();
					cout<<"2 complete"<<endl;*/

					OutFile.open("logtest.txt",ios_base::app);
					start=clock();
					int kol_sol,kol_af_upd;
					double* x_lp;
				    y=P->Go_Over_L_Class_Kuz(1,k,kol_sol,kol_af_upd,x_lp,0,1,0);
					//y=P->Go_Over_L_Class(1,k,0,1,0);
					//y=N.Go_Over_L_Class(1,k,0,1,0);
					finish=clock();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
					OutFile<<str_name<<'\t'<<P->GetSize_n()<<'\t'<<P->GetSize_m()<<'\t'<<y[0]<<'\t'<<x_lp[0]<<'\t';
					OutFile<<k<<'\t'<<kol_sol<<'\t'<<kol_af_upd<<'\t'<<sec<<'\t';
					int rec=y[0];
					delete[] y;
					y=P->Go_Over_L_Class_Kuz(1,k,kol_sol,kol_af_upd,x_lp,1,1,0,rec);
                    OutFile<<kol_sol<<endl;
					//OutFile<<str_name<<'\t'<<P->GetSize_n()<<'\t'<<P->GetSize_m()<<'\t'<<y[0]<<'\t'<<x_lp[0]<<'\t';
					//OutFile<<k<<'\t'<<kol_sol<<'\t'<<kol_af_upd<<'\t'<<sec<<'\t'<<endl;
					
					//OutFile<<str_name<<'\t'<<P->GetSize_n()<<'\t'<<P->GetSize_m()<<'\t'<<y[0];
					//OutFile<<'\t'<<k<<'\t'<<sec<<'\t'<<endl;
					
					delete[] y;
					delete P;
					OutFile.close();
					cout<<"3 complete"<<endl;

					/*OutFile.open("D:\logtest.txt",ios_base::app);
					start=clock();
				    y=P->Go_Over_L_Class(1,k,0,0,1);
					//y=N.Go_Over_L_Class(1,k,0,1,0);
               		finish=clock();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
					OutFile<<4<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
					delete[] y;
					OutFile.close();
					cout<<"4 complete"<<endl;
					
					OutFile.open("D:\logtest.txt",ios_base::app);
					start=clock();
				    y=P->Go_Over_L_Class(1,k,1,1,1);
					//y=N.Go_Over_L_Class(1,k,1,1,1);
               		finish=clock();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
     				if (y!=0)OutFile<<5<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
					else OutFile<<5<<'\t'<<"Time Out"<<'\t'<<k<<'\t'<<sec<<'\t';
					delete[] y;
					OutFile.close();
					cout<<"5 complete"<<endl;
					
					OutFile.open("D:\logtest.txt",ios_base::app);
					start=clock();
					P->Shuffle_Dec();
				    y=P->Go_Over_L_Class(1,k,1,1,1);
					//N.Shuffle_Dec();
					//y=N.Go_Over_L_Class(1,k,1,1,1);
               		finish=clock();
					P->Undo_Shuffle();
					//N.Undo_Shuffle();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
     				OutFile<<6<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
					delete[] y;
					OutFile.close();
					cout<<"6 complete"<<endl;

                    OutFile.open("D:\logtest.txt",ios_base::app);
					start=clock();
					P->Shuffle_Inc();
				    y=P->Go_Over_L_Class(1,k,1,1,1);
					//N.Shuffle_Inc();
					//y=N.Go_Over_L_Class(1,k,1,1,1);
               		finish=clock();
					//N.Undo_Shuffle();
					P->Undo_Shuffle();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
     				OutFile<<7<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
					delete[] y;
					OutFile.close();
					cout<<"7 complete"<<endl;

					OutFile.open("D:\logtest.txt",ios_base::app);
					start=clock();
					P->Shuffle_According_Greedy();
					y=P->Go_Over_L_Class(1,k,1,1,1);
					//N.Shuffle_According_Greedy();
					//y=N.Go_Over_L_Class(1,k,1,1,1);
               		finish=clock();
					P->Undo_Shuffle();
					//N.Undo_Shuffle();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
     				if (y!=0) OutFile<<8<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t'<<endl;
					else OutFile<<8<<'\t'<<"Time Out"<<'\t'<<k<<'\t'<<sec<<'\t'<<endl;
					delete[] y;
					OutFile.close();
					cout<<"8 complete"<<endl;*/
									
					cout<<"File "<<str_name<<" is complete"<<endl;
					
				}
				t='9';
			   
				break;
			   }
	    case '9':
			{
				/*bool start_rec,colzero,table_info;
				int kol_full_enum_R, kol_full_enum;
				cout<<"Use START RECORD = ";
				cin>>start_rec;
				cout<<"Use COL ZERO = ";
				cin>>colzero;
				cout<<"Use TABLE INFO = ";
				cin>>table_info;
				cout<<"KOL_FULL_ENUM_R = ";
				cin>>kol_full_enum_R;
				cout<<"KOL_FULL_ENUM = ";
				cin>>kol_full_enum;

				
				GetSystemTime(&systime);
				start=clock();
				y=P->Go_Over_L_Class_Block(1,k,start_rec,colzero,table_info,kol_full_enum,kol_full_enum_R);
				finish=clock();
				sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
				GetSystemTime(&systime1);
				if (y!=0)	
				{
					for (int i=0; i<P->GetSize_n()+1;i++) cout<<y[i]<<" ";
					cout<<"Number of Iteration ="<<k<<endl;
				}
				else cout<<"No solution"<<endl;
				m=(systime1.wMinute-systime.wMinute);
				s=(systime1.wSecond-systime.wSecond);
				if (s < 0) s=s+60;
			    h=(systime1.wMilliseconds-systime.wMilliseconds);
				if (h < 0) h = h+1000;
				cout<<"Time Execute = "<<m<<":"<<s<<":"<<h<<endl;
				cout<<"Time Execute = "<<sec<<" sec"<<endl;
				break;*/
					return 0;
			}
					
		case '2':
			{
				bool start_rec,colzero,table_info;
				cout<<"Use START RECORD = ";
				cin>>start_rec;
				cout<<"Use COL ZERO = ";
				cin>>colzero;
				cout<<"Use TABLE INFO = ";
				cin>>table_info;
				
				GetSystemTime(&systime);
				//y=P->Go_Over_L_Class_Standart(1,k);
				start=clock();
				y=P->Go_Over_L_Class(1,k,start_rec,colzero,table_info);
				finish=clock();
				sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
				if (y!=0)	
				{
					
					if (P->flag_shuffle==1)
					{
						int vsp;
						int* solution;
						solution=new int[size_n+1];
						solution[0]=y[0];
						for(int t=1; t< P->GetSize_n()+1; t++)
						{
							vsp=P->shuffle[t-1];
							solution[vsp+1]=y[t];
		     			}
						for (int i=0; i<P->GetSize_n()+1;i++) cout<<y[i]<<" ";
						cout<<endl;
                        
						for (int i=0; i<P->GetSize_n()+1;i++) cout<<P->shuffle[i]<<" ";
						cout<<endl;
						for (int i=0; i<P->GetSize_n()+1;i++) cout<<solution[i]<<" ";

					}
					else for (int i=0; i<P->GetSize_n()+1;i++) cout<<y[i]<<" ";
					cout<<"Number of Iteration ="<<k<<endl;
					
							
				}
				else cout<<"No solution"<<endl;
				 GetSystemTime(&systime1);
				
				m=(systime1.wMinute-systime.wMinute);
				s=(systime1.wSecond-systime.wSecond);
				if (s < 0) s=s+60;
			    h=(systime1.wMilliseconds-systime.wMilliseconds);
				if (h < 0) h = h+1000;
				cout<<"Time Execute = "<<m<<":"<<s<<":"<<h<<endl;
				cout<<"Time Execute = "<<sec<<" sec"<<endl;

			break;
			}
		case '3':
			{
		       	int sh=0;
				int j;
				ofstream OutFile;
				int kol_files=1;
				string s;
				char* str_name=new char[50];
				char sl=CHAR(92);
				string str="";
				char* vsp;
				int* y=0;
				
				//OutFile.open("d:\logtest.txt",ios_base::app);
				
				/*char* strM;
				strM = new char[1000];
				ifstream InFile;
				InFile.open("settings.txt",ios_base::app);
				InFile.getline(strM,1000);
				char* str1 =  new char[1000];
				int j=0;
				while (int(strM[j])<>32) 
				{ str1[p]=strM[j]; p++; j++; }
				str1[p]='\0';
				InFile.close;*/

				for (int i=0; i<kol_files; i++)
				{
					str="";
					vsp=int_to_str(i);
					//str=str+"U:"+sl+"AndK"+sl+"Test"+sl+"S5"+sl+"MSP";
					//str=str+"D:"+sl+"Vertex100"+sl+"Seria1"+sl+"S";	
					str=str+"S:"+sl+"Test"+sl+"S19"+sl+"MSP";
					str=str+vsp+".txt";
				    
					/*j=0;
					int str_len=0;
					while (str[j]!='\0') { str_len++; j++; }*/

					int len;
					if (i<10) len=1;
                    if ((i>=10)&&(i<100)) len=2;
	                if ((i>=100)&&(i<1000)) len=3;
	                if ((i>=1000)&&(i<10000)) len=4;
					
					for (j=0; j<19+len; j++)
						str_name[j]=str[j];
					str_name[j]='\0';
					
					Packing_Problem* P;
					P=new Packing_Problem(str_name,1,0);
					//P->Make_Gams_File("d:\MyGams.gms");
					cout<<P->GetSize_n()<<" ";
					cout<<P->GetSize_m()<<endl;
					//cout<<*(P->GetMatrix());
					
					/*OutFile.open("s:\logtest.txt",ios_base::app);
					start=clock();
					y=I->Greedy_Algorithm();
					finish=clock();
				   	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
     				///OutFile<<setiosflags( ios::fixed );
					////OutFile<<setprecision(8);

					OutFile<<"greedy"<<'\t'<<y[0]<<'\t'<<sec<<'\t';
					delete[] y;
					OutFile.close();
					cout<<"greedy complete"<<endl;

					OutFile.open("s:\logtest.txt",ios_base::app);
					start=clock();
					y=I->Probability_Algorithm(5000);
					finish=clock();
				   	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
     				OutFile<<"prob"<<'\t'<<y[0]<<'\t'<<sec<<endl;
					delete[] y;
					OutFile.close();
					cout<<"prob complete"<<endl;
					delete I;*/

					
					OutFile.open("logtest.txt",ios_base::app);
					start=clock();
				    y=P->Go_Over_L_Class(1,k,1,1,1);
				     		finish=clock();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
					if (y!=0)
						OutFile<<str_name<<'\t'<<P->GetSize_n()<<'\t'<<P->GetSize_m()<<'\t'<<1<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
					else OutFile<<str_name<<'\t'<<P->GetSize_n()<<'\t'<<P->GetSize_m()<<'\t'<<1<<'\t'<<"Time Out"<<'\t'<<k<<'\t'<<sec<<'\t';
					//OutFile<<str_name<<'\t'<<N.GetSize_n()<<'\t'<<N.GetSize_m()<<'\t'<<1<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
					delete[] y;
					OutFile.close();
					cout<<"5 complete"<<endl;
										
					/*OutFile.open("logtest.txt",ios_base::app);
					start=clock();
				    y=P->Go_Over_L_Class(1,k,1,0,0);
                    //y=N.Go_Over_L_Class(1,k,1,0,0); 
               		finish=clock();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
					OutFile<<2<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
					delete[] y;
					OutFile.close();
					cout<<"2 complete"<<endl;

					OutFile.open("logtest.txt",ios_base::app);
					start=clock();
				    y=P->Go_Over_L_Class(1,k,0,1,0);
					//y=N.Go_Over_L_Class(1,k,0,1,0);
					finish=clock();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
					OutFile<<3<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
					delete[] y;
					OutFile.close();
					cout<<"3 complete"<<endl;

					OutFile.open("logtest.txt",ios_base::app);
					start=clock();
				    y=P->Go_Over_L_Class(1,k,0,0,1);
					//y=N.Go_Over_L_Class(1,k,0,1,0);
               		finish=clock();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
					OutFile<<4<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
					delete[] y;
					OutFile.close();
					cout<<"4 complete"<<endl;*/
					
					/*OutFile.open("logtest.txt",ios_base::app);
					start=clock();
				    y=P->Go_Over_L_Class(1,k,1,1,1);
					//y=N.Go_Over_L_Class(1,k,1,1,1);
               		finish=clock();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
     				if (y!=0)OutFile<<5<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
					else OutFile<<5<<'\t'<<"Time Out"<<'\t'<<k<<'\t'<<sec<<'\t';
					delete[] y;
					OutFile.close();
					cout<<"5 complete"<<endl;*/
					
					/*OutFile.open("logtest.txt",ios_base::app);
					start=clock();
					P->Shuffle_Dec();
				    y=P->Go_Over_L_Class(1,k,1,1,1);
					//N.Shuffle_Dec();
					//y=N.Go_Over_L_Class(1,k,1,1,1);
               		finish=clock();
					P->Undo_Shuffle();
					//N.Undo_Shuffle();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
     				OutFile<<6<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
					delete[] y;
					OutFile.close();
					cout<<"6 complete"<<endl;*/

                    /*OutFile.open("logtest.txt",ios_base::app);
					start=clock();
					P->Shuffle_Inc();
				    y=P->Go_Over_L_Class(1,k,1,1,1);
					//N.Shuffle_Inc();
					//y=N.Go_Over_L_Class(1,k,1,1,1);
               		finish=clock();
					//N.Undo_Shuffle();
					P->Undo_Shuffle();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
     				OutFile<<7<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
					delete[] y;
					OutFile.close();
					cout<<"7 complete"<<endl;

					OutFile.open("logtest.txt",ios_base::app);
					start=clock();
					P->Shuffle_According_Greedy();
					y=P->Go_Over_L_Class(1,k,1,1,1);
					//N.Shuffle_According_Greedy();
					//y=N.Go_Over_L_Class(1,k,1,1,1);
               		finish=clock();
					P->Undo_Shuffle();
					//N.Undo_Shuffle();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
     				if (y!=0) OutFile<<8<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t'<<endl;
					else OutFile<<8<<'\t'<<"Time Out"<<'\t'<<k<<'\t'<<sec<<'\t'<<endl;
					delete[] y;
					OutFile.close();
					cout<<"8 complete"<<endl;*/
									
					cout<<"File "<<str_name<<" is complete"<<endl;
					delete P;
				}
				t='9';
			break;
			}
		case '4':
			{
				int sh=0;
				int j;
				ofstream OutFile;
				int kol_files=20;
				int Number=0;
				string s;
				char* str_name=new char[50];
				char sl=CHAR(92);
				string str="";
				char* vsp;
				int* y=0;
				int k,size;
				
				if (argc > 2)
				{
					k=0;
					while (argv[2][k]!='\0') k++;
					size=0;
					size=argv[2][k-1]-48;
					for (j=1;j<k;j++) 
					{   
					 int deg=1;
					 for (int h=1;h<=j;h++) {deg = deg*10;}
					 size=size+(argv[2][k-j-1]-48)*deg;
					}
					 Number=size;
				}
				
				if (argc > 3)
				{
				  k=0;
				  while (argv[3][k]!='\0') k++;
				  size=0;
		          size=argv[3][k-1]-48;
					for (j=1;j<k;j++) 
					{   
					 int deg=1;
					 for (int h=1;h<=j;h++) {deg = deg*10;}
					 size=size+(argv[3][k-j-1]-48)*deg;
					}
				   kol_files=size;
				}
				k=0;				
				for (int i=Number; i<kol_files; i++)
				{
					str="";
					vsp=int_to_str(i);
					//str=str+"U:"+sl+"AndK"+sl+"Test_Block"+sl+"Vertex300"+sl+"B";
					str=str+"S:"+sl+"Test_Block3"+sl+"S31"+sl+"B";
					str=str+vsp+".txt";
				    int len;
					if (i<10) len=1;
                    if ((i>=10)&&(i<100)) len=2;
	                if ((i>=100)&&(i<1000)) len=3;
	                if ((i>=1000)&&(i<10000)) len=4;
					
                    
					str_name[0]=(char)argv[1][0];
					str_name[1]=(char)argv[1][1];
					str_name[2]=(char)argv[1][2];
					
					for (j=3; j<24+len; j++)
						str_name[j]=str[j];
					str_name[j]='\0';
					
					for(j=0; j<24+len; j++) cout<<str_name[j];
					cout<<endl;

					Packing_Problem* P;
					P=new Packing_Problem(str_name,1,1);
					//P->Read_MSP_BLOCK_From_File(str_name);
					
					OutFile.open("logtest1.txt",ios_base::app);
					start=clock();
				    y=P->Go_Over_L_Class(1,k,1,1,1);
				    finish=clock();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
					OutFile<<str_name<<'\t'<<P->GetSize_n()<<'\t'<<P->GetSize_m()<<'\t'<<P->Matrix_Block_Param->r<<'\t'<<P->Matrix_Block_Param->block_kol<<'\t';
					OutFile<<2<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
					//OutFile<<str_name<<'\t'<<N.GetSize_n()<<'\t'<<N.GetSize_m()<<'\t'<<1<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
					delete[] y;
					OutFile.close();
					cout<<"2 complete"<<endl;
					
					/*OutFile.open("logtest1.txt",ios_base::app);
					start=clock();
				    y=P->Go_Over_L_Class(1,k,1,1,1);
                    finish=clock();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
					OutFile<<str_name<<'\t'<<P->GetSize_n()<<'\t'<<P->GetSize_m()<<'\t'<<P->Matrix_Block_Param->r<<'\t'<<P->Matrix_Block_Param->block_kol<<'\t';
					OutFile<<2<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t';
					delete[] y;
					OutFile.close();
					cout<<"2 complete"<<endl;*/

					/*if (i>36)
					{
					OutFile.open("logtest1.txt",ios_base::app);
					start=clock();
				    y=P->Go_Over_L_Class_Block(1,k,1,1,1,5,5);
					finish=clock();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
					OutFile<<str_name<<'\t'<<P->GetSize_n()<<'\t'<<P->GetSize_m()<<'\t'<<P->Matrix_Block_Param->r<<'\t'<<P->Matrix_Block_Param->block_kol<<'\t';
					OutFile<<3<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t'<<endl;
					delete[] y;
					OutFile.close();
					cout<<"3 complete"<<endl;
					}*/

					OutFile.open("logtest1.txt",ios_base::app);
					start=clock();
				    y=P->Go_Over_L_Class_Block(1,k,1,1,1,0,0);
				    finish=clock();
			    	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
					OutFile<<str_name<<'\t'<<P->GetSize_n()<<'\t'<<P->GetSize_m()<<'\t'<<P->Matrix_Block_Param->r<<'\t'<<P->Matrix_Block_Param->block_kol<<'\t';
					OutFile<<4<<'\t'<<y[0]<<'\t'<<k<<'\t'<<sec<<'\t'<<endl;
					delete[] y;
					OutFile.close();
					cout<<"4 complete"<<endl;
					
					cout<<"File "<<str_name<<" is complete"<<endl;
					delete P;
				}
				t='9';
				break;
				
			}
		case '5':
			{
				
		       	int sh=0;
				int j;
				ofstream OutFile;
				int kol_files=95;
				string s;
				char* str_name=new char[50];
				char sl=CHAR(92);
				string str="";
				char* vsp;
				int* y=0;
				
				/*int* lim=new int[10];
				lim[0]=1;
				lim[1]=2;
				lim[2]=4;
                lim[3]=8;
				lim[4]=12;
				lim[5]=24;
				lim[6]=48;
				lim[7]=80;
				lim[8]=100;
				lim[9]=256;
				for (int k=0; k<10;k++)
				{*/
				for (int i=0; i<kol_files; i++)
				{
					str="";
					vsp=int_to_str(i);
					str=str+"D:"+sl+"Test3"+sl+"T";
					///str=str+"S:"+sl+"TestK"+sl+"MSP";
					str=str+vsp+".txt";
				    int len;
					if (i<10) len=1;
                    if ((i>=10)&&(i<100)) len=2;
	                if ((i>=100)&&(i<1000)) len=3;
	                if ((i>=1000)&&(i<10000)) len=4;
					
					for (j=0; j<14+len; j++)
						str_name[j]=str[j];
					str_name[j]='\0';
					
									
					Independent_Set_Problem* I;
					I=new Independent_Set_Problem(str_name);
					
					//cout<<P->GetSize_n()<<" ";
					//cout<<P->GetSize_m()<<endl;
					//cout<<*(P->GetMatrix());
					
					/*OutFile.open("s:\logtest.txt",ios_base::app);
					start=clock();
					y=I->Greedy_Algorithm();
					finish=clock();
				   	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
     				///OutFile<<setiosflags( ios::fixed );
					////OutFile<<setprecision(8);
					OutFile<<"greedy"<<'\t'<<y[0]<<'\t'<<sec<<'\t';
					delete[] y;
					OutFile.close();
					cout<<"greedy complete"<<endl;*/

					OutFile.open("s:\logtest.txt",ios_base::app);
					start=clock();
					y=I->Probability_Algorithm(5000,2000);
			    	finish=clock();
				   	sec = ((double)(finish - start) / CLOCKS_PER_SEC); 
					OutFile<<I->GetSize_n()<<'\t'<<I->GetSize_m()<<'\t'<</*"prob"<<'\t'<<*/y[0]<<'\t'<<sec<<endl;
					delete[] y;
					OutFile.close();
					cout<<"prob complete"<<endl;
					delete I;
	     
					cout<<"File "<<str_name<<" is complete"<<endl;
				}
				//}
				//delete[] lim;
			    t='9';
				break;
			}
		default: 
			{
				cout<<"Your choice is wrong!"<<endl;
				break;
			}
		}
	}
	
   

	//A.Print_Answer();
	
	/*Packing_Problem P("D:\MyFilefrb30.txt",1);
	Packing_Problem P("D:\MyFile64.txt",0);
	
	SYSTEMTIME systime;
    GetSystemTime(&systime);
	*/
	/*Packing_Problem P;
    Independent_Set_Problem B;
	B=P.Get_Equivalent_MIS();
	B.Greedy_Algorithm();
	B.Print_Answer();*/
    /*SYSTEMTIME systime1;
    GetSystemTime(&systime1);
	int k=(systime1.wMinute-systime.wMinute);
	cout<<"Время выполнения минут= "<<k<<endl;*/


    /*Problem P;
	int* y;
	int k;
	y=P.Go_Over_L_Class_Standart(1,k);
	if (y!=0)	
	{
		cout<<"Number of Iteration ="<<k<<endl;
		for (int i=0; i<P.GetSize_n()+1;i++) cout<<y[i]<<" ";
				
	}
	else cout<<"No solution"<<endl;*/
	
	
	//Packing_Problem P;
	//Packing_Problem P("D:\MyFile64.txt",0);
	/*Packing_Problem P(20,10,0.1);
	
	int* y;
	int k;
	
	y=P.Go_Over_L_Class_Modified_First(1,k);
	if (y!=0)	
	{
		
		for (int i=0; i<P.GetSize_n()+1;i++) cout<<y[i]<<" ";
		cout<<"Number of Iteration ="<<k<<endl;
				
	}
	else cout<<"No solution"<<endl;
	
	/*y=P.Go_Over_L_Class_Modified_Second(1,k);
	
	if (y!=0)	
	{
		
		for (int i=0; i<P.GetSize_n()+1;i++) cout<<y[i]<<" ";
		cout<<"Number of Iteration ="<<k<<endl;
				
	}
	else cout<<"No solution"<<endl;*/
	
	/*for(int i=0;i<3;i++)
	x[i]=1;*/
	//cout<<P.Check_Int(x);*/

	/*Packing_Problem P;
    Independent_Set_Problem B;
	B=P.Get_Equivalent_MIS();
	B.Probability_Algorithm(20);*/
	/*
	int* proverka=new int[7];
	for(int i=0; i<7; i++) proverka[i]=0;
	
	int num;
	for(int i=0; i<1000; i++)
	{  
		num=B.Select_Vertex();
		proverka[num]++;
	}
	for(int i=0; i<7; i++) cout<<proverka[i]<<" ";*/
	

	return 0;
}

