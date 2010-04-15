// test_vector_include.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
matrix<bool> Graph;
int n;

matrix<bool> generate_graph(int n, double p)
{
   matrix<bool> Graph;
   double r;
   int i,j;
   n = n;
   Graph = matrix<bool>(n,n);
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

  return Graph;
}


// ���� ���� �� �������� �������� ������� ����� ���������� ������ ����� � ������
// ������� ���� ���� �� ������ � ���� �� �������� ��� ����� ������� �����,
// ������ ����������� ������ (i,j) ������ c[i][j] - f[i][j],
// �.�. ����� ������ ��������(���� �������� - ���� ���� ����) ��������� ����������� �����,
// �� �������� �������� ������
int FindPath(int NUM_VERTICES, matrix<int> c, matrix<int> &f, int source, int target) // source - �����, target - ����
{
   const int INFINITY = 10000; // �������� ����� ������������ �������������

   // Link ������������ ��� ���������� ���������� ����
   // Link[i] ������ ����� ���������� ������ �� ���� i -> �����
   int* Link;
   int* Queue; // �������
   int* Flow;
   int QP, QC; // QP - ��������� ������ ������� � QC - ����� ��-��� � �������
   
   // ����� ��������������� ���������� ������������ �������� FindPath - ������ � ������
   // Flow - �������� ������ ����� ������ ������� �� ������ ���� ������
   Flow=new int[NUM_VERTICES];
   Link=new int[NUM_VERTICES];
   Queue=new int[NUM_VERTICES];
    
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
                if ((c[CurVertex][i] - f[CurVertex][i])>0 && Flow[i] == 0) 
                {
                        // ���� �����, �� ��������� i � ����� �������
                        Queue[QC] = i; QC++;
                        Link[i] = CurVertex; // ���������, ��� � i ��������� �� CurVertex
                        // � ������� �������� ������ ������� ����� ������� i
                        if (c[CurVertex][i]-f[CurVertex][i] < Flow[CurVertex])
                             Flow[i] = c[CurVertex][i];
                        else
                             Flow[i] = Flow[CurVertex];
                }
            QP++;// ��������� � ��������� � ������� �������
        }
        // �������� ����� ����
        if (Link[target] == -1) return 0; // �� ��� �� ������� ���� � �������
        // ��� �������:
        // ����� Flow[target] ����� ����� ������ ������� "�����" �� ������� ���� �� ������ � ����
        // ����� �������� �������� ������� f ���  ������� ���� �� �������� Flow[target]
        CurVertex = target;
        while (CurVertex != source) // ���� �� ����� � ����� �� ��������������� � ������� ������� Link
        {
                f[Link[CurVertex]][CurVertex] +=Flow[target];
                CurVertex = Link[CurVertex];
        }
        return Flow[target]; // ���������� �������� ������ ������� �� ��� ������ "�������" �� �����
}

// �������� ������� ������ ������������� ������
int MaxFlow(int NUM_VERTICES, matrix<int> c, matrix<int> &f, int source, int target) // source - �����, target - ����
//c ���������� ��������� � �����������, f ���������� ���������
{
        // �������������� ����������:
	for(int i=0; i<NUM_VERTICES; i++){
		for (int j=0; j<NUM_VERTICES; j++){
			 f[i][j]=0; // �� ����� ������ �� �����
		}
	}
	    //memset(f, 0, sizeof(int)*MAX_VERTICES*MAX_VERTICES); 
        int MaxFlow = 0; // ��������� �������� ������
        int AddFlow;
        do
        {
                // ������ �������� ���� ����-���� ������� ���� �� ������ � ����
                // � ����� ��� ����� ����� ���� ����� �� ����� ����
                AddFlow = FindPath(NUM_VERTICES, c, f, source, target);
			    MaxFlow += AddFlow;
        } while (AddFlow >0);// ��������� ���� ���� ����� �������������
        return MaxFlow;
}

int* find_local_connectivity(matrix<int> c, int n_, int s2, int t1)
//retutn array len n, array[i]=1 if this vertex need to delete
{
	matrix<int> f;
	// f - ������ ���������� ������� �������� ������
    // f[i][j] - ����� ������� �� ������� i � j

	int* local_connectivity = new int[n_];
    
	for (int i=0; i<n_; i++)
       local_connectivity[i] = 0;

    f = matrix<int>(2*n_, 2*n_);    
    MaxFlow(2*n_, c, f, s2, t1);
		//� ������� f � � ����� ������� ����� ����� �������, ��������� ����� ��� ������� 
		// �� ����� �������� �������
	return local_connectivity;
}
int len(int* _array)
{
	int l = 0;
	for (int i=0; i<n; i++)
		if (_array[i]==1)
			l++;
	return l;
}

