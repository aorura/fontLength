#ifndef LENGTHCALCULATIONINTERFACE_H
#define LENGTHCALCULATIONINTERFACE_H

/**
 * \page calc_plugins Längenberechnung
 * Regeln, die für die Implementierung eines Plugins für
 * die Längenberechnung berücksichtigt werden müssen.
 *
 * Qt spezifische Regeln. Diese sind z.B. in der
 * Klassendokumentation zu QPluginLoader oder in der
 * Qt-Dokumentation plugins-howto.html nachzulesen:
 *
 * - QPluginLoader checks that a plugin is linked against
 *   the same version of Qt as the application.
 * - Plugins linked with a Qt library that has a higher version
 *   number will not be loaded by a library with a lower version number.
 *   Example: Qt 4.3.0 will not load a plugin built with Qt 4.3.1.
 * - Plugins linked with a Qt library that has a lower major version
 *   number will not be loaded by a library with a higher major version number.
 *   Example: Qt 4.3.1 will not load a plugin built with Qt 3.3.1.
 *   Example: Qt 4.3.1 will load plugins built with Qt 4.3.0 and Qt 4.2.3.
 * - The Qt library and all plugins are built using a build key.
 *   The build key in the Qt library is examined against the build key in the
 *   plugin, and if they match, the plugin is loaded.
 *   If the build keys do not match, then the Qt library refuses to load the plugin.
 *   The build key contains the following information:
 *		- Architecture, operating system and compiler.
 *		- Configuration of the Qt library. The configuration is a list of
 *        the missing features that affect the available API in the library.
 *		- Optionally, an extra string may be specified on the configure
 *        script command line.
 *
 * Es kann erforderlich sein, dass das Plugin zur Längenberechnung weitere
 * Bibliotheken (DLL's) laden muss. Für diese weiteren DLL's gelten ebenfalls
 * Regeln, damit sie kompatibel zum Plugin und zur Applikation (HMI-Linguist)
 * sind:
 *
 * - Die DLL muss mit der Entwicklungsumgebung Visual Studio 2008 von
 *   Microsoft erstellt werden.
 * - \attention Die Funktionen der "Microsoft C Runtime Library (msvcrXX.dll)" dürfen nicht
 *   in die DLL eingebettet werden. Das kann durch das Setzen des Flags
 *   "Multithreaded Dll (/MD)" (nicht /MT) bei der Codegenerierung erfolgen.
 *   In VisualStudio ist diese Einstellung unter
 *   Konfigurationseigenschaften>>C/C++>>Codegenerierung>>Laufzeitbibliothek
 *   zu finden.
 * - In dem Artikel
 *   http://blog.m-ri.de/?s=statisch+gegen+die+CRT+linken&submit=Suchen
 *   sind einige allgemeine Hinweise für die DLL-Erstellung aufgeführt.
 * - Sowohl für das Plugin als auch für die weiteren DLL's ist darauf zu achten,
 *   dass alle Abhängigkeiten aufgelöst werden können. Das kann z.B. mit dem
 *   Tool Dependency Walker (http://www.dependencywalker.com/) geprüft werden.
 *   Dateien, die zusätzlich benötigt werden, sollten in das gleiche Verzeichnis
 *   gelegt werden wie das Plugin.
 * - Generell dürfen keine absoluten Pfadnamen (z.B. für Fontdateien) benutzt werden.
 * - Folgende Rückgabewerte werden vom Hauptprogamm erwartet und sollten idealerweise
 *   auch unterstützt werden:
 *		CalculationOk,                 // Ok.
 *		CalculationFontError,          // Schriftart-Fehler.
 *		CalculationFontParameterError, // Mind. ein Schriftart-Parameter ist fehlerhaft.
 *		CalculationUnresolvedCharError,// Mind. ein Zeichen kann nicht aufgelöst werden.
 * - HMI-Linguist arbeitet mit Fontnamen und nicht mit Fontdateinamen. Allgemein ist es schwer
 *   vom Fontnamen auf den Dateinamen zu schließen.
 * - Die DLL muss im Release-Modus erstellt werden (nicht Debug)
 * - Die DLL sollte keine weiteren Dateien anlegen bzw. geöffnet halten (z.B. Logdateien).
 */


