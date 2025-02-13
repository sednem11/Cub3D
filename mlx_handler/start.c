#include "../Cub3d.h"

int create_trgb(int red, int green, int blue)
{
    return (red << 16) | (green << 8) | blue;
}

int check_start_map(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return(1);
		i++;
	}
	if (i > 0)
		return(0);
	return(1);
}

int	my_pixel_get(t_image *image, int x, int y, int i)
{
	int	offset;

	y += (i * HEIGHT);
	x += (i * LENGTH);
	offset = (image->line_len * y) + (x * (image->bits_per_pixel / 8));
	return (*(unsigned int *)(image->image_pixel + offset));
}

void	my_pixel_put(t_image **image, int x, int y, int color)
{
	int	offset;

	offset = ((*image)->line_len * y) + (x * ((*image)->bits_per_pixel / 8));
	*((unsigned int *)(offset + (*image)->image_pixel)) = color;
}

void	rendering(t_image **image, int positionx, int positiony, int i)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < LENGTH)
		{
			color = my_pixel_get((*image), x, y, i);
			if (color != -16777216)
				my_pixel_put(&get()->images[2], x + (LENGTH * positionx), y
					+ (HEIGHT * positiony), color);
			x++;
		}
		y++;
	}
}

void	rendering2(int positionx, int positiony)
{
	float	playerpixelx;
	float	playerpixely;
	int		x;
	int		y;
	int		color;
	
	playerpixelx = get()->realpx - positionx;
	playerpixely = get()->realpy - positiony;
	x = ((LENGTH * playerpixelx) - (LENGTH * 0.1));
	y = ((HEIGHT * playerpixely) - (HEIGHT * 0.1));
	while (y < ((HEIGHT * playerpixely) + (HEIGHT * 0.1)))
	{
		x = ((LENGTH * playerpixelx) - (LENGTH * 0.1));
		while (x < ((LENGTH * playerpixelx) + (LENGTH * 0.1)))
		{
			color = create_trgb(200, 0, 0);
			my_pixel_put(&get()->images[2], x + (LENGTH * positionx), y
				+ (HEIGHT * positiony), color);
			x++;
		}
		y++;
	}
}

void	rendering_map()
{
	get()->y = 0;
	while(check_start_map(get()->map[get()->y]) != 0)
		get()->y++;
	while(get()->map[get()->y])
	{
		get()->x = 0;
		while(get()->map[get()->y][get()->x] != '\0')
		{
			if (get()->map[get()->y][get()->x] == '2' || get()->map[get()->y][get()->x] == 'y')
				rendering(&get()->images[0], get()->x, get()->y, 0);
			if (get()->map[get()->y][get()->x] == '1')
				rendering(&get()->images[1], get()->x, get()->y, 0);
			if (get()->map[get()->y][get()->x] == 'y')
				rendering2(get()->x, get()->y);
			get()->x++;
		}
		get()->y++;
	}
	raycasting();
	mlx_put_image_to_window(get()->mlx, get()->window, get()->images[3]->img, 0,
		0);
}

void	create_image_addr(t_image *image)
{
	image->image_pixel = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_len, &image->endian);
	if (!image->image_pixel)
	{
		ft_printf("image_pixel");
		// mlx_end(0);
		exit(1);
	}
}

void	create_image_ptr2(t_image **image, int i)
{
	if (i == 0)
		(*image)->img = mlx_xpm_file_to_image(get()->mlx, get()->texture->no, &(*image)->width, &(*image)->height);
	if (i == 1)
		(*image)->img = mlx_xpm_file_to_image(get()->mlx, get()->texture->so, &(*image)->width, &(*image)->height);
	if (i == 2)
		(*image)->img = mlx_xpm_file_to_image(get()->mlx, get()->texture->ea, &(*image)->width, &(*image)->height);
	if (i == 3)
		(*image)->img = mlx_xpm_file_to_image(get()->mlx, get()->texture->we, &(*image)->width, &(*image)->height);
	if (!(*image)->img)
	{
		printf("%i\n", i);
		ft_printf("AHHH\n");
		ft_printf("ERROR\n");
		// mlx_end(0);
		exit(1);
	}
	create_image_addr(*image);
}

void	create_image_ptr(t_image **image, int width, int height)
{
	(*image)->img = mlx_new_image(get()->mlx, width, height);
	if (!(*image)->img)
	{
		ft_printf("ERROR\n");
		// mlx_end(0);
		exit(1);
	}
	create_image_addr(*image);
}

