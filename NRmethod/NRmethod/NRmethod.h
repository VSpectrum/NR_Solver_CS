// NRmethod.h

#pragma once
#include <cmath>
using namespace System;

namespace NRmethod {

	public ref class NR
	{
		public:
		array<double>^ inpnums;   //MSDN form of setting up a dynamic array (using pointers/handlers)
		array<double>^ differentiated;
		array<double>^ roots;

		NR(double a, double b, double c, double k) //ax^3+bx^2+cx+k=0 , coefficients are inputted when constructed
		{
			inpnums = gcnew array<double>(4); //creating the array dynamically and setting the size
			differentiated = gcnew array<double>(4);
			roots = gcnew array<double>(3);
			inpnums[0]=k;
			inpnums[1]=c;
			inpnums[2]=b;
			inpnums[3]=a;
			getroots(); //finds the roots
		}

		bool dcompare(double num1, double num2)
		{
			if(fabs(num1-num2)<=0.0000001) return true; //If the difference of the number is less than 1/1000000, then it is considered the same
			else return false; //else the numbers are different numbers
		}
		
		double diffx(double x)
		{
			double sumupf=0,sumupfp=0;
			for(short i=3; i>=0; --i)
			{
				sumupf+=inpnums[i]*pow(x,i); //calculates original function with an input number, x
				sumupfp+=differentiated[i]*pow(x,i); //calculates differentiated function with an input, x
			}
			if(sumupfp>0.000000001 || sumupfp<-0.000000001) return (sumupf/sumupfp); //tries to avoid denominators of 0
			else return x-5;
		}
		
		bool recurseNR(double prevx, short count, int timetodie)
		{
			double end = diffx(prevx);
			if(fabs(end)>100000000 || timetodie>=10000) return false;
			if(end<0.000000001 && end>-0.000000001)   //ends if the prevx hasnt changed by at least .0000001 (suggesting root is found)
			{
				roots[count]=prevx;
			 	return true;
			}
			else recurseNR(prevx-end, count, ++timetodie);
		}
		
		void getroots()
		{
			for(int i=3; i>0; --i) differentiated[i-1]=i*inpnums[i]; //differentiates
			recurseNR(-100000000,0,0); //finds 'left' root
			recurseNR(100000000,1,0); //find 'right' root
			roots[2] = -inpnums[2]-roots[0]-roots[1]; //comparing roots with x^2 coefficient, finding 'middle' root
			
			if(inpnums[3]!=0)
			{
				/* below means : if the outer roots are the same then there is no middle root,
				 * therefore, do not show middle root and 1 of the outer roots */
				if(dcompare(roots[0],roots[1])) roots[1]=100000000, roots[2]=100000000; 
			}

			else if(inpnums[2]!=0)
			{
				roots[2] = 100000000; //there is no x^3 coefficient therefore 3rd root doesnt exist
				/* below is a representation b^2 < 4ac . If this condition is true, roots are imaginary, therefore, no output is needed */
				if( (inpnums[1]*inpnums[1]) < (4*inpnums[2]*inpnums[0]) ) roots[1] = 100000000, roots[0] = 100000000;
			}
			
			else if(inpnums[1]!=0) roots[2] = 100000000, roots[1] = 100000000; //no x^3 or x^2 coefficients therefore only 1 root needs to be displayed.
			
			else roots[2] = 100000000, roots[1] = 100000000, roots[0] = 100000000; //no inputs can be taken (all x coeff are 0) therefore no roots.
		}
	};
}
