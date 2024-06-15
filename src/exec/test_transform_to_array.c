/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_transform_to_array.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:19:46 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/15 21:32:53 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_exec.h"

static void	print_feedback(const char *expected, const char *output, int test)
{
	ft_printf("\t\tTest %d failed\n", test + 1);
	ft_printf("\t\tExpected: %s\n", expected);
	if (output == NULL)
		ft_printf("\t\tOutput is NULL\n");
	else
		ft_printf("\t\tOutput: %s\n", output);
}

static int	jump_pipe(t_cmd **cmd, int *argv_i, int *i, int test_num)
{
	const t_token_type	**exp = declare_test_token_type();

	if (exp[test_num][*i] == PIPE)
	{
		*cmd = (*cmd)->next;
		*argv_i = 0;
		(*i)++;
		return (1);
	}
	return (0);
}

static int	jump_redirects(t_cmd **cmd, int *argv_i, int *i, int test_num)
{
	const t_token_type	**exp = declare_test_token_type();
	int					flag;

	flag = 0;
	while (exp[test_num][*i] > STRING && exp[test_num][*i] < PIPE)
	{
		(*i)++;
		flag = 1;
	}
	if (flag)
		jump_pipe(cmd, argv_i, i, test_num);
	return (flag);
}

static int	check_output(t_cmd *cmd)
{
	static int	t_num = 0;
	const char	***exp = declare_test_strings();
	int			i;
	int			argv_i;
	char		*arg;

	i = 0;
	argv_i = 0;
	while (exp[t_num][i] != NULL &&
		(cmd->argv[argv_i] || jump_pipe(&cmd, &argv_i, &i, t_num)
			|| jump_redirects(&cmd, &argv_i, &i, t_num)))
	{
		arg = cmd->argv[argv_i];
		if (ft_strncmp(arg, exp[t_num][i], ft_strlen(exp[t_num][i]) + 1))
			return (print_feedback(exp[t_num][i], arg, t_num), 1);
		i++;
		argv_i++;
	}
	if (exp[t_num][i] != NULL || cmd->argv[argv_i] != NULL)
		return (print_feedback(exp[t_num][i], cmd->argv[argv_i], t_num), 1);
	return (ft_printf("\t\tTest %d passed\n", ++t_num), 0);
}

t_cmd	**test_transform_to_array(t_cmd **cmd_input)
{
	int		i;
	t_cmd	*working_cmd;

	i = -1;
	ft_printf("\tTest transform to array:\n");
	while (++i < TEST_COUNT)
	{
		working_cmd = cmd_input[i];
		while (working_cmd != NULL)
		{
			working_cmd->argv = transform_to_array(working_cmd->strs);
			working_cmd = working_cmd->next;
		}
		if (check_output(cmd_input[i]))
			return (free_expected_cmd(&cmd_input), NULL);
	}
	ft_printf("\tAll test transform to array tests passed\n");
	return (cmd_input);
}
