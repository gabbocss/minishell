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
} t_token;


t_token	*tokens(char *imput);

# endif