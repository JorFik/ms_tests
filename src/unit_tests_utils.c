/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_tests_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:03:36 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/22 20:04:15 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_parser.h"

#ifdef __APPLE__

void	run_leaks(const char *test_name)
{
	int	is_there_leaks;

	is_there_leaks = system("\
if [ $(leaks a.out | grep \"leaks for \" | awk '{print $3}') != 0 ]; then\n\
	leaks a.out | grep \"Process \">> logs/result_parser.log\n\
exit 1\n\
fi\n\
exit 0");
	if (is_there_leaks)
		ft_printf("Failed leak test in %s", test_name);
}
#else

void	run_leaks(const char *test_name)
{
	(void)test_name;
	return ;
}
#endif

void	ft_feedback(int error, t_token *result, const char **exp_str,
			const int *exp_types)
{
	int	i;

	i = -1;
	if (error == WRONG_ARGS)
		while (exp_str[++i] && result && result->content)
		{
			if (ft_strncmp(result->content, exp_str[i], ft_strlen(exp_str[i]) + 1))
				ft_printf("\tToken[%i]: %s\n\tExpected: %s\n", i,
					result->content, exp_str[i]);
			result = result->next;
		}
	if (error == WRONG_ARGS && (result || exp_str[i]))
		ft_printf("\tMore/Less tokens than expected\n");
	if (error == WRONG_TYPE)
		while (exp_types[++i] != -1 && result && result->type)
		{
			if (result->type != (enum e_token)exp_types[i])
				ft_printf("\tToken[%i]: %i\n\tExpected: %i\n", i, result->type,
					exp_str[i]);
			result = result->next;
		}
	if (error == NO_RESULT)
		ft_printf("Output: NULL\nExpected: t_token\n");
}

int	ft_check_output(t_token *token, const char **expect, const int *exp_types)
{
	const t_token	*head = token;
	int				i;

	i = -1;
	if (token == NULL && expect[0] == NULL)
		return (NO_ERROR);
	if (token == NULL && expect[0] != NULL)
		return (NO_RESULT);
	while (expect[++i] && token)
	{
		if (ft_strncmp(token->content, expect[i], ft_strlen(expect[i]) + 1))
			return (WRONG_ARGS);
		token = token->next;
	}
	if (token || expect[i])
		return (WRONG_ARGS);
	token = (t_token *)head;
	i = -1;
	while (exp_types[++i] != -1 && token)
	{
		if (token->type != (enum e_token)exp_types[i])
			return (WRONG_TYPE);
		token = token->next;
	}
	return (NO_ERROR);
}
