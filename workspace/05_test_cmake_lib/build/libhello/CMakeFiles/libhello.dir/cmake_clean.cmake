FILE(REMOVE_RECURSE
  "CMakeFiles/libhello.dir/hello.c.o"
  "../lib/libhello.pdb"
  "../lib/libhello.a"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang C)
  INCLUDE(CMakeFiles/libhello.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
