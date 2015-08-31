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
#include "class.cpp"


bool dateFormat(char date[]);											/*checks if the date is in correct format*/
bool dateValidity(char date[]);											/*checks if the dates makes sense according to their month*/
int menu_selection(int selection);										/*gives user the option to choose what he wants*/
string checkUser_DateFormat1(string startDate);							/*checks the date format and also checks the date validity the user has entered for startDate*/
string checkUser_DateFormat2(string finishDate);						/*checks the date format and also checks the date validity the user has entered for finishDate*/
int validate_date_order(string startCheck, string finishCheck);			/*compares the startDate and finishDate user has enetered and checks if its in order*/
int checkingHits(Websites hits[], string link, string ipAddress[], string startDate, string finishDate, int lineCounter);	/*it gives the user the option to check indivual links hits*/
int info_of_all_links(Websites hits[], string startDate, string finishDate, string websites[], int lineCounter);			/*outputs all the links name with their hits*/

int main(){

	FILE *ptr;						/*pointing to a file*/

	char fileName[FILENAME];
	char ip[IP_SIZE];
	char url[URL_SIZE];
	char date[DATE_SIZE];
	char line[MAX_CHARACTERS_PERLINE];

	int line1 = 0, line2 = 0, lineCount = 0, selection = 0, lineCounter = 0;
	int correct = 0;

	cout << "Enter the name of the file : ";
	while (1){
		cin >> fileName;
		if ((ptr = fopen(fileName, "r")) == NULL) {
			cout << "File not found or could'nt be opened, please re-enter: ";
			continue;
		}
		break;
	}

	cout << "Loading " << fileName << ".... \n\n";

	while (fgets(line, MAX_CHARACTERS_PERLINE, ptr) != NULL){			//gets the number of character in single line and copies it and increments line count
		lineCount++;
	}

//	Websites *hits = (Websites *)calloc(lineCount, sizeof(Websites));	//creating an array of objects
	Websites hits[10];

	rewind(ptr);														//returning back to beginning of the file

	while (!feof(ptr)){													//reading file until it reaches end of file
		line1++;
		line2++;
		bool Valid = true;

		correct = fscanf(ptr, "%s %s %s\n", ip, url, date);				//scanning items from file, correct tells there are 3 items; ip, link, date access

		if (correct != 3){
			line1--;
			cout << "\nError reading line " << line1 << "...ignoring entry" << endl;
			line2--;
			Valid = false;
		}
		else if (dateFormat(date) == false){
			cout << "\nFound a record with invalid date format (mm/dd/yyyy) on line " << line2 << "... ignoring entry";
			Valid = false;
		}
		else if (dateValidity(date) == false){
			cout << "\nFound a record with invalid date on line " << line2 << "... ignoring entry";
			Valid = false;
		}

		/*3 objects, ip, site, date and putting into my class*/
		string IP_string(ip);
		string URL_string(url);
		string Date_string(date);

		/*puts the valid lines into class*/
		if (Valid == true){
			hits[lineCounter].setIp(IP_string);
			hits[lineCounter].setSite(URL_string);
			hits[lineCounter].setAccessDate(Date_string);
			lineCounter++;									//valid lines in a file
		}
	}

	while (1){
		selection = menu_selection(selection);
		switch (selection){

		case(1) :
		{
					string linkName, ipAddress[50];
					string startDate;
					string finishDate;

					cout << "Enter a link name: ";
					cin >> linkName;

					startDate = checkUser_DateFormat1(startDate);
					finishDate = checkUser_DateFormat2(finishDate);

					if (validate_date_order(startDate, finishDate) == -1){
						cout << "Dates out of order...please re-enter" << endl;
						startDate = checkUser_DateFormat1(startDate);
						finishDate = checkUser_DateFormat2(finishDate);
					}

					checkingHits(hits, linkName, ipAddress, startDate, finishDate, lineCounter);

					break;
		}

		case(2) :
		{
					string startDate;
					string finishDate;
					string websites[20];

					cout << "\n      Link Name\t          Unique Visits\t  Return Visits\t Total Visits" << endl;
					cout << "--------------------\t  -------------\t  -------------\t ------------" << endl;
					info_of_all_links(hits, startDate, finishDate, websites, lineCounter);

					break;
		}

		case(3) :
		{
					cout << "Program terminated normally...\n";
					getchar();
					getchar();
					exit(0);
					break;
		}

		default:
			cout << "Wrong selection, please re-enter ";
			break;
		}
	}

	fclose(ptr);

	cin.ignore();
	cin.get();

	return 0;
} // end of main



/*
* The function is for case 2. It gives the user all the information for a link name
* with it Unique hits, Returning hits, and total Hits. It outputs it a tabular format.
*/
int info_of_all_links(Websites hits[], string startDate, string finishDate, string websites[], int lineCounter){
	int i, j, counter = 0;

	int totalHits[MAX_ITEMS] = { 0 }, Returning[MAX_ITEMS] = { 0 }, Unique[MAX_ITEMS] = { 0 };	//intilaze the array to zero
	bool siteExists;
	string ipAddress[MAX_ITEMS];

	for (i = 0; i < lineCounter; i++){
		for (j = 0; j < lineCounter; j++){
			if (hits[i].getSite() == websites[j])		//if the site matches the ip address exists
				siteExists = true;
		}
		if (siteExists == false){						//otherwise inc website to check next link in file
			websites[counter] = hits[i].getSite();
			counter++;
		}
		siteExists = false;								//reset site to false
	}



	string IPes[MAX_ITEMS][MAX_ITEMS];
	bool ipExists[MAX_ITEMS];
	int k = 0, z;

	for (z = 0; z < counter; z++){
		for (i = 0; i < lineCounter; i++){
			ipExists[z] = false;
			if (websites[z] == hits[i].getSite()){
				for (j = 0; j < lineCounter; j++){
					if (hits[i].getIp() == IPes[z][j])
						ipExists[z] = true;
				}

				if (ipExists[z] == false){
					IPes[z][k] = hits[i].getIp();
					Unique[z]++;
					k++;
				}
				else Returning[z]++;
			}
		}

		totalHits[z] = Returning[z] + Unique[z];
	}

	/*sorts the information by looking at unique hits in acending order*/
	for (i = 0; i < counter; i++){
		for (j = i + 1; j < counter; j++){
			if (Unique[i]>Unique[j]){
				swap(websites[i], websites[j]);
				swap(Unique[i], Unique[j]);
				swap(Returning[i], Returning[j]);
				swap(totalHits[i], totalHits[j]);
			}
		}
	}
	/*outputting the results for case 2 in tabular format*/
	for (i = 0; i < counter; i++){
		cout << left << setw(32) << websites[i] << "" << setw(10) << Unique[i]
			<< "" << right << setw(7) << Returning[i]
			<< "" << setw(15) << totalHits[i] << "\n";
	}

	return 0;
}

