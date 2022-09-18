#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "string.h"

#include "contactHelpers.h"
#include "contacts.h"

void getName(struct Name* name)
{
    int opt;

    printf("Please enter the contact's first name: ");
    scanf("%[^\n]s", name->firstName);
    clearKeyboard();

    printf("Do you want to enter a middle initial(s)? (y or n): ");
    opt = yes();


    if (opt == 0)
    {
        name->middleInitial[0] = '\0';
    }
    else
    {
        printf("Please enter the contact's middle initial(s): ");
        scanf("%6[^\n]s", name->middleInitial);
        clearKeyboard();
    }
   // clearKeyboard(); first 1

    printf("Please enter the contact's last name: ");
    scanf("%[^\n]s", name->lastName);
    clearKeyboard();
}


void getAddress(struct Address* address)
{

    int flag = 0;
    int value;
    printf("Please enter the contact's street number: ");

    do
    {
        value = getInt();

        if (value > 0)
        {
            flag = 1;
            address->streetNumber = value;
        }
        else
        {
            printf("*** INVALID STREET NUMBER *** <must be a positive number>: ");

        }

    } while (!flag);

    printf("Please enter the contact's street name: ");
    scanf("%[^\n]40s", address->street);
    clearKeyboard();

    printf("Do you want to enter an apartment number? (y or n): ");
    int opt = yes();


    if (opt == 0)
    {
        address->apartmentNumber = 0;
    }
    else
    {
        printf("Please enter the contact's apartment number: ");
        int flag = 0;
        int value;
        do
        {
            value = getInt();

            if (value > 0)
            {
                flag = 1;
                address->apartmentNumber = value;
            }
            else
            {
                printf("*** INVALID APARTMENT NUMBER *** <must be a positive number>: ");

            }

        } while (!flag);

    }


    printf("Please enter the contact's postal code: ");
    scanf(" %7[^\n]", address->postalCode);
    clearKeyboard();
    printf("Please enter the contact's city: ");
    scanf("%[^\n]s", address->city);
    clearKeyboard();
}


void getNumbers(struct Numbers* numbers)
{
    int optYesNo;


    printf("Please enter the contact's cell phone number: ");
        getTenDigitPhone(numbers->cell);


    printf("Do you want to enter a home phone number? (y or n): ");
    optYesNo = yes();

    if (optYesNo == 0)
    {
        numbers->home[0] = '\0';
    }
    else
    {
        printf("Please enter the contact's home phone number: ");
        //scanf(" %20[^\n]", numbers->home);
        getTenDigitPhone(numbers->home);
    }

    printf("Do you want to enter a business phone number? (y or n): ");
    
    optYesNo = yes();

    if (optYesNo == 0)
    {
        numbers->business[0] = '\0';
    }
    else
    {

        printf("Please enter the contact's business phone number: ");
        getTenDigitPhone(numbers->business);
    }
}

// getContact
void getContact(struct Contact* contact)
{
    struct Contact locContact;

    getName(&locContact.name);
    getAddress(&locContact.address);
    getNumbers(&locContact.numbers);

    *contact = locContact;
}
