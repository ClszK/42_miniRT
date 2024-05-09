/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:54:01 by jeholee           #+#    #+#             */
/*   Updated: 2024/05/10 00:34:15 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void mini_init(t_minirt *mi, char *argv[]) {
  mi->camera = NULL;
  obj_init(&mi->render.world);
  obj_init(&mi->render.light);
  file_parse(argv, mi);
  if (mi->camera == NULL || mi->render.has_amb == FALSE ||
      dlst_count(&mi->render.light) == 0 || dlst_count(&mi->render.world) == 0)
    error_exit("Error\nInvalid elements\n");
  mi->canvas = canvas_init(1280, 720);
  camera_init(mi->canvas, mi->camera);
  mi->vars.mlx = mlx_init();
  mi->vars.win = mlx_new_window(mi->vars.mlx, mi->canvas.image_width,
                                mi->canvas.image_height, "minirt");
  mi->image.img = mlx_new_image(mi->vars.mlx, mi->canvas.image_width,
                                mi->canvas.image_height);
  mi->image.addr = mlx_get_data_addr(mi->image.img, &mi->image.bits_per_pixel,
                                     &mi->image.line_length, &mi->image.endian);
  mi->rendering = FALSE;
  mi->render.has_amb = FALSE;
  mi->yaw = 0;
  mi->pitch = 0;
  mi->start_dir = mi->camera->cam_dir;
  mi->start_center = mi->camera->center;
}

int re_render(t_minirt *mini) {
  if (mini->rendering == TRUE) {
    render(&mini->render, &mini->canvas, mini->camera, &mini->image);
    mlx_put_image_to_window(mini->vars.mlx, mini->vars.win, mini->image.img, 0,
                            0);
    mini->rendering = FALSE;
  }
  return (0);
}

int main(int argc, char *argv[]) {
  t_minirt mi;

  if (argc != 2) error_exit("Error\nUsage: ./miniRT filename.rt\n");
  mini_init(&mi, argv);
  render(&mi.render, &mi.canvas, mi.camera, &mi.image);
  mlx_put_image_to_window(mi.vars.mlx, mi.vars.win, mi.image.img, 0, 0);
  mlx_key_hook(mi.vars.win, key_hook, &mi);
  mlx_loop_hook(mi.vars.mlx, re_render, &mi);
  mlx_loop(mi.vars.mlx);
  return (0);
}
