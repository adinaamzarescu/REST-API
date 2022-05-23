#include "client.h"

int main(int argc, char *argv[])
{
    int sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);
    char tk[BUFLEN];
	char *cmd = malloc(MAX);
    int my_exit = 1;
    int online = 0;
    int bookstore = 0;

    while (my_exit) {
        scanf("%s", cmd);
        // my_exit will become 0 if cmd = "exit"
        my_exit = process_command(sockfd, cmd, tk, &online, &bookstore);
        if (my_exit == CONTINUE)
            continue;
    }

    free(cmd);
    cmd = NULL;

    return 0;
}
