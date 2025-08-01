#include "minishell.h"
#include "libft.h"

void check_pipes_2(t_t *t, t_t **token_list, size_t start, char *word)
{
	size_t i;

	i = 0;
    if (start < t->pos)
    {
        word = ft_substr(t->input, start, t->pos - start);
        add_custom_token(word, TOKEN_WORD, token_list);
        free(word);
    }
    t->anchor_pos = t->pos;
    i = t->pos + 1;
    while (t->input[i] == ' ')
        i++;

    if (t->pos == 0 || t->input[i] == '\0' || t->input[i] == '|')
    {
        ft_printf("minishell: syntax error near unexpected token '|'\n");
        t->error = true;
    }
    else
    {
        t->pos++;
        add_token(t, token_list);
    }
}

void    add_custom_token(char *value, int type, t_t **token_list)
{
	t_t *new_token;

	new_token = malloc(sizeof(t_t));
	if (!new_token)
		return ;
	new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->error = false;
	new_token->next = NULL;
	if (!*token_list)
		*token_list = new_token;
	else
	{
		t_t *tmp = *token_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}
void	is_var(t_t *t, t_t **token_list)
{
	char	*var_temp;
	char	*var;
	char	*var_word;
	if (t->input[t->anchor_pos] == ' ')
		t->anchor_pos++;
    if (t->input[t->anchor_pos] == '$')
	{
		if (t->pos == t->anchor_pos)
			t->pos++;
		while (t->input[t->pos] && (ft_isalnum(t->input[t->pos]) || t->input[t->pos] == '_'))
			t->pos++;
		var_temp = malloc(t->pos - t->anchor_pos +1);
		ft_strlcpy(var_temp, t->input + (t->anchor_pos +1), (t->pos - t->anchor_pos));
		var = getenv(var_temp);
		if (!var)
		{
			free(var_temp);
			t->anchor_pos = t->pos;
			return;
		}		
		var_word = ft_strdup(var);
		add_custom_token(var_word, TOKEN_VAR, token_list);
		free(var_word);
		free(var_temp);
		t->anchor_pos = t->pos;
	}
	else
		is_var_2(t, token_list);
}

void    is_var_2(t_t *t, t_t **token_list)
{
	int		dolar;
	char	*prefix;
	char	*var;
	char	*var_token;
	char	*end_var;

	dolar = t->pos;
	prefix = malloc(t->pos - t->anchor_pos +1);
	ft_strlcpy(prefix, t->input, (t->pos - t->anchor_pos) +1);
	while (t->input[t->pos] && (ft_isalnum(t->input[t->pos]) || t->input[t->pos] == '_'))
		t->pos++;
	dolar++;
	var = malloc((t->pos - dolar) +1);
	ft_strlcpy(var, t->input + dolar, (t->pos - dolar));
	var_token = getenv(var);
	if (!var_token)
	{
		free(var);
		dolar = t->pos;
		dolar++;
		while (t->input[t->pos])
			t->pos++;
		end_var = malloc((t->pos - dolar) +1);
		ft_strlcpy(end_var, t->input + dolar, (t->pos - dolar) +1);
		free(t->input);
		t->input = ft_strjoin(prefix, end_var);
		t->pos = t->anchor_pos;
		return;
	}
	end_var = ft_strjoin(prefix, var_token);
	add_custom_token(end_var, TOKEN_VAR, token_list);
	ft_putstr_fd(end_var, 2);
	ft_putstr_fd(": command not found\n", 2);
	t->error = true;
	free(var);
	free(end_var);
	free(prefix);
	t->anchor_pos = t->pos;
}
