#ifndef CP_REPLACE_H
#define CP_REPLACE_H

struct CPReplace {
  unsigned codepoint_src;
  unsigned codepoint_dst;
};
typedef struct CPReplace CPReplace;


struct CPReplaceTable {
  int size;
  CPReplace *replacements;
};
typedef struct CPReplaceTable CPReplaceTable;


void ren_cp_replace_init(CPReplaceTable *rep_table);
void ren_cp_replace_free(CPReplaceTable *rep_table);
void ren_cp_replace_add(CPReplaceTable *rep_table, const char *src, const char *dst);
void ren_cp_replace_clear(CPReplaceTable *rep_table);

#endif
