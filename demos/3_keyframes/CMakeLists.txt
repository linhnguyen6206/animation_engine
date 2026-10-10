set(LIBS atkmath imgui ${LIBS})

file (GLOB_RECURSE EXAMPLES CONFIGURE_DEPENDS *.cpp)
foreach (example ${EXAMPLES})
  get_filename_component(example_name ${example} NAME_WLE)
  add_executable(3_${example_name} ${example})
  target_link_libraries(3_${example_name} ${LIBS})
endforeach()

