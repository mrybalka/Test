#ifndef _MATRIX_H_
#define _MATRIX_H_
#pragma warning disable

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <typeinfo>
using namespace std;

#define MAX_POINT_SYM 7


/*************************************************************************\
|*************************************************************************|
	the parent class
|*************************************************************************|
\*************************************************************************/
template <class Type_table> class table
{
	//protected:
public:
		unsigned int width, height;
		
		Type_table ** matr;

		table ( unsigned int _width, unsigned int _hight );
		table ( const table <Type_table> &obj );
		~table ();
};
/*************************************************************************/




/*************************************************************************\
|*************************************************************************|
	the child class
|*************************************************************************|
\*************************************************************************/
template <class T> class matrix : public table <T>
{
	unsigned int ret_number_of_symbols ( T number );
	unsigned int ret_max_sym ( void );
	
	friend istream &operator >> ( istream &stream, matrix <T> &ob )
	{
		cout<<"Enter matrix: \n\n";
		for ( unsigned int i = 0; i < ob.ret_h(); i++ )
		{
			cout << "----------------------\n";
			for ( unsigned int j = 0; j < ob.ret_w(); j++ )
			{
				cout << "Enter [" << i+1 << "][" << j+1 << "]: ";
				stream >> ob.matr [i][j];
			}
		}
		return stream;
	}
	
	friend ostream &operator << ( ostream &stream, matrix <T> ob )
	{
		stream.precision ( MAX_POINT_SYM );
		stream.setf ( ios :: fixed );
		stream << "\n\n";
		for ( unsigned int i = 0; i < ob.height; i++ )
		{
			stream << " | ";
			for ( unsigned int j = 0; j < ob.width; j++ )
			{
				stream << ob.matr [i][j];
								for (
				     unsigned int a = 0;
				     a < ( ob.ret_max_sym ( ) - ob.ret_number_of_symbols ( ob.matr[i][j] ) );
				     a++
				    )
					stream << " ";
				stream << " ";
			}
			stream << "|\n";
		}
		cout << "\n\n";
		return stream;
	}

	public:
		matrix ( unsigned int _width, unsigned int _hight ) : table <T> ( _width, _hight ) {};
		matrix () : table <T> ( 5, 5 ) { };
		matrix ( const matrix<T> &obj ) : table <T> (obj)
		{
			table<T>::height = obj.height;
			table<T>::width = obj.width;
			try
			{
				table<T>::matr = new T * [obj.height];
				//table<T>::matr = new T * [obj.width];
			}
			catch ( bad_alloc xa)
			{
				cerr << "error memory allocation\n";
				exit ( 1 );
			}
			for ( unsigned int i = 0; i < obj.height; i++ )
			//for ( unsigned int i = 0; i < obj.width; i++ )
			{
				try
				{
					table<T>::matr[i] = new T [obj.width];
					//table<T>::matr[i] = new T [obj.height];
				}
				catch ( bad_alloc xa)
				{
					cerr << "error memory allocation\n";
					exit ( 1 );
				}
				for ( unsigned int j = 0; j < obj.width; j++ )
				//for ( unsigned int j = 0; j < obj.height; j++ )
				{
					table<T>::matr[i][j] = obj.matr[i][j];
				}
			}
		};
		~matrix () {};
		

		T * operator [] ( int i ) const;
		matrix &operator ~ ();
		matrix &operator + ( const matrix ob );
		matrix &operator - ( const matrix ob );
		matrix &operator * ( const matrix ob );
		matrix &operator * ( T num );
		void operator    = ( const matrix &ob );
		matrix &operator ! ();
		
		T det ( void );

		unsigned int ret_w ( void ) { return table<T>::width; }
		unsigned int ret_h ( void ) { return table<T>::height; }
};
/*************************************************************************/




/*************************************************************************\
|*************************************************************************|
	functions of the parent class
|*************************************************************************|
\*************************************************************************/

