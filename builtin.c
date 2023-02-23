/*
 * File: builtin.c
 * Auth: Haile Baranto
 *       Dayo Farayola
 */

#include "main.h"
int (*get_builtin(char *command))(char **args, char **front);
int simle_shell_exit(char **args, char **front);
int simple_shell_cd(char **args, char __attribute__((__unused__)) **front);
int simple_shell_help(char **args, char __attribute__((__unused__)) **front);

/**
 * get_builtin - Matches a command with a corresponding
 *               shell builtin function.
 * @command: command to be matched.
 *
 * Return: A function pointer to the corresponding builtin command.
 */
int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", simple_shell_exit },
		{ "env", simple_shell_env },
		{ "setenv", simple_shell_setenv },
		{ "unsetenv", simp_shell_unsetenv },
		{ "cd", simple_shell_cd },
		{ "alias", simple_shell_alias },
		{ "help", simple_shell_help },
		{ NULL, NULL }
	};
	int count;

	for (count = 0; funcs[count].builtin_command; count++)
	{
		if (str_cmp(funcs[count].builtin_command, command) == 0)
			break;
	}
	return (funcs[count].f);
}

/**
 * simple_shell_exit - normal process termination
 *                for the simple_shell shell.
 * @args: An array of arguments containing the exit value.
 * @begining: A double pointer to the beginning of args.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         otherwise - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */
int simple_shell_exit(char **args, char **begining)
{
	int cont, length_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			cont = 1;
			length_of_int++;
		}
		for (; args[0][cont]; cont++)
		{
			if (cont <= length_of_int && args[0][cont] >= '0' && args[0][cont] <= '9')
				num = (num * 10) + (args[0][cont] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_args(args, begining);
	free_enviroment();
	free_alias_list(aliases);
	exit(num);
}

/**
 * simple_shell_cd - Changes the current directory of the simple_shell process.
 * @args: pointer array of arguments.
 * @begening: A double pointer to the beginning of args.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int simple_shell_cd(char **args, char __attribute__((__unused__)) **begening)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || str_cmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (get_enviroment("OLDPWD") != NULL)
					(chdir(*get_enviroment("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (get_enviroment("HOME") != NULL)
			chdir(*(get_enviroment("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (simple_shell_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (simple_shell_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, str_len(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * simple_shell_help - Displays information about simle
 * -shell builtin commands.
 * @args: An array of arguments.
 * @begening: A pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int simple_shell_help(char **args, char __attribute__((__unused__)) **begening)
{
	if (!args[0])
		help_all();
	else if (str_cmp(args[0], "alias") == 0)
		help_alias();
	else if (str_cmp(args[0], "cd") == 0)
		help_cd();
	else if (str_cmp(args[0], "exit") == 0)
		help_exit();
	else if (str_cmp(args[0], "env") == 0)
		help_env();
	else if (str_cmp(args[0], "setenv") == 0)
		help_setenv();
	else if (str_cmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (str_cmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, str_len(name));

	return (0);
}
