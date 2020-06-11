#include "Utils.h"
#include "Win32.h"
//#include <stdio.h>
#include <sstream>
#include <iostream>
#include <iomanip>

void ErrorBox(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	char* message = new char[128];
	int result = vsnprintf(message, 128, format, args);
	if (result < 0)
		goto end;
	if (++result > 128)
	{
		delete[] message;
		message = new char[result];
		if (0 > vsnprintf(message, result, format, args))
			goto end;
	}
	MessageBoxA(NULL, message, G3DTZ_NAME, MB_ICONERROR);
end:
	delete[] message;
	va_end(args);
}

void ErrorBox(const wchar* format, ...)
{
	va_list args;
	va_start(args, format);
	wchar* message = new wchar[128];
	int result = _vsnwprintf(message, 128, format, args);
	if (result < 0)
		goto end;
	if (++result > 128)
	{
		delete[] message;
		message = new wchar[result];
		if (0 > _vsnwprintf(message, result, format, args))
			goto end;
	}
	MessageBoxW(NULL, message, G3DTZ_NAME_W, MB_ICONERROR);
end:
	delete[] message;
	va_end(args);
}

char float_buf[20];
const char* Precision(float value)
{
	int length = sprintf(float_buf, "%.2f", value) - 1;
	if (float_buf[length] == '0')
		float_buf[length] = '\0';
	return float_buf;
}
const char* Precision3(float value)
{
	int length = sprintf(float_buf, "%.3f", value) - 1;
	if (float_buf[length] == '0')
	{
		if (float_buf[length - 1] == '0')
			float_buf[length - 1] = '\0';
		else
			float_buf[length] = '\0';
	}
	return float_buf;
}
const char* Precision5(float value)
{
	int length = sprintf(float_buf, "%.5f", value);
	for (int i = 0; i < 4; ++i)
	{
		if (float_buf[--length] != '0')
			break;
		float_buf[length] = '\0';
	}
	return float_buf;
}
const char* PrecisionAny(float value)
{
	static std::string result;
	result = (std::stringstream() << value).str();
	if (result.find('.') == std::string::npos)
		if (result.find('e') == std::string::npos)
			result += ".0";
	return result.c_str();
}