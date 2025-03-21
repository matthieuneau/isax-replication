
cmake_minimum_required(VERSION 3.14)
project(MyProject C)

include(FetchContent)

# Declare the GSL dependency using FetchContent.
FetchContent_Declare(
  gsl
  GIT_REPOSITORY https://git.savannah.gnu.org/git/gsl.git
  # You can specify a tag or branch here; for example, to use the gsl-2-7 release:
  GIT_TAG gsl-2-7
)

# This will download and add the GSL source as a subdirectory.
FetchContent_MakeAvailable(gsl)

# Now add your executable (or library) and link it to GSL.
add_executable(my_app main.c)
target_link_libraries(my_app PRIVATE gsl gslcblas)
