/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:43:09 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/20 18:40:00 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_exec.h"

static int	extract_redir_fd(t_cmd *cmd, t_exp_redir *exp_redir)
{
	t_token	*redir;

	redir = cmd->redirects;
	while (redir != NULL)
	{
		if (redir->type == REDIR_TO || redir->type == APPEND_TO)
			exp_redir->fd = 1;
		else if (redir->type == REDIR_FROM || redir->type == HERE_DOC)
			exp_redir->fd = 0;
		if (ft_isdigit(redir->value[0]))
			exp_redir->fd = ft_atoi(redir->value);
		exp_redir->next = ft_calloc(sizeof(t_exp_redir), 1);
		if (!exp_redir->next)
			return (1);
		exp_redir->next->prev = exp_redir;
		exp_redir = exp_redir->next;
		redir = redir->next->next;
	}
	return (0);
}

static int	extract_file_name(t_cmd *cmd, t_exp_redir *exp_redir)
{
	t_token	*redir;

	redir = cmd->redirects;
	if (redir == NULL)
		return (0);
	while (redir && redir->next != NULL)
	{
		exp_redir->file_name = ft_strdup(redir->next->value);
		if (!exp_redir->file_name)
			return (1);
		exp_redir = exp_redir->next;
		redir = redir->next->next;
	}
	return (0);
}

// TODO Addd prev to t_exp_redir
static t_exp_redir	*create_expectations(t_cmd **cmd_input)
{
	t_exp_redir	*exp_redir;
	int			test_num;
	t_cmd		*cmd;

	exp_redir = ft_calloc(sizeof(t_exp_redir), TEST_COUNT + 1);
	if (!exp_redir)
		return (ft_printf("Error allocating memory for redir expected"), NULL);
	test_num = -1;
	while (++test_num < TEST_COUNT)
	{
		cmd = cmd_input[test_num];
		while (cmd != NULL)
		{
			if (extract_redir_fd(cmd, &exp_redir[test_num]))
				return (free_exp_redir((t_exp_redir **)&exp_redir), NULL);
			if (extract_file_name(cmd, &exp_redir[test_num]))
				return (free_exp_redir((t_exp_redir **)&exp_redir), NULL);
			cmd = cmd->next;
			if (cmd != NULL)
			{
				exp_redir[test_num].next = ft_calloc(sizeof(t_exp_redir), 1);
				if (exp_redir[test_num].next == NULL)
					return (free_exp_redir((t_exp_redir **)&exp_redir), NULL);
				exp_redir[test_num].next->prev = &exp_redir[test_num];
			}
		}
	}
	return (exp_redir);
}

static int	check_fd_and_name(t_cmd *cmd_input, int test_num,
		t_exp_redir *exp_redir)
{
	int		result_fd;
	char	*result_name;

	result_fd = get_fd(cmd_input);
	if (result_fd != exp_redir->fd)
		return (ft_printf(FD_ERROR, test_num, exp_redir->fd, result_fd), 1);
	// result_name = get_file_name(cmd_input);
	// if (ft_strncmp(result_name, exp_redir->file_name,
	// 		ft_strlen(exp_redir->file_name) + 1))
	// 	return (ft_printf(FILE_ERROR, test_num, exp_redir->file_name,
	// 			result_name), ft_free_n_null((void **)&result_name), 1);
	exp_redir = exp_redir->next;
	return (ft_free_n_null((void **)&result_name), 0);
}

int	test_redir(t_cmd **cmd_input)
{
	t_exp_redir *const	exp_redir = create_expectations(cmd_input);
	t_token				*cmd_redir;
	int					test_num;

	if (!exp_redir)
		return (1);
	ft_printf("\tTest redir:\n");
	test_num = 0;
	while (cmd_input[test_num] != NULL)
	{
		cmd_redir = cmd_input[test_num]->redirects;
		while (cmd_redir != NULL)
		{
			if (check_fd_and_name(cmd_input[test_num], test_num,
					&exp_redir[test_num]))
				return (free_exp_redir((t_exp_redir **)&exp_redir), 1);
			cmd_redir = cmd_redir->next;
			if (cmd_redir == NULL && cmd_input[test_num]->next != NULL)
				cmd_redir = cmd_input[test_num]->next->redirects;
		}
		ft_printf("\t\tTest %d passed\n", ++test_num);
	}
	return (free_exp_redir((t_exp_redir **)&exp_redir), 0);
}
