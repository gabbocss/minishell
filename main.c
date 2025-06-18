#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char *input;
	t_token *t;

	while(1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (*input != '\0')
			add_history(input);
		token = tokens(input);


		free(input);
	}
}