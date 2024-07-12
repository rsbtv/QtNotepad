#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Новый файл — Блокнот"); //установка названия окна
    ui->textEdit->setStyleSheet("border: none;"); //стиль границ
    fileSaved = false; //вводим булы
    textChanged = false;
    back = ui->textEdit->toPlainText().toUtf8(); //считываем изначальный текст
    fileOpened = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_open_triggered() //открыть файл
{ 
//    QString text = ui->textEdit->toPlainText().toUtf8(); //ссчитываем текст
    if (textChanged) // ЕСТЬ ИЗМЕНЕНИЯ - ПРЕДЛАГАЕМ СОХРАНИТЬ
    {
        int answer = QMessageBox::question(this, "Блокнот", "Хотите ли вы сохранить изменения?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (answer == QMessageBox::Yes) //ДА ХОЧУ СОХРАНИТЬ
        {
            if (!fileOpened) //ФАЙЛ НЕ ОТКРЫТЫЙ - СОХРАНЯЕМ КАК
            {
                on_action_saveas_triggered(); // если файл не имеет имя - запускаем сохранить как
                if (fileSaved) //ЕСЛИ ФАЙЛ СОХРАНЕН УСПЕШНО - ПЕРЕХОДИМ К ОТКРЫТИЮ
                {
                    QString fileName; //имя файла
                    // windows "C:\\Users\\student\\Documents", tr("Text file (*.txt)"));

                    // linux-style
                    fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "C:/Users/student/Documents", tr("Text file (*.txt)"));

                    if (fileName.isEmpty()) //выбран ли файл?
                    {//не выбран
                        QMessageBox::information(this, "Ошибка", "Файл не выбран", QMessageBox::Ok);

                    }
                    else
                    {//выбран
                        QFile file;
                        file.setFileName(fileName); //связать файловый поток с файлом
                        file.open(QIODevice::ReadOnly); //открыть файл

                        qint64 size; //размер файла

                        size=file.size();

                        QByteArray ba; //промежуточный массив для чтения данных
                        ba=file.read(size); //чтение из файла

                        ui->textEdit->clear(); //очистка поля от старых данных
                        ui->textEdit->append(QString(ba)); //добавляем данные
                        back = ba;

                        file.close(); //Закрыть файл

                        //выводим имя файла в название окна
                        QFileInfo fileInfo(fileName);
                        QString base = fileInfo.baseName(); //имя без пути
                        setWindowTitle(base + " — Блокнот");

                        back = ui->textEdit->toPlainText().toUtf8(); //ссчитываем изначальный текст

                        globalName = fileName;
                        textChanged = false;
                        fileOpened = true;
                    }
                }
            }
            else //ФАЙЛ ОТКРЫТ РАНЕЕ - СОХРАНЯЕМ
            {
                on_action_save_triggered();
                if (fileSaved) //ФАЙЛ УСПЕШНО СОХРАНЕН
                {
                    QString fileName; //имя файла
                    // windows "C:\\Users\\student\\Documents", tr("Text file (*.txt)"));

                    // linux-style
                    fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "C:/Users/student/Documents", tr("Text file (*.txt)"));

                    if (fileName.isEmpty()) //выбран ли файл?
                    {//не выбран
                        QMessageBox::information(this, "Ошибка", "Файл не выбран", QMessageBox::Ok);

                    }
                    else
                    {//выбран
                        QFile file;
                        file.setFileName(fileName); //связать файловый поток с файлом
                        file.open(QIODevice::ReadOnly); //открыть файл

                        qint64 size; //размер файла

                        size=file.size();

                        QByteArray ba; //промежуточный массив для чтения данных
                        ba=file.read(size); //чтение из файла

                        ui->textEdit->clear(); //очистка поля от старых данных
                        ui->textEdit->append(QString(ba)); //добавляем данные
                        back = ba;

                        file.close(); //Закрыть файл

                        //выводим имя файла в название окна
                        QFileInfo fileInfo(fileName);
                        QString base = fileInfo.baseName(); //имя без пути
                        setWindowTitle(base + " — Блокнот");

                        back = ui->textEdit->toPlainText().toUtf8(); //ссчитываем изначальный текст

                        globalName = fileName;
                        textChanged = false;
                        fileOpened = true;
                    }
                }
            }
        }
        else if (answer == QMessageBox::No) //НЕ ХОЧУ СОХРАНЯТЬ СРАЗУ ОТКРЫВАЕМ
        {
            QString fileName; //имя файла
            // windows "C:\\Users\\student\\Documents", tr("Text file (*.txt)"));

            // linux-style
            fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "C:/Users/student/Documents", tr("Text file (*.txt)"));

            if (fileName.isEmpty()) //выбран ли файл?
            {//не выбран
                QMessageBox::information(this, "Ошибка", "Файл не выбран", QMessageBox::Ok);

            }
            else
            {//выбран
                QFile file;
                file.setFileName(fileName); //связать файловый поток с файлом
                file.open(QIODevice::ReadOnly); //открыть файл

                qint64 size; //размер файла

                size=file.size();

                QByteArray ba; //промежуточный массив для чтения данных
                ba=file.read(size); //чтение из файла

                ui->textEdit->clear(); //очистка поля от старых данных
                ui->textEdit->append(QString(ba)); //добавляем данные
                back = ba;

                file.close(); //Закрыть файл

                //выводим имя файла в название окна
                QFileInfo fileInfo(fileName);
                QString base = fileInfo.baseName(); //имя без пути
                setWindowTitle(base + " — Блокнот");

                back = ui->textEdit->toPlainText().toUtf8(); //ссчитываем изначальный текст

                globalName = fileName;
                textChanged = false;
                fileOpened = true;
            }
        }
    }
    else // ИЗМЕНЕНИЙ НЕТ СРАЗУ ОТКРЫВАЕМ
    {
        QString fileName; //имя файла
        // windows "C:\\Users\\student\\Documents", tr("Text file (*.txt)"));

        // linux-style
        fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "C:/Users/student/Documents", tr("Text file (*.txt)"));

        if (fileName.isEmpty()) //выбран ли файл?
        {//не выбран
            QMessageBox::information(this, "Ошибка", "Файл не выбран", QMessageBox::Ok);

        }
        else
        {//выбран
            QFile file;
            file.setFileName(fileName); //связать файловый поток с файлом
            file.open(QIODevice::ReadOnly); //открыть файл

            qint64 size; //размер файла

            size=file.size();

            QByteArray ba; //промежуточный массив для чтения данных
            ba=file.read(size); //чтение из файла

            ui->textEdit->clear(); //очистка поля от старых данных
            ui->textEdit->append(QString(ba)); //добавляем данные
            back = ba;

            file.close(); //Закрыть файл
            //выводим имя файла в название окна
            QFileInfo fileInfo(fileName);
            QString base = fileInfo.baseName(); //имя без пути
            setWindowTitle(base + " — Блокнот");
            back = ui->textEdit->toPlainText().toUtf8(); //ссчитываем изначальный текст
            globalName = fileName;
            textChanged = false;
            fileOpened = true;
        }
    }
}

