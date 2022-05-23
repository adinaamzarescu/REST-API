#include "client.h"

// Request = post
char *post_req(int sockfd, char *cmd, char *user[1], char *tk) {
	char *message = compute_post_request(HOST, cmd, APP, user, 1, NULL, 0, tk);
	send_to_server(sockfd, message);

	return receive_from_server(sockfd);
}

// Request = get
char *get_req(int sockfd, char *cmd, char *tk, char *cookies[1], char *get) {
	char *message = compute_get_request(HOST, cmd, NULL, cookies, 1, tk, get);
	send_to_server(sockfd, message);

	return receive_from_server(sockfd);
}

char *get_user() {
	char *user = malloc(MAX);
	char *pwd = malloc(MAX);

    JSON_Value *val = json_value_init_object();
	JSON_Object *obj = json_value_get_object(val);

	printf("username = ");
	scanf("%s", user);

    printf("\n");

	printf("password = ");
	scanf("%s", pwd);

    printf("\n");

	json_object_set_string(obj, "username", user);
	json_object_set_string(obj, "password", pwd);

    free(user);
    free(pwd);
	return json_serialize_to_string(val);
}

int test_input(char title[MAX], char author[MAX], char publisher[MAX],
           char genre[MAX], int *page_count) {

    if(!strcmp(title, "")) {
        printf("Please add a title.\n");
        printf("title = ");
        return 1;
    }

    if(!strcmp(author, "")) {
        printf("Please add an author.\n");
        printf("author = ");
        return 2;
    }

    if(!strcmp(publisher, "")) {
        printf("Please add a publisher.\n");
        printf("publisher = ");
        return 3;
    }

    if(!strcmp(genre, "")) {
        printf("Please add a genre.\n");
        printf("genre = ");
        return 4;
    }

    // This checks only if the number of pages is negative
    if(*page_count <= 0) {
        printf("Wait a sec.. that's not possible.\n");
        printf("Please add a valid number.\n");
        printf("pages = ");
        return 5;
    }
    return 0;
}

char *get_book(char title[MAX], char author[MAX], char publisher[MAX],
               char genre[MAX], char pages[BUFLEN]) {

    JSON_Value *val = json_value_init_object();
    JSON_Object *obj = json_value_get_object(val);

    json_object_set_string(obj, "title", title);
    json_object_set_string(obj, "author", author);
    json_object_set_string(obj, "publisher", publisher);
    json_object_set_string(obj, "genre", genre);
    json_object_set_string(obj, "page_count", pages);

    return json_serialize_to_string(val);
    
}


int process_command(int sockfd, char *cmd, char tk[BUFLEN], int *online, int *bookstore) {
    char *cookies[1];
    char cookie[MAX];
    char *user[1];
    if (!strcmp(cmd, EXIT_CMD)) {
        // my_exit will become 0
        return 0;
    } else {
        // Open connection
        sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);

        if(!strcmp(cmd, LOGIN_CMD)) {
            *online = 1;
            int ok = 1;
            // Get user credentials
            user[0] = get_user();
            // ok will test if the credentials are valid
            ok = login_cmd(sockfd, user, online, bookstore, cookies, cookie);
            if (!ok)
                return CONTINUE;
        } else if (!strcmp(cmd, REGISTER_CMD)) {
            user[0] = get_user();
            register_cmd(sockfd, user);
        } else if (!strcmp(cmd, LOGOUT_CMD)) {
            // The command is valid only if the user is online
            if (*online) {
                logout_cmd(sockfd, online, bookstore, cookies, tk);
            } else {
                printf("You are not logged in :(\n");
            }
        } else if (!strcmp(cmd, ENTER_CMD)) {
            // If no user is online, the acces to the bookstore is denied
            if (*online) {
                enter_cmd(sockfd, bookstore, cookies, tk);
            } else {
                printf("Sorry boo, you don't have acces to the library\n");
            }
        } else if (!strcmp(cmd, GETBOOKS_CMD)) {
            // This command works only if the user entered the bookstore
            if (*bookstore) {
                getbooks_cmd(sockfd, cookies, tk);
            } else {
                printf("You have to enter the library first.\n");
            }
        } else if (!strcmp(cmd, GETBOOK_CMD)) {
            // This command works only if the user entered the bookstore
            if (*bookstore) {
                getbook_cmd(sockfd, cookies, tk);
            } else {
                printf("You have to enter the library first.\n");
            }
        } else if (!strcmp(cmd, ADDBOOK_CMD)) {
            // This command works only if the user entered the bookstore
            if (*bookstore) {
                addbook_cmd(sockfd, tk);
            } else {
                printf("You have to enter the library first.\n");
            }
        } else if (!strcmp(cmd, DELBOOK_CMD)) {
            // This command works only if the user entered the bookstore
            if (*bookstore) {
                if (delbook_cmd(sockfd, cookies, tk) == CONTINUE) {
                    return CONTINUE;
                }
            } else {
                printf("You have to enter the library first.\n");
            }
        } else {
            printf("This is not a valid command :( \n");
        }
        close_connection(sockfd);
    }
    // my_exit remains 1
    return 1;
}
