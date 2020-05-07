#include <stdio.h>
#include "func1.h"
#include "usedtype.h"

void func1(void)
{
	STR s1;
	s1.info="this is func1";
	printf("%s", s1.info);
}
