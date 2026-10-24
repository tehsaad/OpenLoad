# Windows resources and installer staging (feature/windows-desktop only).
#
# 1. The executable gets an icon and version information from openload.rc.
# 2. `cmake --install <build> --prefix <stage>` puts openload.exe in <stage>/bin;
#    packaging/windows/stage.ps1 then adds the Qt runtime (windeployqt) and the
#    vcpkg DLLs, and installer.nsi turns the staged folder into OpenLoad-<ver>-Setup.exe.

set(OPENLOAD_ICO ${PROJECT_SOURCE_DIR}/packaging/windows/openload.ico)
configure_file(${PROJECT_SOURCE_DIR}/packaging/windows/openload.rc.in
               ${PROJECT_BINARY_DIR}/openload.rc @ONLY)
target_sources(openload PRIVATE ${PROJECT_BINARY_DIR}/openload.rc)

install(FILES ${PROJECT_SOURCE_DIR}/LICENSE ${PROJECT_SOURCE_DIR}/README.md
        DESTINATION ${CMAKE_INSTALL_DOCDIR})
