#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Mahasiswa
{
	char nama[100];
	unsigned int NIM;
	int tahunMasuk;
	float ipk;
};

void tambahData(char *filename)
{
    Mahasiswa mahasiswa;
    printf("\n\n");

    printf("Nama Mahasiswa: ");
    scanf(" %[^\n]", mahasiswa.nama);
    //getchar();
    //fgets(mahasiswa.nama, sizeof(mahasiswa.nama), stdin);
    mahasiswa.nama[strcspn(mahasiswa.nama, "\n")] = '\0';

	
    printf("NIM: ");
    scanf("%u", &mahasiswa.NIM);
    while(getchar() != '\n'); // Mengonsumsi newline yang tersisa dari input sebelumnya

    printf("Tahun Masuk: ");
    scanf("%d", &mahasiswa.tahunMasuk);
    while(getchar() != '\n'); // Mengonsumsi newline yang tersisa dari input sebelumnya

    printf("IPK: ");
    scanf("%f", &mahasiswa.ipk);
    while(getchar() != '\n'); // Mengonsumsi newline yang tersisa dari input sebelumnya

    printf("\n\n");

    FILE *fp = fopen(filename, "a");
    if(fp == NULL)
    {
        printf("Gagal membuka file %s.\n\n", filename);
        return;
    }

    fprintf(fp, "%s, %u, %d, %.2f\n", mahasiswa.nama, mahasiswa.NIM, mahasiswa.tahunMasuk, mahasiswa.ipk);
    fclose(fp);
}


void cariData(char *filename)
{
    char namaCari[100];
    unsigned int nimCari;
    int tahunMasukCari;
    float ipkCari;
	
	printf("\n\n");
    printf("Pilih kriteria pencarian:\n");
    printf("1. Nama\n");
    printf("2. NIM\n");
    printf("3. Tahun Masuk\n");
    printf("4. IPK\n");
    printf("Pilihan Anda: ");

    int pilihan;
    scanf("%d", &pilihan);
    while(getchar() != '\n'); // Mengonsumsi newline yang tersisa dari input sebelumnya

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: Gagal membuka file %s\n\n", filename);
        return;
    }

    struct Mahasiswa mahasiswa;
    int nomorUrut = 1;
    int ditemukan = 0;

    switch (pilihan)
    {
        case 1:
            printf("Masukkan nama yang ingin dicari: ");
            scanf("%[^\n]", namaCari);
            while(getchar() != '\n'); // Mengonsumsi newline yang tersisa dari input sebelumnya

            printf("\n\n### Hasil Pencarian berdasarkan Nama ###\n");
            break;
        case 2:
            printf("Masukkan NIM yang ingin dicari: ");
            scanf("%u", &nimCari);
            while(getchar() != '\n'); // Mengonsumsi newline yang tersisa dari input sebelumnya

            printf("\n\n### Hasil Pencarian berdasarkan NIM ###\n");
            break;
        case 3:
            printf("Masukkan tahun masuk yang ingin dicari: ");
            scanf("%d", &tahunMasukCari);
            while(getchar() != '\n'); // Mengonsumsi newline yang tersisa dari input sebelumnya

            printf("\n\n### Hasil Pencarian berdasarkan Tahun Masuk ###\n");
            break;
        case 4:
            printf("Masukkan IPK yang ingin dicari: ");
            scanf("%f", &ipkCari);
            while(getchar() != '\n'); // Mengonsumsi newline yang tersisa dari input sebelumnya

            printf("\n\n### Hasil Pencarian berdasarkan IPK ###\n");
            break;
        default:
            printf("Pilihan tidak valid.\n");
            fclose(fp);
            return;
    }

    printf("No. Nama, NIM, Tahun Masuk, IPK\n");

    while (fscanf(fp, " %99[^,], %u, %d, %f\n", mahasiswa.nama, &mahasiswa.NIM, &mahasiswa.tahunMasuk, &mahasiswa.ipk) == 4)
    {
        switch (pilihan)
        {
            case 1:
                if (strstr(mahasiswa.nama, namaCari) != NULL)
                {
                    printf("%d. %s, %u, %d, %.2f\n", nomorUrut, mahasiswa.nama, mahasiswa.NIM, mahasiswa.tahunMasuk, mahasiswa.ipk);
                    ditemukan = 1;
                }
                break;
            case 2:
                if (mahasiswa.NIM == nimCari)
                {
                    printf("%d. %s, %u, %d, %.2f\n", nomorUrut, mahasiswa.nama, mahasiswa.NIM, mahasiswa.tahunMasuk, mahasiswa.ipk);
                    ditemukan = 1;
                }
                break;
            case 3:
                if (mahasiswa.tahunMasuk == tahunMasukCari)
                {
                    printf("%d. %s, %u, %d, %.2f\n", nomorUrut, mahasiswa.nama, mahasiswa.NIM, mahasiswa.tahunMasuk, mahasiswa.ipk);
                    ditemukan = 1;
                }
                break;
            case 4:
                if (mahasiswa.ipk == ipkCari)
                {
                    printf("%d. %s, %u, %d, %.2f\n", nomorUrut, mahasiswa.nama, mahasiswa.NIM, mahasiswa.tahunMasuk, mahasiswa.ipk);
                    ditemukan = 1;
                }
                break;
        }
        nomorUrut++;
    }

    if (!ditemukan)
    {
        printf("\n\nData tidak ditemukan.\n");
    }

    fclose(fp);
    printf("\n");
}


