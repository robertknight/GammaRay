include_directories(${CMAKE_CURRENT_BINARY_DIR})

if (Qt5Widgets_FOUND OR QT_QTGUI_FOUND)
set(gammaray_injector_style_srcs injectorstyleplugin.cpp)
qt4_automoc(${gammaray_injector_style_srcs})

add_library(gammaray_injector_style MODULE ${gammaray_injector_style_srcs})

target_link_libraries(gammaray_injector_style
  ${QT_QTCORE_LIBRARIES}
  ${QT_QTGUI_LIBRARIES}
)

set_target_properties(gammaray_injector_style
  PROPERTIES PREFIX ""
  LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/plugins/styles
)

install(
  TARGETS gammaray_injector_style
  DESTINATION ${PLUGIN_INSTALL_DIR}/styles
)
endif()
