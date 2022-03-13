#include <stdlib.h>
#include "push_swap.h"

void	print_stack(t_stack *stack) // DEBUG (votez ajean)
{
	// ft_putstr_fd("/!\\ VOTEZ AJEAN /!\\\n", 2);
		ft_putnbr_fd(0, STDERR_FILENO); ft_putstr_fd(":\t", 2);
	ft_putnbr_fd(stack->value, STDERR_FILENO);
	ft_putchar_fd('\n', 2);
	size_t i = 1;
	while (stack)
	{
		stack = stack->next;
		if (!stack)
			break ;
		ft_putnbr_fd(i, STDERR_FILENO); ft_putstr_fd(":\t", 2);
		ft_putnbr_fd(stack->value, STDERR_FILENO);
		ft_putchar_fd('\n', 2);
		++i;
	}

}

// size_t	number_len(char *str) // whatever
// {
// 	char	*start;

// 	start = str;
// 	while (*str >= '0' && *str <= '9')
// 		++str;
// 	return (str - start);
// }

int		getValue(t_stack *stack, int i)
{
	while (i-- > 0)
		stack = stack->next;
	return (stack->value);
}

void	setValue(t_stack *stack, int i, int value)
{
	while (i-- > 0)
		stack = stack->next;
	stack->value = value;
}

t_stack	*simplify(t_stack *input_stack, size_t len)
{
	size_t	i;
	size_t	j;
	t_stack	*copy;

	copy = stack_sort(stack_dup(input_stack), len);
	ft_putstr_fd("INPUT STACK:\n", 2); fflush(stderr);
	ft_putstr_fd("====\n", 2); print_stack(input_stack); ft_putstr_fd("====\n", 2);
	ft_putstr_fd("SORTED COPY:\n", 2); fflush(stderr);
	ft_putstr_fd("====\n", 2); print_stack(copy); ft_putstr_fd("====\n", 2);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len)
		{
				// printf("%d %d %d %d\n", getValue(input_stack, i), getValue(copy, j), i, j);	// DEBUG
			if (getValue(input_stack, i) == getValue(copy, j))
			{
				// printf("%d %d %d %d\n", getValue(input_stack, i), getValue(copy, j), i, j); // DEBUG
				setValue(input_stack, i, j);
				// printf("%d %d %d %d\n", getValue(input_stack, i), getValue(copy, j), i, j); // DEBUG
				// ft_putstr_fd("what\n", 2);
				break ;
			}
			++j;
		}
		++i;
	}
	// Ne pas oublier de free tous les éléments de copy
	ft_putstr_fd("INPUT STACK WITH SIMPLIFIED NUMS:\n", 2); fflush(stderr);
	ft_putstr_fd("====\n", 2); print_stack(input_stack);
	return (input_stack);
}

t_stack	*parser(int ac, char **av)
{
	t_stack	*input_stack;
	t_stack	*sorted_stack;
	size_t	i;

	input_stack = malloc(sizeof(input_stack));
	if (input_stack == NULL)
		exit (-0x2a);	// ET OUAIS ÇA FAIT QUOI EN DÉCIMAL??
	input_stack->next = NULL;
	input_stack->value = ft_atoi(av[ac - 1]); // Quitter si nombre invalide
	i = ac - 1;
	while (--i > 0)
		stack_pushback(input_stack, ft_atoi(av[i])); // opti en gardant un pointeur sur le dernier élément à chaque fois
				// print_stack(input_stack); // DEBUG
		// check_duplicates(input_stack)
	sorted_stack = simplify(input_stack, (ac - 1));
	return (sorted_stack);
}
