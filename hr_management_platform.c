/*****************************************************************************
* FILE NAME: hr_management_platform.c *
* *
* PURPOSE: Human Resource Management Platform *
* *
* EXTERNAL VARIABLES: *
* Name Type I/O Description *
* ___________ ______ ____ _______________ *
* *
* CONSTRAINTS & RESTRICTIONS: *
* *
* NOTES: *
* *
* DEVELOPMENT HISTORY: *
* *
* Date Author Release No Description Of Change *
* _______ _________ _____________ __________________________ *
* 12/7/2020 Taywan Ham *
*****************************************************************************/

#include <stdio.h>
#include <windows.h> // header file for system function
#include <stdbool.h> // header file for boolean 
#include <string.h> // header file for strcpy, strcmp, strtok function
#include <stdlib.h> // header file for qsort, atoi function
#define _CRT_SECURE_NO_WARNINGS // prevent compile error due to strtok function
#pragma warning(disable: 4996) // to use scanf() function for input
#define INIT 22 // number of personnels in orginal employee.txt

//structure
struct personnel_info {
	int num;
	int id;
	char name[10];
	char sex[3];
	char birth[11];
	char sector[10];
	char level[10];
	int years;
	char salary[10];
};
struct personnel_info p[101]; // create struct array

//variables
int i, j, pi; //i, j: index, pi: present index
bool loop; //bool variable for while 

//functions
void login(); // verify authorization
void option(char input_key); // option select function
void print(); // print all result (function)
void print_personnel(int index); // print specific personnel's info (function)
char find_option(); // get option from user
bool check_overlap(char* option, char* name, int id); // check if personnel already exists in the table
void r(); // read "emplyee.txt" function
void a(); // add function
void d(); // delete function
void f(); // find function
void g(); // replace sector and level (function)
void i_function(); // replace years or salary (function)
void p_function(); // print personnel info table in certain classification
void s(); // sort personnel info
int cmp_birth(const void* A, const void* B); // birth compare function for qsort()
int cmp_level(const void* A, const void* B); // level compare function for qsort()
int cmp_years(const void* A, const void* B); // years compare function for qsort()
char* comma_remover(char* str); // removes "," from string
int cmp_salary(const void* A, const void* B); //salary compare function for qsort()
void w(); // save info in to "emplyee_new.txt"


int main(void) {
	pi = INIT; // initialize present index with INIT
	char input_key;

	// verify authorization
	loop = true;
	login();

	// employee data management operation
	loop = true;
	while (loop) {
		printf("===================================================================================================\n");
		printf("Choose one of the options (r,a,d,f,g,i,p,s,w,q) : ");
		scanf("%c", &input_key); // get option from user
		getchar(); // clear input buffer
		option(input_key); //execute appropriate function(r, a, d, ...)
		print(); // print all personnel info in a table
	}
	return 0;
}

void login() {
	char username[20];
	// print corporate logo in ascii art format 
	printf(" __      __                                       __        ________  ________   ______   __    __      \n");
	printf("/  \\    /  |                                     /  |      /        |/        | /      \\ /  |  /  |     \n");
	printf("$$  \\  /$$/______   _______    _______   ______  $$/       $$$$$$$$/ $$$$$$$$/ /$$$$$$  |$$ |  $$ |          \n");
	printf(" $$  \\/$$//      \\ /       \\  /       | /      \\ /  |         $$ |   $$ |__    $$ |  $$/ $$ |__$$ |           \n");
	printf("  $$  $$//$$$$$$  |$$$$$$$  |/$$$$$$$/ /$$$$$$  |$$ |         $$ |   $$    |   $$ |      $$    $$ |                    \n");
	printf("   $$$$/ $$ |  $$ |$$ |  $$ |$$      \\ $$    $$ |$$ |         $$ |   $$$$$/    $$ |   __ $$$$$$$$ |                   \n");
	printf("    $$ | $$ \\__$$ |$$ |  $$ | $$$$$$  |$$$$$$$$/ $$ |         $$ |   $$ |_____ $$ \\__/  |$$ |  $$ |                   \n");
	printf("    $$ | $$    $$/ $$ |  $$ |/     $$/ $$       |$$ |         $$ |   $$       |$$    $$/ $$ |  $$ |                    \n");
	printf("    $$/   $$$$$$/  $$/   $$/ $$$$$$$/   $$$$$$$/ $$/          $$/    $$$$$$$$/  $$$$$$/  $$/   $$/                     \n");
	printf("                                                                                                                       \n");
	printf("                                                                                                                       \n");
	printf("\n\n\n");
	printf("========================================HR MANAGEMENT PLATFORM======================================\n\n");

	// verify authorization. login only if username is "admin" 
	loop = true;
	while (loop) {
		printf("Enter username: ");
		scanf("%s", username); // get username from the user
		getchar(); // clear input buffer
		if (strcmp(username, "admin") == 0) { // only "admin" can login
			printf("\n=======================================Authorization verified=======================================\n\n");
			loop = false;
		}
		else {
			printf("\n======================================No Authorization confirmed====================================\n\n");
		}
	}
	printf("\nHR data loading......\n");
	Sleep(1200); // wait for 2 secs
	system("cls"); // clear the console
}

