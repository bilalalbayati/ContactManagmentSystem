#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "contactHelpers.h"

#define MAXCONTACTS 5

void clearKeyboard(void) {
	while (getchar() != '\n');
}

void pause(void) {
	printf("(Press Enter to Continue)");
	clearKeyboard();
}

int getIntInRange(int min, int max)
{
	int set = min - 1;
	while (set < min || set > max)
	{
		set = getInt();
		if (set < min || set > max)
		{
			printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max);
		}
	}
	return set;
}

int getInt(void)
{
	char nL = 'x';
	int value;
	while (nL != '\n')
	{
		scanf("%d%c", &value, &nL);
		if (nL != '\n')
		{
			clearKeyboard();
			printf("*** INVALID INTEGER *** <Please enter an integer>: ");
		}
	}
	return value;
}

int menu(void)
{
	printf("Contact Management System\n");
	printf("-------------------------\n");
	printf("1. Display contacts\n");
	printf("2. Add a contact\n");
	printf("3. Update a contact\n");
	printf("4. Delete a contact\n");
	printf("5. Search contacts by cell phone number\n");
	printf("6. Sort contacts by cell phone number\n");
	printf("0. Exit\n\n");
	printf("Select an option:> ");

	int input = getIntInRange(0, 6);
	return input;
}

int yes(void) {
	char nL = 'x';
	char ans = 'b';
	while
		(!(ans == 'y' || ans == 'Y' || ans == 'n' || ans == 'N') || nL != '\n')
	{
		scanf("%c%c", &ans, &nL);
		if (!(ans == 'y' || ans == 'Y' || ans == 'n' || ans == 'N') || nL != '\n')
		{
			clearKeyboard();
			printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
		}
	}
	if (ans == 'y' || ans == 'Y')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void contactManagerSystem(void)
{
	struct Contact contacts[MAXCONTACTS] = { {{"Rick", {'\0'}, "Grimes"},
		{11, "Trailer Park", 0, "A7A 2J2", "King City"},
		{"4161112222", "4162223333", "4163334444"}},  {
			{"Maggie", "R.", "Greene"},
			{55, "Hightop House", 0, "A9A 3K3", "Bolton"},
			{"9051112222", "9052223333", "9053334444"}}, {
			{"Morgan", "A.", "Jones"},
			{77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough"},
			{"7051112222", "7052223333", "7053334444"}}, {
			{"Sasha", {'\0'}, "Williams"},
			{55, "Hightop House", 0, "A9A 3K3", "Bolton"},
			{"9052223333", "9052223333", "9054445555"}} };

	int entry = 5, exit = 0, extra = 0;
	while (exit == 0)
	{
		if (extra != 0) printf("\n");
		extra++;
		entry = menu();
		printf("\n");
		if (entry == 1)
		{
			displayContacts(contacts, MAXCONTACTS);
			pause();
		}
		else if (entry == 2)
		{
			addContact(contacts, MAXCONTACTS);
			pause();
		}
		else if (entry == 3)
		{
			updateContact(contacts, MAXCONTACTS);
			pause();
		}
		else if (entry == 4)
		{
			deleteContact(contacts, MAXCONTACTS);
			pause();
		}
		else if (entry == 5)
		{
			searchContacts(contacts, MAXCONTACTS);
			pause();
		}
		else if (entry == 6)
		{
			sortContacts(contacts, MAXCONTACTS);
			pause();
		}
		else
		{
			printf("Exit the program? (Y)es/(N)o: ");
			exit = yes();
		}
	}
	printf("\nContact Management System: terminated\n");
}

int findContactIndex(const struct Contact contacts[], int size, const char cellNum[])
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (strcmp(cellNum, contacts[i].numbers.cell) == 0) return i;
	}
	return -1;
}

void getTenDigitPhone(char phoneNum[])
{
	int needInput = 1;

	while (needInput == 1)
	{
		scanf("%10s", phoneNum);
		clearKeyboard();

		if (strlen(phoneNum) == 10) {
			needInput = 0;
			int i;
			for (i = 0; i < 10; i++) {
				if (phoneNum[i] < '0' || phoneNum[i] > '9') {
					needInput = 1;
					printf("Enter a 10-digit phone number: ");
					break;
				}
			}
		}
		else
		{
			printf("Enter a 10-digit phone number: ");
		}
	}
}



