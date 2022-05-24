// Copyright 2022 Amzarescu Adina 321CA
#include "client.h"

int login_cmd(int sockfd, char *user[1], int *online, int *bookstore, char **cookies, char *cookie) {
    char *pointer = strstr(post_req(sockfd, LOGIN, user, NULL), "Set-Cookie: ");
    if (!pointer) {
        printf("Oops :( failed to log in.\n");
        *online = 0;
        *bookstore = 0;
        return 0;
    }
    // Each part of the cookie is separated by ;
    strtok(pointer, ";");
    // Moving past the first part
    pointer = pointer + strlen("Set-Cookie: ");
    strcpy(cookie, pointer);
    cookies[0] = pointer;

    if(cookie) {
        printf("Hi there! You just logged in!\n");
    }
    return 1;
}

void logout_cmd (int sockfd, int *online, int *bookstore, char **cookies, char *tk) {
    get_req(sockfd, LOGOUT, tk, cookies, "get");
    *online = 0;
    *bookstore = 0;
    printf("You logged out! We hope we will see you soon!\n");
}

void register_cmd(int sockfd, char *user[1]) {
    char *p = strstr(post_req(sockfd, REGISTER, user, NULL),
                     "is taken");
    if(!p) {
        printf("Welcome to our family! You are now registered.\n");
    } else {
        printf("Somebody stole this username from you. Try another one.\n");
    }
}

void enter_cmd(int sockfd, int *bookstore, char **cookies, char *tk) {
    char *token = strstr(get_req(sockfd, ACCESS, tk, cookies, "get"), "token");
    if (!token) {
        printf("Sorry boo, you don't have acces to the library\n");
        *bookstore = 0;
    } else {
        // The token must be extracted from the
        // original format
        token = token + strlen("token':'");
        memset(tk, 0, BUFLEN);
        strcpy(tk, token);
        tk[strlen(tk) - strlen("'}")] = 0;
        printf("Yay, you are now in the library!\n");
        *bookstore = 1;
    }
}

void getbooks_cmd (int sockfd, char **cookies, char *tk) {
    char *books = strstr(get_req(sockfd, BOOKS, tk, cookies, "get"), "[");
    if (books) {
        // The books wil be printed with the id on the first line
        // and the name on the next one
        char *token = strtok(books, ",");
        while(token) {
            printf("%s\n", token);
            token = strtok(NULL, ",");
            if (token && token[strlen(token) - 1] != '}')
                printf("\n");
        }
    }   
}

void getbook_cmd(int sockfd, char **cookies, char *tk) {
    int id;
    char path[BUFLEN], aux[BUFLEN];
    
    printf("id = ");
    scanf("%d", &id);
    printf("\n");

    // Checking if the id is valid
    if (id < 0) {
        printf("We only work with unsigned numbers around here\n");
        printf("Try again with another id please\n.");
        printf("id = ");
        scanf("%d", &id);
        printf("\n");
    }

    // First adding the books path
    strncpy(path, BOOKS, sizeof(BOOKS));
    // Then the separator
    strcat(path, "/");
    // Converting the integer to a string
    sprintf(aux, "%d", id);
    // Adding the id to the path
    strcat(path, aux);
    // Adding NULL at the end
    strcat(path, "\0");

    char *get_str = get_req(sockfd, path, tk, cookies, "get");
    
    // If the book was found
    if (!strstr(get_str, "No book was found!")) {
        // Printing them on separate lines
        char *book = strstr(get_str, "[");
        char *token = strtok(book, ",");
        while(token) {
            printf("%s\n", token);
            token = strtok(NULL, ",");
            printf("\n");
        }
    } else {
        printf("There is no book with id = %d!\n", id);
    }
}

void addbook_cmd(int sockfd, char *tk) {
    char title[MAX], author[MAX], publisher[MAX], genre[MAX];
    int page_count;
    // This is the string that will store the integer
    char pages[BUFLEN];
    char *book[1];

    printf("title = ");
    scanf("%s", title);
    printf("\n");

    printf("author = ");
    scanf("%s", author);
    printf("\n");

    printf("publisher = ");
    scanf("%s", publisher);
    printf("\n");

    printf("genre = ");
    scanf("%s", genre);
    printf("\n");

    // This tests if page_count is a number
    printf("pages = ");
    int valid = scanf("%d", &page_count);
    if(!valid) {
        printf("\nYour book could not be added.\n");
        printf("You added a string instead of an integer for the pages.\n");
        return;
    }
    printf("\n");

    switch(test_input(title, author, publisher, genre, &page_count)) {
        case 1:
            scanf("%s", title);
            printf("\n");
            break;
        case 2:
            scanf("%s", author);
            printf("\n");
            break;
        case 3:
            scanf("%s", publisher);
            printf("\n");
            break;
        case 4:
            scanf("%s", genre);
            printf("\n");
            break;
        case 5:
            scanf("%d", &page_count);
            printf("\n");
            break;
        default:
            // If everything is valid the book will be added
            sprintf(pages, "%d", page_count);

            book[0] = get_book(title, author, publisher, genre, pages);
            post_req(sockfd, BOOKS, book, tk);
            printf("Congrats! Your book was successfully added!\n");
            break;
    }
}

int delbook_cmd(int sockfd, char **cookies, char *tk) {

    int id;
    char path[BUFLEN], aux[BUFLEN];
    
    printf("id = ");
    scanf("%d", &id);
    printf("\n");

    // Checking if the id is valid
    if (id < 0) {
        printf("We only work with unsigned numbers around here\n");
        printf("Try again with another id please\n.");
        printf("id = ");
        scanf("%d", &id);
        printf("\n");
    }

    // First adding the books path
    strncpy(path, BOOKS, sizeof(BOOKS));
    // Then the separator
    strcat(path, "/");
    // Converting the integer to a string
    sprintf(aux, "%d", id);
    // Adding the id to the path
    strcat(path, aux);
    // Adding NULL at the end
    strcat(path, "\0");

    char *del_str = get_req(sockfd, path, tk, cookies, "delete");
    
    // If there is no book with the given id
    if (strstr(del_str, "No book was deleted!")) {
        printf("There is no book with id = %d!\n", id);
        // The program will continue
        return CONTINUE;
    } else {
        printf("The book with id = %d was deleted!\n", id);
        return 1;
    }

    return 0;
}
