/*
 * ====================================================================
 * Copyright (c) 2002, 2003 The RapidSvn Group.  All rights reserved.
 *
 * This software is licensed as described in the file LICENSE.txt,
 * which you should have received as part of this distribution.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://rapidsvn.tigris.org/.
 * ====================================================================
 * @file entry.hpp
 */
#ifndef _SVNCPP_ENTRY_HPP_
#define _SVNCPP_ENTRY_HPP_

// subversion api
//#include "svn_types.h"
#include "svn_wc.h"

namespace svn
{
  /**
   * C++ API for Subversion. 
   * This class wraps around @a svn_wc_entry_t.
   */
  class Entry
  {
  public:
    /**
     * default constructor. if @a src is set,
     * copy its contents
     *
     * @param src another entry to copy from
     */
    Entry (const svn_wc_entry_t * src = 0);

    /**
     * destructor 
     */
    virtual ~Entry ();

    /**
     * @return entry's name
     */
    const char *
    name () const
    {
      return m_entry->name;
    }

    /**
     * @return base revision
     */
    const svn_revnum_t 
    revision () const
    {
      return m_entry->revision;
    }

    /**
     * @return url in repository
     */
    const char * 
    url () const
    {
      return m_entry->url;
    }

    /**
     * @return canonical repository url
     */
    const char *
    repos () const
    {
      return m_entry->repos;
    }

    /**
     * @return repository uuid
     */
    const char *
    uuid () const
    {
      return m_entry->uuid;
    }

    /**
     * @return node kind (file, dir, ...)
     */
    const svn_node_kind_t
    kind () const
    {
      return m_entry->kind;
    }

    /**
     * @return scheduling (add, delete, replace)
     */
    const svn_wc_schedule_t
    schedule () const
    {
      return m_entry->schedule;
    }

    /**
     * @return TRUE if copied
     */
    const bool 
    isCopied () const
    {
      return m_entry->copied;
    }
    
    /**
     * @return true if deleted
     */
    const bool
    isDeleted () const
    {
      return m_entry->deleted;
    }

    /**
     * @return copyfrom location
     */
    const char *
    copyfromUrl () const
    {
      return m_entry->copyfrom_url;
    }

    /**
     * @return copyfrom revision
     */
    const svn_revnum_t
    copyfromRev () const
    {
      return m_entry->copyfrom_rev;
    }

    /**
     * @return old version of conflicted file
     */
    const char *
    conflictOld () const
    {
      return m_entry->conflict_old;
    }

    /**
     * @return new version of conflicted file
     */
    const char *
    conflictNew () const
    {
      return m_entry->conflict_new;
    }
    
    /**
     * @return working version of conflicted file
     */
    const char *
    conflictWrk () const
    {
      return m_entry->conflict_wrk;
    }

    /**
     * @return property reject file
     */
    const char *
    prejfile () const
    {
      return m_entry->prejfile;
    }

    /**
     * @return last up-to-date time for text contents
     * @retval 0 no information available
     */
    const apr_time_t
    textTime () const
    {
      return m_entry->text_time;
    }
    
    /**
     * @return last up-to-date time for properties
     * @retval 0 no information available
     */
    const apr_time_t
    propTime () const
    {
      return m_entry->prop_time;
    }

    /**
     * @return base64 encoded checksum
     * @retval NULL for backwards compatibility
     */
    const char *
    checksum () const
    {
      return m_entry->checksum;
    }

    /**
     * @return last revision this was changed
     */
    const svn_revnum_t
    cmtRev () const
    {
      return m_entry->cmt_rev;
    }

    /**
     * @return last date this was changed
     */
    const apr_time_t
    cmtDate () const
    {
      return m_entry->cmt_date;
    }

    /**
     * @return last commit author of this file
     */
    const char *
    cmtAuthor () const
    {
      return m_entry->cmt_author;
    }

    /**
     * @return svn_wc_entry_t for this class
     */
    operator svn_wc_entry_t * () const
    {
      return m_entry;
    }

  private:
    svn_wc_entry_t * m_entry;
    Pool m_pool;




 };

}

#endif
/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../../rapidsvn-dev.el")
 * end:
 */
