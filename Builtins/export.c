/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:10:57 by kcouchma          #+#    #+#             */
/*   Updated: 2024/02/26 19:11:20 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./../Pipex/pipex.h"

// if export only, print all of envp to the terminal except the variable "_"
// copy and sort envp, (and free at the end) then in loop add declare -x add "" around the string(after = and at the end)

// if export (variable), then add "variable"+"="+"variable value" to env
// if export (variable=value), then add "variable=value" to env
// in both cases, overwrite variable if present, add if not

////////////// LIBFT FUNCTIONS TO DELETE ///////////////////////////////
int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	if (tab)
		while (tab[i])
			i++;
	return (i);
}

size_t	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(const char *s)
{
	char	*output;

	output = malloc(ft_strlen(s) + 1);
	if (output == NULL)
		return (NULL);
	ft_strlcpy(output, s, ft_strlen(s) + 1);
	return (output);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < (size -1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

/////////////////////////////////////////////////////////////

static int	_sorted(char **ex)
{
	int	i;

	i = 0;
	while (ex[i] && ex[i + 1])
	{
		if (ft_strncmp(ex[i], ex[i + 1], ft_strlen(ex[i]) > 0))
			return (1) ;
		i++;
	}
	return (0);
}

static void	_sort_export(char **ex)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (_sorted(ex))
	{
		while (ex[i] && ex[i + 1])
		{
			ft_strncmp(ex[i], ex[i + 1], 5);
			if (ft_strncmp(ex[i], ex[i + 1], ft_strlen(ex[i])) > 0)
			{
				temp = ex[i];
				ex[i] = ex[i + 1];
				ex[i + 1] = temp;
				temp = NULL;
			}
			i++;
		}
		i = 0;
	}
}

// int ft_export(t_struct *main)
int ft_export(char **envp)
{
	int		i;
	char	**f_envp;
	char	**export;

	i = 0;
	// f_envp = main->common.f_envp;
	f_envp = envp;
	
	//if commmand is "export" only
	export = malloc (sizeof(char *) * ft_tablen(f_envp) + 1);
	if (!export)
		return (EXIT_FAILURE);
	while(f_envp[i])
	{
		export[i] = ft_strdup(f_envp[i]);
		if (!export[i])
			// return (ft_freetable(export), EXIT_FAILURE);
			return (EXIT_FAILURE);
		i++;
	}
	export[i] = NULL;
	_sort_export(export);
	i = 0;
	while(export[i])
	{
		if (export[i][0] != '_')
		{
			write(STDOUT_FILENO, export[i], ft_strlen(export[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		i++;
	}
	// ft_freetable(export);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	argc = 0;
	argv = NULL;
	ft_export(envp);
	return (0);
}

