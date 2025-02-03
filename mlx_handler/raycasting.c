#include "../Cub3d.h"
// #define WALL_COLOR 220,100,0
// #define SKY_OR_FLOOR_COLOR 225,30,0

// void    draw_vertical_line(int x, int height)
// {
//     int start = (600 / 2) - (height / 2);
//     int end = start + height;

//     for (int y = 0; y < 600; y++) {
//         if (y >= start && y <= end) {
//             put_pixel(x, y, WALL_COLOR);
//         } else {
//             put_pixel(x, y, SKY_OR_FLOOR_COLOR);
//         }
//     }
// }

// float   cast_single_ray()
// {
//     get()->map_x = (int)get()->realpx;
//     get()->map_y = (int)get()->realpy;
//     get()->ray_dx = cos(get()->ray_angle * (3.1416 / 180));
//     get()->ray_dy = sin(get()->ray_angle * (3.1416 / 180));
//     get()->delta_distx = fabs(1 / get()->ray_dx);
//     get()->delta_disty = fabs(1 / get()->ray_dy);
//     get()->step_x = (get()->ray_dx < 0) ? -1 : 1;
//     get()->step_y = (get()->ray_dy < 0) ? -1 : 1;
//     get()->side_distx = (get()->ray_dx < 0) ? (get()->realpx - get()->map_x) * get()->delta_distx : (get()->map_x + 1.0 - get()->realpx) * get()->delta_distx;
//     get()->side_disty = (get()->ray_dy < 0) ? (get()->realpy - get()->map_y) * get()->delta_disty : (get()->map_y + 1.0 - get()->realpy) * get()->delta_disty;

//     while (1) {
//         if (get()->side_distx < get()->side_disty)
//         {
//             get()->side_distx += get()->delta_distx;
//             get()->map_x += get()->step_x;
//         }
//         else
//         {
//             get()->side_disty += get()->delta_disty;
//             get()->map_y += get()->step_y;
//         }
//         if (get()->map[get()->map_y][get()->map_x] == 1)
//             break;
//         printf("%i, %i\n", get()->map_y, get()->map_x);
//         printf("%c\n", get()->map[get()->map_y][get()->map_x]);
//     }

//     float wall_dist = (get()->side_distx < get()->side_disty) ? get()->side_distx - get()->delta_distx : get()->side_disty - get()->delta_disty;

//     return wall_dist;
// }

// void    raycasting()
// {
//     get()->angle_increment = get()->fov / 600;
//     for(get()->x = 0; get()->x < 600; get()->x++)    
//     {
//         get()->ray_angle = get()->player_angle - (get()->fov / 2) + (get()->x * get()->angle_increment);
//         if (get()->ray_angle < 0)
//             get()->ray_angle += 360.0f;
//         if (get()->ray_angle > 360.0f)
//             get()->ray_angle -= 360.0f;
//         get()->distance = cast_single_ray();
//         get()->wallheight = (int)(600 / get()->distance);
//         draw_vertical_line();
//     }
// }