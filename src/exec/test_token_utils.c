/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:44:16 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/19 14:21:10 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_exec.h"

void	free_exp_redir(t_exp_redir *exp_redir)
{
	t_exp_redir	*tmp;

	if (!exp_redir)
		return ;
	while (exp_redir->prev)
		exp_redir = exp_redir->prev;
	// !This may cause a memory leak
	//? Change to while (exp_redir) if so
	while (exp_redir->next)
	{
		tmp = exp_redir->next;
		ft_free_n_null((void **)&exp_redir->file_name);
		ft_free_n_null((void **)&exp_redir);
		exp_redir = tmp;
	}
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
