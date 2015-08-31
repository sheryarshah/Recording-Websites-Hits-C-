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


#define _CRT_SECURE_NO_DEPRECATE		//needed for this specific complier, ignores unnessary warnings

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

#define FILENAME 50					//max character allowed for file name
#define IP_SIZE 14					//total characters in ip address
#define URL_SIZE 60					//max character for URL
#define DATE_SIZE 10				//total characters for date
#define MONTHS_IN_YEAR 13			//months in year and 1 extra for offset
#define MAX_CHARACTERS_PERLINE 150	//max number of characters allowed in a single line
#define MAX_ITEMS 50				//max number of ip, link name, date access allowed

