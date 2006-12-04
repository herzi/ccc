/* This file is part of libccc
 *
 * AUTHORS
 *     Sven Herzberg  <herzi@gnome-de.org>
 *
 * Copyright (C) 2006  Sven Herzberg <herzi@gnome-de.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

#ifndef HERZI_ENUM_MODEL_H
#define HERZI_ENUM_MODEL_H

#include <gtk/gtkliststore.h>

G_BEGIN_DECLS

typedef struct _HerziEnumModel    HerziEnumModel;
typedef struct _GtkListStoreClass HerziEnumModelClass;

enum {
	HERZI_ENUM_MODEL_COL_NAME,
	HERZI_ENUM_MODEL_COL_NICK,
	HERZI_ENUM_MODEL_COL_VALUE,
	HERZI_ENUM_MODEL_N_COLUMNS
};

#define HERZI_TYPE_ENUM_MODEL         (herzi_enum_model_get_type())
#define HERZI_ENUM_MODEL(i)           (G_TYPE_CHECK_INSTANCE_CAST((i), HERZI_TYPE_ENUM_MODEL, HerziEnumModel))
#define HERZI_ENUM_MODEL_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST((c), HERZI_TYPE_ENUM_MODEL, HerziEnumModel))
#define HERZI_IS_ENUM_MODEL(i)        (G_TYPE_CHECK_INSTANCE_TYPE((i), HERZI_TYPE_ENUM_MODEL))
#define HERZI_IS_ENUM_MODEL_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE((c), HERZI_TYPE_ENUM_MODEL))
#define HERZI_ENUM_MODEL_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS((i), HERZI_TYPE_ENUM_MODEL, HerziEnumModel))

GType herzi_enum_model_get_type(void);

GtkTreeModel* herzi_enum_model_new      (GType enum_type);
GType         herzi_enum_model_get_gtype(HerziEnumModel const* self);

G_END_DECLS

#endif /* !HERZI_ENUM_MODEL_H */
