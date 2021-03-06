include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

# probe part
set(gammaray_codecbrowser_plugin_srcs
  codecbrowser.cpp
  codecmodel.cpp
)

qt4_automoc(${gammaray_codecbrowser_plugin_srcs})

gammaray_add_plugin(gammaray_codecbrowser_plugin
  gammaray_codecbrowser.desktop
  ${gammaray_codecbrowser_plugin_srcs}
)

target_link_libraries(gammaray_codecbrowser_plugin
  ${QT_QTCORE_LIBRARIES}
  gammaray_core
)

# ui part
if (Qt5Widgets_FOUND OR QT_QTGUI_FOUND)

set(gammaray_codecbrowser_plugin_ui_srcs
  codecbrowserwidget.cpp
)

qt4_automoc(${gammaray_codecbrowser_plugin_ui_srcs})
qt4_wrap_ui(gammaray_codecbrowser_plugin_ui_srcs
  codecbrowserwidget.ui
)

gammaray_add_plugin(gammaray_codecbrowser_ui_plugin
  gammaray_codecbrowser_ui.desktop
  ${gammaray_codecbrowser_plugin_ui_srcs}
)

target_link_libraries(gammaray_codecbrowser_ui_plugin
  ${QT_QTCORE_LIBRARIES}
  ${QT_QTGUI_LIBRARIES}
  gammaray_common
  gammaray_ui
)

endif()
