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

#include "planets.h"

#include <gtk/gtklabel.h>

// The numbers are taken from the german wikipedia pages about these planets
Planet planets[] = {
	{"Merkur",  "☿",  0.3871},
	{"Venus",   "♀",  0.723},
	{"Erde",    "♁",  1.0  },
	{"Mars",    "♂",  1.524},
	{"Jupiter", "♃",  5.204},
	{"Saturn",  "♄",  9.582},
	{"Uranus",  "♅", 19.201},
	{"Neptun",  "♆", 30.047},
	{"Pluto",   "♇", 39.236}
};

guint n_planets = G_N_ELEMENTS(planets);

DemoPage*
planet_page(void) {
	DemoPage* retval = g_new(DemoPage, 1);
	retval->widget = gtk_label_new("Planet Demo");
	retval->title = "Planets";
	return retval;
}

