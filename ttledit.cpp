#include "ttledit.h"

#include <QSettings>
#include <QFile>

TTLEdit::TTLEdit(QWidget *parent)
    : QWidget(parent)
{
    main_layout = new QGridLayout;

    btn_current_ttl = new QPushButton(tr("Current TTL"));
    btn_set_ttl = new QPushButton(tr("Set TTL"));
    btn_restore_ttl = new QPushButton(tr("Restore TTL"));

    num_ttl = new QLineEdit;

    log_ttl = new QTextEdit;
    log_ttl->setReadOnly(true);

    proc_ttl = new QProcess;

    main_layout->addWidget(btn_current_ttl, 1, 0, 1, 2);
    main_layout->addWidget(num_ttl, 2, 0);
    main_layout->addWidget(btn_set_ttl, 2, 1);
    main_layout->addWidget(log_ttl, 3, 0, 3, 2);
    main_layout->addWidget(btn_restore_ttl, 4, 0, 4, 2);

    setLayout(main_layout);

    QFile file_system_ttl("/proc/sys/net/ipv4/ip_default_ttl");
    file_system_ttl.open(QIODevice::ReadOnly);
    QString tmpData = file_system_ttl.readLine();
    int i_stock_ttl = tmpData.toInt();
    file_system_ttl.close();

    QFile file_ttl_settings("/sdcard/settings.ini");
    file_ttl_settings.open(QIODevice::WriteOnly);
    if (!file_ttl_settings.isOpen())
    {
        log_ttl->append("Error!");
        log_ttl->append(file_ttl_settings.errorString());
    }
    file_ttl_settings.close();

    QSettings settings_ttl("/sdcard/settings.ini", QSettings::IniFormat);
    int i_get_stock_ttl = settings_ttl.value("General/Stock").toInt();
    if (i_get_stock_ttl == 0)
    {
        settings_ttl.setValue("General/Stock", i_stock_ttl);
    }
}

TTLEdit::~TTLEdit()
{
    delete btn_restore_ttl;
    delete btn_set_ttl;
    delete btn_current_ttl;

    delete log_ttl;

    delete num_ttl;

    delete main_layout;

    delete proc_ttl;
}

void TTLEdit::getTTL()
{
    QFile f_current_ttl("/proc/sys/net/ipv4/ip_default_ttl");
    f_current_ttl.open(QIODevice::ReadOnly);
    QString tmpData = f_current_ttl.readLine();
    int i_current_ttl = tmpData.toInt();
    f_current_ttl.close();

    QString str = "Current TTL: " + QString::number(i_current_ttl);
    log_ttl->append(str);
}

void TTLEdit::setTTL()
{
    int i_new_ttl = num_ttl->text().toInt();
    if (i_new_ttl > 255 || i_new_ttl <= 0)
    {
        log_ttl->append("Error! Min TTL = 1, Max TTL = 255");
    }
    else
    {
        QSettings sett("/sdcard/settings.ini", QSettings::IniFormat);
        sett.setValue("General/New", i_new_ttl);

        proc_ttl->setProcessChannelMode(QProcess::SeparateChannels);
        proc_ttl->start("su", QStringList() << "-c" << "echo" << QString::number(i_new_ttl) << ">>"
                                            << "/proc/sys/net/ipv4/ip_default_ttl");

        if (!proc_ttl->waitForFinished())
        {
            log_ttl->append(proc_ttl->errorString());
        }
        else
        {
            QString str = "New TTL: " + QString::number(i_new_ttl);
            log_ttl->append(str);
            log_ttl->append(proc_ttl->readAll());
            log_ttl->append("Ok!");
        }
    }
}

void TTLEdit::resetTTL()
{
    QSettings sett("/sdcard/settings.ini", QSettings::IniFormat);
    int i_stock_ttl = sett.value("General/Stock", 64).toInt();

    proc_ttl->setProcessChannelMode(QProcess::SeparateChannels);
    proc_ttl->start("su", QStringList() << "-c" << "echo" << QString::number(i_stock_ttl) << ">>"
                                        << "/proc/sys/net/ipv4/ip_defaul_ttl");

    if (!proc_ttl->waitForFinished())
    {
        log_ttl->append(proc_ttl->errorString());
    }
    else
    {
        QString str = "Current TTL: " + QString::number(i_stock_ttl);
        log_ttl->append("Stock TTL has been restored.");
        log_ttl->append(str);
        log_ttl->append(proc_ttl->readAll());
    }
}
