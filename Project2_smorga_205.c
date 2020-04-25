//Scott Morgan
//Source file for Project 2


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct Trip_struct{//defines the Trip Structure
	char membershipType[12];
	int startID, endID, bikeID, duration, startHr, startMin;
}Trip;

typedef struct Bike_struct{//defines the bike structure
	char mFlag;
	int bikeID, endStationID, numTrips, totalDuration;
	float totalMinutes;
}Bike;

int compareBikes(const void *x, const void *y);
int compareNumTrips(const void *x, const void *y);
int compareHour(const void *x, const void *y);
int compareDuration(const void *x, const void *y);
int compareDurationTrip(const void *x, const void *y);
int compareStartStations(const void *x, const void *y);
int compareEndStations(const void *x, const void *y);
char getChoice();
void mainMenu();
void metricsMenu();
void printMenu();
int avgTrips(Trip* t, int numLines);
int longestTrip(Trip* t, int numLines);
int busiestHour(Trip* t, int numLines);
char* busiestStartStations(Trip* t, int numLines);
char*  busiestEndStations(Trip* t, int numLines);
char* fiveBusiest(char* s);
char* countTrips(Trip* t, int numLines);
float avgDuration(Trip* t, int numLines);
float percentPerType(Trip* t, int numLines);
int fileOrTerminal();
char* longestDurationBikes(Bike* b);
char* endStationForLongBikes(Bike* b, char* s);
char* highestNumTrips(Bike* b);
int bikesLessThan2(Bike* b);
char* numTripsPerStation(Bike* b);
void ceoReport(Bike* b, Trip* t, int numLines);
void metricsMenuOption(Trip* t, Bike* b, int numLines);
char* printTripData(Trip* t, int numLines);
char* printBikeData(Bike* b);
char* printOneBike(Bike* b);
void printMenuOption(Trip* t, Bike* b, int numLines);
Trip* readFile(int* line);
Bike* getBikes(Trip* Trips, int numLines);
Bike* flagBikes(Bike* b);
Bike* updateBikes(Bike* b);




int compareBikes(const void *x, const void *y){//for sorting trips by bikeID
	Trip *a = (Trip *)x;
	Trip *b = (Trip *)y;
	return (a->bikeID - b->bikeID);
}

int compareNumTrips(const void *x, const void *y){//for sorting bikes by numTrips
	Bike *a = (Bike *)x;
	Bike *b = (Bike *)y;
	return (b->numTrips - a->numTrips);
}
int compareHour(const void *x, const void *y){//for sorting trips by starthr
	Trip *a = (Trip *)x;
	Trip *b = (Trip *)y;	
	return (a->startHr - b->startHr);
}

int compareDuration(const void *x, const void *y){//for sorting bikes by total duration
	Bike *a = (Bike *)x;
	Bike *b = (Bike *)y;
	return (b->totalDuration - a->totalDuration);
}

int compareDurationTrip(const void *x, const void *y){//for sorting trips by duration
	Trip *a = (Trip *)x;
	Trip *b = (Trip *)y;
	return (b->duration - a->duration);
}

int compareStartStations(const void *x, const void *y){//for sorting trips by start station id
	Trip *a = (Trip *)x;
	Trip *b = (Trip *)y;
	return (a->startID - b->startID);
}

int compareEndStations(const void *x, const void *y){//for sorting trips by end station id
	Trip *a = (Trip *)x;
	Trip *b = (Trip *)y;
	return (a->endID - b->endID);
}

char getChoice(){//gets a menu choice
	char a = ' ';
	char buffer[10];
	printf("Please choose an option. \n");
	fgets(buffer, 10, stdin);
	sscanf(buffer, "%c", &a);
	return a;
}

void mainMenu(){//prints the main menu
	printf("\n");
	printf("MAIN MENU\n");
	printf("\tRead trip data ('a')\n");
	printf("\tMetrics Menu ('b')\n");
	printf("\tPrint Menu ('c')\n");
	printf("\tFlag bikes for maintenance ('d')\n");
	printf("\tUpdate bike inventory ('e')\n");
	printf("\tQuit ('q')\n\n");
}

