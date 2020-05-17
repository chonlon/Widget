cmake_minimum_required(VERSION 3.0.2)
project(lon_widget)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#include_directories(${CMAKE_CURRENT_LIST_DIR})
find_package(Qt5 COMPONENTS Core Gui Widgets)

set(HeadDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(SrcDir ${CMAKE_CURRENT_LIST_DIR}/src)

set(BuildDemo OFF CACHE BOOL "Add Build Demo.")
set(BuildTest OFF CACHE BOOL "Add Build Test.")


set(LonWidgetHeader
	${HeadDir}/button.h
	${HeadDir}/listwidget.h
	${HeadDir}/menu.h
	${HeadDir}/Toast.h
	${HeadDir}/ShadowWindow.h
	${HeadDir}/Dialog.h
	${HeadDir}/messagebox.h
	${HeadDir}/TitleBar.h
	${HeadDir}/Window.h

	${SrcDir}/AnonymousHeader/Base.h
)
set(LonWidgetSrc
	${SrcDir}/AnonymousHeader/TitleBarPrivate.hpp
	${SrcDir}/AnonymousHeader/WindowPrivate.hpp
	${SrcDir}/AnonymousHeader/DialogPrivate.hpp

	${SrcDir}/messagebox.cpp
	${SrcDir}/Window.cpp
	${SrcDir}/TitleBar.cpp
	${SrcDir}/ShadowWindow.cpp
	${SrcDir}/Button.cpp
	${SrcDir}/Toast.cpp
	${SrcDir}/Dialog.cpp
	lon_widget.qrc
)



include_directories(${HeadDir} ${HeadDir}/3dpart ${SrcDir} ${SrcDir}/AnonymousHeader)

add_library(LonWidgetLib STATIC ${LonWidgetHeader} ${LonWidgetSrc})
target_link_libraries(LonWidgetLib Qt5::Widgets Qt5::Gui Qt5::Core)

if(BuildDemo)
	add_executable(demo ${CMAKE_CURRENT_LIST_DIR}/demo/runner/源.cpp)
	target_link_libraries(demo LonWidgetLib Qt5::Widgets Qt5::Gui Qt5::Core)
endif()