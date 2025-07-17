#include "../minishell.h"

void    check_var(t_t *t)
{
    int count;

    count = t->pos;
    while(t->input[count] && t->input[count] != '"' && t->input[count] != '$')
        count++;
    if (t->input[count] == '$')
    
}