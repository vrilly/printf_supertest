#!/bin/sh
# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    set_printf_path.sh                                 :+:    :+:             #
#                                                      +:+                     #
#    By: tjans <tjans@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2019/12/02 21:33:20 by tjans         #+#    #+#                  #
#    Updated: 2019/12/02 21:33:20 by tjans         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

export LDFLAGS="-L$1"
[ -d "$1/libft" ] && export LDFLAGS="$LDFLAGS -L$1/libft"
echo $LDFLAGS
./configure