void MainWindow::on_action_saveas_triggered() //сохранить как
{
    QString fileName; //имя файла

    fileName = QFileDialog::getSaveFileName(this, "Сохранить файл", "C:/Users/student/Documents", tr("Text file (*.txt)"));

    if (fileName.isEmpty()) //выбран ли файл?
    {//не выбран
        QMessageBox::information(this, "Ошибка", "Файл не выбран", QMessageBox::Ok);
        fileSaved = false;
    }
    else
    {//выбран
//        back = ui->textEdit->toPlainText().toUtf8();
        QFile file;
        file.setFileName(fileName); //связать файловый поток с файлом
        file.open(QIODevice::WriteOnly); //открыть файл

        file.write(ui->textEdit->toPlainText().toUtf8()); //запись

        file.close(); //Закрыть файл
        fileSaved = true;
        //выводим имя файла в название окна
        QFileInfo fileInfo(fileName);
        QString base = fileInfo.baseName();
        setWindowTitle(base + " — Блокнот");
        globalName = fileName;
        textChanged = false;
        back = ui->textEdit->toPlainText().toUtf8();
        fileOpened = true;
    }


}

void MainWindow::on_action_exit_triggered() //выход
{
    if (textChanged) //ЕСТЬ ИЗМЕНЕНИЯ - ПРЕДЛАГАЕМ СОХРАНИТЬ
    {
        int answer = QMessageBox::question(this, "Блокнот", "Хотите ли вы сохранить изменения?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (answer == QMessageBox::No) //НЕ ХОЧУ СОХРАНЯТЬ
            QApplication::quit();
        if (answer == QMessageBox::Yes) //ХОЧУ СОХРАНИТЬ
        {
            if (!fileOpened) //ФАЙЛ НЕ ОТКРЫТ РАНЕЕ - СОХРАНЯЕМ КАК
            {
                on_action_saveas_triggered();
                if (fileSaved)
                    QApplication::quit();
            }
            else //ФАЙЛ БЫЛ РАНЕЕ ОТКРЫТ - СОХРАНЯЕМ
            {
                on_action_save_triggered();
                if (fileSaved)
                    QApplication::quit();
            }
        }
    }
    else //ИЗМЕНЕНИЙ НЕТ - СПОКОЙНО ВЫХОДИМ
    {
        QApplication::quit();
    }
}


void MainWindow::closeEvent(QCloseEvent * event) //событие закрытия окна
{
    if (textChanged) //ЕСТЬ ИЗМЕНЕНИЯ
    {
        int answer = QMessageBox::question(this, "Блокнот", "Хотите ли вы сохранить изменения?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (answer == QMessageBox::Yes) //ХОЧУ СОХРАНИТЬ
        {
            if (!fileOpened) //ФАЙЛ НЕ БЫЛ ОТКРЫТ РАНЕЕ - СОХРАНЯЕМ КАК
            {
                on_action_saveas_triggered();
                if (fileSaved) //СОХРАНЕНИЕ УСПЕШНО
                    event->accept(); //закрываем
                else
                    event->ignore(); //не закрываем
            }
            else //ФАЙЛ ОТКРЫТ РАНЕЕ - СОХРАНЯЕМ
            {
                on_action_save_triggered();
                if (fileSaved) //СОХРАНЕНИЕ УСПЕШНО
                    event->accept();
                else
                    event->ignore();
            }
        }
        else if (answer == QMessageBox::No) //НЕ ХОЧУ СОХРАНЯТЬ
            event->accept();
        else
            event->ignore();
    }
    else //ИЗМЕНЕНИЙ НЕТ СПОКОЙНО ЗАКРЫВАЕМ
        event->accept();
}

void MainWindow::on_action_save_triggered() // сохранить
{
    if (fileOpened) //ФАЙЛ ОТКРЫТ РАНЕЕ - ПРОСТО СОХРАНЯЕМ
    {
        QFile file;
        file.setFileName(globalName); //связать файловый поток с файлом
        file.open(QIODevice::WriteOnly); //открыть файл

        file.write(ui->textEdit->toPlainText().toUtf8()); //запись

        file.close(); //Закрыть файл
        fileSaved = true;
        textChanged = false;
        back = ui->textEdit->toPlainText().toUtf8();
        QFileInfo fileInfo(globalName);
        QString base = fileInfo.baseName();
        setWindowTitle(base + " — Блокнот"); //записываем имя в файла в заголовок программы
    }
    else //ФАЙЛ НЕ БЫЛ ОТКРЫТ РАНЕЕ - СОХРАНЯЕМ КАК
    {
        fileSaved = false;
        on_action_saveas_triggered();
    }
}


void MainWindow::on_action_create_triggered() //создать
{
    if (textChanged) //ЕСТЬ ИЗМЕНЕНИЯ - ПРЕДЛАГАЕМ СОХРАНИТЬ
    {
        int answer = QMessageBox::question(this, "Блокнот", "Хотите ли вы сохранить изменения?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (answer == QMessageBox::Yes) //ДА ХОЧУ СОХРАНИТЬ
        {
            if (!fileOpened) //ФАЙЛ НЕ БЫЛ ОТКРЫТ РАНЕЕ - СОХРАНЯЕМ КАК
            {
                on_action_saveas_triggered();
                if (fileSaved) //СОХРАНЕНИЕ УСПЕШНО
                {
                    QFile file;
                    file.setFileName("Новый файл");
                    setWindowTitle("Новый файл");
                    ui->textEdit->clear();
                    globalName = "Новый файл";
                    this->setWindowTitle("Новый файл  — Блокнот");
                    textChanged = false;
                    fileOpened = false;
                    back = ui->textEdit->toPlainText().toUtf8();
                }
            }
            else //ФАЙЛ БЫЛ ОТКРЫТ РАНЕЕ - СОХРАНЯЕМ
            {
                on_action_save_triggered();
                if (fileSaved) //СОХРАНЕНИЕ УСПЕШНО
                {
                    QFile file;
                    file.setFileName("Новый файл");
                    setWindowTitle("Новый файл");
                    ui->textEdit->clear();
                    globalName = "Новый файл";
                    this->setWindowTitle("Новый файл  — Блокнот");
                    textChanged = false;
                    fileOpened = false;
                    back = ui->textEdit->toPlainText().toUtf8();
                }
            }
        }
        else if (answer == QMessageBox::No) //НЕ ХОЧУ СОХРАНЯТЬ - СПОКОЙНО СОЗДАЕМ
        {
            QFile file;
            file.setFileName("Новый файл");
            setWindowTitle("Новый файл");
            globalName = "Новый файл";
            ui->textEdit->clear();
            this->setWindowTitle("Новый файл  — Блокнот");
            textChanged = false;
            fileOpened = false;
            back = ui->textEdit->toPlainText().toUtf8();
        }
    }
    else //НЕТ ИЗМЕНЕНИЙ - СПОКОЙНО СОЗДАЕМ
    {
        QFile file;
        file.setFileName("Новый файл");
        setWindowTitle("Новый файл");
        globalName = "Новый файл";
        ui->textEdit->clear();
        this->setWindowTitle("Новый файл  — Блокнот");
        textChanged = false;
        fileOpened = false;
        back = ui->textEdit->toPlainText().toUtf8();
    }
}

void MainWindow::on_textEdit_textChanged() //текст изменен
{
//    int number = ui->textEdit->toPlainText().length();
//    ui->label_count->setNum(number);
    QFileInfo fileInfo(globalName);
    QString base = fileInfo.baseName(); //ссчитываем имя в названии окна
    QString text;
    text = ui->textEdit->toPlainText().toUtf8();
    if (text!=back) //текст изменен
    {
        if (!fileOpened) //ФАЙЛ НЕ БЫЛ ОТКРЫТ РАНЕЕ
        {
            base = "";
            this->setWindowTitle(base + "*Новый файл" + " — Блокнот");
            textChanged = true;
            fileSaved = false;
        }
        else //ФАЙЛ БЫЛ ОТКРЫТ РАНЕЕ
        {
            this->setWindowTitle("*" + base + " — Блокнот");
            textChanged = true;
            fileSaved = false;
        }

    }
    else //нет изменений
    {
        if (!fileOpened)
        {
            textChanged = false;
            base = "";
            this->setWindowTitle(base + "Новый файл" + " — Блокнот");
        }
        else
        {
            this->setWindowTitle(base + " — Блокнот");
            textChanged = false;
        }
    }
}

