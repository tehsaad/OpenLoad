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

# The Qt Widgets user interface.
add_library(openload_ui STATIC
    ui/Theme.cpp
    ui/Widgets.cpp
    ui/DownloadTableModel.cpp
    ui/TaskActions.cpp
    ui/AddDownloadDialog.cpp
    ui/DashboardPage.cpp
    ui/DownloadDetailsPage.cpp
    ui/QueuePage.cpp
    ui/SettingsPage.cpp
    ui/MainWindow.cpp
    ${PROJECT_SOURCE_DIR}/assets/openload.qrc
)
target_link_libraries(openload_ui PUBLIC openload_engine Qt6::Widgets Qt6::Svg Qt6::Concurrent)

add_executable(openload WIN32 app/main.cpp)
target_link_libraries(openload PRIVATE openload_ui)

# Developer benchmark (not installed).
add_executable(bench_segments EXCLUDE_FROM_ALL ${PROJECT_SOURCE_DIR}/tools/bench_segments.cpp)
target_link_libraries(bench_segments PRIVATE openload_engine)
