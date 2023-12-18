// Implementaciones de los métodos de la clase LinkedList

// Destructor
template <typename T>
LinkedList<T>::~LinkedList() {
    Node<T> *current = head;
    while (current != nullptr) {
        Node<T> *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

// Insertar un nodo al principio de la lista
template <typename T>
void LinkedList<T>::insert(T value) {
    std::lock_guard<std::mutex> guard(list_mutex);
    Node<T> *new_node = new Node<T>(value);
    if (!new_node) throw std::bad_alloc();
    new_node->next = head;
    head = new_node;
}

// Eliminar un nodo de la lista
template <typename T>
bool LinkedList<T>::remove(T value) {
    std::lock_guard<std::mutex> guard(list_mutex);
    Node<T> *current = head;
    Node<T> *previous = nullptr;
    while (current != nullptr) {
        if (current->value == value) {
            if (previous != nullptr) {
                previous->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}

// Encontrar un nodo en la lista
template <typename T>
bool LinkedList<T>::find(T value) {
    std::lock_guard<std::mutex> guard(list_mutex);
    Node<T> *current = head;
    while (current != nullptr) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Actualizar el valor de un nodo en la lista
template <typename T>
bool LinkedList<T>::update(T old_value, T new_value) {
    std::lock_guard<std::mutex> guard(list_mutex);
    Node<T> *current = head;
    while (current != nullptr) {
        if (current->value == old_value) {
            current->value = new_value;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Mostrar los valores de la lista
template <typename T>
void LinkedList<T>::display() {
    std::lock_guard<std::mutex> guard(list_mutex);
    Node<T> *current = head;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

// Necesario para evitar errores de enlace con plantillas
template class LinkedList<int>;
