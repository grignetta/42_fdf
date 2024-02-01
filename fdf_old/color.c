void draw_bresenham(t_bres_param *params, t_fdf *data, int z, int z1)
{
    // Pre-compute the total distance for color interpolation
    float totalDistance = sqrt((params->x1 - params->x0) * (params->x1 - params->x0) + (params->y1 - params->y0) * (params->y1 - params->y0));
    
    // Start and end colors
    int startColor = data->color; // Initial color
    int endColor = (z != 0) ? 0xff00ff : 0x0fffff; // Determine the end color based on your condition
    
    // Decompose start and end colors into their components
    int startR = (startColor >> 16) & 0xFF;
    int startG = (startColor >> 8) & 0xFF;
    int startB = startColor & 0xFF;
    
    int endR = (endColor >> 16) & 0xFF;
    int endG = (endColor >> 8) & 0xFF;
    int endB = endColor & 0xFF;
    
    // Calculate color component differences
    int diffR = endR - startR;
    int diffG = endG - startG;
    int diffB = endB - startB;
    
    int dx = abs(params->x1 - params->x0), sx = params->x0 < params->x1 ? 1 : -1;
    int dy = -abs(params->y1 - params->y0), sy = params->y0 < params->y1 ? 1 : -1;
    int err = dx + dy, e2;
    
    while (true) // Replace the for loop with a while loop
    {
        // Calculate current distance
        float currentDistance = sqrt((params->x0 - params->xstart) * (params->x0 - params->xstart) + (params->y0 - params->ystart) * (params->y0 - params->ystart));
        // Calculate interpolation factor (0.0 to 1.0)
        float t = 0;
        if (totalDistance > 0) {
            t = currentDistance / totalDistance;
        }
        
        // Interpolate color components
        int currentR = startR + t * diffR;
        int currentG = startG + t * diffG;
        int currentB = startB + t * diffB;
        
        // Combine components back into an integer color
        int currentColor = (currentR << 16) | (currentG << 8) | currentB;
        
        // Draw the pixel with the interpolated color
        if (params->x0 + data->x_shift < data->win_width && params->x0 + data->x_shift > 0 &&
            params->y0 + data->y_shift < data->win_height && params->y0 + data->y_shift > 0) {
            my_mlx_pixel_put(&data->image, (params->x0 + data->x_shift), (params->y0 + data->y_shift), currentColor);
        }
        
        if (params->x0 == params->x1 && params->y0 == params->y1) break;
        
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            params->x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            params->y0 += sy;
        }
    }
}
