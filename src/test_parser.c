/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:45:26 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/22 13:30:57 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_parser.h"

int	main(void)
{
	t_instruction	*result;
	int				error;
	const char		*expected[E_COUNT] = EXPECTED;
	const char		*input = TEST_CASE;

	result = parse_line((char *) input);
	error = ft_check_output(result, expected);
	if (error == NO_ERROR)
		ft_printf("Test for parse_line(\"%s\"): PASS\n", input);
	else
	{
		ft_printf("\nTest for parse_line(\"%s\"): Failed\n", input);
		ft_feedback(error, result, expected);
	}
	if (result)
		ft_free_results(&result);
	return (run_leaks(LEAKS_LINE(TEST_CASE)), 0);
}
