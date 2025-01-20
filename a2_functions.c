/*****************
    Student Name 	= Siddarth Jain
    Student Number	= 101304051
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here

/* -----------------------------------------------------------------------
CHOICE 1: REGISTERING NEW USER TO DATABSE
-----------------------------------------------------------------------*/

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password) {

    user_t *new_user = malloc(sizeof(user_t)); // Malloc 1
    assert(new_user != NULL);

    strcpy(new_user->username, username);
    strcpy(new_user->password, password);
    new_user->friends = NULL;
    new_user->posts = NULL;
    new_user->next = NULL;

    user_t *previous = NULL, *current = users;

    while (current != NULL && strcmp(new_user->username, current->username) > 0) {
        previous = current;
        current = current->next;
    }

    new_user->next = current;
    if (previous == NULL) {
        users = new_user;
    } else {
        previous->next = new_user;
    }

    return users;
}

/* -----------------------------------------------------------------------
CHOICE 2: MANAGING PROFILE
-----------------------------------------------------------------------*/

/*Function that manages password changes by asking 
for current password and changing to the new specified password*/
void manage_password(user_t *user) {

    char old_password[15];
    char new_password[15];

    printf("Enter the old password for %s: ", user->username);
    scanf("%s", old_password);

    // Store the new password in the database if they recall their old password
    if (strcmp(user->password, old_password) == 0) {
        
        do {
            printf("Enter the new password for %s [up to 15 characters]: ", user->username);
            scanf("%s", new_password);

            if (strlen(new_password) < 8) {
                printf("Passwords must be at least 8 characters!\n");
            }
        } while (strlen(new_password) < 8);

        strcpy(user->password, new_password);
        printf("*** Password Changed for %s ***\n", user->username);
    } else {
        printf("*** %s is the incorrect password for %s. ***\n", old_password, user->username);
    }
}

/* -----------------------------------------------------------------------
CHOICE 3: MANAGING POSTS
-----------------------------------------------------------------------*/

