#include "minishell.h"
#include "libft.h"

void print_arguments(t_t *token_list) {
    int i = 0;
    while (token_list) {
        
            printf("Arg[%d]: %s\n", i, token_list->value);
            i++;
	
        token_list = token_list->next;
    }
}


// Uso:

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char *input;
	t_t *token;

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
		if (token)
    		print_arguments(token);
		free(input);
	}
}