template <class Type_table> table <Type_table> :: table ( unsigned int _width, unsigned int _height )
{
	if ( _width < 0 )
	{
		_width = 5;
		cerr << "width is not correct, reset to 5\n";
	}
	
	if ( _height < 0 )
	{
		_height = 5;
		cerr << "height is not correct, reset to 5\n";
	}
	
	width = _width;
	height = _height;
    try
	{
		matr = new Type_table * [height];
		//matr = new Type_table * [width];
	}
	catch ( bad_alloc xa)
	{
		cerr << "error memory allocation\n";
		exit ( 1 );
	}
	for ( unsigned int i = 0; i < height; i++ )
	//for ( unsigned int i = 0; i <width ; i++ )
	{
		try
		{
			matr[i] = new Type_table [width];
			//matr[i] = new Type_table [height];
		}
		catch ( bad_alloc xa)
		{
			cerr << "error memory allocation\n";
			exit ( 1 );
		}
    }
	for ( unsigned int i = 0; i < height; i++ )
	  for ( unsigned int j = 0; j < width; j++ )
		 matr[i][j] = 0;
}



template <class Type_table> table <Type_table> :: table ( const table <Type_table> &obj )
{
	/*if (matr)
	{
	for ( unsigned int i = 0; i < height; i++ )
	{
		delete [] matr[i];
	}
	delete [] matr;
	}*/

	height = obj.height;
	width = obj.width;
	try
	{
		matr = new Type_table * [obj.height];
	}
	catch ( bad_alloc xa)
	{
		cerr << "error memory allocation\n";
		exit ( 1 );
	}
	for ( unsigned int i = 0; i < height; i++ )
	{
		try
		{
			matr[i] = new Type_table [obj.width];
		}
		catch ( bad_alloc xa)
		{
			cerr << "error memory allocation\n";
			exit ( 1 );
		}
		for ( unsigned int j = 0; j < width; j++ )
			matr[i][j] = obj.matr[i][j];
	}
}



template <class Type_table> table <Type_table> :: ~table ()
{
	for ( unsigned int i = 0; i < height; i++ )
	{
		delete [] matr[i];
	}
	delete [] matr;
	width = 0;
	height = 0;
}





/*************************************************************************\
|*************************************************************************|
	functions of the child class
|*************************************************************************|
\*************************************************************************/

template <class T> unsigned int matrix <T> :: ret_number_of_symbols ( T number )
{
	int num = 0, length = 0;

	num = ( int ) ( ( number < 0 ) ? -number : number );

	do
	{
		length++;
		num /= 10;
	} while ( num >= 1 );

	if ( number < 0 )
		length++;

	length += MAX_POINT_SYM + 1;

	return length;
}



template <class T> unsigned int matrix <T> :: ret_max_sym ( void )
{
	unsigned int max = 0;
	
	for ( unsigned int i = 0; i < table<T>::height; i++ )
	{
		for ( unsigned int j = 0; j < table<T>::width; j++ )
		{
			max = ( ret_number_of_symbols ( table<T>::matr [i][j] ) > max) ? ret_number_of_symbols (  table<T>::matr [i][j] ) : max;
		}
	}
	return max;
}



template <class T> matrix <T> &matrix <T> :: operator ~ ()
{
	matrix * temp;
	temp = new matrix <T> ( table<T>::width, table<T>::height );

	for ( unsigned int i = 0; i < table<T>::height; i++ )
		for ( unsigned int j = 0; j < table<T>::width; j++)
			temp->matr[j][i] += table<T>::matr[i][j];
	return *temp;
}



template <class T> matrix <T> &matrix <T> :: operator + ( const matrix <T> ob )
{
	matrix * temp;
	if ( ( table<T>::width != ob.width ) && ( table<T>::height != ob.height ) )
	{
		cerr << "\n\nerror: operator '+' - matrixes should be of the same size\n\n";
		return *this;
	}
	
	temp = new matrix <T> ( table<T>::width, table<T>::height );
	*temp = *this;
	
	for ( unsigned int i = 0; i < table<T>::height; i++ )
		for ( unsigned int j = 0; j < table<T>::width; j++)
			temp->matr[i][j] += ob.matr[i][j];
	return *temp;
}



