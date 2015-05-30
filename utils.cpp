#include <stdarg.h>
#include <iostream>

std::string			args2string(int data, ...){
	std::string		ret;
	va_list			args;
	va_start(args, data);

	for (int i = 0; i < data; i++)
		ret += " " + std::to_string(va_arg(args, int));
	va_end(args);
	return (ret);
}
