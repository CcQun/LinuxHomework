#include <stdio.h>
#include "func3.h"
#include "comp3.h"
#include "usedtype.h"
/*#include "func1.h"*/

void comp3(void)
{
	printf("\n");
	func3();
	STR c;
	c.info="from comp3\n";
	printf("%s", c.info);
}
