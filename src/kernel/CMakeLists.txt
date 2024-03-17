set(ARCH_PATH "arch")

function(load_profile ISA PLATFORM)
  # Set ISA and platform paths
  set(ISA_PATH "${ARCH_PATH}/${ISA}")
  set(PLATFORM_PATH "${ISA_PATH}/${PLATFORM}")

  # Load flags associated with ISA and platform
  include("${ISA_PATH}/flags.cmake")
  include("${PLATFORM_PATH}/flags.cmake")

  # Obtain sources for the ISA and platform
  file(GLOB ISA_SRCS "${ISA_PATH}/*.c" "${ISA_PATH}/*.S")
  file(GLOB PLATFORM_SRCS "${PLATFORM_PATH}/*.c" "${PLATFORM_PATH}/*.S")

  # Control build order using FIRST_SRCS flag from platform flags
  foreach(I ${FIRST_SRCS})
    # Assume path is relative to src/kernel
    list(APPEND TMP_FIRST_SRCS "${CMAKE_CURRENT_LIST_DIR}/${I}")
  endforeach(I)

  # Remove files from the other lists
  list(REMOVE_ITEM ISA_SRCS ${TMP_FIRST_SRCS})
  list(REMOVE_ITEM PLATFORM_SRCS ${TMP_FIRST_SRCS})

  # Export output variables
  set(FIRST_SRCS ${TMP_FIRST_SRCS} PARENT_SCOPE)
  set(ISA_SRCS ${ISA_SRCS} PARENT_SCOPE)
  set(PLATFORM_SRCS ${PLATFORM_SRCS} PARENT_SCOPE)
  set(PLATFORM_LAYOUT "${PLATFORM_PATH}/layout.ld" PARENT_SCOPE)
 
  # Export specific flags
  set(ISA_C_FLAGS ${ISA_C_FLAGS} PARENT_SCOPE)
  set(PLATFORM_C_FLAGS ${PLATFORM_C_FLAGS} PARENT_SCOPE)
  set(ISA_ASM_FLAGS ${ISA_ASM_FLAGS} PARENT_SCOPE)
  set(PLATFORM_ASM_FLAGS ${PLATFORM_ASM_FLAGS} PARENT_SCOPE)
  set(ISA_LINKER_FLAGS ${ISA_LINKER_FLAGS} PARENT_SCOPE)
  set(PLATFORM_LINKER_FLAGS ${PLATFORM_LINKER_FLAGS} PARENT_SCOPE)
endfunction(load_profile)

load_profile("i386" "pc")

file(GLOB GENERIC_SRCS "kernel/*.c")
file(GLOB_RECURSE HEADERS "include/*.h")

# Set up environment
add_executable(kernel ${FIRST_SRCS} ${PLATFORM_SRCS} ${ISA_SRCS} ${GENERIC_SRCS})

# Get the crtbegin.o and crtend.o files from the compiler and link them to the kernel
execute_process(COMMAND ${CMAKE_C_COMPILER} -print-file-name=crtbegin.o
  OUTPUT_VARIABLE CC_CRTBEGIN OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${CMAKE_C_COMPILER} -print-file-name=crtend.o
  OUTPUT_VARIABLE CC_CRTEND OUTPUT_STRIP_TRAILING_WHITESPACE)
target_link_libraries(kernel ${CC_CRTBEGIN} ${CC_CRTEND} libc)

target_include_directories(kernel PRIVATE "include" "../libc/include")
set(CMAKE_C_FLAGS "${ISA_C_FLAGS} ${PLATFORM_C_FLAGS}")
set(CMAKE_ASM-ATT_COMPILE_OBJECT
  "<CMAKE_ASM-ATT_COMPILER> ${ISA_ASM_FLAGS} ${PLATFORM_ASM_FLAGS} -o <OBJECT> <SOURCE>")
add_link_options("-T ${PLATFORM_LAYOUT}")
add_link_options("-N ${ISA_LINKER_FLAGS} ${PLATFORM_LINKER_FLAGS}")
set_target_properties(kernel PROPERTIES LINK_FLAGS 
  "-T ${CMAKE_CURRENT_LIST_DIR}/${PLATFORM_LAYOUT} -N ${ISA_LINKER_FLAGS} ${PLATFORM_LINKER_FLAGS}")
set_target_properties(kernel PROPERTIES PUBLIC_HEADER "${HEADERS}")

# Remove the "lib" prefix and add ".kernel" suffix
set_target_properties(kernel PROPERTIES PREFIX "")
set_target_properties(kernel PROPERTIES SUFFIX ".kernel")

install(TARGETS kernel
  RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/boot"
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/include")