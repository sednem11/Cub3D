/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:44:43 by macampos          #+#    #+#             */
/*   Updated: 2025/03/06 16:07:26 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

t_data	*get(void)
{
	static t_data	data;

	return (&data);
}

int	ft_strlen3(char *line)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ')
			j++;
		i++;
	}
	if (j > 0 || i > 3)
		return (j);
	return (-1);
}

int	main(int argc, char **argv)
{
	if (argc != 2 || open(argv[1], O_RDONLY) == -1)
	{
		ft_putstr_fd("wrong input", 2);
		return (1);
	}
	parsing(argv[1], open(argv[1], O_RDONLY));
	mlx_start();
	return (0);
}
