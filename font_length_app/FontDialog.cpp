#include <QtGui>

#include "FontDialog.h"
#include "LengthCalculationInterface.h"

FontDialog::FontDialog(QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	loadPlugins();

	//connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));

	lineEdit->setText(interfaces[0]->author());
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