/*Helper function that mananages calls to functions related to user posts
Case 1: Get post content and call add_post
Case 2: Call delete_post
Case 3: Return to main menu*/
void manage_posts(user_t *user) {
    
    printf("-----------------------------------------------------------------------\n");
    printf("Managing %s's Posts\n", user->username);
    printf("-----------------------------------------------------------------------\n");

    while (true) {

        print_post_menu(user);
        unsigned short int post_choice = get_choice();

        switch(post_choice) {

            case 1:

                char post[250];
                printf("Enter your post content [up to 250 characters]: ");
                scanf(" %[^\n]s", post);

                add_post(user, post);
                break;

            case 2:

                if (delete_post(user) == false) {
                    printf("*** No posts to delete for %s! ***\n", user->username);
                }

                break;

            case 3:
                return;

            default: 
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}

/*Function that prints the list of options the user can choose from for managing posts*/
void print_post_menu(user_t *user) {

    // Display user posts before printing submenu
    if (user->posts == NULL) {
        printf("Note: No posts available for %s.\n", user->username);
    } else {
        display_all_user_posts(user);
    }

    printf("[1] Add a new post\n"
    "[2] Remove a post\n"
    "[3] Return to main menu\n");
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text) {

    post_t *new_post = malloc(sizeof(post_t)); //2ND MALLOC
    assert(new_post != NULL);

    strcpy(new_post->content, text);
    new_post->next = NULL;

    return new_post;
}

/*
   Function that adds a post to a user's timeline following a stack.
*/
void add_post(user_t *user, const char *text) {

    post_t *new_post = create_post(text);

    new_post->next = user->posts;
    user->posts = new_post;
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user) {

    if (user->posts == NULL) {
        return false;
    }

    post_t *post_to_remove = user->posts; 
    user->posts = post_to_remove->next;
    free(post_to_remove);

    return true;
}

//  Function that  displays a specific user's posts (All posts)
void display_all_user_posts(user_t *user) {

    unsigned short int index = 1;

    printf("-----------------------------------------------------------------------\n");
    printf("%s's posts\n", user->username);
    printf("-----------------------------------------------------------------------\n");

    post_t *current_post = user->posts;
    while (current_post != NULL) {
        printf("%hu - %s\n", index, current_post->content);
        current_post = current_post->next;
        index++;
    }

    printf("-----------------------------------------------------------------------\n");
}


/* -----------------------------------------------------------------------
CHOICE 4: MANAGING USER FRIENDS
-----------------------------------------------------------------------*/

/*Helper function that mananages calls to functions related to user friends
Case 1: Get friend username and call add_friend
Case 2: Get friend username and call delete_friend
Case 3: Return to main menu*/
void manage_friends(user_t *users, user_t *logged_in_user) {
    
    printf("-----------------------------------------------------------------------\n");
    printf("Managing %s's Friends\n", logged_in_user->username);
    printf("-----------------------------------------------------------------------\n");

    while (true) {

        print_friend_menu();
        unsigned short int friend_choice = get_choice();
        
        char friend[30];

        switch(friend_choice) {

            case 1:
                
                printf("Enter a new friend's name: ");
                scanf("%s", friend);

                // *** Assumption: You cannot add yourself as a friend, as it causes issues with case 4 ***
                if (strcmp(logged_in_user->username, friend) == 0) {
                    printf("You cannot add yourself as a friend!\n");
                    break;
                }

                if (find_user(users, friend) == NULL) {
                    printf("User %s is not registered on Facebook. Friends list unchanged.\n", friend);
                } else {
                    friend_t *friend_node = find_friend(logged_in_user, friend);

                    if (friend_node != NULL) {
                        printf("You are already friends with %s! Friends list unchanged.\n", friend);
                    } else {
                        add_friend(logged_in_user, friend);

                        //Task 4
                        user_t *friend_user = find_user(users, friend); // Find the friend user node
                        friend_t *friend_node = find_friend(logged_in_user, friend); // Find the friend node 
                        friend_node->posts = &friend_user->posts; // Save address of friend's posts in friend node

                        printf("*** Friend %s added ***\n", friend);
                        
                        /*Debugging Task 4
                        post_t *current_post = *friend_node->posts;
                        printf("Posts of %s: \n", friend_node->username);
                        while (current_post != NULL) {
                            printf(" - %s\n", current_post->content);
                            current_post = current_post->next;
                        }*/
                    }

                }

                break;

            case 2:

                printf("List of %s' Friends: \n", logged_in_user->username);
                display_user_friends(logged_in_user);

                printf("Enter a friend's name to delete: ");
                scanf("%s", friend);

                if (delete_friend(logged_in_user, friend) == true) {
                    printf("Updated List of %s' Friends: \n", logged_in_user->username);
                    display_user_friends(logged_in_user);
                } else {
                    printf("*** Invalid friend name ***\n");
                }

                break;

            case 3:
                /* *** Assumption: This returns to the main menu, 
                where user can register or log in to come to this menu again *** */
                return;

            default: 
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}

/*Function that returns the friend of a specified logged in user, NULL if friend not found*/
friend_t *find_friend(user_t *logged_in_user, const char *friend) {

    friend_t *current_friend = logged_in_user->friends;
    while (current_friend != NULL) {
        if (strcmp(current_friend->username, friend) == 0) {
            return current_friend;
        }
        current_friend = current_friend->next;
    }

    return NULL;
}

/*Function that prints the list of options the user can choose from for managing friends*/
void print_friend_menu() {

    printf("[1] Add a new friend\n"
    "[2] Remove a friend\n"
    "[3] Return to main menu\n");
}

/*
   Function that creates a new friend's node.
   Return the newly created node.
*/

friend_t *create_friend(const char *username) {

    friend_t *new_friend = malloc(sizeof(friend_t)); //3RD MALLOC
    assert(new_friend != NULL);

    strcpy(new_friend->username, username);
    new_friend->posts = NULL;
    new_friend->next = NULL;

    return new_friend;

}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend) {

    friend_t *new_friend = create_friend(friend);

    friend_t *previous = NULL, *current = user->friends;

    while (current != NULL && strcmp(new_friend->username, current->username) > 0) {
        previous = current;
        current = current->next;
    }

    new_friend->next = current;
    if (previous == NULL) {
        user->friends = new_friend;
    } else {
        previous->next = new_friend;
    }
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name) {

    friend_t *previous = NULL, *current = user->friends;

    while (current != NULL) {
        if (strcmp(current->username, friend_name) == 0) {
            if (previous == NULL) {
                user->friends = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return true;
        }
        previous = current;
        current = current->next;
    }

    return false;
}

/*
   Function that displays a specific user's friends (All friends)
*/
void display_user_friends(user_t *user) {

    unsigned short int index = 1;

    printf("-----------------------------------------------------------------------\n");
    printf("%s's friends\n", user->username);
    printf("-----------------------------------------------------------------------\n");

    friend_t *current_friend = user->friends;
    while (current_friend != NULL) {
        printf("%hu - %s\n", index, current_friend->username);
        current_friend = current_friend->next;
        index++;
    }

    printf("-----------------------------------------------------------------------\n");

}

/* -----------------------------------------------------------------------
CHOICE 5: DISPLAYING N POSTS
-----------------------------------------------------------------------*/

/*
   Function that displays "number" of posts for a given user.
   After displaying "number" posts, it prompts if you want to display
   more posts.
   If there are no more post or the user types “n” or “N”, the function returns. 
*/
void display_posts_by_n(user_t *users, int number) {

    post_t *current = users->posts; 
    if (current == NULL) {
        printf("*** User %s has no posts! ***\n", users->username);
        return;
    }

    unsigned short int index = 1; // To show index of the post
    unsigned short int number_of_repeats = 1; // To keep track of how many times user has pressed Y
    char display_choice; 

    for (; current != NULL && index <= number; current = current->next) {
        printf("Post %d - %s\n", index, current->content);
        index++;
    }

    do {
        if (current == NULL) {
            printf("*** All posts by %s have been displayed! ***\n", users->username);
            return;
        }

        printf("Would you like to see more posts from %s (Y/N): ", users->username);
        scanf(" %c", &display_choice);

        if (display_choice == 'Y' || display_choice == 'y') {
            number_of_repeats++;
            for (; current != NULL && index <= number * number_of_repeats; current = current->next) {
                printf("Post %d - %s\n", index, current->content);
                index++;
            }
        }

    } while (display_choice == 'Y' || display_choice == 'y');

}

/* -----------------------------------------------------------------------
GENERAL FUNCTIONS
-----------------------------------------------------------------------*/

/*Function that manages logged in users
Case 1: Call manage_password
Case 2: Call manage_posts
Case 3: Call manage_friends
Case 4: Call display_posts_by_n
Case 5: Return to main menu*/
void manage_logged_in_user(user_t *users, user_t *logged_in_user) {
    
    // *** Assumption: The textbox below welcoming the user is only printed when the user first logs in ***
    printf("***********************************************\n");
    printf("*               Welcome %s                    *\n", logged_in_user->username);
    printf("***********************************************\n");

    while (true) {

        print_menu();
        unsigned short int menu_choice = get_choice();

        char username[30];
        char password[15];

        switch(menu_choice) {

            case 1: 

                manage_password(logged_in_user); // Function to manage logged in user password 
                break;

            case 2: 

                manage_posts(logged_in_user); // Function to manage logged in user posts
                break;

            case 3:

                manage_friends(users, logged_in_user); // Function to manage logged in user friends
                break;

            case 4:

                printf("Enter a friend's name to display their posts: ");
                scanf("%s", username);
                
                friend_t *friend_node = find_friend(logged_in_user, username);

                if (friend_node == NULL) {
                    printf("You are not friends with %s, or they are not a registered user on Facebook.\n", username);
                } else {
                    user_t *friend_posts = find_user(users, username);
                    display_posts_by_n(friend_posts, NUM_POSTS);
                }
        
                break;

            case 5:

                return;               

            default: 
                printf("Invalid choice. Please try again.\n");
                break;
        }
}
}

/*
   Function that free all users from the database before quitting the application.
*/
void teardown(user_t *users) {

    user_t *current_user = users; 
    while (current_user != NULL) {
        user_t *temp_user = current_user;
        current_user = current_user->next;

        post_t *current_post = temp_user->posts;
        while (current_post != NULL) {
            post_t *temp_post = current_post;
            current_post = current_post->next;
            free(temp_post);
        }

        temp_user->posts = NULL;

        friend_t *current_friend = temp_user->friends;
        while (current_friend != NULL) {
            friend_t *temp_friend = current_friend;
            current_friend = current_friend->next;
            free(temp_friend);
        }
        temp_user->friends = NULL;
        
        free(temp_user);
        temp_user = NULL;

    }

    users = NULL;
}

// Function that prints the main menu with a list of options for the user to choose from.
void print_menu() {

    printf("[1] Manage profile\n"
    "[2] Manage posts (add/remove)\n"
    "[3] Manage friends (add/remove)\n"
    "[4] Display a friend's post\n"
    "[5] Exit\n");
}

/*Function to print the main menu welcoming the user to text-based facebook,
allowing them to register or log in*/
void print_main_menu() {

    printf("***********************************************\n");
    printf("*       Welcome to Text-Based Facebook        *\n");
    printf("***********************************************\n");

    printf("[1] Register a new user\n"
    "[2] Login with existing user's information\n"
    "[3] Exit\n");

}

/*Function that returns an integer, 
representing user's choice for all menus and submenus*/
unsigned short int get_choice(void) {
    
    unsigned short int choice;
    int result;

    while (true) {
        printf("Enter your choice: ");
        result = scanf("%hu", &choice);
        if (result == 1) {  // Successful numeric input
            return choice;
        } else {  // Invalid input (non-numeric)
            printf("Invalid choice. Please enter a valid number: ");
            // Flush the input buffer
            while (getchar() != '\n');  // Discard the rest of the line
        }
    }
}

/*
   Function that searches if the user is available in the database 
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username) {

    user_t *current_user = users;
    while (current_user != NULL) {
        if (strcmp(current_user->username, username) == 0) {
            return current_user;
        }
        current_user = current_user->next;
    }
    
    return NULL;
}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    srand(time(NULL));
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token); 
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}
