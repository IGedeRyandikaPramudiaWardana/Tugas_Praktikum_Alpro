#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[])
 {
    float num1, num2, result1;
	 
	if (argc == 4) // memanggil jika argumen bernilai 4
	{
		num1 = atof(argv[1]); //mengubah karakter/argumen kedua menjadi integer/float
    	num2 = atof(argv[3]); //mengubah karakter/argumen keempat menjadi integer/float
		if (strcmp(argv[2], "+") == 0)
		{
			result1 = num1 + num2;
			printf("Hasil: %.2f\n", result1);
		}
	    else if(strcmp(argv[2], "-") == 0)
	    {
	    	result1 = num1 - num2;
	    	printf("Hasil: %.2f\n", result1);
		}
	    else if (strcmp(argv[2], "*") == 0)
	    {
	    	result1 = num1 * num2;
			printf("Hasil: %.2f\n", result1);	
		}
	    else if (strcmp(argv[2], "/") == 0)
	    {
	    	result1 = num1 / num2;
	    	printf("Hasil: %.2f\n", result1);	
		}
	    else if (strcmp(argv[2], "div") == 0)
		{
	        result1 = (int)num1 / (int)num2;
	        printf("Hasil: %.0f\n", result1);
		}
	    else if (strcmp(argv[2], "mod") == 0 )
		{
			result1 = (int)num1 % (int)num2;
			printf("Hasil: %.0f\n", result1);
		 } 
	    else if (strcmp(argv[2], "%") == 0) 
		{
			result1 = (int)num1 % (int)num2;
	        int sisa = (int)num1 % (int)num2;
	        printf("Hasil: %.0f\n", result1);
	        printf("Sisa %i\n", sisa); 
		}
	    else if (strcmp(argv[2], "pangkat") == 0)
	    {
	    	result1 = pow(num1, num2);
	    	printf("Hasil: %.2f\n", result1);
		}	
	    else if (strcmp(argv[2], "log") == 0)
	    {
	    	result1 = log(num2) / log(num1);
			printf("Hasil: %.2f\n", result1);	
		}
	    else if (strcmp(argv[1], "sum") == 0) 
		{
	        int n = argc - 2;
	        result1 = 0;
	        int i;
	        for (i = 0; i < n; i++) 
			{
	            double temp;
	            sscanf(argv[i + 2], "%lf", &temp);
	            result1 += temp;
	        }
	        printf("Hasil: %.2lf\n", result1);	
	    }
	     else if (strcmp(argv[1], "avg") == 0) {
	        int n = argc - 2;
	        result1 = 0;
	        int i;
	        for ( i = 0; i < n; i++) {
	            double temp;
	            sscanf(argv[i + 2], "%lf", &temp);
	            result1 += temp;
	        }
	        result1 /= n;
	        printf("Hasil: %.2lf\n", result1);	
	    }
	}
   else if (argc == 3)
   {
   		num1 = atof(argv[2]);
	   	if (strcmp(argv[1], "sqrt") == 0)
	   	{
	        result1 = sqrt(num1);
	        printf("Hasil: %.2lf\n", result1);
		}
	    else if (strcmp(argv[1], "sin") == 0)
	    {
	        result1 = sin(num1 * M_PI / 180.0);
	        printf("Hasil: %.2lf\n", result1);
		}
	    else if (strcmp(argv[1], "cos") == 0)
	    {
	        result1 = cos(num1 * M_PI / 180.0);
	        printf("Hasil: %.2lf\n", result1);
		}
	    else if (strcmp(argv[1], "tan") == 0)
		{ 
	    	result1 = tan(num1 * M_PI / 180.0);
	    	if ( num1 == 90 || num1 == -90)
	    	{
	    		printf("tan %.f tidak terdefinisi!!", num1);
			}
			else{
				printf("Hasil: %.2lf\n", result1);
			}
		}
	    else if (strcmp(argv[1], "log") == 0)
		{
	        result1 = log10(num1);
	        printf("Hasil: %.2lf\n", result1);
		}
	    else if (strcmp(argv[1], "ln") == 0)
	    {
	        result1 = log(num1);
	        printf("Hasil: %.2lf\n", result1);
		}
	    else if (strcmp(argv[1], "factorial") == 0)
		 {
	        int n = (int)num1;
	        result1 = 1;
	        int i;
	        for( i = 1; i <= n; i++) {
	            result1 *= i;
        	}
        	printf("Hasil: %.2lf\n", result1);
    	}
	}
   	
    else if ( argc > 4)
	{
    	num1 = atof(argv[1]);
    	num2 = atof(argv[3]);
    	if (strcmp(argv[1], "sum") == 0) 
		{
	        int n = argc - 2;
	        result1 = 0;
	        int i;
	        for (i = 0; i < n; i++) 
			{
	            double temp;
	            sscanf(argv[i + 2], "%lf", &temp);
	            result1 += temp;
	        }
	    }
	    else if (strcmp(argv[1], "avg") == 0) {
	        int n = argc - 2;
	        result1 = 0;
	        int i;
	        for ( i = 0; i < n; i++) {
	            double temp;
	            sscanf(argv[i + 2], "%lf", &temp);
	            result1 += temp;
	        }
	        result1 /= n;
	    }
	    else {
	        printf("Operasi tidak valid\n");
	        return 1;
    	}
    	
	 	printf("Hasil: %.2lf\n", result1);
   }
 return 0;
}

