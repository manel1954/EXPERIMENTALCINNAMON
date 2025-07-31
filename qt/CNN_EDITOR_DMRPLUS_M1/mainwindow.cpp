#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string"
#include "iostream"
#include "QTextEdit"
#include "QLineEdit"
#include "QObject"
#include "QLabel"
#include "QString"
#include "QMessageBox"
#include "QFile"
#include "QTextStream"
#include "QInputDialog"
#include "QTextCodec"
#include "QTimer"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Variables para usar
    modo = "/home/pi/MMDVMHost/MMDVMPLUS.ini_M1";
    memorias = "/home/pi/.local/memorias.ini";

    // la linea siguiente oculta toda la barra superior del formulario
     setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);

    // POSICION DEL FORMULARIO EN LA PANTALLA
    int px  = (1285);
    int py = (63);
    this->move(   QPoint(px,py)  );


    ui->groupBox->setVisible(true);

    // Presenta el fichero memorias
    QFile file0(memorias);
    if (!file0.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr, "info", file0.errorString());
        return;
    }
    QTextStream in0(&file0);
    QString line0;
    bool inDMRPLUSSection = false;

    //Memoria
    while (!in0.atEnd()) {
        line0 = in0.readLine().trimmed();
        if (line0.startsWith('[')) {
            if (line0 == "[DMRPLUS]") {
                inDMRPLUSSection = true;
            } else {
                inDMRPLUSSection = false;
            }
        }
        if (inDMRPLUSSection && line0.startsWith("M1=")) {
            QString memoria = line0.section('=', 1);  // Extrae el valor después del '='
            QString leer = "MEMORIA 1   - " + memoria + " -";
            ui->lineEdit_EDITOR_DMRPLUS->setText(leer);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }


    // Presenta el fichero MMDVMhost
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr, "info", file.errorString());
        return;
    }
    QTextStream in(&file);
    QString line;
    bool inGeneralSection = false;

    //Callsign
    while (!in.atEnd()) {
        line = in.readLine().trimmed();

        // Detecta la sección [Network]
        if (line.startsWith('[')) {
            if (line == "[General]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }

        if (inGeneralSection && line.startsWith("Callsign=")) {
            QString callsign = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_callsign->setText(callsign);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //Id
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[General]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }

        if (inGeneralSection && line.startsWith("Id=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_id->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //Port Nextion
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Nextion]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("Port=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_PorNextion->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

 // **************************************************************************************
 // esta rutina hay que hacerla siempre que utilizemos un parametro que no sea consecutivo
    file.close();
    // Presenta el fichero MMDVMhost
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr, "info", file.errorString());
        return;
    }
// ***************************************************************************************

    //Timeout
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[General]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("Timeout=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_Timeout->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //Duplex
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[General]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }

        if (inGeneralSection && line.startsWith("Duplex=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_Duplex->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //RFModeHang
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[General]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }

        if (inGeneralSection && line.startsWith("RFModeHang=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_RFModeHang->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //Display
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[General]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("Display=")) {
            QString display = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_TipoDisplay->setText(display);
            ui->lineEdit_Display->setText(display);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //RXFrequency
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Info]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("RXFrequency=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_RXF->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //TXFrequency
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Info]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("TXFrequency=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_TXF->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }
    //Latitude
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Info]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("Latitude=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_Latitude->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //Longitude
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Info]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("Longitude=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_Longitude->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }
    //Location
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Info]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("Location=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_Location->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //URL
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Info]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("URL=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_URL->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

    //DisplayLevel
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Log]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("DisplayLevel=")) {
            QString id = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_DisplayLevel->setText(id);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }
    //FileLevel
        while (!in.atEnd()) {
            line = in.readLine().trimmed();
            if (line.startsWith('[')) {
                if (line == "[Log]") {
                    inGeneralSection = true;
                } else {
                    inGeneralSection = false;
                }
            }
            if (inGeneralSection && line.startsWith("FileLevel=")) {
                QString id = line.section('=', 1);  // Extrae el valor después del '='
                ui->lineEdit_FileLevel->setText(id);
                break;  // Ya lo encontramos, salimos del bucle
            }
        }

        //CW Id
            while (!in.atEnd()) {
                line = in.readLine().trimmed();
                if (line.startsWith('[')) {
                    if (line == "[CW Id]") {
                        inGeneralSection = true;
                    } else {
                        inGeneralSection = false;
                    }
                }
                if (inGeneralSection && line.startsWith("Enable=")) {
                    QString id = line.section('=', 1);  // Extrae el valor después del '='
                    ui->lineEdit_CW_Id->setText(id);
                    break;  // Ya lo encontramos, salimos del bucle
                }
            }

            //UARTPort
                while (!in.atEnd()) {
                    line = in.readLine().trimmed();
                    if (line.startsWith('[')) {
                        if (line == "[Modem]") {
                            inGeneralSection = true;
                        } else {
                            inGeneralSection = false;
                        }
                    }
                    if (inGeneralSection && line.startsWith("UARTPort=")) {
                        QString id = line.section('=', 1);  // Extrae el valor después del '='
                        ui->lineEdit_UARTPort->setText(id);
                        break;  // Ya lo encontramos, salimos del bucle
                    }
                }

                //TXInvert
                    while (!in.atEnd()) {
                        line = in.readLine().trimmed();
                        if (line.startsWith('[')) {
                            if (line == "[Modem]") {
                                inGeneralSection = true;
                            } else {
                                inGeneralSection = false;
                            }
                        }
                        if (inGeneralSection && line.startsWith("TXInvert=")) {
                            QString id = line.section('=', 1);  // Extrae el valor después del '='
                            ui->lineEdit_TXInvert->setText(id);
                            break;  // Ya lo encontramos, salimos del bucle
                        }
                    }

                    //RXInvert
                        while (!in.atEnd()) {
                            line = in.readLine().trimmed();
                            if (line.startsWith('[')) {
                                if (line == "[Modem]") {
                                    inGeneralSection = true;
                                } else {
                                    inGeneralSection = false;
                                }
                            }
                            if (inGeneralSection && line.startsWith("RXInvert=")) {
                                QString id = line.section('=', 1);  // Extrae el valor después del '='
                                ui->lineEdit_RXInvert->setText(id);
                                break;  // Ya lo encontramos, salimos del bucle
                            }
                        }

                        //RXOffset
                            while (!in.atEnd()) {
                                line = in.readLine().trimmed();
                                if (line.startsWith('[')) {
                                    if (line == "[Modem]") {
                                        inGeneralSection = true;
                                    } else {
                                        inGeneralSection = false;
                                    }
                                }
                                if (inGeneralSection && line.startsWith("RXOffset=")) {
                                    QString id = line.section('=', 1);  // Extrae el valor después del '='
                                    ui->lineEdit_RXOffset->setText(id);
                                    break;  // Ya lo encontramos, salimos del bucle
                                }
                            }

                            //TXOffset
                                while (!in.atEnd()) {
                                    line = in.readLine().trimmed();
                                    if (line.startsWith('[')) {
                                        if (line == "[Modem]") {
                                            inGeneralSection = true;
                                        } else {
                                            inGeneralSection = false;
                                        }
                                    }
                                    if (inGeneralSection && line.startsWith("TXOffset=")) {
                                        QString id = line.section('=', 1);  // Extrae el valor después del '='
                                        ui->lineEdit_TXOffset->setText(id);
                                        break;  // Ya lo encontramos, salimos del bucle
                                    }
                                }

                                //RXLevel
                                    while (!in.atEnd()) {
                                        line = in.readLine().trimmed();
                                        if (line.startsWith('[')) {
                                            if (line == "[Modem]") {
                                                inGeneralSection = true;
                                            } else {
                                                inGeneralSection = false;
                                            }
                                        }
                                        if (inGeneralSection && line.startsWith("RXLevel=")) {
                                            QString id = line.section('=', 1);  // Extrae el valor después del '='
                                            ui->lineEdit_RXLevel->setText(id);
                                            break;  // Ya lo encontramos, salimos del bucle
                                        }
                                    }

                                    //TXLevel
                                        while (!in.atEnd()) {
                                            line = in.readLine().trimmed();
                                            if (line.startsWith('[')) {
                                                if (line == "[Modem]") {
                                                    inGeneralSection = true;
                                                } else {
                                                    inGeneralSection = false;
                                                }
                                            }
                                            if (inGeneralSection && line.startsWith("TXLevel=")) {
                                                QString id = line.section('=', 1);  // Extrae el valor después del '='
                                                ui->lineEdit_TXLevel->setText(id);
                                                break;  // Ya lo encontramos, salimos del bucle
                                            }
                                        }

                                        //RXDCOffset
                                            while (!in.atEnd()) {
                                                line = in.readLine().trimmed();
                                                if (line.startsWith('[')) {
                                                    if (line == "[Modem]") {
                                                        inGeneralSection = true;
                                                    } else {
                                                        inGeneralSection = false;
                                                    }
                                                }
                                                if (inGeneralSection && line.startsWith("RXDCOffset=")) {
                                                    QString id = line.section('=', 1);  // Extrae el valor después del '='
                                                    ui->lineEdit_RXDCOffset->setText(id);
                                                    break;  // Ya lo encontramos, salimos del bucle
                                                }
                                            }
                                            //TXDCOffset
                                                while (!in.atEnd()) {
                                                    line = in.readLine().trimmed();
                                                    if (line.startsWith('[')) {
                                                        if (line == "[Modem]") {
                                                            inGeneralSection = true;
                                                        } else {
                                                            inGeneralSection = false;
                                                        }
                                                    }
                                                    if (inGeneralSection && line.startsWith("TXDCOffset=")) {
                                                        QString id = line.section('=', 1);  // Extrae el valor después del '='
                                                        ui->lineEdit_TXDCOffset->setText(id);
                                                        break;  // Ya lo encontramos, salimos del bucle
                                                    }
                                                }
                                                //Type
                                                while (!in.atEnd()) {
                                                line = in.readLine().trimmed();
                                                if (line.startsWith('[')) {
                                                if (line == "[DMR Network]") {
                                                inGeneralSection = true;
                                                } else {
                                                inGeneralSection = false;
                                                }
                                                }
                                                if (inGeneralSection && line.startsWith("Type=")) {
                                                QString id = line.section('=', 1);  // Extrae el valor después del '='
                                                ui->lineEdit_Type->setText(id);
                                                break;  // Ya lo encontramos, salimos del bucle
                                                }
                                                }

             //RemoteAddress
             while (!in.atEnd()) {
             line = in.readLine().trimmed();
             if (line.startsWith('[')) {
             if (line == "[DMR Network]") {
             inGeneralSection = true;
             } else {
             inGeneralSection = false;
             }
             }
             if (inGeneralSection && line.startsWith("RemoteAddress=")) {
             QString id = line.section('=', 1);  // Extrae el valor después del '='
             ui->lineEdit_RemoteAddress->setText(id);
             break;  // Ya lo encontramos, salimos del bucle
             }
             }

             //RemotePort
             while (!in.atEnd()) {
             line = in.readLine().trimmed();
             if (line.startsWith('[')) {
             if (line == "[DMR Network]") {
             inGeneralSection = true;
             } else {
             inGeneralSection = false;
             }
             }
             if (inGeneralSection && line.startsWith("RemotePort=")) {
             QString id = line.section('=', 1);  // Extrae el valor después del '='
             ui->lineEdit_RemotePort->setText(id);
             break;  // Ya lo encontramos, salimos del bucle
             }
             }

             //Password
             while (!in.atEnd()) {
             line = in.readLine().trimmed();
             if (line.startsWith('[')) {
             if (line == "[DMR Network]") {
             inGeneralSection = true;
             } else {
             inGeneralSection = false;
             }
             }
             if (inGeneralSection && line.startsWith("Password=")) {
             QString id = line.section('=', 1);  // Extrae el valor después del '='
             ui->lineEdit_Password->setText(id);
             break;  // Ya lo encontramos, salimos del bucle
             }
             }

             //Jitter
             while (!in.atEnd()) {
             line = in.readLine().trimmed();
             if (line.startsWith('[')) {
             if (line == "[DMR Network]") {
             inGeneralSection = true;
             } else {
             inGeneralSection = false;
             }
             }
             if (inGeneralSection && line.startsWith("Jitter=")) {
             QString id = line.section('=', 1);  // Extrae el valor después del '='
             ui->lineEdit_Jitter->setText(id);
             break;  // Ya lo encontramos, salimos del bucle
             }
             }

             //Slot1
             while (!in.atEnd()) {
             line = in.readLine().trimmed();
             if (line.startsWith('[')) {
             if (line == "[DMR Network]") {
             inGeneralSection = true;
             } else {
             inGeneralSection = false;
             }
             }
             if (inGeneralSection && line.startsWith("Slot1=")) {
             QString id = line.section('=', 1);  // Extrae el valor después del '='
             ui->lineEdit_Slot1->setText(id);
             break;  // Ya lo encontramos, salimos del bucle
             }
             }


             //Slot2
             while (!in.atEnd()) {
             line = in.readLine().trimmed();
             if (line.startsWith('[')) {
             if (line == "[DMR Network]") {
             inGeneralSection = true;
             } else {
             inGeneralSection = false;
             }
             }
             if (inGeneralSection && line.startsWith("Slot2=")) {
             QString id = line.section('=', 1);  // Extrae el valor después del '='
             ui->lineEdit_Slot2->setText(id);
             break;  // Ya lo encontramos, salimos del bucle
             }
             }


             //Options
             while (!in.atEnd()) {
             line = in.readLine().trimmed();
             if (line.startsWith('[')) {
             if (line == "[DMR Network]") {
             inGeneralSection = true;
             } else {
             inGeneralSection = false;
             }
             }
             if (inGeneralSection && line.startsWith("Options=")) {
             QString id = line.section('=', 1);  // Extrae el valor después del '='
             ui->lineEdit_Options->setText(id);
             break;  // Ya lo encontramos, salimos del bucle
             }
             }
    // **************************************************************************************
    // esta rutina hay que hacerla siempre que utilizemos un parametro que no sea consecutivo
       file.close();
       // Presenta el fichero MMDVMhost
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
           QMessageBox::information(nullptr, "info", file.errorString());
           return;
       }
   // ***************************************************************************************

       //[DMR] Enable
       while (!in.atEnd()) {
           line = in.readLine().trimmed();
           if (line.startsWith('[')) {
               if (line == "[DMR]") {
                   inGeneralSection = true;
               } else {
                   inGeneralSection = false;
               }
           }
           if (inGeneralSection && line.startsWith("Enable=")) {
               QString labeldmr = line.section('=', 1);  // Extrae el valor después del '='
               ui->label_DMR->setText(labeldmr);
               break;  // Ya lo encontramos, salimos del bucle
           }
       }

            if (ui->label_DMR->text() == "1") {
            ui->radioButton_DMR->setChecked(true);

        } else {
            ui->radioButton_DMR->setChecked(false);
        }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_id_editingFinished()
{
    QString nuevoId = ui->lineEdit_id->text();
    nuevoId = nuevoId.toUpper(); //convierte minúsculas a mayúsculas
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Id=" + nuevoId;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[General]");
        }
        if (enSeccionGeneral && linea.trimmed().startsWith("Id=")) {
            lineas << "Id=" + nuevoId;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_id->setText(nuevoId);
    ui->lineEdit_id->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_callsign_editingFinished()
{
    QString nuevoCallsign = ui->lineEdit_callsign->text();
    nuevoCallsign = nuevoCallsign.toUpper(); //convierte minúsculas a mayúsculas
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Callsign=" + nuevoCallsign;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[General]");
        }
        if (enSeccionGeneral && linea.trimmed().startsWith("Callsign=")) {
            lineas << "Callsign=" + nuevoCallsign;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_callsign->setText(nuevoCallsign);
    ui->lineEdit_callsign->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_pushButton_clicked()
{
    close();
}

void MainWindow::on_comboBox_currentIndexChanged(int /*index*/)
{
    //extrae número de item del comboBo
    QString sistema;

    if (ui->comboBox->currentIndex() == 1) {
    QString sed="sed -i '341c Port=modem' ";
    QString path=modo;
    QString PorNextion=sed + path;
    ui->lineEdit_puente->setText(PorNextion);
    system(ui->lineEdit_puente->text().toStdString().c_str());
    }


    if (ui->comboBox->currentIndex() == 2) {
    QString sed="sed -i '341c Port=/dev/ttyUSB0' ";
    QString path=modo;
    QString PorNextion=sed + path;
    ui->lineEdit_puente->setText(PorNextion);
    system(ui->lineEdit_puente->text().toStdString().c_str());
    }

    if (ui->comboBox->currentIndex() == 3) {
    QString sed="sed -i '341c Port=/dev/ttyUSB1' ";
    QString path=modo;
    QString PorNextion=sed + path;
    ui->lineEdit_puente->setText(PorNextion);
    system(ui->lineEdit_puente->text().toStdString().c_str());
    }

    if (ui->comboBox->currentIndex() == 4) {
    QString sed="sed -i '341c Port=/dev/rfcomm1' ";
    QString path=modo;
    QString PorNextion=sed + path;
    ui->lineEdit_puente->setText(PorNextion);
    system(ui->lineEdit_puente->text().toStdString().c_str());
    }

    if (ui->comboBox->currentIndex() == 5) {
    QString sed="sed -i '341c Port=/dev/rfcomm2' ";
    QString path=modo;
    QString PorNextion=sed + path;
    ui->lineEdit_puente->setText(PorNextion);
    system(ui->lineEdit_puente->text().toStdString().c_str());
    }

    if (ui->comboBox->currentIndex() == 6) {
    QString sed="sed -i '341c Port=/dev/virtual1' ";
    QString path=modo;
    QString PorNextion=sed + path;
    ui->lineEdit_puente->setText(PorNextion);
    system(ui->lineEdit_puente->text().toStdString().c_str());
    }

    if (ui->comboBox->currentIndex() == 7) {
    QString sed="sed -i '341c Port=/dev/virtual2' ";
    QString path=modo;
    QString PorNextion=sed + path;
    ui->lineEdit_puente->setText(PorNextion);
    system(ui->lineEdit_puente->text().toStdString().c_str());
    }
    // Presenta el fichero MMDVMhost
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr, "info", file.errorString());
        return;
    }
    QTextStream in(&file);
    QString line;
    bool inGeneralSection = false;

    //Callsign
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[Nextion]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("Port=")) {
            QString portnextion = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_PorNextion->setText(portnextion);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }

}

