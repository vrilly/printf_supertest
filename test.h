/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tjans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 14:40:24 by tjans         #+#    #+#                 */
/*   Updated: 2019/12/04 16:31:38 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H
# include <stdio.h>

typedef struct	s_testprogress
{
	char	test_section[256];
	char	test_fmt[256];
	char	ret_std[5000];
	char	ret_ft[5000];
	FILE	*p_ft;
	FILE	*p_std;
}				t_testprogress;

#endif
