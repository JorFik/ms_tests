/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:43:09 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/23 16:35:46 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_exec.h"

static int	extract_redir_fd(t_cmd *cmd, t_exp_redir *exp_redir)
{
	t_token	*redir;

	redir = cmd->redirects;
	while (exp_redir->next)
		exp_redir = exp_redir->next;
	while (redir != NULL)
	{
		if (redir->type == REDIR_TO || redir->type == APPEND_TO)
			exp_redir->fd = 1;
		else if (redir->type == REDIR_FROM || redir->type == HERE_DOC)
			exp_redir->fd = 0;
		if (ft_isdigit(redir->value[0]))
			exp_redir->fd = ft_atoi(redir->value);
		if (create_last_exp_redir(exp_redir))
			return (1);
		exp_redir = exp_redir->next;
		redir = redir->next->next;
	}
	if (exp_redir->prev)
		exp_redir = exp_redir->prev;
	return (ft_free_n_null((void **)&exp_redir->next), 0);
}

static int	extract_file_name(t_cmd *cmd, t_exp_redir *exp_redir)
{
	t_token	*redir;

	redir = cmd->redirects;
	if (redir == NULL)
		return (0);
	while (exp_redir->next && exp_redir->file_name != NULL)
		exp_redir = exp_redir->next;
	redir = cmd->redirects;
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
				if (create_last_exp_redir(&exp_redir[test_num]))
					return (free_exp_redir((t_exp_redir **)&exp_redir), NULL);
		}
	}
	return (exp_redir);
}

static int	check_fd_and_name(t_cmd *cmd_input, int test_num,
		t_exp_redir *exp_redir)
{
	int		result_fd;
	char	*result_name;
	t_token	*cmd_redir;

	result_name = NULL;
	cmd_redir = cmd_input->redirects;
	while (ft_strncmp(cmd_redir->next->value, exp_redir->file_name,
			ft_strlen(exp_redir->file_name) + 1))
		exp_redir = exp_redir->next;
	while (cmd_redir != NULL)
	{
		result_fd = get_fd(cmd_input);
		if (result_fd != exp_redir->fd)
			return (ft_printf(FD_ERROR, test_num, exp_redir->fd, result_fd), 1);
		cmd_redir = cmd_redir->next->next;
		cmd_input->redirects = cmd_redir;
		exp_redir = exp_redir->next;
	}
	// result_name = get_file_name(cmd_input);
	// if (ft_strncmp(result_name, exp_redir->file_name,
	// 		ft_strlen(exp_redir->file_name) + 1))
	// 	return (ft_printf(FILE_ERROR, test_num, exp_redir->file_name,
	// 			result_name), ft_free_n_null((void **)&result_name), 1);
	return (ft_free_n_null((void **)&result_name), 0);
}

int	test_redir(t_cmd **cmd_input)
{
	t_exp_redir *const	exp_redir = create_expectations(cmd_input);
	t_token				*cmd_redir;
	int					test_num;
	t_cmd				*cmd_head;
	t_token				*redir_head;

	if (!exp_redir)
		return (1);
	ft_printf("\tTest redir:\n");
	test_num = 0;
	while (cmd_input[test_num] != NULL)
	{
		cmd_redir = cmd_input[test_num]->redirects;
		redir_head = cmd_redir;
		cmd_head = cmd_input[test_num];
		while (cmd_redir != NULL && cmd_input[test_num] != NULL)
		{
			if (check_fd_and_name(cmd_input[test_num], test_num,
					&exp_redir[test_num]))
				return (free_exp_redir((t_exp_redir **)&exp_redir), 1);
			cmd_redir = cmd_redir->next;
			cmd_input[test_num] = cmd_input[test_num]->next;
			if (cmd_redir == NULL && cmd_input[test_num]->next != NULL)
				cmd_redir = cmd_input[test_num]->next->redirects;
		}
		cmd_input[test_num] = cmd_head;
		cmd_input[test_num]->redirects = redir_head;
		ft_printf("\t\tTest %d passed\n", ++test_num);
	}
	return (free_exp_redir((t_exp_redir **)&exp_redir), 0);
}