void MainWindow::on_lineEdit_Timeout_editingFinished()
{
    QString nuevoTimeout = ui->lineEdit_Timeout->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Timeout=" + nuevoTimeout;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[General]");
        }
        if (enSeccionGeneral && linea.trimmed().startsWith("Timeout=")) {
            lineas << "Timeout=" + nuevoTimeout;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Timeout->setText(nuevoTimeout);
    ui->lineEdit_Timeout->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_Display_editingFinished()
{
    QString nuevoDisplay = ui->lineEdit_Display->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Display=" + nuevoDisplay;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[General]");
        }
        if (enSeccionGeneral && linea.trimmed().startsWith("Display=")) {
            lineas << "Display=" + nuevoDisplay;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Display->setText(nuevoDisplay);
    ui->lineEdit_Display->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_Duplex_editingFinished()
{
    QString nuevoDuplex = ui->lineEdit_Duplex->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Duplex=" + nuevoDuplex;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[General]");
        }
        if (enSeccionGeneral && linea.trimmed().startsWith("Duplex=")) {
            lineas << "Duplex=" + nuevoDuplex;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Duplex->setText(nuevoDuplex);
    ui->lineEdit_Duplex->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_lineEdit_PorNextion_editingFinished()
{
    QString nuevoPortNextion = ui->lineEdit_PorNextion->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Port=" + nuevoPortNextion;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[Nextion]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("Port=")) {
            lineas << "Port=" + nuevoPortNextion;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_PorNextion->setText(nuevoPortNextion);
    ui->lineEdit_PorNextion->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_pushButton_NextionAbrir_clicked()
{
    ui->groupBox->setGeometry(0,65,626,595);
    //ui->groupBox->setVisible(true);
    ui->pushButton_NextionAbrir->setVisible(false);
    ui->pushButton_NextionCerrar->setVisible(true);
}
void MainWindow::on_pushButton_NextionCerrar_clicked()
{
    ui->groupBox->setGeometry(0,660,626,300);
    //ui->groupBox->setVisible(false);
    ui->pushButton_NextionAbrir->setVisible(true);
    ui->pushButton_NextionCerrar->setVisible(false);
}

void MainWindow::on_lineEdit_RFModeHang_editingFinished()
{
    QString nuevoRFModeHang = ui->lineEdit_RFModeHang->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "RFModeHang=" + nuevoRFModeHang;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[General]");
        }
        if (enSeccionGeneral && linea.trimmed().startsWith("RFModeHang=")) {
            lineas << "RFModeHang=" + nuevoRFModeHang;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_RFModeHang->setText(nuevoRFModeHang);
    ui->lineEdit_RFModeHang->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_pushButton_geany_clicked()
{
    system("geany /home/pi/MMDVMHost/MMDVMPLUS.ini_M1 &");
}

void MainWindow::on_radioButton_DMR_pressed()
{
    QString nuevodmr = "1";
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Enable=" + nuevodmr;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[DMR]");
        }
        if (enSeccionGeneral && linea.trimmed().startsWith("Enable=")) {
            lineas << "Enable=" + nuevodmr;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
//    ui->lineEdit_RFModeHang->setText(nuevodmr);
//    ui->lineEdit_RFModeHang->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");


    QString nuevodstar = "0";
    QFile file1(modo);
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file1.errorString());
        return;
    }
    QStringList lineas1;
    QTextStream in1(&file1);
    QString linea1;
    bool DStar = false;
    bool dstarenable = false;
    while (!in1.atEnd()) {
        linea1 = in1.readLine();
        // Verifica si se cambia de sección
        if (linea1.trimmed().startsWith('[')) {
            if (DStar && !dstarenable) {
                lineas1 << "Enable=" + nuevodstar;
                dstarenable = true;
            }
            DStar = (linea1.trimmed() == "[D-Star]");
        }
        if (DStar && linea1.trimmed().startsWith("Enable=")) {
            lineas1 << "Enable=" + nuevodstar;
            dstarenable = true;
        } else {
            lineas1 << linea1;
        }
    }
    file1.close();
    if (!file1.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file1.errorString());
        return;
    }
    QTextStream out1(&file1);
    for (const QString &l : lineas1) {
        out1 << l << "\n";
    }
    file1.close();

    ui->radioButton_DMR->setChecked(true);
}

