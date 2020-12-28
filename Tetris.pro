SOURCES += \
    game.cpp \
    game_input_controller.cpp \
    gradient_raster_window.cpp \
    keyboard_handler.cpp \
    playingfield.cpp \
    tetrimino_factory.cpp \
    tetrimino.cpp \
    main.cpp

QT += core gui widgets gui 3dcore 3drender 3dinput 3dlogic 3dextras 3danimation

CONFIG += c++2a sdk_no_version_check

HEADERS += \
    game.hpp \
    game_input_controller.hpp \
    gradient_raster_window.hpp \
    keyboard_handler.hpp \
    input_controller.hpp \
    player_action.hpp \
    playingfield.hpp \
    tetrimino_factory.hpp \
    tetrimino.hpp
