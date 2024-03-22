project(libc LANGUAGES C)

set(ARCH_PATH "arch")

function(load_profile ISA PLATFORM)
  # Set ISA and platform paths
  set(ISA_PATH "${ARCH_PATH}/${ISA}")
  set(PLATFORM_PATH "${ISA_PATH}/${PLATFORM}")

  # Load flags associated with ISA and platform
  include("${ISA_PATH}/flags.cmake")
  include("${PLATFORM_PATH}/flags.cmake")
 
  # Export specific flags
  set(ISA_C_FLAGS ${ISA_C_FLAGS} PARENT_SCOPE)
  set(PLATFORM_C_FLAGS ${PLATFORM_C_FLAGS} PARENT_SCOPE)
  set(ISA_ASM_FLAGS ${ISA_ASM_FLAGS} PARENT_SCOPE)
  set(PLATFORM_ASM_FLAGS ${PLATFORM_ASM_FLAGS} PARENT_SCOPE)
  set(ISA_LINKER_FLAGS ${ISA_LINKER_FLAGS} PARENT_SCOPE)
  set(PLATFORM_LINKER_FLAGS ${PLATFORM_LINKER_FLAGS} PARENT_SCOPE)
endfunction(load_profile)

load_profile("i386" "pc")

file(GLOB_RECURSE SRCS "*.c" "*.S")
file(GLOB HEADERS "include/*.h")

# Set up environment
add_library(libc STATIC ${SRCS})
add_library(libk STATIC ${SRCS})
  
target_include_directories(libc PRIVATE "include")
target_include_directories(libk PRIVATE "include" "../kernel/include")

target_link_libraries(libk PRIVATE kernel)

target_compile_options(libc PRIVATE $<$<COMPILE_LANGUAGE:C>:${ISA_C_FLAGS} ${PLATFORM_C_FLAGS}>)
target_compile_options(libk PRIVATE $<$<COMPILE_LANGUAGE:C>:${ISA_C_FLAGS} ${PLATFORM_C_FLAGS} "-D__is_libk">)
target_compile_options(libc PRIVATE $<$<COMPILE_LANGUAGE:ASM>:${ISA_ASM_FLAGS} ${PLATFORM_ASM_FLAGS}>)
target_compile_options(libk PRIVATE $<$<COMPILE_LANGUAGE:ASM>:${ISA_ASM_FLAGS} ${PLATFORM_ASM_FLAGS}>)

target_link_options(libc PRIVATE ${ISA_LINKER_FLAGS} ${PLATFORM_LINKER_FLAGS})
target_link_options(libk PRIVATE ${ISA_LINKER_FLAGS} ${PLATFORM_LINKER_FLAGS})

set_target_properties(libc PROPERTIES PUBLIC_HEADER ${HEADERS})
# Remove the "lib" prefix
set_target_properties(libc PROPERTIES PREFIX "")
set_target_properties(libk PROPERTIES PREFIX "")
install(TARGETS libc
  ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/lib"
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/include")
