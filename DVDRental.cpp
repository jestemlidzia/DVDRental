#include "DVDRental.h"

int adminsCounter, usersCounter;

void DVDRental::getUsers() {
	adminsCounter = 0, usersCounter = 0;
	fstream fileAdmins("admins.txt");
	if (fileAdmins.is_open())
	{
		while (!fileAdmins.eof()) {
			string login;
			string passwd;

			getline(fileAdmins, login, '|');
			getline(fileAdmins, passwd, '\n');

			Admin* admin = new Admin(login, passwd, true);
			users_.push_back(admin);
			adminsCounter++;
			//delete admin;
		}
		fileAdmins.close();
	}

	fstream fileClients("users.txt");
	if (fileClients.is_open())
	{
		while (!fileClients.eof()) {
			string login, passwd;

			getline(fileClients, login, '|');
			getline(fileClients, passwd, '\n');

			Client* client = new Client(login, passwd, false);
			users_.push_back(client);
			usersCounter++;
			//delete client;
		}
		fileClients.close();
	}
}

void DVDRental::getMovies() {
	fstream file("movies.txt");
	if (file.is_open())
	{
		while (!file.eof()) {
			string id, title, director, genre, currentUser, dateOfDelivery, sumOfClientsReviews, counterOfClientsReviews;
			int sumOfClientsReviewsINT, counterOfClientsReviewsINT;
			getline(file, id, '|');
			getline(file, title, '|');
			getline(file, director, '|');
			getline(file, genre, '|');
			getline(file, counterOfClientsReviews, '|');
			getline(file, sumOfClientsReviews, '|');
			getline(file, currentUser, '|');
			getline(file, dateOfDelivery, '|');

			vector<string> comments;
			string temp;
			getline(file, temp, '\n');

			size_t poz1 = 0;
			size_t poz2 = temp.find(";");

			while (poz2 != string::npos) {
				string tmp = temp.substr(poz1, poz2 - poz1);
				comments.push_back(tmp);
				poz1 = poz2 + 1;
				poz2 = temp.find(";", poz2 + 1);
			}

			string tmp = temp.substr(poz1, temp.size() - poz1);
			comments.push_back(tmp);

			istringstream(sumOfClientsReviews) >> sumOfClientsReviewsINT;
			istringstream(counterOfClientsReviews) >> counterOfClientsReviewsINT;

			Movie* movie = new Movie(id, title, director, genre, sumOfClientsReviewsINT, counterOfClientsReviewsINT, comments, currentUser, dateOfDelivery);
			movies_.push_back(*movie);
			delete movie;
		}
		file.close();
	}

}

void DVDRental::printUsers() {
	for (auto i : users_) cout << i;
}

int DVDRental::searchUser(string login) {

	for (int i = 0; i < users_.size(); i++) {
		if (users_[i]->getLogin() == login) return i;
	}
	return -1;
}
vector<Account*> DVDRental::getUsersArray() {
	return users_;
}
string DVDRental::getPasswordByIndex(int idx) {
	return users_[idx]->getPassword();
};

bool DVDRental::adminCheck(int idx) {
	return users_[idx]->getIsItAdmin();
}

void DVDRental::showMovieList(bool admin){
	cout << "___________________________________________________________________________________________" << endl << endl;
	cout << "   ID" << setw(22) << "TYTU£" << setw(25) << "RE¯YSER" << setw(25) << "GATUNEK" << setw(25) << endl;
	cout << "___________________________________________________________________________________________" << endl << endl;
	for (auto i : movies_) {
		cout << i;
		if (admin) {
			if(i.getCurrentUser() != "null") cout << endl << "		NIEDOSTÊPNY. Wypo¿yczony przez u¿ytkownika " << i.getCurrentUser() << endl;
			else cout << endl << "		DOSTÊPNY" << endl;
		}
		cout << "___________________________________________________________________________________________" << endl << endl;
	}
};

int DVDRental::searchMovie(int id){
	string idStr = to_string(id);
	for (int i = 0; i < movies_.size(); i++) {
		if (movies_[i].getId() == idStr) return i;
	}
	return -1;
}

void DVDRental::printDetails(int idx) {

	movies_[idx].print();
	
}

void DVDRental::showClientStatus(string login) {
	int idx = searchUser(login);
	int counterOfMovies = 0;
	users_[idx]->showStatus();

	cout << "___________________________________________________________________________________" << endl << endl;
	cout << "		TWOJE FILMY: " << endl << endl;
	for (int i = 0; i < movies_.size(); i++) {
		if (movies_[i].getCurrentUser() == login) {
			cout << movies_[i] << endl;
			cout << "	Data oddania: " << movies_[i].getDataOfDelivery() << endl;
			cout << "___________________________________________________________________________________" << endl << endl;
			counterOfMovies++;
		};
	}
	
	if (counterOfMovies == 0) cout << endl << "		Obecnie nie posiadasz ¿adnego filmu." << endl;
	else cout << endl <<"		Iloœæ wypo¿ycznych filow: " << counterOfMovies << endl;

}