void metricsMenu(){//prints the metrics menu
	printf("\n");
	printf("METRICS MENU\n");
	printf("  TRIP METRICS\n");
	printf("\tAverage number of trips per hour ('a')\n");
	printf("\tHour with largest number of trips ('b')\n");
	printf("\tReport of the count of trips in each hour ('c')\n");
	printf("\tAverage duration of the trips ('d')\n");
	printf("\tTrip with the longest duration ('e')\n");
	printf("\t5 busiest starting stations ('f')\n");
	printf("\t5 busiest ending stations ('g')\n");
	printf("\tPercentage of trips in each membership type ('h')\n");
	printf("  BIKE METRICS\n");
	printf("\t10 bikes with the longest duration in minutes ('i')\n");
	printf("\tEnd stations for bikes with the longest duration in minutes ('j')\n");
	printf("\t10 bikes with the most trips ('k')\n");
	printf("\tCount of bikes used for 2 or less trips ('l')\n");
	printf("\tThe start station IDs number of trips for bikes with less than 2 trips ('m')");
	printf("\tReturn to Main Menu ('q')\n\n");
}

int avgTrips(Trip* t, int numLines){//gets the average number of trips
	double x = numLines/24;
	x += 0.5;
	int y = (int)x;
	return y; 
}

int longestTrip(Trip* t, int numLines){//gets the longest trip
	qsort(t, numLines, sizeof(Trip), compareDurationTrip);
	return t[0].duration;
}

int busiestHour(Trip* t, int numLines){//gets the busiest hour
	qsort(t, numLines, sizeof(Trip), compareHour);
	int i;
	int max = 0;
	int temp = 0;
	int h = -1;
	int current = t[0].startHr;
	for(i = 0; i < numLines; i++){
		if(current == t[i].startHr){
			temp++;
		}
		else{//when the id changes, reset temp and check it against max
			current = t[i].startHr;
			if(temp > max){
				max = temp;
				h = t[i-1].startHr;
			}
			temp = 1;
		}
		
	}
	return h;
}

char* busiestStartStations(Trip* t, int numLines){//puts the start stations in order and then returns the count of each one in a String
	qsort(t, numLines, sizeof(Trip), compareStartStations);
	int i;
	int temp = 0;
	char *ans = (char *)malloc(sizeof(Trip)*1000);
	char app[50];
	int current = t[0].startID;
	for(i = 0; i < numLines; i++){
		if(current == t[i].startID){
			temp++;
		}
		else{
			strcpy(app, "");
			sprintf(app, "%d %d\n", current, temp);
			strcat(ans, app);
			current = t[i].startID;
			temp = 1;
		}
	}

return ans;
}

char* busiestEndStations(Trip* t, int numLines){//puts the end stations in order and then returns the count of each one in a string
	qsort(t, numLines, sizeof(Trip), compareEndStations);
	int i;
	int temp = 0;
	char *ans = (char *)malloc(sizeof(Trip)*1000);
	char app[50];
	int current = t[0].endID;
	for(i = 0; i < numLines; i++){
		if(current == t[i].endID){
			temp++;
		}
		else{
			strcpy(app, "");
			sprintf(app, "%d %d\n", current, temp);
			strcat(ans, app);
			current = t[i].endID;
			temp = 1;
		}
	}

return ans;
}

