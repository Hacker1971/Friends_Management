#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_PHONE_LEN 20
#define MAX_EMAIL_LEN 50
#define MAX_ADDRESS_LEN 100
#define MAX_FRIENDS 1000

// Struct definition
struct Friend
{
    char name[MAX_NAME_LEN];
    char phone[MAX_PHONE_LEN];
    char email[MAX_EMAIL_LEN];
    char address[MAX_ADDRESS_LEN];
    int roomNo;
    char gender[10];
};

struct Friend friends[MAX_FRIENDS];
int numFriends = 0;

// Function prototypes
void addFriend();
void deleteFriend();
void searchFriend();
void updateFriend();
void displayFriends();
void saveFriends();
void loadFriends();

int main()
{
    loadFriends(); // Load friends data from file

    int choice;

    while (1)
    {
        // Display menu
        printf("\n------------------\n");
        printf("Friend Management System\n");
        printf("1. Add Friend\n");
        printf("2. Delete Friend\n");
        printf("3. Search Friend\n");
        printf("4. Update Friend\n");
        printf("5. Display Friends\n");
        printf("6. Exit\n");
        printf("------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addFriend();
            break;
        case 2:
            deleteFriend();
            break;
        case 3:
            searchFriend();
            break;
        case 4:
            updateFriend();
            break;
        case 5:
            displayFriends();
            break;
        case 6:
            saveFriends(); // Save data to file
            printf("Exiting program.\n");
            //saveFriends(); // Save data before exiting
            return 0;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

void addFriend()
{
    // Get friend details from user
    if (numFriends >= MAX_FRIENDS)
    {
        printf("Maximum number of friends reached.\n");
        return;
    }

    printf("Enter name: ");
    scanf("%49s", friends[numFriends].name);

    printf("Enter phone: ");
    scanf("%19s", friends[numFriends].phone);

    printf("Enter email: ");
    scanf("%49s", friends[numFriends].email);

    printf("Enter address: ");
    scanf("%99s", friends[numFriends].address);

    printf("Enter room number: ");
    scanf("%d", &friends[numFriends].roomNo);

    printf("Enter gender: ");
    scanf("%9s", friends[numFriends].gender);

    numFriends++;
}

void deleteFriend()
{
    // Delete friend by name
    char name[MAX_NAME_LEN];
    int found = 0;

    printf("Enter name to delete: ");
    scanf("%49s", name);

    for (int i = 0; i < numFriends; i++)
    {
        if (strcmp(friends[i].name, name) == 0)
        {
            found = 1;
            for (int j = i; j < numFriends - 1; j++)
            {
                friends[j] = friends[j + 1];
            }
            numFriends--;
            printf("Friend '%s' deleted.\n", name);
            break;
        }
    }

    if (!found)
    {
        printf("Friend '%s' not found.\n", name);
    }
}

void searchFriend()
{
    // Search friend by name
    char searchName[MAX_NAME_LEN];
    int found = 0;

    printf("Enter name to search: ");
    scanf("%49s", searchName);

    for (int i = 0; i < numFriends; i++)
    {
        if (strcmp(friends[i].name, searchName) == 0)
        {
            printf("Friend found:\n");
            printf("Name: %s\nPhone: %s\nEmail: %s\nAddress: %s\nRoom No: %d\nGender: %s\n",
                   friends[i].name, friends[i].phone, friends[i].email,
                   friends[i].address, friends[i].roomNo, friends[i].gender);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Friend '%s' not found.\n", searchName);
    }
}

void updateFriend()
{
    // Update friend's details by name
    char name[MAX_NAME_LEN];
    int found = 0;

    printf("Enter name to update: ");
    scanf("%49s", name);

    for (int i = 0; i < numFriends; i++)
    {
        if (strcmp(friends[i].name, name) == 0)
        {
            printf("Enter updated phone: ");
            scanf("%19s", friends[i].phone);

            printf("Enter updated email: ");
            scanf("%49s", friends[i].email);

            printf("Enter updated address: ");
            scanf("%99s", friends[i].address);

            printf("Enter updated room number: ");
            scanf("%d", &friends[i].roomNo);

            printf("Enter updated gender: ");
            scanf("%9s", friends[i].gender);

            printf("Friend '%s' updated.\n", name);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Friend '%s' not found.\n", name);
    }
}

void displayFriends()
{
    // Display all friends' details
    printf("\n------------------\n");
    printf("List of Friends\n");
    printf("------------------\n");

    for (int i = 0; i < numFriends; i++)
    {
        printf("Name: %s\nPhone: %s\nEmail: %s\nAddress: %s\nRoom No: %d\nGender: %s\n",
               friends[i].name, friends[i].phone, friends[i].email,
               friends[i].address, friends[i].roomNo, friends[i].gender);
        printf("------------------\n");
    }
}

void saveFriends()
{
    // Save friends' details to a file
    FILE *file = fopen("friends.dat", "w");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < numFriends; i++)
    {
        fprintf(file, "%s;%s;%s;%s;%d;%s\n",
                friends[i].name, friends[i].phone, friends[i].email,
                friends[i].address, friends[i].roomNo, friends[i].gender);
    }

    fclose(file);
    printf("Friends' details saved to file.\n");
}

void loadFriends()
{
    // Load friends' details from a file
    FILE *file = fopen("friends.dat", "r");

    if (file == NULL)
    {
        printf("File not found or error opening file.\n");
        return;
    }

    while (fscanf(file, "%49[^;];%19[^;];%49[^;];%99[^;];%d;%9[^\n]\n",
                  friends[numFriends].name, friends[numFriends].phone,
                  friends[numFriends].email, friends[numFriends].address,
                  &friends[numFriends].roomNo, friends[numFriends].gender) == 6)
    {
        numFriends++;
        if (numFriends >= MAX_FRIENDS)
        {
            printf("Maximum number of friends reached.\n");
            break;
        }
    }

    fclose(file);
    printf("Friends' details loaded from file.\n");
}
