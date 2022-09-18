#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "contactHelpers.h"
#include "contacts.h"

#define MAXCONTACTS 5

void clearKeyboard(void)
{
    while (getchar() != '\n')
        ; // empty execution code block on purpose
}

// pause function definition goes here:
void pause(void)
{
    printf("(Press Enter to Continue)");
    clearKeyboard();
}

// getInt function definition goes here:
int getInt(void)
{
    int value;
    char NL = 'x';

    while (NL != '\n')
    {
        scanf("%d%c", &value, &NL);
        if (NL != '\n')
        {
            printf("*** INVALID INTEGER *** <Please enter an integer>: ");
            clearKeyboard();
        }
    }
    return value;
}

// getIntInRange function definition goes here:
int getIntInRange(int min, int max)
{
    int value = getInt();

    while ((value > max) || (value < min))
    {
        printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max);
        value = getInt();
    }

    return value;
}

// yes function definition goes here:
int yes(void)
{
    int flag = 0;
    char value = 'x';
    char NL = 'x';
    int retval = 0;

    while (NL != '\n' || flag == 0)
    {
        scanf("%c%c", &value, &NL);
        if (NL != '\n')
        {
            printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
            flag = 0;
            clearKeyboard();
        }
        else if (value == 'Y' || value == 'y')
        {
            flag = 1;
            retval = 1;
        }
        else if (value == 'N' || value == 'n')
        {
            flag = 1;
            retval = 0;
        }
    }
    return retval;
}

// menu function definition goes here:
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
    return getIntInRange(0, 6);
    printf("\n");
}

