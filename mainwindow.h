#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include <detail.h>
#include <cut.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int blank_width_;
    int blank_length_;
    int detail_width_;
    int detail_length_;
    static const size_t scale_factor_ = 2;
    static const size_t screen_width_ = 840;
    static const size_t screen_height_ = 840;
    QVector <Detail> details_;
    Cut cut_;


private slots:
    void on_cutButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_addButton_clicked();

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_lineEdit_4_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
