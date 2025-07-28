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

noinst_PROGRAMS = check_gcal
TESTS = check_gcal
check_gcal_SOURCES = check_gcal.c \
                           check_file-io.c \
                           check_gcal2txt.c \
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
                           check_tcal.c \
                           check_tty.c \
                           check_txt2gcal.c \
                           check_utils.c 


check_gcal_CFLAGS = $(CFLAGS) $(CHECK_CFLAGS)
check_gcal_LDADD = $(LDFLAGS) $(CHECK_LIBS)
