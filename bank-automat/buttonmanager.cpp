// buttonmanager.cpp
#include "buttonmanager.h"
#include <QPushButton>

ButtonManager::ButtonManager(QObject *parent) : QObject(parent)
{
    parentObject = parent;
}

void ButtonManager::connectNumeronappaimetToSlot(QObject *targetObject, const char *slot)
{
    for (int i = 0; i <= 9; ++i) {
        QString buttonName = "N" + QString::number(i);
        QPushButton *button = parentObject->findChild<QPushButton*>(buttonName);
        if (button) {
            QObject::connect(button, SIGNAL(clicked()), targetObject, slot);
        }
    }
}
