#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <additivedictionarybin.h>
#include <additivedictionaryhash.h>
#include <additivedictionaryhtc.h>

#include <fstream>

#include <ctime>

const unsigned amount_multy = 1000;

AdditiveDictionaryBin Bin;
AdditiveDictionaryHash Hash;
AdditiveDictionaryHTC HTC;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initValues(std::list<unsigned int> amount, std::list<float> time){
    this->time = time;
    this->amount = amount;
}
void MainWindow::on_draw_clicked()
{
    Bin.toDoFromFile(file_name, 11*amount_multy, AdditiveDictionaryBin::addValue);
    HTC.toDoFromFile(file_name, 11*amount_multy, AdditiveDictionaryHTC::addValue);
    Hash.toDoFromFile(file_name, 11*amount_multy, AdditiveDictionaryHash::addValue);
    if (ui->structure->currentIndex() == 0){
        for (unsigned i = 1; i < 11; ++i){
            clock_t begin = clock();
            if (ui->action->currentIndex() == 0){
                Bin.toDoFromFile(change_file_name, i*amount_multy, AdditiveDictionaryBin::addValue);
            }else if (ui->action->currentIndex() == 1){
                Bin.toDoFromFile(change_file_name, i*amount_multy, AdditiveDictionaryBin::delValue);
            }else{
                Bin.toDoFromFile(change_file_name, i*amount_multy, AdditiveDictionaryBin::findValue);
            }

            clock_t end = clock();
            time.push_back(end - begin);
            amount.push_back(i*amount_multy);
        }
    }else if (ui->structure->currentIndex() == 1){
        for (unsigned i = 1; i < 11; ++i){
            clock_t begin = clock();
            if (ui->action->currentIndex() == 0){
                HTC.toDoFromFile(change_file_name, i*amount_multy, AdditiveDictionaryHTC::addValue);
            }else if (ui->action->currentIndex() == 1){
                HTC.toDoFromFile(change_file_name, i*amount_multy, AdditiveDictionaryHTC::delValue);
            }else{
                HTC.toDoFromFile(change_file_name, i*amount_multy, AdditiveDictionaryHTC::findValue);
            }

            clock_t end = clock();
            time.push_back(end - begin);
            amount.push_back(i*amount_multy);
        }
    }else{
        for (unsigned i = 1; i < 11; ++i){
            clock_t begin = clock();
            if (ui->action->currentIndex() == 0){
                Hash.toDoFromFile(change_file_name, i*amount_multy, AdditiveDictionaryHash::addValue);
            }else if (ui->action->currentIndex() == 1){
                Hash.toDoFromFile(change_file_name, i*amount_multy, AdditiveDictionaryHash::delValue);
            }else{
                Hash.toDoFromFile(change_file_name, i*amount_multy, AdditiveDictionaryHash::findValue);
            }

            clock_t end = clock();
            time.push_back(end - begin);
            amount.push_back(i*amount_multy);
        }
    }



    float max_time = time.front();
    unsigned max_amount = amount.front();
    float min_time = time.front();
    unsigned min_amount = amount.front();

    QVector<double> x(time.size()), y(amount.size());
    int i = 0;
    while(!amount.empty()) {
        x[i] = amount.front();
        y[i] = time.front();

        if(time.front() > max_time){
            max_time = time.front();
        }
        if(time.front() < min_time){
            min_time = time.front();
        }
        if(amount.front() > max_amount){
            max_amount = amount.front();
        }
        if(amount.front() < min_amount){
            min_amount = amount.front();
        }


        time.pop_front();
        amount.pop_front();
        i++;




    }

    ui->plot->clearGraphs();
    ui->plot->addGraph();
    ui->plot->graph(0)->setData(x,y);

    ui->plot->xAxis->setLabel("Amount");
    ui->plot->yAxis->setLabel("Time");

    ui->plot->xAxis->setRange(0, max_amount);


    ///
    double minY = min_time;
    double maxY = max_time;

    ui->plot->yAxis->setRange(minY,maxY);

    ui->plot->replot();

}

void MainWindow::on_open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"));
    file_name = fileName.toStdString();
}


void MainWindow::on_change_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"));
    change_file_name = fileName.toStdString();
}

void MainWindow::on_out_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"));
    std::string save_file_name = fileName.toStdString();



    std::ofstream output;
    output.open(save_file_name, std::ofstream::out | std::ofstream::app);

    if (ui->structure->currentIndex() == 0){
        std::list<ADWord> X = Bin.inOrder(treeElement<ADWord>::getRight, treeElement<ADWord>::getLeft);


        while (!X.empty()){
            std::string result_line;
            result_line.append(X.front().getValue());
            result_line.append(" - ");
            result_line.append(std::to_string(X.front().getAmount()));
            result_line.append("\n");

            output<<result_line;

            X.pop_front();
        }
    }else if (ui->structure->currentIndex() == 1){
         std::list<ADWord> X = HTC.out();
         while (!X.empty()){
             std::string result_line;
             result_line.append(X.front().getValue());
             result_line.append(" - ");
             result_line.append(std::to_string(X.front().getAmount()));
             result_line.append("\n");

             output<<result_line;

             X.pop_front();
         }
    }else{
        std::list<ADWord> X = Hash.out();
        while (!X.empty()){
            std::string result_line;
            result_line.append(X.front().getValue());
            result_line.append(" - ");
            result_line.append(std::to_string(X.front().getAmount()));
            result_line.append("\n");

            output<<result_line;

            X.pop_front();
        }
    }
}
