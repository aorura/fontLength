#ifndef FINDDIALOG_H
#define SORTDIALOG_H

#include <QDialog>

#include "ui_FontLengthApp.h"

class QDir;

class LengthCalculationInterface;

class FontDialog : public QDialog, public Ui::FontDialog
{
	Q_OBJECT

public:
	FontDialog(QWidget *parent  = 0);

private:
	static QDir directoryOf(const QString &subdir);
	void loadPlugins();

	QList<LengthCalculationInterface *> interfaces;
};

#endif
