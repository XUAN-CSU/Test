#include <stdio.h>
#include <stdarg.h>

void custom_log(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

int main()
{
	int a = 8;
	custom_log("This test %d %d\n", a, a);
	custom_log("This test %d %d %d\n", a, a, a);

	return 0;
}
