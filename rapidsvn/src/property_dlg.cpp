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

// wxwindows
#include "wx/wx.h"
#include "wx/grid.h"
#include "wx/listctrl.h"
#include "wx/valgen.h"

// svncpp
#include "svncpp/exception.hpp"
#include "svncpp/url.hpp"

// app
#include "property_dlg.hpp"
#include "utils.hpp"


struct PropertyDlg::Data
{
  wxWindow * window;
  svn::Property property;
  
public:
  Data (wxWindow * wnd, svn::Context * context, const char * target)
    : window (wnd), property (context, target)
  {
  }

};

PropertyDlg::PropertyDlg (wxWindow * parent, 
                          svn::Context * context,
                          const svn::Path & target)
  : ListEditorDlg (parent, _("Property Editor"))
{
  const char * target_ = target.c_str ();
  // the property list is read-only when working 
  // on a repository 
  const bool readOnly = svn::Url::isValid(target_);
  m = new Data (this, context, target_);

  SetCaption (_("Properties:"));
  SetAddTitle (_("New Property"));
  SetEditTitle (_("Edit Property"));
  SetReadOnly (readOnly);
}

PropertyDlg::~PropertyDlg ()
{
  delete m;
}

/**
 * transfer the contents of the grid to @a property.
 * Properties, that are set only in @a property will be
 * set to NULL
 * 
 * @see WriteToGrid
 */
void
PropertyDlg::ReadFromGrid ()
{
  try
  {
    const std::vector<svn::PropertyEntry> & entries
      = m->property.entries ();
    std::vector<svn::PropertyEntry>::const_iterator it = entries.begin ();

    // first check for deleted properties
    while (it != entries.end ())
    {
      const svn::PropertyEntry & entry = *it;
      const char * name = entry.name.c_str ();
      bool found = FindEntry (name) != -1;

      if (!found)
      {
        m->property.remove (name);
      }

      it++;
    }

    // now set the rest. this will add missing properties as well
    int index;
    const int count = GetEntryCount ();

    for (index = 0; index < count; index++ )
    {
      wxString name, value;

      GetEntryAtIndex (index, name, value);

      m->property.set (name.c_str (), value.c_str ());
    }    
  }
  catch (...)
  {
    wxMessageBox (_("Error setting the property values"), _("Error"));
  }

}

/**
 * this method takes the contents of @a property and write it contents
 * to the grid. all user manipulations will be performed only in the
 * grid.
 *
 * @see ReadFromGrid
 */
void 
PropertyDlg::WriteToGrid ()
{
  const std::vector<svn::PropertyEntry> & 
    entries = m->property.entries ();
  std::vector<svn::PropertyEntry>::const_iterator 
    it = entries.begin ();

  DeleteAllEntries ();
  while (it != entries.end ())
  {
    const svn::PropertyEntry & entry = *it;

    SetEntry (entry.name.c_str (), entry.value.c_str ());
  
    it++;
  }
}


/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../rapidsvn-dev.el")
 * end:
 */