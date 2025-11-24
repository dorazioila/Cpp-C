#ifndef XML_FILE_SERIALIZER_HPP
#define XML_FILE_SERIALIZER_HPP

#include <fstream>
#include <string>
#include <stdexcept>

template<typename T>
class XmlFileSerializer {
private:
    std::fstream file;           // lien avec le fichier sur disque
    std::string filename;        // nom du fichier
    char mode;                   // READ ou WRITE
    std::string collectionName;  // nom de la collection

public:
    // constantes pour les modes
    static const char READ = 'R';
    static const char WRITE = 'W';

    // constructeur / destructeur
    XmlFileSerializer(const std::string& fname, const std::string& colName, char m);
    ~XmlFileSerializer();

    // ecriture fichier XML
    void writeHeader();            // écrit <?xml version="1.0" encoding="UTF-8"?>
    void writeCollectionStart();   // écrit <collectionName>
    void writeCollectionEnd();     // écrit </collectionName>
};

#include "XmlFileSerializer.ipp"

#endif // XML_FILE_SERIALIZER_HPP