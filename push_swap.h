# ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "libft/libft.h"

typedef struct s_stack
{
	struct	s_stack	*next;
	int				value;
	char			_copied;
}	t_stack;

typedef struct s_stack_infos
{
	int		size_a;
	int		size_b;
	t_stack	*a;
	t_stack *b;
}	t_stack_infos;

t_stack	*parser(int ac, char **av);


void	stack_pushback(t_stack *stack, int value);
t_stack	*stack_dup(t_stack *input_stack);
t_stack	*stack_sort(t_stack *stack, int len);
t_stack	*stack_get_top(t_stack *stack);

void	print_stack(t_stack *stack); // DEBUG (votez ajean)
int		getValue(t_stack *stack, int i);
void	setValue(t_stack *stack, int i, int value);

# endif
