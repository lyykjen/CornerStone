# CMake generated Testfile for 
# Source directory: /home/lyy/software/glog-0.5.0
# Build directory: /home/lyy/software/glog-0.5.0/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(demangle "/home/lyy/software/glog-0.5.0/build/demangle_unittest")
set_tests_properties(demangle PROPERTIES  _BACKTRACE_TRIPLES "/home/lyy/software/glog-0.5.0/CMakeLists.txt;733;add_test;/home/lyy/software/glog-0.5.0/CMakeLists.txt;0;")
add_test(logging "/home/lyy/software/glog-0.5.0/build/logging_unittest")
set_tests_properties(logging PROPERTIES  _BACKTRACE_TRIPLES "/home/lyy/software/glog-0.5.0/CMakeLists.txt;734;add_test;/home/lyy/software/glog-0.5.0/CMakeLists.txt;0;")
add_test(signalhandler "/home/lyy/software/glog-0.5.0/build/signalhandler_unittest")
set_tests_properties(signalhandler PROPERTIES  _BACKTRACE_TRIPLES "/home/lyy/software/glog-0.5.0/CMakeLists.txt;737;add_test;/home/lyy/software/glog-0.5.0/CMakeLists.txt;0;")
add_test(stacktrace "/home/lyy/software/glog-0.5.0/build/stacktrace_unittest")
set_tests_properties(stacktrace PROPERTIES  TIMEOUT "30" _BACKTRACE_TRIPLES "/home/lyy/software/glog-0.5.0/CMakeLists.txt;741;add_test;/home/lyy/software/glog-0.5.0/CMakeLists.txt;0;")
add_test(stl_logging "/home/lyy/software/glog-0.5.0/build/stl_logging_unittest")
set_tests_properties(stl_logging PROPERTIES  _BACKTRACE_TRIPLES "/home/lyy/software/glog-0.5.0/CMakeLists.txt;745;add_test;/home/lyy/software/glog-0.5.0/CMakeLists.txt;0;")
add_test(symbolize "/home/lyy/software/glog-0.5.0/build/symbolize_unittest")
set_tests_properties(symbolize PROPERTIES  _BACKTRACE_TRIPLES "/home/lyy/software/glog-0.5.0/CMakeLists.txt;748;add_test;/home/lyy/software/glog-0.5.0/CMakeLists.txt;0;")
add_test(cmake_package_config_init "/usr/local/bin/cmake" "-DTEST_BINARY_DIR=/home/lyy/software/glog-0.5.0/build/test_package_config" "-DINITIAL_CACHE=/home/lyy/software/glog-0.5.0/build/test_package_config/glog_package_config_initial_cache.cmake" "-DCACHEVARS=set (BUILD_SHARED_LIBS ON CACHE BOOL \"Build shared libraries\")
set (BUILD_TESTING ON CACHE BOOL \"Build the testing tree.\")
set (BZRCOMMAND \"BZRCOMMAND-NOTFOUND\" CACHE FILEPATH \"Path to a program.\")
set (CMAKE_ADDR2LINE \"/usr/bin/addr2line\" CACHE FILEPATH \"Path to a program.\")
set (CMAKE_AR \"/usr/bin/ar\" CACHE FILEPATH \"Path to a program.\")
set (CMAKE_AR \"/usr/bin/ar\" CACHE FILEPATH \"Path to a program.\")
set (CMAKE_COLOR_MAKEFILE ON CACHE BOOL \"Enable/Disable color output during build.\")
set (CMAKE_CXX_COMPILER \"/usr/local/bin/c++\" CACHE FILEPATH \"CXX compiler\")
set (CMAKE_CXX_COMPILER \"/usr/local/bin/c++\" CACHE FILEPATH \"CXX compiler\")
set (CMAKE_CXX_COMPILER_AR \"/usr/bin/gcc-ar-4.9\" CACHE FILEPATH \"A wrapper around 'ar' adding the appropriate '--plugin' option for the GCC compiler\")
set (CMAKE_CXX_COMPILER_AR \"/usr/bin/gcc-ar-4.9\" CACHE FILEPATH \"A wrapper around 'ar' adding the appropriate '--plugin' option for the GCC compiler\")
set (CMAKE_CXX_COMPILER_RANLIB \"/usr/bin/gcc-ranlib-4.9\" CACHE FILEPATH \"A wrapper around 'ranlib' adding the appropriate '--plugin' option for the GCC compiler\")
set (CMAKE_CXX_COMPILER_RANLIB \"/usr/bin/gcc-ranlib-4.9\" CACHE FILEPATH \"A wrapper around 'ranlib' adding the appropriate '--plugin' option for the GCC compiler\")
set (CMAKE_CXX_FLAGS \"-fPIC\" CACHE STRING \"Flags used by the CXX compiler during all build types.\")
set (CMAKE_CXX_FLAGS_DEBUG \"-g\" CACHE STRING \"Flags used by the CXX compiler during DEBUG builds.\")
set (CMAKE_CXX_FLAGS_MINSIZEREL \"-Os -DNDEBUG\" CACHE STRING \"Flags used by the CXX compiler during MINSIZEREL builds.\")
set (CMAKE_CXX_FLAGS_RELEASE \"-O3 -DNDEBUG\" CACHE STRING \"Flags used by the CXX compiler during RELEASE builds.\")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO \"-O2 -g -DNDEBUG\" CACHE STRING \"Flags used by the CXX compiler during RELWITHDEBINFO builds.\")
set (CMAKE_DLLTOOL \"CMAKE_DLLTOOL-NOTFOUND\" CACHE FILEPATH \"Path to a program.\")
set (CMAKE_EXPORT_COMPILE_COMMANDS OFF CACHE BOOL \"Enable/Disable output of compile commands during generation.\")
set (CMAKE_INSTALL_BINDIR \"bin\" CACHE PATH \"User executables (bin)\")
set (CMAKE_INSTALL_DATAROOTDIR \"share\" CACHE PATH \"Read-only architecture-independent data root (share)\")
set (CMAKE_INSTALL_INCLUDEDIR \"include\" CACHE PATH \"C header files (include)\")
set (CMAKE_INSTALL_LIBDIR \"lib\" CACHE PATH \"Object code libraries (lib)\")
set (CMAKE_INSTALL_LIBEXECDIR \"libexec\" CACHE PATH \"Program executables (libexec)\")
set (CMAKE_INSTALL_LOCALSTATEDIR \"var\" CACHE PATH \"Modifiable single-machine data (var)\")
set (CMAKE_INSTALL_OLDINCLUDEDIR \"/usr/include\" CACHE PATH \"C header files for non-gcc (/usr/include)\")
set (CMAKE_INSTALL_PREFIX \"/usr/local\" CACHE PATH \"Install path prefix, prepended onto install directories.\")
set (CMAKE_INSTALL_SBINDIR \"sbin\" CACHE PATH \"System admin executables (sbin)\")
set (CMAKE_INSTALL_SHAREDSTATEDIR \"com\" CACHE PATH \"Modifiable architecture-independent data (com)\")
set (CMAKE_INSTALL_SYSCONFDIR \"etc\" CACHE PATH \"Read-only single-machine data (etc)\")
set (CMAKE_LINKER \"/usr/bin/ld\" CACHE FILEPATH \"Path to a program.\")
set (CMAKE_LINKER \"/usr/bin/ld\" CACHE FILEPATH \"Path to a program.\")
set (CMAKE_NM \"/usr/bin/nm\" CACHE FILEPATH \"Path to a program.\")
set (CMAKE_OBJCOPY \"/usr/bin/objcopy\" CACHE FILEPATH \"Path to a program.\")
set (CMAKE_OBJDUMP \"/usr/bin/objdump\" CACHE FILEPATH \"Path to a program.\")
set (CMAKE_RANLIB \"/usr/bin/ranlib\" CACHE FILEPATH \"Path to a program.\")
set (CMAKE_RANLIB \"/usr/bin/ranlib\" CACHE FILEPATH \"Path to a program.\")
set (CMAKE_READELF \"/usr/bin/readelf\" CACHE FILEPATH \"Path to a program.\")
set (CMAKE_SKIP_INSTALL_RPATH NO CACHE BOOL \"If set, runtime paths are not added when installing shared libraries, but are added when building.\")
set (CMAKE_SKIP_RPATH NO CACHE BOOL \"If set, runtime paths are not added when using shared libraries.\")
set (CMAKE_STRIP \"/usr/bin/strip\" CACHE FILEPATH \"Path to a program.\")
set (CMAKE_VERBOSE_MAKEFILE FALSE CACHE BOOL \"If this value is on, makefiles will be generated without the .SILENT directive, and all commands will be echoed to the console during the make.  This is useful for debugging only. With Visual Studio IDE projects all commands are done without /nologo.\")
set (COVERAGE_COMMAND \"/usr/local/bin/gcov\" CACHE FILEPATH \"Path to the coverage program that CTest uses for performing coverage inspection\")
set (COVERAGE_EXTRA_FLAGS \"-l\" CACHE STRING \"Extra command line flags to pass to the coverage tool\")
set (CPACK_BINARY_DEB OFF CACHE BOOL \"Enable to build Debian packages\")
set (CPACK_BINARY_FREEBSD OFF CACHE BOOL \"Enable to build FreeBSD packages\")
set (CPACK_BINARY_IFW OFF CACHE BOOL \"Enable to build IFW packages\")
set (CPACK_BINARY_NSIS OFF CACHE BOOL \"Enable to build NSIS packages\")
set (CPACK_BINARY_RPM OFF CACHE BOOL \"Enable to build RPM packages\")
set (CPACK_BINARY_STGZ ON CACHE BOOL \"Enable to build STGZ packages\")
set (CPACK_BINARY_TBZ2 OFF CACHE BOOL \"Enable to build TBZ2 packages\")
set (CPACK_BINARY_TGZ ON CACHE BOOL \"Enable to build TGZ packages\")
set (CPACK_BINARY_TXZ OFF CACHE BOOL \"Enable to build TXZ packages\")
set (CPACK_BINARY_TZ ON CACHE BOOL \"Enable to build TZ packages\")
set (CPACK_SOURCE_RPM OFF CACHE BOOL \"Enable to build RPM source packages\")
set (CPACK_SOURCE_TBZ2 ON CACHE BOOL \"Enable to build TBZ2 source packages\")
set (CPACK_SOURCE_TGZ ON CACHE BOOL \"Enable to build TGZ source packages\")
set (CPACK_SOURCE_TXZ ON CACHE BOOL \"Enable to build TXZ source packages\")
set (CPACK_SOURCE_TZ ON CACHE BOOL \"Enable to build TZ source packages\")
set (CPACK_SOURCE_ZIP OFF CACHE BOOL \"Enable to build ZIP source packages\")
set (CTEST_SUBMIT_RETRY_COUNT \"3\" CACHE STRING \"How many times to retry timed-out CTest submissions.\")
set (CTEST_SUBMIT_RETRY_DELAY \"5\" CACHE STRING \"How long to wait between timed-out CTest submissions.\")
set (CVSCOMMAND \"CVSCOMMAND-NOTFOUND\" CACHE FILEPATH \"Path to a program.\")
set (CVS_UPDATE_OPTIONS \"-d -A -P\" CACHE STRING \"Options passed to the cvs update command.\")
set (DART_TESTING_TIMEOUT \"1500\" CACHE STRING \"Maximum time allowed before CTest will kill the test.\")
set (GITCOMMAND \"/usr/bin/git\" CACHE FILEPATH \"Path to a program.\")
set (GTEST_INCLUDE_DIR \"GTEST_INCLUDE_DIR-NOTFOUND\" CACHE PATH \"Path to a file.\")
set (GTEST_LIBRARY \"GTEST_LIBRARY-NOTFOUND\" CACHE FILEPATH \"Path to a library.\")
set (GTEST_LIBRARY_DEBUG \"GTEST_LIBRARY_DEBUG-NOTFOUND\" CACHE FILEPATH \"Path to a library.\")
set (GTEST_MAIN_LIBRARY \"GTEST_MAIN_LIBRARY-NOTFOUND\" CACHE FILEPATH \"Path to a library.\")
set (GTEST_MAIN_LIBRARY_DEBUG \"GTEST_MAIN_LIBRARY_DEBUG-NOTFOUND\" CACHE FILEPATH \"Path to a library.\")
set (HGCOMMAND \"/usr/bin/hg\" CACHE FILEPATH \"Path to a program.\")
set (MAKECOMMAND \"/usr/local/bin/cmake --build . --config \\\"\${CTEST_CONFIGURATION_TYPE}\\\" -- -i\" CACHE STRING \"Command to build the project\")
set (MEMORYCHECK_COMMAND \"MEMORYCHECK_COMMAND-NOTFOUND\" CACHE FILEPATH \"Path to the memory checking command, used for memory error detection.\")
set (P4COMMAND \"P4COMMAND-NOTFOUND\" CACHE FILEPATH \"Path to a program.\")
set (PRINT_UNSYMBOLIZED_STACK_TRACES OFF CACHE BOOL \"Print file offsets in traces instead of symbolizing\")
set (SITE \"ubuntu\" CACHE STRING \"Name of the computer/site where compile is being run\")
set (SLURM_SBATCH_COMMAND \"SLURM_SBATCH_COMMAND-NOTFOUND\" CACHE FILEPATH \"Path to the SLURM sbatch executable\")
set (SLURM_SRUN_COMMAND \"SLURM_SRUN_COMMAND-NOTFOUND\" CACHE FILEPATH \"Path to the SLURM srun executable\")
set (SVNCOMMAND \"/usr/bin/svn\" CACHE FILEPATH \"Path to a program.\")
set (Unwind_INCLUDE_DIR \"Unwind_INCLUDE_DIR-NOTFOUND\" CACHE PATH \"unwind include directory\")
set (Unwind_LIBRARY \"Unwind_LIBRARY-NOTFOUND\" CACHE FILEPATH \"unwind library\")
set (Unwind_PLATFORM_LIBRARY \"Unwind_PLATFORM_LIBRARY-NOTFOUND\" CACHE FILEPATH \"unwind library platform\")
set (WITH_CUSTOM_PREFIX OFF CACHE BOOL \"Enable support for user-generated message prefixes\")
set (WITH_GFLAGS ON CACHE BOOL \"Use gflags\")
set (WITH_GTEST ON CACHE BOOL \"Use googletest\")
set (WITH_PKGCONFIG ON CACHE BOOL \"Enable pkg-config support\")
set (WITH_SYMBOLIZE ON CACHE BOOL \"Enable symbolize module\")
set (WITH_THREADS ON CACHE BOOL \"Enable multithreading support\")
set (WITH_TLS ON CACHE BOOL \"Enable Thread Local Storage (TLS) support\")
set (WITH_UNWIND ON CACHE BOOL \"Enable libunwind support\")
set (gflags_DIR \"/home/lyy/software/gflags-2.2.0/build\" CACHE PATH \"The directory containing a CMake configuration file for gflags.\")
" "-P" "/home/lyy/software/glog-0.5.0/cmake/TestInitPackageConfig.cmake")
set_tests_properties(cmake_package_config_init PROPERTIES  FIXTURES_SETUP "cmake_package_config" _BACKTRACE_TRIPLES "/home/lyy/software/glog-0.5.0/CMakeLists.txt;760;add_test;/home/lyy/software/glog-0.5.0/CMakeLists.txt;0;")
add_test(cmake_package_config_generate "/usr/local/bin/cmake" "-DGENERATOR=Unix Makefiles" "-DGENERATOR_PLATFORM=" "-DGENERATOR_TOOLSET=" "-DINITIAL_CACHE=/home/lyy/software/glog-0.5.0/build/test_package_config/glog_package_config_initial_cache.cmake" "-DPACKAGE_DIR=/home/lyy/software/glog-0.5.0/build" "-DPATH=.:/home/lyy/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/lyy/project/sxcmdb/coa/bin" "-DSOURCE_DIR=/home/lyy/software/glog-0.5.0/src/package_config_unittest/working_config" "-DTEST_BINARY_DIR=/home/lyy/software/glog-0.5.0/build/test_package_config/working_config" "-P" "/home/lyy/software/glog-0.5.0/cmake/TestPackageConfig.cmake")
set_tests_properties(cmake_package_config_generate PROPERTIES  FIXTURES_REQUIRED "cmake_package_config" FIXTURES_SETUP "cmake_package_config_working" _BACKTRACE_TRIPLES "/home/lyy/software/glog-0.5.0/CMakeLists.txt;767;add_test;/home/lyy/software/glog-0.5.0/CMakeLists.txt;0;")
add_test(cmake_package_config_build "/usr/local/bin/cmake" "--build" "/home/lyy/software/glog-0.5.0/build/test_package_config/working_config")
set_tests_properties(cmake_package_config_build PROPERTIES  FIXTURES_REQUIRED "cmake_package_config;cmake_package_config_working" _BACKTRACE_TRIPLES "/home/lyy/software/glog-0.5.0/CMakeLists.txt;779;add_test;/home/lyy/software/glog-0.5.0/CMakeLists.txt;0;")
add_test(cmake_package_config_cleanup "/usr/local/bin/cmake" "-E" "remove_directory" "/home/lyy/software/glog-0.5.0/build/test_package_config")
set_tests_properties(cmake_package_config_cleanup PROPERTIES  FIXTURES_CLEANUP "cmake_package_config" _BACKTRACE_TRIPLES "/home/lyy/software/glog-0.5.0/CMakeLists.txt;783;add_test;/home/lyy/software/glog-0.5.0/CMakeLists.txt;0;")