void print() {
	printf("--------------------------------------------------------------------------------------\n");

	for (i = 0; i < pi; i++) { // print personnel's info in each line
		printf("%d\t%d\t%s\t%s\t%s\t%s\t%s\t%d\t%s\n",
			i + 1, p[i].id, p[i].name, p[i].sex, p[i].birth, p[i].sector, p[i].level, p[i].years, p[i].salary);
	}
}

void print_personnel(int index) {
	printf("\nsex\tbirth\tsector\tlevel\tyears\tsalary\n");
	printf("%s\t%s\t%s\t%s\t%d\t%s\n\n",
		p[index].sex, p[index].birth, p[index].sector, p[index].level, p[index].years, p[index].salary); // print out specific personnel's info
}

void option(char input_key) {
	switch (input_key) {
	case 'r': // read file
		r();
		break;
	case 'a': // add info
		a();
		break;
	case 'd': // delete info
		d();
		break;
	case 'f':
		f(); // find info
		break;
	case 'g':
		g(); // replace personnel's sector and level info
		break;
	case 'i':
		i_function(); // replace personnel's years or salary info
		break;
	case 'p':
		p_function(); // print personnel info table in certain classification
		break;
	case 's':
		s(); // sort personnel info
		break;
	case 'w':
		w(); // save result in to txt file
		break;
	case 'q':
		loop = false; // escape while loop
		break;
	default:
		printf("You typed the wrong option. Please try again...\n");
		break;
	}
}

char find_option() {
	char tmp; // temporary variable for input
	printf("Enter option... (a) Name / (b) ID number: "); // Choose options
	scanf("%c", &tmp);
	getchar(); // clear input buffer
	return tmp; // return option
}

bool check_overlap(char* option, char* name, int id) {
	bool overlapped;
	if (strcmp(option, "name") == 0) { // if search key is name
		for (i = 0; i < pi; i++) {
			if (strcmp(p[i].name, name) == 0) { // if target personnel is found
				overlapped = true;
				return overlapped;
			}
		}
		overlapped = false; // if target personnel is not found
		return overlapped;
	}

	else { // if search key is id
		for (i = 0; i < pi; i++) {
			if (p[i].id == id) { // if target personnel is found
				overlapped = true;
				return overlapped;
			}
		}
		overlapped = false; // if target personnel is not found
		return overlapped;
	}
}

void r() {
	FILE* fp = fopen("employee.txt", "rt"); // read mode
	for (i = 0; i < INIT; i++) { // get all personnel data and save
		fscanf(fp, "%d\t%d\t%s\t%s\t%s\t%s\t%s\t%d\t%s",
			&p[i].num, &p[i].id, p[i].name, p[i].sex, p[i].birth, p[i].sector, p[i].level, &p[i].years, p[i].salary);
	}
	fclose(fp); // close
	return;
}

