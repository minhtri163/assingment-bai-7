#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_ADDRESS_LENGTH 50

struct information {
    char name[MAX_NAME_LENGTH];
    int phone;
    char address[MAX_ADDRESS_LENGTH];
};

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void add_contact() {
    struct information contact;
    printf("Enter name: ");
    fgets(contact.name, MAX_NAME_LENGTH, stdin);
    contact.name[strcspn(contact.name, "\n")] = '\0';

    printf("Enter phone number: ");
    scanf("%d", &contact.phone);
    clearInputBuffer();

    printf("Enter address: ");
    fgets(contact.address, MAX_ADDRESS_LENGTH, stdin);
    contact.address[strcspn(contact.address, "\n")] = '\0';

    FILE* file = fopen("danhba.txt", "a");
    if (file == NULL) {
        printf("Can not open this file!\n");
        return;
    }

    fprintf(file, "%s %d %s\n", contact.name, contact.phone, contact.address);
    fclose(file);
    printf("\nContact added successfully!\n");
}

void Display_contact() {
    FILE* file = fopen("danhba.txt", "r");
    if (file == NULL) {
        printf("Can not open this file!\n");
        return;
    }
    printf("Contact List: \n");

    struct information Display;
    while (fscanf(file, " %s %d %[^\n]", &Display.name, &Display.phone, &Display.address) == 3) {
        printf(" Name: %s\n Phone: %d\n Address: %s\n\n", Display.name, Display.phone, Display.address);
    }
    fclose(file);
}

void Search_contact() {
    char search[MAX_NAME_LENGTH];
    printf("Enter name to search for: ");
    fgets(search, MAX_NAME_LENGTH, stdin);
    search[strcspn(search, "\n")] = '\0';

    FILE* file = fopen("danhba.txt", "r");
    if (file == NULL) {
        printf("Can not open this file!\n");
        return;
    }
    int found = 0;
    struct information Display;
    while (fscanf(file, " %s %d %[^\n]", &Display.name, &Display.phone, &Display.address) == 3) {
        if (strcmp(Display.name, search) == 0) {
            printf(" Name: %s\n Phone: %d\n Address: %s\n\n", Display.name, Display.phone, Display.address);
            found = 1;
        }
    }
    fclose(file);

    if (found == 0) {
        printf("No contact found!\n");
    }
}

int main() {
    while (1) {
        printf("\nWelcome to the Contact Manager!\n");
        printf("1. Add a new contact\n");
        printf("2. Display all contacts\n");
        printf("3. Search for a contact\n");
        printf("4. Exit\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                add_contact();
                break;
            case 2:
                Display_contact();
                break;
            case 3:
                Search_contact();
                break;
            case 4:
                printf("Good bye!\n");
                return 0;
            default:
                printf("Please try again!\n");
        }
    }

    return 1;
}
