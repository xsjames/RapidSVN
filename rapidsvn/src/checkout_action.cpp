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

// svncpp
#include "svncpp/client.hpp"

// app
#include "checkout_action.hpp"
#include "checkout_dlg.hpp"
#include "ids.hpp"
#include "utils.hpp"

CheckoutAction::CheckoutAction (wxWindow * parent)
  : Action (parent, _("Checkout"), GetBaseFlags ())
{
}

bool
CheckoutAction::Prepare ()
{
  if (!Action::Prepare ())
  {
    return false;
  }

  CheckoutDlg dlg (GetParent ());
  if( dlg.ShowModal () != wxID_OK )
  {
    return false;
  }
  m_data = dlg.GetData ();
  return true;
}

bool
CheckoutAction::Perform ()
{
  svn::Client client (GetContext ());

  TrimString(m_data.DestFolder);
  UnixPath(m_data.DestFolder);
  TrimString(m_data.RepUrl);
  
  long revnum=-1;
  
  svn::Revision revision (svn::Revision::HEAD);

  // Did the user request a specific revision?:
  if (!m_data.UseLatest)
  {
    TrimString(m_data.Revision);
    if (!m_data.Revision.IsEmpty ())
    {
      m_data.Revision.ToLong(&revnum, 10);  // If this fails, revnum is unchanged.
    }
    revision = svn::Revision(revnum);
  }
  
  wxSetWorkingDirectory (m_data.DestFolder);
  client.checkout (m_data.RepUrl.c_str (), 
                   m_data.DestFolder.c_str (), 
                   revision, m_data.Recursive);

  // now post event to add bookmark to bookmarks
  if (m_data.Bookmarks)
  {
    wxCommandEvent event = CreateActionEvent (TOKEN_ADD_BOOKMARK);
    event.SetString (m_data.DestFolder);

    PostEvent (event);
  }
 
  return true;
}
/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../rapidsvn-dev.el")
 * end:
 */