void a() {
	int id, years;
	bool overlapped;
	char name[8], sex[3], birth[11], sector[15], level[10], salary[10];
	printf("Enter id, name, sex, birth, sector, level, years, salary: ");
	scanf("%d %s %s %s %s %s %d %s", &id, name, sex, birth, sector, level, &years, salary); // get info from the user
	getchar(); // clear input buffer

	//check if id is overlapped with the previous personnels
	overlapped = check_overlap("id", "", id);
	//if it is not overlapped, add to the personnel info list
	if (!overlapped) {
		p[pi].id = id;
		strcpy(p[pi].name, name);
		strcpy(p[pi].sex, sex);
		strcpy(p[pi].birth, birth);
		strcpy(p[pi].sector, sector);
		strcpy(p[pi].level, level);
		p[pi].years = years;
		strcpy(p[pi].salary, salary);
		pi++;
	}
	else {
		printf("Already exists...\n");
		return;
	}
}

void d() {
	char tmp, tmp1; // temporary char variables for input
	char name[10]; // name info
	int id; // id number info
	bool overlapped;

	tmp = find_option();
	if (tmp == 'a') { // entered personnel info will be 'name'
		printf("Enter personnel's name: ");
		scanf("%s", name); // get personnel's name
		getchar(); // clear input buffer
		overlapped = check_overlap("name", name, 0); // check whether 'name' is in personnel info table
	}
	else if (tmp == 'b') { // entered personnel info will be 'ID number'
		printf("Enter personnel's ID number: ");
		scanf("%d", &id); // get personnel's name
		getchar(); // clear input buffer
		overlapped = check_overlap("id", "", id); // check whether 'id' is in personnel info table
	}
	else { // if entered key value is neither 'a' or 'b'
		printf("Entered the wrong option...\n");
		return;
	}

	if (!overlapped) { // if not, print error message and end function d
		printf("There is no target personnel...\n");
		return;
	}

	print_personnel(i);
	printf("Do you really want to delete? (y/n) : "); // Ask again
	scanf("%c", &tmp1);
	getchar(); // clear input buffer
	if (tmp1 == 'n') { // cancel delete process
		printf("Delete process canceled...\n");
		return;
	}
	else if (tmp1 == 'y') {
		for (j = i; j < pi; j++) { // replace nth personnel info with (n+1)th personnel info 
			p[j].id = p[j + 1].id;
			strcpy(p[j].name, p[j + 1].name);
			strcpy(p[j].sex, p[j + 1].sex);
			strcpy(p[j].birth, p[j + 1].birth);
			strcpy(p[j].sector, p[j + 1].sector);
			strcpy(p[j].level, p[j + 1].level);
			p[j].years = p[j + 1].years;
			strcpy(p[j].salary, p[j + 1].salary);
		}
		pi--; // apply result of delete into number info
	}

	else { // if entered option that is not 'y' or 'n'
		printf("Entered the wrong option...\n");
		return;
	}
}

void f() {
	char tmp;
	char name[10];
	int id;
	bool found;

	tmp = find_option();
	if (tmp == 'a') { // entered personnel info will be 'name'
		printf("Enter personnel's name: ");
		scanf("%s", name); // get name info
		getchar(); // clear input buffer
		found = check_overlap("name", name, 0); // check whether 'name' is in personnel data table
		if (found) print_personnel(i);
	}

	else if (tmp == 'b') { // entered personnel info will be 'id number'
		printf("Enter personnel's ID number: ");
		scanf("%d", &id); // get id-num info
		getchar(); // clear input buffer
		found = check_overlap("id", "", id); // check whether 'id' is in personnel data table
		if (found) print_personnel(i);
	}

	else { // if entered key value is neither 'a' or 'b'
		printf("Entered the wrong option...\n");
	}
}

