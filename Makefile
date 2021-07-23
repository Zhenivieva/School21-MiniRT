# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/02 18:08:00 by mmaryjan          #+#    #+#              #
#    Updated: 2021/02/25 21:27:29 by mmaryjan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

NAME_LIBMLX	= libmlx.dylib libmlx.a

DIR_OBJ = ./

SRCS	=   srcs/camera.c \
            srcs/canvas.c \
            srcs/check_light.c \
            srcs/check_light_cylinder.c \
            srcs/ft_strncmp.c \
            srcs/get_next_line.c \
            srcs/get_next_line_utils.c \
            srcs/image.c \
            srcs/intersec_all.c \
            srcs/intersec_cylinder.c \
            srcs/intersec_plane.c \
            srcs/intersec_sphere.c \
            srcs/intersec_square.c \
            srcs/intersec_triangle.c \
            srcs/key_press.c \
            srcs/light.c \
            srcs/lightning.c \
            srcs/lstadd_back.c \
            srcs/ft_lstadd_front.c \
            srcs/make_bmp.c \
            srcs/minirt.c \
            srcs/object_square.c \
            srcs/objects.c \
            srcs/parse_cameras.c \
            srcs/parse_cylinder.c \
            srcs/parse_lights.c \
            srcs/parse_main.c \
            srcs/parse_plane.c \
            srcs/parse_res_alight.c \
            srcs/parse_sphere.c \
            srcs/parse_square.c \
            srcs/parse_triangle.c \
            srcs/parse_utils.c \
            srcs/print_errors.c \
            srcs/raytracing.c \
            srcs/reflect.c \
            srcs/scene.c \
            srcs/set_color.c \
            srcs/shiny.c \
            srcs/vector1.c \
            srcs/vector2.c \
            srcs/vector3.c \
            srcs/vector_rot.c \

DIR_HEADERS	= ./includes/

OBJS	= $(SRCS:.c=.o)

RM		= rm -f

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -g

.c.o:
			$(CC) $(CFLAGS) -c -I $(DIR_HEADERS) $< -o $(<:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	$(MAKE) -C ./minilibx_mms
	$(MAKE) -C ./minilibx_opengl
	cp ./minilibx_mms/libmlx.dylib libmlx.dylib
	cp ./minilibx_opengl/libmlx.a libmlx.a
	$(CC) $(CFLAGS) -I $(DIR_HEADERS) $(NAME_LIBMLX) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:		clean
	make clean -C ./minilibx_mms
	make clean -C ./minilibx_opengl
	$(RM) libmlx.dylib
	$(RM) libmlx.a
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
