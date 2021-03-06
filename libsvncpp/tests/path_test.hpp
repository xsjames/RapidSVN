/*
 * ====================================================================
 * Copyright (c) 2002-2018 The RapidSVN Group.  All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program (in the file LGPL.txt).
 * If not, see <http://www.gnu.org/licenses/>.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://rapidsvn.tigris.org/.
 * ====================================================================
 */
#include "cppunit/TestCase.h"
#include "cppunit/extensions/HelperMacros.h"

/**
 * Tests the svn::Path class.
 */
class PathTestCase : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(PathTestCase);
  CPPUNIT_TEST(testInit);
  CPPUNIT_TEST(testSplit);
  CPPUNIT_TEST(testAddComponent);
  CPPUNIT_TEST(testCopy);
  CPPUNIT_TEST(testIsUrl);
  CPPUNIT_TEST(testSubstr);
  CPPUNIT_TEST(testUnescape);
  CPPUNIT_TEST(testLength);
  CPPUNIT_TEST(testGetTempDir);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();

protected:
  void testInit();
  void testSplit();
  void testAddComponent();
  void testCopy();
  void testIsUrl();
  void testSubstr();
  void testUnescape();
  void testLength();
  void testGetTempDir();
};

/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../../rapidsvn-dev.el")
 * end:
 */
