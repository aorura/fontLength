#include "LengthCalculationDummy8.h"

#include <QtPlugin>
#include <QStringList>

LengthCalculationDummy8::LengthCalculationDummy8()
{
}

const QStringList LengthCalculationDummy8::fetchFontFiles() const
{
	return QStringList();
}

const QStringList LengthCalculationDummy8::availableFonts() const
{
	return QStringList();
}

const QStringList LengthCalculationDummy8::availableFonts(QString const & path) const
{
    Q_UNUSED(path);

	return QStringList();
}

int LengthCalculationDummy8::calculateWidth(QString const & text, QString const & fontName, int const fontSize, 
        bool const bold, bool const italic, CalculateFontShowMessagesE const messages, unsigned int * const resultCode)
{
    Q_UNUSED(fontName); Q_UNUSED(fontSize); Q_UNUSED(bold); Q_UNUSED(italic); Q_UNUSED(messages);

	int width;
	int maxWidth(0);

	QStringList l(text.split('\n', QString::SkipEmptyParts));
    for (QStringList::const_iterator pos = l.constBegin(), end = l.constEnd(); pos != end; ++pos)
    {
        // every char is 8 pixels wide in this sample
		width = pos->length() * 8;
		if (width > maxWidth)
			maxWidth = width;
	}

	if (resultCode)
		*resultCode = CalculationOk;

	return maxWidth;
}

Q_EXPORT_PLUGIN2( LengthCalculationDummy8, LengthCalculationDummy8 )
