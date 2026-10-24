#include "Platform.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QStandardPaths>

namespace openload::platform {

QString databasePath()
{
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (dir.isEmpty())
        dir = QDir::homePath() + QStringLiteral("/.openload");
    return QDir(dir).filePath(QStringLiteral("openload.db"));
}

#if defined(Q_OS_WIN)

static const char *kRunKey = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";

bool autostartSupported()
{
    return true;
}

bool isAutostartEnabled()
{
    QSettings run(QString::fromLatin1(kRunKey), QSettings::NativeFormat);
    return run.contains(QStringLiteral("OpenLoad"));
}

bool setAutostartEnabled(bool enabled)
{
    QSettings run(QString::fromLatin1(kRunKey), QSettings::NativeFormat);
    if (enabled) {
        const QString exe = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
        run.setValue(QStringLiteral("OpenLoad"), QStringLiteral("\"%1\" --minimized").arg(exe));
    } else {
        run.remove(QStringLiteral("OpenLoad"));
    }
    run.sync();
    return run.status() == QSettings::NoError;
}

#elif defined(Q_OS_LINUX)

static QString autostartFile()
{
    QString config = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation);
    return QDir(config).filePath(QStringLiteral("autostart/openload.desktop"));
}

bool autostartSupported()
{
    return true;
}

bool isAutostartEnabled()
{
    return QFile::exists(autostartFile());
}

bool setAutostartEnabled(bool enabled)
{
    const QString path = autostartFile();
    if (!enabled)
        return !QFile::exists(path) || QFile::remove(path);

    QDir().mkpath(QFileInfo(path).absolutePath());
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        return false;
    QString exe = QCoreApplication::applicationFilePath();
    exe.replace(QLatin1Char(' '), QLatin1String("\\s"));
    const QString content = QStringLiteral(
        "[Desktop Entry]\nType=Application\nName=OpenLoad\nExec=%1 --minimized\nIcon=openload\n"
        "X-GNOME-Autostart-enabled=true\nNoDisplay=false\n").arg(exe);
    return file.write(content.toUtf8()) > 0;
}

#else

bool autostartSupported() { return false; }
bool isAutostartEnabled() { return false; }
bool setAutostartEnabled(bool) { return false; }

#endif

} // namespace openload::platform
