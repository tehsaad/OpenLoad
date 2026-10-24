#include "DownloadTask.h"

#include "Formatters.h"

#include <QDir>

namespace openload {

QString priorityLabel(Priority priority)
{
    switch (priority) {
    case Priority::Low: return QStringLiteral("Low");
    case Priority::Normal: return QStringLiteral("Normal");
    case Priority::High: return QStringLiteral("High");
    }
    return QStringLiteral("Normal");
}

QString DownloadTask::finalPath() const
{
    return QDir(directory).filePath(fileName);
}

QString DownloadTask::partPath() const
{
    return finalPath() + QStringLiteral(".openload-part");
}

QString DownloadTask::segmentPath(int index) const
{
    return finalPath() + QStringLiteral(".openload-seg%1").arg(index);
}

int DownloadTask::progressPercent() const
{
    return openload::progressPercent(downloadedBytes, totalBytes);
}

} // namespace openload
