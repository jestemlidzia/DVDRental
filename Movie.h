#pragma once
#include <string>
#include <iostream>
#include<vector>
#include <iomanip>
#include "Movie.h"
using namespace std;

class Movie
{
private:
	string id_;
	string title_;
	string director_;
	string genre_;
	int sumOfClientsReviews_;
	int counterOfClientsReviews_;
	vector<string> comments_;
	string currentUser_;
	string dateOfDelivery_;

public:
	Movie() {};
	Movie(string id, string title, string director, string genre, int sumOfClientsReviews, int counterOfClientsReviews, vector<string> comments, string currentUser, string dateOfDelivery) :
		id_(id), title_(title), director_(director), genre_(genre), sumOfClientsReviews_(sumOfClientsReviews), counterOfClientsReviews_(counterOfClientsReviews), comments_(comments), currentUser_(currentUser), dateOfDelivery_(dateOfDelivery) {};
	//getters
	string getId() { return id_; }
	string getTitle() { return title_; }
	string getDirector() { return director_; }
	string getGenre() { return genre_; }
	int getSumOfClientsReviews() { return sumOfClientsReviews_; };
	vector<string> getComments() { return comments_; };
	int getCounterOfClientsReviews() { return counterOfClientsReviews_; };
	string getCurrentUser() { return currentUser_; };
	string getDataOfDelivery() { return dateOfDelivery_; };
	//setters
	void setId(string id) { id_ = id; }
	void setTitle(string title) { title_ = title; }
	void setDirector(string director) { director_ = director; }
	void setGenre(string genre) { genre_ = genre; }
	void setSumOfClientsReviews( int sumOfClientsReviews) { sumOfClientsReviews_ = sumOfClientsReviews; };
	void setCounterOfClientsReviews(int counterOfClientsReviews) {counterOfClientsReviews_= counterOfClientsReviews; };
	
	void addComment(string comment) { comments_.push_back(comment); } //dodaje komentarz comment do filmu.
	void setCurrentUser(string currentUser) { currentUser_ = currentUser; };
	void setDataOfDelivery(string dateOfDelivery) {dateOfDelivery_ = dateOfDelivery; };
	void newRate(int value) { counterOfClientsReviews_++; sumOfClientsReviews_ += value; }; //dodaje ocene

	friend ostream& operator<<(ostream&, const Movie&);
	void print(); 
	
};

