#include "push_swap.h"

void	stack_pushback(t_stack *stack, int value)
{
	while (stack->next)
		stack = stack->next;
	stack->next = (t_stack *)malloc(sizeof(t_stack));
	if (stack->next == NULL)
		exit (-0x2a);	
	stack = stack->next;
	stack->value = value;
	stack->next = NULL;
}

t_stack	*stack_dup(t_stack *input_stack)
{
	t_stack *copy;
	t_stack	*start;

	copy = (t_stack *)malloc(sizeof(t_stack));
	if (copy == NULL)
		exit(-0x2a);
	copy->value = input_stack->value;
	start = copy;
	input_stack = input_stack->next;
	while (input_stack)
	{
		copy->next = (t_stack *)malloc(sizeof(t_stack));
		if (copy == NULL)
			exit(-0x2a);
		copy = copy->next;
		copy->value = input_stack->value;
		input_stack = input_stack->next;
	}
	copy->next = NULL;
	return (start);
}

/**
 *	BUBBLE SORT DEGUEU A CORRIGER
**/
t_stack	*stack_sort(t_stack *stack, int len)
{
	t_stack	*start;
	t_stack *st_i;	
	t_stack	*st_j;
	int		tmp;

	start = stack;
	while (len-- >= 0)
	{
		st_i = stack;
		st_j = stack->next;
		while (st_i && st_j)
		{
			if (st_i->value > st_j->value)
			{
				tmp = st_i->value;
				st_i->value = st_j->value;
				st_j->value = tmp;
			}
			st_i = st_i->next;
			st_j = st_j->next;
		}

	}
	return (start);
}

t_stack	*stack_get_top(t_stack *stack)
{
	if (!stack)
		return (NULL);
		// printf("%s\n", __func__);
	while (stack->next)
		stack = stack->next;
			// printf("<->\n"); fflush(stdout);
	return (stack);
}
