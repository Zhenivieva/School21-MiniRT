/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:55:47 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/25 21:34:26 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <errno.h>
# include <stdio.h>

# include <mlx.h>

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*g_mem;

typedef struct		s_vector
{
	float			x;
	float			y;
	float			z;
}					t_vector;

typedef struct		s_lstobj
{
	int				type;
	void			*obj;
	float			reflective;
	void			*prev;
	void			*next;
}					t_lstobj;

typedef struct		s_canvas
{
	float			height;
	float			width;
	float			distance;
}					t_canvas;

typedef struct		s_sphere
{
	t_vector		*coords;
	t_vector		*color;
	float			radius;
	float			gloss;
}					t_sphere;

typedef struct		s_plane
{
	t_vector		*coords;
	t_vector		*dir;
	t_vector		*color;
	float			gloss;
}					t_plane;

typedef struct		s_square
{
    t_vector		*coords;
    t_vector		*dir;
    float			size;
    t_vector		*color;
    t_vector		*a;
    t_vector		*b;
    t_vector		*c;
    t_vector		*d;
    t_vector		*ab;
    t_vector		*ac;
    float			gloss;
}					t_square;

typedef struct		s_trian
{
	t_vector		*a;
	t_vector		*b;
	t_vector		*c;
	t_vector		*color;
	t_vector		*ab;
	t_vector		*ac;
	t_vector		*normal;
	float			gloss;
	float			abIab;
	float			abIac;
	float			acIac;
	float			d;
}					t_trian;

typedef	struct		s_cylinder
{
	t_vector		*coords;
	t_vector		*dir;
	t_vector		*point1;
	t_vector		*point2;
	float 			diametr;
	float 			height;
	t_vector		*color;
	float			gloss;
}					t_cylinder;

typedef struct		s_camera
{
	t_vector		*coords;
	t_vector		*direction;
	int				fov;
}					t_camera;

typedef struct		s_light
{
    int				type;
    t_vector		*coords;
	float			bright;
	t_vector		*color;
}					t_light;

typedef struct		s_scene
{
	t_canvas		*vport;
	t_canvas		*vplane;
	t_lstobj		*cams;
	t_lstobj		*objs;
	t_lstobj		*lights;
	int				cam_num;
	int				background_color;
	int				depth;
	float			sum_bright;
	float			t_min;
	float			t_max;
}					t_scene;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	t_scene			*scene;

}					t_mlx;

typedef	struct		s_params
{
	t_vector		*l_vectors[3];
	t_scene			*scene;
	t_vector		*color[4];
	float			gloss;
}					t_params;

/* parsing:      */
t_scene		*parse_main(int fd);
void		move_by_space(char **stroka);
void		check_end_of_str(char **stroka);
long int	get_int(char **stroka);
float		get_mantfloat(char **stroka, float cel_float);
int			parse_resolution(t_scene **scene, char *stroka);
int			parse_alight(t_scene **scene, char *stroka);
int			parse_cam(t_scene **scene, char *stroka);
int			parse_plight(t_scene **scene, char *stroka);
int			parse_sphere(t_scene **scene, char *stroka);
int			parse_plane(t_scene **scene, char *stroka);
int			parse_square(t_scene **scene, char *stroka);
int			parse_triangle(t_scene **scene, char *stroka);
int			parse_cylinder(t_scene **scene, char *stroka);

/* utils:        */
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_save(char *buf, char *ost);
char		*ft_check_line(char *ost, char **line, int resread);
int			retresread(char **ost, int fd);
int			get_next_line(int fd, char **line);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s1);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *l_new);
void		ft_lstclear(t_list **lst);
void		free_and_null(void **ptr);

/* vectors:      */
t_vector	*new_vector(float x, float y, float z);
t_vector	*copy_vector(t_vector *v1);
float		scal_mult_vec(t_vector v1, t_vector v2);
float		length_vec(t_vector vector);
float		dist_vec(t_vector v1, t_vector v2);
t_vector	*cross_vect(t_vector v1, t_vector v2);
t_vector	*add_vect(t_vector v1, t_vector v2);
t_vector	*subtract_vect(t_vector v1, t_vector v2);
t_vector	*mult_vect(t_vector v1, float t);
int			color_vect_to_int(t_vector *color);
t_vector	*color_int_to_vect(unsigned int color);
void		set_maxmin_color(t_vector *color);
void		normalise_vect(t_vector *vector);
t_vector	*get_normalised_vect(t_vector *vec);
void		rot_v1_v2(t_vector *v1, t_vector *vec_angle);
void		rot_x(t_vector *v1, float a);
void		rot_y(t_vector *v1, float a);
void		rot_z(t_vector *v1, float a);
t_vector	add_vvect(t_vector v1, t_vector v2);

