#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "alltom.h"

char *
unencode(char *str) {
	char *deststart, *dest;
	int len = 0, maxlen = strlen(str);
	deststart = dest = (char *) malloc(maxlen);
	if(dest == NULL) return NULL;
	for(; str != '\0' && len < maxlen; str++, dest++, len++) {
		if(*str == '+') {
			*dest = ' ';
		} else if(*str == '%') {
			unsigned int code;
			if(sscanf(str+1, "%2x", &code) != 1) code = '?';
			*dest = code;
			str +=2;
		} else {
			*dest = *str;
		}
	}
	*dest = '\n';
	*++dest = '\0';
	return deststart;
}
