#include "minishell.h"
#include "libft.h"

void	quotes(t_t *t)
{
	if ((t->input[t->pos] == '\'' && !t->double_quote) && (t->start == t->input
		|| t->input[t->pos -1] != '\\'))
	{
		t->single_quote = !t->single_quote;
		t->pos++;
	}
	else if ((t->input[t->pos] == '\"' && !t->single_quote) && (t->start == t->input
		|| t->input[t->pos -1] != '\\'))
	{
		t->double_quote = !t->double_quote;
		t->pos++;
	}
}

void	metacharacters(t_t *t, t_t **token_list)
{
	
	if (t->input[t->pos])
	{
		if (t->input[t->pos] == ' ' || t->input[t->pos] == '|' || t->input[t->pos] == '<'
			|| t->input[t->pos] == '>')
			add_token(t, token_list);
		t->pos++;
	}
}

void	open_quotes(t_t *t, t_t **token_list)
{
	if (t->single_quote)
		while (t->input[t->pos])
		{
			if (t->input[t->pos] == '\'' && t->input[t->pos -1] != '\\')
			{
				t->single_quote = !t->single_quote;
				add_token(t, token_list);
				return ;
			}
			t->pos++;
		}
	else if (t->double_quote)
		while (t->input[t->pos])
		{
			if (t->input[t->pos] == '\"' && t->input[t->pos -1] != '\\')
			{
				t->double_quote = !t->double_quote;
				add_token(t, token_list);
				return ;
			}
			t->pos++;
		}
	t->pos++;
}

void add_token(t_t *t, t_t **token_list)
{
	size_t	len;
	t_t *new_token;
	int check_memory;
	if (t->start[t->anchor_pos] == ' ' && t->pos != t->anchor_pos)
		t->anchor_pos++;
	len = t->pos - t->anchor_pos;
	if (len == 0)
		return ;
	check_memory = alloc_new_token(&new_token, len);
	if (check_memory == 0)
		return ;
	ft_strlcpy(new_token->value, t->start + t->anchor_pos, len +2);
	t->anchor_pos = t->pos +1; // il +1 è per non ripettere l'ultimo carattere
	if (ft_strchr(("|<>"), new_token->value[0]))
		new_token->type = METACHAR;
	else
		new_token->type = WORD;
	new_token->next = NULL;
	add_token_2(new_token, token_list);
}

void add_token_2(t_t *new_token, t_t **token_list)
{
	if (*token_list == NULL) {
        *token_list = new_token;
    } else {
        t_t *last = *token_list;
        while (last->next != NULL)
            last = last->next;
        last->next = new_token;
    }
}