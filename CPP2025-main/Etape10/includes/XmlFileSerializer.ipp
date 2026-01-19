#ifndef XMLFILESERIALIZER_IPP
#define XMLFILESERIALIZER_IPP

template<typename T>
const char XmlFileSerializer<T>::READ = 'R';

template<typename T>
const char XmlFileSerializer<T>::WRITE = 'W';


/* ============================================================
   CONSTRUCTEUR
   ============================================================ */
template<typename T>
XmlFileSerializer<T>::XmlFileSerializer(const std::string& fn, char m, const std::string& cn)
    : filename(fn), mode(m), collectionName(cn)
{
    if (mode == WRITE)
    {
        file.open(filename, std::ios::out | std::ios::trunc);
        if (!file)
            throw XmlFileSerializerException("Impossible d'ouvrir le fichier en écriture.", 
                                            XmlFileSerializerException::FILE_NOT_FOUND);

        writeXmlHeader();
        writeStartCollection();
    }
    else if (mode == READ)
    {
        file.open(filename, std::ios::in);
        if (!file)
            throw XmlFileSerializerException("Fichier introuvable.", 
                                            XmlFileSerializerException::FILE_NOT_FOUND);

        readXmlHeader();
        readStartCollection();   // met à jour collectionName depuis le fichier
    }
    else {
        throw XmlFileSerializerException("Mode invalide.", XmlFileSerializerException::NOT_ALLOWED);
    }
}


/* ============================================================
   DESTRUCTEUR
   ============================================================ */
template<typename T>
XmlFileSerializer<T>::~XmlFileSerializer()
{
    if (mode == WRITE && file.is_open())
        writeEndCollection();

    if (file.is_open())
        file.close();
}


/* ============================================================
   WRITE(T)
   ============================================================ */
template<typename T>
void XmlFileSerializer<T>::write(const T& val)
{
    if (mode != WRITE)
        throw XmlFileSerializerException("Lecture uniquement : write() interdit.",
                                         XmlFileSerializerException::NOT_ALLOWED);

    file << val;
}


/* ============================================================
   READ()
   ============================================================ */
template<typename T>
T XmlFileSerializer<T>::read()
{
    if (mode != READ)
        throw XmlFileSerializerException("Ecriture uniquement : read() interdit.",
                                         XmlFileSerializerException::NOT_ALLOWED);

    std::streampos pos = file.tellg();

    std::string token;
    file >> token;  // lit un mot (ou balise)

    std::string endTag = "</" + collectionName + ">";

    if (token == endTag)
        throw XmlFileSerializerException("Fin de fichier XML",
                                         XmlFileSerializerException::END_OF_FILE);

    // Sinon, on doit revenir en arrière avant la lecture
    file.seekg(pos);

    T obj;
    file >> obj;
    return obj;
}


/* ============================================================
   ÉCRITURE XML
   ============================================================ */
template<typename T>
void XmlFileSerializer<T>::writeXmlHeader()
{
    file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
}

template<typename T>
void XmlFileSerializer<T>::writeStartCollection()
{
    file << "<" << collectionName << ">\n";
}

template<typename T>
void XmlFileSerializer<T>::writeEndCollection()
{
    file << "</" << collectionName << ">\n";
}


/* ============================================================
   LECTURE XML
   ============================================================ */
template<typename T>
void XmlFileSerializer<T>::readXmlHeader()
{
    std::string line;
    std::getline(file, line);
}

template<typename T>
void XmlFileSerializer<T>::readStartCollection()
{
    std::string line;
    std::getline(file, line);

    // line devrait être du type : <clients> ou <whatever>
    if (line.size() > 2 && line[0] == '<' && line[1] != '/')
    {
        // extraire collectionName depuis la balise
        collectionName = line.substr(1, line.size() - 2);
    }
}

#endif
