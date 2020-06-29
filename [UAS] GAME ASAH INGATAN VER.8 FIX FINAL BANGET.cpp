#include <iostream>				/* printf, scanf, puts, NULL */
#include <string>
#include <conio.h>
#include <fstream>              // Untuk file handling
#include <ctime>
#include <stdlib.h>           /* srand, rand */
#include <time.h>            /* time_t, struct tm, difftime, time, mktime */
#include <windows.h>        /* Untuk mewarnai text */

using namespace std;

/* PENTING! JANGAN DIOTAK-ATIK */
// size untuk membaca file_highscore
int size = 0;
//read file into array
int ArrayAngkaSkor[100];
int ArrayAngkaSkor_sudah_urut[100];
int level=1, digit_angka, stages=1; 
int skor=0, nyawa;

/* Boleh diotak-atik. Tingkat_kesulitan semakin banyak angkanya, 
semakin mudah karena waktu menghafalnya semakin lama */
int max_level=5, max_stages=10, tingkat_kesulitan=3; 

string opsi_user;

int soal[100];
int jawaban[100];
/* Functions untuk game */

string setcolor(unsigned short color){
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
	return "";
}
void gotoxy(int x, int y) {
    COORD koord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), koord);
}
void tulisTengah(string s, int y) {
    gotoxy(34 - (s.length() / 2), y);
    cout << s;
}
void jeda_ms(int a){
    time_t now = clock();
    while((clock() - now) < a) {};
}
void opening() {
    tulisTengah("JOIN IN GAME", 10);
    jeda_ms(1000);
    tulisTengah("             ", 10);
    tulisTengah("3", 10);
    jeda_ms(1000);
    tulisTengah("2", 10);
    jeda_ms(1000);
    tulisTengah("1", 10);
    jeda_ms(1000);
    tulisTengah(" ", 10);
}

