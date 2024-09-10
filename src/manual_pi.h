 /**************************************************************************
 *   Copyright (C) 2017 by Mike Rossiter                                   *
 *   Copyright (c) 2024 Alec Leamas                                        *
 *   $EMAIL$                                                               *
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
 ************************************************************************* */

#ifndef MANUAL_PI_H_
#define MANUAL_PI_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#include <wx/glcanvas.h>
#endif

#include <wx/fileconf.h>
#include <wx/datetime.h>
#include <wx/tokenzr.h>

#include "config.h"

#include "ocpn_plugin.h"  //Required for OCPN plugin functions

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------

static int kToolPosition = -1;  ///< Toolbar tool default position

class Manual : public opencpn_plugin_118 {
public:
  explicit Manual(void* ppimgr);
  ~Manual() override;

  wxBitmap m_panel_bitmap;

  //    The required PlugIn Methods
  int Init() override;
  bool DeInit() override;

  int GetAPIVersionMajor() override;
  int GetAPIVersionMinor() override;
  int GetPlugInVersionMajor() override;
  int GetPlugInVersionMinor() override;
  int GetPlugInVersionPatch() override;
  const char* GetPlugInVersionPre() override;
  int GetPlugInVersionPost() override;
  const char* GetPlugInVersionBuild() override;
  wxBitmap* GetPlugInBitmap() override;
  wxString GetCommonName() override;
  wxString GetShortDescription() override;
  wxString GetLongDescription() override;

  //    The required override PlugIn Methods
  int GetToolbarToolCount() override;
  void OnToolbarToolCallback(int id) override;

private:
  int m_position_menu_id;
  int m_leftclick_tool_id;
  wxFileConfig* m_config;
  wxWindow* m_parent_window;

  bool LoadConfig();
  bool SaveConfig();

};

#endif   // MANUAL_PI_H_