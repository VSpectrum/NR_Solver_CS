#include <cmath>
class NR
{
	public:
		double inpnums[4];
		double differentiated[4];
		double roots[3];

		bool dcompare(double a, double b)
		{
			if(a-b<=0.000001 && a-b>=-0.000001) return true;
			else return false;
		}
		
		double diffx(double x)
		{
			double sumupf=0,sumupfp=0;
			for(short i=3; i>=0; --i)
			{
				sumupf+=inpnums[i]*pow(x,i);
				sumupfp+=differentiated[i]*pow(x,i);
			}
			if(sumupfp>0.0001 || sumupfp<-0.0001) return (sumupf/sumupfp); //tries to avoid denominators of 0
			else return x-5;
		}
		
		bool recurseNR(double prevx, short count)
		{
			double end = diffx(prevx);
			if(fabs(end)>100000000) return false;
			if(end<0.0000001 && end>-0.0000001)   //ends if the prevx hasnt changed by at least .0000001 (suggesting root is found)
			{
				roots[count]=prevx;
			 	return true;
			}
			else recurseNR(prevx-end, count);
		}
		
		void getroots()
		{
			for(int i=3; i>0; --i) differentiated[i-1]=i*inpnums[i]; //differentiates
			recurseNR(-100000000,0);
			recurseNR(100000000,1);
			roots[2] = -inpnums[2]-roots[0]-roots[1]; //comparing roots with x^2 coefficient
			if(inpnums[3] && dcompare(roots[0],roots[1])) 
				roots[1]=100000000, roots[2]=100000000;
			else if(inpnums[2] && inpnums[3]==0)
				roots[2] = 100000000;
		}
};
