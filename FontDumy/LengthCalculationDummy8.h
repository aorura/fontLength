#ifndef LENGTHCALCULATIONDUMMY8_H
#define LENGTHCALCULATIONDUMMY8_H

#include "LengthCalculationInterface.h"

#include <QObject>

class LengthCalculationDummy8 : public QObject, public LengthCalculationInterface
{
    Q_OBJECT
    Q_INTERFACES(LengthCalculationInterface)

public:

    /// Konstruktor.
    LengthCalculationDummy8();

    /** 
     * \name Attribute: 
     */ 
    //@{

    /// Der Name der Längenberechnung.
    virtual QString name() const;

    /// Eine eindeutige Id der Längenberechnung.
    virtual const QUuid &uniqueId() const;

    /// Eine (ausführliche) Beschreibung.
    virtual QString description() const;

    /// Version.
    virtual QString version() const;
    /// Autor.
    virtual QString author() const;
    /// Datum.
    virtual QString date() const;

    /// Schriftart-Typ.
    virtual FontTypeE fontType() const;
        
    //@}


    /** 
     * \name Verzeichnis: 
     */ 
    //@{

    /**
     * Dateien aus dem Datenverzeichnis auslesen.		 
     */
    virtual const QStringList fetchFontFiles() const;

    //@}


    /** 
     * \name Schriftarten: 
     */ 
    //@{
    
    /**
     * Kann die Schriftart \a strFontName aufgelöst werden?.
     * Bei dem Parameter \a strFontName handelt es sich um eine
     * Schriftartbezeichnung und nicht um einen Dateinamen.
     */
    virtual bool canResolveFont( const QString &strFontName ) const;
    
    /// Eine Liste mit allen zur Verfügung stehenden Schriftarten.
    virtual const QStringList availableFonts() const;

    /// Eine Liste mit allen zur Verfügung stehenden Schriftarten im Verzeichnis \a strPath.
    virtual const QStringList availableFonts( const QString &strPath ) const;

    /**
     * Kann das Zeichen \a chr in der Schriftart \a strFontName aufgelöst werden?.
     * Wenn der Parameter \a bStore = true ist, kann ein nicht aufgelöstes Zeichen
     * in einer Fehlerliste gespeichert werden.
     */
    virtual bool canResolveChar( const QChar &c, const QString &strFontName, bool bStore );

    //@}


    /** 
     * \name Breitenberechnung: 
     */ 
    //@{

    /**
     * Breitenberechnung für den Text \a strText durchführen.
     * Zur Längenberechnung wird die Schriftart verwendet, die
     * die Attribute \a strFontName, \a iFontSize, \a bBoldFont
     * und \a bItalicFont besitzt.
     * 
     * \return Es wird die berechnete Breite in Pixeln zurückgegeben.
     * Im Fehlerfall wird -1 zurückgegeben.
     *
     * Der Parameter \a iResultCode gibt Auskunft darüber, ob
     * die Berechnung korrekt ausgeführt werden konnte oder
     * ein spezieller Fehler auftrat.
     *
     * \sa CalculationResultE.
     */
    virtual int calculateWidth( const QString &strText,
                                const QString &strFontName,
                                int            iFontSize,
                                bool           bBoldFont,
                                bool           bItalicFont,
                                const CalculateFontShowMessagesE eMessages,
                                unsigned int  *iResultCode = 0 );

    //@}
};


/*=================================================================*\
 *  Inlines                                                        *
\*-----------------------------------------------------------------*/
inline QString LengthCalculationDummy8::name() const
{
#if defined(NDEBUG)
	return tr( "Dummy8" );
#else
	return tr( "Dummy8-DBG" );
#endif
}

inline const QUuid &LengthCalculationDummy8::uniqueId() const
{
	static QUuid *uuid = 0;
	if ( ! uuid ) {
		uuid = new QUuid( "{d7eeb149-ba5a-46ef-a9cc-4bb09e7d6eef}" );
	}
	return *uuid;
}


inline QString LengthCalculationDummy8::description() const
{
	return tr( "A dummy length-calculation is executed, which assumes 8 pixels for every character." );
}

inline QString LengthCalculationDummy8::version() const
{
	return tr( "3.0" );
}

inline QString LengthCalculationDummy8::author() const
{
	return tr( "Kai Schrader" );
}

inline QString LengthCalculationDummy8::date() const
{
	return tr( "August 04, 2009" );
}

inline LengthCalculationInterface::FontTypeE LengthCalculationDummy8::fontType() const
{
	return FontTypeVector;
}

inline bool LengthCalculationDummy8::canResolveFont( const QString &/* strFontName */ ) const
{
	return true;
}

inline bool LengthCalculationDummy8::canResolveChar( const QChar &/*c*/, const QString &/*strFontName*/, bool /*bStore*/ )
{
	return true;
}


#endif // LENGTHCALCULATIONDUMMY8_H
