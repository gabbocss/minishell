#include "minishell.h"

t_token *tokens(char *input)
{
	t_token	*head;
	char *start;
	bool single_quote;
	bool double_quote;

	head = NULL;
	start = input;
	single_quote = false;
	double_quote = false;

	while(*input)
	{
		quotes(&input, &single_quote, &double_quote, start);
		
	}

}

static void quotes(char **input, bool *single_quote, bool *double_quote,
	char *start)
{
	if ((**input == '\'' && !double_quote) && (start == *input || *(*input -1) != '\\'))
	{
		single_quote = !single_quote;
		(*input)++;
	}
	else if ((**input == '\"' && !single_quote) && (start == *input || *(*input -1) != '\\'))
	{
		double_quote = !double_quote;
		(*input)++;
	}
}