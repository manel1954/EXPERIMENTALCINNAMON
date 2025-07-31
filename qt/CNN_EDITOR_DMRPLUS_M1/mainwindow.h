#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Variables para usar
    QString modo;
    QString memorias;

private slots:
    void on_lineEdit_id_editingFinished();

    void on_lineEdit_callsign_editingFinished();

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_lineEdit_Timeout_editingFinished();

    void on_lineEdit_Display_editingFinished();

    void on_lineEdit_Duplex_editingFinished();

    void on_lineEdit_PorNextion_editingFinished();

    void on_pushButton_NextionAbrir_clicked();

    void on_pushButton_NextionCerrar_clicked();

    void on_lineEdit_RFModeHang_editingFinished();

    void on_pushButton_geany_clicked();

    void on_radioButton_DMR_pressed();

    void on_comboBox_Display_currentIndexChanged(int index);

    void on_lineEdit_TipoDisplay_editingFinished();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
