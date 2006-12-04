/* this file is part of libccc, criawips' cairo-based canvas
 *
 * AUTHORS
 *       Sven Herzberg        <herzi@gnome-de.org>
 *
 * Copyright (C) 2005,2006 Sven Herzberg
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

#include <gtk/gtkmain.h>

#include "crossing.h"
#include "demo-window.h"
#include "fifteen.h"
#include "line.h"
#include "main.h"
#include "planets.h"
#include "zoom-and-scroll.h"

int
main(int argc, char* argv[]) {
	GtkWidget* mainwin = NULL;

	gtk_init(&argc, &argv);
	mainwin = demo_window_new();
	g_signal_connect(mainwin, "delete-event",
			 G_CALLBACK(gtk_main_quit), NULL);

	demo_window_add(DEMO_WINDOW(mainwin), crossing());
	demo_window_add(DEMO_WINDOW(mainwin), fifteen());
	demo_window_add(DEMO_WINDOW(mainwin), line());
	demo_window_add(DEMO_WINDOW(mainwin), pixbuf_demo());
	demo_window_add(DEMO_WINDOW(mainwin), text_demo());
	demo_window_add(DEMO_WINDOW(mainwin), tree_integration());
	demo_window_add(DEMO_WINDOW(mainwin), zoom_and_scroll());
	demo_window_add(DEMO_WINDOW(mainwin), camera_demo());
#ifdef BUILD_UNFINISHED
	demo_window_add(DEMO_WINDOW(mainwin), credits());
	demo_window_add(DEMO_WINDOW(mainwin), planet_page());
	demo_window_add(DEMO_WINDOW(mainwin), printer_demo());
#endif
	gtk_widget_show_all(mainwin);
	gtk_main();

	return 0;
}

