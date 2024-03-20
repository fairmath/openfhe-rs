set(LIBRARY_SOURCES
    pke/cryptocontext_wrapper.cpp
    pke/serialization.cpp
    bindings.cpp
)

# Optionally, specify headers for IDEs
set(LIBRARY_HEADERS
    pke/cryptocontext_wrapper.hpp
    pke/serialization.hpp
    bindings.hpp
)

# Define the library
add_library(openfhesys ${LIBRARY_SOURCES})

# Specify include directories
target_include_directories(openfhesys PUBLIC ../include)
