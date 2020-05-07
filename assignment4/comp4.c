#include <stdio.h>
#include "func1.h"
#include "func3.h"
#include "func2.h"
#include "comp4.h"

void comp4(void)
{
	printf("this is from comp4. the combined comp:\n");
	func1();
	func2();
	func3();
}
