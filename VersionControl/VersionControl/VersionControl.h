#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VersionControl.h"

class VersionControl : public QMainWindow
{
	Q_OBJECT

public:
	VersionControl(QWidget *parent = Q_NULLPTR);

private:
	Ui::VersionControlClass ui;
};
