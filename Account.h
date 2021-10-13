#pragma once
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

class Account
{
private:
	string login_;
	string password_;
	bool isItAdmin_;
public:
	
	//gettery
	virtual string getLogin() = 0;
	virtual string getPassword() = 0;
	virtual bool getIsItAdmin() = 0;
	//settery 
	virtual void setLogin(string login) = 0;
	virtual void setPassword(string password) = 0;

	virtual void print() = 0; //wypisuje typ konta
	virtual void showStatus() = 0; //wypisuje dane logowania
};

