/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:49:53 by macampos          #+#    #+#             */
/*   Updated: 2025/02/18 15:49:30 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	end_before()
{
	int i;

	i = 0;
	if (get()->map)
	{
		while(i < get()->map_y)
		{
			free(get()->map[i]);
			i++;
		}
		free(get()->map);
	}
	if (get()->texture)
	{
		free(get()->texture->c);
		free(get()->texture->f);
		free(get()->texture->ea);
		free(get()->texture->no);
		free(get()->texture->so);
		free(get()->texture->we);
		free(get()->texture);
	}
	i = 0;
	if (get()->images)
	{
		while(get()->images[i] != NULL)
		{
			if (get()->images[i]->img)
				mlx_destroy_image(get()->mlx, get()->images[i]->img);
			free(get()->images[i]);
			i++;
		}
		free(get()->images);
	}
	if (get()->mlx)
	{
		if (get()->window)
			mlx_destroy_window(get()->mlx, get()->window);
		mlx_destroy_display(get()->mlx);
		free(get()->mlx);
	}
	exit(1);
	return(1);
}

void	mapy(int fd)
{
	int i;
	char *temp;
	char *str;

	i = 0;
	temp = get_next_line(fd);
	str = ft_strtrim(temp, "\n ");
	while(temp && check_start_map(str) != 0)
	{
		free(temp);
		free(str);
		temp = get_next_line(fd);
		str = ft_strtrim(temp, "\n ");
	}
	while(1)
	{
		if (temp == NULL)
			break;
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
	int i;
	char *temp;
	char *str;

	i = 0;
	temp = get_next_line(fd);
	str = ft_strtrim(temp, "\n ");
	while(temp && check_start_map(str) != 0)
	{
		free(temp);
		free(str);
		temp = get_next_line(fd);
		str = ft_strtrim(temp, "\n ");
	}
	while(1)
	{
		if (temp == NULL)
			break;
		if (i < (int)ft_strlen(temp))
			i = (int)ft_strlen(temp);
		free(temp);
		temp = get_next_line(fd);
	}
	get()->map_x = i - 1;
	free(temp);
	free(str);
}

void	create_map(char *name)
{
	char	*temp;
	char	*str;
	int 	fd;
	int		j;

	j = 0;
	fd = open(name, O_RDONLY);
	mapy(open(name, O_RDONLY));
	mapx(open(name, O_RDONLY));
	get()->map = (char **)ft_calloc((get())->map_y + 1, sizeof(char *));
	temp = get_next_line(fd);
	str = ft_strtrim(temp, "\n ");
	while(check_start_map(str) != 0)
	{
		free(temp);
		free(str);
		temp = get_next_line(fd);
		str = ft_strtrim(temp, "\n ");
	}
	while (j < get()->map_y)
	{
		(get())->map[j] = ft_strtrim(temp, "\n");
		j++;
		free(temp);
		temp = get_next_line(fd);
	}
	get()->map[get()->map_y] = NULL;
	free(temp);
	free(str);
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

void	get_pangle(char *line)
{
	get()->fov = 60;
	if (line[get()->i] == 'W')
		get()->player_angle = 0;
	else if(line[get()->i] == 'E')
		get()->player_angle = 180;
	else if (line[get()->i] == 'N') 
		get()->player_angle = 90;
	else if (line[get()->i] == 'S')
		get()->player_angle = 270;
}

void	get_pxy(int fd)
{
	char	*line;
	char	*str;

	line = get_next_line(fd);
	str = ft_strtrim(line, "\n ");
	while(check_start_map(str) != 0)
	{
		free(line);
		free(str);
		line = get_next_line(fd);
		str = ft_strtrim(line, "\n ");
	}
	while(line != NULL)
	{
		get()->i = -1;
		while(get()->i++ < (int)ft_strlen(line))
		{
			if (line[get()->i] == 'E' || line[get()->i] == 'W'
				|| line[get()->i] == 'N' || line[get()->i] == 'S')
			{
				get()->px = get()->i;
				get()->py = get()->j;
				get_pangle(line);
			}
		}
		free(line);
		line = get_next_line(fd);
		get()->j++;
	}
	get()->realpx = get()->px + 0.5;
	get()->realpy = get()->py + 0.5;
	free(line);
	free(str);
}

void	check_textures(int fd)
{
	char	*temp;
	char	*str;
	char	**line;
	int		check;
	int 	check2;

	check = 0;
	check2 = 0;
	temp = get_next_line(fd);
	str = ft_strtrim(temp, "\n ");
	while(temp && check_start_map(str) != 0)
	{
		get()->i = 0;
		line = ft_split(str, ' ');
		if (line[0] != NULL && strcmp(line[0], "NO") == 0)
		{
			check2 += 1;
			check += 1;
		}
		else if (line[0] != NULL && strcmp(line[0], "SO") == 0)
		{
			check2 += 1;
			check += 2;
		}
		else if (line[0] != NULL && strcmp(line[0], "WE") == 0)
		{
			check2 += 1;
			check += 3;
		}
		else if (line[0] != NULL && strcmp(line[0], "EA") == 0)
		{
			check2 += 1;
			check += 4;
		}
		else if (line[0] != NULL && strcmp(line[0], "F") == 0)
		{
			check2 += 1;
			check += 5;
		}
		else if (line[0] != NULL && strcmp(line[0], "C") == 0)
		{
			check2 += 1;
			check += 6;
		}
		while(line[get()->i] != NULL)
		{
			free(line[get()->i]);
			get()->i++;
		}
		free(line);
		free(temp);
		free(str);
		temp = get_next_line(fd);
		str = ft_strtrim(temp, "\n ");
	}
	free(str);
	free(temp);
	if (check != 21 || check2 != 6)
	{
		ft_putstr_fd("texture missing or over initialized texture\n", 2);
		end_before();
	}
}

int	check_map(char *name, int fd)
{
    int i;
	(void) fd;

    i = 0;
	check_textures(open(name, O_RDONLY));
    while(name[i] && name[i] != '.')
        i++;
    if (strcmp(&name[i], ".cub") != 0)
        return(1);
    return(0);
}

void	get_floor_cealing(char *line, int i)
{
	char **texture;

	get()->i = 0;
	get()->j = 0;
	texture = NULL;
	if (i == 1)
	{
		texture = ft_split(line, ',');
		get()->texture->f = (int *)ft_calloc(4, sizeof(int));
		while(get()->i < 3)
		{
			get()->texture->f[get()->i] = ft_atoi(texture[get()->i]);
			get()->j += (int)ft_strlen(texture[get()->i] + 1);
			free(texture[get()->i]);
			get()->i++;
		}
	}
	else if (i == 2)
	{
		texture = ft_split(line, ',');
		get()->texture->c = (int *)ft_calloc(4, sizeof(int));
		while(get()->i < 3)
		{
			get()->texture->c[get()->i] = ft_atoi(texture[get()->i]);
			get()->j += (int)ft_strlen(texture[get()->i] + 1);
			free(texture[get()->i]);
			get()->i++;
		}
	}
	free(texture);
}

void	get_texture_help(char *line, int i)
{
	char *str;
	
	get()->j = 2;
	while(line[get()->j] && line[get()->j] == ' ')
		get()->j++;
	if (line[get()->j])
	{
		str = ft_strtrim(&line[get()->j], "\n");
		if (i == 0)
			get()->texture->no = ft_strdup(str);
		else if (i == 1)
			get()->texture->ea = ft_strdup(str);
		else if (i == 2)
			get()->texture->so = ft_strdup(str);
		else if (i == 3)
			get()->texture->we = ft_strdup(str);
		else if (i == 4)
			get_floor_cealing(&line[get()->j], 1);
		else if (i == 5)
			get_floor_cealing(&line[get()->j], 2);
		free(str);
	}
}

void	get_textures(int fd)
{
	char	*line;
	
	line = get_next_line(fd);
	get()->texture = (t_textures *)ft_calloc(1, sizeof(t_textures));
	while(line != NULL)
	{
		
		get()->i = -1;
		while(get()->i < (int)ft_strlen(line) && get()->i++)
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