// contactManagerSystem function definition goes here:
void contactManagerSystem(void)
{
    int option;
    int done = 0;
    struct Contact contacts[MAXCONTACTS] = { { { "Rick", {"\0"}, "Grimes" },
                                               { 11, "Trailer Park", 0, "A7A 2J2", "King City" },
                                               { "4161112222", "4162223333", "4163334444" } },
                                             {
                                                 { "Maggie", "R.", "Greene" },
                                                 { 55, "Hightop House", 0, "A9A 3K3", "Bolton"},
                                                 { "9051112222", "9052223333", "9053334444" } },
                                             {
                                                 { "Morgan", "A.", "Jones" },
                                                 { 77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough" },
                                                 { "7051112222", "7052223333", "7053334444" } },
                                             {
                                                 { "Sasha", {"\0"}, "Williams" },
                                                 { 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
                                                 { "9052223333", "9052223333", "9054445555" } },
    };
    while (!done) {
        option = menu();
        printf("\n");
        switch (option) {
        case 1:
            displayContacts(contacts, MAXCONTACTS);
            pause();
            printf("\n");
            break;
        case 2:
            addContact(contacts, MAXCONTACTS);
            pause();
            printf("\n");
            break;
        case 3:
            updateContact(contacts, MAXCONTACTS);
            pause();
            printf("\n");
            break;
        case 4:
            deleteContact(contacts, MAXCONTACTS);
            pause();
            printf("\n");
            break;
        case 5:
            searchContact(contacts, MAXCONTACTS);
            pause();
            printf("\n");
            break;
        case 6:
            //Withouth sorting feature
            printf("<<< Feature to sort is unavailable >>>\n\n");
            //sortContacts(contacts, MAXCONTACTS);
            pause();
            printf("\n");
            break;
        default:
            printf("Exit the program? (Y)es/(N)o: ");
            if (yes() == 1) {
                printf("\nContact Management System: terminated");
                done = 1;
            }
            printf("\n");
        }
    }
}

void getTenDigitPhone(char phoneNum[])
{
    int needInput = 1;
    int i = 0;

    while (needInput == 1) {
        scanf("%10s", phoneNum);
        clearKeyboard();

        if (strlen(phoneNum) == 10)
            needInput = 0;
        else
        {
            printf("Enter a 10-digit phone number: ");
            needInput = 1;
        }

        for (i = 0; i < MAXCONTACTS; i++)
        {
            if (isdigit(phoneNum[i]) == 0)
            {
                needInput = 1;
                printf("Enter a 10-digit phone number: ");
            }
        }
    }




}



// findContactIndex:
int findContactIndex(const struct Contact contacts[], int size, const char cellNum[])
{
    int i;
    int found = -1;

    for (i = 0; found == -1 && i < size; i++) {
        if (strcmp(contacts->numbers.cell, cellNum) == 0) {
            found = i;
        }
        else {
            contacts++;
        }
    }
    return found;
}



// displayContactHeader
// Put empty function definition below:
void displayContactHeader(void)
{
    printf("+-----------------------------------------------------------------------------+\n");
    printf("|                              Contacts Listing                               |\n");
    printf("+-----------------------------------------------------------------------------+\n");
}


// displayContactFooter
// Put empty function definition below:
void displayContactFooter(int count)
{
    printf("+-----------------------------------------------------------------------------+\n");
    printf("Total contacts: %d\n\n", count);
}


// displayContact:
// Put empty function definition below:
void displayContact(const struct Contact* contact)
{
    printf(" %s", contact->name.firstName);

    if (*contact->name.middleInitial == 0) {
        printf(" ");
    }
    else {
        printf(" %s ", contact->name.middleInitial);
    }
    printf("%s\n", contact->name.lastName);
    printf("    C: %-10s   H: %-10s   B: %-10s\n", contact->numbers.cell, contact->numbers.home, contact->numbers.business);
    printf("       %d %s, ", contact->address.streetNumber, contact->address.street);

    if (contact->address.apartmentNumber > 0) {
        printf("Apt# %d, ", contact->address.apartmentNumber);
    }
    printf("%s, %s\n", contact->address.city, contact->address.postalCode);
}


// displayContacts:
// Put empty function definition below:
void displayContacts(const struct Contact contacts[], int size)
{
    int total = 0;
    int i;
    
    displayContactHeader();
    for (i = 0; i < size; i++) {
        if (strlen(contacts[i].name.firstName) != 0) {
            displayContact(&contacts[i]);
            total++;
        }
    }
    displayContactFooter(total);
}


// searchContacts:
// Put empty function definition below:
void searchContact(const struct Contact contacts[], int size)
{
    char numTel[11];
    int numIndex;
    printf("Enter the cell number for the contact: ");
    getTenDigitPhone(numTel);

    numIndex = findContactIndex(contacts, size, numTel);

    if (numIndex != -1) {
        printf("\n");
        displayContact(&(contacts[numIndex]));
        printf("\n");
    }
    else {
        printf("*** Contact NOT FOUND ***\n\n");
    }
}


// addContact:
// Put empty function definition below:
void addContact(struct Contact contacts[], int size)
{
    int i;

    for (i = 0; i < size; i++) {
        if (strlen(contacts[i].name.firstName) == 0) {
            getContact(&contacts[i]);
            printf("--- New contact added! ---\n\n");
            break;
        }
        else if (i == size - 1) {
            printf("*** ERROR: The contact list is full! ***\n\n");
            break;
        }
    }

}


// updateContact:
// Put empty function definition below:
void updateContact(struct Contact contacts[], int size)
{
    char numCell[11];
    int update;

    printf("Enter the cell number for the contact: ");
    getTenDigitPhone(numCell);

    update = findContactIndex(contacts, MAXCONTACTS, numCell);
    if (update == -1) {
        printf("*** Contact NOT FOUND ***\n\n");
    }
    else {
        printf("\nContact found:\n");
        displayContact(&contacts[update]);
        printf("\nDo you want to update the name? (y or n): ");
        if (yes() == 1) {
            getName(&contacts[update].name);
        }
        printf("Do you want to update the address? (y or n): ");
        if (yes() == 1) {
            getAddress(&contacts[update].address);
        }
        printf("Do you want to update the numbers? (y or n): ");
        if (yes() == 1) {
            getNumbers(&contacts[update].numbers);
        }
        printf("--- Contact Updated! ---\n\n");
    }
}


// deleteContact:
// Put empty function definition below:
void deleteContact(struct Contact contacts[], int size)
{
    struct Contact temp = { { "\0" } };
    int position;
    char numTel[11];
    char option;

    printf("Enter the cell number for the contact: ");
    getTenDigitPhone(numTel);
    position = findContactIndex(contacts, size, numTel);
    if (position != -1) {
        printf("\nContact found:\n");
        displayContact(&contacts[position]);
        printf("\nCONFIRM: Delete this contact? (y or n): ");
        option = yes();
        if (option == 0)
            printf("\n");
   
        if (option == 1) {
            contacts[position] = temp;
            printf("--- Contact deleted! ---\n\n");
        }
    }
    else {
        printf("*** Contact NOT FOUND ***\n");
    }
}



/*
// sortContacts:
// Put empty function definition below:
void sortContacts(struct Contact contacts[], int size)
{
        struct Contact temp;
        int i;
        int j;

        for (i = size - 1; i > 0; i--) {
            for (j = 0; j < size; j++) {
                if (strcmp(contacts[j].numbers.cell, contacts[j + 1].numbers.cell) > 0) {
                    temp = contacts[j];
                    contacts[j] = contacts[j + 1];
                    contacts[j + 1] = temp;
                }
            }
        }
        printf("--- Contacts sorted! ---\n\n");
    
}
*/
