#include <QtGui>

#include "FontDialog.h"
#include "LengthCalculationInterface.h"

FontDialog::FontDialog(QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	loadPlugins();

	connect(pushButton, SIGNAL(clicked()), this, SLOT(showFontWidth()));

	comboBox->addItem("Skoda");

	QStringList fonts = interfaces[0]->availableFonts();

	foreach (QString fontName, fonts) {
		comboBox_2->addItem(fontName);
	}
}

void FontDialog::showFontWidth()
{
	// Only use an fontType and text to calculate the width of an font.
	QString fontType = comboBox_2->currentText();
	QString text = plainTextEdit->toPlainText();
	unsigned int result;	// not used.
	LengthCalculationInterface::CalculateFontShowMessagesE e;	// not used.

	int totalWidth = interfaces[0]->calculateWidth(text, fontType, 1,false,false,e,&result);
	PixcelOfFont->setText(QString::number(totalWidth));
	qDebug() << "totalWidth: " << totalWidth << endl;
}

void FontDialog::loadPlugins()
{
	QDir pluginsDir =  directoryOf("plugins");
	foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
		QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
		if (LengthCalculationInterface *interface = qobject_cast<LengthCalculationInterface *> (loader.instance())) {
			interfaces.append(interface);
		}
	}
}


QDir FontDialog::directoryOf(const QString &subdir)
{
    QDir dir(QApplication::applicationDirPath());

#if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug"
            || dir.dirName().toLower() == "release")
        dir.cdUp();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS") {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
    dir.cd(subdir);
    return dir;
}