void create_solid_color_image(t_image **image, int color)
{
    int x;
	int y;
	int *pixel_data;

    (*image)->img = mlx_new_image(get()->mlx, WINDOW_LENGTH / get()->map_x, WINDOW_HEIGHT / get()->map_y);
	(*image)->width = WINDOW_LENGTH / get()->map_x;
	(*image)->height = WINDOW_HEIGHT / get()->map_y;
    if (!(*image)->img)
	{
        printf("ERROR creating image\n");
        // mlx_end(1);
        exit(1);
    }
    create_image_addr(*image);
    pixel_data = (int *)(*image)->image_pixel;
    for (y = 0; y < (*image)->height; y++)
	{
        for (x = 0; x < (*image)->width; x++)
		{
            pixel_data[(y * ((*image)->line_len / 4)) + x] = color;
        }
    }
}


void	init_mlx_window_images(void)
{
	get()->i = 0;
	get()->window = mlx_new_window(get()->mlx, WINDOW_LENGTH, WINDOW_HEIGHT, "Cub_3D");
	get()->images = (t_image **)ft_calloc(8, sizeof(t_image *));
	while(get()->i < 8)
	{
		get()->images[get()->i] = (t_image *)malloc(sizeof(t_image));
		get()->i++;
	}
	create_image_ptr2(&get()->images[0], 0);
	create_image_ptr2(&get()->images[1], 1);
	create_image_ptr(&get()->images[2], WINDOW_LENGTH, WINDOW_HEIGHT);
	create_image_ptr(&get()->images[3], WINDOW_LENGTH, WINDOW_HEIGHT);
	create_image_ptr2(&get()->images[4], 2);
	create_image_ptr2(&get()->images[5], 3);
}

void	change_player(int key)
{
	float	directionangle;

	if (key == 1)
		directionangle = get()->player_angle;
	if (key == 2)
		directionangle = get()->player_angle + 90;
	if (key == 3)
		directionangle = get()->player_angle + 180;
	if (key == 4)
		directionangle = get()->player_angle + 270;
	if (directionangle > 360)
		directionangle -= 360;
	// checking wall colision
	if ((get()->map[get()->py - 1][get()->px] != '1'
		|| get()->realpy - 0.1 * sin(directionangle * (3.1415926 / 180)) > get()->py)
		&& (get()->map[get()->py + 1][get()->px] != '1'
		|| get()->realpy - 0.1 * sin(directionangle * (3.1415926 / 180)) < get()->py + 1))
			get()->realpy -= 0.1 * sin(directionangle * (3.1415926 / 180));
	if ((get()->realpx + 0.1 * cos(directionangle * (3.1415926 / 180)) > get()->px
		|| get()->map[get()->py][get()->px - 1] != '1')
		&& (get()->realpx + 0.1 * cos(directionangle * (3.1415926 / 180)) < get()->px + 1
		|| get()->map[get()->py][get()->px + 1] != '1'))
			get()->realpx += 0.1 * cos(directionangle * (3.1415926 / 180));
	if (get()->realpx < get()->px)
	{
		get()->map[get()->py][get()->px] = '2';
		get()->px -= 1;
		get()->map[get()->py][get()->px] = 'y';
	}
	if (get()->realpy < get()->py)
	{
		get()->map[get()->py][get()->px] = '2';
		get()->py -= 1;
		get()->map[get()->py][get()->px] = 'y';
	}
	if (get()->realpx > get()->px + 1)
	{
		get()->map[get()->py][get()->px] = '2';
		get()->px += 1;
		get()->map[get()->py][get()->px] = 'y';
	}
	if (get()->realpy > get()->py + 1)
	{
		get()->map[get()->py][get()->px] = '2';
		get()->py += 1;
		get()->map[get()->py][get()->px] = 'y';
	}
}

int	handle_input(int keysym)
{
	// if (keysym == XK_Escape)
	// 	mlx_end(1);
	if (keysym == XK_w)
		change_player(1);
	if (keysym == XK_a)
		change_player(2);
	if (keysym == XK_s)
		change_player(3);
	if (keysym == XK_d)
		change_player(4);
	if (keysym == XK_Left)
		get()->player_angle += 2.5;
	if (keysym == XK_Right)
		get()->player_angle -= 2.5;
	rendering_map();
	return(1);
}


void	mlx_start(void)
{
	get()->mlx = mlx_init();
	init_mlx_window_images();
	rendering_map();
	// mlx_hook(get()->window, 17, 0, last_handel_input, NULL);
	mlx_hook(get()->window, 2, (1L << 0), handle_input, NULL);
	// mlx_key_hook(get()->window, handel_input2, NULL);
	mlx_loop(get()->mlx);
}