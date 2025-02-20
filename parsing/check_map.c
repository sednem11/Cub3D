/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:49:53 by macampos          #+#    #+#             */
/*   Updated: 2025/02/20 09:48:05 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	check_map(char *name, int fd)
{
	int	i;

	(void)fd;
	i = 0;
	check_textures(open(name, O_RDONLY));
	while (name[i] && name[i] != '.')
		i++;
	if (strcmp(&name[i], ".cub") != 0)
		return (1);
	return (0);
}

void	get_floor_cealing(char *line, int i)
{
	char	**texture;

	get()->i = 0;
	get()->j = 0;
	texture = NULL;
	if (i == 1)
	{
		texture = ft_split(line, ',');
		(get()->texture->f) = ft_calloc(4, sizeof(int));
		while (get()->i < 3)
		{
			get()->texture->f[get()->i] = ft_atoi(texture[get()->i]);
			get()->j += (int)ft_strlen(texture[get()->i] + 1);
			free(texture[get()->i]);
			get()->i++;
		}
	}
	else if (i == 2)
		cealing_texture(&texture, &line);
	free(texture);
}

void	get_textures(int fd)
{
	char	*line;

	line = get_next_line(fd);
	get()->texture = (t_textures *)ft_calloc(1, sizeof(t_textures));
	while (line != NULL)
	{
		get()->i = -1;
		while (get()->i < (int)ft_strlen(line) && get()->i++)
		{
			if (ft_strncmp(&line[get()->i], "NO ", 3) == 0)
				get_texture_help(&line[get()->i], 0);
			else if (ft_strncmp(&line[get()->i], "EA ", 3) == 0)
				get_texture_help(&line[get()->i], 1);
			else if (ft_strncmp(&line[get()->i], "SO ", 3) == 0)
				get_texture_help(&line[get()->i], 2);
			else if (ft_strncmp(&line[get()->i], "WE ", 3) == 0)
				get_texture_help(&line[get()->i], 3);
			else if (ft_strncmp(&line[get()->i], "F ", 2) == 0)
				get_texture_help(&line[get()->i], 4);
			else if (ft_strncmp(&line[get()->i], "C ", 2) == 0)
				get_texture_help(&line[get()->i], 5);
		}
		free(line);
		line = get_next_line(fd);
	}
}

void	parsing(char *name, int fd)
{
	if (check_map(name, fd) == 1)
	{
		ft_putstr_fd("map is not acording to the needs", 2);
		end_before();
	}
	create_map(name);
	get_pxy(open(name, O_RDONLY));
	get_textures(open(name, O_RDONLY));
	floodfill(get()->map, get()->px, get()->py);
}
