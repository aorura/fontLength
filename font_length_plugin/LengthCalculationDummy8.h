#ifndef LENGTHCALCULATIONDUMMY8_H
#define LENGTHCALCULATIONDUMMY8_H

#include <QObject>

#include "../font_length_app/LengthCalculationInterface.h"

class LengthCalculationDummy8 : public QObject, public LengthCalculationInterface
{
    Q_OBJECT
    Q_INTERFACES(LengthCalculationInterface)

public:
    /** 
     * \name Attribute: 
     */ 
    //@{

    // The name of the length calculation
    virtual QString name() const;

    // An unique identifier for the length calculation.
    virtual const QUuid &uniqueId() const;

    // A detailed description.
    virtual QString description() const;

    // Version.
    virtual QString version() const;
    // Author.
    virtual QString author() const;
    // Date.
    virtual QString date() const;

    // Font Type.
    virtual FontTypeE fontType() const;
        
    //@}


    /** 
     * \name directory: 
     */ 
    //@{

    /**
     * Read files from the file directory.
     */
    virtual const QStringList fetchFontFiles() const;

    //@}


    /** 
     * \name Fonts: 
     */ 
    //@{
    
    /**
     * Can the font \a setFontName be resolved?.
     * The parameter \a strFontName If it is a
     * Font name, not a filename.
     */
    virtual bool canResolveFont( const QString &strFontName ) const;
    
    // A list of all available fonts.
    virtual const QStringList availableFonts() const;

    /// A list of all available fonts in strPath directory.
    virtual const QStringList availableFonts( const QString &strPath ) const;

    /**
     * Can the characters in the font str chr Fontname be resolved ?.
     * If bstore the parameter is = true, an unresolved characters
     * are stored in an error list.
     */
    virtual bool canResolveChar( const QChar &c, const QString &strFontName, bool bStore );

    //@}


    /** 
     * \name width calculation: 
     */ 
    //@{

    /**
     * Perform width calculation for the text strText.
     * To calculate the length of font is used, the
     * the Attribute strFontName, iFontSize, bBoldFont
     * and bItalicFont has.
     * 
     * return It returns the calculated width in pixels.
     * If an error occurs -1 is returned.
     *
     * The ResultCode parameter tells you, ob
     * whether the invoice was properly executed or a specific error occurred.
     *
     * a CalculationResultE.
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
	return tr( "0.1" );
}

inline QString LengthCalculationDummy8::author() const
{
	return tr( "Chalse Park" );
}

inline QString LengthCalculationDummy8::date() const
{
	return tr( "December 22, 2015" );
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
