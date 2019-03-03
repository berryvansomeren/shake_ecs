#----------------------------------------------------------------
# Create the external targets that our project relies on

# global compile definitions for all external targets
add_compile_definitions( 
	NOMINMAX 
)

# pybind11
add_subdirectory( external/pybind11-2.2.3 )
# also needs an installed Python version (We use Python3)


# a list of all include directories
set( SHAKE_INCLUDE_DIRECTORIES 
	src/
    external/
	${PYBIND11_INCLUDE_DIR} # defined by pybind11
	${PYTHON_INCLUDE_DIRS}	# defined by pybind11
	external/glad/include/
	C:/Users/Berry/Documents/shake3/shake_core/src/
	C:/Users/Berry/Documents/shake3/shake_graphics/src/
	C:/Users/Berry/Documents/shake3/shake_hid/src/
)

# a list of all external libraries
set( SHAKE_EXTERNAL_LIBRARIES 
	${EXECUTABLE_NAME}
    pybind11
	${PYTHON_LIBRARIES}		# defined by pybind11
	${GLAD_LIBRARIES}
	shake_core
	shake_graphics
)