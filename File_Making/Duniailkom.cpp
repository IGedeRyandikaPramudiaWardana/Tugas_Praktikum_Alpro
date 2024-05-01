#include <stdio.h>
 
int main(void)
{
  printf("## Program Bahasa C Biodata Mahasiswa ## \n");
  printf("======================================== \n\n");
 
  char nama[50], nim[10], fakultas[60];
  char jurusan[60], kota_asal[60], alamat[200];
 
  // proses input data mahasiswa
  printf("Nama mahasiswa: ");
  gets(nama);
 
  printf("NIM: ");
  gets(nim);
 
  printf("Fakultas: ");
  gets(fakultas);
 
  printf("Jurusan: ");
  gets(jurusan);
 
  printf("Kota Asal: ");
  gets(kota_asal);
 
  printf("Alamat: ");
  gets(alamat);
 
  printf("\n");
 
  // Tampilkan biodata mahasiswa
  printf("# Data Mahasiswa # \n");
  printf("================== \n");
  printf("Nama: %s \n",nama);
  printf("NIM: %s \n",nim);
  printf("Fakultas: %s \n",fakultas);
  printf("Jurusan: %s \n",jurusan);
  printf("Kota Asal: %s \n",kota_asal);
  printf("Alamat: %s \n",alamat);
 
  return 0;
}