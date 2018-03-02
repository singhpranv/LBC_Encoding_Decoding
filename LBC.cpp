// LBC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"    //exclude if you are not using visual studio
#include<iostream>
#include<bitset>
#include<math.h>

using namespace std;


//class lbc containing necessary elements 

class lbc
{
public:
	lbc(int, int, int, int);
	~lbc();
	void input();
	void print();
	void checkType();
	void generateMatrices();
	void generateCodeVectors();

private:
	int n, k, x, y;
	bool **ipMatrix, **genMatrix, **hMatrix, **pMatrix, **symbols,***checkBits,**checkBitMatrix, **codeVectors;
	int **noOfOnes, *weight;
	char type;
	void print(bool**, int, int);
	void print(int**, int, int);

	
};


// constructor for class lbc

lbc::lbc(int n1, int k1, int x1, int y1)
{
	ipMatrix = new bool*[x1];
	for (int i = 0; i < x1; ++i)   ipMatrix[i] = new bool[y1];
		
	n = n1;
	k = k1;
	x = x1;
	y = y1;

}

// a function take a matrix of defined order from user

void lbc::input()
{
	cout << "enter elements\n";
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			cout << "(" << i << "," << j << ") \t";
			cin >> ipMatrix[i][j];
		} cout << "\n";
	}
}


// a function to print entered martrix

void lbc::print()
{
	
	for (int i = 0; i < x; i++)
	{
		cout << "\t";
		for (int j = 0; j < y; j++)
		{
			//cout << bitset<8>(ipMatrix[i * j]) << "\t";
			cout << ipMatrix[i][j] << "\t";
		} cout << "\n";


	}
	
}

void lbc::print(bool **mat, int row, int col)
{ 
	for (int i = 0; i < row; i++)
	{
		cout << "\t";
		for (int j = 0; j < col; j++)
		{
			//cout << bitset<8>(ipMatrix[i * j]) << "\t";
			cout << mat[i][j] << "\t";
		} cout << "\n";


	}
}

void lbc::print(int **mat, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		cout << "\t";
		for (int j = 0; j < col; j++)
		{
			//cout << bitset<8>(ipMatrix[i * j]) << "\t";
			cout << mat[i][j] << "\t";
		} cout << "\n";


	}
}


// a function to check the type of matrix entered by user

void lbc::checkType()
{
	if (x == k && y == (n - k))                    // checks if entered matrix is a parity bit matrix
	{
		type = 'P';             
		cout << "\n the entered is a parity bit matix";
		return;
	}


	if (x == k && y == n)                         // checks if entered matrix is generator matrix
	{
		bool flag= true;
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < (y - x); j++)
			{
				if (i != j && ipMatrix[i][j] != 0)
				{   
					flag = false;
					break;
				}

				if (i == j && ipMatrix[i][ j] != 1)
				{   
					flag = false;
				    break;
                }


			}
		}

		if (flag)
		{
			type = 'G';             
			cout << "\n the entered is a generator matix";
			return;
			
		}
	}


	if (x == n-k && y == n)                         // checks if entered matrix is hamming matrix
	{
		int diff = y - x;
		bool flag =true;
		for (int i = 0; i < x; i++)
		{
			for (int j = (y-x); j < y; j++)
			{
				if ((i+j == diff) && ipMatrix[i][j] != 1)
				{
					flag = false;
					break;
				} 
				if ( (i+j)!=diff && ipMatrix[i][j] != 0)
				{
					flag = false;
					break;
				}


			}  diff += 2;
		}

		if (flag)
		{
			type = 'H';
			cout << "\n the entered is a hamming matix";
			return;
			
		}
	}

}


// a function to generate H, G and P

