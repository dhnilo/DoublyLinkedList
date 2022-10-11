//Drew Hnilo
//CS310
//Template class for DoublyLinkedList

#include <iostream>
#include <vector>
#include "movie.h"

using namespace std;

template<class T> class Node {
  public:
    T data;
    Node<T>* next;
    Node<T>* prev;
    Node(T data){
      this->data = data;
      next = nullptr;
      prev = nullptr;
    }
    Node(T d, Node<T>* n, Node<T>* p) {
      data = d;
      next = n;
      prev = p;
    }
};

template<class T> class DoublyLinkedList{
  public:
    Node<T>* head;
    Node<T>* tail;
    int count;
    
    // default
    DoublyLinkedList() {
      head = nullptr;
      tail = nullptr;
      count = 0;
    }

    //copy constructor
    DoublyLinkedList(const DoublyLinkedList<T> &obj) {
      if (obj.head == nullptr) {  //List is empty
        this->head = nullptr;
        this->tail = nullptr;
      }
      else {
        this->head = createNewNode(obj.head->data);
        Node<T>* oTemp = obj.head->next;
        Node<T>* temp = this->head;

        while (oTemp != nullptr) {
          temp->next = createNewNode(oTemp->data, nullptr, temp);
          temp = temp->next;
          oTemp = oTemp->next;
        }
        tail = temp;
      }
    }

    // this method deallocates memory
    ~DoublyLinkedList() {
      Node<T>* current = head;
      Node<T>* temp = nullptr;
      while (current != nullptr) {
        temp = current->next;
        delete current;
        current = temp;
        count--;
      }
      head = nullptr;
      tail = nullptr;
      count = 0;
    }

    Node<T>* createNewNode(T data) {
      count++;
      return new Node<T>(data);
    }
    Node<T>* createNewNode(T data, Node<T>* next, Node<T>* prev) {
      count++;
      return new Node<T>(data, next, prev);
    }

    void push_front(T data);
    void push_back(T data);
    void insert_after(Node<T>* prevNode, T data);
    bool insert(int index, T data);
    bool pop_front(T &data);
    bool pop_back(T &data);
    void deleteItem(T data);
    void deleteAt(int index);
    vector<int> search(T data);
    void displayList();
    void displayReverse();
};


int main() {
  DoublyLinkedList<Movie> movCollection;
  
  Movie m1("Harry Potter and the Sorcerer's Stone", "J.K. Rowling", 2001);
  Movie m2("Hotel Transylvania", "Genndy Tartakovsky", 2012);
  Movie m3("Dispicable Me", "Pierre Coffin", 2010);
  Movie m4("Harry Potter and the Order of the Phoenix", "J.K. Rowling", 2007);
  Movie m5("Star Wars: A New Hope", "George Lucas", 1977);
  Movie m6("Star Trek", "Robert Wise", 1978);
  Movie m7("The Godfather", "Francis Ford Coppola", 1972);
  Movie m8("Harry Potter and the Sorcerer's Stone", "J.K. Rowling", 2001);
  Movie m9("Interstellar", "Christopher Nolan", 2014);
  Movie m10("The Martian", "Ridley Scott", 2015);


  movCollection.push_back(m1);
  movCollection.push_back(m2);
  movCollection.push_back(m3);
  movCollection.push_back(m4);
  movCollection.push_back(m5);
  movCollection.push_back(m6);
  movCollection.push_back(m7);
  movCollection.push_back(m8);
  movCollection.push_back(m9);
  movCollection.push_back(m10);

  movCollection.displayList();

  DoublyLinkedList<Movie> myMovCollection(movCollection);

  myMovCollection.displayList();

  movCollection.displayReverse();
  movCollection.displayList();

  Movie findMovie("Harry Potter and the Sorcerer's Stone", "J.K. Rowling", 2001);
  vector<int> searchIndex = movCollection.search(findMovie);
  cout << "\n";
  for(int i=0; i<searchIndex.size(); i++) {
    cout<<searchIndex[i]<<" ";
  }
  cout << endl;
  movCollection.displayList();

  Movie deleteMovie("Harry Potter and the Sorcerer's Stone", "J.K. Rowling", 2001);
  movCollection.deleteItem(deleteMovie);
  movCollection.displayList();
  return 0;
}

template<class T>
void DoublyLinkedList<T>::push_front(T data) {
  //allocate memory for New node
  Node<T>* newNode = createNewNode(data);
  // list is not empty
  if (head != nullptr){
    //new node is head and previous is null, we are adding at the front
    newNode->next = head;
    head->prev = newNode; //previous of head is new node
    head = newNode;
  }
  else { // list is empty
    //new node is the new head
    head = newNode;
    tail = newNode;
  }
  count++;
}

template<class T>
void DoublyLinkedList<T>::push_back(T data) {
  //allocate memory for node
  Node<T>* newNode = createNewNode(data);
  // list is not empty
  if(tail != nullptr) {
    tail->next = newNode; // tail should point to newNode
    newNode->prev = tail; // newNode points to the tail
    tail = newNode;
  }
  else { // list is empty
    head = newNode;
    tail = newNode;
  }
  count++;
}

