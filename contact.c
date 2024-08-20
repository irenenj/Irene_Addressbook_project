#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "populate.h"

int validatePhoneNumber(const char *phone) {
    return strlen(phone) == 10 && strspn(phone, "0123456789") == 10;
}

int validateEmailAddress(const char *email) {
    return strstr(email, "@") != NULL && strstr(email, ".com") != NULL;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // discard characters
    }
}

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("%s, %s, %s\n", 
               addressBook->contacts[i].name, 
               addressBook->contacts[i].phone, 
               addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    exit(EXIT_SUCCESS);
}

void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS) {
        printf("Address book is full.\n");
        return;
    }

    char name_t[50], phone_t[20], email_t[50];
    
    printf("Enter Name: ");
    clearInputBuffer(); 
    fgets(name_t, sizeof(name_t), stdin);
    name_t[strcspn(name_t, "\n")] = '\0';  

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].name, name_t) == 0) 
        {
            printf("Contact with this name already exists.\n");
            return;
        }
    }

    printf("Enter Phone Number: ");
    fgets(phone_t, sizeof(phone_t), stdin);
    phone_t[strcspn(phone_t, "\n")] = '\0';  

    if (!validatePhoneNumber(phone_t)) 
    {
        printf("Invalid phone number. It should be 10 digits long and numeric.\n");
        return;
    }

    printf("Enter Email: ");
    fgets(email_t, sizeof(email_t), stdin);
    email_t[strcspn(email_t, "\n")] = '\0';  

    if (!validateEmailAddress(email_t)) 
    {
        printf("Invalid email address. It must contain '@' and end with '.com'.\n");
        return;
    }

    strcpy(addressBook->contacts[addressBook->contactCount].name, name_t);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone_t);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email_t);

    addressBook->contactCount++;
    printf("Contact added successfully.\n");
}

void searchContact(AddressBook *addressBook) 
{
    char search[50];
    printf("Enter name, phone, or email to search: ");
    clearInputBuffer(); 
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';  

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strstr(addressBook->contacts[i].name, search) || 
            strstr(addressBook->contacts[i].phone, search) || 
            strstr(addressBook->contacts[i].email, search)) 
        {
            printf("Contact Found: %s, %s, %s\n", 
                   addressBook->contacts[i].name, 
                   addressBook->contacts[i].phone, 
                   addressBook->contacts[i].email);
            return;
        }
    }
    printf("Contact not found.\n");
}

void editContact(AddressBook *addressBook)
{
    char edit[50],name_t[50],phone_t[50],email_t[50];
    printf("Enter the name/phone/email of the contact to edit: ");
    clearInputBuffer(); 
    fgets(edit, sizeof(edit), stdin);
    edit[strcspn(edit, "\n")] = '\0';  
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].name, edit) == 0 || strcmp(addressBook->contacts[i].phone,edit) == 0
            || strcmp(addressBook->contacts[i].email,edit) == 0)
        {
            int choice;
            printf("Contact Found: %s, %s, %s\n", 
                   addressBook->contacts[i].name, 
                   addressBook->contacts[i].phone, 
                   addressBook->contacts[i].email);
            printf("1. Edit Name\n2. Edit Phone\n3. Edit Email\nEnter choice: ");
            scanf("%d", &choice);
            clearInputBuffer(); 

            switch (choice) {
                case 1:
                    printf("Enter new name: ");
                    fgets(name_t, sizeof(name_t), stdin);
                    name_t[strcspn(name_t, "\n")] = '\0';  
                    strcpy(addressBook->contacts[i].name, name_t);
                    break;
                case 2:
                    printf("Enter new phone number: ");
                    fgets(phone_t, sizeof(phone_t), stdin);
                    phone_t[strcspn(phone_t, "\n")] = '\0'; 
                    if (!validatePhoneNumber(phone_t) )
                    {
                        printf("Invalid phone number.\n");
                        return;
                    }
                    strcpy(addressBook->contacts[i].phone, phone_t);
                    break;
                case 3:
                    printf("Enter new email: ");
                    fgets(email_t, sizeof(email_t), stdin);
                    email_t[strcspn(email_t, "\n")] = '\0';  
                    if (!validateEmailAddress(email_t)) 
                    {
                        printf("Invalid email address.\n");
                        return;
                    }
                    strcpy(addressBook->contacts[i].email, email_t);
                    break;
                default:
                    printf("Invalid choice.\n");
                    return;
            }
            printf("Contact updated successfully.\n");
            return;
        }
    }
    printf("Contact not found.\n");
}

void deleteContact(AddressBook *addressBook)
{
    char name_t[50];
    printf("Enter the name of the contact to delete: ");
    clearInputBuffer(); 
    fgets(name_t, sizeof(name_t), stdin);
    name_t[strcspn(name_t, "\n")] = '\0';  

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, name_t) == 0) {
            for (int j = i; j < addressBook->contactCount - 1; j++) {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            addressBook->contactCount--;
            printf("Contact deleted successfully.\n");
            return;
        }
    }
    printf("Contact not found.\n");
}
