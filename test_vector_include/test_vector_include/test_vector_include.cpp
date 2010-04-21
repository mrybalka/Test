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


// ����� ����, �� �������� �������� ������� �����. �������� ������ ����� � ������.
// ������� ���� ���� �� ������ � ���� �� �������� ��� ����� ������� ����� 
// �� ��������������� ����, ��� ���������� ����������� ������ �������� c_f, 
// �������� �������(������� f)��������� � ��������� �������� ����� � ������ ������ 2*n. 

int* FindPath(int NUM_VERTICES, matrix<int> c_f, matrix<int> c, matrix<int> &f, int source, int target) // source - �����, target - ����
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

// �������� ������� ������ ������������� ������
int* MaxFlow(matrix<bool> org_graph, int NUM_VERTICES, matrix<int> c, int source, int target) 
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
	                if ((org_graph[i][j]==1 && f[i][j]<c[i][j])||(org_graph[j][i]==1 && f[j][i]!=0))
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

int* find_local_connectivity(matrix<bool> org_graph, matrix<int> c, int n_, int s2, int t1)
//���������: n_ ���� ������ � �������� �����,
// s2, t1 ������� ����� �������� ������ ��������� ��������� � ���� ������������� org_graph
//������� ���������� ������ ����� n_, array[i]=1 if this vertex need to delete
{
	int* local_connectivity = new int[n_];
    for (int i=0; i<n_; i++)
       local_connectivity[i] = 0;

    int* W; //W �������� ������ ������ ���������� �� ����� �� ��������� ��������
	W = MaxFlow(org_graph, 2*n_, c, s2, t1);
	int* W_ = new int[2*n_+1]; //����������� ��������� ������ �������
	//������ ����������� ��������� ������
	W_[0] = W[0];
	bool flag;
	int WC=1;
	for (int i=1; i<2*n_+1; i++) W_[i]=-1;
	for (int i=0; i<2*n_; i++){
		flag = false;
		for (int j=1; j<2*n_+1; j++)
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
	for(int i=1; i<2*n_+1; i++){
		for(int j=1; j<2*n_+1; j++)
		   if (W[i]!=-1 && W_[j]!=-1 && org_graph[W[i]][W_[j]]==1 && W[i]+1==W_[j])
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
int len(int* _array, int n)
//���������� ���������� ������ � �������, �������� �����
{
	int lenght = 0;
	for (int i=0; i<n; i++)
		if (_array[i]==1)
			lenght ++;
	return lenght;
}

int* find_vertex_connectivity(int n)
//������� ���������� ������ ������� n, i ������� ������� ����� 1, ���� ������� i �����
//������� �� �����, ����� �� �������� �� ���������� ���������
{
  matrix<int> c;
  matrix<bool> org_graph;
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
  org_graph = matrix<bool>(2*n, 2*n);
  
  for (int i=0; i<2*n; ++i)
	  for (int j=0; j<2*n; ++j){ 
		c[i][j]=0;
        org_graph[i][j]=0;
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
		    
			org_graph[2*i_old][2*i_old+1]=1;
            org_graph[2*j_old][2*j_old+1]=1;
            org_graph[2*i_old+1][2*j_old]=1;
			org_graph[2*j_old+1][2*i_old]=1;
		    
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
		local_connectivity  = find_local_connectivity(org_graph, c, n, 2*s+1, 2*t);
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
int find_connected_components (matrix<bool> g, int n)
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

matrix<bool> delete_vertex_from_graph(matrix<bool> graph, int n, int* vertex_connectivity)
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

void new_algorithm(matrix<bool> g, int n, int count_vertex_in_block)
{
	//�������� ���������� ��������� �������� ������ ��� ����� count_vertex_in_block
	matrix<bool> components = matrix<bool>(n, n);
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			components[i][j] = 0;
	bool* common_cols = new bool[n];
    memset(common_cols, false , sizeof(bool)*n); 

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
					if ((g[cur][j]==1)&&(!used[j]))
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
					if ((g[j][k]==true)&&(components[component_number][k]==false)){
						used[k]=true;
						common_cols[k]=true;
					}
			}
		component_number++;
		}//if
 
        
	  }//for

//print 
cout<<"Common cols: [";
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
}

}
int _tmain(int argc, _TCHAR* argv[])
{
	int n = 20;
	double p;
	p = 0.3;
	int count_component =0;
	//�������� ��������� �����!
	for(int k=0; k<10; k++){
	do{
	Graph = generate_graph(n, p);
    //cout<<Graph<<endl;
	count_component = find_connected_components(Graph, n);
	} while (count_component > 1);

	/*int* vertex_connectivity = find_vertex_connectivity(n);
	cout<<endl;
	for (int i=0; i< n; i++)
		cout<<vertex_connectivity[i]<<" ";
	cout<<endl;
	
    matrix<bool> new_graph = delete_vertex_from_graph(Graph, n, vertex_connectivity);
	cout<<new_graph;
	int n_new = n - len(vertex_connectivity, n );
    count_component = find_connected_components(new_graph, n_new);*/
	
	new_algorithm(Graph, n , 5);
	}
	cin>> p;
	return 0;
}

