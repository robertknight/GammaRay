add_subdirectory(injector)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}

  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/3rdparty
  ${CMAKE_SOURCE_DIR}/common
)

set(gammaray_runner_srcs
  injector/abstractinjector.cpp
  injector/injectorfactory.cpp
  injector/preloadinjector.cpp
  injector/styleinjector.cpp
  injector/windllinjector.cpp
  injector/interactiveprocess.cpp
  injector/preloadcheck.cpp

  probefinder.cpp
  main.cpp
  promolabel.cpp
  launcherwindow.cpp
  launchpage.cpp
  selftestpage.cpp
  connectpage.cpp
  networkdiscoverymodel.cpp
  launchoptions.cpp
  clientlauncher.cpp

  attachdialog.cpp
  processmodel.cpp
  processfiltermodel.cpp
)
if(NOT WIN32)
  set(gammaray_runner_srcs
    ${gammaray_runner_srcs}
    injector/gdbinjector.cpp
    processlist_unix.cpp
  )
else()
  set(gammaray_runner_srcs
    ${gammaray_runner_srcs}
    processlist_win.cpp
  )
endif()

qt4_wrap_ui(gammaray_runner_srcs
  attachdialog.ui
  launcherwindow.ui
  launchpage.ui
  selftestpage.ui
  connectpage.ui
)
# TODO we don't need all the class icons here, so split the qrc file accordingly
qt4_add_resources(gammaray_runner_srcs ${CMAKE_SOURCE_DIR}/resources/gammaray.qrc)
qt4_automoc(${gammaray_runner_srcs})

add_executable(gammaray ${gammaray_runner_srcs})

target_link_libraries(gammaray ${QT_QTCORE_LIBRARIES} ${QT_QTGUI_LIBRARIES} gammaray_common_internal gammaray_ui)

if (QNXNTO)
  target_link_libraries(gammaray cpp)
endif()

if(UNIX AND NOT APPLE AND NOT QNXNTO)
  target_link_libraries(gammaray dl) # for preload check
endif()

install(TARGETS gammaray ${INSTALL_TARGETS_DEFAULT_ARGS})
