/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 14:28:48 by tjans         #+#    #+#                 */
/*   Updated: 2019/12/07 23:55:55 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "test.h"
#include "config.h"

int		check_testbins()
{
	FILE	*printer_ft, *printer_std;

	printer_ft = fopen("printer_ft", "rb");
	if (!printer_ft)
		return (0);
	fclose(printer_ft);
	printer_std = fopen("printer_std", "rb");
	if (!printer_std)
		return (0);
	fclose(printer_std);
	return (1);
}

void	log_msg(char *msg, int verbose)
{
	static FILE	*logfile = NULL;
	char		*logbuff;

	if (logfile == NULL)
		logfile = fopen("test_output.txt", "a");
	asprintf(&logbuff, "%s", msg);
	fputs(logbuff, logfile);
	if (verbose)
		printf("%s", logbuff);
	free(logbuff);
}

void	log_test(t_testprogress *test)
{
	char	*logent;

	asprintf(&logent,
			"\nTest: %s:%s\nret ft(%d):\n%s\nret std(%d):\n%s\n---\n",
			test->test_section,
			test->test_fmt,
			test->rf_ft,
			test->ret_ft,
			test->rf_std,
			test->ret_std);
	if (strcmp(test->ret_ft, test->ret_std) || test->rf_ft != test->rf_std)
		log_msg(logent, 1);
	else
		log_msg(logent, 0);
	free(logent);
}

void	print_version(FILE *fp)
{
	char	buf[256];
	int		n;

	n = 0;
	while (n < 2)
	{
		fgets(buf, 256, fp);
		log_msg(buf, 1);
		n++;
	}
}

int		skip_to_test(FILE *fp, char *ret, t_testprogress *tp)
{
	if (strncmp(ret, "fmt:", 4) == 0)
		return (1);
	while (fgets(ret, 5000, fp))
	{
		if (strncmp(ret, "fmt:", 4) == 0)
		{
			strncpy(tp->test_fmt, ret + 4, 256);
			return (1);
		}
		if (*ret == '$')
			strncpy(tp->test_section, ret + 1, 256);
		if (strncmp(tp->test_section, "LEAKCHECK", 9) == 0)
			return (1);
	}
	return (0);
}

int		run_next_test(t_testprogress *tp)
{
	char	atoi_buff[64];

	if (	!skip_to_test(tp->p_ft, tp->ret_ft, tp) ||
			!skip_to_test(tp->p_std, tp->ret_std, tp))
		return (0);
	if (strncmp(tp->test_section, "LEAKCHECK", 9) == 0)
	{
		while (fgets(tp->ret_ft, 5000, tp->p_ft))
			log_msg(tp->ret_ft, 1);
		return (0);
	}
	if (!fgets(tp->ret_ft, 5000, tp->p_ft))
		return (0);
	if (!fgets(tp->ret_std, 5000, tp->p_std))
		return (0);
	if (!fgets(atoi_buff, 64, tp->p_ft))
		return (0);
	tp->rf_ft = atoi(atoi_buff + 1);
	if (!fgets(atoi_buff, 64, tp->p_std))
		return (0);
	tp->rf_std = atoi(atoi_buff + 1);
	return (1);
}

void	run_tests()
{
	char			ret[256];
	t_testprogress *tp;

	tp = calloc(1, sizeof(t_testprogress));
	tp->p_ft = popen("./printer_ft", "r");
	tp->p_std = popen("./printer_std", "r");
	log_msg("FT printer version:\n", 1);
	print_version(tp->p_ft);
	log_msg("STD printer version:\n", 1);
	print_version(tp->p_std);
	while (run_next_test(tp))
		log_test(tp);
	pclose(tp->p_ft);
	pclose(tp->p_std);
}

int 	main(int argc, char *argv[])
{
	if (!check_testbins())
	{
		fprintf(stderr,
				"One of the test binaries is missing, please recompile\n");
		return (1);
	}
	log_msg(PACKAGE_STRING, 1);
	log_msg("\n", 1);
	run_tests();
	return (0);
}
