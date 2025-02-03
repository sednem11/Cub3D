/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:42:28 by macampos          #+#    #+#             */
/*   Updated: 2025/01/23 12:54:37 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx_int.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>


# define WINDOW_LENGTH 900
# define WINDOW_HEIGHT 600
# define SCALE 32

typedef struct s_image
{
	void	*img;
	char	*image_pixel;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}		t_image;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*c;
	char	*f;
}	t_textures;


typedef struct s_data
{
    int		map_y;
	int		map_x;
	int		i;
	int		x;
	int		j;
	int		px;
	int		py;
	float	realpy;
	float	realpx;
	float	fov;
	float	angle_increment;
	float	ray_angle;
	float	player_angle;
	float	distance;
	float	ray_dx;
	float	ray_dy;
	float	delta_distx;
	float	delta_disty;
	float	side_disty;
	float	side_distx;
	int		step_x;
	int		step_y;
	int		wallheight;
	int		lastx;
	int		lasty;
	char	**map;
	t_textures	*texture;
	t_image	**images;
	void	*mlx;
	void	*window;
	int		width;
	int		height;
}   t_data;

t_data	*get(void);

void	parsing(char *name, int fd);
void	mlx_start(void);
// void    raycasting();


#endif