void lbc::generateMatrices()
{
	cout << "\n...............................Generating Matrices .............................\n";
	
	genMatrix = new bool*[k];
	for (int i = 0; i < k; ++i)   genMatrix[i] = new bool[n];

	hMatrix = new bool*[n-k];
	for (int i = 0; i < (n-k); ++i)   hMatrix[i] = new bool[n];

	pMatrix = new bool*[k];
	for (int i = 0; i < k; ++i)   pMatrix[i] = new bool[n-k];


	switch (type)
	{
	case 'P' :
	{   
		pMatrix = ipMatrix;

		cout << "\n Parity Matrix  : \n";
		print(ipMatrix, k, n - k);

		//**********************************************************generator matrix  remember G=[I:P]

		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j <= (n - k); j++)
			{
				if (i != j)  genMatrix[i][j] = 0;
				else if (i == j) genMatrix[i][j] = 1;				
			}
		}

		
		for (int i = 0; i < k; i++)
		{
			for (int j = (n - k)+1, p=0; j < n && p<(n-k) ; j++,p++)
			{
				genMatrix[i][j] = pMatrix[i][p];
			}  
		}

		cout << "\n Generator Matrix Generated : \n";
		print(genMatrix, k, n);


		//**********************************************************Hamming Matrix  remember H=[Pt:I]

	
		int diff = k;

		for (int i = 0; i < (n - k); i++)
		{
			for (int j = 0; j < k; j++)
			{
				hMatrix[i][j] = pMatrix[j][i];

			}
		}

		for (int i = 0; i < (n - k); i++)
		{
			for (int j = k; j < n; j++)
			{
				if ((i + j == diff)) hMatrix[i][j] = 1;
				
				else if ((i + j) != diff) hMatrix[i][j] = 0;
				


			}  diff += 2;
			
		}

		cout << "\n Hamming Matrix Generated : \n";
		print(hMatrix, n-k, n);

		break;

	}

	case 'G' :
	{
		genMatrix = ipMatrix;
		cout << "\n Generator Matrix  : \n";
		print(genMatrix, k, n );

		//**************************************************** Parity Matrix remember G=[I:P]

		for (int i = 0; i < k; i++)
		{
			for (int j = ((n - k) + 1),p=0; j < n,p<(n-k); j++,p++)
			{
				pMatrix[i][p] = genMatrix[i][j];
			}
		}
         
		cout << "\n Parity Matrix Generated  : \n";
		print(pMatrix, k, n - k);


		//*************************************************** Hamming Matrix remember H=[Pt:I]

		for (int i = 0; i < n - k; i++)
		{
			for (int j = 0; j < k; j++)
			{
				hMatrix[i][j] = pMatrix[j][i];

			}
		}

		int diff = k;
		for (int i = 0; i < (n - k); i++)
		{
			for (int j = k; j < n; j++)
			{
				if ((i + j == diff)) hMatrix[i][j] = 1;

				else if ((i + j) != diff) hMatrix[i][j] = 0;

			}  diff += 2;

		}

		cout << "\n Hamming Matrix Generated  : \n";
		print(hMatrix, n-k, n);

		break;


	}

	case 'H':
	{
		hMatrix = ipMatrix;
		cout << "\n Hamming Matrix :\n";
		print(hMatrix, n - k, n);

		//*********************************************generating parity matrix remember H=[pt:I]

		for (int i = 0; i <= (n - k);i++)
		{
			for (int j = 0; j < n-k; j++)
			{
				pMatrix[i][j] = hMatrix[j][i];
			}
		}

		cout << "\n Parity Matrix generated :\n";
		print(pMatrix, k, n - k);

		//**********************************************************generator matrix  remember G=[I:P]

		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j <= (n - k); j++)
			{
				if (i != j)  genMatrix[i][j] = 0;
				else if (i == j) genMatrix[i][j] = 1;
			}
		}


		for (int i = 0; i < k; i++)
		{
			for (int j = (n - k) + 1, p = 0; j < n && p<(n - k); j++, p++)
			{
				genMatrix[i][j] = pMatrix[i][p];
			}
		}

		cout << "\n Generator Matrix Generated : \n";
		print(genMatrix, k, n);
		
	}

	
	}
}


