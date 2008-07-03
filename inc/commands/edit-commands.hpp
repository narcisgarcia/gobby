/* gobby - A GTKmm driven libobby client
 * Copyright (C) 2005 - 2008 0x539 dev group
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef _GOBBY_EDIT_COMMANDS_HPP_
#define _GOBBY_EDIT_COMMANDS_HPP_

#include "operations/operations.hpp"
#include "dialogs/documentlocationdialog.hpp"
#include "core/header.hpp"
#include "core/browser.hpp"

#include <gtkmm/window.h>
#include <gtkmm/filechooserdialog.h>
#include <sigc++/trackable.h>

namespace Gobby
{

class EditCommands: public sigc::trackable
{
public:
	EditCommands(Gtk::Window& parent, Header& header,
	             Folder& folder, Preferences& preferences);
	~EditCommands();

protected:
	void on_document_changed(DocWindow* document);

	static void on_can_undo_changed_static(InfAdoptedAlgorithm* algorithm,
	                                       InfAdoptedUser* user,
					       gboolean can_undo,
	                                       gpointer user_data)
	{
		static_cast<EditCommands*>(user_data)->on_can_undo_changed(
			user, can_undo);
	}

	static void on_can_redo_changed_static(InfAdoptedAlgorithm* algorithm,
	                                       InfAdoptedUser* user,
	                                       gboolean can_redo,
	                                       gpointer user_data)
	{
		static_cast<EditCommands*>(user_data)->on_can_redo_changed(
			user, can_redo);
	}

	static void on_sync_complete_static(InfSession* session,
	                                    InfXmlConnection* connection,
	                                    gpointer user_data)
	{
		static_cast<EditCommands*>(user_data)->on_sync_complete();
	}

	static void on_mark_set_static(GtkTextBuffer* buffer,
	                               GtkTextIter* iter,
	                               GtkTextMark* mark,
	                               gpointer user_data)
	{
		static_cast<EditCommands*>(user_data)->on_mark_set();
	}

	static void on_changed_static(GtkTextBuffer* buffer,
	                              gpointer user_data)
	{
		static_cast<EditCommands*>(user_data)->on_changed();
	}

	void on_sync_complete();
	void on_active_user_changed(InfTextUser* active_user);
	void on_mark_set();
	void on_changed();

	void on_can_undo_changed(InfAdoptedUser* user, bool can_undo);
	void on_can_redo_changed(InfAdoptedUser* user, bool can_redo);

	void on_undo();
	void on_redo();
	void on_cut();
	void on_copy();
	void on_paste();

	DocWindow* m_current_document;
	// Only valid when m_current_document is nonzero:
	sigc::connection m_active_user_changed_connection;
	gulong m_can_undo_changed_handler;
	gulong m_can_redo_changed_handler;
	gulong m_synchronization_complete_handler;
	gulong m_mark_set_handler;
	gulong m_changed_handler;

	Gtk::Window& m_parent;
	Header& m_header;
	Folder& m_folder;
	Preferences& m_preferences;
};

}
	
#endif // _GOBBY_EDIT_COMMANDS_HPP_
