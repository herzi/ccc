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

#ifndef HERZI_PROPERTIES_GROUP_H
#define HERZI_PROPERTIES_GROUP_H

#include <gtk/gtkwidget.h>

G_BEGIN_DECLS

typedef struct _HerziPropertiesGroup      HerziPropertiesGroup;
typedef struct _HerziPropertiesGroupClass HerziPropertiesGroupClass;

#define HERZI_TYPE_PROPERTIES_GROUP         (herzi_properties_group_get_type())
#define HERZI_PROPERTIES_GROUP(i)           (G_TYPE_CHECK_INSTANCE_CAST((i), HERZI_TYPE_PROPERTIES_GROUP, HerziPropertiesGroup))
#define HERZI_PROPERTIES_GROUP_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST((c), HERZI_TYPE_PROPERTIES_GROUP, HerziPropertiesGroupClass))
#define HERZI_IS_PROPERTIES_GROUP(i)        (G_TYPE_CHECK_INSTANCE_TYPE((i), HERZI_TYPE_PROPERTIES_GROUP))
#define HERZI_IS_PROEPRTIES_GROUP_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE((c), HERZI_TYPE_PROPERTIES_GROUP))
#define HERZI_PROPERTIES_GROUP_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS((i), HERZI_TYPE_PROPERTIES_GROUP, HerziPropertiesGroupClass))

GType herzi_properties_group_get_type(void);

HerziPropertiesGroup* herzi_properties_group_new(gchar const         * label);
void                  herzi_properties_group_add(HerziPropertiesGroup* self,
						 gchar const         * label,
						 GtkWidget           * widget);

G_END_DECLS

#endif /* !HERZI_PROPERTIES_GROUP_H */
