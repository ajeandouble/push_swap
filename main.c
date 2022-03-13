#include "libft/libft.h"
#include "push_swap.h"

t_stack	*stack_get_elem(t_stack *stack, int i)
{
	while (i-- > 0)
		stack = stack->next;
	return (stack);
}

void	op_ra(t_stack_infos *infos)
{
	ft_putstr("ra\n");
		ft_putstr_fd(__func__, 2); ft_putstr_fd("\n", 2);
	t_stack	*before_last;
	t_stack	*last_a;

		fprintf(stderr, "infos->size_a %d\n", infos->size_a);
	if (infos->size_a <= 1)
		return ;
	before_last = stack_get_elem(infos->a, infos->size_a - 2);
	last_a = stack_get_top(infos->a);
	// printf("[%d]\n", last_a->value);
	last_a->next = infos->a;
	before_last->next = NULL;
	infos->a = last_a;
	ft_putstr_fd("A===\n", 2); print_stack(infos->a); ft_putstr_fd("====\n", 2);
}

void	op_pb(t_stack_infos *infos)
{
	ft_putstr("pb\n");
		ft_putstr_fd(__func__, 2); ft_putstr_fd("\n", 2);
	t_stack	*start_a;
	if (!infos->b)
	{
		infos->b = (t_stack *)malloc(sizeof(t_stack));
		infos->b->value = stack_get_top(infos->a)->value;
		// printf("topvalue=%d\n", stack_get_top(infos->a)->value);	// DEBUG
		infos->b->next = NULL;
	}
	else
		stack_pushback(infos->b, stack_get_top(infos->a)->value);
	start_a = infos->a;
	while (start_a->next && start_a->next->next)
		start_a = start_a->next;
	if (start_a->next)
	{
		start_a->next = NULL;
		free(start_a->next);
	}
	else
	{
		free(infos->a);
		infos->a = NULL;
	}
	infos->size_a--;
	infos->size_b++;
		ft_putstr_fd("B===\n", 2); print_stack(infos->a); ft_putstr_fd("====\n", 2); // DEBUG
}


void	op_pa(t_stack_infos *infos)
{
	ft_putstr("pa\n");

		ft_putstr_fd(__func__, 2); ft_putstr_fd("\n", 2);
	t_stack	*start_b;
	if (!infos->a)
	{
		infos->a = (t_stack *)malloc(sizeof(t_stack));
		infos->a->value = stack_get_top(infos->b)->value;
		printf("b topvalue=%d\n", stack_get_top(infos->b)->value);
		infos->a->next = NULL;
	}
	else
		stack_pushback(infos->a, stack_get_top(infos->b)->value);
	start_b = infos->b;
	while (start_b->next && start_b->next->next)
		start_b = start_b->next;
	if (start_b->next)
	{
		start_b->next = NULL;
		free(start_b->next);
	}
	else
	{
		free(infos->b);
		infos->b = NULL;
	}
	infos->size_a++;
	infos->size_b--;
	ft_putstr_fd("B===\n", 2); print_stack(infos->a); ft_putstr_fd("====\n", 2);
}


void	solve(t_stack_infos *infos)
{
	ft_putstr_fd("A===\n", 2); print_stack(infos->a); ft_putstr_fd("====\n", 2);
	int	i;
	int	j;
	int	max_num;
	int	max_bits;
	size_t	size;

	max_num = infos->size_a;
	size = infos->size_a;
	max_bits = 0;
	while ((max_num >> max_bits) != 0)
		++max_bits;
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < size)
		{
			int	num = (stack_get_top(infos->a)->value >> i)&1;
			if (num == 1)
				op_ra(infos);
			else
				op_pb(infos);
		
			++j;
		}
		++i;
		while (infos->size_b)
			op_pa(infos);
	}
	ft_putnbr_fd(infos->size_a, 2); ft_putstr_fd("\n", 2);
}

void	free_stacks(int size, t_stack *stack)
{
	t_stack	*prev;

	prev = stack;
	while (size--)
	{
		stack = stack->next;
		free(prev);
		prev = stack;
	}
}
int	main(int ac, char **av)
{
	t_stack *input_stack;
	t_stack_infos	stack_infos;
	t_stack *prev;
	t_stack	*next;

	if (ac < 3) // MINIMUM 2 ÉLÉMENTS !
		return (-1);
	input_stack = parser(ac, av);
	ft_memset(&stack_infos, 0, sizeof(t_stack_infos));
	stack_infos.a = input_stack;
	stack_infos.size_a = ac - 1;
	solve(&stack_infos);
	free_stacks(stack_infos.size_a, stack_infos.a);
	free_stacks(stack_infos.size_b, stack_infos.b);
}
