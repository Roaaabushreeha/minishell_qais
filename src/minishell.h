/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:36:10 by jalqam            #+#    #+#             */
/*   Updated: 2025/05/21 15:48:29 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
extern volatile sig_atomic_t	g_signals_status;

typedef enum s_enum
{
	WORD,	
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	DQUOTE,
	DELIMITER,
	SQUOTE,
	COMMAND,
	INFILE,
	OUTFILE,
	ARGS
}	t_enum;

typedef struct s_token
{
	char			*value;
	t_enum			type;
	int				count_pip;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_redirction
{
	char				*last_file_in;
	char				*last_file_out;
	int					valid_in;
	int					valid_out;
	int					in_fd;
	int					out_fd;
	struct s_redirction	*next;
	struct s_redirction	*prev;
}	t_redirction;
typedef struct s_cmd
{
	char			*temp;
	char			**args;
	int				f;
	int				flag_heredoc;
	int				command_num;
	int				cmd_count;
	char			*type;
	struct s_cmd	*next;
	int				pid;
	int				last_pid;
	int				prev;
	int				fd_in;
	int				fd_out;
	int				saved_stdout;
	int				saved_stdin;
	int				error;
}	t_cmd;
typedef struct s_split
{
	size_t			i;
	size_t			j;
	int				in_quotes;
	char			quote_char;
	char			*new_word;
	char			**word_splitted;
}	t_split;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	char			*pwd;
	int				exit_status;
	int				reset_flag;
}	t_env;

typedef struct s_quote_state
{
	char			*result;
	char			*value;
	int				i;
	int				inside_double;
	int				inside_single;
}	t_quote_state;
typedef struct s_quote_handler
{
	char	*str;
	int		*i;
	char	**result;
	int		*in_squotes;
	int		*in_dquotes;
}	t_quote_handler;

typedef struct s_expander_state
{
	char	*str;
	int		idx;
	char	*result;
	t_env	*env;
	int		in_dquotes;
	int		in_squotes;
}	t_expander_state;
typedef struct s_command
{
	char			*cmd;
	struct s_command	*next;
}	t_command;

typedef struct s_pip
{
	pid_t			*pid;
	int				old_fd;
	char			*cmd;
	char			*path;
}	t_pip;

typedef struct s_pipe_data
{
	int				fd[2];
	int				*prev_pipe;
	int				cmd_index;
}	t_pipe_data;

typedef struct s_fork_data
{
	t_cmd			*cmd;
	int				fd[2];
	int				*prev_pipe;
	t_env			*env;
	int				index;
	t_token			*tokens;
}	t_fork_data;

typedef struct s_pipe_fds
{
	int				fd[2];
	int				prev_pipe[2];
}	t_pipe_fds;

int		execute_commands_pip(t_cmd *cmd, t_env *env, t_token *tokens,
			int prev_pipe[2]);
int		handle_fork_error(t_cmd *cmd, t_env *env, t_token *tokens,
			t_pipe_fds *pipes);
char	*process_command_arg(t_token *token, int is_first_arg,
			t_env *env);
int		add_command_arg(t_cmd *new_cmd, t_token *token,
			int *count_cmd, t_env *env);
int		clean_files(t_cmd *cmds);
int		handle_redirection(t_token **token, t_cmd *new_cmd,
			t_env *env);
int		init_validate_redirection(t_token *token);
int		init_handle_output_redirection(t_cmd *cmd, const char *filename,
			int is_append);
int		save_stdout_and_redirect(t_cmd *cmds, int *saved_stdout);
int		init_handle_input_redirection(t_cmd *cmd, const char *filename);
int		handle_single_command(t_cmd *cmd, t_env *env, t_token *token, int *flag);
char	*get_path_from_env(char *cmd, t_env *env);
char	**env_to_array(t_env *env);
void	cleanup_and_exit(t_token *tokens, t_cmd *cmd,
			t_env *env, int exit_code);
char	*clean_delimiter(char *delimiter);
int		is_quoted_delimiter(char *delimiter);
int		is_builtin_commands(t_cmd *cmd);
t_token	*new_token(char *value);
void	add_token(t_token **head, char *value);
t_token	*tokenize(char *input);
void	print_tokens(t_token *head);
void	free_tokens(t_token *head);
void	free_tokens_split(char **token_split);
void	cleanup_command_list(t_cmd *cmd_list);
int		right_command_check(char *command);
char	**our_split(char *word);
int		ft_strcmp(const char *s1, const char *s2);
void	clean_single(t_cmd *cmd, int saved_stdout, int status);
char	**split_with_quotes(char *str);
t_cmd	*init_cmd(void);
int		handle_pwd(void);
void	print_sorted_env(t_env *sorted);
void	swap_nodes(t_env *a, t_env *b);
t_env	*create_env_copy_node(t_env *env);
void	sort_env_list(t_env *sorted);
void	write_heredoc_expanded(int fd, char *buffer, char *expanded, t_env *env);
int		check_heredoc_exit(char *buffer, t_env *env);
void	write_heredoc_line(int fd, char *buffer, int quoted, t_env *env);
char	*get_key(char *var);
int		is_valid_export(char *arg);
void	handle_invalid_export(char *arg, t_env *env, int *i);
int		handle_existing_var(t_env *env, char *key, char *arg, int *i);
int		add_new_var(t_env **env, t_env **last, char *arg, int *i);
void	handle_quote_states(char c, int *in_double, int *in_single);
int		check_token_quotes(t_token *temp);
void	handle_token_expansion(t_token *temp, t_env *env, char **expanded);
void	handle_token_quotes(t_token *temp, char **expanded);
int		handle_mixed_quote_char(char c, int *inside_double,
			int *inside_single, int *i);
			char    *handle_dollar_param(char *str, int *i);
int handle_special_param(char *str, int *i, char **result, t_env *env);
int expand_env_var(char *str, int *i, char **result, t_env *env, int in_dquotes);
int toggle_quotes(char c, int *in_squotes, int *in_dquotes);
// char *append_char_to_result(char *result, char c);
int handle_and_expand(char *str, int *i, char **result, t_env *env, int *quotes);
char	*handle_mixed_quotes(t_token *token);
int		append_char_to_string(char **result, char c);
char	*ft_strjoin_char(char *str, char c);
// void	skip_leading_whitespace(const char *str, int *i);
void	handle_char(char *result, int *j, int *space, char c);
char	*get_exit_status(t_env *env);
int		handle_quote_state(t_quote_handler *handler);
int		handle_exit_status_expansion(char *str, int *i,
			char **result, t_env *env);
 //void	append_char_to_result_q(char **result, char c);
 char   *append_char_to_result(char *result, char c);
// int		handle_special_param(char *str, int *i, char **result);
void	init_expander_state(t_expander_state *exp, t_token *token, t_env *env);
int		handle_expander_quotes(t_expander_state *exp);
int		handle_variable_expansion(t_expander_state *state);
char	*handle_dollar_expander(t_token *token, t_env *env);
char	*handle_twoquotes(t_token *token);
int		handle_single_quote_char(char c, int *inside_quotes, int *i);
void	cleanup_resources(t_env *env, t_token *tokens,
			t_cmd *temp);
void	split_quotes(char c, int *in_quotes, char *quote_char);
void	wait_for_children(int count);
void	cleanup_heredocs(t_cmd *temp);
void	init_split_vars(t_split *s, char *word);
void	free_result(char **result, size_t j);
void	skip_spaces(char *str, size_t *i);
void	handle_quotes_parse(char *str, size_t *i, int *in_quotes,
			char *quote_char);
char	*extract_word(char *str, size_t *i);
void	text_error(int which);
 //void	append_char_to_result(char **result, char c);
// void handle_quote_state(t_dollar_exp *exp);
int		count_pip(t_token *token);
void	split_chars(char *word, char *new_word, size_t *i, size_t *j);
t_cmd	*command(int cmd_num, t_token **token, t_env *env);
t_cmd	*separator(t_token *token, t_env *env);
void	print_commands(t_cmd *cmd);
void	get_built_in_type(t_token *token);
void	define_word(t_token *token);
int		execute_commands(t_cmd *cmd, t_env *env,
			t_token *token);
void	echo_command(t_cmd *cmds, t_env *env);
void	exit_command(t_cmd *cmds, t_env *env, t_token *token);
void	env_print(t_env *env);
t_env	*create_env_node(char *env_var);
void	free_env_list(t_env *env);
t_env	*init_envp(char **env_list);
void	free_commands(t_cmd *cmd);
int		export_command(t_cmd *cmd, t_env **env);
int		print_export_command(t_env *env);
int		expander_main(t_token *token, t_env *env);
char	*handle_mixed_quotes(t_token *token);
void	cleanup_iteration(char *readline_shell, char *pwd,
			t_token *tokens, t_cmd *cmd);
void	free_cmd(t_cmd *cmd);
int		check_fd_validity(int fd);
int		check_quotes_num(t_token *token);
char	*handle_onequote_expander(t_token *token);
char	*handle_twoquotes(t_token *token);
t_env	*find_env_node(char *key, t_env *env);

void	update_env_value(t_env *node, char *var);
void	append_node(t_env **env, t_env **last, t_env *new_node);
void	free_env_node(t_env *node);
int		unset_command(t_cmd *cmd, t_env **env);
int		cd_command(t_cmd *cmds, t_env *env);
int		ft_isnumeric(char *str);
char	*my_env(const char *key, char **envp);
int		num_pip(t_token *token);
void	ft_exit(char *path, char **s_cmd, int which);
void	error_handel(void);
void	ft_free(char **s_cmd);
void	free_function(char **s_cmd, char **paths);
int		get_cmd_execution(t_cmd *cmd, t_env *env,
			t_token *tokens);
int		is_redirect(char *value);
int		init_fork(t_fork_data *fork_data);
char	*handle_dollar_expander(t_token *token, t_env *env);
t_env	*copy_env_list(t_env *env);
char	*epur_string(char *str);
char	*clean_quotes(char *str);
char	*get_env_value(t_env *env, char *key);
int		handle_heredoc(char *delimiter, t_cmd *cmd, t_env *env);
// char	*handle_dollar_param(char *str, int *i, int start);
void	expand_echo_args(t_cmd *cmds, t_env *env);
int		initredirction(t_token *token, t_cmd *cmd, t_env *env);
int		builtin_commands(t_cmd *cmds, t_env *env, int *flag);
int		child_process(t_cmd *cmd, t_env *env, int *fd,
			t_token *tokens);
char	*expand_variables(char *str, t_env *env, int i);
char	*process_var_value(char *var_value, int in_dquotes);
char	*extract_var_name(char *str, int *i);
void	sigint_handler(int sig);
void	heredoc_signal_handler(int sig);
void	child_signal(int sig);
void	signal_nnl(int sig);
void	signal_handler(int mode);
int		get_cmd_execution(t_cmd *cmd, t_env *env, t_token *token);
int		handle_pipe_case(t_cmd *cmd, t_env *env, t_token *token);
int		handle_builtin_case(t_cmd *cmd, t_env *env, t_token *token);
int		handle_pipe_execution(t_cmd *cmd, t_env *env, t_token *token);
int		handle_regular_execution(t_cmd *cmd, t_env *env, t_token *token);
int		handle_builtin_execution(t_cmd *cmd, t_env *env, t_token *token);
int		execute_command_temp(t_cmd *cmd, t_env *env, t_token *token);
int		handle_null_readline(t_env *env, char *readline_shell);
int		execute_and_cleanup(char *readline_shell, t_env *env, t_token *tokens);
int		process_input(char *readline_shell, t_env *env);
int		init_minishell(int argc, char *argv[], char *envp[], t_env **env);
#endif