char* fiveBusiest(char* s){//takes a string from one of the busiest methods and returns a string that has to 5 busiest
	int ID;
	int count;
	int temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0;
	int max1 = 0, max2 = 0, max3 = 0, max4 = 0, max5 = 0;
	int ID1= 0, ID2 = 0, ID3 = 0, ID4 = 0, ID5 = 0;
	int iTemp1 = 0, iTemp2 = 0, iTemp3 = 0, iTemp4 = 0;
	char* ans = (char *)malloc(sizeof(Trip)*100);
	char* token = strtok(s, "\n");
	while(token != NULL){
		sscanf(token, "%d %d", &ID, &count);
		if(count > max1){//have to bump all of the other ones down
			temp1 = max1;
			temp2 = max2;
			temp3 = max3;
			temp4 = max4;
			max1 = count;
			max2 = temp1;
			max3 = temp2;
			max4 = temp3;
			max5 = temp4;
			iTemp1 = ID1;
			iTemp2 = ID2;
			iTemp3 = ID3;
			iTemp4 = ID4;
			ID1 = ID;//keeps track of ids, this stays consistent for all else if statemnets
			ID2 = iTemp1;
			ID3 = iTemp2;
			ID4 = iTemp3;
			ID5 = iTemp4;
		}
		else if(count > max2){
			temp2 = max2;
			temp3 = max3;
			temp4 = max4;
			max2 = count;
			max3 = temp2;
			max4 = temp3;
			max5 = temp4;
			iTemp2 = ID2;
			iTemp3 = ID3;
			iTemp4 = ID4;
			ID2 = ID;
			ID3 = iTemp2;
			ID4 = iTemp3;
			ID5 = iTemp4;
		}
		else if(count > max3){
			temp3 = max3;
			temp4 = max4;
			max3 = count;
			max4 = temp3;
			max5 = temp4;
			iTemp3 = ID3;
			iTemp4 = ID4;
			ID3 = ID;
			ID4 = iTemp3;
			ID5 = iTemp4;
		}
		else if(count > max4){
			temp4 = max4;
			max4 = count;
			max5 = temp4;
			iTemp4 = ID4;
			ID4 = ID;
			ID5 = iTemp4;
		}
		else if(count > max5){
			max5 = count;
			ID5 = ID;
		}
		token = strtok(NULL, "\n");
	}
	strcpy(ans, "");
	sprintf(ans, "%d\t%d \n%d\t%d \n%d\t%d \n%d\t%d \n%d\t%d", ID1, max1, ID2, max2, ID3, max3, ID4, max4, ID5, max5);
return ans;
}
char* countTrips(Trip* t, int numLines){//counts the number of trips by each start hr
	qsort(t, numLines, sizeof(Trip), compareHour);
	int i;
	int temp = 0;
	char *ans = (char *)malloc(sizeof(char)*750);
	char app[50];
	int current = t[0].startHr;
	strcpy(ans, "");
	for(i = 0; i <= numLines; i++){
		if(current == t[i].startHr){
			temp++;
		}
		else{
			sprintf(app, "%d: %d\n", current, temp);
			strcat(ans, app);
			current++;
			temp = 1;
		}
		
	}
return ans;
}

float avgDuration(Trip* t, int numLines){//average duration of a trip
	int i;
	double sum = 0;
	float lines = (float)numLines;
	for(i = 0; i < numLines; i++){
		sum += t[i].duration;
	}
	return (sum/lines);
}
float percentPerType(Trip* t, int numLines){//%of casual and %of Registered
	int i;
	int rCount = 0;
	float lines = (float)numLines;
	for(i = 0; i < numLines; i++){
		if(strcmp(t[i].membershipType, "Registered\0")){
			rCount++;
		}
	}
	float ans = (((float)(rCount))/lines);
	return ans;
}
int fileOrTerminal(){//asks the user if they would like to print to the terminal or the file
	int boo = 0;
	char write;
	printf("Would you like to print to the terminal ('a') or print to a file ('b')?\n");
	write = getChoice();
	if(write == 'b'){
		boo = 1;
	}
	return boo;
}

char* longestDurationBikes(Bike* b){//gets the 10 bikes with the longest durations
	qsort(b, 4000, sizeof(Bike), compareDuration);
	int i = 0;
	char* ans = (char *)malloc(sizeof(Bike)*10);
	char app[50];
	float x;
	strcpy(ans, "");
	strcpy(app, "");
	for(i = 0; i < 10; i++){
		x = b[i].totalDuration/60000;
		sprintf(app, "%d\t%.2f\n", b[i].bikeID, x);
		strcat(ans, app);
	}
return ans;
}

char* endStationforLongBikes(Bike* b, char* s){//gets the end station for the bikes with the longest durations
	int ID;
	float x;
	int i;
	char* ans = (char *)malloc(sizeof(Bike)*100);
	char app[50];
	strcpy(ans, "End station IDs for the bikes with the longest durations:\nBikeID\tEnd Station ID\n");
	char* token = strtok(s, "\n");
	while(token != NULL){
		sscanf(token, "%d %f", &ID, &x);
		for(i = 0; i < 4000; i++){
			if(b[i].bikeID == ID){
				sprintf(app, "%d\t%d\n", b[i].bikeID, b[i].endStationID);
				strcat(ans, app);
			}
		}
		token = strtok(NULL, "\n");
	}
return ans;
}

