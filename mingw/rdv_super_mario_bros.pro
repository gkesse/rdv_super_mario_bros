TARGET = rdv_super_mario_bros
TEMPLATE = app
CONFIG += console debug
QT += widgets core5compat multimedia sql

DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build

QMAKE_CXXFLAGS +=\
	-std=c++17 \

SOURCES +=\
	$$PWD/../code/main.cpp \
	$$PWD/../code/rdv_application.cpp \
	$$PWD/../code/rdv_startup.cpp \
	$$PWD/../code/rdv_splashscreen.cpp \
	$$PWD/../code/rdv_window_startup.cpp \
	$$PWD/../code/rdv_window.cpp \
	$$PWD/../code/rdv_settings.cpp \
	$$PWD/../code/rdv_view.cpp \
	$$PWD/../code/rdv_title.cpp \
	$$PWD/../code/rdv_sound_manager.cpp \
	$$PWD/../code/rdv_db_mysql.cpp \
	$$PWD/../code/rdv_db_mysql_run.cpp \
	$$PWD/../code/rdv_game_dao.cpp \
	$$PWD/../code/rdv_user_registration.cpp \
	$$PWD/../code/rdv_errors.cpp \

HEADERS +=\
	$$PWD/../code/rdv_application.h \
	$$PWD/../code/rdv_startup.h \
	$$PWD/../code/rdv_splashscreen.h \
	$$PWD/../code/rdv_window_startup.h \
	$$PWD/../code/rdv_window.h \
	$$PWD/../code/rdv_settings.h \
	$$PWD/../code/rdv_view.h \
	$$PWD/../code/rdv_title.h \
	$$PWD/../code/rdv_sound_manager.h \
	$$PWD/../code/rdv_db_mysql.h \
	$$PWD/../code/rdv_db_mysql_run.h \
	$$PWD/../code/rdv_game_dao.h \
	$$PWD/../code/rdv_user_registration.h \
	$$PWD/../code/rdv_errors.h \

FORMS +=\
	$$PWD/../code/rdv_user_registration.ui \

RESOURCES +=\
	mario.qrc \
	audio.qrc \

	