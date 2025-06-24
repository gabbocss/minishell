#include "minishell.h"
#include "libft.h"

void print_arguments(t_t *token_list) {
    int i = 0;
    while (token_list) {
        printf("Arg[%d]: %-10s | Tipo: ", i, token_list->value);
        switch (token_list->type) {
            case TOKEN_WORD:
                printf("WORD\n");
                break;
            case METACHAR:
                printf("METACHAR\n");
                break;
            case TOKEN_PIPE:
                printf("TOKEN_PIPE\n");
                break;
            case TOKEN_REDIR_IN:
                printf("TOKEN_REDIR_IN\n");
                break;
            case TOKEN_DOUBLE_REDIR_IN:
                printf("TOKEN_DOUBLE_REDIR_IN\n");
                break;
            case TOKEN_REDIR_OUT:
                printf("TOKEN_REDIR_OUT\n");
                break;
            case TOKEN_DOUBLE_REDIR_OUT:
                printf("TOKEN_DOUBLE_REDIR_OUT\n");
                break;
            case TOKEN_HEREDOC:
                printf("TOKEN_HEREDOC\n");
                break;
            case TOKEN_END:
                printf("TOKEN_END\n");
                break;
            default:
                printf("TOKEN_DEFAULT\n");
        }
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
    		parse(token);
		free(input);
	}
}
