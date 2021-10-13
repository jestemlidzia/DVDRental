#pragma once
#include <string>


using namespace std;

void init();
void start();
bool login();
//funkcje r�nych menu wywo�ywane w zale�no�ci od miejsca w kt�rym znajduje si� u�ytkownik
//oraz funkcje pomagaj�ce w wy�wietlaniu informacji
void menuClient(); //menu dla klienta
void movieMenuClient();
void clientInfo();
void clientMovieDetail(int index);

void menuAdmin(); //menu dla administratora
void movieMenuAdmin();
void usersListMenu();
void userDetail(string login);
void menuGetMovie();
void menuReturnMovie();
void addUser();
void addMovie();
