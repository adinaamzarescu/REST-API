#include "requests.h"

char *compute_get_request(char *host, char *url, char *query_params,
                          char **cookies, int cookies_count, char *tk, char *cmd)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    // Write the method name, URL, request params (if any) and protocol type
    memset(line, 0, LINELEN);
    if (!strstr(cmd, "get")) {
        if (query_params) {
            sprintf(line, "DELETE %s?%s HTTP/1.1", url, query_params);
        } else {
            sprintf(line, "DELETE %s HTTP/1.1", url);
        }
    } else {
		if (query_params) {
			sprintf(line, "GET %s?%s HTTP/1.1", url, query_params);
		}
		else {
			sprintf(line, "GET %s HTTP/1.1", url);
		}
    }

    compute_message(message, line);

    // Add the host
    memset(line, 0, LINELEN);
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    // Add headers and/or cookies, according to the protocol format
    if (cookies) {
        sprintf(line, "Cookie: %s", cookies[0]);
        compute_message(message, line);
    }
    if(tk) {
        memset(line, 0, LINELEN);
		sprintf(line, "Authorization: Bearer %s\n", tk);
		compute_message(message, line);
	}

    // Add final new line
    compute_message(message, "\n");
    strcat(message, "\0");
    free(line);
    return message;
}


char *compute_post_request(char *host, char *url, char* content_type,
                           char **body_data, int body_data_fields_count,
                           char **cookies, int cookies_count, char *tk)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    char *body_data_buffer = calloc(LINELEN, sizeof(char));

    // Write the method name, URL and protocol type
    memset(line, 0, LINELEN);
    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);

    if(tk) {
        memset(line, 0, LINELEN);
		sprintf(line, "Authorization: Bearer %s", tk);
		compute_message(message, line);
	}
    
    // Add the host
    memset(line, 0, LINELEN);
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    // Add necessary headers (Content-Type and Content-Length are mandatory)
    int body_data_size = 0;
    for (int i = 0; i < body_data_fields_count - 1; i++) {
        strcat(body_data_buffer, body_data[i]);
        strcat(body_data_buffer, "&");
        body_data_size += strlen(body_data[i]);
        body_data_size++; //for '&
    }

    strcat(body_data_buffer, body_data[body_data_fields_count - 1]);
    body_data_size += strlen(body_data[body_data_fields_count - 1]);

    sprintf(line, "Content-Type: %s\r\nContent-Length: %d", content_type, body_data_size);
    compute_message(message, line);

    // Add cookies
    if (cookies) {
        compute_message(message, line);
    }

    // Add new line at end of header
    strcat(message, "\n");

    // Add data
	if (body_data) {
	    compute_message(message, body_data_buffer);
	}

    free(line);
    return message;
}
