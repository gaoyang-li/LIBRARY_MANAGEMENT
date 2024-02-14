#include "library.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include <vector>

void Document::updateTitle(const std::string newTitle) {  // getters and setters
  _title = newTitle;
}

void Document::updateYear(int newYear) { _year = newYear; }
void Document::updateQuantity(int newQuantity) { _quantity = newQuantity; }
std::string Document::getTitle() { return _title; }
int Document::getYear() { return _year; }
int Document::getQuantity() { return _quantity; }



Document::Document(std::string title, int year, int quantity):
  _title(title), _year(year), _quantity(quantity) {}     // constructor member initializer lists of Document



bool Document::borrowDoc() {         // Used when borrowing a document, should return true on success and false on failure 
  if (_quantity > 0) {
    _quantity--;
    return true;
  }
  return false;
}

void Document::returnDoc() { _quantity++; } // used when a document is returned. quantity incremented.


Novel::Novel(const std::string title, const std::string author, int year, int quantity):
  Document(title, year, quantity), _author(author) {}   //Constructor member initializer lists of Novel

Novel::~Novel() {}          // destructor of Novel

DocType Novel::getDocType() { return DOC_NOVEL; } // return DOC_NOVEL when the document type is Novel

void Novel::print() {       // Output the title, author, year and quantity of Novel
  std::cout << "Novel, title: " << _title << ", author: " << _author << ", year: " << _year << ", quantity: " << _quantity << "\n"; 
}

void Novel::updateAuthor(const std::string newAuthor) { // update the author of Novel
  _author = newAuthor;
}

std::string Novel::getAuthor() { return _author; }    // get the author of Novel

Comic::Comic(const std::string title, const std::string author, int issue, int year, int quantity):
  Document(title, year, quantity), _author(author), _issue(issue) {} // Constructor member initializer lists of Comic

Comic::~Comic() { // destructor of Comic
}

DocType Comic::getDocType() { return DOC_COMIC; } // return DOC_COMIC when the document type is comic

void Comic::print() { // Output the title, author, issue, year and quantity of Comic
  std::cout << "Comic, title: " << _title << ", author: " << _author << ", issue: " << _issue << ", year: " << _year << ", quantity: " << _quantity << "\n";
}

void Comic::updateAuthor(const std::string newAuthor) { // update the author of Comic
  _author = newAuthor;
}

void Comic::updateIssue(int newIssue) { _issue = newIssue; }    // update the issue of Comic
std::string Comic::getAuthor() { return _author; }              // update the author of Comic
int Comic::getIssue() { return _issue; }                        // update the issue of Comic

Magazine::Magazine(const std::string title, int issue, int year, int quantity):
  Document(title, year, quantity), _issue(issue) {}       // Constructor member initializer lists

Magazine::~Magazine() { // destructor of Magazine
}

DocType Magazine::getDocType() { return DOC_MAGAZINE; } // return DOC_MAGAZINE when the document type is Magazine

void Magazine::print() {  // output the title, issue, year and quantity of Magazine
  std::cout << "Magazine, title: " << _title << ", issue: " << _issue << ", year: " << _year << ", quantity: " << _quantity << "\n";
}

void Magazine::updateIssue(int newIssue) {  // update the issue of Magazine
  _issue = newIssue;
}

int Magazine::getIssue() {  // get the issue of Magazine
  return _issue;
}

Library::Library(){} // constructor of Library

bool Library::addDocument(DocType t, const std::string title, const std::string author, int issue, int year, int quantity) {  // add a document. return true on success and false on failure
  Document *d = NULL;
  switch (t) {
  case DOC_NOVEL: {
    d = (Document *)new Novel(title, author, year, quantity);
    break;
  }

  case DOC_COMIC: {
    d = (Document *)new Comic(title, author, issue, year, quantity);
    break;
  }

  case DOC_MAGAZINE: {
    d = (Document *)new Magazine(title, issue, year, quantity);
    break;
  }

  default:
    return false;
  }

  return addDocument(d);
}


bool Library::addDocument(Document *d) {  // add a document. return true on success and false on failure
  for (auto ele: _docs){
    if (!(ele->getTitle().compare(d->getTitle()))){
      return false;
    }
  }

  _docs.push_back(d); // use push_back to add the pointer to _docs

  return true;
}



bool Library::delDocument(const std::string title) {  // delete an document in the library. return ture on success and false on failure
    std::vector<Document*>::iterator it = _docs.begin();  // use iterator to loop the vector
    while (it != _docs.end()){
      if (!((*it)->getTitle().compare(title))){           // if the title is found, use erase to remove it from the vector
        it = _docs.erase(it);
        return true;
      }
      else{
        it++;
      }
    }
  return false;
}

int Library::countDocumentOfType(DocType t) { // count the number of document of a given type present in the library
  int i = 0;
  int res = 0;
  for (auto ele: _docs){
    if (ele->getDocType() == t){
      res++;
    }
    i++;
  }
  return res;
}


Document *Library::searchDocument(const std::string title) { // search for a document based on the title.
  for (auto ele: _docs){
    if (!(ele->getTitle().compare(title))){
      return ele;
    } 
  }
  return NULL;
}

void Library::print() {   // print the entire library
  for (auto ele: _docs){
    ele->print();
  }
}

bool Library::borrowDoc(const std::string title) {  // borrow a document. return true on success and false on failure
  Document *d = searchDocument(title);
  if (d){
    return d->borrowDoc();
  }
  return false;
}

bool Library::returnDoc(const std::string title) {  // return a document. return true on success and false on failure
  Document *d = searchDocument(title);
  if (d) {
    d->returnDoc();
    return true;
  }
  return false;
}

bool Library::dumpCSV(const std::string filename) { // dump the library in a CSV file
  std::string line;             // initialise the content of each document
  std::string content = "";     // initialise the content to be write to the file
  std::ofstream myFile;
  myFile.open(filename, std::ios::out); // open the file for write

  for (auto ele: _docs){
    switch (ele->getDocType()) {  

    case DOC_NOVEL: {
      Novel *n = dynamic_cast<Novel*> (ele);              //use dynamic_cast to convert safely
      line = "novel," + n->getTitle() + "," + n->getAuthor() + ",," + std::to_string(n->getYear()) + "," + std::to_string(n->getQuantity()) + "\n";
      content = content + line;
      break;
    }

    case DOC_COMIC: {
      Comic *c = dynamic_cast<Comic*> (ele);              //use dynamic_cast to convert safely
      line = "comic," + c->getTitle() + "," + c->getAuthor() + "," + std::to_string(c->getIssue()) + "," + std::to_string(c->getYear()) + "," + std::to_string(c->getQuantity()) + "\n";
      content = content + line;
      break;
    }

    case DOC_MAGAZINE: {
      Magazine *m = dynamic_cast<Magazine*> (ele);        //use dynamic_cast to convert safely
      line = "magazine," + m->getTitle() + ",," + std::to_string(m->getIssue()) + "," + std::to_string(m->getYear()) + "," + std::to_string(m->getQuantity()) + "\n";
      content = content + line;
      break;
    }

    default:
      return false;
    }

  }
  myFile << content;  // write to the file
  myFile.close();     // close the file
  return true;
}