template<class T>
void DoublyLinkedList<T>::insert_after(Node<T>* prevNode, T data) {
  //check if prevNode is null
  if (prevNode == nullptr) {
    cout << "Previous node is required, it cannot be NULL" << endl;
    return;
  }

  Node<T>* newNode = new Node<T>(data);
  newNode->next = prevNode->next;
  prevNode->next = newNode;
  newNode->prev = prevNode;

  //set prev of newNode next to newNode
  if(newNode->next != nullptr)
    newNode->next->prev = newNode;
  count++;
}

template<class T>
bool DoublyLinkedList<T>::insert(int index, T data) {
  if (index<0 || index>count)
    return false; //invalid index
  if (index==0) //insert at front
    push_front(data);
  else if(index==count) //insert at back
    push_back(data);
  else { //navigate to the node at index position
    Node<T>* current = head;
    for (int i = 0; i < index-1; i++) {
      current = current->next;
    }
    insert_after(current, data);
  }
  return true;
}

template<class T>
bool DoublyLinkedList<T>::pop_front(T &data) {
  if(count==0 || head == nullptr)
    return false;
  // get the value from the front
  data = head->data;
  if(head->next== nullptr) { // if this is the only node
    delete head;
    tail = nullptr;
    head = nullptr;
    count = 0;
    return true;
  }
  Node<T>* prevHead = head;
  // head should point to the next node
  head = head->next;
  // the current head would be deleted
  head->prev = nullptr;
  if(head == tail) // this is the only node
    tail->prev = nullptr;
  delete prevHead;
  count--;
  return true;
}

template<class T>
bool DoublyLinkedList<T>::pop_back(T &data) {
  if(count==0 || tail == nullptr)
    return false;
  // get the value from the back
  data = tail->data;
  if(head->next== nullptr) { // if this is the only node
    delete head;
    tail = nullptr;
    head = nullptr;
    count = 0;
    return true;
  }
  Node<T>* prevTail = tail;
  // tail should be the previous node
  tail = tail->prev;
  // the current tail would be deleted
  tail ->next = nullptr;
  if(head == tail) // this is the only node
    head->next = nullptr;
  delete prevTail;
  count--;
  return true;
}

template<class T>
void DoublyLinkedList<T>::deleteItem(T data) {
  //if list is empty
  if(head == nullptr) {
    cout<< "List is empty" << endl;
    return;
  }
  //if list is not empty
  Node<T> *temp = head;
  while(temp != nullptr) {
    if(temp->data == data) {
      if(temp == head) { //if node to be deleted is head
        head = head->next;
        head->prev = nullptr;
        delete temp;
        temp = head;
      }
      else if(temp == tail) { //if node to be deleted is tail
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        temp = nullptr;
      }
      else { //if node to be deleted is in between
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        Node<T> *temp2 = temp->next;
        delete temp;
        temp = temp2;
      }
      count--;
    }
    else { //if node to be deleted is not found
      temp = temp->next;
    }
  }
}

template<class T>
void DoublyLinkedList<T>::deleteAt(int index) {
  //if list is empty
  if(head == nullptr) {
    cout << "List is empty" << endl;
    return;
  }
  //if index is invalid
  if(index < 0 || index >= count) {
    cout << "Invalid index" << endl;
    return;
  }
  Node<T> *temp = head;
  int i = 0;
  if(index <= count/2) { //from beginning
    while(i < index) {
      temp = temp->next;
      i++;
    }
  }
  else { // from tail
    temp = tail;
    i = count-1;
    while(i > index) {
      temp = temp->prev;
      i--;
    }
  }
  if(temp == head) {
    head = head->next;
    head->prev =nullptr;
    delete temp;
  }
  else if(temp == tail) {
    tail = tail->prev;
    tail->next = nullptr;
    delete temp;
  }
  else {
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    delete temp;
  }
  count--;
}

template<class T>
vector<int> DoublyLinkedList<T>::search(T data) {
  vector<int> found;
  if (head == nullptr) {
    cout << "List is empty" << endl;
    return {};
  }
  Node<T> *temp = head;
  int index = 0;
  while (temp != nullptr) {
    if (temp->data == data) {
      found.push_back(index);
    }
    temp = temp->next;
    index++;
  }
  return found;
}

template<class T>
void DoublyLinkedList<T>::displayList() {
  Node<T>* node = head;
  cout << "FRONT\n";
  while (node != nullptr) {
    cout << node->data << "\n<==>\n";
    node = node->next;
  }
  if(node==nullptr)
    cout<< "END" << endl;
}

template <class T>
void DoublyLinkedList<T>::displayReverse() {
  Node<T> *hNode = head;
  Node<T> *tNode = tail;
  while(hNode != tNode && hNode->prev != tNode) {
    T temp = hNode->data;
    hNode->data = tNode->data;
    tNode->data = temp;
    hNode = hNode->next;
    tNode = tNode->prev;
  }
}
