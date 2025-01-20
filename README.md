# Text-Based Facebook

Upon starting the project with the user_details.csv file in project directory, all users alongside their friends and posts are loaded into the "database" as the program begins.
All the options described below regarding log-in, posts, and friends are functional for these users as well.

# Sign-in Screen

1. Register a new user 
    - Enter a username up to 30 characters, and a password between 8 and 15 characters (inclusive). 
2. Log in with an existing user
    - Enter a valid username and password combination.

# Logged-in Screen

1. Manage profile
    - Change your password with the [8-15] character criterion.
2. Manage posts (add/remove)
    - Add a post up to 250 characters.
    - Or remove a post, where the latest post is removed first due to a stack implementation.
    - Or return to the logged-in menu.
3. Manage friends (add/remove)
    - Add or remove another valid user on the platform as a friend.
    - Or return to the logged-in menu.
4. Display a friend's post
    - Display a friend's posts in batches of 3. 
    - Choose if you would like to display the next 3 posts or not. 
5. Exit
    - Exits to the sign-in screen, where you can sign up or log in again.
