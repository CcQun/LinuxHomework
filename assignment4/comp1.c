#include <stdio.h>
#include "comp1.h"
#include "func1.h"
//#include "func1.c"
#include "func2.h"
#include "usedtype.h"

void comp1(void)
{
	STR c;
	c.info="This is from comp1:\n";
	printf("%s", c.info);
	func1();
	func2();
	printf("\n");
}
