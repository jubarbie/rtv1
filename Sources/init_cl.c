/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 11:51:06 by jubarbie          #+#    #+#             */
/*   Updated: 2016/11/09 16:57:07 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_cl(t_env *e)
{
	cl_int				err;
	cl_context			context;
	cl_device_id		device;
	cl_device_id		cpu;
	cl_command_queue	cmd_queue;
	char				*pgr_source;
	cl_program			program[0];
	cl_kernel			kernel[1];
	cl_char				vendor_name[1024] = {0};
	cl_char				device_name[1024] = {0};
	size_t				returned_size = 0;
	size_t				buffer_size;

	cpu = NULL;
	device = NULL;
	if ((err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_CPU, 1, &cpu, NULL)) != CL_SUCCESS)
		error_perso(e, "Getting cpu device not working");
	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
	if (err != CL_SUCCESS)
		device = cpu;
	err = clGetDeviceInfo(device, CL_DEVICE_VENDOR, sizeof(vendor_name), vendor_name, &returned_size);
	err = clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(device_name), device_name, &returned_size);
	printf("Connecting to %s %s ...\n", vendor_name, device_name);
	
	pgr_source = load_program_source("sphere.cl");
	program[0] = clCreateProgramWithSource(context, 1, (const char **)&pgr_source,
				NULL, &err);
	if (err != CL_SUCCESS)
		error_perso("Failed creating program");
	kernel[0] = clCreateKernel(program[0], "add", &err);

	obj_mem = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(t_object), NULL, NULL);
	err = clEnqueueWriteBuffer(cmd_queue, a_mem, CL_TRUE, 0, sizeof(t_object));
}