// a function to generate code vectors

void lbc::generateCodeVectors()
{   

	// generate a matrix of binary message bits from 0 to 2^k

	int power = pow(2, k);

	symbols = new bool*[power];
	for (int i = 0; i < power; ++i)  symbols[i] = new bool[k];

	int count ;
	bool bit ;

	for (int bitPos = 0; bitPos < k; bitPos++)
	{
		count = 0;
		bit = 0;
		
			for (int j = 0; j < power; j++)
			{
				symbols[j][k-(bitPos+1)] = bit;
				++count;
				if (count == pow(2,bitPos))
				{   count = 0;
					if (bit)
					{
						bit = 0;
					}
					else
					{
						bit = 1;
					}


				}
			}
			
		 
	}

	cout << "\nwe have following message bits : \n";
	print(symbols, power, k);

	// generate check bit matrix for each bit (c1, c2, c3,....) for ex-oring i.e (n-k) matrices of order (power * k)
    
	checkBits = new bool**[n - k];
	for (int i = 0; i < (n - k); ++i)
	{
		checkBits[i] = new bool*[power];
		for (int j = 0; j < power ; j++)
		checkBits[i][j] = new bool[k];

	   }

	for (int i = 0; i < n - k ; i++)
	{
		for (int j = 0; j < power; j++)
		{
			for (int l = 0; l < k; l++)
			{
				checkBits[i][j][l] = symbols[j][l] * pMatrix[l][i];
			}
		}
	}


	/*cout << "\nmultiplying check bits with respective message bits  :";
	for (int i = 0; i < n - k; i++)
	{
		print(checkBits[i], power, k);
		cout << "\n";
	}*/


	// now that checkbits have been multiplied with corresponding message bits, thing left to do is moduli-2 addition of check bits

	noOfOnes = new int*[power];
	for (int i = 0; i < power; i++) noOfOnes[i] = new int[n - k];
	
	for (int i = 0; i < power; i++)
		for (int j = 0; j < n-k; j++)
			noOfOnes[i][j] = 0;                                                    //count no of ones in checkbits

	for (int i = 0; i < n - k; i++)
	{
		for (int j = 0; j < power; j++)
		{
			for (int l = 0; l < k; l++)
			{
				if (checkBits[i][j][l] == 1) noOfOnes[j][i]++;
				
			}
		}
	}

	

	//*************** moduli 2  on the basis of logic that if a there are odd number of ones then op is 1 otherwise 0

	checkBitMatrix = new bool*[power];
		for (int i = 0; i < power; i++) checkBitMatrix[i] = new bool[n - k];
    
		for (int i = 0; i < power; i++)
		{
			for (int j = 0; j < k; j++)
			{
				if (noOfOnes[i][j] % 2 == 0)
				{
					checkBitMatrix[i][j] = 0;
				}
				else
				{
					checkBitMatrix[i][j] = 1;
				}
			}
		}
    
    //****************** creating code vector matrix 

		codeVectors = new bool*[power];
		for (int i = 0; i < power; i++) codeVectors[i] = new bool[n];

		for (int i = 0; i < power; i++)
		{
			for (int j = 0; j < k; j++)
				codeVectors[i][j] = symbols[i][j];

			for (int j = k; j < n; j++)
				codeVectors[i][j] = checkBitMatrix[i][j-k];
		}
       
		cout << "\n code vectors :";
		print(codeVectors, power, n);

  		

	
}

lbc::~lbc()
{
}

int main()
{

	int n, k, x, y;     //where variables n & k  have there usual meaning as in LBC and x & y are order of matrix user has
	
	

	cout << "enter order of lbc (n,k), first n then k";
	cin >> n >> k;
	cout << "enter the order of matrix you want to enter (x*y), first x then y";
	cin >> x >> y;
	lbc container(n,k,x,y);

	container.input();
	container.print();
	container.checkType();
	container.generateMatrices();
	container.generateCodeVectors();


	return 0;
}