void DVDRental::showClientList() {
	cout << "		LOGIN" << setw(20) << "		TYP KONTA" << endl; 
	cout << "___________________________________________________________________________________" << endl << endl;
	for (auto i : users_)
	{
		i->print();
	}
};

bool DVDRental::showUserDetail(string login) {
	bool find = false;
	for (auto i : users_) 
	{
		if (i->getLogin() == login) {
			find = true;
			i->showStatus();
			if (i->getIsItAdmin()) cout << "		Administrator." << endl;
			else { 
				cout << endl << "		WYPO¯YCZONE FILMY: " << endl; 
				for (auto i : movies_) {
					if (i.getCurrentUser() == login) {
						cout << i;
						cout << "		Data oddania: " << i.getDataOfDelivery() << endl;
					}
				}
			}
		}
	}
	return find;
}


void DVDRental::updateAdmins()
{
	fstream fout;
	
	fout.open("adminsnew.txt", ios::out);

	int counter = 0;
	for (auto i : users_) {
		if (i->getIsItAdmin()) {
			fout << i->getLogin() << "|" << i->getPassword();
			if(counter != adminsCounter) fout << "\n";
			counter++;
		} 
	}

	fout.close();

	remove("admins.txt");
	rename("adminsnew.txt", "admins.txt");

	users_.clear();
	getUsers();
}

void DVDRental::updateClients() {
	fstream fout;

	fout.open("C:/Users/Lidia/Documents/JPO/usersnew.txt", ios::out);

	int counter = 0;
	for (auto i : users_) {
		if (!(i->getIsItAdmin())) {
			fout << i->getLogin() << "|" << i->getPassword();
			if (counter != usersCounter) fout << "\n";
			counter++;
		} 
	}

	fout.close();

	remove("users.txt");
	rename("usersnew.txt", "users.txt");

	users_.clear();
	getUsers();
}

void DVDRental::updateMovies() {
	fstream fout;
	fout.open("moviesnew.txt", ios::out);

	int counter = 1;
	
	for (auto i : movies_) {
		fout << counter << "|" << i.getTitle() << "|" << i.getDirector() << "|" << i.getGenre() << "|" << i.getCounterOfClientsReviews() << "|" << i.getSumOfClientsReviews() << "|" << i.getCurrentUser() << "|" << i.getDataOfDelivery() << "|";

		int temp = i.getComments().size() - 1;
		int check = 0;
		
			for (auto j : i.getComments()) {
				fout << j;
				if (check != temp) fout << ";";
				check++;
			}
		
		
		if(counter != movies_.size()) fout << "\n";
		counter++;
	}

	fout.close();

	remove("movies.txt");
	rename("moviesnew.txt", "movies.txt");

	movies_.clear();
	getMovies();
}

void DVDRental::addUser(string login, string passwd) {
	Client* client = new Client(login, passwd, false);
	users_.push_back(client);
	updateClients();
	
};
void DVDRental::addAdmin(string login, string passwd) {
	Admin* admin = new Admin(login, passwd, true);
	users_.push_back(admin);
	updateAdmins();
	
};

void DVDRental::addMovie(string title, string director, string genre) {

	string id, currentUser = "null", dateOfDelivery = "null";
	int sumOfClientsReviewsINT = 0, counterOfClientsReviewsINT = 0;
	vector<string> comments;

	id = to_string(movies_.size() + 1);


	Movie* movie = new Movie(id, title, director, genre, sumOfClientsReviewsINT, counterOfClientsReviewsINT, comments, currentUser, dateOfDelivery);
	movies_.push_back(*movie);
	delete movie;

	updateMovies();
}

void DVDRental::rentMovie(int idx, string user, string date) {
	
	movies_[idx].setCurrentUser(user);
	movies_[idx].setDataOfDelivery(date);

	updateMovies();
}

void DVDRental::returnMovie(int idx) {

	movies_[idx].setCurrentUser("null");
	movies_[idx].setDataOfDelivery("null");

	updateMovies();
}

void DVDRental::rateMovie(int idx, int value) {

	movies_[idx].newRate(value);

	updateMovies();
}

void DVDRental::commentMovie(int idx, string comment) {

	movies_[idx].addComment(comment);

	updateMovies();

	for (auto i : movies_[idx].getComments()) {
		cout << i << endl;
	}
}