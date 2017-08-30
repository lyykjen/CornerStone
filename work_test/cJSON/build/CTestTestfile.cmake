# CMake generated Testfile for 
# Source directory: /home/lvyayun/test/work_test/cJSON
# Build directory: /home/lvyayun/test/work_test/cJSON/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(cJSON_test "/home/lvyayun/test/work_test/cJSON/build/cJSON_test")
SUBDIRS(tests)
SUBDIRS(fuzzing)
