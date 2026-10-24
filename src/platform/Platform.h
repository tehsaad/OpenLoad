#pragma once

#include <QString>

namespace openload::platform {

// Where OpenLoad keeps its database:
//   Linux:   ~/.local/share/OpenLoad/OpenLoad/openload.db  (XDG_DATA_HOME)
//   Windows: %APPDATA%\OpenLoad\OpenLoad\openload.db
QString databasePath();

// Whether "launch at login" can be offered on this platform.
bool autostartSupported();
bool isAutostartEnabled();
// Linux: writes/removes ~/.config/autostart/openload.desktop.
// Windows: writes/removes HKCU\Software\Microsoft\Windows\CurrentVersion\Run\OpenLoad.
bool setAutostartEnabled(bool enabled);

} // namespace openload::platform
