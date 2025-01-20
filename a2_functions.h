/********* functions.h ********
   Student Name 	= Siddarth Jain
   Student Number	= 101304051
*/

#ifndef A2_FUNCTIONS_H
#define A2_FUNCTIONS_H

#define NUM_POSTS 3

#include "a2_nodes.h"


/********** DON'T MODIFY **********/
/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password);

/*
   Function that searches if the user is available in the database 
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username);


/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username);


/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend);

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name);

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text);

/*
   Function that adds a post to a user's timeline following a stack.
*/
void add_post(user_t *user, const char *text);

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user);

/*
   Function that  displays a specific user's posts (All posts)
*/
void display_all_user_posts(user_t *user);


/*
   Function that displays a specific user's friends (All friends)
*/
void display_user_friends(user_t *user);

/*
   Function that displays "number" of posts for a given user.
   After displaying "number" posts, it prompts if you want to display
   more posts.
   If there are no more post or the user types “n” or “N”, the function returns. 
*/
void display_posts_by_n(user_t *users, int number);

/*
   Function that free all users from the database before quitting the application.
*/
void teardown(user_t *users);

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu();


/* 
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users);


/********** DON'T MODIFY **********/

// Extra functions' Prototypes/Declarations go here

/*Function that returns an integer, 
representing user's choice for all menus and submenus*/
unsigned short int get_choice();

/*Function that manages password changes by asking 
for current password and changing to the new specified password*/
void manage_password(user_t *user);

/*Helper function that mananages calls to functions related to user posts
Case 1: Get post content and call add_post
Case 2: Call delete_post
Case 3: Return to main menu*/
void manage_posts (user_t *user);

/*Helper function that mananages calls to functions related to user friends
Case 1: Get friend username and call add_friend
Case 2: Get friend username and call delete_friend
Case 3: Return to main menu*/
void manage_friends(user_t *users, user_t *logged_in_user);

/*Function that returns the friend of a specified logged in user, NULL if friend not found*/
friend_t *find_friend(user_t *logged_in_user, const char *friend);

/*Function that prints the list of options the user can choose from for managing friends*/
void print_friend_menu();
/*Function that prints the list of options the user can choose from for managing posts*/
void print_post_menu(user_t *user);

/*Function to print the main menu welcoming the user to text-based facebook,
allowing them to register or log in*/
void print_main_menu();

/*Function that manages logged in users
Case 1: Call manage_password
Case 2: Call manage_posts
Case 3: Call manage_friends
Case 4: Call display_posts_by_n
Case 5: Return to main menu*/
void manage_logged_in_user(user_t *users, user_t *logged_in_user);

#endif 



