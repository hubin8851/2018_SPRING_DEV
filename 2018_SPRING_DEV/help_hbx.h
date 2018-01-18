#pragma once
#include <string>

#ifndef STRNCASECMP
#define STRNCASECMP _strnicmp
#endif

inline int stringRemoveDelimiter(char delimiter, const char *string)
{
	int string_start = 0;

	while (string[string_start] == delimiter)
	{
		string_start++;
	}

	if (string_start >= (int)strlen(string) - 1)
	{
		return 0;
	}

	return string_start;
}

bool checkCmdLineFlag(const int argc, const char **argv, const char *string_ref)
{
	bool bFound = false;

	if (argc >= 1)
	{
		for (int i = 1; i < argc; i++)
		{
			int string_start = stringRemoveDelimiter('-', argv[i]);
			const char *string_argv = &argv[i][string_start];

			const char *equal_pos = strchr(string_argv, '=');
			int argv_length = (int)(equal_pos == 0 ? strlen(string_argv) : equal_pos - string_argv);

			int length = (int)strlen(string_ref);

			if (length == argv_length && !STRNCASECMP(string_argv, string_ref, length))
			{
				bFound = true;
				continue;
			}
		}
	}

	return bFound;
}

inline bool getCmdLineArgumentString(const int argc, const char **argv,
	const char *string_ref, char **string_retval)
{
	bool bFound = false;

	if (argc >= 1)
	{
		for (int i = 1; i < argc; i++)
		{
			int string_start = stringRemoveDelimiter('-', argv[i]);
			char *string_argv = (char *)&argv[i][string_start];
			int length = (int)strlen(string_ref);

			if (!STRNCASECMP(string_argv, string_ref, length))
			{
				*string_retval = &string_argv[length + 1];
				bFound = true;
				continue;
			}
		}
	}

	if (!bFound)
	{
		*string_retval = NULL;
	}

	return bFound;
}

void	printhelp()
{
	printf("春招测试用例...\n");
	printf("Options:\n");
	printf("--help\tDisplay this help menu\n");
	printf("--FileName\t读取文件的文件名，默认为data.txt\n");
	printf("--FilePath\t文件路径，默认为空\n");
}