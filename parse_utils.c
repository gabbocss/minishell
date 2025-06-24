#include "minishell.h"
#include "libft.h"

t_command	*parse_commands(t_t *token)
{
	t_command *head;
    t_command *current;

	head = NULL;
	current = NULL;
	while(token)
	{
		if (!current)
		{
			current = malloc(sizeof(t_command));
			ft_bzero(current, sizeof(t_command));
		}
		if (token->type == TOKEN_WORD)
			add_argument(current, token->value);
		else if (token->type == TOKEN_REDIR_IN
		|| token->type == TOKEN_DOUBLE_REDIR_IN)
			redir_in(current, token->value, token->next->value);
		else
			parse_commands_2(&current, &head, token);
		token = token->next;
	}
}

void	*parse_commands_2(t_command **current, t_command **head, t_t *token)
{
	if (token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_DOUBLE_REDIR_OUT)
			redir_out(current, token->value, token->next->value);
		else if (token->type == TOKEN_PIPE)
			add_pipe(&head, current);
}

void	add_argument(t_command *cmd, char *arg)
{
	int	count;
	char **new_argv;
	int	i;

	i = 0;
	new_argv = NULL;
	count = 0;
	if (cmd->argv)
		while(cmd->argv[count])
			count++;
	new_argv = malloc(sizeof(char *) * (count +2));
	while (i < count)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[count] = ft_strdup(arg);
	new_argv[count +1] = NULL;	// richiesto da execve
	free(cmd->argv);
	cmd->argv = new_argv;
}