/*
* The function is for case 1. It gives user the option to check the number of hits for
* a specific link, and date the user want to check. It returns the Unique hits, Return hits, and
* total hits.
*/
int checkingHits(Websites hits[], string linkName, string ipAddress[], string startDate, string finishDate, int lineCounter){
	int totalHits = 0, Unique = 0, Returning = 0, i, j, k = 0;
	bool ipExists = true;

	for (i = 0; i < lineCounter; i++){
		if (linkName == hits[i].getSite()){
			if (validate_date_order(startDate, hits[i].getAccessDate()) >= 0 && validate_date_order(finishDate, hits[i].getAccessDate()) <= 0){
				ipExists = true;
				for (j = 0; j < lineCounter; j++){
					if (hits[i].getIp() == ipAddress[j])
						ipExists = false;
				}

				if (ipExists == true){
					ipAddress[k] = hits[i].getIp();
					Unique++;
					k++;
				}
				else Returning++;
			}
		}
	}

	totalHits = Returning + Unique;
	cout << "\nLink: " << linkName << endl;
	cout << "Total Hits: " << totalHits << endl;
	cout << "Unique: " << Unique << endl;
	cout << "Returning: " << Returning << endl;

	return 0;

}

/*
* The function checks the start date format and also checks the start date format the user
* has entered.
*/
string checkUser_DateFormat1(string startDate){


	do{
		cout << "Enter a start date: ";
		cin >> startDate;
		if (dateFormat(const_cast<char *>(startDate.c_str())) == false)
			cout << "Date Format incorrect, enter like this: mm/dd/yyyy\n";
		else if (dateValidity(const_cast<char *>(startDate.c_str())) == false)
			cout << "Date invalid, please re-enter\n";
	} while ((dateFormat(const_cast<char *>(startDate.c_str())) == false) || (dateValidity(const_cast<char *>(startDate.c_str())) == false));

	return startDate;
}

/*
* The function checks the finish date format and also checks the finish date format the user
* has entered.
*/
string checkUser_DateFormat2(string finishDate){

	do{
		cout << "Enter a finish date: ";
		cin >> finishDate;
		if (dateFormat(const_cast<char *>(finishDate.c_str())) == false)
			cout << "Date Format incorrect, enter like this: mm/dd/yyyy\n";
		else if (dateValidity(const_cast<char *>(finishDate.c_str())) == false)
			cout << "Date invalid, please re-enter\n";
	} while ((dateFormat(const_cast<char *>(finishDate.c_str())) == false) || (dateValidity(const_cast<char *>(finishDate.c_str())) == false));


	return finishDate;
}

/*
* The function checks the date order the user has entered and gives user the option
* to re-enter the date if start date is greater than finish date
*/
int validate_date_order(string startCheck, string finishCheck){

	int dateOrder;

	string dateOrder1;
	string dateOrder2;

	strcpy(const_cast<char *>(dateOrder1.c_str()), const_cast<char *>(startCheck.c_str()));
	strcpy(const_cast<char *>(dateOrder2.c_str()), const_cast<char *>(finishCheck.c_str()));

	dateOrder = strcmp(const_cast<char *>(dateOrder1.c_str()), const_cast<char *>(dateOrder2.c_str()));

	if (dateOrder > 0){				//if finishDate is greater than startDate
		return -1;
	}
	else if (dateOrder < 0){		//if startDate is greater than finishDate
		return 1;
	}
	else{
		return 0;					//if equal
	}

}

/*
* The gives user the option to select what choice he wants
*/
int menu_selection(int selection){

	cout << "\n\nPlease select a menu option: \n";
	cout << "1) Link Information in data range\n";
	cout << "2) Information about all links\n";
	cout << "3) Quit the program\n";
	cout << "Option (1,2,3): ";
	cin >> selection;

	return selection;

}

/*
* The function looks if the slashes are in right spot and date is entered like this: 00/00/(14 or 2014)
*/
bool dateFormat(char date[]){
	if (date[2] != '/' || date[5] != '/')			//if backslach is not after month and day, also return false
		return false;
}

/*
* The function checks if the date is valid or not by checking its leap year, and if the date is valid for given a month
*/
bool dateValidity(char date[]){

	int month, dates, year;

	int daysEachMonth[MONTHS_IN_YEAR] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //Janurary.....Decemember

	sscanf(date, "%d/%d/%d", &month, &dates, &year);	//read the string in date and seperate it into month,day,year

	if (dates > 0 && dates <= daysEachMonth[month])		//if number of days increases for given month return false
		return true;

	//checking leap year
	else if (month == 2 && dates == 29 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)))
		return true;

	else
		return false;


}


