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
	void getUsers(); //wczytuje u¿ytkowników z plików do wektora u¿ytkowników
	void printUsers(); //wypisuje u¿ytkowników
	int searchUser(string login); //zwraca miejsce w wektorze, na którym znajdujê siê u¿ytkownik o nazwie login
	void getMovies(); //wczytuje u¿ytkowników z plików do wektora u¿ytkowników
	string getPasswordByIndex(int idx); //zwraca has³o u¿ytkownika o indeksie idx
	bool adminCheck(int idx);// zwrca true kiedy u¿ytkownik o indeksie idx jest administratorem, w przeciwnym razie zwraca false
	vector<Account*> getUsersArray();//
	void showMovieList(bool admin);//pokazuje listê filmów odpowiednio zmodyfikowan¹ dla klienta i administratora
	int searchMovie(int id);//zwraca indeks filmu o id id
	void printDetails(int idx);//wyœwietla detale filmu o indeksie id x
	void showClientStatus(string login); //pokazuje wypo¿yczone filmy u¿ytkownika o loginie login
	void showClientList(); //wyœwietla listê klientów
	bool showUserDetail(string login); //pokazuje szczegó³y konta o nazwie login
	void updateAdmins(); //uaktualnia plik a dmins. txt
	void updateClients(); //uaktualnia plik users txt
	void updateMovies(); //uaktualnia plik a dmins. txt
	void addUser(string login, string passwd); //dodaje klienta o loginie login i haœle passwd
	void addAdmin(string login, string passwd); //dodaje administratora o loginie login i haœle passwd
	void addMovie(string title, string director, string genre); //dodaje film o tytule title i gatunku genre w re¿yserii director
	void rentMovie(int idx, string user, string date); //wypo¿ycza film o indeksie idx
	void returnMovie(int idx); //zwraca wypo¿yczony film o indeksie idx
	void rateMovie(int idx, int value); //dodaje ocenê value do filmu o indeksie idx
	void commentMovie(int idx, string comment); //dodaje komentarz comment do filmu o indeksie idx
};

