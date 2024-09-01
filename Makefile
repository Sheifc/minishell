# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 05:20:05 by sheferna          #+#    #+#              #
#    Updated: 2024/09/01 10:00:36 by svilla-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR       =	libft/
LIBS            =	-lft -lreadline

NAME            =	minishell

CC              =	gcc
CFLAGS          =	-Wall -Werror -Wextra -Iincludes -Ilibft/includes -g

RM              =	rm -rf

SRC_DIR         =	src/
EXEC_DIR        =	$(SRC_DIR)executor/
PARSER_DIR      =	$(SRC_DIR)parser/
OBJ_DIR         =	obj/
OBJ_EXEC_DIR    =	$(OBJ_DIR)executor/
OBJ_PARSER_DIR  =	$(OBJ_DIR)parser/

FILES_SRC       =	main.c

FILES_PARSER	=	parser_utils.c										\
					command.c command_utils.c command_handles_a.c		\
					command_handles_b.c command_handles_utils.c			\
					command_exe.c command_extra.c						\
					stack_operations.c stack_pipes.c					\
					ast.c ast_utils.c ast_handles.c 					\
					syntax.c syntax_utils.c								\
					token.c token_utils.c token_verify.c				\
					token_handles.c token_handles_utils.c				\
					token_preprocess.c token_preprocess_utils.c 		\
					enviroment.c enviroment_utils.c	enviroment_check.c	\
					error.c												\
					wildcard_bonus.c wildcard_utils_bonus.c				\
					wildcard_preprocess_bonus.c

FILES_EXEC      =	init.c						\
					signals.c					\
					signals_heredoc.c			\
					exec_builtins.c				\
					free_env.c					\
					free_cmd.c					\
                	free_all.c					\
                	list_utils.c				\
                	key_value.c					\
                	echo.c						\
                	pwd.c						\
                	cd.c						\
					cd_utils.c					\
					cd_chdir.c					\
					cd_update_vars.c			\
                	env.c						\
					env_error_handle.c			\
                	exit.c						\
                	export.c					\
					export_utils.c				\
                	unset.c						\
					checker_pre_exec.c			\
					path.c						\
					set_fds.c					\
					set_tmp_fds.c				\
                	executor.c					\
					exec_utils.c				\
                	exec_one_cmd.c				\
					exec_multi_cmds.c			\
					exec_pipeline.c				\
					exec_and_or_bonus.c			\
					exec_parenthesis_bonus.c	\
					exec_redir.c				\
                	printing.c					\
					exec_error.c

SRC_MAIN        =	$(addprefix $(SRC_DIR),$(FILES_SRC))
SRC_PARSER      =	$(addprefix $(PARSER_DIR),$(FILES_PARSER))
SRC_EXEC        =	$(addprefix $(EXEC_DIR),$(FILES_EXEC))
SRC             =	$(SRC_MAIN) $(SRC_EXEC) $(SRC_PARSER)

OBJ_MAIN        =	$(SRC_MAIN:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
OBJ_PARSER      =	$(SRC_PARSER:$(PARSER_DIR)%.c=$(OBJ_PARSER_DIR)%.o)
OBJ_EXEC        =	$(SRC_EXEC:$(EXEC_DIR)%.c=$(OBJ_EXEC_DIR)%.o)
OBJ_SRC         =	$(OBJ_MAIN) $(OBJ_EXEC) $(OBJ_PARSER)

vpath %.c $(SRC_DIR) $(PARSER_DIR) $(EXEC_DIR)

$(OBJ_PARSER_DIR)%.o: $(PARSER_DIR)%.c
	@mkdir -p $(OBJ_PARSER_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_EXEC_DIR)%.o: $(EXEC_DIR)%.c
	@mkdir -p $(OBJ_EXEC_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS)$(INCLUDES)  -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_SRC)
	@$(MAKE) -s all bonus printf gnl -C $(LIBFT_DIR)
	$(CC) $(OBJ_SRC) -L $(LIBFT_DIR) $(LIBS) -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) token
	@$(RM) ast
	@$(RM) cmd
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# --------------------------------------------------
#             Test compilation process             |
# --------------------------------------------------

# ***** Test token *****
FILES_SRC_TOKEN	=	test_token.c
SRC_MAIN_TOKEN	=	$(addprefix $(PARSER_DIR),$(FILES_SRC_TOKEN))
SRC_TOKEN		=	$(SRC_MAIN_TOKEN) $(SRC_EXEC) $(SRC_PARSER)
OBJ_MAIN_TOKEN	=	$(SRC_MAIN_TOKEN:$(PARSER_DIR)%.c=$(OBJ_PARSER_DIR)%.o)
OBJ_SRC_TOKEN	=	$(OBJ_MAIN_TOKEN) $(OBJ_EXEC) $(OBJ_PARSER)

$(OBJ_MAIN_TOKEN)%.o: $(PARSER_DIR)%.c | directories
	@$(CC) $(CFLAGS) -c $< -o $@

token: $(OBJ_SRC_TOKEN)
	@$(MAKE) -s all bonus printf gnl -C $(LIBFT_DIR)
	$(CC) $(OBJ_SRC_TOKEN) -L $(LIBFT_DIR) $(LIBS) $(LDFLAGS) -o $@

# ***** Test ast *****
FILES_SRC_AST	=	test_ast.c
SRC_MAIN_AST	=	$(addprefix $(PARSER_DIR),$(FILES_SRC_AST))
SRC_AST			=	$(SRC_MAIN_AST) $(SRC_EXEC) $(SRC_PARSER)
OBJ_MAIN_AST	=	$(SRC_MAIN_AST:$(PARSER_DIR)%.c=$(OBJ_PARSER_DIR)%.o)
OBJ_SRC_AST		=	$(OBJ_MAIN_AST) $(OBJ_EXEC) $(OBJ_PARSER)

$(OBJ_MAIN_AST)%.o: $(PARSER_DIR)%.c | directories
	@$(CC) $(CFLAGS) -c $< -o $@

ast: $(OBJ_SRC_AST)
	@$(MAKE) -s all bonus printf gnl -C $(LIBFT_DIR)
	$(CC) $(OBJ_SRC_AST) -L $(LIBFT_DIR) $(LIBS) $(LDFLAGS) -o $@

# ***** Test command *****
FILES_SRC_CMD	=	test_command.c
SRC_MAIN_CMD	=	$(addprefix $(PARSER_DIR),$(FILES_SRC_CMD))
SRC_CMD			=	$(SRC_MAIN_CMD) $(SRC_EXEC) $(SRC_PARSER)
OBJ_MAIN_CMD	=	$(SRC_MAIN_CMD:$(PARSER_DIR)%.c=$(OBJ_PARSER_DIR)%.o)
OBJ_SRC_CMD		=	$(OBJ_MAIN_CMD) $(OBJ_EXEC) $(OBJ_PARSER)

$(OBJ_MAIN_CMD)%.o: $(PARSER_DIR)%.c | directories
	@$(CC) $(CFLAGS) -c $< -o $@

cmd: $(OBJ_SRC_CMD)
	@$(MAKE) -s all bonus printf gnl -C $(LIBFT_DIR)
	$(CC) $(OBJ_SRC_CMD) -L $(LIBFT_DIR) $(LIBS) $(LDFLAGS) -o $@

directories:
	mkdir -p $(AST_OBJ_DIR) $(TOKEN_OBJ_DIR) $(CMD_OBJ_DIR)

tests: token ast cmd

# norminette src/parser/*
# norminette includes/*
# valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all -s ./minishell

.PHONY: all clean fclean re token ast cmd directories