#include "minishell.h"
#include "libft.h"

void add_pipe(t_command **head, t_command *new_node)
{
    t_command *tmp;

    if (!head || !new_node)
        return ;
    if (!*head)
    {
        *head = new_node;
        return ;
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}
