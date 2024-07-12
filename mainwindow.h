#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog> //библиотека диалоговых окон работы с файлами
#include <QMessageBox>
#include <QCloseEvent> //для перехвата сигнала закрытия окна
#include <QTranslator> //перевод на русский
#include <QLibraryInfo>
#include <QApplication>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_open_triggered();

    void on_action_saveas_triggered();

    void on_action_exit_triggered();

    void closeEvent(QCloseEvent * event); //событие закрытия окна

    void on_action_save_triggered();

    void on_action_create_triggered();

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
    bool textChanged = false;
    bool fileSaved = false;
    bool fileOpened;
    QString globalName;
    QString back;

};

#endif // MAINWINDOW_H