char* highestNumTrips(Bike* b){//returns the bikes with the highest number of trips
	qsort(b, 4000, sizeof(Bike), compareNumTrips);
	int i = 0;
	char* ans = (char *)malloc(sizeof(Bike)*10);
	char app[50];
	strcpy(ans, "The 10 bikes with highest number of trips are:\nBikeID\tNumTrips\n");
	strcpy(app, "");
	for(i = 0; i < 10; i++){
		sprintf(app, "%d\t%d\n", b[i].bikeID, b[i].numTrips);
		strcat(ans, app);
	}
return ans;
}
	
int bikesLessThan2(Bike* b){//returns how many bikes with less than 2 trips
	int i = 0;
	int count = 0;
	for(i = 0; i < 4000; i++){
		if(b[i].numTrips <= 2 && b[i].numTrips > 0){
			count++;
		}
	}
	return count;
}

char* numTripsPerStation(Bike* b){//returns the number of trips per start station for bikes with less than 2 trips
	int i = 0;
	char app[50];
	char* ans = (char *)malloc(sizeof(Bike) * 200);
	strcpy(ans,"The start station IDs number of trips for bikes with less than 2 trips\nStationID\tNumTrips");
	for(i = 0; i < 10; i++){
		if(b[i].numTrips <= 2 && b[i].numTrips != 0){
			sprintf(app, "%d\t%d\n", b[i].endStationID, b[i].numTrips);
			strcat(ans, app);
		}
	}
return ans;
}
	
void ceoReport(Bike* b, Trip* t, int numLines){//prints out the CEO Report to a file called "CEOReport.txt"
	FILE* file;
	file = fopen("CEOReport.txt", "w");
	double x;
	fprintf(file,"%d trips per hour on average.\n\n", avgTrips(t, numLines));
	fprintf(file, "Busiest hour: %d\n\n", busiestHour(t, numLines));
	fprintf(file, "Count of trips for each hour:\nHour NumTrips\n%s\n", countTrips(t, numLines));
	x = avgDuration(t, numLines);
	fprintf(file, "Average duration of a trip in\nMilliseconds: %.2f\tMinutes: %.2f\n\n", x, x/60000);
	x = longestTrip(t, numLines);
	fprintf(file, "Longest single trip duration in\nMilliseconds: %.0f\tMinutes: %.2f\n\n", x, x/60000);
	fprintf(file, "Five busiest starting stations\nID   \tNumber of Trips\n%s\n\n", fiveBusiest(busiestStartStations(t, numLines)));
	fprintf(file, "Five busiest ending stations\nID   \tNumber of Trips\n%s\n\n", fiveBusiest(busiestEndStations(t, numLines)));
	fprintf(file, "Percentages for membership types\nCasual: %.2f\t Registered: %.2f\n\n",100*(1- percentPerType(t, numLines)), (100*percentPerType(t, numLines)));
	fprintf(file, "The 10 bikes with the longest total durations are:\nBikeID\tDuration\n%s\n\n", longestDurationBikes(b));
	fprintf(file, "%s\n\n", endStationforLongBikes(b, longestDurationBikes(b)));
	fprintf(file, "%s\n\n", highestNumTrips(b));
	fprintf(file, "There are %d bikes with 2 or less trips\n\n", bikesLessThan2(b));
	fprintf(file, "%s\n\n", numTripsPerStation(b));
	fclose(file);
}