// Qt
#include <QStringList>
#include <QUuid>
#include <QFont>

class QPluginLoader;


/**
	\brief	Schnittstelle für die Längenberechnung.
			Die Längenberechnung ist über Plugins erweiterbar, bzw. austauschbar. Die hier beschriebene Schnittstelle muss
			von allen Plugins implementiert werden.
*/
class LengthCalculationInterface
{
public:
	/**
		\brief	Aufzählung der Berechnungsergebnisse
	*/
	enum CalculationResultE
	{
		CalculationOk,                          /**< \brief Ok */
		CalculationFontError,                   /**< \brief Schriftart-Fehler */
		CalculationFontParameterError,          /**< \brief Mind. ein Schriftart-Parameter ist fehlerhaft */
		CalculationResolveRequiredLibraryError, /**< \brief Fehler beim Auflösen einer zusätzlichen Bibliothek */
		CalculationResolveFunctionError,        /**< \brief Fehler beim Auflösen einer benötigten Funktion */
		CalculationUnresolvedCharError,	        /**< \brief Mind. ein Zeichen kann nicht aufgelöst werden */
		CalculationUnknownError                 /**< \brief Es trat ein (unbekannter) Fehler auf */
	};

	/**
		\brief	Optionen für die Meldungsausgabe
	*/
	enum CalculateFontShowMessagesE
	{
		CalculateFontShowMessagesAll		= 0, /**< \brief Alle Meldungen ausgeben */
		CalculateFontShowMessagesNewError	= 1, /**< \brief Nur Meldungen ausgeben, die noch nicht aufgetreten sind, ohne Textbezug */
		CalculateFontShowMessagesNone		= 2 /**< \brief Keine Meldungen ausgeben */
	};

	/**
		\brief	Für welchen Schriftart-Typ ist die Längenberechnung?
	*/
	enum FontTypeE
	{
		FontTypeMin		= 0,
		FontTypeVector	= FontTypeMin,	/**< \brief Die Längenberechnung ist für Vector-Schriftarten */
		FontTypeBitmap,					/**< \brief Die Längenberechnung ist für Bitmap-Schriftarten */
		FontTypeMax
	};

	/**
		\brief	Mögliche Fehlercodes
		\attention	Beim Hinzufuegen neuer Fehler-Ids diese Methode errorMessage erweitern
	*/
	enum ErrorE
	{
		ErrorSelectedFileExists,		/**< \brief The selected file '%1' already exists in project! */
		ErrorFileCouldNotCopy,			/**< \brief The file '%1' couldn't copy! */
		ErrorFileDoesNotIncludeFont,	/**< \brief The file '%1' doesn't include the font '%2'! */
		ErrorSelectedDirectoryEmpty,	/**< \brief The selected directory '%1' is empty! */
		ErrorDirectoryMismatchFont,		/**< \brief The selected directory '%1' doesn't match the font name '%2'! */
		ErrorSelectedDirectoryExists,	/**< \brief The selected directory '%1' already exists in project! */
		ErrorDirectoryCouldNotRenamed,  /**< \brief The directory '%1' couldn't be renamed! */
		ErrorDirectoryNotExists,		/**< \brief The directory '%1' of font '%2' does not exist!" */
		ErrorDirectoryIsEmpty,			/**< \brief The directory '%1' of font '%2' is empty! */
		ErrorWrongKerningValue,			/**< \brief Entry '%1' in file '%2' has wrong format! Kerning value could not be calculated */
	};

	/**
		\brief	Konstruktor der Klasse LengthCalculationInterface
		\nsc
	*/
	LengthCalculationInterface();

	/**
		\brief	Destruktor der Klasse LengthCalculationInterface
		\nsd
	*/
	virtual ~LengthCalculationInterface();

