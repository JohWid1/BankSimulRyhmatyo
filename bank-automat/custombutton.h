#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>


class CustomButton : public QWidget {
public:
    CustomButton(QWidget *parent = nullptr) : QWidget(parent) {
        QPushButton *button = new QPushButton("Insert\nCard", this);
        QLabel *line = new QLabel(this);

        // Style the line
        line->setStyleSheet("background-color: black; min-height: 2px; max-height: 2px;");

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(button);
        layout->addWidget(line);

        setLayout(layout);
    }
};

#endif // CUSTOMBUTTON_H