void displayContactHeader(void) {
	printf("+-----------------------------------------------------------------------------+\n");
	printf("|                              Contacts Listing                               |\n");
	printf("+-----------------------------------------------------------------------------+\n");
}

void displayContacts(const struct Contact contacts[], int size)
{
	displayContactHeader();
	int num = 0, i = 0;
	for (i = 0; i < size; i++) {
		if (contacts[i].numbers.cell[0] != '\0') {
			displayContact(&(contacts[i]));
			num++;
		}
	}
	displayContactFooter(num);
}

void displayContactFooter(int count)
{
	printf("+-----------------------------------------------------------------------------+\n");
	printf("Total contacts: %d\n\n", count);
}


void displayContact(const struct Contact* contact)
{
	if
		((contact->name.middleInitial[0]) != '\0') printf(" %s %s %s\n", (contact->name.firstName), (contact->name.middleInitial), (contact->name.lastName));
	else
		printf(" %s %s\n", (contact->name.firstName), (contact->name.lastName));
	printf("    C: %-10s   H: %-10s   B: %-10s\n", (contact->numbers.cell), (contact->numbers.home), (contact->numbers.business));

	if
		((contact->address.apartmentNumber > 0)) printf("       %d %s, Apt# %d, %s, %s\n", (contact->address.streetNumber), (contact->address.street), (contact->address.apartmentNumber), contact->address.city, contact->address.postalCode);
	else
		printf("       %d %s, %s, %s\n", (contact->address.streetNumber), (contact->address.street), (contact->address.city), (contact->address.postalCode));
}



void searchContacts(const struct Contact contacts[], int size) {
	printf("Enter the cell number for the contact: ");
	char phoneNum[11];
	getTenDigitPhone(phoneNum);
	int index = findContactIndex(contacts, size, phoneNum);
	if (index != -1) {
		printf("\n");
		displayContact(&(contacts[index]));
		printf("\n");
	}
	else {
		printf("*** Contact NOT FOUND ***\n\n");
	}
}

void deleteContact(struct Contact contacts[], int size) {
	printf("Enter the cell number for the contact: ");
	char cell[11];
	getTenDigitPhone(cell);
	int index = findContactIndex((contacts), size, cell);
	if (index != -1)
	{
		printf("\nContact found:\n");
		displayContact(&(contacts[index]));
		printf("\nCONFIRM: Delete this contact? (y or n): ");
		int ans = yes();
		if
			(ans) {
			contacts[index].numbers.cell[0] = '\0';
			printf("--- Contact deleted! ---\n");
		}
		printf("\n");
	}
	else
	{
		printf("*** Contact NOT FOUND ***\n\n");
	}
}

void addContact(struct Contact contacts[], int size) {
	char check[] = { '\0' };
	int avail = findContactIndex(contacts, size, check);
	if (avail != -1)
	{
		struct Contact addition;
		getContact(&(addition));
		contacts[avail] = addition;
		printf("--- New contact added! ---\n\n");
	}
	else
	{
		printf("*** ERROR: The contact list is full! ***\n\n");
	}
}


void updateContact(struct Contact contacts[], int size) {
	printf("Enter the cell number for the contact: ");
	char cell[11];
	getTenDigitPhone(cell);
	int found = findContactIndex(contacts, size, cell);
	if
		(found != -1) {
		printf("\nContact found:\n");
		displayContact(&(contacts[found]));
		printf("\nDo you want to update the name? (y or n): ");
		int ans = yes();
		if
			(ans) getName(&(contacts[found].name));

		printf("Do you want to update the address? (y or n): ");
		ans = yes();
		if
			(ans) getAddress(&(contacts[found].address));

		printf("Do you want to update the numbers? (y or n): ");
		ans = yes();
		if
			(ans) getNumbers(&(contacts[found].numbers));

		printf("--- Contact Updated! ---\n\n");
	}
	else
	{
		printf("*** Contact NOT FOUND ***\n\n");
	}
}



void sortContacts(struct Contact contacts[], int size) {
	printf("<<< Feature to sort is unavailable >>>\n\n");
}