# ~~~
# Summary:      Local, non-generic plugin setup
# Copyright (c) 2024 ALec Leamas
# License:      GPLv3+
# ~~~

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.


# -------- Options ----------

set(OCPN_TEST_REPO
    "alec-leamas/opencpn-plugins-unstable"
    CACHE STRING "Default repository for untagged builds"
)
set(OCPN_BETA_REPO
    "alec-leamas/opencpn-plugins-unstable"
    CACHE STRING
    "Default repository for tagged builds matching 'beta'"
)
set(OCPN_RELEASE_REPO
    "alec-leamas/opencpn-plugins-stable"
    CACHE STRING
    "Default repository for tagged builds not matching 'beta'"
)

#
#
# -------  Plugin setup --------
#
set(PKG_NAME manual_pi)
set(PKG_VERSION 0.0.1)
set(PKG_PRERELEASE "")  # Empty, or a tag like 'beta'

set(DISPLAY_NAME Manual)    # Dialogs, installer artifacts, ...
set(PLUGIN_API_NAME manual) # As of GetCommonName() in plugin API
set(PKG_SUMMARY "Plugin and developer manual")
set(PKG_DESCRIPTION [=[
Off-line copy of the plugin and developer manual available at
https://opencpn-manuals.github.io/main
]=])

set(PKG_AUTHOR "Alec Leamas")
set(PKG_IS_OPEN_SOURCE "yes")
set(PKG_HOMEPAGE https://opencpn-manuals.github.io/main)
set(PKG_INFO_URL https://opencpn-manuals.github.io/main)

set(SRC
    src/manual_pi.h
    src/manual_pi.cpp
    src/plug_utils.cpp
    src/plug_utils.h
)

set(PKG_API_LIB api-18)  #  A dir in opencpn-libs/ e. g., api-17 or api-16

macro(late_init)
  # Perform initialization after the PACKAGE_NAME library, compilers
  # and ocpn::api is available.
  add_subdirectory("${CMAKE_SOURCE_DIR}/libs/std_filesystem")
  target_link_libraries(${PACKAGE_NAME} ocpn::filesystem)
  if (UNIX AND NOT APPLE AND NOT QT_ANDROID)
    # Linux. including Flatpak
    install(DIRECTORY doc DESTINATION "share/opencpn/plugins/${PACKAGE_NAME}")
  elseif (APPLE)
    install(
      DIRECTORY doc
      DESTINATION "OpenCPN.app/Contents/SharedSupport/plugins/${PACKAGE_NAME}"
    )
  elseif (WIN32)
    install(DIRECTORY doc DESTINATION "plugins/${PACKAGE_NAME}")
  endif ()
endif ()

endmacro ()

macro(add_plugin_libraries)
  # Add libraries required by this plugin
endmacro ()