	/**
		\brief	Initialisiert Resourcen
				Hier können z.B. weitere Bibliotheken oder Fonts geladen werden.
	*/
	virtual void initResources();

	/**
		\brief	Gibt belegte Resourcen frei
				Es können z.B. weitere Bibliotheken freigegeben werden.
	*/
	virtual void freeResources();


	/**
		\name Attribute:
	*/
	/**@{*/

	/**
		\brief	Gibt den Name der Längenberechnung zurück
				Frei wählbare Bezeichnung.
		\return	Name der Längenberechnung
	*/
	virtual QString name() const = 0;

	/**
		\brief	Gibt eine eindeutige Id der Längenberechnung zurück
				Jede Längenberechnung wird über ihre uniqueId() identifiziert.
		\return eindeutige Id der Längenberechnung
	*/
	virtual const QUuid& uniqueId() const = 0;

	/**
		\brief	Gibt die (ausführliche) Beschreibung der Längenberechnung zurück
		\return	Beschreibung der Längeberechnung
	*/
	virtual QString description() const;

	/**
		\brief	Gibt die aktuelle Version des Plugins zurück
		\return	Versionstext des Plugins
	*/
	virtual QString version() const;

	/**
		\brief	Gibt den Autor des Plugins zurück
		\return	Autor des Plugins
	*/
	virtual QString author() const;

	/**
		\brief	Gibt das Datum des Plugins zurück
		\return	Datum des Plugins
	*/
	virtual QString date() const;

	/**
		\brief	Gibt den Schriftart-Typ zurück
		\sa FontTypeE.
		\return	der Schriftart-Typ
	*/
	virtual FontTypeE fontType() const = 0;

	/**
		\brief	Gibt den Name des Schriftart-Typs zurück
		\param[in]	bPlural
		\return	Name des Schriftart-Typs
	*/
	QString fontTypeName(bool bPlural = true) const;

	/**
		\brief	Gibt den Name des Schriftart-Typs \a fontType zurück
		\param[in]	fontType	Typ dessen Name zurückgegeben werden soll
		\param[in]	bPlural
		\return	Name des Schriftart-Typs
	*/
	static const QString fontTypeName(LengthCalculationInterface::FontTypeE fontType, bool bPlural = true);

	/**
		\brief	Prüft, ob die Längenberechnung das Standardverfahren darstellt
		\retval true	Längenberechnung stellt das Standardverfahren dar
		\retval false	Längenberechnung stellt nicht das Standardverfahren dar
	*/
	bool isStandard() const;

	/**
		\brief	Gibt die Id zu dem Schriftart-Typ \a fontType zurück, die die Standard-Längenberechnung identifiziert
		\param[in]	fontType	Schriftart-Typ
		\return	Id, die die Standard-Längenberechnung identifiziert
	*/
	static const QUuid& standardId(LengthCalculationInterface::FontTypeE fontType);

	/**@}*/


	/**
	 * \name Schriftartverzeichnis:
	 */
	//@{

	/**
	 * Den Pfad für (zusätzliche) Schriftartdateien zuweisen.
	 * Der Pfad wird vom Programm HMI-Linguist aus gesetzt.
	 * In der Redakteursversion handelt es sich um ein frei wählbares
	 * Verzeichnis. Bei der Übersetzerversion des Programms ergibt
	 * sich der Pfad implizit durch die Programminstallation.
	 *
	 * \sa fontDirectoryPath().
	 */
	void setFontDirectoryPath(const QString& strFontDirectoryPath);

	/**
	 * Der Pfad zum Verzeichnis für (zusätzliche) Schriftartdateien.
	 * Ggf. müssen Schriftarten zunächst initialisiert werden, bevor
	 * sie für die Berechnung verwendet werden können.
	 * Qt stellt dazu z.B. die Klasse QFontDatabase zur Verfügung.
	 * Diese zusätzlichen Schriftartdateien befinden sich dann in diesem
	 * Verzeichnis.
	 * Wenn der Pfad leer ist, gibt es keine zusätzlichen Schriftartdateien.
	 *
	 * \sa setFontDirectoryPath().
	 */
	const QString& fontDirectoryPath() const;

