find_package(Qt6 REQUIRED COMPONENTS Test)
find_package(Python3 REQUIRED COMPONENTS Interpreter)

function(openload_add_test name)
    add_executable(${name} ${name}.cpp ${ARGN})
    target_link_libraries(${name} PRIVATE openload_engine Qt6::Test)
    target_include_directories(${name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_compile_definitions(${name} PRIVATE
        OPENLOAD_TEST_SERVER="${CMAKE_CURRENT_SOURCE_DIR}/server/test_server.py"
        OPENLOAD_PYTHON="${Python3_EXECUTABLE}")
    add_test(NAME ${name} COMMAND ${name})
    set_tests_properties(${name} PROPERTIES
        TIMEOUT 300
        ENVIRONMENT "QT_QPA_PLATFORM=offscreen")
endfunction()

openload_add_test(tst_core)
openload_add_test(tst_queue)
openload_add_test(tst_storage)
openload_add_test(tst_network)
openload_add_test(tst_manager)

if(TARGET openload_ui)
    openload_add_test(tst_ui)
    target_link_libraries(tst_ui PRIVATE openload_ui)
endif()