void hasil_jawaban(){
// Atribut untuk Warna
	/* 
	0 = Hitam, 1 = Biru, 2 = Hijau, 3 = Aqua, 
	4 = Merah, 5 = Ungu, 6 = Yellow, 7 = Putih
	8 = Abu-abu, 9 = Biru Cerah, A = Hijau Cerah, 
	B = Aqua Cerah, C = Merah Cerah, D = Ungu Cerah, 
	E = Kuning Cerah, F = Putih Cerah. 
	*/

	HANDLE hstdin  = GetStdHandle( STD_INPUT_HANDLE  );
	HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
	WORD   index   = 0;

	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo( hstdout, &csbi );
// Atribut Untuk Warna - END

for(int i=0; i<digit_angka; i++)
	    		{
	    			if(jawaban[i] == soal[i])
	    			{
	    				// Warnai jadi hijau
	    				SetConsoleTextAttribute(hstdout, 0x9A);
	    				cout << "[" << jawaban[i] << "]";
	    				SetConsoleTextAttribute( hstdout, csbi.wAttributes );
	    				cout << " ";
	    				// Nonaktifkan warna
					}
					else
	    			{
	    				// Warnai jadi hijau
	    				SetConsoleTextAttribute(hstdout, 0x47);
	    				cout << "[X]";
	    				SetConsoleTextAttribute( hstdout, csbi.wAttributes );
	    				cout << " ";
	    				// Nonaktifkan warna
					}
				}
cout<<"\n";
}
void jeda_waktu(int detik){
	// Function delay waktu	
	clock_t endwait;
	endwait=clock()+detik*CLOCKS_PER_SEC;
	while (clock()<endwait);
}
void generate_angka () {
	/* MENGGUNAKAN PRINSIP QUEUE */
	
	// Men-generate angka secara acak
	/* initialize random seed: (ini membuat sisa memori 
	sesi sebelumnya hilang, me-reset lah istilahnya
	kalo enggak, nanti angkanya sama terus)*/
	
	srand (time(NULL));
	// Mendapatkan angka acak dari angka 0 sampai 9
	for(int i=0; i < digit_angka; i++){
		int a = rand()%9+1;
		// Menyimpan ke dalam array soal
		soal[i] = a;
	}
	for(int i=0; i < digit_angka; i++){
	// menampilkan array soal
		cout << "[" << soal[i] << "] ";
	}
}
void tentukan_jumlah_angka(int *level_ptr){
	//Menentukan jumlah angka berdasarkan level
	switch (*level_ptr)
	{
	case 1: digit_angka = 5; // 5 digit
	    break; 
	case 2: digit_angka = 7; // 7 digit
	    break;
	case 3: digit_angka = 10; // 10 digit
	    break;
	case 4: digit_angka = 12; // 10 digit
	    break;
	case 5: digit_angka = 14; // 10 digit
	    break;
	case 6: digit_angka = 16; // 10 digit
	    break;
	case 7: digit_angka = 18; // 10 digit
	    break;
	case 8: digit_angka = 20; // 10 digit
	    break;
	case 9: digit_angka = 22; // 10 digit
	    break;
	case 10: digit_angka = 24; // 10 digit
	    break;
	// jika nilainya 4, maka user menang
	default: digit_angka = 0;
	    break;
	}
}
void terjadi_error(){
	cout<<"PILIHLAH DENGAN BENAR!"<<endl;
	jeda_waktu(1);
	cout<<"Loading .";
	jeda_waktu(1);
	cout<<".";
	jeda_waktu(1);
	cout<<".";
	system("cls");
	
}
void loading_page(){
	setcolor(14);
	cout<<"\nNICE! ";
	setcolor(15);
	cout<<"Bersiap ke stage berikutnya\nLoading .";
	jeda_waktu(1);
	cout<<".";
	jeda_waktu(1);
	cout<<".";
	jeda_waktu(1);
	cout<<".";
	system("cls");
}
void kalah(){
	cout<<"\nLoading .";
	jeda_waktu(1);
	cout<<".";
	jeda_waktu(1);
	cout<<".";
	jeda_waktu(1);
	cout<<".";
	system("cls");	
}
void game_over(){
	
	system("cls");
	setcolor(10);
	cout<<"===================================================================<<\n";
	setcolor(12);
	tulisTengah("GAME OVER!\n\n",2);
	setcolor(15);
	cout<<"===================================================================<<\n";
	cout << "YOUR SCORE IS "<< skor <<endl;
	kalah();
}
void cetak_nyawa(){
	for(int i=0; i<nyawa; i++){
	cout << "+ ";
	}
}
void cetak_level_stage(){
	setcolor(10);cout<<"===================================================================<<";
	setcolor(15);cout<<"\n";
	cout << "STAGE : "<< stages << endl;
	cout << "LEVEL : "<< level << endl;
//	cout << "Jum.angka : "<< digit_angka << endl;
	cout << "NYAWA : "; cetak_nyawa(); cout << "\n";
	cout << "SKOR  : "<< skor << endl << endl;
	cout<<"===================================================================<<\n\n";
}
void hitung_mundur(int *tingkat_kesulitanPtr){
	cout<<"\nHafalkan angka-angka di atas \ndalam "<< *tingkat_kesulitanPtr <<" detik.";
	for(int i=0; i<*tingkat_kesulitanPtr; i++){
		jeda_waktu(1);
		cout<<".";
	}
	system("cls");
	cetak_level_stage();
	
}
void clear_jawaban(){
	for(int i=0; i < digit_angka; i++){
	// menyamadengankan semua elemen array menjadi nol, supaya tidak ada soal [X] yang bocor
		jawaban[i] = 0;
	}
}
void intro(){
		setcolor(10);cout<<">>=================================================================<<\n\n";
		setcolor(15);cout<<"\n                               GAME\n";
		setcolor(15);cout<<"\n                         MENGASAH INGATAN";
		setcolor(10);cout<<"\n                                ...                              \n\n";
		setcolor(8);cout<<"\n                              MADE BY:                            ";
		setcolor(8);cout<<"\n                         Widi Dwi Nurcahyo                        ";
		setcolor(8);cout<<"\n                      Nerinda Ayu Sekar Arum                      ";
		setcolor(11);cout<<"\n\n\n";
		setcolor(15);cout<<"\n                      DUTA BANGSA UNIVERSITY                    \n";
		setcolor(12);cout<<"\n                               2019                             \n\n";
		setcolor(10);cout<<"\n>> Loading...";
		setcolor(15);cout<<"\n\n"; 
		jeda_ms(100);
		setcolor(10);cout<<"||";
		for(int x=0; x<66; x++){
			// nge-print "=" sebanyak 66 kali biar kek loading gitu
			setcolor(10);cout<<"=";
			jeda_ms(60);
		}
		cout<<"||";
		jeda_ms(100);
		setcolor(15);cout<<"\n"; 
		system("cls"); 
}
void animasi_kedip_kedip(){
	for(int c=0; c<3; c++){
		system("cls");
		cetak_level_stage();
		jeda_ms(200);
		hasil_jawaban();
		jeda_ms(200);
	}
}


