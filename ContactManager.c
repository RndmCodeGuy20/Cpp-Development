/**
 * @file ContactManager.c
 * @author Shantanu Mane (@RndmCodeGuy20) (shantanu.mane.200@outlook.com)
 * @brief A contact manager program using C language which can perform CRUD operations.
 * @version  1.0.12
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 * @ref 1. Let Us C - Yashwant Kanetkar
 *      2. Programming in ANSI C - E. Balagurusamy
 */
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

struct ContactManager
{
    long int phoneNum;
    char Name[20];
} contacts;

int contact, numcon = 0;
char search[20], searchName[20];

FILE *fp;
FILE *ftemp;

void Add()
{
    fp = fopen("ContactsList.dll", "a"); // Storing all the data in a dll (Dynamic Link Library) file. DLL, because this file contains instructions that other programs can call upon to do certain things.

    printf("\n\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~\n\t\t\tAdd Contact(s)\n\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

    do
    {
        fflush(stdin);

        printf("\n\nEnter contact name : (input blank space if no contact / contact already added) : ");
        scanf("%[^\n]", &contacts.Name);

        if (stricmp(contacts.Name, " ") == 0)
        {
            break;
        }
        fflush(stdin);

        printf("Add Phone Number : ");
        scanf("%ld", &contacts.phoneNum);

        if (contacts.phoneNum >= 99999 || contacts.phoneNum <= 90000)
        {
            printf("\n\n INVALID CONTACT NUMBER!!! \n\n");
            break;
        }

        fflush(stdin);

        numcon++;

        fwrite(&contacts, sizeof(contacts), 1, fp);
    } while (1);
    printf("\tNumber of Contacts Added : %d", numcon);

    fclose(fp);
}

void List()
{
    printf("\n\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~\n\t\t\tContact List\n\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~\n\nName\t\tPhone Number\n.-.-.-.-.-.-.-.-.-.-.-.-.-.-.\n\n");

    contact = 0;

    for (int i = 97; i <= 122; i++) // i = ASCII value, for a valid name, name should start with an alphabet.
    {
        fp = fopen("ContactsList.dll", "r");

        // fflush(stdin);

        while (fread(&contacts, sizeof(contacts), 1, fp) == 1) // (pointer, size, Num of ele., Pointer to FILE object [Input ])
        {
            if (contacts.Name[0] == i || contacts.Name[0] == i - 32) // Checking the first character of every entry.
            {
                printf("\nName\t\t: %s\nPhone\t\t: %ld\n\n.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-", contacts.Name, contacts.phoneNum);

                contact++;
            }
        }

        fclose(fp);
    }
    printf("\tTotal Contacts : %d", contact);
}

void Search()
{
    int trychoice;

    do
    {
        contact = 0;
        printf("\n\n\tSEARCH CONTACT \n\t.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-\n\tEnter the Name you want to search : ");

        fflush(stdin);

        scanf("%[^\n]", &search);

        fp = fopen("ContactsList.dll", "r");

        printf("\n\nSearch result for '%s' \n.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-\n", search);

        while (fread(&contacts, sizeof(contacts), 1, fp) == 1)
        {
            for (int i = 0; i <= strlen(search); i++)
            {
                searchName[i] = contacts.Name[i];
            }
            searchName[strlen(search)] = '\0';

            if (stricmp(searchName, search) == 0)
            {
                printf("\nName\t: %s\nPhone Number\t: %ld\n", contacts.Name, contacts.phoneNum);

                contact++;
            }
        }

        if (contact == 0)
        {
            printf("\nSorry! No matching contacts found!!!");
        }
        else
        {
            printf("\n%d match(s) found for your searched contact!", contact);
        }
        fclose(fp);

        printf("\nSearch Another Contact?\n\n\t[1] Yes\t\t[0] No\n\t");
        scanf("%d", &trychoice);

    } while (trychoice == 1);
}

void Edit()
{
    fp = fopen("ContactsList.dll", "r");

    ftemp = fopen("temporary.dat", "w");

    fflush(stdin);

    printf("EDIT CONTACT\n.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-\n\n\tEnter the name of contact you want to edit : ");

    scanf("%[^\n]", searchName);

    while (fread(&contacts, sizeof(contacts), 1, fp) == 1)
    {
        if (stricmp(searchName, contacts.Name) != 0)
        {
            fwrite(&contacts, sizeof(contacts), 1, ftemp);
        }
    }

    fflush(stdin);

    printf("\n\nThe contact you chose is : '%s'\n\n", searchName);

    printf("New Name : ");
    scanf("%[^\n]", &contacts.Name);

    fflush(stdin);

    printf("New Phone : ");
    scanf("%ld", &contacts.phoneNum);

    fflush(stdin);

    fwrite(&contacts, sizeof(contacts), 1, ftemp);

    fclose(fp);
    fclose(ftemp);

    remove("ContactsList.dll");
    rename("temporary.dat", "ContactsList.dll");
}

void Delete()
{
    fflush(stdin);

    printf("\n\n\tDELETE CONTACT(s)\n\t.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-\n\tEnter the name of the contact you want to delete : ");
    scanf("%[^\n]", &searchName);

    fp = fopen("ContactsList.dll", "r");
    ftemp = fopen("temporary.dat", "w");

    while (fread(&contacts, sizeof(contacts), 1, fp) != 0)

        if (stricmp(searchName, contacts.Name) != 0)
        {
            fwrite(&contacts, sizeof(contacts), 1, ftemp);
        }

    fclose(fp);
    fclose(ftemp);

    remove("ContactsList.dll");
    rename("temporary.dat", "ContactsList.dll");
}

void Default()
{
    printf("Wrong Choice!!! Select any choice from the main menu : ");
}

int main()
{
    int choice;
    char exitchoice;

label:
    printf("\n\t\t     ~~~~ Shantanu Mane's ~~~~\n");
    printf("\n\t\t ~~~~ Contact Manager Program ~~~~");

    printf("\n\n\n\t\t\t~~~~ MAIN MENU ~~~~\n\t\t~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\n\t\t[Option : 1] Add New Contact\n\t\t[Option : 2] List Contacts\n\t\t[Option : 3] Search a Contact\n\t\t[Option : 4] Edit a Contact\n\t\t[Option : 5] Delete a Contact\n\t\t[Option : 0] Exit Program\n\t\t~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\n\t\t");

    printf("\n\t\tEnter the choice : ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 0:
        fflush(stdin);
        printf("Are you sure you want to exit? [Y = Yes/N = No] : ");
        scanf("%c", &exitchoice);

        if (exitchoice == 'Y')
        {
            goto end;
        }
        else if (exitchoice == 'N')
        {
            goto label;
        }

    case 1:
        Add();
        break;

    case 2:
        List();
        break;

    case 3:
        Search();
        break;

    case 4:
        Edit();
        break;

    case 5:
        Delete();
        break;

    default:
        Default();
        break;
    }
    int Rechoice;

    printf("\n\n\nAre you sure you want to exit? \n\n\t[1] Return to Main Menu!\t\t[0] Exit the Program!\n");

    scanf("%d", &Rechoice);

    switch (Rechoice)
    {
    case 1:
        goto label;

    case 0:
        break;

    default:
        Default();
        break;
    }
    end:
    return 0;
}