void tampilkanData(char *filename)
{
	printf("### Data Mahasiswa ###\n");
	printf("======================\n");
	
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Error: Gagal membuka file %s\n\n", filename);
		return;
	}
	
	struct Mahasiswa mahasiswa;
	int noUrut = 1;
	
	printf("No. Nama, NIM, Tahun Masuk, IPK\n");
	
	while(fscanf(fp, " %99[^,], %u, %d, %f\n", mahasiswa.nama, &mahasiswa.NIM, &mahasiswa.tahunMasuk, &mahasiswa.ipk) == 4)
	{
		printf("%d. %s, %u, %d, %.2f\n", noUrut, mahasiswa.nama, mahasiswa.NIM, mahasiswa.tahunMasuk, mahasiswa.ipk);
		noUrut++;
	}
	
	printf("\n\n");
	
	fclose(fp);
}

void editData(char *filename)
{
    int pilihanEdit;
    struct Mahasiswa mahasiswa;

    // Menampilkan data terlebih dahulu
    printf("\n\n");
    tampilkanData(filename);

    printf("Pilih nomor urut data yang ingin diedit: ");
    scanf("%d", &pilihanEdit);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: Gagal membuka file %s\n\n", filename);
        return;
    }

    // Membuka file untuk menulis ulang data dengan memperbarui data yang diedit
    FILE *temp = fopen("temp.csv", "w");
    int nomorUrut = 1;

    while (fscanf(fp, " %99[^,], %u, %d, %f\n", mahasiswa.nama, &mahasiswa.NIM, &mahasiswa.tahunMasuk, &mahasiswa.ipk) == 4)
    {
        if (nomorUrut == pilihanEdit)
        {
            printf("Nama Mahasiswa: ");
            scanf(" %[^\n]", mahasiswa.nama);
            mahasiswa.nama[strcspn(mahasiswa.nama, "\n")] = '\0';

            printf("NIM: ");
            scanf("%u", &mahasiswa.NIM);
            while (getchar() != '\n'); // Mengonsumsi newline yang tersisa dari input sebelumnya

            printf("Tahun Masuk: ");
            scanf("%d", &mahasiswa.tahunMasuk);
            while (getchar() != '\n'); // Mengonsumsi newline yang tersisa dari input sebelumnya

            printf("IPK: ");
            scanf("%f", &mahasiswa.ipk);
            while (getchar() != '\n'); // Mengonsumsi newline yang tersisa dari input sebelumnya
        }

        fprintf(temp, "%s, %u, %d, %.2f\n", mahasiswa.nama, mahasiswa.NIM, mahasiswa.tahunMasuk, mahasiswa.ipk);
        nomorUrut++;
    }

    fclose(fp);
    fclose(temp);

    // Menghapus file asli dan menamai ulang file sementara
    remove(filename);
    rename("temp.csv", filename);

    printf("Data telah berhasil diedit.\n\n");
}


