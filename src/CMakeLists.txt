# Everything except the widgets: core logic, networking, queue, storage, platform.
# Tests link against this library directly.
add_library(openload_engine STATIC
    core/TaskState.cpp
    core/DownloadTask.cpp
    core/Formatters.cpp
    core/UrlValidator.cpp
    core/FileNameUtils.cpp
    core/RetryPolicy.cpp
    core/SpeedMeter.cpp
    core/RateLimiter.cpp
    core/Checksum.cpp
    core/SegmentPlan.cpp
    network/CurlEasy.cpp
    network/HttpProbe.cpp
    network/HttpDownloader.cpp
    network/SegmentDownloader.cpp
    network/DownloadWorker.cpp
    scheduler/DownloadQueue.cpp
    scheduler/Schedule.cpp
    scheduler/Scheduler.cpp
    storage/Database.cpp
    storage/DownloadRepository.cpp
    storage/SettingsRepository.cpp
    platform/Platform.cpp
    app/DownloadManager.cpp
)
target_include_directories(openload_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(openload_engine PUBLIC Qt6::Core CURL::libcurl SQLite::SQLite3)
target_compile_definitions(openload_engine PUBLIC
    OPENLOAD_VERSION="${PROJECT_VERSION}")
