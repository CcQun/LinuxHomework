#include <stdio.h>
#include "func2.h"
#include "usedtype.h"

void func2(void)
{
	STR s;
	s.info="\tthis is func2";
	printf("%s", s.info);
}
