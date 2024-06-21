/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:44:16 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/21 17:59:27 by JFikents         ###   ########.fr       */
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
	ft_free_n_null((void **)*e_redir);
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