void MainWindow::on_comboBox_Display_currentIndexChanged(int /*index*/)
{
    QFile file1(modo);
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo: " + file1.errorString());
        return;
    }
    QTextStream in1(&file1);
    QString line1;
    int lineNumber = 0;
    int numero_linea = -1;  // Guardará la línea de "Display=", -1 si no se encuentra
    bool inGeneral = false;

    while (!in1.atEnd()) {
        line1 = in1.readLine();
        lineNumber++;
        if (line1.trimmed() == "[General]") {
            inGeneral = true;
        } else if (line1.trimmed().startsWith('[') && inGeneral) {
            // Salimos de la sección [General]
            inGeneral = false;
        }
        if (inGeneral && line1.trimmed().startsWith("Display=")) {
            numero_linea = lineNumber;
            break;  // Ya lo encontramos, no hace falta seguir
        }
    }
    file1.close();

    //extrae número de item del comboBo
    QString sistema;
    if (ui->comboBox_Display->currentIndex() == 1) {
        QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
        QString sed = "sed -i '" + numLineaStr + "c Display=Nextion' ";
        QString Display = sed + modo;
        ui->lineEdit_puente->setText(Display);
        system(ui->lineEdit_puente->text().toStdString().c_str());
    }
    if (ui->comboBox_Display->currentIndex() == 2) {
        QString numLineaStr = QString::number(numero_linea);  // convertir int a QString
        QString sed = "sed -i '" + numLineaStr + "c Display=OLED' ";
        QString Display = sed + modo;
        ui->lineEdit_puente->setText(Display);
        system(ui->lineEdit_puente->text().toStdString().c_str());
    }

    // Presenta el fichero MMDVMhost
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr, "General", file.errorString());
        return;
    }
    QTextStream in(&file);
    QString line;
    bool inGeneralSection = false;

    //Callsign
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.startsWith('[')) {
            if (line == "[General]") {
                inGeneralSection = true;
            } else {
                inGeneralSection = false;
            }
        }
        if (inGeneralSection && line.startsWith("Display=")) {
            QString display = line.section('=', 1);  // Extrae el valor después del '='
            ui->lineEdit_TipoDisplay->setText(display);
            ui->lineEdit_Display->setText(display);
            break;  // Ya lo encontramos, salimos del bucle
        }
    }
}

