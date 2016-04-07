#ifndef PERSISTENTCONNECTION_H
#define PERSISTENTCONNECTION_H

#include <QDialog>
#include <QTimer>
#include <QList>

#include "packet.h"
#include "tcpthread.h"

namespace Ui {
class PersistentConnection;
}

class PersistentConnection : public QDialog
{
    Q_OBJECT

public:
    explicit PersistentConnection(QWidget *parent = 0);
    ~PersistentConnection();
    Packet sendPacket;
    TCPThread *thread;

    void init();

signals:
    void persistentPacketSend(Packet sendpacket);
    void closeConnection();


public slots:
    void packetToSend(Packet sendpacket);
    void refreshTimerTimeout();
    void aboutToClose();
    void statusReceiver(QString message);

    void packetSentSlot(Packet pkt);
private slots:
    void on_buttonBox_rejected();

    void on_asciiSendButton_clicked();

    void on_packetComboBox_currentIndexChanged(const QString &arg1);

    void on_searchEdit_textEdited(const QString &arg1);

    void on_clearButton_clicked();

    void on_asciiCheck_clicked(bool checked);

    void on_rawCheck_clicked(bool checked);

    void on_LoadButton_clicked();

private:
    Ui::PersistentConnection *ui;
    QTimer refreshTimer;
    QList<Packet> trafficList;
    QDateTime startTime;
    bool wasConnected;
    bool stopTimer;
    bool useraw;

    void loadComboBox();
    void loadTrafficView();
};

#endif // PERSISTENTCONNECTION_H
