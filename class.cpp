/****************************************************************************************
* Author: Sheyar Shah
* Last updated: 4-15-14
* Compiler Used: Microsoft Visual Studio 2013 Professional.
* Program Description: Program written in C.
* The program reads in a file which contains linkname and date it was accessed and gives an
* ip address for the person who accessed it. The program allows user to access individual
* sites and date range and see how many time it was accessed and gives unique and returning
* hits for the website. The program also allow user to see the all the websites and gives
* there total hits, returning and unique hits.
*****************************************************************************************/

#include "header.h"

class Websites{
private:
	string ip, site, accessDate;
	int Unique, Returning, TotalHits;

public:
	Websites(){}	//creating default values

	Websites(string ip, string site, string accessDate){ //argument constructor
		setIp(ip);
		setSite(site);
		setAccessDate(accessDate);
	}

	/*Mutator method for ip, site, date*/
	void setIp(string newIP){
		ip = newIP;
	}
	void setSite(string newSite){
		site = newSite;
	}
	void setAccessDate(string newAccessDate){
		accessDate = newAccessDate;
	}

	/*Get method or accessor method for ip, link, date*/
	string getIp(){
		return ip;
	}
	string getSite(){
		return site;
	}
	string getAccessDate(){
		return accessDate;
	}

	/*Mutator method for hits*/
	void setUnique(int newUnique){
		Unique = newUnique;
	}

	void setReturning(int newReturning){
		Returning = newReturning;
	}

	void setTotalHits(int newTotalHits){
		TotalHits = newTotalHits;
	}

	/*get method for hits*/
	int getUnique(){
		return Unique;
	}

	int getReturning(){
		return Returning;
	}

	int getTotalHits(){
		return TotalHits;
	}

};
