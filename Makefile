NAME		=	libftprintf.a

SRC_DIR		=	./src
SRC			:=	ft_printf.c\
				f_get_params.c\
				f_calc_params.c\
				fs_cs.c\
				fs_diuxp.c\
				fs_wcs.c\
				fs_f.c\
				fs_e_print.c\
				fs_e_count.c\
				fs_g.c\
				fs_g_support.c\
				fs_float_utils.c\
				fs_float_print_utils.c\
				fs_float_inf_nan.c

FT_DIR		=	./ft_src
FT_SRC		:=	ft_memset.c\
				ft_calloc.c\
				ft_bzero.c\
				ft_strchr.c\
				ft_min.c\
				ft_print_num_base.c\
				ft_countdigits_base.c

OBJ		=	$(addprefix $(BIN)/, $(SRC:c=o))\
			$(addprefix $(BIN)/, $(FT_SRC:c=o))

INCLUDES	=	$(NAME:.a=.h)

BIN			=	./bin

.PHONY: all clean fclean re bonus

all bonus: $(NAME)

$(BIN):
	@mkdir $(BIN)

$(NAME): $(OBJ) $(INCLUDES)
	@ar rc $@ $?
	@ranlib $@
	@echo "$(NAME) compiled"

$(BIN)/%.o: ./*/%.c $(INCLUDES) | $(BIN)
	@gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -rf $(OBJ)
	@echo "Object files deleted"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(NAME) deleted"

re: fclean all