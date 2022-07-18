# Web Client - REST-API
## Copyright 2022 Amzarescu-Adina 321CA

____________________________________________________________________________

This is the third University Project for the Communication Protocols course.

The idea of this project is a client that interacts with a REST API.

Objectives:

• understanding the mechanisms of communication over HTTP

• Interaction with a REST API

• Understanding the concepts often used in the web such as JSON, session, JWT

____________________________________________________________________________

`JSON`

I parsed the user creditentials and book information using the files from:

https://github.com/kgabis/parson

____________________________________________________________________________

## `Client`

You can find all the necessary files in "clientdir".

The main function opens a connection and then reads the commands in an
infinite loop. This loop will end only if the given command is "exit",
in which case the "my_exit" variable becomes 0.

`client_functions.c`

Process_command will test for each of the possible commands and call the
respective functions. If the command is wrong the "This is not a valid command"
will be printed.

Here you will find 2 functions that use the request.

 * post_req
   
   Sends the message to the server and then receives a message back.
   
 * get_req

   There are 2 possibilities for "get" -> get and delete
   
The get_book and get_user functions are used to parse the given information
in JSON format.

The test_input function is used when adding a new book. If any information
is wrong, the user will be asked to enter a valid one. For the number
of pages, this function only checks if they are positive, but the testing
for the correct format (int) is done in the main function (addbook_cmd).

`commands.c`

Here are the main functions of the project.
The possible commands:

   * login
   
   * logout
   
   * register
   
   * enter_library
   
   * get_books
   
   * get_book
   
   * add_book
   
   * delete_book

-> The login function checks if the given username is in the database,
   keeps only the necessary characters of the cookie and sends back a
   message if the login was successful.
 
-> The logout function disconnects a user

-> The register function checks if the username is taken and 
   if not, it adds the user to the database
   
-> The enter function checks if the user is online and extracts
   the token from the initial format. The "bookstore" variable
   will be set to 1 since other commands are only possible if the
   user has already entered the library.
   
-> The get_books command will print all the books in the library
   as a pair of id and title, separated by a new line.
   
-> The get_book command will check if the given id is valid,
   create the url and print the book details
   
      * title
      * author
      * publisher
      * genre
      * pages
      
-> The add_book function will test if the given details are valid in which
   case a JSON object will be created and sent to the database.
   
-> The delete_book function will check if the given id is valid and then
   remove the given book from the library.

____________________________________________________________________________

Mentions:
  * I have added stdout messages in order to make the project more
    aesthetically.
      * Examples: "This is not a valid command", "Please enter a command:"
      * I also added new lines in order to make the output intelligible.
____________________________________________________________________________
