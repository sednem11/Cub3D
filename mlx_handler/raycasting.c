#include "../Cub3d.h"

void draw_vertical_line(int x, int height)
{
    int start = (WINDOW_HEIGHT / 2) - (height / 2);
    int end = start + height;

    // Draw ceiling
    for (int y = 0; y < start; y++)
        my_pixel_put(&get()->images[3], x, y, create_trgb(get()->texture->f[0], get()->texture->f[1], get()->texture->f[2]));

    // Draw wall
    for (int y = start; y < end && y < WINDOW_HEIGHT; y++)
        my_pixel_put(&get()->images[3], x, y, create_trgb(get()->texture->c[0], get()->texture->c[1], get()->texture->c[2]));

    // Draw floor
    for (int y = end; y < WINDOW_HEIGHT; y++)
        my_pixel_put(&get()->images[3], x, y, create_trgb(get()->texture->f[0], get()->texture->f[1], get()->texture->f[2]));
}

float   cast_single_ray()
{
    float   dist_x;
    float   dist_y;

    get()->calcx = get()->realpx;
    get()->calcy = get()->realpy;
    get()->ray_dx = cos(get()->ray_angle * (3.1415926 / 180));
    get()->ray_dy = sin(get()->ray_angle * (3.1415926 / 180));
    get()->step_x = (get()->ray_dx < 0) ? -1 : 1;
    get()->step_y = (get()->ray_dy < 0) ? 1 : -1;
    get()->side_distx = (get()->step_x > 0) ? ((int)(get()->calcx + 1) - get()->calcx) : (get()->calcx - (int)get()->calcx);
    get()->side_disty = (get()->step_y > 0) ? ((int)(get()->calcy + 1) - get()->calcy) : (get()->calcy - (int)get()->calcy);
    dist_x = get()->side_distx / fabs(get()->ray_dx);
    dist_y = get()->side_disty / fabs(get()->ray_dy);
    while (1) {
        // printf("sidex%f\n", get()->side_distx);
        // printf("sidey%f\n", get()->side_disty);
        // printf("distx%f\n", dist_x);
        // printf("disty%f\n", dist_y);
        if (dist_x < dist_y) {
            printf("1\n");
            get()->calcx += get()->step_x;
            if (get()->map[(int)get()->calcy][(int)get()->calcx] == '1') {
                // printf("%f, %c, x%i, y%i\n", dist_x, get()->map[(int)get()->calcy][(int)get()->calcx], (int)get()->calcx, (int)get()->calcy);
                return fabs(dist_x);
            }
            dist_x += fabs(1 / get()->ray_dx);
        } else {
            printf("2\n");
            // get()->calcy = (int)get()->calcy;
            get()->calcy += get()->step_y;
            if (get()->map[(int)get()->calcy][(int)get()->calcx] == '1') {
                // printf("%f, %c, x%i, y%i\n", dist_y, get()->map[(int)py][(int)px], (int)px, (int)py);
                return fabs(dist_y);
            }
            dist_y += fabs(1 / get()->ray_dy);
        }
    }
}

// float   cast_single_ray()
// {
//     get()->i = get()->px;
//     get()->y = get()->py;
//     // printf("%f, %f\n",get()->realpy, get()->realpx);
//     get()->ray_dx = cos(get()->ray_angle * (3.1415926 / 180));
//     get()->ray_dy = sin(get()->ray_angle * (3.1415926 / 180));
//     get()->delta_distx = fabs(1 / (get()->ray_dx));
//     get()->delta_disty = fabs(1 / (get()->ray_dy));
//     get()->step_x = (get()->ray_dx < 0) ? -1 : 1;
//     get()->step_y = (get()->ray_dy < 0) ? -1 : 1;
//     // printf("%i\n", get()->step_x);
//     get()->side_distx = (get()->ray_dx < 0) ? (get()->realpx - get()->i) * get()->delta_distx : (get()->i + 1.0 - get()->realpx) * get()->delta_distx;
//     get()->side_disty = (get()->ray_dy < 0) ? (get()->realpy - get()->y) * get()->delta_disty : (get()->y + 1.0 - get()->realpy) * get()->delta_disty;
//     // printf("%f\n", get()->side_distx);
//     while (1) {
//         if (get()->side_distx < get()->side_disty)
//         {
//             get()->side_distx += get()->delta_distx;
//             get()->i += get()->step_x;
//         }
//         else
//         {
//             get()->side_disty += get()->delta_disty;
//             get()->y -= get()->step_y;
//         }
//         if (get()->map[get()->y][get()->i] == '1')
//             break;
//     }

//     float wall_dist = (get()->side_distx < get()->side_disty) 
//         ? (get()->side_distx - get()->delta_distx)
//         : (get()->side_disty - get()->delta_disty);
//     // printf("%f, x%f, %f, %f\n", wall_dist, get()->side_distx, get()->delta_distx, get()->ray_angle);
//     // printf("%f, y%f, %f, %f\n", wall_dist, get()->side_disty, get()->delta_disty, get()->ray_angle);
//     printf("%f, %c, x%i, y%i\n", wall_dist, get()->map[get()->y][get()->i], get()->i, get()->y);
//     return wall_dist;
// }

void    raycasting()
{
    get()->angle_increment = get()->fov / WINDOW_LENGTH;
    for(get()->x = 0; get()->x < WINDOW_LENGTH; get()->x++)    
    {
        get()->ray_angle = get()->player_angle + (get()->fov / 2) - (get()->x * get()->angle_increment);
        if (get()->ray_angle < 0)
            get()->ray_angle += 360.0f;
        if (get()->ray_angle > 360.0f)
            get()->ray_angle -= 360.0f;
        get()->distance = cast_single_ray();
        printf("%f\n", get()->distance);
        if (get()->distance < 0.01f)
            get()->distance = 0.1f;
        get()->wallheight = (int)(WINDOW_HEIGHT / get()->distance);
        if (get()->wallheight > WINDOW_HEIGHT)
            get()->wallheight = WINDOW_HEIGHT;
        draw_vertical_line(get()->x, get()->wallheight);
    }
}