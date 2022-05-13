CSCI 2270 Spring 2021
Final Project: Mini-Git
Group Members: Matthew Van Winkle, Tyler Curnow, Bach Nguyen.

This program demonstrates an imlplimentatoin of a version control system similar to git and github.
There are five main options a user can choose while running the program: initilize, add, remove, commit and checkout.
1: The initilize funcion is used to create a new repository where the user will be able to commit and store their file versions as they work.
2: Add is used to add files to the current stage in the commit in order to be uploaded to the reposityor later.
3: Remove is used to remove files from the current stage in the commit in order to prevent them from being uploaded to the repository later.
4: Commit allows the user to push changes into the repository. If a file's contents has been changed from it's previous version, a new fileversion will be created.
5: Checkout allows the user to checkout a previous version of their files allowing them to go to a version of the file where the current changes were not added.

The user-interface is built in a way to allow the user to easily navigate the program. If a syntax error is made the UI will let the user know.