void MainWindow::on_lineEdit_TipoDisplay_editingFinished()
{
    QString nuevoDisplay = ui->lineEdit_TipoDisplay->text();
    QFile file(modo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para lectura: " + file.errorString());
        return;
    }
    QStringList lineas;
    QTextStream in(&file);
    QString linea;
    bool enSeccionGeneral = false;
    bool callsignActualizado = false;
    while (!in.atEnd()) {
        linea = in.readLine();
        // Verifica si se cambia de sección
        if (linea.trimmed().startsWith('[')) {
            if (enSeccionGeneral && !callsignActualizado) {
                lineas << "Display=" + nuevoDisplay;
                callsignActualizado = true;
            }
            enSeccionGeneral = (linea.trimmed() == "[General]");
        }
        // Si estamos dentro de [General] y la línea contiene Callsign=
        if (enSeccionGeneral && linea.trimmed().startsWith("Display=")) {
            lineas << "Display=" + nuevoDisplay;
            callsignActualizado = true;
        } else {
            lineas << linea;
        }
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo para escritura: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    for (const QString &l : lineas) {
        out << l << "\n";
    }
    file.close();
    ui->lineEdit_Display->setText(nuevoDisplay);
    ui->lineEdit_TipoDisplay->setText(nuevoDisplay);
    ui->lineEdit_TipoDisplay->setStyleSheet("border:1px solid #ccc;background:#272727;font-weight: bold;font-size:15px;border-radius:3px;color:#fff;padding:2px;");

}

void MainWindow::on_pushButton_2_clicked()
{
    system("cp /home/pi/MMDVMHost/MMDVMPLUS.ini_M1 /home/pi/MMDVMHost/MMDVMPLUS.ini &");
    close();
}