	/**
	 * Ist der aktuelle Verzeichnispfad fontDirectoryPath() gültig?.
	 * Ist der Pfad ungültig, steht in \a strError der Grund.
	 * Ist der Pfad leer wird 'false' zurückgegeben.
	 */
	bool hasValidFontDirectoryPath(QString* strError = 0) const;

	/**
	 * Schriftartdateien aus dem Datenverzeichnis auslesen.
	 * Über die Methode setFontDirectoryPath() wird dem Plugin
	 * ein Schriftartverzeichnis zugewiesen. Über diese Methode werden
	 * alle vorhandenen Schriftartdateien ausgelesen.
	 * Diese Methode wird aufgerufen, wenn ein Übersetzungspaket
	 * für einen Übersetzer zusammengestellt wird.
	 *
	 * Diese Schriftartdateien werden in das Übersetzungspaket
	 * gepackt und beim Übersetzer relativ zum Projektpfad
	 * abgelegt:
	 * - Vektor-Schriftarten: fonts
	 * - Bitmap-Schriftarten: bfonts
	 *
	 * Im einfachsten Fall kann diese Methode die Methode _fetchDataFiles()
	 * benutzen, um die Schriftartdateien aus dem Schriftartverzeichnis
	 * auszulesen.
	 */
	virtual const QStringList fetchFontFiles() const = 0;

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
	virtual bool canResolveFont(const QString& strFontName) const = 0;

	/**
	 * Eine Liste mit allen zur Verfügung stehenden Schriftarten.
	 * In der Regel sind das die Schriftarten, die in dem
	 * aktuellen Datenverzeichnis vorhanden sind.
	 */
	virtual const QStringList availableFonts() const = 0;

	/**
	 * Eine Liste mit allen zur Verfügung stehenden Schriftarten im Verzeichnis \a strPath.
	 * Diese Methode wird z.B. vom Dialog Projekteigenschaften verwendet, wenn das Verzeichnis
	 * für Schriftarten oder sich das Plugin geändert hat, um bei den alternativen Schriftarten
	 * die aktuell zur Verfügung stehenden Schriftarten anzuzeigen.
	 */
	virtual const QStringList availableFonts(const QString& strPath) const = 0;

	//@}


	/**
	 * \name Zeichenauflösung:
	 */
	//@{

	/**
	 * Kann das Zeichen \a c in der Schriftart \a strFontName aufgelöst werden?.
	 * Wenn der Parameter \a bStore = true ist, kann ein nicht aufgelöstes Zeichen
	 * in einer internen Datenstruktur für unaufgelöste Zeichen gespeichert werden.
	 * Auf diese interne Datenstruktur kann dann z.B. von der Methode unresolvedChars()
	 * zugegriffen werden.
	 *
	 * Falls Zeichenauflösung nicht zur Verfügung steht, sollte diese Methode
	 * immer true zurückgeben.
	 *
	 * \sa unresolvedChars(), calculateWidth().
	 */
	virtual bool canResolveChar(const QChar& c, const QString& strFontName, bool bStore) = 0;

	/**
	 * Liefert alle nicht aufgelösten Zeichen der Schriftart \a strFontName zurück.
	 * Die Defaultimplementierung gibt eine leere Liste zurück, was bedeutet,
	 * dass alle Zeichen für die übergebene Schriftart \a strFontName aufgelöst
	 * werden können.
	 * Die interne Datenstruktur der unaufgelösten Zeichen wird über den Aufruf
	 * der Methoden canResolveChar() und calculateWidth() befüllt.
	 * \sa canResolveChar(), calculateWidth().
	 */
	virtual QList<ushort> unresolvedChars(const QString& strFontName) const;

