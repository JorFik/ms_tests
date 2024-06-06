/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_transform_to_array.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:19:46 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/06 19:37:30 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_exec.h"

void	check_generated_argv(const char ***expected_argvs, char ***output_argvs)
{
	int	i;
	int	j;

	i = -1;
	while (++i < TEST_COUNT)
	{
		j = -1;
		while (expected_argvs[i][++j] != NULL)
		{
			if (output_argvs[i] == NULL
				|| ft_strncmp(expected_argvs[i][j], output_argvs[i][j],
					ft_strlen(expected_argvs[i][j]) + 1) != 0)
			{
				ft_printf("Test %d failed\n", i + 1);
				ft_printf("Expected: %s\n", expected_argvs[i][j]);
				if (output_argvs[i] == NULL)
					ft_printf("Output is NULL\n");
				else
					ft_printf("Output: %s\n", output_argvs[i][j]);
				return ;
			}
		}
		ft_printf("\t\tTest %d passed\n", i + 1);
	}
	ft_printf("\tAll tests passed\n");
}

char	***test_transform_to_array(const char ***expected_output,
	t_token **in_token)
{
	int		i;
	char	***output;

	i = 0;
	output = ft_calloc(TEST_COUNT + 1, sizeof(char **));
	while (i < TEST_COUNT)
	{
		output[i] = transform_to_array(in_token[i]);
		while (in_token[i] != NULL)
		{
			ft_free_n_null((void **)&in_token[i]->prev);
			in_token[i] = in_token[i]->next;
		}
		i++;
	}
	check_generated_argv(expected_output, output);
	return (output);
}