void metricsMenuOption(Trip* t, Bike* b, int numLines){//for running the metrics menu
	char z;
	FILE* file;
	file = fopen("out.txt", "w");
	double x;
	int boo = fileOrTerminal();
	metricsMenu();
	z = getChoice();
	switch(z){
		case 'a'://case for each option in the menu, condensed conditional statements for organizational purpose
			if(boo == 0){printf("%d trips per hour on average.\n\n", avgTrips(t, numLines));}
			else{fprintf(file,"%d trips per hour on average.\n\n", avgTrips(t, numLines));}
			break;
		case 'b':
			if(boo == 0){printf("Busiest hour: %d\n\n", busiestHour(t, numLines));}
			else{fprintf(file, "Busiest hour: %d\n\n", busiestHour(t, numLines));}
			break;
		case 'c':
			if(boo == 0){printf("Count of trips for each hour:\nHour NumTrips\n%s\n", countTrips(t, numLines));}
			else{fprintf(file, "Count of trips for each hour:\nHour NumTrips\n%s\n", countTrips(t, numLines));}
			break;
		case 'd':
			x = avgDuration(t, numLines);
			if(boo == 0){printf("Average duration of a trip in\nMilliseconds: %.2f\tMinutes: %.2f\n\n", x, x/60000);}
			else{fprintf(file, "Average duration of a trip in\nMilliseconds: %.2f\tMinutes: %.2f\n\n", x, x/60000);}
			break;
		case 'e':
			x = longestTrip(t, numLines);
			if(boo == 0){printf("Longest single trip duration in\nMilliseconds: %.0f\tMinutes: %.2f\n\n", x, x/60000);}
			else{fprintf(file, "Average duration of a trip in\nMilliseconds: %.2f\tMinutes: %.2f\n\n", x, x/60000);}
			break;
		case 'f':
			if(boo == 0){printf("Five busiest starting stations\nID\tNumber of Trips\n%s\n\n", fiveBusiest(busiestStartStations(t, numLines)));}
			else{fprintf(file, "Five busiest starting stations\nID\tNumber of Trips\n%s\n\n", fiveBusiest(busiestStartStations(t, numLines)));}
			break;
		case 'g':
			if(boo == 0){printf("Five busiest ending stations\nID\tNumber of Trips\n%s\n\n", fiveBusiest(busiestEndStations(t, numLines)));}
			else{fprintf(file, "Five busiest ending stations\nID\tNumber of Trips\n%s\n\n", fiveBusiest(busiestEndStations(t, numLines)));}
			break;
		case 'h':
			if(boo == 0){printf("Percentages for membership types\nCasual: %.2f\t Registered: %.2f\n\n",100*(1- percentPerType(t, numLines)), (100*percentPerType(t, numLines)));}
			else{fprintf(file, "Percentages for membership types\nCasual: %.2f\t Registered: %.2f\n\n",100*(1- percentPerType(t, numLines)), (100*percentPerType(t, numLines)));}
			break;
		case 'i':
			if(boo == 0){printf("The 10 bikes with the longest total durations are:\nBikeID\tDuration\n%s\n\n", longestDurationBikes(b));}
			else{fprintf(file, "The 10 bikes with the longest total durations are:\nBikeID\tDuration\n%s\n\n", longestDurationBikes(b));}
			break;
		case 'j':
			if(boo == 0){printf("%s\n\n", endStationforLongBikes(b, longestDurationBikes(b)));}
			else{fprintf(file, "%s\n\n", endStationforLongBikes(b, longestDurationBikes(b)));}
			break;
		case 'k':
			if(boo == 0){printf("%s\n\n", highestNumTrips(b));}
			else{fprintf(file, "%s\n\n", highestNumTrips(b));}
			break;
		case 'l':
			if(boo == 0){printf("There are %d bikes with 2 or less trips\n\n", bikesLessThan2(b));}
			else{fprintf(file, "There are %d bikes with 2 or less trips\n\n", bikesLessThan2(b));}
			break;
		case 'm':
			if(boo == 0){printf("%s\n\n", numTripsPerStation(b));}
			else{fprintf(file, "%s\n\n", numTripsPerStation(b));}
			break;
		case 'q':
			break;
		default:
			printf("Please enter one of the menu choices");
			metricsMenu();
			break;
	}
}


void printMenu(){//prints out the print menu
	printf("\n");
	printf("PRINT MENU\n");
	printf("\tPrint all trip data ('a')\n");
	printf("\tPrint all bike inventory ('b')\n");
	printf("\tPrint CEO report *only prints to a file* ('c')\n");
	printf("\tPrint a bike ('d')\n");
	printf("\tReturn to Main Menu ('q')\n\n");
	
}

char* printTripData(Trip* t, int numLines){//prints all of the trip data
	char *ans = (char *)malloc(numLines * sizeof(Trip) * 2);
	char* app = (char *)malloc(sizeof(Trip)*sizeof(char) * 2);
	strcpy(ans, "");
	int i = 0;
	for(i = 0; i < numLines; i++){
		sprintf(app, "%s %d %d %d %d %d %d\n", t[i].membershipType, t[i].startID, t[i].endID, t[i].bikeID, t[i].duration, t[i].startHr, t[i].startMin);
		strcat(ans, app);
	}
	printf("%s\n", ans);
	free(app);
	return ans;
}