	/**
	 * Liefert alle fehlerhaften Kerningeintäge der Schriftart \a strFontName zurück.
	 * Die Defaultimplementierung gibt eine leere Liste zurück, was bedeutet,
	 * dass die übergebene Schriftart \a strFontName keine Kerning-Fehler enthält.
	 * \attention Diese Methode ist speziell für Bitmapschriftarten von Bedeutung!
	 */
	virtual QStringList kerningErrors(const QString& strFontName) const;

	//@}


	/**
	 * \name Breitenberechnung:
	 */
	//@{

	/**
	 \brief Breitenberechnung für den Text \a strText durchführen.
	 Zur Längenberechnung wird die Schriftart verwendet, die
	 die Attribute \a strFontName, \a iFontSize, \a bBoldFont
	 und \a bItalicFont besitzt.
	 \attention Wird ein leerer Text übergeben, so muss das Plugin 0 statt -1 zurückgeben - ein leerer Text belegt keinen Platz.
	 * \return Es wird die berechnete Breite in Pixeln zurückgegeben.
	 * Im Fehlerfall wird -1 zurückgegeben.
	 *
	 * Wenn die Breitenberechnung nicht durchgeführt werden kann,
	 * weil einzelne Zeichen in \a strText nicht aufgelöst werden
	 * können, wird \a iResultCode auf CalculationUnresolvedCharError
	 * gesetzt. Idealerweise benutzt diese Methode zu diesem Test
	 * die Methode canResolveChar( someChar, strFontName, true ), d.h.
	 * unaufgelöste Zeichen werden auch gespeichert.
	 *
	 * Der Parameter \a iResultCode gibt Auskunft darüber, ob
	 * die Berechnung korrekt ausgeführt werden konnte oder
	 * ein spezieller Fehler gemäß CalculationResultE auftrat.
	 *
	 * \sa CalculationResultE.
	 */
	virtual int calculateWidth(const QString&                   strText,
							   const QString&                   strFontName,
							   int                              iFontSize,
							   bool                             bBoldFont,
							   bool                             bItalicFont,
							   const CalculateFontShowMessagesE eMessages,
							   unsigned int*                    iResultCode = 0) = 0;
	//@}


	/**
	 * \name Schriftarten zur Laufzeit ändern:
	 *
	 * Diese Methoden müssen nur implementiert werden, wenn
	 * an den Schriftarten zur Laufzeit des Programms Änderungen
	 * durchführbar sein sollen. Diese Änderungsoperationen sind
	 * über den Dialog 'Übersicht Schriftarten' verfügbar.
	 */
	//@{

	/**
	 * Kann eine Schriftart hinzugefügt werden?.
	 * Die Defaultimplementierung gibt false zurück.
	 * Wenn diese Methode überschrieben wird, sollte auch
	 * die Methode addFont() überschrieben werden.
	 * \sa addFont().
	 */
	virtual bool canAddFont() const;

	/**
	 * Fügt die Quelldatei für die Schriftart \a strFontName hinzu.
	 * Im Fall eines Fehlers wird in \a strError die Fehlermeldung
	 * zurückgegeben.
	 *
	 * Wenn diese Methode implementiert wird, sollte die Quelldatei
	 * der Schriftart in das Standardverzeichnis kopiert werden, falls
	 * sie sich dort noch nicht befindet.
	 *
	 * Die Defaultimplementierung führt keine Aktion durch
	 * und gibt false zurück.
	 *
	 * \sa canAddFont().
	 */
	virtual bool addFont(const QString& strFontName,
						 QString* strError = 0);


	/**
	 * Kann die Quelldatei einer Schriftart ausgetauscht werden?.
	 * Die Defaultimplementierung gibt false zurück.
	 * Wenn diese Methode überschrieben wird, sollte auch
	 * die Methode replaceFont() überschrieben werden.
	 * \sa replaceFont().
	 */
	virtual bool canReplaceFont() const;

