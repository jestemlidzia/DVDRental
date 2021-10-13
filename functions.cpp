#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
#include "functions.h"
#include "DVDRental.h"
#include "Movie.h"
#include "Account.h"
#include "Client.h"
#include "Admin.h"

#include <cwchar>
#include <windows.h>
#include <iomanip>
#include <stdlib.h>

DVDRental dvd;
string currentUSER = "";
bool isItAdmin;

void init() {

	dvd.getUsers();
	dvd.getMovies();

	start();
}

void start() {
	bool userLogged = false;
	while (!userLogged) {
		userLogged = login();
	}

	if (isItAdmin) menuAdmin();
	else menuClient();
}

bool login() {
	system("cls");
	cout << "___________________________________________________________________________________________" << endl << endl;
	cout << "		Witaj w wypo¿yczalni DVD!" << endl;
	cout << "___________________________________________________________________________________________" << endl << endl;
	cout << "		Aby przegl¹dac filmy zaloguj siê. Jeœli chcesz wyjœæ wybierz 0." << endl << endl;
	string login, passwd;
	cout << "		LOGIN: ";
	cin >> login;

	if (login != "0") {
		cout << "		HASLO: ";
		cin >> passwd;

		int userIndex = dvd.searchUser(login); //nr indeksu na którym znajduje sie user
		if (userIndex == -1) {
			cout << "		Nie ma takiego konta. Mo¿esz za³o¿yæ konto u sprzedawcy." << endl;
			system("pause");
			return false;
		}
		else {
			if (dvd.getPasswordByIndex(userIndex) == passwd) {
				isItAdmin = dvd.adminCheck(userIndex);
				currentUSER = login;
				return true;
			}
			else {
				cout << "		B³êdne has³o. Spróbuj jeszcze raz." << endl;
				system("pause");
				return false;
			}
		}
	}
	else exit(3);

	
}

void menuClient() {
	system("cls");
	cout << "___________________________________________________________________________________________" << endl << endl;
	cout << "		Witaj " << currentUSER << "!" << endl;
	cout << "___________________________________________________________________________________________" << endl << endl;
	cout << "		Co chcesz zrobiæ?" << endl;
	cout << "		1 - Zobacz listê filmów." << endl << "		2 - Poka¿ moje konto." << endl << "		3 - Wyloguj." << endl;

	cout << endl << "		WPISZ WYBRANY NUMER: ";
	int choose;
	cin >> choose;

	switch (choose) {
	case 1:
		movieMenuClient();
		break;
	case 2:
		clientInfo();
		break;
	case 3:
		currentUSER = "";
		isItAdmin = false;
		start();
		break;
	default:
		cout << "		Nie ma takiej opcji." << endl;
		menuClient();
		break;
	}
}

void movieMenuClient() {
	system("cls");
	dvd.showMovieList(isItAdmin);
	cout << endl << "		1 - Aby zobaczyæ szczegó³y filmu wpisz jego ID." << endl << "		0 - Powrót." << endl;
	cout << endl << "		WPISZ WYBRANY NUMER: ";
	int choose;
	cin >> choose;

	switch (choose)
	{
	case 0:
		menuClient();
		break;
	default:
		clientMovieDetail(choose);
		break;
	}
}

void clientMovieDetail(int index) {
	system("cls");
	int idx = dvd.searchMovie(index);
	if (idx == -1) {
		cout << "		Nie ma takiej opcji." << endl;
		movieMenuClient();
	}
	else {
		dvd.printDetails(idx);
	}
	cout << "		___________________________________________________________________________________" << endl << endl;
	cout << endl << "		0 - Powrot." << endl;
	if (!isItAdmin) {
		cout << endl << "		1 - Oceñ." << endl;
		cout << endl << "		2 - Dodaj komentarz." << endl;
	}

	int choose = 0;
	cout << endl << "		WPISZ WYBRANY NUMER: ";
	cin >> choose;

	cin.ignore();
	if (choose == 0) {
		if (isItAdmin) movieMenuAdmin();
		else movieMenuClient();

	}
	else if (choose == 1) {
		int value;
		cout << "Twoja ocena [1-5]: ";
		cin >> value;

		if (value >= 1 && value <= 5) {
			dvd.rateMovie(index - 1, value);
			clientMovieDetail(index);
		}
		else {
			cout << "Niepoprawna wartoœæ. Spróbuj jeszcze raz." << endl;
			system("pause");
			clientMovieDetail(index);
		}
		clientMovieDetail(index);
	}
	else if (choose == 2) {
		string comment;
		cout << "Komentarz: ";
		getline(cin, comment);

		dvd.commentMovie(index - 1, comment);
		clientMovieDetail(index);
	}
	else clientMovieDetail(index);
}

void clientInfo() {
	system("cls");
	cout << "___________________________________________________________________________________________" << endl << endl;
	cout << "		Informacje o Twoim koncie: " << endl;
	dvd.showClientStatus(currentUSER);
	cout << "___________________________________________________________________________________________" << endl << endl;
	cout << "		0 - Powrót." << endl;
	cout << endl << "		WPISZ WYBRANY NUMER: ";
	int choose;
	cin >> choose;
	if (choose == 0) menuClient();
	else clientInfo();
}

