/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 18:37:59 by tjans         #+#    #+#                 */
/*   Updated: 2019/12/04 14:25:50 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "config.h"

int			ft_printf(const char *fmt, ...);

typedef		int (*printf_t)(const char *, ...);

#ifdef PRINTF_FT
printf_t	pf_ptr = ft_printf;
#else
printf_t	pf_ptr = printf;
#endif

static int	parrot_shuffler(char **fmt, char c)
{
	const char	fmtstr[][256] =
	{
		"",
		"%%%c",
		"Hello world %%%c",
		"%%%cMerp",
		"OvO%%%cOwO",
		"Really long string with a %%%c conversion but not \n really long tbh",
		"No conversions in here mate",
		"Flag test %%.14%c",
		"Flag test %%-.8%c",
		"Flag test %%-0.7%c",
		"Flag test %%.%c",
		"Flag test %%.1%c",
		"Flag test %%40%c",
		"Flag test %%-40%c",
		"Flag test %%040%c",
		"Flag test %%40.8%c",
		""
	};
	static int	f_pos = 0;

	if (f_pos != 0 && fmtstr[f_pos][0] == '\0')
	{
		f_pos = 0;
		return (0);
	}
	if (*fmt != NULL)
	{
		free(*fmt);
		*fmt = NULL;
	}
	asprintf(fmt, fmtstr[f_pos], c);
	f_pos++;
	return (1);
}

static void	test_signed_int()
{
	const int	test_ints[8] =
	{
		0,
		INT_MIN,
		INT_MAX,
		-1,
		1,
		420,
		-1337,
		-13370000
	};
	int			i;
	char		*fmt;

	fmt = NULL;
	printf("\n\n$SIGNED_INT\n\n");
	i = 0;
	while (i < 8)
	{
		while(parrot_shuffler(&fmt, 'd'))
		{
			printf("\nfmt: %s\n", fmt);
			(pf_ptr)(fmt, test_ints[i]);
		}
		while(parrot_shuffler(&fmt, 'i'))
		{
			printf("\nfmt: %s\n", fmt);
			(pf_ptr)(fmt, test_ints[i]);
		}
		i++;
	}
	free(fmt);
}

static void	test_unsigned_int()
{
	const unsigned int	test_ints[9] =
	{
		0,
		INT_MIN,
		INT_MAX,
		-1,
		1,
		420,
		-1337,
		UINT_MAX,
		(unsigned int)INT_MAX + 420
	};
	int					i;
	char				*fmt;

	fmt = NULL;
	printf("\n\n$UNSIGNED_INT\n\n");
	i = 0;
	while (i < 9)
	{
		while(parrot_shuffler(&fmt, 'u'))
		{
			printf("\nfmt: %s\n", fmt);
			(pf_ptr)(fmt, test_ints[i]);
		}
		i++;
	}
	free(fmt);
}

static void	test_hex()
{
	const unsigned int	test_ints[9] =
	{
		0,
		INT_MIN,
		INT_MAX,
		-1,
		1,
		420,
		-1337,
		UINT_MAX,
		(unsigned int)INT_MAX + 420
	};
	int					i;
	char				*fmt;

	fmt = NULL;
	printf("\n\n$HEX\n\n");
	i = 0;
	while (i < 9)
	{
		while(parrot_shuffler(&fmt, 'x'))
		{
			printf("\nfmt: %s\n", fmt);
			(pf_ptr)(fmt, test_ints[i]);
		}
		while(parrot_shuffler(&fmt, 'X'))
		{
			printf("\nfmt: %s\n", fmt);
			(pf_ptr)(fmt, test_ints[i]);
		}
		i++;
	}
	free(fmt);
}

static void	test_escape()
{
	char	*fmt;

	fmt = NULL;
	printf("\n\n$ESCAPE\n\n");
	while (parrot_shuffler(&fmt, '%'))
	{
		printf("\nfmt: %s\n", fmt);
		(pf_ptr)(fmt);
	}
	free(fmt);
}

static void test_ptr()
{

	const void	*ptrs[4] =
	{
		pf_ptr,
		(void*)"string",
		(void*)ULONG_MAX,
		NULL
	};
	char		*fmt;
	int			i;

	fmt = NULL;
	printf("\n\n$POINTER\n\n");
	i = 0;
	while (i < 4)
	{
		while (parrot_shuffler(&fmt, 'p'))
		{
			printf("\nfmt: %s\n", fmt);
			(pf_ptr)(fmt, ptrs[i]);
		}
		i++;
	}
	free(fmt);
}

static void	test_char()
{
	unsigned char	c;
	char			*fmt;

	fmt = NULL;
	printf("\n\n$CHAR\n\n");
	c = 0;
	while (c < UCHAR_MAX)
	{
		while (parrot_shuffler(&fmt, 'c'))
		{
			printf("\nfmt: %s\n", fmt);
			(pf_ptr)(fmt, c);
		}
		c++;
	}
	while (parrot_shuffler(&fmt, 'c'))
	{
		printf("\nfmt: %s\n", fmt);
		(pf_ptr)(fmt, c);
	}
	free(fmt);
}

static void	test_string()
{
	char	*fmt;
	char	str[2000];
	FILE	*handle;

	fmt = NULL;
	printf("\n\n$STR\n\n");
	handle = fopen("a.txt", "r");
	while (fgets(str, 2000, handle))
		while (parrot_shuffler(&fmt, 's'))
		{
			printf("\nfmt: %s\n", fmt);
			(pf_ptr)(fmt, str);
		}
	free(fmt);
}

#ifdef LEAKS_AVALIABLE
static void	test_leaks()
{
	pid_t	pid;
	FILE	*p_leaks;
	char	*s_leaks;
	char	buff[2000];

	pid = getpid();
	printf("\n\n$LEAKCHECK MACOS\nPID: %d\n", pid);
	asprintf(&s_leaks, "leaks -quiet %d", pid);
	p_leaks = popen(s_leaks, "r");
	while (fgets(buff, 2000, p_leaks))
		printf("%s", buff);
	if (pclose(p_leaks) > 0)
		printf("\nLEAK CHECK FAILED\n");
	else
		printf("\nNO MEMLEAKS\n");
	free(s_leaks);
}
#endif

int main(int argc, char *argv[])
{
	setbuf(stdout, NULL);
	printf("PRINT TESTER. VERSION %s\n", PACKAGE_VERSION);
	#ifdef PRINTF_FT
		printf("Using ft_printf\n---\n");
	#else
		printf("Using system printf\n---\n");
	#endif
	test_signed_int();
	test_unsigned_int();
	test_hex();
	test_escape();
	test_ptr();
	test_char();
	test_string();
	#ifdef LEAKS_AVALIABLE
		test_leaks();
	#endif
	printf("\n\nFin.\n");
	return 0;
}
