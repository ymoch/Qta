#-------------------------------------------------
#
# Project created by QtCreator 2014-09-13T10:05:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qta
TEMPLATE = app

CONFIG += \
    c++11

QMAKE_CFLAGS_WARN_ON
QMAKE_CXXFLAGS_WARN_ON

QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3

SOURCES += \
    src/app/main.cpp \
    src/app/application.cpp \
    src/app/application_config.cpp \
    src/gui/common.cpp \
    src/gui/main_dialog.cpp \
    src/gui/control_edit_time_dialog.cpp \
    src/gui/control_inherit_time_dialog.cpp \
    src/gui/timer_edit_dialog.cpp \
    src/gui/gui_config.cpp \
    src/core/api/timer_table.cpp \
    src/core/api/timer_table_config.cpp \
    src/core/timer/timer.cpp \
    src/core/timer/timer_item.cpp \
    src/core/timer/category.cpp \
    src/core/manager/timer_table_manager.cpp \
    src/core/manager/category_manager.cpp \
    src/externals/id_maker/id_maker.cpp \
    src/externals/time_util/formatted_time.cpp

HEADERS += \
    src/app/application.h \
    src/app/application_config.h \
    src/gui/time/formatted_time.h \
    src/gui/common.h \
    src/gui/main_dialog.h \
    src/gui/control_edit_time_dialog.h \
    src/gui/control_inherit_time_dialog.h \
    src/gui/timer_edit_dialog.h \
    src/gui/gui_config.h \
    src/core/api/typedef.h \
    src/core/api/return_code.h \
    src/core/api/timer_table.h \
    src/core/api/timer_table_config.h \
    src/core/timer/timer.h \
    src/core/timer/timer_item.h \
    src/core/timer/category.h \
    src/core/manager/timer_table_manager.h \
    src/core/manager/category_manager.h \
    src/externals/serialization/oarchive.h \
    src/externals/serialization/archive.h \
    src/externals/serialization/iarchive.h \
    src/externals/id_maker/id_maker.h \
    src/externals/time_util/formatted_time.h \
    src/core/api/version.h \
    src/externals/serialization/typedef.h \
    src/app/version.h

FORMS += \
    src/gui/main_dialog.ui \
    src/gui/control_inherit_time_dialog.ui \
    src/gui/control_edit_time_dialog.ui \
    src/gui/timer_edit_dialog.ui \

Release:DESTDIR = release
Debug:DESTDIR   = debug
OBJECTS_DIR     = .obj
MOC_DIR         = .moc
RCC_DIR         = .rcc
UI_DIR          = .ui