void menuAdmin() {
	system("cls");
	cout << "___________________________________________________________________________________________" << endl << endl;
	cout << "		Witaj " << currentUSER << "!" << endl;
	cout << "___________________________________________________________________________________________" << endl << endl;
	cout << "		Co chcesz zrobiæ?" << endl;
	cout << "		1 - Zobacz listê filmów." << endl << "		2 - Poka¿ listê u¿ytkowników." << endl << "		3 - Wypo¿ycz film." << endl << "		4 - Zwróæ film." << endl << "		5 - Utwórz konto." << endl << "		6 - Dodaj film." << endl << "		0 - Wyloguj." << endl;

	cout << endl << "		WPISZ WYBRANY NUMER: ";
	int choose;
	cin >> choose;

	switch (choose) {
	case 0:
		currentUSER = "";
		isItAdmin = false;
		start();
		break;
	case 1:
		movieMenuAdmin();
		break;
	case 2:
		usersListMenu();
		break;

	case 3:
		menuGetMovie();
		break;
	case 4:
		menuReturnMovie();
		break;
	case 5:
		addUser();
		break;
	case 6:
		addMovie();
		break;
	default:
		cout << "		Nie ma takiej opcji." << endl;
		menuClient();
		break;
	}
}

void movieMenuAdmin() {
	system("cls");
	dvd.showMovieList(isItAdmin);
	cout << endl << "		1 - Aby zobaczyæ szczegó³y filmu wpisz jego ID." << endl << "		0 - Powrót." << endl;
	cout << endl << "		WPISZ WYBRANY NUMER: ";
	int choose;
	cin >> choose;

	switch (choose)
	{
	case 0:
		menuAdmin();
		break;
	default:
		clientMovieDetail(choose);
		break;
	}
}

void usersListMenu() {
	system("cls");
	dvd.showClientList();

	cout << endl << "		Jeœli chcesz zobaczyæ szczególy konta podaj login." << endl << "		0 - Powrót." << endl;
	string choose;
	cout << endl << "		WPISZ LOGIN LUB 0: ";
	cin >> choose;

	if (choose == "0") menuAdmin();
	else {
		userDetail(choose);
	}
}

void userDetail(string login) {
	system("cls");
	if (!dvd.showUserDetail(login)) {
		cout << "		Nie ma takiego konta";
		system("pause");
		usersListMenu();
	}
	else {
		cout << endl << "		0 - Powrót." << endl << endl;
		cout << endl << "		WPISZ WYBRANY NUMER: ";
		int choose;
		cin >> choose;
		if (choose == 0) usersListMenu();
		else userDetail(login);
	}
}

void menuGetMovie() {
	system("cls");
	dvd.showMovieList(isItAdmin);
	int id;
	string user, date;
	cout << "		0 - Powrót." << endl << endl;
	cout << "		Id wypo¿yczanego filmu (lub 0): ";
	cin >> id;

	if (id == 0) menuAdmin();

	cout << "		Nazwa wypo¿yczaj¹cego u¿ytkownika: ";
	cin >> user;
	cout << "		Data oddania: [dd-mm-rrrr] ";
	cin >> date;



	int idx = dvd.searchMovie(id);

	if (idx == -1) {
		cout << "		Nie ma filmu o takim id. Spróbuj jeszcze raz." << endl;
		system("pause");
		menuGetMovie();
	}

	int idxUser = dvd.searchUser(user);

	if (idxUser == -1) {
		cout << "		Nie ma takiego u¿ytkownika. Spróbuj jeszcze raz." << endl;
		system("pause");
		menuGetMovie();
	}

	dvd.rentMovie(idx, user, date);
	cout << "		Film zosta³ wypo¿yczony u¿ytkownikowi " << user << "." << endl;
	system("pause");
	menuAdmin();

};

void menuReturnMovie() {
	system("cls");
	dvd.showMovieList(isItAdmin);
	int id;
	cout << "		0 - Powrót." << endl << endl;
	cout << "		Id oddawanego filmu (lub 0): ";
	cin >> id;

	if (id == 0) menuAdmin();

	int idx = dvd.searchMovie(id);

	if (idx == -1) {
		cout << "		Nie ma filmu o takim id. Spróbuj jeszcze raz." << endl;
		system("pause");
		menuReturnMovie();
	}

	dvd.returnMovie(idx);
	cout << "		Film zosta³ oddany." << endl;
	system("pause");
	menuAdmin();
};

void addUser() {
	system("cls");
	string login, passwd, admin;
	cout << "		0 - Powrót." << endl << endl;
	cout << "		Podaj login (lub 0): ";
	cin >> login;

	if (login == "0") menuAdmin();

	int idxUser = dvd.searchUser(login);

	if (idxUser != -1) {
		cout << "		Ta nazwa jest ju¿ zajêta. Spróbuj jeszcze raz." << endl;
		system("pause");
		addUser();
	}

	cout << "		Podaj has³o: ";
	cin >> passwd;
	cout << "		Czy konto ma pe³niæ funkcjê administratora? [TAK/NIE]:";
	cin >> admin;


	if (admin == "TAK") dvd.addAdmin(login, passwd);
	else if (admin == "NIE") dvd.addUser(login, passwd);
	else {
		cout << "		le wpisane dane. Spróbuj jeszcze raz." << endl;
		addUser();
	}

	system("cls");
	cout << "		U¿ytkownik" << login << "zosta³ dodany poprawnie." << endl;
	system("pause");
	menuAdmin();
};
void addMovie() {
	system("cls");
	string title, director, genre;
	cout << "		0 - Powrót." << endl << endl;
	cin.ignore();
	cout << "		Tytu³ (lub 0): ";
	getline(cin, title);

	if (title == "0") menuAdmin();

	cout << "		Re¿yser: ";
	getline(cin, director);
	cout << "		Gatunek: ";
	getline(cin, genre);

	dvd.addMovie(title, director, genre);
	system("cls");
	cout << "		Film zosta³ dodany." << endl;
	system("pause");
	menuAdmin();
};