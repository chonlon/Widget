set(HeadDir ${CMAKE_CURRENT_LIST_DIR}/include)
set(SrcDir ${CMAKE_CURRENT_LIST_DIR}/src)

set(LonWidgetHeader
	${HeadDir}/autodeletewidgetpointer.hpp
	${HeadDir}/button.h
	${HeadDir}/listwidget.hpp
	${HeadDir}/menu.h
	${HeadDir}/messagebox.h
	${HeadDir}/TitleBar.h
	${HeadDir}/Windowo.h
)
set(LonWidgetSrc
	${SrcDir}/TitleBarrPrivate.hpp
	${SrcDir}/WindowPrivate.hpp
	${SrcDir}/messagebox.cpp
	${SrcDir}/Window.cpp
	${SrcDir}/TitleBar.cpp
	lon_widget.qrc
)

set(DemoSrc
	${CMAKE_CURRENT_LIST_DIR}/demo/runner/源.cpp
)

include_directories(${HeadDir} ${SrcDir})

add_library(LonWidgetLib STATIC ${LonWidgetHeader} ${LonWidgetSrc})
target_link_libraries(LonWidgetLib Qt5::Widgets Qt5::Gui Qt5::Core)