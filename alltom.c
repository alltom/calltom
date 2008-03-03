#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alltom.h"

static void process_root(Dict *params, char *method);

int
main(void) {
	Dict *get;

	printf("%s: %s\r\n", "Content-type", "text/html;charset=utf-8");
	printf("\r\n");

	get = get_query_dict(getenv("QUERY_STRING"));
	process_root(get, getenv("REQUEST_METHOD"));
	return 0;
}

static void
process_root(Dict *get, char *method) {
	char *cm, *cn, *unencoded;
	char post[255];
	int m, n, len;

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
	printf("<p>Why the heck is this here instead of my normal site? SHUT UP!</p>\n");
}
