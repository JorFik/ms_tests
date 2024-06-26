/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:49:01 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/01 16:01:33 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static pid_t	send_commands_to_minishell(int *status)
{
	pid_t	pid;
	int		write_minishell;

	pid = start_minishell_builtins(&write_minishell);
	ft_putendl_fd("pwd", write_minishell);
	ft_putendl_fd("cd ..", write_minishell);
	ft_putendl_fd("pwd", write_minishell);
	ft_putendl_fd("echo Hello World", write_minishell);
	ft_putendl_fd("echo -nnnnnnnnnm Hello World", write_minishell);
	ft_putendl_fd("echo -nnnnnnnnn Hello World", write_minishell);
	ft_putendl_fd("echo -n Hello World", write_minishell);
	ft_putendl_fd("echo Hello World-n", write_minishell);
	ft_putendl_fd("echo Hello World -n", write_minishell);
	ft_putendl_fd("cd ", write_minishell);
	ft_putendl_fd("env", write_minishell);
	ft_check_minishell_builtins_leaks();
	ft_putendl_fd("exit -1", write_minishell);
	usleep(TIMEOUT);
	kill(pid, SIGKILL);
	waitpid(pid, status, WUNTRACED);
	ft_close(&write_minishell);
	return (pid);
}

static void	pwd_test(int read_output_fd)
{
	static int	i = 1;
	char		*output;
	char		*cwd;
	char		*test_str;
	char		*test_num_str;

	output = get_next_line(read_output_fd);
	test_str = ft_strjoin("Test ", test_num_str = ft_itoa(i++));
	ft_free_n_null((void **)&test_num_str);
	test_num_str = ft_strjoin(test_str, " pwd");
	ft_free_n_null((void **)&test_str);
	test_str = test_num_str;
	print_feedback(test_str, output, cwd = getcwd(NULL, 0));
	ft_free_n_null((void **)&test_str);
	ft_free_n_null((void **)&output);
	ft_free_n_null((void **)&cwd);
}

static void	prompt_test(int read_output_fd)
{
	static int	i = 1;
	char		*output;
	char		*prompt;
	char		*test_str;
	char		*test_num_str;

	output = get_test_input(read_output_fd);
	if (!output)
		return ;
	test_str = ft_strjoin("Test ", test_num_str = ft_itoa(i++));
	ft_free_n_null((void **)&test_num_str);
	test_num_str = ft_strjoin(test_str, " prompt");
	ft_free_n_null((void **)&test_str);
	test_str = test_num_str;
	print_feedback(test_str, output, prompt = get_prompt());
	ft_free_n_null((void **)&test_str);
	ft_free_n_null((void **)&output);
	ft_free_n_null((void **)&prompt);
}

static void	env_test(int read_output_fd)
{
	int			i;
	char		*line;
	extern char	**environ;
	int			fail_flag;

	fail_flag = 0;
	i = -1;
	while (environ[++i])
	{
		line = get_next_line(read_output_fd);
		if (ft_strncmp(line, environ[i],
				ft_strchr(environ[i], '=') - environ[i]))
		{
			ft_printf(RED"Test 1 env failed\n");
			ft_printf("Output:\t\t%sExpected:\t%s\n\n", line, environ[i]);
			ft_printf(DEFAULT);
			fail_flag = 1;
		}
		if (!line)
			break ;
		ft_free_n_null((void **)&line);
	}
	if (!environ[i] && !fail_flag)
		ft_putendl_fd(GREEN"Test 1 env success"DEFAULT, 1);
}

void	test_1_builtins(void)
{
	pid_t		pid;
	char		*line;
	int			read_output_fd;
	int			status;

	pid = send_commands_to_minishell(&status);
	read_output_fd = open("tests/logs/minishell_builtins.log", O_RDONLY);
	if (read_output_fd < 0)
		exit(1);
	prompt_test(read_output_fd);
	pwd_test(read_output_fd);
	line = get_test_input(read_output_fd);
	ft_free_n_null((void **)&line);
	chdir("..");
	prompt_test(read_output_fd);
	pwd_test(read_output_fd);
	echo_test_1(read_output_fd);
	echo_test_2(read_output_fd);
	echo_test_3(read_output_fd);
	echo_test_4(read_output_fd);
	echo_test_5(read_output_fd);
	echo_test_6(read_output_fd);
	cd_test_1(read_output_fd);
	env_test(read_output_fd);
	exit_test_1(read_output_fd, status);
	reset_tty(pid);
}
