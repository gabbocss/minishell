#ifndef MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>


typedef enum token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_END,
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
} t_t;


t_token	*tokens(char *input);

# endif