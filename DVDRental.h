#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

#include "Account.h"
#include "Movie.h"
#include "Client.h"
#include "Admin.h"

class DVDRental
{
private:
	vector<Account*> users_;
	vector<Movie> movies_;
public:
	DVDRental(){};
	void getUsers(); //wczytuje u�ytkownik�w z plik�w do wektora u�ytkownik�w
	void printUsers(); //wypisuje u�ytkownik�w
	int searchUser(string login); //zwraca miejsce w wektorze, na kt�rym znajduj� si� u�ytkownik o nazwie login
	void getMovies(); //wczytuje u�ytkownik�w z plik�w do wektora u�ytkownik�w
	string getPasswordByIndex(int idx); //zwraca has�o u�ytkownika o indeksie idx
	bool adminCheck(int idx);// zwrca true kiedy u�ytkownik o indeksie idx jest administratorem, w przeciwnym razie zwraca false
	vector<Account*> getUsersArray();//
	void showMovieList(bool admin);//pokazuje list� film�w odpowiednio zmodyfikowan� dla klienta i administratora
	int searchMovie(int id);//zwraca indeks filmu o id id
	void printDetails(int idx);//wy�wietla detale filmu o indeksie id x
	void showClientStatus(string login); //pokazuje wypo�yczone filmy u�ytkownika o loginie login
	void showClientList(); //wy�wietla list� klient�w
	bool showUserDetail(string login); //pokazuje szczeg�y konta o nazwie login
	void updateAdmins(); //uaktualnia plik a dmins. txt
	void updateClients(); //uaktualnia plik users txt
	void updateMovies(); //uaktualnia plik a dmins. txt
	void addUser(string login, string passwd); //dodaje klienta o loginie login i ha�le passwd
	void addAdmin(string login, string passwd); //dodaje administratora o loginie login i ha�le passwd
	void addMovie(string title, string director, string genre); //dodaje film o tytule title i gatunku genre w re�yserii director
	void rentMovie(int idx, string user, string date); //wypo�ycza film o indeksie idx
	void returnMovie(int idx); //zwraca wypo�yczony film o indeksie idx
	void rateMovie(int idx, int value); //dodaje ocen� value do filmu o indeksie idx
	void commentMovie(int idx, string comment); //dodaje komentarz comment do filmu o indeksie idx
};

