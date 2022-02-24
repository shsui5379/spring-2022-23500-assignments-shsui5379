#pragma once

#include "Node.h"

class List
{
private:
   Node *head;

public:
   List();
   void insert(std::string data);
   std::string toString();
   int locate(std::string data);
   void remove(std::string data);
   ~List();
};