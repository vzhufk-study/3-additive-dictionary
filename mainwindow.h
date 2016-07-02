#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{


    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    std::list<unsigned int> amount;
    std::list<float> time;
    std::string file_name = "1984.txt";
    std::string change_file_name = "1984.txt";

    void initValues(std::list<unsigned int> amount, std::list<float> time);
private slots:

    void on_draw_clicked();

    void on_open_clicked();

    void on_change_clicked();

    void on_out_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