template <class T> matrix <T> &matrix <T> :: operator - ( const matrix <T> ob )
{
	matrix * temp;
	if ( ( table<T>::width != ob.width ) && ( table<T>::height != ob.height ) )
	{
		cerr << "\n\nerror: operator '-' - matrixes should be of the same size\n\n";
		return *this;
	}
	
	temp = new matrix <T> ( table<T>::width, table<T>::height );

	*temp = *this;
	
	for ( unsigned int i = 0; i < table<T>::height; i++ )
		for ( unsigned int j = 0; j < table<T>::width; j++)
			temp->matr[i][j] -= ob.matr[i][j];
	return *temp;
}



template <class T> matrix <T> &matrix <T> :: operator * ( const matrix <T> ob )
{
	matrix * temp;
	if ( table<T>::width != ob.height )
	{
		cerr << "\n\nerror: operator '*' - the width of the first matrix must be equal to the height of the second one\n\n";
		return *this;
	}
	
	temp = new matrix <T> ( table<T>::width, table <T>::height );
	
	for ( unsigned int i = 0; i < temp->ret_h(); i++ )
		for ( unsigned int j = 0; j < temp->ret_w(); j++ )
		{
			for ( unsigned int counter = 0; counter < table<T>::width; counter++ )
				temp->matr[i][j] += table<T>::matr[i][counter] * ob.matr[counter][j];
		}
	return *temp;
}



template <class T> matrix <T> &matrix <T> :: operator * ( T num )
{
	matrix * temp;
	temp = new matrix <T> ( table<T>::width, table <T>::height );
	for ( unsigned int i = 0; i < temp->ret_h(); i++ )
		for ( unsigned int j = 0; j < temp->ret_h(); j++ )
			temp->matr[i][j] = table<T>::matr[i][j] * num;
	return *temp;
}



template <class T> T * matrix <T> :: operator [] ( int i ) const
{
	return ( i < 0 || i >= table<T>::height ) ? NULL : table<T>::matr[i];
}



template <typename T> void matrix <T> :: operator = ( const matrix <T> &ob )
{
	
	for ( unsigned int i = 0; i < table<T>::height; i++ )
	{
		delete [] table<T>::matr[i];
	}
	delete [] table<T>::matr;
	
	table<T>::height = ob.height;
	table<T>::width = ob.width;
	try
	{
		table <T>::matr = new T * [ob.height];
	}
	catch ( bad_alloc xa)
	{
		cerr << "error memory allocation\n";
		exit ( 1 );
	}
	for ( unsigned int i = 0; i < ob.height; i++ )
	{
		try
		{
			table<T>::matr[i] = new T [ob.width];
		}
		catch ( bad_alloc xa)
		{
			cerr << "error memory allocation\n";
			exit ( 1 );
		}
		for ( unsigned int j = 0; j < ob.width; j++ )
			table<T>::matr[i][j] = ob.matr[i][j];
	}
}



template <class T> T matrix <T> :: det ( void )
{
	if ( table<T>::width != table<T>::height )
	{
		cerr << "determinant could not be calculated for nonsquare matrix\n";
		return NULL;
	}
		
	
	matrix<T> * temp;
	T det = 0;

	if ( table<T>::width > 1 )
	{
		temp = new matrix <T> ( table<T>::width - 1, table<T>::height - 1 );
		
		for ( int i = 0; i < table<T>::width; i++ )
		{
 			for ( int j = 0; j < temp->table<T>::width; j++ )
				for ( int k = 0; k < temp->table<T>::height; k++ )
					temp->table<T>::matr[j][k] = table<T>::matr[j+1][ ( k < i ) ? k : k + 1];
			det = det + ( table<T>::matr[0][i] * ( ( i & 0x1 ) ? -1 : 1 ) * temp->det() );
		}
	}
	else
		det = table<T>::matr[0][0];
	return det;
}



