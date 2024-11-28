/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:49:59 by miparis           #+#    #+#             */
/*   Updated: 2024/11/28 11:16:52 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


pid_t	create_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Problem creating process\n");
		exit(1);
	}
	else
		return (pid);
}
/*
void	father(char *argv[], char **envp)
{
	int		pipes[2];
	pid_t	pid[2];

	if (pipe(pipes) == -1)
		perror("Problem creating pipe\n");
	pid[0] = create_process();
	if (pid[0] == 0)
	{
		close(pipes[0]);
		first_child(pipes, argv, envp);
	}
	pid[1] = create_process();
	if (pid[1] == 0)
	{
		close(pipes[1]);
		second_child(pipes, argv, envp);
	}
	close(pipes[0]);
	close(pipes[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}

void	first_child(int pipes[], char *argv[], char **envp)
{
	char	*command_path;
	char	**arguments;
	int		new_file;

	new_file = open(argv[1], O_RDONLY);
	if (new_file == -1)
	{
		printf("%s : No such file or directory\n", argv[1]);
		close(pipes[1]);
		exit(1);
	}
	arguments = get_args(argv[2]);
	command_path = find_path(arguments[0], envp);
	dup2(new_file, STDIN_FILENO);
	close(new_file);
	dup2(pipes[1], STDOUT_FILENO);
	close(pipes[1]);
	if (execve(command_path, arguments, envp) == -1)
	{
		perror("Execve failed 1");
		exit(127);
	}
}

void	second_child(int pipes[], char *argv[], char **envp)
{
	char	*command_path;
	char	**arguments;
	int		new_file;

	new_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (new_file == -1)
	{
		printf("%s : Problem creating file\n", argv[4]);
		close(pipes[0]);
		exit(1);
	}
	arguments = get_args(argv[3]);
	command_path = find_path(arguments[0], envp);
	dup2(pipes[0], STDIN_FILENO);
	close(pipes[0]);
	dup2(new_file, STDOUT_FILENO);
	close(new_file);
	if (execve(command_path, arguments, envp) == -1)
	{
		perror("Execve failed 1");
		exit(127);
	}
}*/
