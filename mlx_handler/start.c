#include "../Cub3d.h"

void	rendering_map()
{

}

void	init_mlx_window_images(void)
{
	get()->i = 0;
	get()->window = mlx_new_window(get()->mlx, WINDOW_LENGTH, WINDOW_HEIGHT, "Cub_3D");
	get()->images = (t_image **)ft_calloc(5, sizeof(t_image *));
	while(get()->images[get()->i])
	{
		get()->images[get()->i] = (t_image *)ft_calloc(1, sizeof(t_image));
		get()->i++;
	}
}



void	mlx_start(void)
{
	get()->mlx = mlx_init();
	init_mlx_window_images();
	rendering_map();
    // raycasting();
	// mlx_hook(get()->window, 17, 0, last_handel_input, NULL);
	// mlx_hook(get()->window, 2, (1L << 0), handel_input, NULL);
	// mlx_key_hook(get()->window, handel_input2, NULL);
	mlx_loop(get()->mlx);
}