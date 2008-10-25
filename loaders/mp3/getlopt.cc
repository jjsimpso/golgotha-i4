/********************************************************************** 

    Golgotha Forever - A portable, free 3D strategy and FPS game.
    Copyright (C) 1999 Golgotha Forever Developers

    Sources contained in this distribution were derived from
    Crack Dot Com's public release of Golgotha which can be
    found here:  http://www.crack.com

    All changes and new works are licensed under the GPL:

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    For the full license, see COPYING.

***********************************************************************/
 

/*
 *   getlopt.c
 *
 *   Oliver Fromme  <oliver.fromme@heim3.tu-clausthal.de>
 *   Tue Apr  8 07:15:13 MET DST 1997
 */

#include "loaders/mp3/getlopt.hh"

int loptind = 1;	/* index in argv[] */
int loptchr = 0;	/* index in argv[loptind] */
char *loptarg;		/* points to argument if present, else to option */
static char shortopt[2] = {0, 0};

void init_getlopt(void)
{
	loptind = 1;	/* index in argv[] */
	loptchr = 0;	/* index in argv[loptind] */
	shortopt[0] = 0;
	shortopt[1] = 0;
}

#if defined(ultrix) || defined(ULTRIX)
char *strdup (char *src)
{
	char *dest;

	if (!(dest = (char *) malloc(strlen(src)+1)))
		return (NULL);
	return (strcpy(dest, src));
}
#endif

topt *findopt (int islong, char *opt, topt *opts)
{
	if (!opts)
		return (0);
	while (opts->lname) {
		if (islong) {
			if (!strcmp(opts->lname, opt))
				return (opts);
		}
		else
			if (opts->sname == *opt)
				return (opts);
		opts++;
	}
	return (0);
}

int performoption (int argc, char *argv[], topt *opt)
{
	int result = GLO_CONTINUE;

	if (!(opt->flags & 1)) /* doesn't take argument */
		if (opt->var)
			if (opt->flags & 2) /* var is *char */
				*((char *) opt->var) = (char) opt->value;
			else
				*((int *) opt->var) = opt->value;
		else
			result = opt->value ? opt->value : opt->sname;
	else { /* requires argument */
		if (loptind >= argc)
			return (GLO_NOARG);
		loptarg = argv[loptind++]+loptchr;
		loptchr = 0;
		if (opt->var)
			if (opt->flags & 2) /* var is *char */
				*((char **) opt->var) = strdup(loptarg);
			else
				*((int *) opt->var) = atoi(loptarg);
		else
			result = opt->value ? opt->value : opt->sname;
	}
	if (opt->func)
		opt->func(loptarg);
	return (result);
}

int getsingleopt (int argc, char *argv[], topt *opts)
{
	char *thisopt;
	topt *opt;

	if (loptind >= argc)
		return (GLO_END);
	thisopt = argv[loptind];
	if (!loptchr) { /* start new option string */
		if (thisopt[0] != '-' || !thisopt[1]) /* no more options */
			return (GLO_END);
		if (thisopt[1] == '-') /* "--" */
			if (thisopt[2]) { /* long option */
				loptarg = thisopt+2;
				loptind++;
				if (!(opt = findopt(1, thisopt+2, opts)))
					return (GLO_UNKNOWN);
				else
					return (performoption(argc, argv, opt));
			}
			else { /* "--" == end of options */
				loptind++;
				return (GLO_END);
			}
		else /* start short option(s) */
			loptchr = 1;
	}
	shortopt[0] = thisopt[loptchr];
	loptarg = shortopt;
	opt = findopt(0, thisopt+(loptchr++), opts);
	if (!thisopt[loptchr]) {
		loptind++;
		loptchr = 0;
	}
	if (!opt)
		return (GLO_UNKNOWN);
	else
		return (performoption(argc, argv, opt));
}

int getlopt (int argc, char *argv[], topt *opts)
{
	int result;
	
	while ((result = getsingleopt(argc, argv, opts)) == GLO_CONTINUE);
	return (result);
}

/* EOF */
