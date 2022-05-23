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

### `Client`

You can find all the necessary files in "clientdir".

The main function opens a connection and then reads the commands in an
infinite loop. This loop will end only if the given command is "exit",
in which case the "my_exit" variable becomes 0.

`client_functions.c
`

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
is wrong, teh user will be asked to enter a valid one. For the number
of pages, this function only checks if they are positive, but the testing
for the correct format (int) is done in teh main function (addbook_cmd).

____________________________________________________________________________

Mentions:
  * I have used the 10th laboratory (HTTP) as skel for this project.
      * I have changed the requests.c, requests.h and client.c files
  * I have added stdout messages in order to make the project more
    aesthetically.
      * Examples: "This is not a valid command", "Please enter a command:"
      * I also added new lines in order to make the output intelligible.
____________________________________________________________________________
