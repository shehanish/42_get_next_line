/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:58:50 by shkaruna          #+#    #+#             */
/*   Updated: 2024/03/05 17:35:29 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_save(char *str)
{
	int		i;
	int		new_i;
	char	*new_save;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	new_save = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!new_save)
		return (NULL);
	i++;
	new_i = 0;
	while (str[i])
		new_save[new_i++] = str[i++];
	new_save[new_i] = '\0';
	free(str);
	return (new_save);
}

char	*read_and_append(int fd, char *save)
{
	char	*buff;
	int		read_bytes;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (1)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buff[read_bytes] = '\0';
		save = ft_strjoin(save, buff);
		if (!save)
		{
			free(buff);
			return (NULL);
		}
		if (ft_strchr(save, '\n'))
			break ;
	}
	free(buff);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_and_append(fd, save);
	if (!save)
		return (NULL);
	line = extract_line(save);
	save = update_save(save);
	return (line);
}

// int	main()
// {
// 	//int fd;
// 	char *line;
// 	int i;

// 	/*if (argc != 2)
// 	{
// 		printf("Usage: %s file1.txt\n", argv[0]);
// 		return (1);
// 	}

// 	fd = open(argv[1], O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Failed to open file: %s\n", argv[1]);
// 		return (1);
// 	}*/
// 	i = 0;
// 	while ((line = get_next_line(0)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		i++;
// 	}
// 	line = get_next_line(0);
// 	printf("%s", line);
// 	//close(fd);
// }
