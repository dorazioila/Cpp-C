template<typename T>
XmlFileSerializer<T>::XmlFileSerializer(const std::string& fname, const std::string& colName, char m): filename(fname), collectionName(colName), mode(m)
{
    if (mode == WRITE) {
        file.open(filename, std::ios::out);
        if (!file.is_open())
            throw std::runtime_error("Impossible d'ouvrir le fichier en écriture");

        writeHeader();          // étape 1 : écrire l'entête
        writeCollectionStart(); // étape 2 : écrire la balise de début de collection
    } 
    else if (mode == READ) {
        file.open(filename, std::ios::in);
        if (!file.is_open())
            throw std::runtime_error("Impossible d'ouvrir le fichier en lecture");
        // on pourrait lire et vérifier l'entête ici
    } 
    else {
        throw std::invalid_argument("Mode inconnu. Utiliser READ ou WRITE.");
    }
}

template<typename T>
XmlFileSerializer<T>::~XmlFileSerializer() {
    if (mode == WRITE) writeCollectionEnd(); // étape 2 : fin de collection
    if (file.is_open()) file.close();
}

template<typename T>
void XmlFileSerializer<T>::writeHeader() {
    file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
}

template<typename T>
void XmlFileSerializer<T>::writeCollectionStart() {
    file << "<" << collectionName << ">\n";
}

template<typename T>
void XmlFileSerializer<T>::writeCollectionEnd() {
    file << "</" << collectionName << ">\n";
}
