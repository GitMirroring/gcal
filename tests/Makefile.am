# GNU gcal
#
# Copyright (C) 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002,
# 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2013 Free
# Software Foundation, Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# add this until tests are really working

#AM_CFLAGS = -I$(top_srcdir)/lib -I$(srcdir) -I.. $(CPPFLAGS)
AM_CPPFLAGS = -I$(top_srcdir)/lib -I$(srcdir) -I.. $(CPPFLAGS) -D_GNU_SOURCE

MOSTLYCLEANFILES = *.gcda *.gcno *.gcov

GCAL_OBJS= \
  ../src/file-io.o \
  ../src/hd-astro.o \
  ../src/hd-data.o \
  ../src/hd-data1.o \
  ../src/hd-data2.o \
  ../src/hd-data3.o \
  ../src/hd-data4.o \
  ../src/hd-data5.o \
  ../src/hd-use.o \
  ../src/help.o \
  ../src/print.o \
  ../src/rc-astro.o \
  ../src/rc-check.o \
  ../src/rc-insert.o \
  ../src/rc-use.o \
  ../src/rc-utils.o \
  ../src/tty.o \
  ../src/utils.o

GCAL_GNULIB_OBJS= \
  ../lib/fclose.o \
  ../lib/fflush.o \
  ../lib/fseeko.o \
  ../lib/ioctl.o \
  ../lib/tmpdir.o 

noinst_PROGRAMS = check_gcal check_gcal_file_io
TESTS = check_gcal check_gcal_file_io

check_gcal_SOURCES = check_gcal.c \
                           check_file-io.c \
                           check_hd-astro.c \
                           check_hd-data.c \
                           check_hd-use.c \
                           check_help.c \
                           check_print.c \
                           check_rc-astro.c \
                           check_rc-check.c \
                           check_rc-insert.c \
                           check_rc-use.c \
                           check_rc-utils.c \
                           check_tty.c \
                           check_utils.c 

check_gcal_CFLAGS = $(CFLAGS) $(CHECK_CFLAGS) $(DEFS)
check_gcal_LDFLAGS = -lgcov --coverage
check_gcal_LDADD = $(LDFLAGS) $(CHECK_LIBS) $(GCAL_OBJS) $(GCAL_GNULIB_OBJS)


# splitting tests might be needed later, so this is how it is done
check_gcal_file_io_SOURCES = check_gcal_file-io.c \
                           check_file-io.c

check_gcal_file_io_CFLAGS = $(CFLAGS) $(CHECK_CFLAGS) $(DEFS)
check_gcal_file_io_LDFLAGS = -lgcov --coverage
check_gcal_file_io_LDADD = $(LDFLAGS) $(CHECK_LIBS) $(GCAL_OBJS) $(GCAL_GNULIB_OBJS)
