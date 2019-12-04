# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    configure.ac                                       :+:    :+:             #
#                                                      +:+                     #
#    By: tjans <tjans@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2019/12/02 20:27:53 by tjans         #+#    #+#                  #
#    Updated: 2019/12/04 17:14:25 by tjans         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

AC_PREREQ([2.69])
AC_INIT([printf_supertest], [1.1.0])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AM_SILENT_RULES([yes])
AC_PREFIX_DEFAULT("./out")
AC_PROG_CC
AC_CHECK_LIB([ft], [ft_strlen])
AC_CHECK_LIB([ftprintf], [ft_printf], [], [
				echo "Please use set_printf_path.sh";
				exit 0;
				])
AC_CHECK_PROG([LEAKS_AVALIABLE],[leaks], [yes])
AS_IF([test "x$LEAKS_AVALIABLE" = xyes],
	[AC_DEFINE([LEAKS_AVALIABLE], [1],
		["Define LEAKS_AVALIABLE when leaks is present"])])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
