FILE(REMOVE_RECURSE
  "CMakeFiles/test-common.dir/common.c.o"
  "libtest-common.pdb"
  "libtest-common.so"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang C)
  INCLUDE(CMakeFiles/test-common.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
