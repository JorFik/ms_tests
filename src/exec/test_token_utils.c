/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:44:16 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/24 13:43:14 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_exec.h"

void	restart_token(t_token **token)
{
	while (*token != NULL && (*token)->prev != NULL)
		*token = (*token)->prev;
}

void	free_exp_redir(t_exp_redir **e_redir)
{
	t_exp_redir	*tmp;
	int			test_num;

	test_num = -1;
	while (++test_num < TEST_COUNT)
	{
		tmp = &e_redir[0][test_num];
		while (tmp->next)
			tmp = tmp->next;
		while (tmp->prev)
		{
			if (tmp->next)
				ft_free_n_null((void **)&(tmp->next->file_name));
			ft_free_n_null((void **)&(tmp->next));
			tmp = tmp->prev;
		}
		if (tmp->next)
			ft_free_n_null((void **)&(tmp->next->file_name));
		ft_free_n_null((void **)&(tmp->next));
		ft_free_n_null((void **)&(tmp->file_name));
	}
	ft_free_n_null((void **)e_redir);
}

int	count_tokens(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL)
	{
		count++;
		token = token->next;
	}
	return (count);
}

t_token	*create_next_token(t_token *token, const char *value,
		t_token_type type)
{
	if (token == NULL)
		return (create_token_head(value, type));
	token->next = ft_calloc(1, sizeof(t_token));
	if (token->next == NULL)
		return (NULL);
	token->next->prev = token;
	token->next->value = (char *)value;
	token->next->type = type;
	return (token->next);
}

t_token	*create_token_head(const char *value, t_token_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->value = (char *)value;
	token->type = type;
	return (token);
}

const char	***declare_test_strings(void)
{
	static const char	*case_1[2] = {"echo", NULL};
	static const char	*case_2[4] = {"echo", "Hello", "World", NULL};
	static const char	*case_3[5] = {"echo", "Hello   World", "|", "cat",
		NULL};
	static const char	*case_4[13] = {"echo", "Hello", ">", " test_file1",
		"2>", "test_file2", "|", "cat", "<<", "EOF3", ">>", "test_file4", NULL};
	static const char	**test_cases[TEST_COUNT + 1] = {case_1, case_2, case_3,
		case_4, NULL};

	return (test_cases);
}

const t_token_type	**declare_test_token_type(void)
{
	static const t_token_type	case_1[2] = {STRING, -1};
	static const t_token_type	case_2[4] = {STRING, STRING, STRING, -1};
	static const t_token_type	case_3[5] = {STRING, STRING, PIPE, STRING, -1};
	static const t_token_type	case_4[13] = {STRING, STRING, REDIR_TO, STRING,
		REDIR_TO, STRING, PIPE, STRING, HERE_DOC, STRING, APPEND_TO, STRING,
		-1};
	static const t_token_type	*tokens[TEST_COUNT] = {case_1, case_2, case_3,
		case_4};

	return (tokens);
}
