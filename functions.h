#pragma once
#include <string>


using namespace std;

void init();
void start();
bool login();
//funkcje ró¿nych menu wywo³ywane w zale¿noœci od miejsca w którym znajduje siê u¿ytkownik
//oraz funkcje pomagaj¹ce w wyœwietlaniu informacji
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
