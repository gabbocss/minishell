#ifndef MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <stdlib.h>



typedef enum token_type
{
	WORD,
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
} t_t;


t_t	*tokens(char *input);
void	quotes(t_t *t);
void	metacharacters(t_t *t, t_t **token_list);
void	open_quotes(t_t *t, t_t **token_list);
void	add_token(t_t *t, t_t **token_list);
void	initStruct(t_t *t);
void print_arguments(t_t *token_list); // per i test, cancellare alla fine
void	add_token_2(t_t *new_token, t_t **token_list);
int		alloc_new_token(t_t **new_token, int len);
void	triple_meta(t_t *t, t_t **token_list);
t_t		*set_metachar_type(t_t **token_list);

# endif