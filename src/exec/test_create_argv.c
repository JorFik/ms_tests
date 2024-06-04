/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_create_argv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:19:46 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/04 22:10:56 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_exec.h"

static const char	***test_cases_declaration(void)
{
	static const char	*case_1[2] = {"echo", NULL};
	static const char	*case_2[4] = {"echo", "Hello", "World", NULL};
	static const char	**test_cases[TEST_COUNT + 1] = {case_1, case_2, NULL};

	return (test_cases);
}

static const t_token_type	**test_token_declaration(void)
{
	static const t_token_type	case_1[1] = {STRING};
	static const t_token_type	case_2[3] = {STRING, STRING, STRING};
	static const t_token_type	*tokens[TEST_COUNT] = {case_1, case_2};

	return (tokens);
}

static const char	***assign_test_token(t_token **input_token)
{
	const char			***test_cases = test_cases_declaration();
	const t_token_type	**type = test_token_declaration();
	int					test_num;
	int					argc;

	test_num = 0;
	while (test_num < TEST_COUNT)
	{
		input_token[test_num] = ft_calloc(1, sizeof(t_token));
		argc = -1;
		while (test_cases[test_num][++argc] != NULL)
		{
			input_token[test_num]->value = (char *)test_cases[test_num][argc];
			input_token[test_num]->type = type[test_num][argc];
			input_token[test_num]->next = ft_calloc(1, sizeof(t_token));
			input_token[test_num]->next->prev = input_token[test_num];
			input_token[test_num] = input_token[test_num]->next;
		}
		input_token[test_num] = input_token[test_num]->prev;
		ft_free_n_null((void **)&input_token[test_num]->next);
		while (input_token[test_num]->prev != NULL)
			input_token[test_num] = input_token[test_num]->prev;
		test_num++;
	}
	return (test_cases);
}

void	check_generated_argv(const char ***expected_argvs, char ***output_argvs)
{
	int	i;
	int	j;

	i = -1;
	while (++i < TEST_COUNT)
	{
		j = -1;
		while (expected_argvs[i][++j] != NULL)
		{
			if (output_argvs[i] == NULL
				|| ft_strncmp(expected_argvs[i][j], output_argvs[i][j],
					ft_strlen(expected_argvs[i][j]) + 1) != 0)
			{
				ft_printf("Test %d failed\n", i + 1);
				ft_printf("Expected: %s\n", expected_argvs[i][j]);
				if (output_argvs[i] == NULL)
					ft_printf("Output is NULL\n");
				else
					ft_printf("Output: %s\n", output_argvs[i][j]);
				return ;
			}
		}
	}
	ft_printf("\tAll tests passed\n");
}

int	main(void)
{
	int			i;
	t_token		*input_token[TEST_COUNT];
	const char	***expected_argvs = assign_test_token(input_token);
	char		**output_argvs[TEST_COUNT + 1];

	i = 0;
	ft_bzero(output_argvs, sizeof(output_argvs));
	while (i < TEST_COUNT)
	{
		output_argvs[i] = create_argvs(input_token[i]);
		while (input_token[i] != NULL)
		{
			ft_free_n_null((void **)&input_token[i]->prev);
			input_token[i] = input_token[i]->next;
		}
		i++;
	}
	check_generated_argv(expected_argvs, output_argvs);
	i = 0;
	while (i < TEST_COUNT && output_argvs[i] != NULL)
		ft_free_n_null((void **)&output_argvs[i++]);
	return (0);
}
