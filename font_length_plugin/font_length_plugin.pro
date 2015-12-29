TEMPLATE = lib
CONFIG  += plugin
HEADERS = ../font_length_app/LengthCalculationInterface.h \
          LengthCalculationDummy8.h \
		  LGFont.h \
		  LGFontIdentifier.h \
		  LGFontManager.h \
		  LGFontSet.h \
		  LGResource.h \
		  LGResourceReader.h \
		  LGTypeDef.h

SOURCES = LengthCalculationDummy8.cpp \
          LGFont.cpp \
		  LGFontManager.cpp \
		  LGFontSet.h
		  
DESTDIR = ../font_length_app/plugins