void g() {
	char tmp, tmp1; // temporary variable for options
	char name[10], sector[10], level[10];
	int id;
	bool found;

	tmp = find_option();
	if (tmp == 'a') { // Entered info will be 'name'
		printf("Enter personnel's name: ");
		scanf("%s", name); // get info from user
		getchar(); // clear input buffer
		found = check_overlap("name", name, 0); // check whether 'name' is in personnel data table
	}
	else if (tmp == 'b') {
		printf("Enter personnel's id: ");
		scanf("%d", &id);
		getchar(); // clear input buffer
		found = check_overlap("id", "", 0); // check whether 'id' is in personnel data table
	}
	else { // Entered key value is neither 'a' or 'b'
		printf("Entered wrong option...\n");
		return;
	}

	if (!found) { // if there is no target personnel
		printf("There is no target personnel...\n");
		return;
	}

	printf("Enter new sector and level : ");
	scanf("%s %s", sector, level); // get info from user
	getchar(); // clear input buffer
	print_personnel(i); // print specific personnel's info
	printf("Do you really want to change? (y/n): "); // double check before execution
	scanf("%c", &tmp1);
	getchar(); // clear input buffer
	if (tmp1 == 'y') { // proceed process
		strcpy(p[i].sector, sector); // replace personnel's sector
		strcpy(p[i].level, level); // replace personnel's level
	}
	else if (tmp1 == 'n') { // cancel process
		printf("Relocation process canceled...\n");
		return;
	}
	else { // if entered key value is neither 'y' or 'n'
		printf("Entered wrong option...\n");
		return;
	}
}

void i_function() {
	char tmp, tmp1; // temporary variable for options
	char name[10], salary[10];
	int id, years, option;
	bool found;

	tmp = find_option();
	if (tmp == 'a') { // Entered info will be 'name'
		printf("Enter personnel's name: ");
		scanf("%s", name); // get info from user
		getchar(); // clear input buffer
		found = check_overlap("name", name, 0); // check whether 'name' is in personnel data table
	}
	else if (tmp == 'b') {
		printf("Enter personnel's id number: ");
		scanf("%d", &id);
		getchar(); // clear input buffer
		found = check_overlap("id", "", id);
	}
	else { // Entered key value is neither 'a' or 'b'
		printf("Entered wrong option...\n");
		return;
	}

	if (!found) {
		printf("There is no target personnel...\n");
		return;
	}

	printf("Enter option Change (1) years / (2) salary : ");
	scanf("%d", &option); // get option from user
	getchar(); // clear input buffer
	if (option == 1) {
		printf("Enter new years: ");
		scanf("%d", &years);
		getchar(); // clear input buffer
		print_personnel(i); // print specific personnel's info
		printf("Do you really want to change? (y/n): "); // double check before execution
		scanf("%c", &tmp1);
		getchar(); // clear input buffer
		if (tmp1 == 'y') { // proceed process
			p[i].years = years; // replace personnel's years
		}
		else if (tmp1 == 'n') { // cancel process
			printf("Replace process canceled...\n");
			return;
		}
		else { // if entered key value is neither 'y' or 'n'
			printf("Entered wrong option...\n");
			return;
		}
	}
	else if (option == 2) {
		printf("Enter new salary: ");
		scanf("%s", salary);
		getchar(); // clear input buffer
		print_personnel(i);
		printf("Do you really want to change? (y/n): "); // double check before execution
		scanf("%c", &tmp1);
		getchar(); // clear input buffer
		if (tmp1 == 'y') { // proceed process
			strcpy(p[i].salary, salary); // replace personnel's sector
		}
		else if (tmp1 == 'n') { // cancel process
			printf("Replace process canceled...\n");
			return;
		}
		else { // if entered key value is neither 'y' or 'n'
			printf("Entered wrong option...\n");
			return;
		}
	}
	else { // if entered key value is neither '1' or '2'
		printf("Entered wrong option...\n");
		return;
	}
}

void p_function() {
	int option;
	char sex[10], sector[15];

	printf("Enter option...Classify personnel with...(1) index number / (2) sex / (3) sector : ");
	scanf("%d", &option);
	getchar(); // clear input buffer
	if (option == 1) {
		print(); // print all personnel (automatically sorted with index num)
	}
	else if (option == 2) {
		printf("Enter sex: ");
		scanf("%s", sex); // get target sex from user
		getchar(); // clear input buffer
		for (i = 0; i < pi; i++) {
			if (strcmp(p[i].sex, sex) == 0) { // print personnel with specific sex
				printf("%d\t%d\t%s\t%s\t%s\t%s\t%s\t%d\t%s\n",
					i + 1, p[i].id, p[i].name, p[i].sex, p[i].birth, p[i].sector, p[i].level, p[i].years, p[i].salary);
			}
		}
	}
	else if (option == 3) {
		printf("Enter sector: ");
		scanf("%s", sector); // get target sector from user
		getchar(); // clear input buffer
		for (i = 0; i < pi; i++) {
			if (strcmp(p[i].sector, sector) == 0) { // print personnel with specific sector
				printf("%d\t%d\t%s\t%s\t%s\t%s\t%s\t%d\t%s\n",
					i + 1, p[i].id, p[i].name, p[i].sex, p[i].birth, p[i].sector, p[i].level, p[i].years, p[i].salary);
			}
		}
	}
	else { // if entered key is neither '1', '2' or '3'
		printf("Entered wrong option...\n");
		return;
	}
}

