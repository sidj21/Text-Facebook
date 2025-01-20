/********* main.c ********
    Student Name 	= Siddarth Jain
    Student Number	= 101304051
*/

// Includes go here
#include <stdlib.h>
#include <ctype.h> // tolower()
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

int main()
{
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);

    while (true) {

        print_main_menu();
        unsigned short int main_menu_choice = get_choice();
        char username[30];
        char password[15];

        switch (main_menu_choice) {

            case 1: 

                printf("Enter your username: ");
                scanf("%s", username);
                
                // Change username to lower case
                for (int i = 0; i < strlen(username); i++) {
                    username[i] = tolower(username[i]); 
                }

                // Check if user already exists in database
                if (find_user(users, username) != NULL) { 
                    printf("Username %s is taken! Please choose another username.\n", username);
                    break;
                }

                // Ensure password is at least 8 characters
                do {
                    printf("Enter your password [up to 15 characters]: ");
                    scanf("%s", password);

                    if (strlen(password) < 8) {
                        printf("Passwords must be at least 8 characters!\n");
                    }
                } while (strlen(password) < 8); // Keep asking if password is less than 8 characters
                

                users = add_user(users, username, password);
                printf("*** User %s added to Facebook! ***\n", username);
                
                break;

            case 2: 
                
                printf("Enter your username: ");
                scanf("%s", username);

                printf("Enter your password: ");
                scanf("%s", password); 

                // *** Assumption: If they enter username in caps, they will still be able to log in ***

                // Change username to lower case
                for (int i = 0; i < strlen(username); i++) {
                    username[i] = tolower(username[i]); 
                }

                // Check if this user exists, print an error if they don't
                user_t *logged_in_user = find_user(users, username);

                if (logged_in_user == NULL) {
                    printf("User %s not found. Please register with this username!\n", username);
                    break;
                }

                if (strcmp(password, logged_in_user->password) == 0) {
                    manage_logged_in_user(users, logged_in_user); // Function to manage all choices when logged in
                } else {
                    printf("*** %s is not the correct password for %s. ***\n", password, username);
                }

                break;

            case 3:

                // Exits the application
                teardown(users);
                printf("Goodbye, visit again! Shutting down aplication...");

                return EXIT_SUCCESS;

            default:
                printf("Invalid choice. Please try again.\n");
        }
        
    }
}