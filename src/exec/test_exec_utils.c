/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:12:56 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/17 13:44:17 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_exec.h"

void	leaks(void)
{
	run_leaks("Test exec");
}

#ifdef __APPLE__

void	run_leaks(const char *test_name)
{
	int	is_there_leaks;

	is_there_leaks = system("\
if [ $(leaks exec_test | grep \"leaks for \" | awk '{print $3}') != 0 ]; then\n\
	leaks exec_test | grep \"Process \">> tests/logs/results_exec.log\n\
exit 1\n\
fi\n\
exit 0");
	if (is_there_leaks)
		ft_printf("\tLeak test failed in %s", test_name);
}
#else

void	run_leaks(const char *test_name)
{
	(void)test_name;
	return ;
}

#endif