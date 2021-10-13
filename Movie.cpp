#include "Movie.h"



ostream& operator<<(ostream& out, const Movie& m)
{// operator wyjœcia
	out << "   " << m.id_<< setw(22 ) << m.title_ << setw(25) << m.director_ << setw(25) << m.genre_<< setw(25) << endl;
	return out;
}

void Movie::print() {
	float temp = 1.0 * sumOfClientsReviews_ / counterOfClientsReviews_;
	if (counterOfClientsReviews_ == 0) temp = 0;
	
	cout << "		___________________________________________________________________________________________" << endl << endl;
	cout << "		ID: " << id_  << endl;
	cout << "		Tytu³: " << title_ << endl;
	cout << "		Re¿yser: "  << director_  << endl;
	cout << "		Gatunek: "<< genre_  << endl;
	cout << "		Œrednia ocen filmu: " << temp  << endl;
	cout << "		Liczba ocen filmu: "<< counterOfClientsReviews_ << endl;
	if (currentUser_ != "null") {
		cout << "		Film obecnie wypo¿yczony." << endl;
		cout << "		Przewidywana data zwrotu: " << dateOfDelivery_ << endl;
	}
	else {
		cout << "		Film dostêpny." << endl;
	}
	cout << endl << "		KOMENTARZE: " << endl;

	for (auto i : comments_)
	{
		if (i != "") {
			cout << "		___________________________________________________________________________________" << endl << endl;
			cout << "		" << i << endl;
		}
	}
}
