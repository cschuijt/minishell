/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dir_builtins.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 19:38:38 by mde-cloe      #+#    #+#                 */
/*   Updated: 2023/03/08 19:38:38 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

#define CHDIR_ERROR	"\x1b[38;2;255;192;128m\x1b[1m \
cd? more like c deez error messages haHA\x1b[0m"

//changed from void to char * ret so it can be used internally, if u dont like
// it this way I can also just make 1 only for printing and put the instructions
// in cd
// 3/4 update.. yeah I might refactor this cause I can just call getcwd
void	pwd(t_argument *args, t_shell *shell)
{
	char	*path;

	(void) args;
	(void) shell;
	path = getcwd(NULL, 0);
	if (!path)
		error_exit(MAL_ERR, errno);
	printf("%s\n", path);
	//do i need to give a newline??
	// set PWD in ENVP!
	free(path);
}
// so.. yeah getcwd seems to make this basicly a freebie?
// Idk if there's edgecases that im not thinking of

void	cd(t_argument *args, t_shell *shell)
{
	char	current_dir[PATH_MAX];
	char	*new_dir;

	new_dir = NULL;
	if (!getcwd(current_dir, PATH_MAX) || access(current_dir, F_OK) != 0)
	{
		perror(C_RED "current dir destroyed, I'm going HOME >:c\n" C_RESET);
		args = NULL;
	}
	if (!args)
		new_dir = get_env_var_value("HOME", shell->environment); //should be new alloc
	//other arguments just get ignored by bash :)
	else if (args->content && args->content[0] == '-' && !args->content[1])
		new_dir = get_env_var_value("OLDPWD", shell->environment);
	if (!new_dir || !*new_dir)
		dprintf(2, C_RED " you can't cd to your HOME or OLDPWD if its not set silly! \
				\n" C_RESET);
	if (chdir(new_dir) == -1)
		perror(CHDIR_ERROR);
	//set new PWD and old PWD
	return ;
}
// EDGECASE deleting current dir and then cding
// solve by access checking first->if false cd OLDPWD if false cd HOME if false
// then cmon bro then your minishell wouldnt even be there anymore

void	builtin_exit(t_argument *args, t_shell *shell)
{
	(void)shell; //do we have to free before exiting?
	printf("exit\n");
	if (args && args->content)
		exit(ft_atoi(args->content)); //custom atoi that protects against >230 overflow?
	exit(10);
}

void	echo(t_argument *args, t_shell *shell)
{
	(void)args;
	(void)shell;
}

void	export(t_argument *args, t_shell *shell)
{
	if (!args)
		print_2d_charray(shell->envp); //sort alphabetically?
	else if (!ft_strchr(args->content, (int) '='))
	{
		puts("placeholder");
	}
}

void	env(t_argument *args, t_shell *shell)
{
	(void)args;
	(void)shell;
	print_2d_charray(shell->envp);
}
//ok so, cd both starting with dir names and ./dirname should function the same
// ./../ is possible though!

// bash cd doesnt go into hidden directories nice
// cd blank space/with no args goes to home folder??

// https://man7.org/linux/man-pages/man1/cd.1p.html

void		unset(t_argument *args, t_shell *shell)
{

}