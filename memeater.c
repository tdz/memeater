/*
 * Copyright 2012 Mozilla Foundation
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
  static const char optstr[] =
    "+"
    "m:"; /* memory */

  size_t siz = 0;
  long res;
  size_t pgsize;
  int opt;
  unsigned char *mem;
  size_t i;

  res = sysconf(_SC_PAGESIZE);

  if (!res) {
    fprintf(stderr, "failed to determine page size\n");
  } else if (res < 0) {
    fprintf(stderr, "failed to determine page size: %s\n", strerror(errno));
  }

  pgsize = res;

  while ((opt = getopt(argc, argv, optstr)) != -1)
  {
    switch (opt) {
      case '?':
        exit(EXIT_FAILURE);
      case 'm': {
        char *end = NULL;

        errno = 0;
        siz = strtoull(optarg, &end, 0);
        if (errno) {
          fprintf(stderr, "invalid memory size %s", optstr);
          exit(EXIT_FAILURE);
        }

        switch (*end) {
          case 'p':
          case 'P':
            siz *= pgsize;
          case 'g':
          case 'G':
            siz *= 1024;
            /* fall through */
          case 'm':
          case 'M':
            siz *= 1024;
            /* fall through */
          case 'k':
          case 'K':
            siz *= 1024;
            /* fall through */
          case 'b':
          case 'B':
          case 0:
            break;
          default:
            fprintf(stderr, "unknown size mulitplier %c\n", *end);
            exit(EXIT_FAILURE);
        }
        break;
      }
    }
  }

  if (!siz) {
    fprintf(stderr, "no memory size given\n");
    exit(EXIT_FAILURE);
  }

  mem = malloc(siz);

  if (!mem) {
    fprintf(stderr, "memory allocation failed: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  /* lock pages */

  res = mlock(mem, siz);

  if (res < 0) {
    fprintf(stderr,
            "failed to lock memory, pages might get evicted\n",
            strerror(errno));
  }

  /* touch pages to map them into address space */

  for (i = 0; i < siz; i += pgsize) {
    mem[i] = i/pgsize;
  }

  exit(EXIT_SUCCESS);
}
