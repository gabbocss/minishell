#include "minishell.h"
#include "libft.h"

void	parse(t_t *token)
{
	t_command *cmd_list;

	cmd_list = NULL;
	cmd_list = parse_commands(token);

}