void s() {
	char option;

	printf("Enter option... sort by (b) birth / (g) level / (y) years / (s) salary : ");
	scanf("%c", &option); // get sort option from user
	getchar(); // clear input buffer
	if (option == 'b') { // sort by birth
		qsort(p, pi, sizeof(struct personnel_info), cmp_birth);
	}
	else if (option == 'g') { // sort by level
		qsort(p, pi, sizeof(struct personnel_info), cmp_level);
	}
	else if (option == 'y') { // sort by years
		qsort(p, pi, sizeof(struct personnel_info), cmp_years);
	}
	else if (option == 's') { //sort by salary
		qsort(p, pi, sizeof(struct personnel_info), cmp_salary);
	}
	else { // if entered key is not appropriate
		printf("Entered wrong option...\n");
		return;
	}
}

int cmp_birth(const void* A, const void* B) {
	struct personnel_info* p1 = (struct personnel_info*)A;
	struct personnel_info* p2 = (struct personnel_info*)B;
	return strcmp(p2->birth, p1->birth);
}

int cmp_years(const void* A, const void* B) {
	struct personnel_info* p1 = (struct personnel_info*)A;
	struct personnel_info* p2 = (struct personnel_info*)B;
	return p2->years - p1->years;
}

int cmp_level(const void* A, const void* B) {
	char e1[10], e2[10]; // level of employee 1, employee 2
	int lv1, lv2; // level rank of employee 1, employee 2
	char lv_order[9][10] = { "사장", "부사장", "전무", "상무", "부장", "책임", "과장", "선임", "대리" }; // level rank
	struct personnel_info* p1 = (struct personnel_info*)A;
	struct personnel_info* p2 = (struct personnel_info*)B;
	// copy level to e1, e2
	strcpy(e1, p1->level);
	strcpy(e2, p2->level);
	for (j = 0; j < 9; j++) {
		if (strcmp(e1, lv_order[j]) == 0) lv1 = j; // save rank in to lv1
		if (strcmp(e2, lv_order[j]) == 0) lv2 = j; // save rank in to lv2
	}
	return lv1 - lv2;
}

int cmp_salary(const void* A, const void* B) {
	char e1[10], e2[10]; // salary of employee 1, employee 2
	//char s1[10], s2[10];
	struct personnel_info* p1 = (struct personnel_info*)A;
	struct personnel_info* p2 = (struct personnel_info*)B;
	// copy salary to e1, e2
	strcpy(e1, p1->salary);
	strcpy(e2, p2->salary);
	char* s1 = comma_remover(e1);
	char* s2 = comma_remover(e2);
	return atoi(s1) - atoi(s2); // change s1, s2 to integer and subtract. then return the result
}

char* comma_remover(char *str) {
	static char result[10];
	int tmp = 0;
	for (j = 0; j < strlen(str); j++) {
		if (str[j] != ',') {
			result[tmp] = str[j];
			tmp++;
		}
	}
	return result;
}

void w() {
	FILE* fp = fopen("employee_new.txt", "wt"); // write mode
	for (i = 0; i < pi; i++) { // write result in each line
		fprintf(fp, "%d\t%d\t%s\t%s\t%s\t%s\t%s\t%d\t%s\n",
			i + 1, p[i].id, p[i].name, p[i].sex, p[i].birth, p[i].sector, p[i].level, p[i].years, p[i].salary);
	}
	fclose(fp); // close
}
