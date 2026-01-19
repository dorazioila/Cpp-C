#ifndef XMLFILESERIALIZER_HPP
#define XMLFILESERIALIZER_HPP

#include "XmlFileSerializerException.h" 
#include "Exception.h"
#include <fstream>
#include <string>

template<typename T>
class XmlFileSerializer {
public:
    static const char READ;
    static const char WRITE;

private:
    std::fstream file;
    std::string filename;
    char mode;
    std::string collectionName;

public:
    // --- Pas de constructeur par défaut / copie
    XmlFileSerializer() = delete;
    XmlFileSerializer(const XmlFileSerializer&) = delete;
    XmlFileSerializer& operator=(const XmlFileSerializer&) = delete;

    // --- Constructeur principal ---
    XmlFileSerializer(const std::string& fn, char m, const std::string& cn = "entities");

    // --- Destructeur ---
    ~XmlFileSerializer();

    // --- Méthodes demandées ---
    void write(const T& val);
    T read();

    // --- Accesseurs ---
    std::string getFilename() const { return filename; }
    std::string getCollectionName() const { return collectionName; }
    bool isReadable() const { return mode == READ; }
    bool isWritable() const { return mode == WRITE; }

private:
    void writeXmlHeader();
    void writeStartCollection();
    void writeEndCollection();
    void readXmlHeader();
    void readStartCollection();

};

#include "XmlFileSerializer.ipp"

#endif