template <class T> matrix <T> &matrix <T> :: operator ! ( void )
{
	int i, j, _i, _j, __i, __j;
	if ( table<T>::width != table<T>::height )
	{
		cerr << "determinant could not be calculated for nonsquare matrix\n";
		return *this;
	}
	if ( this->det() == 0 )
	{
		cerr << "determinant is 0, inverse matrix can not be found\n";
		return *this;
	}
	matrix <T> * temp_1;
	matrix <T> * temp_2;
	
	temp_1 = new matrix <T> ( table<T>::width, table <T>::height );

	for ( i = 0; i < table<T>::height; i++)
	{	

		for ( j = 0; j < table<T>::width; j++)
		{
			__i = 0;
			temp_2 = new matrix <T> ( table<T>::width - 1, table <T>::height - 1 );
			for ( _i = 0; _i < table<T>::height; _i++)
			{
				if ( _i == i ) continue;
				__j = 0;
				for ( _j = 0; _j < table<T>::width; _j++)
				{
					if ( _j == j ) continue;
					temp_2->matr[__i][__j] = table<T>::matr[_i][_j];
					__j++;
				}
				__i++;
			}
			temp_1->matr[i][j] = ( ( ( ( i + 1 ) + ( j + 1 ) ) & 0x1 == 1 ) ? -1 : 1 ) * temp_2->det();
		}
	}
	*temp_1= ~ ( *temp_1 );
	*temp_1 = *temp_1 * ( 1 / this->det() );
	//cout << 1 / temp_1->det() << endl;
	return *temp_1;
}


/*************************************************************************\
|*************************************************************************|
	the main function
|*************************************************************************|
\*************************************************************************/
/*

int main ( void )
{
	unsigned int rows, columns;
	matrix <double> tmp (4,3);
	
	cout << "\nThe first matrix:\n\n";
	do
	{
		cout << "Enter number of columns (1-10): ";
		cin >> columns;
	} while ( columns < 1 || columns > 10 );
	do
	{
		cout << "Enter number of rows (1-10): ";
		cin >> rows;
	} while ( rows < 1 || rows > 10 );
	cout << "\n";

	matrix<double> obj_0 ( columns, rows );
	
	cin >> obj_0;
	cout << obj_0;
	
	
	cout << "\nThe second matrix:\n\n";
	do
	{
		cout << "Enter number of columns (1-10): ";
		cin >> columns;
	} while ( columns < 1 || columns > 10 );
	do
	{
		cout << "Enter number of rows (1-10): ";
		cin >> rows;
	} while ( rows < 1 || rows > 10 );
	cout << "\n";

	matrix<double> obj_1 ( columns, rows );
	
	cin >> obj_1;
	cout << obj_1;
	
	cout << "\n----------------------\nmatrix_1 + matrix_2:\n";
	tmp = obj_0 + obj_1;
	cout << tmp;
	
	cout << "\n----------------------\nmatrix_1 - matrix_2:\n";
	tmp = obj_0 - obj_1;
	cout << tmp;
	
	cout << "\n----------------------\nmatrix_1 * matrix_2:\n";
	tmp = obj_0 * obj_1;
	cout << tmp;
	
	cout << "\n----------------------\nmatrix_1 * 5\n";
	tmp = obj_0 * 5;
	cout << tmp;
	
	cout << "\n----------------------\n~matrix_1:\n";
	tmp = ~obj_0;
	cout << tmp;
	
	cout << "\n----------------------\ndet:\n";
	cout << obj_0.det();
	cout << "\n";
	
	cout << "\n----------------------\n!matrix_1:\n";
	tmp = !obj_0;
	cout << tmp;
	cout << obj_0 * tmp;


	return 0;
}*/


#endif