char* printBikeData(Bike* b){//prints all of the bike data
	int i;
	Bike* c = malloc(sizeof(Bike)*4000);
	c = b;
	char* ans = (char *)malloc(sizeof(Bike)*4000);
	char* app = (char *)malloc(sizeof(Bike));
	strcpy(ans, "");
	for(i = 0; i < 4000; i++){
		sprintf(app, "%d %d %d %d %.2f %c\n",c[i].bikeID, c[i].endStationID, c[i].numTrips, c[i].totalDuration, c[i].totalMinutes, c[i].mFlag);
		strcat(ans, app);
	}
	free(c);
	return ans;
}
char* printOneBike(Bike* b){//prints a bike based on the id that the user enters
	int i = 0;
	int ID;
	
	char* ans = (char *)malloc(sizeof(Bike));
	char* app = (char *)malloc(sizeof(Bike));
	strcpy(ans, "");
	Bike* c = malloc(sizeof(Bike)*4000);
	c = b;
	int x = 0;
	char inbuf[25];
	printf("What is the ID of the bike to remove?\n");
	fgets(inbuf, 25, stdin);
	sscanf(inbuf, "%d", &ID);
	for(i = 0; i < 4000; i++){
		if(ID == c[i].bikeID){
			x = 1;
			sprintf(app, "%d %d %d %d %.2f %c\n",c[i].bikeID, c[i].endStationID, c[i].numTrips, c[i].totalDuration, c[i].totalMinutes, c[i].mFlag);
			strcat(ans, app);
		}
	}
	if(x == 0){
		sprintf(app, "Bike %d does not exist.\n", ID);
		strcat(ans, app);
	}
	free(c);
	return ans;
}

void printMenuOption(Trip* t, Bike* b, int numLines){//for running the print menu
	char z;
	int boo = fileOrTerminal();
	FILE* file;

	file = fopen("out.txt", "w");
	printMenu();
	z = getChoice();
	switch(z){
		case 'a'://case for all the menu options of the print menu
			if(boo == 0){
				printf("%s\n", printTripData(t, numLines));
			}
			else{
				fprintf(file,"%s\n", printTripData(t, numLines));
			}
			break;
		case 'b':
			if(boo == 0){
				printf("%s\n", printBikeData(b));
			}
			else{
				fprintf(file,"%s\n", printBikeData(b));
			}
			break;
		case 'c':
			ceoReport(b, t,  numLines);
			break;
		case 'd':
			if(boo == 0){
				printf("%s\n", printOneBike(b));
			}
			else{
				fprintf(file,"%s\n", printOneBike(b));
			}
			break;
		case 'q':
			break;
		default:
			printf("Please enter one of the menu choices");
			printMenu();
			break;
	}
	fclose(file);
}

Trip* readFile(int* line){//reads the input file and puts it into an array of Trips
	char buf[100];
	char fileName[100];
	FILE *file;
	int numLines;	

	printf("Please enter the filename\n");
	fgets(buf, 100, stdin);
	sscanf(buf, "%s", fileName);	
	if((file = fopen(fileName, "r"))==NULL){
		printf("Error opening file\n");
		return  NULL;
	}
	fscanf(file, "%d", &numLines);
	Trip *Trips = (Trip *)malloc(numLines*sizeof(Trip));
	int i = 0;
	
	while(i < numLines){
		fscanf(file, "%s %d %d %d %d %d %d", Trips[i].membershipType, &Trips[i].startID, &Trips[i].endID, &Trips[i].bikeID, &Trips[i].duration, &Trips[i].startHr, &Trips[i].startMin);
		i++;
	}
	*line = numLines;//also allows us to get the number of lines in the file so we can use that in other methods 
	fclose(file);
	return Trips;
}

