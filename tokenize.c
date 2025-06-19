#include "minishell.h"
#include "libft.h"

void	initStruct(t_t *t)
{
	t->value = NULL;
	t->type = TOKEN_DEFAULT;
	t->next = NULL;
	t->single_quote = false;
	t->double_quote = false;
	t->input = NULL;
	t->start = NULL;
	t->pos = 0;
	t->anchor_pos = 0;
}

t_t*tokens(char *input)
{
	t_t t;
	t_t *token_list;
	
	initStruct(&t);
	token_list = NULL;
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
		ft_printf("minishell: syntax error near unexpected EOF\n");
		return (0);
	}
	 return (token_list);
}



