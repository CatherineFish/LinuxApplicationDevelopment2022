#include <stdio.h> 
#include <string.h>
#include <libintl.h>
#include <locale.h>
#include <stdlib.h>

#include "config.h"

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "po"

int main (int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	bindtextdomain("guessNumber", LOCALE_PATH);
	textdomain ("guessNumber");
	int start = 1,end = 100, med;
	char *answer = NULL;
	size_t len = 4;
    ssize_t read;
	printf(_("Make a number from 1 to 100\n"));
	while (start != end)
	{
		med = start + (end - start) / 2;;
		printf(_("Is number greater %d?\n"), med);
		read = getline(&answer, &len, stdin);
      	if (read == -1) {
        	fprintf(stderr, "Something wrong\n");
        	return 1;
      	}
      	answer[strlen(answer) - 1] = 0;
		if (!strcmp(answer, _("yes")))
		{
			start = med + 1;
		} else if (!strcmp(answer, _("no")))
		{
			end = med;
		} else {
			printf(_("Wrong answer, 'yes'/'no' are avaliable\n"));	
		}
	}
	printf(_("Result! Your number is %d\n"), start);
	return 0;
}