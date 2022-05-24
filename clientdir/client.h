// Copyright 2022 Amzarescu Adina 321CA
#ifndef _CLIENT_
#define _CLIENT_

#include <stdio.h>     
#include <stdlib.h>     
#include <unistd.h>     
#include <string.h>     
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h>
#include <arpa/inet.h>
#include "../helpers/helpers.h"
#include "../requests/requests.h"
#include "../parson/parson.h"

#define PORT 8080
#define HOST "34.241.4.235"
#define MAX 100
#define CONTINUE 2

#define REGISTER "/api/v1/tema/auth/register"
#define LOGIN "/api/v1/tema/auth/login"
#define ACCESS "/api/v1/tema/library/access"
#define BOOKS "/api/v1/tema/library/books"
#define LOGOUT "/api/v1/tema/auth/logout"
#define APP "application/json"

#define REGISTER_CMD "register"
#define LOGIN_CMD "login"
#define LOGOUT_CMD "logout"
#define ENTER_CMD "enter_library"
#define GETBOOKS_CMD "get_books"
#define GETBOOK_CMD "get_book"
#define ADDBOOK_CMD "add_book"
#define DELBOOK_CMD "delete_book"
#define EXIT_CMD "exit"

// You can find those functions in client_functions.c
char *post_req(int sockfd, char *cmd, char *user[1], char *tk);

char *get_req(int sockfd, char *cmd, char *tk, char *cookies[1], char *get);

char *get_user();

int test_input(char title[MAX], char author[MAX], char publisher[MAX],
               char genre[MAX], int *page_count);

char *get_book(char title[MAX], char author[MAX], char publisher[MAX],
               char genre[MAX], char pages[BUFLEN]);

int process_command(int sockfd, char *cmd, char tk[BUFLEN], int *online, int *bookstore);


// You can find those functions in commands.c
int login_cmd(int sockfd, char *user[1], int *online, int *bookstore, char **cookies, char *cookie);

void logout_cmd (int sockfd, int *online, int *bookstore, char **cookies, char *tk);

void register_cmd(int sockfd, char *user[1]);

void enter_cmd(int sockfd, int *bookstore, char **cookies, char *tk);

void getbooks_cmd (int sockfd, char **cookies, char *tk);

void getbook_cmd(int sockfd, char **cookies, char *tk);

void addbook_cmd(int sockfd, char *tk);

int delbook_cmd(int sockfd, char **cookies, char *tk);

#endif
