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
 *      2. Programming in ANSI C - E. Balagurusamy -> Test Project Appendix IV
 */
#include <stdio.h>
#include <conio.h>
#include <dos.h>
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

/**
 * @brief Functions and their parameters.
 * 
 * @brief stricmp(str1,str2)
 * 
 *       @type     @return
 *  |------------|---------|
 *  |str1 > str2 | 1       |
 *  |------------|---------|
 *  |str1 == str2| 0       |
 *  |------------|---------|
 *  |str1 < str2 | -1      |
 *  |------------|---------|
 * @brief fread(array where the elements are stored, size of elements , num of elements, stream to be read)
 *                 @type                     @return
 *  |--------------------------------------|---------|
 *  |number of elements read               | 1       |
 *  |--------------------------------------|---------|
 *  |if size of number of elements are zero| 0       |
 *  |--------------------------------------|---------|
 * 
 * @brief Similarly fwrite(param1, param2, param3, param4)
 * 
 */

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
        if (fp == NULL)
        {
            printf("\nFile could not be opened!!!");
        }
        else if (ferror(fp) != 0)
        {
            printf("\nAn error has occurred in opening the file!");
        }
        else
        {
            while (fread(&contacts, sizeof(contacts), 1, fp) == 1) // (pointer, size, Num of ele., Pointer to FILE object [Input])
            {
                if (contacts.Name[0] == i || contacts.Name[0] == i - 32) // Checking the first character of every entry.
                {
                    printf("\nName\t\t: %s\nPhone\t\t: %ld\n\n.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-", contacts.Name, contacts.phoneNum);

                    contact++;
                }
            }

            fclose(fp);
        }
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
            for (int i = 0; i <= strlen(search); i++) // Single for loop to get the name of the contact "String after a space will also be considered."
            {
                searchName[i] = contacts.Name[i]; // searchName variable being assigned the name "character - by - character" from contacts.Name variable.
            }
            searchName[strlen(search)] = '\0'; // Last character of every string must be the *null* character.

            if (stricmp(searchName, search) == 0) // Check if the name read from the file matches the string(name) the user wants to search.
            {
                printf("\nName\t: %s\nPhone Number\t: %ld\n", contacts.Name, contacts.phoneNum);

                contact++; // Counter variable for the number of search results found.
            }
        }

        if (contact == 0) // Using the counter variable to display the number of matching contacts found.
        {
            printf("\nSorry! No matching contacts found!!!");
        }
        else
        {
            printf("\n%d match(s) found for your searched contact!", contact);
        }
        fclose(fp);

        printf("\nSearch Another Contact?\n\n\t[1] Yes\t\t[0] No\n\t");
        scanf("%d", &trychoice); // Giving the user a choice if he/she wants to search another contact.

    } while (trychoice == 1);
}

void Edit()
{
    /**
     * @brief Algorithm used here is taken from the book "Programming in C - Balaguruswamy -> Appendix IV Pg. 503 -> "Backup Database"".
     * 
     * @brief A temporary copy of the original file is created and edited and the original file is then deleted from the system. The temporary file created earlier is then converted and used as the original file.
     */

    List();

    fp = fopen("ContactsList.dll", "r");
    ftemp = fopen("temporary.dat", "w");

    fflush(stdin);

    printf("\n\tEDIT CONTACT\n.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-\n\n\tFrom the above list : \n\n\tEnter the name of contact you want to edit : ");
    scanf("%[^\n]", searchName);

    while (fread(&contacts, sizeof(contacts), 1, fp) == 1)
    {
        if (stricmp(searchName, contacts.Name) != 0)
        {
            fwrite(&contacts, sizeof(contacts), 1, ftemp);
        }
    } // Data from the original file is copied and written in the temporary file UNLESS and UNTIL the data to be altered is reached. Once the point is reached the contact to be edited is skipped and the rest of the contacts are written normally.
    fflush(stdin);

    printf("\n\nThe contact you want to edit is : '%s'\n\n", searchName);

reedit:

    printf("New Name : ");
    scanf("%[^\n]", &contacts.Name);
    if (stricmp(contacts.Name, " ") == 0)
    {
        printf("\tINVALID NAME!!!");
        goto reedit;
    }
    fflush(stdin);

    printf("New Phone : ");
    scanf("%ld", &contacts.phoneNum);

    if (contacts.phoneNum >= 99999 || contacts.phoneNum <= 90000)
    {
        printf("\n\n INVALID CONTACT NUMBER!!! \n\n");
        goto reedit;
    }

    fflush(stdin);

    fwrite(&contacts, sizeof(contacts), 1, ftemp);
    // The contact to be edited is changed here and added afterwards.

    fclose(fp);
    fclose(ftemp);

    remove("ContactsList.dll");
    rename("temporary.dat", "ContactsList.dll");

    // The original file is then removed and the new file is then converted to the original one.
}

void Delete()
{
    /**
     * @brief Algorithm used here is taken from the book "Programming in C - Balaguruswamy -> Appendix IV Pg. 503 -> "Backup Database"".
     * 
     * @brief A temporary copy of the original file is created and edited and the original file is then deleted from the system. The temporary file created earlier is then converted and used as the original file.
     */

    List();

    fflush(stdin);

    printf("\n\n\tDELETE CONTACT(s)\n\t.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-\n\n\tFrom the above list : \n\tEnter the name of the contact you want to delete : ");
    scanf("%[^\n]", &searchName);

    fp = fopen("ContactsList.dll", "r");
    ftemp = fopen("temporary.dat", "w");

    while (fread(&contacts, sizeof(contacts), 1, fp) != 0)
    {
        if (stricmp(searchName, contacts.Name) != 0)
        {
            fwrite(&contacts, sizeof(contacts), 1, ftemp);
        } // Data from the original file is copied and written in the temporary file UNLESS and UNTIL the data to be altered is reached. Once the point is reached the contact to be deleted is skipped and the rest of the contacts are written normally.
    }
    fclose(fp);
    fclose(ftemp);

    remove("ContactsList.dll");
    rename("temporary.dat", "ContactsList.dll");
}

void WrongChoice()
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
    scanf("%d", &choice);   // Take input from the user on what he/she wants to perform.

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
        WrongChoice();
        break;
    }
    int Rechoice;

rechoice:
    printf("\n\n\nAre you sure you want to exit? \n\n\t[1] Return to Main Menu!\t\t[0] Exit the Program!\n");

    scanf("%d", &Rechoice);

    switch (Rechoice)
    {
    case 1:
        goto label;

    case 0:
        break;

    default:
        WrongChoice();
        goto rechoice;
    }
end:

    system("cls");
    return 0;
}