int* find_vertex_connectivity(int n)
{
  matrix<int> C;
  int* local_connectivity;
  const int infinity = 1000;
  
  int* global_connectivity;
  global_connectivity = new int[n];
  for (int i=0; i< n-1; i++)
	  global_connectivity[i] = 1;
  global_connectivity[n-1] = 0;
 
  // � - ������ ���������� ���������� �����,
  // �.�. c[i][j] - ������������ �������� ������ ��������� ���� �� ����� (i,j)
  
  //������ ���������������� ���� � ������������ ��������� , ��������� ������� �
  // C[i][j] = 0 ���� ������� �� ������
  // C[i][j] = 1 or infinyty  ���� ������� ������
  C = matrix<int>(2*n, 2*n);
  for (int i=0; i<n; ++i)
	for (int j=0; j<n; ++j) 
		C[i][j]=0;
  //������� ���������� ���������� �������� �����
  int i_old, j_old;
  for (int i=0; i<n; ++i)
	for (int j=0; j<n; ++j) 
	{
      if (((i%2 == 0)&&(j%2 ==0)) || ((i%2 != 0)&&(j%2 !=0))) C[i][j] = 0;
	  else
	   {
		   i_old = i/2;
		   j_old = j/2;
		   if (Graph[i_old][j_old] == 1)
		   {
			   if (i_old==j_old){
			       C[i][j]=1;
				   C[j][i]=1;}
			   else{
				   C[i][j]=infinity;
				   C[j][i]=infinity;}
			       
     	   }
	   }
	}
  cout<<C<<endl;
  for (int s=0; s<n; ++s)
	for (int t=0; t<n; ++t) 
	{
		if (Graph[s][t])  continue;
		//s1 = 2*s, s2 = 2*s + 1
		//... ������� �������� flow ������������� ������ �� s2 � t1 ...
		local_connectivity  = find_local_connectivity(C, n, 2*s+1, 2*t);
        if (len(local_connectivity) < len(global_connectivity))
		{
			delete [] global_connectivity;
			global_connectivity = local_connectivity;
		}
	}
   return global_connectivity;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int n = 5;
	double p;
	p = 0,4;
	Graph = generate_graph(n, p);
	cout<<Graph<<endl;
	int* vertex_connectivity = find_vertex_connectivity(n);
	for (int i=0; i< n; i++)
		cout<<vertex_connectivity[i]<<" ";
	cout<<endl;
	cin>> p;

	return 0;
}

/*
typedef vector<int> vint;
typedef vector<vint> vvint;
const int inf = 1000*1000*1000;

	int n = 2*n_;//����� �������� � ����������� ������
    vvint c (n, vint(n));
	for (int i=0; i<n; i++)
	{
		if (i==0)
		    for (int j=0; j<n; j++)
			{   if (j==0) c[i][j]=C[s2][s2];
	            if (j==s2) c[i][j]=C[s2][0];
				if (j==t1) c[i][j]=C[s2][n-1];
                if (j==n-1) c[i][j]=C[s2][t1]; 
				if ((j!=0)&&(j!=n-1)&&(j!=s2)&&(j!=t1)) c[i][j]=C[s2][j]; 
		     }
        if (i==n-1)
			for (int j=0; j<n; j++){
                if (j==0) c[i][j]=C[t1][s2];
	            if (j==s2) c[i][j]=C[t1][0];
				if (j==t1) c[i][j]=C[t1][n-1];
                if (j==n-1) c[i][j]=C[t1][t1]; 
				if ((j!=0)&&(j!=n-1)&&(j!=s2)&&(j!=t1)) c[i][j]=C[t1][j]; } 
		if (i==s2)
			for (int j=0; j<n; j++){
                if (j==0) c[i][j]=C[0][s2];
	            if (j==s2) c[i][j]=C[0][0];
				if (j==t1) c[i][j]=C[0][n-1];
                if (j==n-1) c[i][j]=C[0][t1]; 
				if ((j!=0)&&(j!=n-1)&&(j!=s2)&&(j!=t1)) c[i][j]=C[0][j]; }
        if (i==t1)
			for (int j=0; j<n; j++){
                if (j==0) c[i][j]=C[n-1][s2];
	            if (j==s2) c[i][j]=C[n-1][0];
				if (j==t1) c[i][j]=C[n-1][n-1];
                if (j==n-1) c[i][j]=C[n-1][t1]; 
				if ((j!=0)&&(j!=n-1)&&(j!=s2)&&(j!=t1)) c[i][j]=C[n-1][j]; }
		if ((i!=0)&&(i!=n-1)&&(i!=s2)&&(i!=t1))
            for (int j=0; j<n; j++)
                 c[i][j]=C[i][j]; 
	}

     //������ ������� � ������� s2 c 0, � � ������� t1 c n-1
	// ����� - ������� 0, ���� - ������� n-1

	vvint f (n, vint(n));
	for (;;)
	{
    	vint from (n, -1);
		vint q (n);
		int h=0, t=0;
		q[t++] = 0;
		from[0] = 0;
		for (int cur; h<t;)
		{
			cur = q[h++];
			for (int v=0; v<n; v++)
				if (from[v] == -1 &&
					c[cur][v]-f[cur][v] > 0)
				{
					q[t++] = v;
					from[v] = cur;
				}
		}

		if (from[n-1] == -1)
			break;
		int cf = inf;
		for (int cur=n-1; cur!=0; )
		{
			int prev = from[cur];
			cf = min (cf, c[prev][cur]-f[prev][cur]);
			cur = prev;
		}

		for (int cur=n-1; cur!=0; )
		{
			int prev = from[cur];
			f[prev][cur] += cf;
			f[cur][prev] -= cf;
			cur = prev;
		}

	}
	int flow = 0;
	for (int i=0; i<n; i++)
		if (c[0][i])
			flow += f[0][i];
			*/