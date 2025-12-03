cmake_minimum_required(VERSION 3.10)
project(libnativehelper LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Define the source files that work on all JVM targets (not just Android)
# These are the files from the libnativehelper_any_vm target in Android.bp
set(SOURCES
    DlHelp.c
    ExpandableString.c
    JNIHelp.c
    JniInvocation.c
    android/log.c
)

# Define the header files to include
set(HEADERS
    DlHelp.h
    ExpandableString.h
    include/nativehelper/JNIHelp.h
    include_platform/nativehelper/JniInvocation.h
    include_jni/jni.h
    ALog-priv.h
    jvm_compat_log.h
    android/log.h
)

# Create the static library
add_library(nativehelper_static STATIC ${SOURCES})

# Create the shared library
add_library(nativehelper SHARED ${SOURCES})

# Set include directories for the libraries
target_include_directories(nativehelper_static
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include_jni
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/header_only_include
        ${CMAKE_CURRENT_SOURCE_DIR}/include_platform
        ${CMAKE_CURRENT_SOURCE_DIR}/include_platform_header_only
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(nativehelper
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include_jni
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/header_only_include
        ${CMAKE_CURRENT_SOURCE_DIR}/include_platform
        ${CMAKE_CURRENT_SOURCE_DIR}/include_platform_header_only
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Add preprocessor definitions to handle Android-specific code
target_compile_definitions(nativehelper PRIVATE
    # Define a non-Android build to handle Android-specific functions
    -DANDROID_JVM_BUILD=1
    # Suppress Android-specific logging that might not be available
    -D__ANDROID_API__=21
)

target_compile_definitions(nativehelper_static PRIVATE
    -DANDROID_JVM_BUILD=1
    -D__ANDROID_API__=21
)

# Link with dl library for dynamic loading functions on Unix systems
if(UNIX AND NOT APPLE)
    target_link_libraries(nativehelper PRIVATE dl)
    target_link_libraries(nativehelper_static PRIVATE dl)
endif()

# On macOS, link with appropriate libraries
if(APPLE)
    target_link_libraries(nativehelper PRIVATE "-framework CoreFoundation")
    target_link_libraries(nativehelper_static PRIVATE "-framework CoreFoundation")
endif()

# On Windows, link with appropriate libraries
if(WIN32)
    target_link_libraries(nativehelper PRIVATE ws2_32)
    target_link_libraries(nativehelper_static PRIVATE ws2_32)
endif()

# Additional compiler flags for error checking
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(nativehelper PRIVATE -Wall -Wextra -fvisibility=hidden)
    target_compile_options(nativehelper_static PRIVATE -Wall -Wextra -fvisibility=hidden)
endif()

# Export symbols for the shared library
set_target_properties(nativehelper PROPERTIES
    VERSION 1.0
    SOVERSION 1
)

# Install targets
install(TARGETS nativehelper nativehelper_static
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(FILES ${HEADERS}
    DESTINATION include/nativehelper
)