/* Functions untuk highscore */
void baca_file_highscore(){
	/* MEMBACA FILE DAN MENYIMPANNYA DALAM ARRAY */
	// deklarasi file_skor
    FILE *File_Skor;
    // buka file
    File_Skor = fopen("highscore", "r");
	// Jika file_skor tidak ada, maka error
    if (File_Skor == NULL){
        printf("Error Reading File\n");
        exit (0);
    }
    
    int i = 0;
    
    // Scan terus file nya sampai tidak tersisa/nilainya NULL, lalu scan berhenti.
    do {
        fscanf(File_Skor, "%d,", &ArrayAngkaSkor[i] );
        i++;
        // menentukan size untuk looping "for" di bawah nanti
        size = i-1;
    } while ( ArrayAngkaSkor[i-1] != NULL );
	// tutup file
    fclose(File_Skor);
}
void add_ke_array_skor(){
	// menambahkan elemen ke dalam array
	ArrayAngkaSkor[size] = skor;
	size++;
	/* kenapa di sini digunakan variabel "size" bukan "size-1" untuk 
	menunjuk index skor ... ArrayAngkaSkor[size]...,
	itu karena index array dimulai dari nol, sehingga tidak perlu
	dikurangi satu. */
}
void tampilkan_skor(){
    cout << "\nYOUR HIGHSCORE: " << endl<<endl;
	// menampilkan skor dengan loop
	for (int i = 0; i < size; i++){
        cout << ArrayAngkaSkor_sudah_urut[i] << endl;
    }
}
void tulis_highscore(int a[]) {
  ofstream myfile ("highscore");
  if (myfile.is_open())
  {
    for(int index = 0; index < size; index++){
        myfile << a[index] << "," ;
    }
    myfile.close();
  }
  else cout << "Unable to open file";
}
void urutkan_skor(int *n, int data[]){
	// Menurutkan array menggunakan shell-shorting
	int i,j,jarak,simpan;
	jarak=*n/2;
	while(jarak>0) {
		for(i=jarak;i<*n;i++) {
    	j=i-jarak;
			while(j>=0) {
	     		if(data[j+jarak]>data[j]) {
				 	simpan=data[j+jarak];
	        		data[j+jarak]=data[j];
	        		data[j]=simpan;
   				}
					j=j-jarak;
    		}
 		}
			jarak=jarak/2;
	}
	// menyimpan dalam array yang dideklarasikan di awal tadi
 	for(i=0;i<*n;i++) {
 		ArrayAngkaSkor_sudah_urut[i] = data[i];
	}
}
void update_highscore(){
	// Baca file "highscore" dan update data nya
	baca_file_highscore();
	add_ke_array_skor();
	urutkan_skor(&size, ArrayAngkaSkor);
	tulis_highscore(ArrayAngkaSkor_sudah_urut);
}

