# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile.am                                        :+:    :+:             #
#                                                      +:+                     #
#    By: tjans <tjans@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2019/12/02 21:16:07 by tjans         #+#    #+#                  #
#    Updated: 2019/12/04 17:09:01 by tjans         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

bin_PROGRAMS = printer_std printer_ft test_ftprintf

printer_std_SOURCES = printer.c

printer_ft_SOURCES = printer.c
printer_ft_CFLAGS = -D PRINTF_FT

test_ftprintf_SOURCES = test.c

include_HEADERS = test.h

dist_bin_SCRIPTS = set_printf_path.sh
dist_doc_DATA = README a.txt
