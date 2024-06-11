/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_test_divide_tokens.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:15:39 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/11 19:26:28 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_exec.h"

void	free_expected_cmd(t_cmd ***expected_cmd)
{
	t_cmd	*tmp;
	int		i;

	i = -1;
	while (i != TEST_COUNT)
	{
		tmp = expected_cmd[0][++i];
		while (tmp != NULL)
		{
			while (tmp->strs != NULL)
			{
				ft_free_n_null((void **)&tmp->strs->prev);
				tmp->strs = tmp->strs->next;
			}
			while (tmp->redirects != NULL)
			{
				ft_free_n_null((void **)&tmp->redirects);
				tmp->redirects = tmp->redirects->next;
			}
			tmp = tmp->next;
		}
		ft_free_n_null((void **)&expected_cmd[0][i]);
	}
	ft_free_n_null((void **)&expected_cmd[0]);
}

static t_cmd	*create_cmd_per_test(t_cmd *cmd, const char **cases,
		const t_token_type *type)
{
	t_cmd	*tmp;
	int		i;

	i = -1;
	tmp = cmd;
	while (cases[++i] != NULL)
	{
		if (type[i] == STRING)
			tmp->strs = create_next_token(tmp->strs, cases[i], type[i]);
		else if (type[i] > STRING && type[i] < PIPE)
			tmp->redirects = create_next_token(tmp->redirects, cases[i],
					type[i]);
		if (type[i] == PIPE)
		{
			tmp->pipe[0] = PIPING_OUT;
			tmp->next = ft_calloc(1, sizeof(t_cmd));
			tmp->next->pipe[0] = PIPING_IN;
			tmp = tmp->next;
		}
	}
	while (cmd->strs && cmd->strs->prev != NULL)
		cmd->strs = cmd->strs->prev;
	while (cmd->redirects && cmd->redirects->prev != NULL)
		cmd->redirects = cmd->redirects->prev;
	return (cmd);
}

const t_cmd	**create_all_expected_cmds(void)
{
	const char			***cases = declare_test_strings();
	const t_token_type	**type = declare_test_token_type();
	t_cmd				**cmd;
	int					test;

	cmd = ft_calloc(TEST_COUNT, sizeof(t_cmd *));
	test = -1;
	while (++test < TEST_COUNT)
	{
		cmd[test] = ft_calloc(1, sizeof(t_cmd));
		create_cmd_per_test(cmd[test], cases[test], type[test]);
	}
	return ((const t_cmd **)cmd);
}

// void	print_cmd(const t_cmd **cmd)
// {
// 	t_cmd	*tmp;
// 	int		i;

// 	i = -1;
// 	while (++i < TEST_COUNT)
// 	{
// 		tmp = (t_cmd *)cmd[i];
// 		while (tmp != NULL)
// 		{
// 			ft_printf("Cmd[%d]->argv: ", i);
// 			while (tmp->strs != NULL)
// 			{
// 				ft_printf("<%s> ", tmp->strs->value);
// 				tmp->strs = tmp->strs->next;
// 			}
// 			ft_printf("\nCmd->redirects: ");
// 			while (tmp->redirects != NULL)
// 			{
// 				ft_printf("<%s> ", tmp->redirects->value);
// 				tmp->redirects = tmp->redirects->next;
// 			}
// 			ft_printf("\n");
// 			tmp = tmp->next;
// 		}
// 	}
// }