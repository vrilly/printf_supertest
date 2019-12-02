# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    configure.ac                                       :+:    :+:             #
#                                                      +:+                     #
#    By: tjans <tjans@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2019/12/02 20:27:53 by tjans         #+#    #+#                  #
#    Updated: 2019/12/02 21:54:12 by tjans         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

AC_PREREQ([2.69])
AC_INIT([printf_supertest], [1.0.0])
AM_INIT_AUTOMAKE([-Wall -Werror])
AM_SILENT_RULES([yes])
AC_PREFIX_DEFAULT("./out")
AC_PROG_CC
AC_CHECK_LIB([ft], [ft_strlen])
AC_CHECK_LIB([ftprintf], [ft_printf], [], [
			  echo "Please use set_printf_path.sh";
			  exit 0;
			  ])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
