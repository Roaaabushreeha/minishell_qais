CC = cc
FLAGS = -Wall -Wextra -Werror -g
SRC_DIR = src
OBJ_DIR = obj

SRC = built_in/cd.c built_in/echo.c built_in/env.c built_in/env_helping.c built_in/export.c built_in/unset.c built_in/export_helping.c built_in/export_print.c\
execute/execute.c execute/execute_helping.c execute/expander.c  execute/pipex.c execute/pipex_helping.c execute/expander_utils.c execute/execute_handle.c execute/main_temp.c  execute/expnader_token.c execute/expander_main.c execute/expander_state.c execute/expander_quotes.c execute/handle_expander.c execute/main.c execute/built_in.c execute/path.c execute/get_path_env.c execute/signals.c execute/child_process.c\
helping/free.c helping/handle.c helping/handle_helping.c helping/utils.c \
parsing/cmd.c parsing/parsing.c parsing/separater.c parsing/heredoc.c parsing/heredoc_process.c parsing/heredoce_processer.c parsing/heredoc_expande.c parsing/init_heredoc.c parsing/command_process.c\
tokens/split_handle.c tokens/split_quotes.c tokens/token.c tokens/tokens_parsing.c\
free/clean.c free/free.c free/free_execution.c execute/expander_utils1.c execute/expander_utils2.c

SRC := $(addprefix $(SRC_DIR)/, $(SRC))
OBSRC := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

NAME = minishell

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBSRC)
	$(CC) $(FLAGS) $(OBSRC) -L$(LIBFT_DIR) -lft -lreadline -o $@

$(LIBFT_A):
	@echo "Making libft..."
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/built_in
	@mkdir -p $(OBJ_DIR)/execute
	@mkdir -p $(OBJ_DIR)/helping
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/tokens
	@mkdir -p $(OBJ_DIR)/free

clean:
	@make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re