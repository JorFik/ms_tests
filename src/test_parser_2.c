/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:50:49 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/21 15:55:06 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_parser.h"

#if TEST == 6

int	main(void)
{
	t_instruction	*result;
	int				error;
	const char		*expected[3] = {"Hello", "World\"", NULL};
	const char		*input = "echo \"Hello\" World\"";
	const char		*leaks_line = "parse_line(\"echo \"Hello\" World\"\")";

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
	return (run_leaks(leaks_line), 0);
}

#elif TEST == 7

int	main(void)
{
	t_instruction	*result;
	int				error;
	const char		*expected[3] = {"Hello\"", "World", NULL};
	const char		*input = "echo Hello\" World";
	const char		*leaks_line = "parse_line(\"echo Hello\" World\")";

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
	return (run_leaks(leaks_line), 0);
}

#elif TEST == 8

int	main(void)
{
	t_instruction	*result;
	int				error;
	const char		*expected[2] = {"HelloWorld", NULL};
	const char		*input = "echo \"Hello\"World";
	const char		*leaks_line = "parse_line(\"echo \"Hello\"World\")";

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
	return (run_leaks(leaks_line), 0);
}

#elif TEST == 9

int	main(void)
{
	t_instruction	*result;
	int				error;
	const char		*expected[2] = {"HelloWorld", NULL};
	const char		*input = "echo Hello\"World\"       ";
	const char		*leaks_line = "parse_line(\"echo Hello\"World\"       \")";

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
	return (run_leaks(leaks_line), 0);
}

#elif TEST == 10

int	main(void)
{
	t_instruction	*result;
	int				error;
	const char		*expected[2] = {"HelloWorldstuck", NULL};
	const char		*input = "echo Hello\"World\"'stuck'";
	const char		*leaks_line = "parse_line(\"echo Hello\"World\"'stuck'\")";

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
	return (run_leaks(leaks_line), 0);
}

#else

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

#endif