	/**
	 * Tauscht die Quelldatei der Schriftart \a strFontName aus.
	 * Im Fall eines Fehlers wird in \a strError die Fehlermeldung
	 * zurückgegeben.
	 *
	 * Wenn diese Methode implementiert wird, sollte:
	 * - Wenn die Quelldatei nicht im zugehörigen Standardverzeichnis liegt,
	 *   muss die vorhandene Quelldatei gelöscht werden und die neue Quelldatei
	 *   in das Standardverzeichnis kopiert werden.
	 *
	 * Die Defaultimplementierung führt keine Aktion durch
	 * und gibt false zurück.
	 *
	 * \sa canReplaceFont().
	 */
	virtual bool replaceFont(const QString& strFontName,
							 QString* strError = 0);

	/**
	 * Kann die Quelle für eine Schriftart neu geladen werden?.
	 * Die Defaultimplementierung gibt false zurück.
	 * Wenn diese Methode überschrieben wird, sollte auch
	 * die Methode refreshFont() überschrieben werden.
	 * \sa refreshFont().
	 */
	virtual bool canRefreshFont() const;

	/**
	 * Aktualisiert die Schriftart \a strFontName.
	 * Im Fall eines Fehlers wird in \a strError die Fehlermeldung zurückgegeben.
	 * Die Defaultimplementierung führt keine Aktion durch
	 * und gibt false zurück.
	 * \sa canRefreshFont().
	 */
	virtual bool refreshFont(const QString& strFontName,
							 QString* strError = 0);

	//@}


	/**
	 * \name Plugin:
	 */
	//@{

	/**
	 * Den Lader zuweisen, der dieses Plugin geladen hat.
	 * Hintergrund: Über den Loader kann das Plugin wieder
	 * korrekt entladen werden.
	 */
	void setPluginLoader(QPluginLoader* plugLoader);

	/// Der Lader, der dieses Plugin geladen hat.
	QPluginLoader* pluginLoader() const;

	/// Kann das Plugin entladen / gelöscht werden?.
	bool canUnloadPlugin() const;

	//@}


	/**
	 * \name Fehlermeldungen:
	 */
	//@{

	/**
	 * Gibt zu dem Fehler \a error die entsprechende Meldung zurück.
	 * Die Meldung wird mit dem !-Zeichen abgeschlossen.
	 * Die fehlenden Parameter werden in \a param übergeben.
	 */
	static QString errorMessage(ErrorE	     error,
								QStringList param);

	//@}


protected:
	/**
	 * Dateien aus dem Datenverzeichnis \a strPath auslesen.
	 * Wenn \a strPath leer ist, wird \a _strFontDirectoryPath genommen.
	 * Ggf. können die Dateien über den Filter \a lNameFilters
	 * gefiltert werden.
	 */
	const QStringList _fetchDataFiles(const QStringList* lNameFilters	   = 0,
									  const QString& 	strPath		   = QString::null,
									  bool		  addDirectoryPath = true) const;

	/**
	 * Eine Datei für die Schriftart \a strFontName über einen Dialog auswählen.
	 * Ggf. können die Dateien über den Filter \a lNameFilters
	 * gefiltert werden.
	 */
	const QString _selectExistingFile(const QString&     strFontName,
									  const QStringList* lNameFilter) const;

	/**
	 * Ein Verzeichnis für die Schriftart \a strFontName über einen Dialog auswählen.
	 */
	const QString _selectExistingDir(const QString& strFontName) const;


private:

	static void _completeParamList(QStringList* param, int paramCount);
	QPluginLoader*	_pluginLoader;
	QString			m_fontDirectoryPath;

	static QUuid m_uuid;
	static QUuid m_uuidBitmap;
};


// EXPAND: Die Versionsnummer in dem unten aufgefuehrten String
// muss angepasst werden, wenn sich wesentliche Aenderungen in dieser
// Schnittstelle ergeben.
// Durch eine Aenderung des Strings werden alle Plugins, die sich
// im Umlauf befinden automatisch ungueltig und koennen nicht mehr
// geladen werden!
Q_DECLARE_INTERFACE(LengthCalculationInterface, "vw.eefh.HMI-Linguist.LengthCalculationInterface/2.0")

#endif // LENGTHCALCULATIONINTERFACE_H

