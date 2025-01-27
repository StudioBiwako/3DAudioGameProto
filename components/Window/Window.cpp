/**
 * @file Window.cpp
 * @author Devendra Tambat
 */

#include "Window.h"

Window::Window(const QString &title)
{
setWindowTitle(title);
resize(300, 300);

QWidget *centralWidget = new QWidget(this);
QVBoxLayout *layout = new QVBoxLayout(centralWidget);

QPushButton *button = new QPushButton("Button in " + title, centralWidget);
layout->addWidget(button);

setCentralWidget(centralWidget);
}