LIBFT_DIR       = libft/
LIBS            = -lft -lreadline

NAME            = minishell

CC              = gcc
CFLAGS          = -Wall -Werror -Wextra -Iincludes -Ilibft/includes -g #-fsanitize=address
#LDFLAGS         = -fsanitize=address
RM              = rm -rf

SRC_DIR         = src/
EXEC_DIR        = $(SRC_DIR)executor/
PARSER_DIR      = $(SRC_DIR)parser/
OBJ_DIR         = obj/
OBJ_EXEC_DIR    = $(OBJ_DIR)executor/
OBJ_PARSER_DIR  = $(OBJ_DIR)parser/

FILES_SRC       = main.c

FILES_PARSER	=	parser_utils.c										\
					command.c command_utils.c command_handles1.c		\
					command_handles2.c command_handles_utils.c			\
					command_exe.c command_extra.c						\
					stack_operations.c stack_pipes.c					\
					ast.c ast_utils.c ast_handles.c 					\
					syntax.c syntax_utils.c								\
					token.c token_utils.c								\
					token_handles.c token_handles_utils.c				\
					token_preprocess.c token_preprocess_utils.c 		\
					token_env.c											\
					error.c												\
					wildcard.c wildcard_utils.c

FILES_EXEC      = init.c				\
				  signals.c				\
				  exec_builtins.c		\
				  builtin_utils.c		\
				  free_env.c			\
				  free_token.c			\
				  free_cmd.c			\
                  free.c				\
                  list_utils.c			\
                  key_value.c			\
                  echo.c				\
                  pwd.c					\
                  cd.c					\
                  env.c					\
                  exit.c				\
                  export.c				\
				  export_utils.c		\
                  unset.c				\
				  path.c				\
				  set_fds.c				\
				  set_tmp_fds.c			\
                  executor.c			\
				  exec_utils.c			\
                  exec_one_cmd.c		\
				  exec_pipeline.c		\
				  exec_bonus.c			\
				  exec_redir.c			\
                  printing.c


SRC_MAIN        = $(addprefix $(SRC_DIR),$(FILES_SRC))
SRC_PARSER      = $(addprefix $(PARSER_DIR),$(FILES_PARSER))
SRC_EXEC        = $(addprefix $(EXEC_DIR),$(FILES_EXEC))
SRC             = $(SRC_MAIN) $(SRC_EXEC) $(SRC_PARSER)

OBJ_MAIN        = $(SRC_MAIN:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
OBJ_PARSER      = $(SRC_PARSER:$(PARSER_DIR)%.c=$(OBJ_PARSER_DIR)%.o)
OBJ_EXEC        = $(SRC_EXEC:$(EXEC_DIR)%.c=$(OBJ_EXEC_DIR)%.o)
OBJ_SRC         = $(OBJ_MAIN) $(OBJ_EXEC) $(OBJ_PARSER)

vpath %.c $(SRC_DIR) $(PARSER_DIR) $(EXEC_DIR)

# Determine OS and architecture
OS := $(shell uname)

# Check the includes and libs on macOS
ifeq ($(OS), Darwin)
INCLUDES += -I/usr/local/opt/readline/include
LIBS += -L/usr/local/opt/readline/lib
endif

# Check the includes and libs on Linux
ifeq ($(OS), Linux)
INCLUDES += -I/usr/include/readline
LIBS += -L/usr/lib
endif

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
	$(CC) $(OBJ_SRC) -L $(LIBFT_DIR) $(LIBS) $(LDFLAGS) -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) test_token
	@$(RM) test_ast
	@$(RM) test_cmd
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# --------------------------------------------------
#             Test compilation process             |
# --------------------------------------------------

TOKEN_FILES		=	test_token.c token.c token_utils.c			\
					token_handles.c token_handles_utils.c		\
					token_preprocess.c token_preprocess_utils.c \
					token_env.c									\
					error.c										\
					wildcard.c wildcard_utils.c
TOKEN_DIR		=	$(SRC_DIR)parser/
TOKEN_OBJ_DIR	=	$(OBJ_DIR)parser/
TOKEN_SRC		=	$(addprefix $(TOKEN_DIR),$(TOKEN_FILES))
TOKEN_OBJ		=	$(TOKEN_SRC:$(TOKEN_DIR)%.c=$(TOKEN_OBJ_DIR)%.o)

$(TOKEN_OBJ_DIR)%.o: $(TOKEN_DIR)%.c | directories
	@$(CC) $(CFLAGS) -c $< -o $@

test_token: $(TOKEN_OBJ)
	@$(MAKE) -s all bonus printf gnl -C $(LIBFT_DIR)
	$(CC) $(TOKEN_OBJ) -L $(LIBFT_DIR) $(LIBS) $(LDFLAGS) -o $@

AST_FILES	= 	test_ast.c ast.c ast_utils.c ast_handles.c 	\
				syntax.c syntax_utils.c						\
				token.c token_utils.c						\
				token_handles.c token_handles_utils.c		\
				token_preprocess.c token_preprocess_utils.c \
				token_env.c									\
				error.c										\
				wildcard.c wildcard_utils.c
AST_DIR		=	$(SRC_DIR)parser/
AST_OBJ_DIR	=	$(OBJ_DIR)parser/
AST_SRC		=	$(addprefix $(AST_DIR),$(AST_FILES))
AST_OBJ		=	$(AST_SRC:$(AST_DIR)%.c=$(AST_OBJ_DIR)%.o)

$(AST_OBJ_DIR)%.o: $(AST_DIR)%.c | directories
	@$(CC) $(CFLAGS) -c $< -o $@

test_ast: $(AST_OBJ)
	@$(MAKE) -s all bonus printf gnl -C $(LIBFT_DIR)
	$(CC) $(AST_OBJ) -L $(LIBFT_DIR) $(LIBS) $(LDFLAGS) -o $@

CMD_FILES	= 	test_command.c command.c command_utils.c command_handles1.c	\
				command_handles2.c command_handles_utils.c	\
				command_exe.c command_extra.c				\
				stack_operations.c stack_pipes.c			\
				ast.c ast_utils.c ast_handles.c 			\
				syntax.c syntax_utils.c						\
				token.c token_utils.c						\
				token_handles.c token_handles_utils.c		\
				token_preprocess.c token_preprocess_utils.c \
				token_env.c									\
				error.c										\
				wildcard.c wildcard_utils.c
CMD_DIR		=	$(SRC_DIR)parser/
CMD_OBJ_DIR	=	$(OBJ_DIR)parser/
CMD_SRC		=	$(addprefix $(CMD_DIR),$(CMD_FILES))
CMD_OBJ		=	$(CMD_SRC:$(CMD_DIR)%.c=$(CMD_OBJ_DIR)%.o)

$(CMD_OBJ_DIR)%.o: $(CMD_DIR)%.c | directories
	@$(CC) $(CFLAGS) -c $< -o $@

test_cmd: $(CMD_OBJ)
	@$(MAKE) -s all bonus printf gnl -C $(LIBFT_DIR)
	$(CC) $(CMD_OBJ) -L $(LIBFT_DIR) $(LIBS) $(LDFLAGS) -o $@

directories:
	mkdir -p $(AST_OBJ_DIR) $(TOKEN_OBJ_DIR) $(CMD_OBJ_DIR)

# norminette src/parser/token*
# norminette src/parser/wildcard*
# norminette src/parser/ast*
# norminette src/parser/syntax*
# norminette src/parser/command*
# norminette src/parser/test_*
# norminette includes/token.h includes/ast.h includes/syntax.h includes/command.h includes/stacks.h

.PHONY: all clean fclean re test_token test_ast directories