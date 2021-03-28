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

#endif
