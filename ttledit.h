#ifndef TTLEDIT_H
#define TTLEDIT_H

#include <QWidget>

#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>

#include <QGridLayout>

class TTLEdit : public QWidget
{
    Q_OBJECT

private:
    QGridLayout *main_layout;

    QPushButton *btn_current_ttl;
    QPushButton *btn_set_ttl;
    QPushButton *btn_restore_ttl;

    QLineEdit *num_ttl;

    QTextEdit *log_ttl;

public:
    TTLEdit(QWidget *parent = nullptr);
    ~TTLEdit();
};
#endif // TTLEDIT_H
