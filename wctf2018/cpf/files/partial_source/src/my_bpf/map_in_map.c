/* Copyright (c) 2017 Facebook
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#include <linux/slab.h>
#include <linux/cpf.h>

#include "map_in_map.h"

struct cpf_map *cpf_map_meta_alloc(int inner_map_ufd)
{
	struct cpf_map *inner_map, *inner_map_meta;
	struct fd f;

	f = fdget(inner_map_ufd);
	inner_map = __cpf_map_get(f);
	if (IS_ERR(inner_map))
		return inner_map;

	/* prog_array->owner_prog_type and owner_jited
	 * is a runtime binding.  Doing static check alone
	 * in the verifier is not enough.
	 */
	if (inner_map->map_type == CPF_MAP_TYPE_PROG_ARRAY) {
		fdput(f);
		return ERR_PTR(-ENOTSUPP);
	}

	/* Does not support >1 level map-in-map */
	if (inner_map->inner_map_meta) {
		fdput(f);
		return ERR_PTR(-EINVAL);
	}

	inner_map_meta = kzalloc(sizeof(*inner_map_meta), GFP_USER);
	if (!inner_map_meta) {
		fdput(f);
		return ERR_PTR(-ENOMEM);
	}

	inner_map_meta->map_type = inner_map->map_type;
	inner_map_meta->key_size = inner_map->key_size;
	inner_map_meta->value_size = inner_map->value_size;
	inner_map_meta->map_flags = inner_map->map_flags;
	inner_map_meta->ops = inner_map->ops;
	inner_map_meta->max_entries = inner_map->max_entries;

	fdput(f);
	return inner_map_meta;
}

void cpf_map_meta_free(struct cpf_map *map_meta)
{
	kfree(map_meta);
}

bool cpf_map_meta_equal(const struct cpf_map *meta0,
			const struct cpf_map *meta1)
{
	/* No need to compare ops because it is covered by map_type */
	return meta0->map_type == meta1->map_type &&
		meta0->key_size == meta1->key_size &&
		meta0->value_size == meta1->value_size &&
		meta0->map_flags == meta1->map_flags &&
		meta0->max_entries == meta1->max_entries;
}

void *cpf_map_fd_get_ptr(struct cpf_map *map,
			 struct file *map_file /* not used */,
			 int ufd)
{
	struct cpf_map *inner_map;
	struct fd f;

	f = fdget(ufd);
	inner_map = __cpf_map_get(f);
	if (IS_ERR(inner_map))
		return inner_map;

	if (cpf_map_meta_equal(map->inner_map_meta, inner_map))
		inner_map = cpf_map_inc(inner_map, false);
	else
		inner_map = ERR_PTR(-EINVAL);

	fdput(f);
	return inner_map;
}

void cpf_map_fd_put_ptr(void *ptr)
{
	/* ptr->ops->map_free() has to go through one
	 * rcu grace period by itself.
	 */
	cpf_map_put(ptr);
}

u32 cpf_map_fd_sys_lookup_elem(void *ptr)
{
	return ((struct cpf_map *)ptr)->id;
}
