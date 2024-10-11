#ifndef LISTENER_H
#define LISTENER_H

#include <QMainWindow>

class QTextEdit;
class QToolBar;
class QStatusBar;
class QAction;
class QLabel;
class QUdpSocket;


class Listener : public QMainWindow
{

    Q_OBJECT

    QTextEdit *textEdit;

    QAction *action_StartServer;
    QAction *action_StopServer;

    QUdpSocket *serverSockect;

    QLabel *serverStatusLabel;

    void setUp();

public:

    explicit Listener(QWidget *parent = NULL);
    ~Listener();

private slots:

    void startServer();
    void readyToReadDatagrams();
    void stopServer();

};

#endif // LISTENER_H
