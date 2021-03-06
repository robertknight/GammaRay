include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

# probe part
set(gammaray_fontbrowser_plugin_srcs
  fontbrowserinterface.cpp
  fontbrowser.cpp
  fontmodel.cpp
  fontbrowserserver.cpp
)

qt4_automoc(${gammaray_fontbrowser_plugin_srcs})

gammaray_add_plugin(gammaray_fontbrowser_plugin
  gammaray_fontbrowser.desktop
  ${gammaray_fontbrowser_plugin_srcs}
)

target_link_libraries(gammaray_fontbrowser_plugin
  ${QT_QTCORE_LIBRARIES}
  gammaray_core
)

# ui part
if (Qt5Widgets_FOUND OR QT_QTGUI_FOUND)

set(gammaray_fontbrowser_plugin_ui_srcs
  fontbrowserinterface.cpp
  fontbrowserwidget.cpp
  fontbrowserclient.cpp
)

qt4_automoc(${gammaray_fontbrowser_plugin_ui_srcs})
qt4_wrap_ui(gammaray_fontbrowser_plugin_ui_srcs
  fontbrowserwidget.ui
)

gammaray_add_plugin(gammaray_fontbrowser_ui_plugin
  gammaray_fontbrowser_ui.desktop
  ${gammaray_fontbrowser_plugin_ui_srcs}
)

target_link_libraries(gammaray_fontbrowser_ui_plugin
  ${QT_QTCORE_LIBRARIES}
  ${QT_QTGUI_LIBRARIES}
  gammaray_common
  gammaray_ui
)

endif()
