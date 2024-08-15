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
	$$PWD/../code/rdv_globals.cpp \
	$$PWD/../code/rdv_scene.cpp \
	$$PWD/../code/rdv_coin.cpp \
	$$PWD/../code/rdv_question_box.cpp \
	$$PWD/../code/rdv_mushroom_box.cpp \
	$$PWD/../code/rdv_flower_box.cpp \
	$$PWD/../code/rdv_brick_platform.cpp \
	$$PWD/../code/rdv_wall_platform.cpp \
	$$PWD/../code/rdv_note_box.cpp \
	$$PWD/../code/rdv_player.cpp \
	$$PWD/../code/rdv_small_mario.cpp \
	$$PWD/../code/rdv_fire_mario.cpp \
	$$PWD/../code/rdv_goomba.cpp \
	$$PWD/../code/rdv_turtle.cpp \
	$$PWD/../code/rdv_piranha.cpp \
	$$PWD/../code/rdv_flag.cpp \
	$$PWD/../code/rdv_coin_counter.cpp \
	$$PWD/../code/rdv_score.cpp \
	$$PWD/../code/rdv_timer.cpp \
	$$PWD/../code/rdv_stretch.cpp \
	$$PWD/../code/rdv_conveyor.cpp \
	$$PWD/../code/rdv_giant_goomba.cpp \
	$$PWD/../code/rdv_warp_tube.cpp \
	$$PWD/../code/rdv_stair_block.cpp \
	$$PWD/../code/rdv_bomb.cpp \
	$$PWD/../code/rdv_red_turtle.cpp \
	$$PWD/../code/rdv_spiny.cpp \
	$$PWD/../code/rdv_castle.cpp \
	$$PWD/../code/rdv_pixmap_painter.cpp \
	$$PWD/../code/rdv_fire_ball.cpp \
	$$PWD/../code/rdv_level_complete_window.cpp \
	$$PWD/../code/rdv_game_over_window.cpp \
	$$PWD/../code/rdv_mushroom.cpp \
	$$PWD/../code/rdv_flower.cpp \

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
	$$PWD/../code/rdv_globals.h \
	$$PWD/../code/rdv_scene.h \
	$$PWD/../code/rdv_coin.h \
	$$PWD/../code/rdv_question_box.h \
	$$PWD/../code/rdv_mushroom_box.h \
	$$PWD/../code/rdv_flower_box.h \
	$$PWD/../code/rdv_brick_platform.h \
	$$PWD/../code/rdv_wall_platform.h \
	$$PWD/../code/rdv_note_box.h \
	$$PWD/../code/rdv_player.h \
	$$PWD/../code/rdv_small_mario.h \
	$$PWD/../code/rdv_fire_mario.h \
	$$PWD/../code/rdv_goomba.h \
	$$PWD/../code/rdv_turtle.h \
	$$PWD/../code/rdv_piranha.h \
	$$PWD/../code/rdv_flag.h \
	$$PWD/../code/rdv_coin_counter.h \
	$$PWD/../code/rdv_score.h \
	$$PWD/../code/rdv_timer.h \
	$$PWD/../code/rdv_stretch.h \
	$$PWD/../code/rdv_conveyor.h \
	$$PWD/../code/rdv_giant_goomba.h \
	$$PWD/../code/rdv_warp_tube.h \
	$$PWD/../code/rdv_stair_block.h \
	$$PWD/../code/rdv_bomb.h \
	$$PWD/../code/rdv_red_turtle.h \
	$$PWD/../code/rdv_spiny.h \
	$$PWD/../code/rdv_castle.h \
	$$PWD/../code/rdv_pixmap_painter.h \
	$$PWD/../code/rdv_fire_ball.h \
	$$PWD/../code/rdv_level_complete_window.h \
	$$PWD/../code/rdv_game_over_window.h \
	$$PWD/../code/rdv_mushroom.h \
	$$PWD/../code/rdv_flower.h \

FORMS +=\
	$$PWD/../code/rdv_user_registration.ui \

RESOURCES +=\
	mario.qrc \
	audio.qrc \

	