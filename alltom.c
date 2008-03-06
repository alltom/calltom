#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "alltom.h"

static void process_root(Dict *params, char *method, char **path);
static void process_pages(Dict *params, char *method, char **path);
static void process_page(Dict *params, char *method, char **path, char *page);

static char **parse_uri(char *uri);

int
main(void) {
	Dict *get;
	char **path;

	get = get_query_dict(getenv("QUERY_STRING"));
	path = parse_uri(getenv("PATH_INFO"));

	process_root(get, getenv("REQUEST_METHOD"), path);

	free_dict(get);
	free(path);

	return 0;
}

static char **
parse_uri(char *uri) {
	/* count slashes */
	int num_slashes = 1, i;
	char **ary, *pos = uri; /* always starts with '/' */
	while((pos = strchr(pos + 1, '/')) != NULL)
		num_slashes++;

	/* stuff into array */
	ary = (char **) malloc(num_slashes * sizeof(char *));
	if(ary == NULL) return NULL;
	pos = strtok(uri + 1, "/");
	for(i = 0; pos != NULL; pos = strtok(NULL, "/"), i++)
		ary[i] = pos;
	ary[i] = NULL;

	return ary;
}

static void
show_404(void) {
	printf("%s: %s\r\n", "Content-type", "text/html;charset=utf-8");
	printf("%s: %s\r\n", "Status", "404 Not Found");
	printf("\r\n");

	printf("<title>AllTom.com - Not Found</title>\n");
	printf("<h1>That URL was not found</h1>\n");

	printf("<p>suxxor 4j00</p>\n");

	printf("<hr />\n");
	printf("<p>My site does NOT normally suck. Right now I'm experimenting with coding it as a single CGI in C, so this level of suckage should be temporary. All of the old content will return.</p>\n");
}

static void
process_root(Dict *get, char *method, char **path) {
	if(path[0] != NULL) {
		if(strcmp(path[0], "pages") == 0) {
			process_pages(get, method, path+1);
		} else {
			show_404();
		}
		return;
	}

	printf("%s: %s\r\n", "Content-type", "text/html;charset=utf-8");
	printf("\r\n");

	printf("<title>AllTom.com</title>\n");
	printf("<h1>AllTom.com</h1>\n");

	printf("<p>I have many <a href=\"/pages\">pages</a>.</p>\n");

	printf("<hr />\n");
	printf("<p>My site does NOT normally suck. Right now I'm experimenting with coding it as a single CGI in C, so this level of suckage should be temporary. All of the old content will return.</p>\n");
}

static void
process_pages(Dict *get, char *method, char **path) {
	if(path[0] != NULL) {
		process_page(get, method, path+1, path[0]);
		return;
	}

	printf("%s: %s\r\n", "Content-type", "text/html;charset=utf-8");
	printf("\r\n");

	printf("<title>AllTom.com Pages</title>\n");
	printf("<h1>My Pages</h1>\n");

	printf("<p>See?</p>\n");

	printf("<ul>\n");
	printf("<li><a href=\"/pages/a\">Page A</a></li>\n");
	printf("<li><a href=\"/pages/b\">Page B</a></li>\n");
	printf("</ul>\n");

	printf("<hr />\n");
	printf("<p>My site does NOT normally suck. Right now I'm experimenting with coding it as a single CGI in C, so this level of suckage should be temporary. All of the old content will return.</p>\n");
}

static void
process_page(Dict *get, char *method, char **path, char *page) {
	if(path[0] != NULL) {
		show_404();
		return;
	}

	if(strcmp(page, "a") != 0 &&
	   strcmp(page, "A") != 0 &&
	   strcmp(page, "b") != 0 &&
	   strcmp(page, "B") != 0) {
		show_404();
		return;
	}
	page[0] = toupper(page[0]);

	printf("%s: %s\r\n", "Content-type", "text/html;charset=utf-8");
	printf("\r\n");

	printf("<title>AllTom.com Page %s</title>\n", page);
	printf("<h1>Page %s</h1>\n", page);

	printf("<p>Page %s is nothing like those other pages.</p>\n", page);

	printf("<hr />\n");
	printf("<p>My site does NOT normally suck. Right now I'm experimenting with coding it as a single CGI in C, so this level of suckage should be temporary. All of the old content will return.</p>\n");
	printf("<p><a href=\"http://github.com/AllTom/calltom/tree/master\">You can help</a> if you're not a lazy bum.</p>\n");
}

/* vim:set ts=4 sts=4 sw=4 noet: */
