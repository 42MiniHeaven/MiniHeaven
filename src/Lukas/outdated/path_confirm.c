/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_confirm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwittwer <lwittwer@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:34:07 by lwittwer          #+#    #+#             */
/*   Updated: 2026/01/13 17:27:02 by lwittwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// ft_strjoin for quick testing

static char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	lenstrjoin;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	lenstrjoin = strlen((char *)s1) + strlen((char *)s2);
	ptr = calloc(lenstrjoin +1, sizeof(char));
	if (ptr == NULL)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		ptr[i + j] = s2[j];
		j++;
	}
	return (ptr);
}

/* Description: HF: checks if a command is executable */

static int	is_executable(const char *path) //make static after debugging
{
	return (access(path, X_OK)); //maybe check also lstat and for other access types
}

/* Description: returns absolute path if executable or NULL*/

static char	*ret_absolute(char *cmd)
{
	if (!cmd)
		return (NULL);
	if (strchr(cmd, '/')) //use ft_strchr
	{
		if (is_executable(cmd) == 0)
			return (strdup(cmd)); //free! and change to ft_strdup
	}
	return (NULL);
}

/* Description: returns built absolute path or NULL if not found*/

static char	*ret_builtabsolute(char *cmd, char **dirs)
{
	char	*absolute;
	char	*tmp;
	int		i;
	if (!cmd || !dirs || !*dirs)
		return (NULL);

	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		if (!tmp)
			return (NULL);
		if (tmp)
		{
			absolute = ft_strjoin(tmp, cmd);
			free(tmp);
		}
		if (absolute && (is_executable(absolute) == 0))
			return (absolute);
		free(absolute);
		i++;
	}
	return (NULL);
}

/* Description: returns built absolute path or NULL if error */

char	*ret_full_path(char *cmd, char **dirs)
{
	char	*ret;
	
	ret = ret_absolute(cmd);
	if (!ret)
	{
		ret = ret_builtabsolute(cmd, dirs);
		if (!ret)
			return (NULL);
	}
	return (ret);
}
