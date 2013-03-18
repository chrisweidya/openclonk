/*
 * mape - C4 Landscape.txt editor
 *
 * Copyright (c) 2005-2009 Armin Burgmeier
 *
 * Portions might be copyrighted by other authors who have contributed
 * to OpenClonk.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * See isc_license.txt for full license and disclaimer.
 *
 * "Clonk" is a registered trademark of Matthes Bender.
 * See clonk_trademark_license.txt for full license.
 */

#ifndef INC_MAPE_C4_GROUP_HANDLE_H
#define INC_MAPE_C4_GROUP_HANDLE_H

#include <glib.h>

G_BEGIN_DECLS

typedef struct _C4GroupHandle C4GroupHandle;

typedef enum _C4GroupHandleStatus {
  C4_GROUP_HANDLE_INACTIVE,
  C4_GROUP_HANDLE_FILE,
  C4_GROUP_HANDLE_FOLDER
} C4GroupHandleStatus;

C4GroupHandle* c4_group_handle_new(void);
void c4_group_handle_free(C4GroupHandle* handle);

const gchar* c4_group_handle_get_error(C4GroupHandle* handle);

gboolean c4_group_handle_open(C4GroupHandle* handle, const gchar* path, gboolean create);
gboolean c4_group_handle_open_as_child(C4GroupHandle* handle, C4GroupHandle* mother, const gchar* name, gboolean exclusive, gboolean create);

const gchar* c4_group_handle_get_name(C4GroupHandle* handle);
gchar* c4_group_handle_get_full_name(C4GroupHandle* handle);

void c4_group_handle_reset_search(C4GroupHandle* handle);

gboolean c4_group_handle_find_next_entry(C4GroupHandle* handle, const gchar* wildcard, gsize* size, gchar* filename, gboolean start_at_filename);
gboolean c4_group_handle_access_next_entry(C4GroupHandle* handle, const gchar* wildcard, gsize* size, gchar* filename, gboolean start_at_filename);
gboolean c4_group_handle_access_entry(C4GroupHandle* handle, const gchar* wildcard, gsize* size, gchar* filename, gboolean needs_to_be_a_group);
gsize c4_group_handle_accessed_entry_size(C4GroupHandle* handle);
gboolean c4_group_handle_read(C4GroupHandle* handle, gpointer buffer, gsize size);

C4GroupHandleStatus c4_group_handle_get_status(C4GroupHandle* handle);

G_END_DECLS

#endif /* INC_MAPE_C4_GROUP_HANDLE_H */