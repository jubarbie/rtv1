__kernel void
sphere(	__global t_object *obj,
		__local	t_ray	*ray
		__global 

void	sphere(t_object *obj, t_ray *ray)
{
	t_v3d	o;
	t_v3d	q;
	float	r;
	float	t1;
	float	t2;

	o = v3d(obj->pos.x, obj->pos.y, obj->pos.z);
	r = obj->param[0];
	q.x = ray->dir.x * ray->dir.x + ray->dir.y * ray->dir.y + ray->dir.z * ray->dir.z;
	q.y = 2.0 * (ray->dir.x * (ray->pos.x - o.x) + ray->dir.y * (ray->pos.y - o.y) +
			ray->dir.z * (ray->pos.z - o.z));
	q.z = (pow(ray->pos.x - o.x, 2.0) + pow(ray->pos.y - o.y, 2.0) +
			pow(ray->pos.z - o.z, 2.0)) - r * r;
	r = q.y * q.y - 4.0 * q.x * q.z;
	if (r >= 0.0)
	{
		t1 = (-q.y + sqrt(r)) / 2.0 * q.x;
		t2 = (-q.y - sqrt(r)) / 2.0 * q.x;
		t1 = fmin(t1, t2);
		if (t1 < ray->dist)
		{
			ray->obj = obj;
			ray->dist = t1;
			ray->inter = add_v3d(ray->pos, smul_v3d(ray->dir, t1));
			ray->norm = unit_v3d(sub_v3d(ray->inter, obj->pos));
		}
	}
}