#include "minishell.h"

t_t*tokens(char *input)
{
	t_t t;
	t_t *token_list;
	
	t = {0};
	*token_list = NULL;
	t.input = input;
	t.start = input;

	while(t.input[t.pos])
	{
		quotes(&t);
		if (t.single_quote || t.double_quote)
			open_quotes(&t, &token_list);
		if(t.input[t.pos])
			metacharacters(&t, &token_list);
		t.pos++;
	}
	if (t.single_quote || t.double_quote)
	{
		ft_printf("minishell: syntax error near unexpected EOF");
		return ;
	}
}

static void	quotes(t_t *t)
{
	if ((t->input[t->pos] == '\'' && !t->double_quote) && (t->start == t->input
		|| t->input[t->pos -1] != '\\'))
	{
		t->single_quote = !t->single_quote;
		t->anchor_pos = t->pos;
		t->pos++;
	}
	else if ((t->input[t->pos] == '\"' && !t->single_quote) && (t->start == t->input
		|| t->input[t->pos -1] != '\\'))
	{
		t->double_quote = !t->double_quote;
		t->anchor_pos = t->pos;
		t->pos++;
	}
}

static void	metacharacters(t_t *t, t_t **token_list)
{
	if (t->input[t->pos] == '\'' || t->input[t->pos] == '\"')
		return ;
	if (t->input[t->pos] == ' ' || t->input[t->pos] == '|' || t->input[t->pos] == '<'
		|| t->input[t->pos] == '>')
		add_token();
	t->pos++;
}

static void	open_quotes(t_t *t, t_t **token_list)
{
	if (t->single_quote)
		while (t->input[t->pos])
		{
			if (t->input[t->pos] == '\'' && t->input[t->pos -1] != '\\')
			{
				t->single_quote = !t->single_quote;
				add_token();
			}
			t->pos++;
		}
	else if (t->double_quote)
		while (t->input[t->pos])
		{
			if (t->input[t->pos] == '\"' && t->input[t->pos -1] != '\\')
			{
				t->double_quote = !t->double_quote;
				add_token();
			}
			t->pos++;
		}
	t->pos++;
}
static void add_token(t_t *t, t_t **token_list)
{
	size_t	len;
	t_t *new_token;

	len = t->pos - t->anchor_pos;
	new_token = malloc(sizeof(t_t));
	if (!new_token)
		return ;
	new_token->value = malloc(len +1);
	if (!new_token->value)
	{
		free(new_token->value);
		free(new_token);
		return ;
	}
	ft_strlcpy(new_token->value, t->start, len +1);
	if (ft_strchr("|<>"), new_token->value[0])
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