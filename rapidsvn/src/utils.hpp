/*
 * ====================================================================
 * Copyright (c) 2002-2004 The RapidSvn Group.  All rights reserved.
 *
 * This software is licensed as described in the file LICENSE.txt,
 * which you should have received as part of this distribution.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://rapidsvn.tigris.org/.
 * ====================================================================
 */
#ifndef _RAPIDSVN_UTILS_H_INCLUDED_
#define _RAPIDSVN_UTILS_H_INCLUDED_


// wx
#include "wx/dynarray.h"

// svn
#include "svn_wc.h"

// forward declarations
class wxString;
class Tracer;
class wxMenu;
class wxCommandEvent;

namespace svn
{
  class Status;
}


/**
 * declaration of an array with @a svn_revnum_t elements
 */
#ifdef WX_DEFINE_ARRAY_LONG
WX_DEFINE_ARRAY_LONG (svn_revnum_t, RevnumArray);
#else
WX_DEFINE_ARRAY (svn_revnum_t, RevnumArray);
#endif


/**
 * Create pseudo-unix paths on windows for use with svn (reverse backslashes,
 * but leave the rest as it is)
 *
 * NOTE: Does nothing on non-windows platforms
 *
 * @param path Native path to convert
 * @return string with all backslashes converted to forward slashes
 */
wxString & 
UnixPath (wxString & path);

/**
 * Trim whitespace at start and end of string
 * (Convenience function for trimming first left, then right)
 */
void 
TrimString (wxString & str);

/**
 * Post a menu command event with the given ID. 
 *
 * Used for converting non-command events to command events so they'll move up
 * the GUI hierarchy.
 */
bool 
PostMenuEvent (wxEvtHandler *source, long id);

/**
 * Create a correctly sized button with an ellipsis (three dots)
 */
wxButton *
CreateEllipsisButton (wxWindow *parent, long id);

/**
 * Append entries for the "Modify" menu
 *
 * @param parentMenu menu that will receive the items
 */
void 
AppendModifyMenu (wxMenu * parentMenu);

/**
 * Append entries for the "Repository" menu
 *
 * @param parentMenu menu that will receive the items
 */
void
AppendBookmarksMenu (wxMenu * parentMenu);

/**
 * Append entries for the "Query" menu
 *
 * @param parentMenu menu that will receive the items
 */
void 
AppendQueryMenu (wxMenu * parentMenu);


/**
 * Append entries for "verbs" (Win32 only).
 * Since this feature is context specific (based on
 * the selected file), @a status has to be passed.
 * Works only with one selected file
 *
 * @param parentMenu menu that will receive the items
 * @param status status instance of the selected item
 */
void
AppendVerbMenu (wxMenu * parentMenu, svn::Status * status);


/**
 * Checks if the given string contains a valid
 * revision number
 *
 * @param revstring revision string
 * @return true if valid revision
 */
bool
CheckRevision (const char * revstring);

/**
 * Creates an action event with @a token.
 *
 * @param token 
 */
wxCommandEvent 
CreateActionEvent (int token);

/**
 * Creates a menu item for @a id (with whistles and bells, uh,
 * bitmaps)
 *
 * @param menu menu where the new item will be appended
 * @param id menu item to create
 */
wxMenuItem *
AppendMenuItem (wxMenu & menu, int id);


/**
 * Tries to interpret @a revstring a revision number
 *
 * @param revstring string with revision number
 * @param revnum revision number
 * @return success?
 * @retval true valid revision number
 */
bool
ParseRevision (const wxString & revstring, svn_revnum_t & revnum);


/**
 * Tries to interpret @a datestring as a date
 * (using to current locales) 
 *
 * @param datestring string with date (and time)
 * @param date apr date
 * @return success?
 * @retval true valid date
 */
bool 
ParseDateTime (const wxString & datestring, apr_time_t & time);


/**
 * Checks whether the given @a datestring is a valid date/time string
 * for the current locale
 *
 * @retval true valid
 */
bool
CheckDateTime (const wxString & datestring);


/**
 * Format a date/time value to standard format
 *
 * @param data 
 * @param fmt format string
 * @return formatted date/time string
 */
wxString
FormatDateTime (apr_time_t date, wxString fmt = "%x %X");


/**
 * beautify a path so drive letters (if existing) are uppercase
 *
 * Examples:
 * 1. Local Unix path (leave alone)
 *    Before:  /home/users/xela/work/rapidsvn/src/svncpp
 *    After:   /home/users/xela/work/rapidsvn/src/svncpp
 *
 * 2. Local Windows path (uppercase drive letter)
 *    Before:  d:\Documents and Settings\alex\Application Data
 *    After:   D:\Documents and Settings\alex\Application Data
 * 
 * 3. Repository URL (lowercase url schema)
 *    Before:  https://svn.collab.net/repos/rapidsvn/trunk/src/svncpp
 *    After:   https://svn.collab.net/repos/rapidsvn/trunk/src/svncpp
 *
 * Jobs to do:
 * - Uppercase Windows drive letters
 * - Lowecase url schemas
 *
 * @param path input path
 * @return beatified path
 */
wxString 
BeautifyPath (const wxString & path);


/**
 * creates a textual description for a status value 
 *
 * @param kind
 * @return brief textual description
 */
wxString
StatusDescription (const svn_wc_status_kind kind);


/**
 * converts a string from local encoding (like Ansi on 
 * Windows) to utf8
 *
 * @see Utf8ToLocal
 *
 * @param srcLocal string in local encoding
 * @return string in local encoding
 */
wxString
LocalToUtf8 (const wxString & srcLocal);


/**
 * converts a string from utf to the local encoding 
 * (like Ansi on Windows)
 *
 * @see LocalToUtf8
 *
 * @param srcUtf8 string in utf8 encoding
 * @return string in utf8 encoding
 */
wxString
Utf8ToLocal (const wxString & srcUtf8);


#endif
/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../rapidsvn-dev.el")
 * end:
 */