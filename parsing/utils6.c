/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:47:12 by macampos          #+#    #+#             */
/*   Updated: 2025/02/20 09:53:59 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	mapy(int fd)
{
	int		i;
	char	*temp;
	char	*str;

	i = 0;
	temp = get_next_line(fd);
	str = ft_strtrim(temp, "\n ");
	while (temp && check_start_map(str) != 0)
	{
		free(temp);
		free(str);
		temp = get_next_line(fd);
		str = ft_strtrim(temp, "\n ");
	}
	while (1)
	{
		if (temp == NULL)
			break ;
		i++;
		free(temp);
		temp = get_next_line(fd);
	}
	free(str);
	free(temp);
	get()->map_y = i;
}

void	mapx(int fd)
{
	int		i;
	char	*temp;
	char	*str;

	i = 0;
	temp = get_next_line(fd);
	str = ft_strtrim(temp, "\n ");
	while (temp && check_start_map(str) != 0)
	{
		free(temp);
		free(str);
		temp = get_next_line(fd);
		str = ft_strtrim(temp, "\n ");
	}
	while (1)
	{
		if (temp == NULL)
			break ;
		if (i < (int)ft_strlen(temp))
			i = (int)ft_strlen(temp);
		free(temp);
		temp = get_next_line(fd);
	}
	get()->map_x = i - 1;
	free(str);
}

void	create_map(char *name)
{
	char	*temp;
	char	*str;
	int		fd;
	int		j;

	j = 0;
	temp = NULL;
	str = NULL;
	fd = open(name, O_RDONLY);
	mapy(open(name, O_RDONLY));
	mapx(open(name, O_RDONLY));
	get()->map = (char **)ft_calloc((get())->map_y + 1, sizeof(char *));
	help_create_map(temp, fd, str, j);
}

void	floodfill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == '2' || map[y][x] == 'w'
		|| map[y][x] == 'n' || map[y][x] == 's' || map[y][x] == 'e'
		|| map[y][x] == 'y')
		return ;
	if (!map[y][x] || map[y][x] == ' ' || y <= 0 || x <= 0)
	{
		printf("dead flood\n");
		end_before();
	}
	map[get()->py][get()->px] = 'y';
	if (map[y][x] == '0')
		map[y][x] = '2';
	floodfill(map, (x + 1), y);
	floodfill(map, (x - 1), y);
	floodfill(map, x, (y + 1));
	floodfill(map, x, (y - 1));
}

void	check_textures(int fd)
{
	char	*temp;
	char	*str;
	char	**line;

	get()->check = 0;
	get()->check2 = 0;
	temp = get_next_line(fd);
	str = ft_strtrim(temp, "\n ");
	while (temp && check_start_map(str) != 0)
	{
		get()->i = 0;
		line = ft_split(str, ' ');
		help_check_textures2(&line);
		free(temp);
		free(str);
		temp = get_next_line(fd);
		str = ft_strtrim(temp, "\n ");
	}
	free(str);
	free(temp);
	if (get()->check != 21 || get()->check2 != 6)
	{
		ft_putstr_fd("texture missing or over initialized texture\n", 2);
		end_before();
	}
}
