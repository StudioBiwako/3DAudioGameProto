/**
 * @file Window.h
 * @author Devendra Tambat
 *
 *
 */

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#ifndef INC_8_72_COMPONENTS_WINDOW_WINDOW_H
#define INC_8_72_COMPONENTS_WINDOW_WINDOW_H
class Window : public QMainWindow
{
public:
    Window(const QString &title);

};
#endif //INC_8_72_COMPONENTS_WINDOW_WINDOW_H