int main ()
{
intro();
//opening();
system("cls");

MenuUtama:
while(level <= max_level){
	
	//memanggil fungsi tentukan_jumlah_angka
	tentukan_jumlah_angka(&level);
	// Reset jumlah nyawa setiap kali naik level sebagai hadiah
	nyawa = digit_angka;
	// Menghapus sisa-sisa jawaban biar gak nge-bug (jawabannya udah muncul sendiri gitu)
	clear_jawaban();
	//menentukan pemberhentian level
	while (stages <= max_stages)
	{
		// memunculkan pilihan ketika stage tereset menjadi stages = 1
		if (stages == 1)
		{
			setcolor(10);cout<<"===================================================================<<\n";
			setcolor(15);cout<<"\n";
			cout << "OPSI GAME: \n\n";
			cout << "  1. ADVENTURE\n";
			cout << "  2. PILIH LEVEL \n";
			cout << "  3. CARA MAIN \n";
			cout << "  4. HIGHSCORE \n";
			cout << "  5. EXIT \n";
			cout<<"\nJawab: ";cin >> opsi_user;
			system("cls");
		}
		if (opsi_user == "1")
		{
			goto Permainan;
		}
		else if (opsi_user == "2")
		{
			system("cls");
			setcolor(10);cout<<"===================================================================<<\n";
			setcolor(15);cout<<"\n";
			cout << "PERGI KE LEVEL BERAPA?" << endl<<endl;
			cout << "Jawab: ";
			cin >> level;
			system("cls");
			if(level > max_level){
				setcolor(14);
				tulisTengah("WARNING!\n", 2);
				setcolor(15);
				cout << "\n        LEVEL MAKSIMAL HANYA " << max_level <<"! SILAHKAN PILIH LEVEL LAIN.\n\n\n";
				cout<<"===================================================================<<\n\n";
				system("pause");
				level = NULL;
				system("cls");
				goto MenuUtama;
			}
			tentukan_jumlah_angka(&level);
			// Reset jumlah nyawa setiap kali naik level sebagai hadiah
			nyawa = digit_angka;
			// Reset nilai opsi_user agar gak balik lagi ke pertanyaan
			opsi_user = "1";
			goto Permainan;
		}
		else if (opsi_user == "3")
		{
			setcolor(10);
			cout<<"===============================RULE================================<<\n\n";
			setcolor(15);
			cout << "1. Pilih adventure, jika Anda ingin memainkan permainan\n";
			cout << "   dari level satu hingga level maksimal secara berurutan.\n\n";
			cout << "2. Pilih level, Jika hanya ingin bermain pada level tertentu saja.\n\n";
			cout << "3. Untuk memainkan game, jika waktu menghafal telah selesai\n";
			cout << "   maka kita dapat menginputkan jawaban per angka.\n";
			cout << "   Contoh: Angka >> Enter >> Angka >> Enter dan seterusnya.\n\n";
			cout << "4. Semakin sulit level yang diberikan maka akan semakin banyak\n   digit angka yang harus ditebak.\n\n";
			cout << "5. Jangan menyerah! Ganbatte!! (^_^)\n\n";
			cout<<"===================================================================<<\n\n";
			system("pause");
			system("cls");
			goto MenuUtama;
		}
		
		else if (opsi_user == "4")
		{
			// Baca file "highscore" dan update urutan data-nya
			baca_file_highscore();
			urutkan_skor(&size, ArrayAngkaSkor);
			tulis_highscore(ArrayAngkaSkor_sudah_urut);
			tampilkan_skor();
			cout << "\n\n";
			system("pause");
			system("cls");
			goto MenuUtama;
		}
		else if (opsi_user == "5")
		{
			return 0;
		}
		else {
			terjadi_error();
			goto MenuUtama;
		}
		
		Permainan:
		// mencetak angka berdasarkan level
		cetak_level_stage();
		//Memanggil fungsi generate_angka
		generate_angka();
		cout << "\n";
		// jeda waktu
		hitung_mundur(&tingkat_kesulitan);
	    hasil_jawaban();
		// menerima angka jawaban user
	    for(int i=0; i<digit_angka; i++)
	    {
	    	cout<<"\nJawab: "; cin >> jawaban[i];
	    	if(jawaban[i] == soal[i])
	    	{
	    		skor++;
	    		system("cls");
	    		cetak_level_stage();
	    		hasil_jawaban();
	    		// Cek jumlah nyawa
				if (nyawa<0){
					system("cls");
					setcolor(10);
					cout<<"===================================================================<<\n";
					setcolor(15);
					tulisTengah("GAME OVER!\n\n",2);
					cout<<"===================================================================<<\n";
					cout << "YOUR SCORE IS "<< skor <<endl;
					kalah();
					goto SesiAkhir;
				}
			}
	    	else
	    	{
	    		nyawa--;
	    		system("cls");
	    		cetak_level_stage();
	    		hasil_jawaban();
	    		// Cek jumlah nyawa
				if (nyawa<0){
					game_over();
					goto SesiAkhir;
				}
			}
		}
		//animasi kedip2 ketika berhasil naik ke stage berikutnya
		animasi_kedip_kedip();
		// Untuk me-reset value array agar tidak sama dengan soal
		clear_jawaban();
		// Tambah stage
		stages++;
		
		loading_page();
		system("cls");
		
	};
		// level++ (ditambah satu) untuk menaikkan level
		level++;
		//memanggil fungsi tentukan_jumlah_angka
		tentukan_jumlah_angka(&level);
		nyawa = digit_angka;
		NaikLevel:
		setcolor(10);
		cout<<"===================================================================<<\n";
		setcolor(15);
		// di sini dipakai "level - 1" karena yang ingin ditampilkan adalah level sebelumnya.
		cout << "SELAMAT!\n";
		cout << "ANDA TELAH MEMENANGKAN LEVEL "<< level-1 <<". \n";
		cout << "BERSIAPLAH MENUJU LEVEL "<< level <<" DENGAN "<< nyawa <<" NYAWA. \n\n";
		cout<<"===================================================================<<\n";
		stages = 1;
		cout << "Pilihan: \n";
		cout << "  1. Lanjut \n";
		cout << "  2. Menu Utama \n";
		cout<<"\nJawab: ";cin >> opsi_user;
		if (opsi_user == "1"){
			system("cls");
			// uji nilai level apakah sudah menang
			if(level == max_level+1)
			{
				goto Menang;
			}
			goto Permainan;
		}
		if (opsi_user == "2"){
			system("cls");
			update_highscore();
			goto MenuUtama;
		}
		else {
			system("cls");
			terjadi_error();
			goto NaikLevel;
		}
		system("cls");
		
}
// syarat kemenangan
Menang:
if(level == max_level+1){
	system("cls");
	// reset skor supaya nilainya gak berlanjut
	skor = 0;
	setcolor(10);
	cout<<"===================================================================<<\n\n";
	setcolor(15);
	cout << "               SELAMAT! ANDA MEMENANGKAN GAME INI!\n" << endl;
	cout << "           INGATAN DAN KESABARAN ANDA DI ATAS RATA-RATA!\n\n" << endl;
	cout << "===================================================================<<\n";
	system("pause");
	system("cls");
}

SesiAkhir:
system("cls");
// Reset stage dan level
level = 1;
stages = 1;
// Baca file "highscore" dan update data nya
update_highscore();
// reset skor supaya nilainya gak berlanjut
skor = 0;
// kembali ke menu awal
goto MenuUtama;

return 0;
}

