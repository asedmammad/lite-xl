#include <stdlib.h>
#include "cp_replace.h"

#define REPLACEMENT_CHUNK_SIZE 8

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// FIXME: duplicate function with renderer.c!!!!!!!!!!!!!!!!!!!!!!!!!!
static const char* utf8_to_codepoint(const char *p, unsigned *dst) {
  unsigned res, n;
  switch (*p & 0xf0) {
    case 0xf0 :  res = *p & 0x07;  n = 3;  break;
    case 0xe0 :  res = *p & 0x0f;  n = 2;  break;
    case 0xd0 :
    case 0xc0 :  res = *p & 0x1f;  n = 1;  break;
    default   :  res = *p;         n = 0;  break;
  }
  while (n--) {
    res = (res << 6) | (*(++p) & 0x3f);
  }
  *dst = res;
  return p + 1;
}


void ren_cp_replace_init(CPReplaceTable *rep_table) {
  rep_table->size = 0;
  rep_table->replacements = NULL;
}


void ren_cp_replace_free(CPReplaceTable *rep_table) {
  free(rep_table->replacements);
}


void ren_cp_replace_add(CPReplaceTable *rep_table, const char *src, const char *dst) {
  int table_size = rep_table->size;
  if (table_size % REPLACEMENT_CHUNK_SIZE == 0) {
    CPReplace *old_replacements = rep_table->replacements;
    const int new_size = (table_size / REPLACEMENT_CHUNK_SIZE + 1) * REPLACEMENT_CHUNK_SIZE;
    rep_table->replacements = malloc(new_size * sizeof(CPReplace));
    if (!rep_table->replacements) {
      rep_table->replacements = old_replacements;
      return;
    }
    memcpy(rep_table->replacements, old_replacements, table_size * sizeof(CPReplace));
    free(old_replacements);
  }
  CPReplace *rep = &rep_table->replacements[table_size];
  utf8_to_codepoint(src, &rep->codepoint_src);
  utf8_to_codepoint(dst, &rep->codepoint_dst);
  rep_table->size = table_size + 1;
}


void ren_cp_replace_clear(CPReplaceTable *rep_table) {
  // TODO: we may keep the memory if the chunk is small.
  free(rep_table->replacements);
  rep_table->replacements = NULL;
  rep_table->size = 0;
}

