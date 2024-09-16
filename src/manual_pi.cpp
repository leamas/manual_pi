 /**************************************************************************
 *   Copyright (C) 2017 by Mike Rossiter                                   *
 *   Copyright (c) 2024 Alec Leamas                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 **************************************************************************/

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/fileconf.h>
#include <wx/log.h>
#include <wx/utils.h>

#include "config.h"
#include "manual_pi.h"
#include "ocpn_plugin.h"
#include "plug_utils.h"


using namespace std;

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void* ppimgr) {
  return new Manual(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p) { delete p; }


//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

Manual::Manual(void* ppimgr)
  : opencpn_plugin_118(ppimgr),
  m_position_menu_id(-1),
  m_leftclick_tool_id(-1),
  m_config(nullptr),
  m_parent_window(nullptr)
{
  // Create  plugin icons
  auto icon_path = GetPluginIcon("panel-icon", PKG_NAME);
  if (icon_path.type == IconPath::Type::Svg)
    m_panel_bitmap = LoadSvgIcon(icon_path.path.c_str());
  else if (icon_path.type == IconPath::Type::Png)
    m_panel_bitmap = LoadPngIcon(icon_path.path.c_str());
  else  // icon_path.type == notfound
    wxLogWarning("cannot find icon for basename: %s", "manual_panel_icon");
}

Manual::~Manual()  = default;


int Manual::Init() {
  AddLocaleCatalog("opencpn-manual_pi");
  auto icon = GetPluginIcon("toolbar-icon", PKG_NAME);
  auto toggled_icon = GetPluginIcon("toolbar-icon", PKG_NAME);
  if (icon.type == IconPath::Type::Svg)
    m_leftclick_tool_id = InsertPlugInToolSVG(
        "Manual", icon.path, icon.path, toggled_icon.path, wxITEM_CHECK,
        "Manual", "", nullptr, kToolPosition, 0, this);
  else if (icon.type == IconPath::Type::Png) {
    auto bitmap = LoadPngIcon(icon.path.c_str());
    m_leftclick_tool_id =
        InsertPlugInTool("", &bitmap, &bitmap, wxITEM_CHECK, "Manual", "",
                         nullptr, kToolPosition, 0, this);
  }
  return WANTS_TOOLBAR_CALLBACK | INSTALLS_TOOLBAR_TOOL;
}

bool Manual::DeInit() {
  return true;
}

int Manual::GetAPIVersionMajor() { return atoi(API_VERSION); }

int Manual::GetAPIVersionMinor() {
  std::string v(API_VERSION);
  size_t dotpos = v.find('.');
  return atoi(v.substr(dotpos + 1).c_str());
}

int Manual::GetPlugInVersionMajor() { return PLUGIN_VERSION_MAJOR; }

int Manual::GetPlugInVersionMinor() { return PLUGIN_VERSION_MINOR; }

int Manual::GetPlugInVersionPatch() { return PLUGIN_VERSION_PATCH; }

int Manual::GetPlugInVersionPost() { return PLUGIN_VERSION_TWEAK; };

const char* Manual::GetPlugInVersionPre() { return PKG_PRERELEASE; }

const char* Manual::GetPlugInVersionBuild() { return PKG_BUILD_INFO; }

wxBitmap* Manual::GetPlugInBitmap() { return &m_panel_bitmap; }

wxString Manual::GetCommonName() { return PLUGIN_API_NAME; }

wxString Manual::GetShortDescription() { return PKG_SUMMARY; }

wxString Manual::GetLongDescription() { return PKG_DESCRIPTION; }

int Manual::GetToolbarToolCount() { return 1; }

void Manual::OnToolbarToolCallback(int id) {
  std::string url("file://");
  url += GetPluginDataDir(PKG_NAME).ToStdString();
  url += "/doc/index.html";
  wxLaunchDefaultBrowser(url);
}

bool Manual::LoadConfig() {
  if (!m_config) return false;
  m_config->SetPath("/PlugIns/Manual");
  return true;
}

bool Manual::SaveConfig() {
  if (!m_config) return false;
  m_config->SetPath("/PlugIns/Manual");
  return true;
}
