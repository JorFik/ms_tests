/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:00:56 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/15 18:10:33 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_exec.h"

static int	init_environ(void)
{
	extern char	**environ;
	extern int	errno;
	int			env_var_count;
	char		**new_env;

	errno = 0;
	env_var_count = 0;
	while (environ[env_var_count])
		env_var_count++;
	new_env = ft_calloc(env_var_count + 1, sizeof(char *));
	if (!new_env)
		return (EXIT_FAILURE);
	env_var_count = 0;
	while (environ[env_var_count])
	{
		new_env[env_var_count] = ft_strdup(environ[env_var_count]);
		if (!new_env[env_var_count])
			return (ft_free_2d_array((void ***)&new_env, -1), EXIT_FAILURE);
		env_var_count++;
	}
	environ = new_env;
	return (0);
}

const char	***declare_test_strings(void)
{
	static const char	*case_1[2] = {"echo", NULL};
	static const char	*case_2[4] = {"echo", "Hello", "World", NULL};
	static const char	*case_3[5] = {"echo", "Hello   World", "|", "cat",
		NULL};
	static const char	**test_cases[TEST_COUNT + 1] = {case_1, case_2, case_3,
		NULL};

	return (test_cases);
}

const t_token_type	**declare_test_token_type(void)
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
	const char			***test_cases = declare_test_strings();
	const t_token_type	**type = declare_test_token_type();
	int					test_num;
	int					argc;

	test_num = -1;
	while (++test_num < TEST_COUNT)
	{
		tokens[test_num] = ft_calloc(1, sizeof(t_token));
		argc = 0;
		tokens[test_num]->value = (char *)test_cases[test_num][argc];
		tokens[test_num]->type = type[test_num][argc];
		while (test_cases[test_num][++argc] != NULL)
		{
			tokens[test_num] = create_next_token(tokens[test_num],
					test_cases[test_num][argc], type[test_num][argc]);
		}
		while (tokens[test_num]->prev != NULL)
			tokens[test_num] = tokens[test_num]->prev;
	}
	return ((const t_token **)tokens);
}

int	main(void)
{
	const t_token	**in_token = create_tokens();
	t_cmd			**cmd_output;

	if (init_environ())
	{
		perror("minishell: Error initializing environment");
		return (EXIT_FAILURE);
	}
	cmd_output = test_divide_tokens(in_token);
	if (cmd_output == NULL)
		return (1);
	// cmd_output = test_transform_to_array(cmd_output);
	return (free_expected_cmd(&cmd_output), 0);
}
