/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_divide_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:33:15 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/15 14:02:17 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_exec.h"

static int	check_tokens(const t_token *token, const t_token *expected,
	char *check_type, int test_num)
{
	const t_token	*token_head = token;
	const t_token	*expected_head = expected;
	int				len;

	test_num++;
	while (token != NULL && expected != NULL)
	{
		len = ft_strlen(expected->value) + 1;
		if (ft_strncmp(token->value, expected->value, len) != 0)
			return (ft_printf(
					"Test case %d failed\nCmd->%s->value: %s\nExpected: %s\n",
					test_num, check_type, token->value, expected->value), 1);
		token = token->next;
		expected = expected->next;
	}
	if (token != NULL || expected != NULL)
		return (ft_printf("Test case %d failed\n+/- cmd->%s tokens expected",
				test_num, check_type), 1);
	token = token_head;
	expected = expected_head;
	return (0);
}

static int	check_pipe(t_cmd *cmd, int test_num, int out_or_in)
{
	test_num++;
	if (out_or_in == PIPING_OUT && cmd->pipe[PIPE_FD_WRITE] <= 2)
	{
		ft_printf("Test case %d failed\nCmd->pipe[PIPE_FD_WRITE]: %d\n",
			test_num, cmd->pipe);
		ft_printf("Expected: <An open FD>\n");
		return (1);
	}
	else if (cmd->pipe[PIPE_FD_WRITE] >= 2)
		ft_close(&cmd->pipe[PIPE_FD_WRITE]);
	if (out_or_in == PIPING_IN && cmd->pipe[PIPE_FD_READ] <= 2)
	{
		ft_printf("Test case %d failed\nCmd->pipe[PIPE_FD_READ]: %d\n",
			test_num, cmd->pipe);
		ft_printf("Expected: <An open FD>\n");
		return (1);
	}
	else if (cmd->pipe[PIPE_FD_READ] >= 2)
		ft_close(&cmd->pipe[PIPE_FD_READ]);
	return (0);
}

static int	check_cmd(t_cmd **cmd)
{
	const t_cmd	**exp_cmd = create_all_expected_cmds();
	t_cmd		*w_cmd;
	t_cmd		*e_cmd;
	int			i;

	i = -1;
	while (i != TEST_COUNT)
	{
		w_cmd = cmd[++i];
		e_cmd = (t_cmd *)exp_cmd[i];
		while (w_cmd != NULL && e_cmd != NULL)
		{
			if (w_cmd->argv != NULL)
				ft_printf("Test case %d failed\nCmd->argv isn't initialize", i);
			if (check_tokens(w_cmd->redirects, e_cmd->redirects, "redirects", i)
				|| check_tokens(w_cmd->strs, e_cmd->strs, "strs", i)
				|| check_pipe(w_cmd, i, e_cmd->pipe[0]))
				return (1);
			w_cmd = w_cmd->next;
			e_cmd = e_cmd->next;
		}
		if (w_cmd != NULL || e_cmd != NULL)
			return (ft_printf("Test case %d failed\n+/- t_cmd expected", i), 1);
	}
	return (free_expected_cmd((t_cmd ***)&exp_cmd), 0);
}

t_cmd	**test_divide_tokens(const t_token **input_token)
{
	static t_cmd	*cmd[TEST_COUNT];
	int				test_num;

	test_num = -1;
	while (++test_num < TEST_COUNT)
		cmd[test_num] = divide_tokens((t_token *)input_token[test_num]);
	if (check_cmd(cmd))
		return (NULL);
	return ((t_cmd **)cmd);
}