void hapusData(char *filename)
{
    int pilihanHapus;
    struct Mahasiswa mahasiswa;

    // Menampilkan data terlebih dahulu
    printf("\n\n");
    tampilkanData(filename);

    printf("Pilih nomor urut data yang ingin dihapus: ");
    scanf("%d", &pilihanHapus);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: Gagal membuka file %s\n\n", filename);
        return;
    }

    // Membuka file untuk menulis ulang data kecuali data yang dihapus
    FILE *temp = fopen("temp.csv", "w");
    int nomorUrut = 1;

    while (fscanf(fp, " %99[^,], %u, %d, %f\n", mahasiswa.nama, &mahasiswa.NIM, &mahasiswa.tahunMasuk, &mahasiswa.ipk) == 4)
    {
        if (nomorUrut != pilihanHapus)
        {
            fprintf(temp, "%s, %u, %d, %.2f\n", mahasiswa.nama, mahasiswa.NIM, mahasiswa.tahunMasuk, mahasiswa.ipk);
        }
        nomorUrut++;
    }

    fclose(fp);
    fclose(temp);

    // Menghapus file asli dan menamai ulang file sementara
    remove(filename);
    rename("temp.csv", filename);

    printf("Data telah berhasil dihapus.\n\n");
}

void operasi(char *filename)
{
	int pilihan;
	
	do
	{
		printf("Pilih Operasi: \n");
		printf("1. Tambah data baru\n");
		printf("2. Tampilkan data\n");
		printf("3. Cari Data\n");
		printf("4. Edit Data\n");
		printf("5. Hapus Data\n");
		printf("6. Keluar\n");
		printf("Pilihan anda: ");
		scanf("%d", &pilihan);
		
		switch(pilihan)
		{
			case 1:
				//system("cls");
				tambahData(filename);
				break;
			case 2:
				//system("cls");
				tampilkanData(filename);
				break;
			case 3:
				cariData(filename);
				break;
			case 4:
				editData(filename);
				break;
			case 5:
				hapusData(filename);
				break;
			case 6:
				//system("cls");
				printf("\n ### Anda telah keluar dari program ###");
				exit(0);
			default:
				printf("Pilihan anda tidak valid.");
		}
	} while (pilihan != 7);
}

void buatFile(char *filename)
{	
	FILE *fp = fopen(filename, "w");
	if(fp == NULL)
	{
		printf("Gagal membuat file %s.\n\n", filename);
		return;
	}
	
	printf("File %s berhasil dibuat.\n\n", filename);
	operasi(filename);
	fclose(fp);
}

void bukaFile(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("Gagal membuka file %s, coba masukkan nama yang berbeda.\n\n", filename);
        return;
    }
    
    printf("File %s berhasil dibuka.\n\n", filename);
    operasi(filename); // Mengirim nama file ke fungsi operasi
    
    fclose(fp);
}




int main(int argc, char** argv)
{
 	char filename[100];  
    int opsi;
	printf("Pilihan: \n");
	printf("1. Membuat file baru.\n");
	printf("2. Membuka file yang sudah ada.\n");
	printf("3. Keluar.\n");
	printf("Pilihan anda: ");
	scanf("%d", &opsi);
	
	switch(opsi)
	{
		case 1:
			printf("Masukkan namafile yang ingin dibuat: ");
			scanf("%s", &filename);
			strcat(filename, ".csv");
			buatFile(filename);
			break;
		case 2:
			printf("Masukkan namafile yang ingin dibuka: ");
			scanf("%s", &filename);
			strcat(filename, ".csv");
			bukaFile(filename);
			break;
		case 3:
			printf("\n ### Anda telah keluar dari program ###");
			exit(0);
		default:
			printf("Pilihan anda tidak valid");
	}
	
	operasi(filename);
	
	return 0;
}