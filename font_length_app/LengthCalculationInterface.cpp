#include "LengthCalculationInterface.h"
//#include "QxLog.h"

#include <QDir>
#include <QFileDialog>
#include <QApplication>


QUuid LengthCalculationInterface::m_uuid = QUuid(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
QUuid LengthCalculationInterface::m_uuidBitmap = QUuid(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2);


LengthCalculationInterface::LengthCalculationInterface() : 
	_pluginLoader(NULL)
{
}

LengthCalculationInterface::~LengthCalculationInterface()
{
}

void LengthCalculationInterface::initResources()
{
}

void LengthCalculationInterface::freeResources()
{
}

QString LengthCalculationInterface::description() const
{
	return "";
}

QString LengthCalculationInterface::version() const
{
	return "";
}

QString LengthCalculationInterface::author() const
{
	return "";
}

QString LengthCalculationInterface::date() const
{
	return "";
}

QString LengthCalculationInterface::fontTypeName(bool bPlural) const
{
	return fontTypeName(fontType(), bPlural);
}

const QString LengthCalculationInterface::fontTypeName(FontTypeE fontType, bool bPlural)
{
	switch(fontType)
	{
	default:
	case FontTypeVector:
		if(bPlural)
		{
			return qApp->translate("LengthCalculationInterface", "Vector fonts");
		}
		else
		{
			return qApp->translate("LengthCalculationInterface", "Vector font");
		}

	case FontTypeBitmap:
		if(bPlural)
		{
			return qApp->translate("LengthCalculationInterface", "Bitmap fonts");
		}
		else
		{
			return qApp->translate("LengthCalculationInterface", "Bitmap font");
		}
	}
}

QUuid const & LengthCalculationInterface::standardId(FontTypeE fontType)
{
	if(fontType == FontTypeVector)
		return m_uuid;
	else
		return m_uuidBitmap;
}

bool LengthCalculationInterface::isStandard() const
{
	return uniqueId() == standardId(fontType());
}

void LengthCalculationInterface::setFontDirectoryPath(const QString& strFontDirectoryPath)
{
	m_fontDirectoryPath = strFontDirectoryPath;
	initResources();
}

const QString& LengthCalculationInterface::fontDirectoryPath() const
{
	return m_fontDirectoryPath;
}

bool LengthCalculationInterface::hasValidFontDirectoryPath(QString * strError) const
{
	// INFO: Diese Methode entspricht der Methode QxFile::checkPath

	// Diese Ueberpruefung wird immer ausgefuehrt!
	if(m_fontDirectoryPath.isEmpty())
	{
		if(strError)
		{
            //Qx::warn(QString("[LengthCalculationInterface::hasValidFontDirectoryPath] error: The directory for %1 is not set!").arg(fontTypeName()));
			*strError = qApp->translate("LengthCalculationInterface", "The directory for %1 is not set!")
						.arg(fontTypeName());
		}
		return false;
	}

	QFileInfo fiDir(m_fontDirectoryPath);

	//if ( ( checkFlags & CheckExists ) != 0 )
	if(! fiDir.exists())
	{
		if(strError)
        {
            /*Qx::warn(QString("[LengthCalculationInterface::hasValidFontDirectoryPath] error: The directory '%1' for %2 does not exist!")
                .arg(QDir::toNativeSeparators(m_fontDirectoryPath))
                .arg(fontTypeName()));*/
			*strError = qApp->translate("LengthCalculationInterface", "The directory '%1' for %2 does not exist!")
						.arg(QDir::toNativeSeparators(m_fontDirectoryPath))
						.arg(fontTypeName());
		}
		return false;
	}

	//if ( ( checkFlags & CheckIsDir ) != 0 )
	if(! fiDir.isDir())
	{
		if(strError)
        {
            /*Qx::warn(QString("[LengthCalculationInterface::hasValidFontDirectoryPath] error: The path '%1' for %2 is not a directory!")
                .arg(QDir::toNativeSeparators(m_fontDirectoryPath))
                .arg(fontTypeName()));*/
			*strError = qApp->translate("LengthCalculationInterface", "The path '%1' for %2 is not a directory!")
						.arg(QDir::toNativeSeparators(m_fontDirectoryPath))
						.arg(fontTypeName());
		}
		return false;
	}

	QDir dir(m_fontDirectoryPath);

	//if ( ( checkFlags & CheckReadable ) != 0 )
	if(! dir.isReadable())
	{
		if(strError)
        {
            /*Qx::warn(QString("[LengthCalculationInterface::hasValidFontDirectoryPath] error: The directory '%1' for %2 is not readable!")
                .arg(QDir::toNativeSeparators(m_fontDirectoryPath))
                .arg(fontTypeName()));*/
			*strError = qApp->translate("LengthCalculationInterface",
										"The directory '%1' for %2 is not readable!")
						.arg(QDir::toNativeSeparators(m_fontDirectoryPath))
						.arg(fontTypeName());
		}
		return false;
	}

	return true;
}

QList<ushort> LengthCalculationInterface::unresolvedChars(const QString& /*strFontName*/) const
{
	return QList<ushort>();
}

QStringList LengthCalculationInterface::kerningErrors(const QString& /*strFontName*/) const
{
	return QStringList();
}

bool LengthCalculationInterface::canAddFont() const
{
	return false;
}

bool LengthCalculationInterface::canReplaceFont() const
{
	return false;
}

bool LengthCalculationInterface::canRefreshFont() const
{
	return false;
}

bool LengthCalculationInterface::addFont(const QString& /*strFontName*/, QString* /*strError*/)
{
	return false;
}

bool LengthCalculationInterface::replaceFont(const QString& /*strFontName*/, QString* /*strError*/)
{
	return false;
}

bool LengthCalculationInterface::refreshFont(const QString& /*strFontName*/, QString* /*strError*/)
{
	return false;
}

void LengthCalculationInterface::setPluginLoader(QPluginLoader * pluginLoader)
{
	_pluginLoader = pluginLoader;
}

QPluginLoader * LengthCalculationInterface::pluginLoader() const
{
	return _pluginLoader;
}

bool LengthCalculationInterface::canUnloadPlugin() const
{
	return _pluginLoader;
}

QString LengthCalculationInterface::errorMessage(ErrorE error, QStringList param)
{
	// EXPAND: Beim Hinzufuegen neuer Fehler-Ids diese Methode erweitern:
	switch(error)
	{
	case ErrorSelectedFileExists:
		_completeParamList(&param, 1);
		return qApp->translate("LengthCalculationInterface", "The selected file '%1' already exists in project!")
			   .arg(param.at(0));

	case ErrorFileCouldNotCopy:
		_completeParamList(&param, 1);
		return qApp->translate("LengthCalculationInterface", "The file '%1' couldn't copy!")
			   .arg(param.at(0));

	case ErrorFileDoesNotIncludeFont:
		_completeParamList(&param, 2);
		return qApp->translate("LengthCalculationInterface", "The selected file '%1' doesn't include the font '%2'!")
			   .arg(param.at(0))
			   .arg(param.at(1));

	case ErrorSelectedDirectoryEmpty:
		_completeParamList(&param, 1);
		return qApp->translate("LengthCalculationInterface", "The selected directory '%1' is empty!")
			   .arg(param.at(0));

	case ErrorDirectoryMismatchFont:
		_completeParamList(&param, 2);
		return qApp->translate("LengthCalculationInterface", "The selected directory '%1' doesn't match the font name '%2'!")
			   .arg(param.at(0))
			   .arg(param.at(1));

	case ErrorSelectedDirectoryExists:
		_completeParamList(&param, 1);
		return qApp->translate("LengthCalculationInterface", "The selected directory '%1' already exists in project!")
			   .arg(param.at(0));

	case ErrorDirectoryCouldNotRenamed:
		_completeParamList(&param, 1);
		return qApp->translate("LengthCalculationInterface", "The directory '%1' couldn't be renamed!")
			   .arg(param.at(0));

	case ErrorDirectoryNotExists:
		_completeParamList(&param, 2);
		return qApp->translate("LengthCalculationInterface", "The directory '%1' of font '%2' does not exist!")
			   .arg(param.at(0))
			   .arg(param.at(1));

	case ErrorDirectoryIsEmpty:
		_completeParamList(&param, 2);
		return qApp->translate("LengthCalculationInterface", "The directory '%1' of font '%2' is empty!")
			   .arg(param.at(0))
			   .arg(param.at(1));

	case ErrorWrongKerningValue:
		_completeParamList(&param, 2);
		return qApp->translate("LengthCalculationInterface", "Entry '%1' in file '%2' has wrong format! Kerning value could not be calculated.")
			   .arg(param.at(0))
			   .arg(param.at(1));

	default:
		return qApp->translate("LengthCalculationInterface", "length calculation error: Invalid case");

	}
}

const QStringList LengthCalculationInterface::_fetchDataFiles(QStringList const * lNameFilters, 
	QString const & strPath, bool addDirectoryPath) const
{
	// entspricht Qx::fetchDataFiles
	QString path(strPath);

	if (strPath == QString::null)
		path = m_fontDirectoryPath;

	QStringList lFileAbs;
	QString strError;

	if (!hasValidFontDirectoryPath(&strError))
	{
		if (!strError.isEmpty())
			//Qx::warn( strError );
		return lFileAbs;
	}

	QDir dir(path);
	if (!dir.exists())
		return lFileAbs;

	QStringList lFileRel;
	if (lNameFilters)
		lFileRel = dir.entryList(*lNameFilters, QDir::Files | QDir::Readable);
	else
		lFileRel = dir.entryList(QDir::Files | QDir::Readable);

	if(addDirectoryPath)
	{
		for(int i = 0; i < lFileRel.size(); ++i)
			lFileAbs.append(dir.absoluteFilePath(lFileRel[i]));

		return lFileAbs;
	}
	else
	{
		return lFileRel;
	}
}

const QString LengthCalculationInterface::_selectExistingFile(const QString& strFontName, const QStringList* lNameFilter) const
{
	// Datei mit der Schriftart ermitteln
	QString strFile = QFileDialog::getOpenFileName(0,
					  qApp->translate("LengthCalculationInterface", "Select file of font '%1'").arg(strFontName),
					  m_fontDirectoryPath,
					  qApp->translate("LengthCalculationInterface", "%1 (%2)").arg(fontTypeName(false))
					  .arg(lNameFilter->join(" ")));

	if(strFile.isEmpty())
	{
		//Qx::status( qApp->translate( "LengthCalculationInterface", "Selecting file aborted by user" ) );
		return strFile;
	}

	return QDir::toNativeSeparators(strFile);
}

const QString LengthCalculationInterface::_selectExistingDir(const QString& strFontName) const
{
	// Verzeichnis mit der Schriftart ermitteln
	QString strDir(QFileDialog::getExistingDirectory(0,
				   qApp->translate("LengthCalculationInterface", "Select directory of font '%1'")
				   .arg(strFontName),
				   m_fontDirectoryPath));

	if(strDir.isEmpty())
		return QString::null;

	return QDir::toNativeSeparators(strDir);
}

void LengthCalculationInterface::_completeParamList(QStringList* param, int paramCount)
{
	if(paramCount > 0)
	{
		if(param->count() < paramCount)
		{
			for(int i = param->count(); i < paramCount; i++)
			{
				param->append(QString("%%1").arg(i + 1));
			}
		}
	}
}