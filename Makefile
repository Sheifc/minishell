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

FILES_PARSER    = init.c    	   \
                  lexer.c          \
                  tokenizator.c    \
                  setter.c         \
                  token_list.c   	\
                  printer.c        \
                  quote_stuff.c    \
                  in_out.c         \
                  expansion.c		\
				  expand_utils.c	\
                  exp_utils.c      \
                  syntaxis.c       \
				  heredoc.c 	   \
				  parser_utils.c	\
				  token.c token_handles.c token_utils.c	\
				  ast.c ast_utils.c ast_handles.c		\
				  syntax.c syntax_utils.c				\
				  wildcard.c wildcard_utils.c

FILES_EXEC      = exec_builtins.c  \
                  exec_utils.c     \
				  token_to_cmd.c   \
				  redirections.c   \
				  free_env.c 	   \
				  free_token.c	   \
				  free_cmd.c	   \
                  free.c           \
                  list_utils.c     \
                  key_value.c      \
                  echo.c           \
                  pwd.c            \
                  cd.c             \
                  env.c            \
                  exit.c           \
                  export.c         \
                  unset.c          \
                  executor.c       \
                  path.c           \
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

$(OBJ_PARSER_DIR)%.o: $(PARSER_DIR)%.c
	@mkdir -p $(OBJ_PARSER_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_EXEC_DIR)%.o: $(EXEC_DIR)%.c
	@mkdir -p $(OBJ_EXEC_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

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
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# --------------------------------------------------
#             Test compilation process             |
# --------------------------------------------------

TOKEN_FILES		=	token.c token_handles.c token_utils.c test_token.c \
					wildcard.c wildcard_utils.c
TOKEN_DIR		=	$(SRC_DIR)parser/
TOKEN_OBJ_DIR	=	$(OBJ_DIR)parser/
TOKEN_SRC		=	$(addprefix $(TOKEN_DIR),$(TOKEN_FILES))
TOKEN_OBJ		=	$(TOKEN_SRC:$(TOKEN_DIR)%.c=$(TOKEN_OBJ_DIR)%.o)

$(TOKEN_OBJ_DIR)%.o: $(TOKEN_DIR)%.c | directories
	@$(CC) $(CFLAGS) -c $< -o $@

test_token: $(TOKEN_OBJ)
	@$(MAKE) -s all bonus printf gnl -C $(LIBFT_DIR)
	$(CC) $(TOKEN_OBJ) -L $(LIBFT_DIR) $(LIBS) -o $@

AST_FILES	= 	ast.c ast_utils.c ast_handles.c test_ast.c token.c token_handles.c \
				token_utils.c syntax.c syntax_utils.c wildcard.c wildcard_utils.c
AST_DIR		=	$(SRC_DIR)parser/
AST_OBJ_DIR	=	$(OBJ_DIR)parser/
AST_SRC		=	$(addprefix $(AST_DIR),$(AST_FILES))
AST_OBJ		=	$(AST_SRC:$(AST_DIR)%.c=$(AST_OBJ_DIR)%.o)

$(AST_OBJ_DIR)%.o: $(AST_DIR)%.c | directories
	@$(CC) $(CFLAGS) -c $< -o $@

test_ast: $(AST_OBJ)
	@$(MAKE) -s all bonus printf gnl -C $(LIBFT_DIR)
	$(CC) $(AST_OBJ) -L $(LIBFT_DIR) $(LIBS) -o $@

directories:
	mkdir -p $(AST_OBJ_DIR) $(TOKEN_OBJ_DIR)

# norminette src/parser/token.c src/parser/token_handles.c src/parser/token_utils.c
# norminette src/parser/wildcard.c src/parser/wildcard_utils.c
# norminette src/parser/ast.c src/parser/ast_handles.c src/parser/ast_utils.c
# norminette src/parser/syntax.c src/parser/syntax_utils.c
# norminette src/parser/test_token.c src/parser/test_ast.c
# norminette includes/token.h includes/ast.h includes/syntax.h

.PHONY: all clean fclean re test_token test_ast directories