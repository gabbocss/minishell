#ifndef MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

#include <fcntl.h>
#include <sys/wait.h>
//#include <string.h>

#include <signal.h>

extern int g_exit_status;

typedef enum token_type
{
	METACHAR,
	TOKEN_DEFAULT,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_END,
	TOKEN_DOUBLE_REDIR_IN,
	TOKEN_DOUBLE_REDIR_OUT,
	TOKEN_VAR,
	TOKEN_QUOTE,
} t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	bool			single_quote;
	bool			double_quote;
	char			*input;
	char			*start;
	size_t			pos;
	size_t			anchor_pos;
	bool			error;
	size_t			quote;
	int				token_quote;
} t_t;

typedef struct s_command 
{
    char				**argv;        
    char				*infile;       
    char				*outfile;      
    int					redir_in;      
    int					redir_out;
	int					token_quote;
    struct s_command	*next;
} t_command;

t_t	*tokens(char *input);
void		quotes(t_t *t);
void		metacharacters(t_t *t, t_t **token_list);
void		open_quotes(t_t *t, t_t **token_list);
void		add_token(t_t *t, t_t **token_list);
void		initStruct(t_t *t);
void		add_token_2(t_t *new_token, t_t **token_list);
int			alloc_new_token(t_t **new_token, int len);
void		triple_meta(t_t *t, t_t **token_list);
t_t			*set_metachar_type(t_t **token_list);
void		parse(t_t *token);
t_command	*parse_commands(t_t *token);
void		parse_commands_2(t_command **current, t_command **head, t_t *token);
void		add_argument(t_command *cmd, char *arg, int token_quote);
void 		redir_in(t_command *cmd, t_t *token);
void		redir_out(t_command *cmd, t_t *token);
void		add_pipe(t_command **head, t_command *new_node);
void print_commands(t_command *cmd); // per i test, cancellare alla fine
void 		free_command_list(t_command *cmd);
void 		free_token_list(t_t *token);
void		free_command(t_command *cmd);
bool		check_errorNclose(t_command **head, t_command *current, bool error);
void		check_pipes(t_t *t, t_t **token_list);
void    	check_pipes_2(t_t *t, t_t **token_list, size_t start, char *word);
void		add_custom_token(char *value, int type, t_t **token_list);
void		is_var(t_t *t, t_t **token_list);
void		is_var_2(t_t *t, t_t **token_list);
void		free_quotes(char *str1, char *str2, char *str3);
void		check_var(t_t *t);
void		new_input(t_t *t, char *exp_var, int count, int dollar);
bool		expand_exit_status(t_t *t);

typedef struct s_env
{
    char *key;
    char *value;
	int exportable;
    struct s_env *next;
} t_env;

int	builtin_cd(char **args, t_env **env);
void	builtin_env(t_env *env);
t_env	*copy_env_node(t_env *src);
t_env	*copy_env_list_sorted(t_env *env);
void	print_export(t_env *sorted);
int	handle_no_args(t_env *env);
int	handle_invalid_identifier(char *arg);
void	handle_key_value_pair(char *arg, t_env **env);
int	process_export_arg(char *arg, t_env **env);
int	builtin_export(char **args, t_env **env);
int	is_valid_identifier(const char *str);
int	unset_env(t_env **env, char *key);
int	builtin_unset(char **args, t_env **env);
void	free_env(t_env *env);
char	*get_env_value(t_env *env, const char *key);
int	mark_as_exportable(t_env **env, char *key);
t_env	*create_env_node(char *key, char *value, int exportable);
int	add_env(t_env **env, char *key, char *value, int exportable);
int	update_env(t_env **env, const char *key, const char *value);
void	update_env_var(t_env **env, const char *key, const char *value);
int	env_exists(t_env *env, const char *key);
void	insert_sorted(t_env **sorted, t_env *new_node);
int builtin_pwd(void);
int is_option_n(const char *str);
int builtin_echo(t_command *cmd);

void apply_redirections(t_command *cmd);
void apply_redir_in1(t_command *cmd);
void apply_redir_in2(void);
void apply_redir_out1(t_command *cmd);
void apply_redir_out2(t_command *cmd);
char *mini_getline(const char *prompt);
void create_heredoc_open(const char *delimiter);
void create_heredoc_effective(const char *delimiter);
void handle_child_process(t_command *cmd, int prev_fd, int pipe_fd[], t_env *env);
void handle_parent_process(int *prev_fd, int pipe_fd[]);
void setup_pipe(t_command *cmd, int pipe_fd[]);
void fork_process(pid_t *pid);
void wait_for_children(void);
void exec_command_list(t_command *cmd_list, t_env *env);
char *get_command_path(char *cmd, t_env *env);
char	**convert_env_list_to_array(t_env *env);
bool is_builtin(t_command *cmd);
//void	exec_single_simple_command(t_command *cmds, t_env **env);
void	exec_builtin(t_command *cmds, t_env **env);
void	exec_single_non_builtin(t_command *cmds, t_env **env);
void	builtin_exit(char **args);


# endif