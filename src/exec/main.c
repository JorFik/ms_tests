/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:00:56 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/06 19:54:18 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_exec.h"

static const char	***test_cases_declaration(void)
{
	static const char	*case_1[2] = {"echo", NULL};
	static const char	*case_2[4] = {"echo", "Hello", "World", NULL};
	static const char	*case_3[5] = {"echo", "Hello   World", "|", "cat",
		NULL};
	static const char	**test_cases[TEST_COUNT + 1] = {case_1, case_2, case_3,
		NULL};

	return (test_cases);
}

static const t_token_type	**test_token_declaration(void)
{
	static const t_token_type	case_1[1] = {STRING};
	static const t_token_type	case_2[3] = {STRING, STRING, STRING};
	static const t_token_type	case_3[4] = {STRING, STRING, PIPE, STRING};
	static const t_token_type	*tokens[TEST_COUNT] = {case_1, case_2, case_3};

	return (tokens);
}

static const char	***create_tokens(t_token **input_token)
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

int	main(void)
{
	t_token	*in_token[TEST_COUNT];
	char	***output_array;
	int		i;

	output_array = test_transform_to_array(create_tokens(in_token), in_token);

	i = -1;
	while (++i < TEST_COUNT)
		ft_free_n_null((void **)&output_array[i]);
	ft_free_n_null((void **)&output_array);
	return (0);
}
