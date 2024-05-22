/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:45:26 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/22 19:12:14 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_parser.h"

int	main(void)
{
	t_token		*result;
	int			error;
	const char	*expected[E_COUNT] = EXPECTED;
	const char	*input = TEST_CASE;
	const int	exp_types[E_COUNT] = EXP_TYPES;

	result = parse_line((char *) input);
	error = ft_check_output(result, expected, exp_types);
	if (error == NO_ERROR)
		ft_printf("Test for parse_line(\"%s\"): PASS\n", input);
	else
	{
		ft_printf("\nTest for parse_line(\"%s\"): Failed\n", input);
		ft_feedback(error, result, expected, exp_types);
	}
	if (result)
		ft_free_link_list(result);
	return (run_leaks(LEAKS_LINE(TEST_CASE)), 0);
}
