#include <cstdio> //saya menggunakan header cmath untuk operasi logaritma dll.
#include <cstdlib> 
#include <cmath>
//#include <bayu>

int main(int argc, char** argv) {

	int num1,num2,operationSign;
	if (argc == 4){	/*untuk argumen = 3,
	ubah variabel num1 dan num 2 menjadi int */
	num1 = atoi(argv[1]);
	num2 = atoi(argv[3]);
	operationSign = argv[2][0];//tanda diambil di argumen kedua
	switch(operationSign){
		case '+':// operasi penambahan
		{
			int x = num1 + num2;
			printf ("%i",x); 
			break;
		}
		case '-':// operasi pengurangan
		{
			int x = num1 - num2; 
			printf ("%i",x); 
			break;
		}
		case '*':// operasi perkalian
		{
			int x = num1 * num2; 
			printf ("%i",x); 
			break;
		}
		case '/':// operasi pembagian
		{
			float x = (float)num1 / (float)num2;
			printf ("%.1f",x); 
			break;
		}
		case 'm':// operasi modulus
		{
			int x = num1 % num2;
			printf ("%i",x); 
			break;
		}
		case 'p':/* operasi perpangkatan ,
		untuk operasi ini saya menggunakan huruf p 
		sebagai simbol karena tanda ^ tidak bisa digunakan*/
		{	
			int x = pow(num1, num2);
			printf ("%i",x); 
			break;
		}
		{
		case 'L': // Operasi log
		{
 		   double log_value_base_10 = log10(num2);
			double log_base_base_10 = log10(num1);
 		   double result = log_value_base_10 / log_base_base_10;
  			printf("%1.f\n",result);
 		   break;
		}

		}
		default:// pesan error untuk 3 argumen
		{
			printf ("Tanda yang anda masukkan salah\n");
			printf ("Gunakan tanda '+' untuk operasi penambahan\n");
			printf ("Gunakan tanda '-' untuk operasi pengurangan\n");
			printf ("Gunakan tanda '*' untuk operasi perkalian\n");
			printf ("Gunakan tanda '/' untuk operasi pembagian\n");
			printf ("Gunakan tanda 'p' untuk operasi perpangkatan\n");
			printf ("Gunakan tanda 'm' untuk operasi modulus\n");
			printf ("Gunakan tanda 'L' untuk operasi log\n");
			break;
		}
		}
	}
	else if (argc == 3){/*untuk argumen = 2 , 
	tidak memerlukan variabel num2*/
	num1 = atoi(argv[2]);
	operationSign = argv[1][0];// tanda diambil di argumen pertama
	switch (operationSign){
	case 'a'://operasi pengakaran
	{
		int x = sqrt(num1);
		printf ("%.i",x); 
		break;
	}
	case 'L':// operasi logaritma basis 10
	{
		float x = log10(num1);
		printf ("%.1f",x); 
		break;
	}
		case 'S':// operasi sin
	{
		double angle_radians, result;
		angle_radians = num1 * M_PI / 180;
		float x = sin(angle_radians);
		result = sin(angle_radians);
		printf ("%.1f",result); 
		break;
	}
		case 'C':// operasi cos
	{
		double angle_radians, result;
		angle_radians = num1 * M_PI / 180;
		float x = cos(angle_radians);
		result = cos(angle_radians);
		printf ("%.1f",result); 
		break;
	}
		case 'T':// operasi sin
	{
		double angle_radians, result;
		angle_radians = num1 * M_PI / 180;
		float x = tan(angle_radians);
		result = tan(angle_radians);
		printf ("%.1f",result); 
		break;
	}
			
		case 'f':// operasi faktorial
		{
   	 	int faktorial = 1;
   	 	for (int i = 1; i <= num1; i++) {
        faktorial *= i;
    }
    	printf ("%d",faktorial);
		break;
		}
		case 'l':// operasi ln
	{
		float x = log(num1);
		printf ("%.1f",x); 
		break;
	}
	default:// pesan error untuk 2 argumen
		{
			printf ("Tanda yang anda masukkan salah\n");
			printf ("Gunakan tanda 'a' untuk operasi pengakaran\n");
			printf ("Gunakan tanda 'L' untuk operasi logaritma berbasis 10\n");
			printf ("Gunakan tanda 'S' untuk operasi sin\n");
			printf ("Gunakan tanda 'C' untuk operasi cos\n");
			printf ("Gunakan tanda 'T' untuk operasi tan\n");
			printf ("Gunakan tanda 'l' untuk operasi ln\n");
			printf ("Gunakan tanda 'f' untuk operasi faktorial\n");
			break;
		}
	}
	}
	else{//pesan error jika user memasukkan argumen tidak sesuai
		printf ("Jumlah argumen tidak sesuai\n");
		printf ("Silahkan masukkan 3 argumen untuk operasi penambahan,pengurangan,pembagian,perkalian,modulus & perpangkatan\n");
		printf ("Silahkan masukkan 2 argumen untuk operasi pengakaran & logaritma\n");
	}

	return 0;
}
