#-------------------------------------------------
#
# Project created by QtCreator 2018-09-05T16:42:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IM_INSAN
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/scene/Scene.cpp \
    src/scene/SceneStart.cpp \
    src/scene/SceneStory.cpp \
    src/scene/SceneBattle.cpp \
    src/scene/SceneSelect.cpp \
    src/object/BreedFactury.cpp \
    src/object/Logic.cpp \
    src/object/Effect.cpp \
    src/object/EffectContainer.cpp \
    src/component/ComponentPaint.cpp \
    src/scene/SceneMachine.cpp \
    src/scene/GVariantKeeper.cpp \
    src/object/ObjectScript.cpp \
    src/object/ObjectBlock.cpp \
    src/object/ObjectSprite.cpp \
    src/object/ObjectGame.cpp \
    src/object/Breed.cpp \
    src/object/LogicFSM.cpp

HEADERS += \
    src/mainwindow.h \
    src/scene/Scene.h \
    src/scene/SceneStart.h \
    src/scene/SceneStory.h \
    src/scene/SceneBattle.h \
    src/scene/SceneSelect.h \
    src/Constant.h \
    src/object/BreedFactury.h \
    src/object/Logic.h \
    src/object/Effect.h \
    src/object/EffectContainer.h \
    src/component/ComponentPaint.h \
    src/scene/SceneMachine.h \
    src/scene/GVariantKeeper.h \
    src/object/ObjectScript.h \
    src/object/ObjectBlock.h \
    src/object/ObjectSprite.h \
    src/object/ObjectGame.h \
    src/object/Breed.h \
    src/object/LogicFSM.h

FORMS += \
    src/mainwindow.ui

RESOURCES += \
    images.qrc
