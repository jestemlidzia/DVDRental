#pragma once
#include "Account.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>


class Admin : public Account
{
private:
	string login_;
	string password_;
	bool isItAdmin_;
public:
	Admin(string login, string password, bool isItAdmin) : login_(login), password_(password), isItAdmin_(isItAdmin) {};

	//gettery
	string getLogin() { return login_; };
	string getPassword() { return password_; };
	bool getIsItAdmin() { return isItAdmin_; };
	//settery
	void setLogin(string login) { login_ = login; };
	void setPassword(string password) { password_ = password; };

	void showStatus() {
		cout << "		Dane logowania: " << endl;
		cout << "		Login: " << login_ << endl;
		cout << "		Haslo: " << password_ << endl;
	}

	void print() {
		cout << "		" << login_ << setw(20) << "		Administrator" << endl;
	}
};