/* main:        */
void		print_errors(int ernum);
int			finish(void);
int			key_press(int b, t_mlx *mmlx);
void		make_bmp(t_mlx *mmlx);

/* scene:       */
t_scene		*new_scene();
t_canvas	*new_canvas(float width, float height, float distance);
t_camera	*new_camera(t_vector *coords, t_vector *direction, int fov);
void		set_cam(t_scene **scene);
void		set_viewplane(t_scene **scene);
t_vector	*make_cam_crd(t_vector *coord, t_vector *dir);
t_light		*new_light(int type, t_vector *coords, float bright, t_vector
*color);
t_lstobj	*new_obj(void  *object, int type, float reflective);
int			lstadd_back(t_lstobj **lst, void *object, int type, float
reflective);

/* objects:       */
t_sphere	*new_sphere(t_vector *coords, float radius, t_vector *color);
t_plane		*new_plane(t_vector *coords, t_vector *dir, t_vector *color);
t_square	*new_square(t_vector *coords, t_vector *dir, float size, t_vector
*col);
t_trian		*new_trian(t_vector *a, t_vector *b, t_vector *c, t_vector *col);
t_cylinder	*new_cylinder(t_vector *coords, t_vector *dir, float param[2],
							t_vector *col);

/* mlx:          */
void		my_pixel_put(t_mlx *mmlx, int x, int y, int color);
void		fill_image(t_mlx *mmlx, int x, int y);
void		create_image(t_mlx *my_mlx);

/* raytracing:   */
float		get_intersec(t_vector coords, t_vector direction, t_lstobj *object);
float		intersec_sphere(t_sphere *sphere, t_vector coords, t_vector
direction);
float		intersec_plane(t_plane *object, t_vector coords, t_vector direction);
float		intersec_square(t_square *sqr, t_vector coords, t_vector direction);
float		intersec_triangle(t_trian *trian, t_vector coords, t_vector
direction);
float		intersec_cylinder(t_cylinder *cyl, t_vector coords, t_vector
direction);
int			raytraycing(t_vector direction, t_scene *scene);
t_lstobj	*closest_obj_intersect(t_vector coords, t_vector direction,
t_scene *scene, float *closest_t);
int			calc_color_with_light(t_lstobj *closest_obj, t_vector direction,
float closest_t, t_scene *scene);

/* lightning:   */
int			compute_lightning(t_vector *l_vectors, t_lstobj *lights,
t_scene *scene, t_lstobj *objects);
float		compute_special_lights(t_params *params, t_light *light,
t_lstobj *objects);
void		calculate_normal(t_params *params, t_light *light, t_lstobj
*objects);
t_vector	*type_light(t_params *params, t_light *light);
void		check_light_intersec_sphere(t_vector *l_vectors, void *object);
void		check_light_intersec_plane(t_vector *l_vectors, void *object,
t_light *light);
void		check_light_intersec_triangle(t_vector *l_vectors, void *object,
t_light *light);
void		check_light_intersec_square(t_vector *l_vectors, void *object,
									 t_light *light);
void		check_light_intersec_cyl(t_params *params, void *object,
t_light *light);
t_vector 	*get_color(t_lstobj *objects);
float		calcul_shiny(t_vector *l_vectors, t_light *light, t_vector *vec_l,
float gloss);
void		set_color_special_lights(float *bright, t_params *params,
t_lstobj *objects, t_lstobj *lights);
void		set_color_ambient (t_vector *color[4], float *bright,
t_lstobj  *lights);
int			color_with_reflect(t_lstobj *closest_object, t_scene *scene,
t_vector *l_vectors, int color);
t_vector	*reflect_ray(t_vector v1, t_vector v2);

#endif
