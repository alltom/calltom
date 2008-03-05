#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alltom.h"

static void process_root(Dict *params, char *method, char **path);
static char **parse_uri(char *uri);

int
main(void) {
	Dict *get;
	char **path;

	printf("%s: %s\r\n", "Content-type", "text/html;charset=utf-8");
	printf("\r\n");

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
	ary[i] = '\0';

	return ary;
}

static void
process_root(Dict *get, char *method, char **path) {
	char *cm, *cn, *unencoded;
	char post[255];
	int i, m, n, len;

	printf("<title>Multiplication results</title>\n");
	printf("<h1>Multiplication results</h1>\n");

	cm = get_value(get, "m");
	cn = get_value(get, "n");
	if(cm == NULL || cn == NULL) {
	} else {
		m = atoi(cm);
		n = atoi(cn);
		printf("<p>The product of %d and %1d is %d.</p>\n", m, n, m*n);
	}

	printf("<hr />\n");

	printf("<p>URI: %s</p>\n", getenv("PATH_INFO"));
	for(i = 0; path[i] != NULL; i++)
		printf("<p>[%s]</p>\n", path[i]);

	printf("<hr />\n");

	printf("<h2>GET form</h2>\n");
	printf("<form action=\"\" method=get>\n");
	printf("<p>m = <input name=m /></p>\n");
	printf("<p>n = <input name=n /></p>\n");
	printf("<p><input type=submit /></p>\n");
	printf("</form>\n");

	printf("<hr />\n");

	printf("<h2>POST form</h2>\n");
	printf("<form action=\"\" method=post>\n");
	printf("<p>m = <input name=m /></p>\n");
	printf("<p>n = <input name=n /></p>\n");
	printf("<p><input type=submit /></p>\n");
	printf("</form>\n");

	if(strcmp(method, "POST") == 0) {
		printf("<hr />\n");
		len = getenv("CONTENT_LENGTH") ? atoi(getenv("CONTENT_LENGTH")) : 0;
		printf("<p>Your content-length is crazy! It's %d%s</p>\n", len, len > 254 ? " (which is too long)" : "");

		fgets(post, len > 254 ? 255 : len + 1, stdin);
		if( (unencoded = unencode(post)) != NULL) {
			printf("<pre>%s</pre>\n", post);
			printf("<p>... decodes to ...</p>\n");
			printf("<pre>%s</pre>\n", unencoded);
			free(unencoded);
		} else {
			printf("<p>Not enough memory to display it. :(</p>");
		}
	}

	printf("<hr />\n");
	printf("<p>My site does NOT normally suck. Right now I'm experimenting with coding it as a single CGI in C, so this level of suckage should be temporary. All of the old content will return.</p>\n");
}

/* vim:set ts=4 sts=4 sw=4 noet: */
