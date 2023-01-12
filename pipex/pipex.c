/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynafiss <ynafiss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:03:36 by ynafiss           #+#    #+#             */
/*   Updated: 2022/12/22 15:32:52 by ynafiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get(char **env, char *cmd, int f)
{
	int		i;
	char	**path;
	char	*path_f;
	char	*envv;

	i = 0;
	if (cmd == NULL)
		com_n(cmd);
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	envv = env[i] + 5;
	i = 0;
	path = ft_split(envv, ':');
	path_f = ft_strjoin(path[i++], cmd);
	while (access(path_f, X_OK) != 0 && path[i])
	{
		free(path_f);
		path_f = ft_strjoin(path[i++], cmd);
	}
	free(path);
	if (access(path_f, X_OK) == 0)
		return (path_f);
	else
		com_n(cmd);
	return (cmd);
}

void	sucond_cmd(char **env, int *fd, char **av, int ch1)
{
	int		fd1;
	char	**cmd2;
	char	*path;

	fd1 = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd1 == -1)
	{
		perror("Error opening file");
		exit (1);
	}
	cmd2 = ft_split(av[3], ' ');
	if (cmd2 == NULL)
		exit (127);
	if (av[3][0] == '/')
		path = av[3];
	else
		path = get(env, cmd2[0], 2);
	close(fd[1]);
	waitpid(ch1, NULL, 0);
	dup2(fd[0], 0);
	dup2(fd1, 1);
	execve(path, cmd2, env);
}

void	first_cmd(char **env, int *fd, char **av)
{
	int		fd0;
	char	**cmd1;
	char	*path;
	char	*d;

	d = av[1];
	fd0 = open(av[1], O_RDONLY);
	if (fd0 == -1)
	{
		write(2, "no such a file or directory: ", 29);
		write(2, d, ft_strlen(d));
		exit (1);
	}
	cmd1 = ft_split(av[2], ' ');
	if (av[2][0] == '/' && access(av[2], X_OK) == 0)
		path = av[2];
	else
		path = get(env, cmd1[0], 1);
	if (cmd1 == NULL)
		exit (0);
	dup2(fd[1], 1);
	dup2(fd0, 0);
	close(fd[0]);
	execve(path, cmd1, env);
}

int	pipex(char **av, char **env, int *fd)
{
	int	ch1;
	int	ch2;
	int	status;

	if (pipe(fd) == -1)
		perror("PIPE");
	ch1 = fork();
	if (ch1 == -1)
		perror("fork1 failed");
	if (ch1 == 0)
		first_cmd(env, fd, av);
	ch2 = fork();
	if (ch2 == -1)
		perror("fork2 failed");
	if (ch2 == 0)
		sucond_cmd(env, fd, av, ch1);
	close(fd[1]);
	close(fd[0]);
	waitpid(ch1, NULL, 0);
	waitpid(ch2, &status, 0);
	if (WIFEXITED(status))
		exit (WEXITSTATUS(status));
	return (1);
}

int	main(int ac, char **av, char **env)
{
	int	fd[2];

	if (!env[0])
		exit (2);
	if (ac != 5)
	{
		perror("Invalid number of arguments.");
		exit(1);
	}
	if (ac == 5)
	{
		if (!av[3])
			exit (127);
		pipex(av, env, fd);
	}
}
