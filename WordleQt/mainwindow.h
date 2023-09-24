#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"Game.h"
#include <QMainWindow>
#include<Qstring>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Game *wordle;
    bool has_won;

private slots:
    void on_guessInput_returnPressed();
    void on_guessInput_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
