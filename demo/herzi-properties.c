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

#include "herzi-properties.h"

#include <gtk/gtkhbox.h>

struct _HerziProperties {
	GtkHBox  base_instance;

	GList  * groups;
};

struct _HerziPropertiesClass {
	GtkHBoxClass base_class;
};

GtkWidget*
herzi_properties_new(void) {
	return g_object_new(HERZI_TYPE_PROPERTIES, NULL);
}

GtkWidget*
herzi_properties_add(HerziProperties* self, gchar const* label) {
	HerziPropertiesGroup* retval = herzi_properties_group_new(label);
	self->groups = g_list_append(self->groups, retval);
	gtk_box_pack_start(GTK_BOX(self), GTK_WIDGET(retval), FALSE, FALSE, 0);
	return GTK_WIDGET(retval);
}

/* GType stuff */
G_DEFINE_TYPE(HerziProperties, herzi_properties, GTK_TYPE_HBOX);

static void
herzi_properties_init(HerziProperties* self) {
	gtk_box_set_spacing(GTK_BOX(self), 18);
}

static void
herzi_properties_class_init(HerziPropertiesClass* self_class) {}

