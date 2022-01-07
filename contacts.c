
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "contacts.h"
#include "contactHelpers.h"

void getNumbers(struct Numbers* numbers) {
    int yesNo;
    printf("Please enter the contact's cell phone number: ");
    getTenDigitPhone(numbers->cell);
    printf("Do you want to enter a home phone number? (y or n): ");
    yesNo = yes();
    if (yesNo == 1) {
        printf("Please enter the contact's home phone number: ");
        getTenDigitPhone(numbers->home);
    }
    else
    {
        numbers->home[0] = '\0';
    }
    printf("Do you want to enter a business phone number? (y or n): ");
    yesNo = yes();

    if (yesNo == 1)
    {
        printf("Please enter the contact's business phone number: ");
        getTenDigitPhone(numbers->business);
    }
    else {
        numbers->business[0] = '\0';
    }
}

void getAddress(struct Address* address) {
    int yesNo, i;
    address->streetNumber = 0;
    printf("Please enter the contact's street number: ");
    while (address->streetNumber < 1)
    {
        address->streetNumber = getInt();
        if (address->streetNumber < 1) {
            printf("*** INVALID STREET NUMBER *** <must be a positive number>: ");
        }
    }
    printf("Please enter the contact's street name: ");
    scanf("%40[^\n]%*c", address->street);
    printf("Do you want to enter an apartment number? (y or n): ");
    yesNo = yes();
    if (yesNo == 1) {
        address->apartmentNumber = 0;
        printf("Please enter the contact's apartment number: ");
        while (address->apartmentNumber < 1) {
            address->apartmentNumber = getInt();
            if (address->apartmentNumber < 1)
            {
                printf("*** INVALID APARTMENT NUMBER *** <must be a positive number>: ");
            }
        }
    }
    else
    {
        address->apartmentNumber = 0;
    }

    char midi[12];
    printf("Please enter the contact's postal code: ");
    scanf("%11[^\n]%*c", midi);
    for (i = 0; i < 7; i++) address->postalCode[i] = midi[i];
    address->postalCode[7] = '\0';

    printf("Please enter the contact's city: ");
    scanf("%40[^\n]%*c", address->city);
}

void getName(struct Name* name) {
    int yesNo, i;
    printf("Please enter the contact's first name: ");
    scanf("%30[^\n]%*c", name->firstName);
    printf("Do you want to enter a middle initial(s)? (y or n): ");
    yesNo = yes();
    if (yesNo == 1) {
        char midi[15];
        printf("Please enter the contact's middle initial(s): ");
        scanf("%14[^\n]%*c", midi);
        for (i = 0; i < 6; i++) name->middleInitial[i] = midi[i];
        name->middleInitial[6] = '\0';
    }
    else
    {
        name->middleInitial[0] = '\0';
    }

    printf("Please enter the contact's last name: ");
    scanf("%35[^\n]%*c", name->lastName);
}


void getContact(struct Contact* contact)
{
    getName(&(contact->name));
    getAddress(&(contact->address));
    getNumbers(&(contact->numbers));
}