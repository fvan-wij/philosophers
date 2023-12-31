NAME		:=	philo
COMPILER	:=	cc -pthread
FLAGS		:= 	-Wall -Wextra -Werror
HEADERS		:= 	-I includes
SRC			:= 	main.c \
				init_data.c \
				philo_threads.c \
				monitor_thread.c \
				mutex_management.c \
				thread_management.c \
				eat_routines.c \
				utils_time.c \
				utils_misc.c \
				utils_init.c \

SRCDIR 		:= 	./src
OBJDIR 		:= 	./obj
OBJ			:= 	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))
SRC			:= 	$(addprefix $(SRCDIR)/,$(SRC))
MODE		:=

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

ifdef THREAD
	COMPILER	+= -g -fsanitize=thread
	MODE		+= $(Yellow) $(Bold) "(THREAD DEBUG MODE) Philosophers compiled succesfully ✅" $(Text_Off)
else ifdef ADDRESS
	COMPILER	+= -g -fsanitize=address
	MODE		+= $(Yellow) $(Bold) "(ADDRESS DEBUG MODE) Philosophers compiled succesfully ✅" $(Text_Off)
else ifdef VALGRIND
	COMPILER	+= -g
	MODE		+= $(Yellow) $(Bold) "(VALGRIND DEBUG MODE) Philosophers compiled succesfully ✅" $(Text_Off)
else 
	MODE 		+= $(Green) $(Bold) "Philosophers compiled succesfully ✅" $(Text_Off)
endif

all: $(NAME)

run: $(NAME)

$(NAME): $(OBJ)
	@$(COMPILER) $^ $(LIBS) -o $(NAME)
	@echo $(MODE) 

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(@D) 
	@echo $(Cyan) Building... [$<] $(Text_Off)
	@$(COMPILER) $(FLAGS) $(HEADERS) -c $< -o $@

$(OBJDIR):
	@mkdir $@

clean:
	@rm -rf $(OBJDIR)
	@echo $(Yellow) Cleaned object files! $(Text_Off)

fclean:	clean
	@rm -f $(NAME) 
	@echo $(Yellow) Cleaned executable! $(Text_Off)

compile_cmd: fclean
	@compiledb make; mv *.json ./data

re:	fclean all

.PHONY:	all, clean, fclean, re
