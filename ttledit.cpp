#include "ttledit.h"

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

    main_layout->addWidget(btn_current_ttl, 1, 0, 1, 2);
    main_layout->addWidget(num_ttl, 2, 0);
    main_layout->addWidget(btn_set_ttl, 2, 1);
    main_layout->addWidget(log_ttl, 3, 0, 3, 2);
    main_layout->addWidget(btn_restore_ttl, 4, 0, 4, 2);

    setLayout(main_layout);
}

TTLEdit::~TTLEdit()
{
    delete btn_restore_ttl;
    delete btn_set_ttl;
    delete btn_current_ttl;

    delete log_ttl;

    delete num_ttl;

    delete main_layout;
}

