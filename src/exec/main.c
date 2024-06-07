/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:00:56 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/07 17:16:56 by JFikents         ###   ########.fr       */
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

static const t_token	**create_tokens(void)
{
	static t_token		*tokens[TEST_COUNT];
	const char			***test_cases = test_cases_declaration();
	const t_token_type	**type = test_token_declaration();
	int					test_num;
	int					argc;

	test_num = -1;
	while (++test_num < TEST_COUNT)
	{
		tokens[test_num] = ft_calloc(1, sizeof(t_token));
		argc = -1;
		while (test_cases[test_num][++argc] != NULL)
		{
			tokens[test_num]->value = (char *)test_cases[test_num][argc];
			tokens[test_num]->type = type[test_num][argc];
			tokens[test_num]->next = ft_calloc(1, sizeof(t_token));
			tokens[test_num]->next->prev = tokens[test_num];
			tokens[test_num] = tokens[test_num]->next;
		}
		tokens[test_num] = tokens[test_num]->prev;
		ft_free_n_null((void **)&tokens[test_num]->next);
		while (tokens[test_num]->prev != NULL)
			tokens[test_num] = tokens[test_num]->prev;
	}
	return ((const t_token **)tokens);
}

int	main(void)
{
	const t_token	**in_token = create_tokens();
	const char		***expected_output = test_cases_declaration();
	char			***array_output;
	int				i;
	// t_cmd			**cmd_output;

	// test_divide_tokens(in_token);
	array_output = test_transform_to_array(expected_output,
			(t_token **)in_token);
	i = -1;
	while (++i < TEST_COUNT)
		ft_free_n_null((void **)&array_output[i]);
	ft_free_n_null((void **)&array_output);
	return (0);
}
