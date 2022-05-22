cmake_minimum_required(VERSION 3.5)

project(3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
find_package(glm REQUIRED)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        qt_ui/mainwindow.cpp
        qt_ui/mainwindow.h
        qt_ui/mainwindow.ui
        object/inc/scene_object.h object/inc/drawable_model.h math/inc/transformation.h math/inc/linalg.h tests/main_test.h tests/test_math.h math/src/transformation.cpp object/inc/mesh_model.h object/src/mesh_model.cpp object/inc/camera.h object/src/camera.cpp scene/inc/scene.h math/inc/linalg.hpp drawer/inc/test_canvas.h drawer/src/test_canvas.cpp load/inc/mesh_model_source.h load/inc/mesh_objfile_source.h load/src/mesh_objfile_source.cpp tests/test_load.h load/inc/abstract.h load/inc/mesh_model_builder.h load/src/mesh_model_builder.cpp load/inc/loader.h load/src/loader.cpp  load/inc/mesh_model_loader.h load/src/mesh_model_loader.cpp manager/inc/base_manager.h manager/inc/transform_manager.h manager/src/transform_manager.cpp drawer/inc/test_canvas.h drawer/inc/base_canvas.h visitor/inc/base_visitor.h scene/inc/scene_group.h scene/src/scene_group.cpp scene/src/scene.cpp visitor/inc/draw_visitor.h visitor/src/draw_visitor.cpp manager/inc/camera_manager.h tests/test_draw.h drawer/src/test_canvas.cpp drawer/src/test_canvas.cpp manager/inc/scene_manager.h manager/src/scene_manager.cpp manager/src/camera_manager.cpp manager/inc/test_draw_manager.h manager/src/test_draw_manager.cpp manager/inc/load_manager.h manager/src/load_manager.cpp drawer/inc/qt_canvas.h tests/test_managers.h object/inc/model_ref.h command/inc/base_command.h command/facade.h command/inc/scene_command.h command/src/scene_command.cpp command/inc/model_command.h command/src/model_command.cpp command/inc/object_command.h command/src/object_command.cpp drawer/src/qt_canvas.cpp drawer/inc/qt_canvas_factory.h drawer/src/qt_canvas_factory.cpp drawer/inc/canvas_factory.h manager/inc/draw_manager.h manager/src/draw_manager.cpp qt_ui/scene_meta.h qt_ui/scene_meta.cpp qt_ui/interactor.h qt_ui/logic.h qt_ui/logic.cpp qt_ui/interactor.cpp math/src/linalg.cpp command/inc/camera_command.h command/src/camera_command.cpp math/inc/glm_wrapper.h object/inc/light_source.h manager/inc/manager_solution.h manager/src/manager_solution.cpp exception/base_exception.h exception/loader_exceptions.h exception/logic_exceptions.h math/src/glm_wrapper.cpp load/inc/mesh_model_source_factory.h load/src/mesh_model_source_factory.cpp drawer/inc/canvas_solution.h drawer/src/canvas_solution.cpp)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 3 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(3 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(3 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets  ${GTEST_LIBRARIES} Threads::Threads glm)
enable_testing()

set_target_properties(3 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3)
endif()
