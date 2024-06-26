/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_test_divide_tokens.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:15:39 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/25 11:58:35 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_exec.h"

static void	free_expected_tokens(t_token **token)
{
	if (*token == NULL)
		return ;
	while ((*token)->next != NULL)
	{
		ft_free_n_null((void **)&(*token)->prev);
		(*token) = (*token)->next;
	}
	ft_free_n_null((void **)&(*token)->prev);
	ft_free_n_null((void **)&(*token));
}

void	free_expected_cmd(t_cmd ***cmd_output)
{
	t_cmd	*working_cmd;
	t_cmd	*tmp;
	int		i;

	i = -1;
	while (cmd_output[0][++i] != NULL)
	{
		working_cmd = cmd_output[0][i];
		while (working_cmd != NULL)
		{
			free_expected_tokens(&working_cmd->strs);
			free_expected_tokens(&working_cmd->redirects);
			if (working_cmd->argv != NULL)
				ft_free_2d_array((void ***)&working_cmd->argv, FREE_ANY_SIZE);
			tmp = working_cmd->next;
			ft_free_n_null((void **)&working_cmd);
			working_cmd = tmp;
		}
	}
	ft_free_n_null((void **)&cmd_output[0]);
}

void	set_cmd_pipe(t_cmd **cmd)
{
	(*cmd)->pipe[0] = PIPING_OUT;
	(*cmd)->next = ft_calloc(1, sizeof(t_cmd));
	(*cmd)->next->pipe[0] = PIPING_IN;
	while ((*cmd)->strs && (*cmd)->strs->prev != NULL)
		(*cmd)->strs = (*cmd)->strs->prev;
	while ((*cmd)->redirects && (*cmd)->redirects->prev != NULL)
		(*cmd)->redirects = (*cmd)->redirects->prev;
	(*cmd) = (*cmd)->next;
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
		if (type[i] == PIPE)
			set_cmd_pipe(&tmp);
		if (type[i] == PIPE || type[i] == STRING)
			continue ;
		tmp->redirects = create_next_token(tmp->redirects, cases[i], type[i]);
		i++;
		tmp->redirects = create_next_token(tmp->redirects, cases[i], type[i]);
	}
	while (tmp->strs && tmp->strs->prev != NULL)
		tmp->strs = tmp->strs->prev;
	while (tmp->redirects && tmp->redirects->prev != NULL)
		tmp->redirects = tmp->redirects->prev;
	return (cmd);
}

const t_cmd	**create_all_expected_cmds(void)
{
	const char			***cases = declare_test_strings();
	const t_token_type	**type = declare_test_token_type();
	t_cmd				**cmd;
	int					test;

	cmd = ft_calloc(TEST_COUNT + 1, sizeof(t_cmd *));
	test = -1;
	while (++test < TEST_COUNT)
	{
		cmd[test] = ft_calloc(1, sizeof(t_cmd));
		create_cmd_per_test(cmd[test], cases[test], type[test]);
	}
	return ((const t_cmd **)cmd);
}
