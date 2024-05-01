#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[])
{
	double angka1, angka2, hasil;
	
	
	if(argc == 4)
	{
		angka1 = atof(argv[1]);
		angka2 = atof(argv[3]);
		
		if (strcmp(argv[2], "tambah") == 0) 
	{
        printf("%d + %d = %d\n", (int)angka1, (int)angka2, (int)angka1 + (int)angka2);
    } 
    
	else if (strcmp(argv[2], "kurang") == 0) 
	{
        printf("%d - %d = %d\n", (int)angka1, (int)angka2, (int)angka1 - (int)angka2);
    } 
    
	else if (strcmp(argv[2], "kali") == 0) 
	{
        printf("%d * %d = %d\n", (int)angka1, (int)angka2, (int)angka1 * (int)angka2);
    } 
	else if (strcmp(argv[2], "div") == 0) 
	{
        printf("%d div %d = %d\n", (int)angka1, (int)angka2, (int)angka1 / (int)angka2);
    } 
	
	else if (strcmp(argv[2], "mod") == 0) 
	{
        printf("%d mod %d = %d\n", (int)angka1, (int)angka2, (int)angka1 % (int)angka2);
    } 
	
	else if (strcmp(argv[2], "bagi") == 0) 
	{
        printf("%d %% %d = %d sisa %d\n", (int)angka1, (int)angka2, (int)angka1 / (int)angka2, (int)angka1 % (int)angka2);
    } 
	
	else if (strcmp(argv[2], "pangkat") == 0) 
	{
        printf("%d ^ %d = %.0f\n", (int)angka1, (int)angka2, pow(angka1, angka2));
	}
	else if (strcmp(argv[2], "log") == 0) 
	{
		hasil = log(angka2) / log(angka1);
        printf("%d log %d = %.2f\n", (int)angka1, (int)angka2, hasil);
    } 
    else if(strcmp(argv[1], "sum") == 0)
    {
    	int n = argc - 2;
    	hasil = 0;
    	int i;
    	for(i = 0; i < n; i++)
    	{
    		double temp = atof(argv[i + 2]);
    
    		hasil += temp;
		}
		printf("%.2f", hasil);
	}
    else if(strcmp(argv[1], "avg") == 0)
    {
    	int n = argc - 2;
    	hasil = 0;
    	int i;
    	for(i = 0; i < n; i++)
    	{
    		double temp = atof(argv[i + 2]);
    
    		hasil += temp;
		}
		hasil /= n;
		printf("%.2f", hasil);
	}
	}
	
	else if(argc == 3)
	{
		angka1 = atof(argv[2]);
		if(strcmp(argv[1], "sqrt") == 0)
		{
			hasil = sqrt(angka1);
		}
		else if(strcmp(argv[1], "sin") == 0)
		{
			hasil = sin(angka1 * M_PI / 180.0);
		}
		else if(strcmp(argv[1], "cos") == 0)
		{
			hasil = cos(angka1 * M_PI / 180.0);
		}
		else if(strcmp(argv[1], "tan") == 0)
		{
			hasil = tan(angka1 * M_PI / 180.0);
		}
		else if(strcmp(argv[1], "log") == 0)
		{
			hasil = log10(angka1);
		}
		else if(strcmp(argv[1], "ln") == 0)
		{
			hasil = log(angka1);
		}
		else if(strcmp(argv[1], "factorial") == 0)
		{
			int n = (int)angka1;
			hasil = 1;
			int i;
			for(i = 1; i <= n; i++)
			{
				hasil *= i;
			}
		} 
		printf("hasilnya %.2f", hasil);
	}
	
	
	
	else if(argc > 4)
	{	

	if(strcmp(argv[1], "sum") == 0)
    {
    	int n = argc - 2;
    	hasil = 0;
    	int i;
    	for(i = 0; i < n; i++)
    	{
    		double temp = atof(argv[i + 2]);
    		
    		hasil += temp;
		}
		
		printf("\n%.2f\n", hasil);
	}
	else if(strcmp(argv[1], "avg") == 0)
    {
    	int n = argc - 2;
    	hasil = 0;
    	int i;
    	for(i = 0; i < n; i++)
    	{
    		double temp = atof(argv[i + 2]);
    		
    		hasil += temp;
		}
		hasil /= n;
		printf("\n%.2f\n", hasil);
	}
	
	
	}
	
	return 0;
	
}