Bike* getBikes(Trip* Trips, int numLines){//initializes the array of bikes from the array of trips
	qsort(Trips, numLines, sizeof(Trip), compareBikes);
	int i;
	int current = -1;
	int bikeIndex = 0;
	i = 0;
	Bike *Bikes = (Bike *)malloc(sizeof(Bike)*4000);
	for(i = 0; i <= numLines; i++){//sorted by bike id
		float k = (Trips[i].startHr*60) + Trips[i].startMin + (Trips[i].duration/60000);
		float r = (Trips[i-1].startHr*60) + Trips[i-1].startMin + (Trips[i-1].duration/60000);
		if(current == Trips[i].bikeID){
			Bikes[bikeIndex].totalDuration += Trips[i].duration;
			Bikes[bikeIndex].numTrips++;
			Bikes[bikeIndex].totalMinutes += Trips[i].duration/60000;
			if(k > r){
				Bikes[bikeIndex].endStationID = Trips[i].endID;
			}
		}
		else{//this is now a new bike
			current = Trips[i].bikeID;
			bikeIndex++;
			Bikes[bikeIndex].bikeID = Trips[i].bikeID;
			Bikes[bikeIndex].numTrips = 1;
			Bikes[bikeIndex].totalDuration = Trips[i].duration;
			Bikes[bikeIndex].endStationID = Trips[i].endID;
			Bikes[bikeIndex].mFlag = '0';
			Bikes[bikeIndex].totalMinutes = Trips[i].duration/60000;
		}
	}
return Bikes;
}

Bike* flagBikes(Bike* b){//flags the 10 bikes with the highest totalDuration
	qsort(b, 4000, sizeof(Bike), compareDuration);
	int i = 0;
	printf("\nThe bike IDs that have been flagged for maintenance are: \n");
	for(i = 0; i < 10; i++){
		b[i].mFlag = 1;
		printf("Bike %d\tTotal Duration (in minutes): %d\n", b[i].bikeID, b[i].totalDuration/60000);
	}
	printf("The 10 bikes with the longest duration have been flagged for maintenance\n");
	return b;
}

Bike* updateBikes(Bike* b){//removes and then adds a bike to the bikes array
	int i = 0;
	int ID;
	int x = 0;
	int newID;
	int endID;
	char buffer[25];
	char inbuf[25];
	printf("What is the ID of the bike to remove?\n");
	fgets(inbuf, 25, stdin);
	sscanf(inbuf, "%d", &ID);
	for(i = 0; i < 4000; i++){
		if(ID == b[i].bikeID){
			x = 1;
			endID = b[i].endStationID;
			printf("Removed Bike %d\n",ID);
			printf("What is the ID of the bike to be added?\n");
			fgets(buffer, 25, stdin);
			sscanf(buffer, "%d", &newID);			
			b[i].bikeID = newID;
			b[i].endStationID = endID;
			b[i].totalDuration = 0;
			b[i].mFlag = 0;
			b[i].numTrips = 0;
			b[i].totalMinutes = 0;
		}
	}
	if(x == 0){
		printf("Bike %d does not exist.\n", ID);
	}
	return b;
}

int main(){
	char ans;	
	int boolean = 0;
	Trip *Trips;
	Bike *Bikes = (Bike*)malloc(sizeof(Bike)*4000);
	int line = 0;
	int numLines = 0;
	while(ans != 'q'){
		mainMenu();
		ans = getChoice();
		switch(ans){
			case 'a'://case for each option of the main menu
				Trips = readFile(&line);
				numLines =(uintptr_t)line;
				if(Trips != NULL){
					boolean = 1;
					Bikes = getBikes(Trips, numLines);
				}
				break;
			case 'b':
				if(boolean == 0){
					printf("No file has been read with Trip data yet\n");
					break;
				}
				metricsMenuOption(Trips, Bikes, numLines);
				break;
			case 'c':
				if(boolean == 0){
					printf("No file has been read with Trip data yet\n");
					break;
				}
				printMenuOption(Trips, Bikes, numLines);
				break;
			case 'd':
				if(boolean == 0){
					printf("No file has been read with Trip data yet\n");
					break;
				}
				Bikes = flagBikes(Bikes);
				break;
			case 'e':
				if(boolean == 0){
					printf("No file has been read with Trip data yet\n");
					break;
				}
				Bikes = updateBikes(Bikes);
				break;
			case 'q':
				break;
			default:
				if(boolean == 0){
					break;
				}
				printf("Please enter one of the menu choices");
				break;
		}

	}
	
	return 1;
}
