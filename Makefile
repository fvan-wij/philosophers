NAME		:=	philo
COMPILER	:=	cc
FLAGS		:= 	-Wall -Wextra -Werror -pthread
LIBS		:= 	./libft/libft.a
HEADERS		:= 	-I libft -I includes
SRC			:= 	main.c \
				time.c \
				init.c \
				threads.c \
				actions.c \

SRCDIR 		:= 	./src
OBJDIR 		:= 	./obj
OBJ			:= 	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))
SRC			:= 	$(addprefix $(SRCDIR)/,$(SRC))

# Colors #############################################
Black		= "\033[0;30m"		# Black
Red			= "\033[0;31m"		# Red
Green		= "\033[0;32m"		# Green
Yellow		= "\033[0;33m"		# Yellow
Blue		= "\033[0;34m"		# Blue
Purple		= "\033[0;35m"		# Purple
Cyan		= "\033[0;36m"		# Cyan
White		= "\033[0;37m"		# White
Text_Off	= "\033[0m"			# Text Style Off
Bold		= "\033[1m"			# Text Style Bold
######################################################

ifdef DEBUG
	CC += -g -fsanitize=address
endif

all: $(NAME)

run: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C libft
	@$(COMPILER) $^ $(LIBS) -o $(NAME)
	@echo $(Green) $(Bold) Philosophers compiled succesfully ✅ $(Text_Off)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(@D) 
	@echo $(Cyan) Building... [$<] $(Text_Off)
	@$(COMPILER) $(FLAGS) $(HEADERS) -c $< -o $@

$(OBJDIR):
	@mkdir $@

clean:
	@rm -rf $(OBJDIR)
	@echo $(Yellow) Cleaned object files! $(Text_Off)
	@$(MAKE) -C libft clean

fclean:	clean
	@rm -f $(NAME) 
	@echo $(Yellow) Cleaned executable! $(Text_Off)
	@$(MAKE) -C libft fclean

compile_cmd: fclean
	@compiledb make; mv *.json ./data

re:	fclean all

.PHONY:	all, clean, fclean, re
