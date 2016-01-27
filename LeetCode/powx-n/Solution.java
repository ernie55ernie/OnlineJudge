public class Solution {
    public double myPow(double x, int n) {
    	if(x == 1)
    		return 1;
    	if(x == -1)
    		return (n % 2 == 0) ? 1 : -1;
    	if(n < 0){
    		n = - n;
    		x = 1 / x;
    	}
    	return pow(x, n);
    }

    double pow(double x, int n){
		if(n % 2 != 0){
   			return pow(x, n - 1) * x;
    	}else{
    		if(n == 0) return 1;
	   		double value = pow(x, n / 2);
	   		return value * value;
    	}
    }
}