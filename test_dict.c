#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "alltom.h"

int
test(int num) {
	Dict *d;

	switch(num) {
	case 0:
		d = get_query_dict(NULL);
		assert(d != NULL);
		assert(get_value(d, "a") == NULL);
		break;

	case 1:
		d = get_query_dict("");
		assert(d != NULL);
		assert(get_value(d, "a") == NULL);
		break;

	case 2:
		d = get_query_dict("&");
		assert(d != NULL);
		assert(get_value(d, "a") == NULL);
		break;

	case 3:
		d = get_query_dict("a&");
		assert(d != NULL);
		assert(get_value(d, "b") == NULL);
		assert(get_value(d, "a") != NULL);
		assert(strcmp(get_value(d, "a"), "") == 0);
		break;

	case 4:
		d = get_query_dict("a=&");
		assert(d != NULL);
		assert(get_value(d, "b") == NULL);
		assert(get_value(d, "a") != NULL);
		assert(strcmp(get_value(d, "a"), "") == 0);
		break;

	case 5:
		d = get_query_dict("a=b&");
		assert(d != NULL);
		assert(get_value(d, "b") == NULL);
		assert(get_value(d, "a") != NULL);
		assert(strcmp(get_value(d, "a"), "b") == 0);
		break;

	case 6:
		d = get_query_dict("a=b");
		assert(d != NULL);
		assert(get_value(d, "b") == NULL);
		assert(get_value(d, "a") != NULL);
		assert(strcmp(get_value(d, "a"), "b") == 0);
		break;

	case 7:
		d = get_query_dict("a=");
		assert(d != NULL);
		assert(get_value(d, "b") == NULL);
		assert(get_value(d, "a") != NULL);
		assert(strcmp(get_value(d, "a"), "") == 0);
		break;

	case 8:
		d = get_query_dict("=");
		assert(d != NULL);
		assert(get_value(d, "a") == NULL);
		break;

	case 9:
		d = get_query_dict("=a&");
		assert(d != NULL);
		assert(get_value(d, "a") == NULL);
		break;

	case 10:
		d = get_query_dict("=a");
		assert(d != NULL);
		assert(get_value(d, "a") == NULL);
		break;

	case 11:
		d = get_query_dict("a");
		assert(d != NULL);
		assert(get_value(d, "b") == NULL);
		assert(get_value(d, "a") != NULL);
		assert(strcmp(get_value(d, "a"), "") == 0);
		break;

	case 12:
		d = get_query_dict("a=b1=2");
		assert(d != NULL);
		assert(get_value(d, "b") == NULL);
		assert(get_value(d, "a") != NULL);
		assert(strcmp(get_value(d, "a"), "b1=2") == 0);
		break;

	case 13:
		d = get_query_dict("a=b&1=2");
		assert(d != NULL);
		assert(get_value(d, "b") == NULL);
		assert(get_value(d, "a") != NULL);
		assert(strcmp(get_value(d, "a"), "b") == 0);
		assert(get_value(d, "1") != NULL);
		assert(strcmp(get_value(d, "1"), "2") == 0);
		break;

	case 14:
		d = get_query_dict("a=b&&1=2&");
		assert(d != NULL);
		assert(get_value(d, "b") == NULL);
		assert(get_value(d, "a") != NULL);
		assert(strcmp(get_value(d, "a"), "b") == 0);
		assert(get_value(d, "1") != NULL);
		assert(strcmp(get_value(d, "1"), "2") == 0);
		break;

	case 15:
		d = get_query_dict("&a=b&&1=2&=19&");
		assert(d != NULL);
		assert(get_value(d, "b") == NULL);
		assert(get_value(d, "a") != NULL);
		assert(strcmp(get_value(d, "a"), "b") == 0);
		assert(get_value(d, "1") != NULL);
		assert(strcmp(get_value(d, "1"), "2") == 0);
		break;

	case 16:
		d = get_query_dict("&something long=another long thing&?");
		assert(d != NULL);
		assert(get_value(d, "this is a long thing") == NULL);
		assert(get_value(d, "something long") != NULL);
		assert(strcmp(get_value(d, "something long"), "another long thing") == 0);
		break;

	case 17:
		d = get_query_dict("a=b");
		assert(d != NULL);
		assert(get_value(d, "b") == NULL);
		assert(get_value(d, "a") != NULL);
		assert(get_value(d, "A") != NULL);
		assert(strcmp(get_value(d, "a"), "b") == 0);
		assert(strcmp(get_value(d, "A"), "b") == 0);
		break;

	case 18:
		d = get_query_dict("a=b&a=c");
		assert(d != NULL);
		assert(get_value(d, "b") == NULL);
		assert(get_value(d, "a") != NULL);
		assert(get_value(d, "A") != NULL);
		assert(strcmp(get_value(d, "a"), "c") == 0);
		assert(strcmp(get_value(d, "A"), "c") == 0);
		break;

	default: return 0;
	}

	return 1;
}

int
main(void) {
	int i = 0;

	while(test(i++));

	printf("=== done (%d tests) ===\n", i-1);

	return 0;
}
