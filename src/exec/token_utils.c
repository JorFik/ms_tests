/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:44:16 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/08 14:07:26 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_exec.h"

t_token	*create_token_as_next(t_token *token, const char *value,
		t_token_type type)
{
	token->next = ft_calloc(1, sizeof(t_token));
	if (token->next == NULL)
		return (NULL);
	token->next->prev = token;
	token->next->value = (char *)value;
	token->next->type = type;
	return (token->next);
}