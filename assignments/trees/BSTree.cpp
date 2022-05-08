#include <iostream>
#include "Node.h"

#include "BSTree.h"

BSTree::BSTree()
{
   root = nullptr;
}

std::string BSTree::get_debug_string()
{
   return traverse(root);
}

std::string BSTree::traverse(Node *subtreeRoot)
{
   if (subtreeRoot == nullptr)
   {
      return "";
   }

   if (subtreeRoot->getLeft() == nullptr && subtreeRoot->getRight() == nullptr)
   {
      return std::to_string(subtreeRoot->getData());
   }

   return std::to_string(subtreeRoot->getData()) + ", " + traverse(subtreeRoot->getLeft()) + ", " + traverse(subtreeRoot->getRight());
}

void BSTree::setup()
{
   Node *n = new Node(10);
   root = n;
   n = new Node(20);
   root->setRight(n);
   Node *n2 = new Node(30);
   n->setRight(n2);
   n2 = new Node(15);
   n->setLeft(n2);
   n2 = new Node(5);
   root->setLeft(n2);
   n = new Node(3);
   n2->setLeft(n);
   n = new Node(8);
   n2->setRight(n);
}

int BSTree::search(int value)
{
   Node *t = root;

   while (t != nullptr)
   {
      int tval = t->getData();
      if (tval == value)
      {
         // here we'd really return a full object
         // with all the stuff associated with value
         // not just an int
         return value;
      }

      if (tval < value)
      {
         t = t->getRight();
      }
      else
      {
         t = t->getLeft();
      }
   }

   // if we get here then the value isn't
   // in the tree

   // normally, if we had a tree of objects
   // we could return null but since we only have
   // an int, we can't return an int to represent
   // not found so we'll throw an exception

   throw NODE_NOT_FOUND; // we should define our exceptions.
}

// we will always insert new nodes as leaves
void BSTree::insert(int value)
{

   // make a new node
   Node *newnode = new Node(value);

   // search for where the node would go as a leaf
   // that is, search until we get to null
   // we can use the piggyback strategy of having
   // a second pointer trail the lead pointer
   Node *p = root;
   Node *trailer;

   while (p != nullptr)
   {
      // note that trailer is one level behind
      trailer = p;
      if (p->getData() == value)
      {
         // do the stuff when the node is already in the tree
         return;
      }
      else if (p->getData() < value)
      {
         p = p->getRight();
      }
      else
      {
         p = p->getLeft();
      }
   }

   // handle the special case of the tree
   // being empty (null)
   if (root == nullptr)
   {
      root = newnode;
   }
   else
   {
      // trailer points to the node ABOVE where the new node
      // will go.
      // we have to figure out if newnode goes on the
      // left of trailer or on the right of trailer
      if (trailer->getData() < value)
      {
         trailer->setRight(newnode);
      }
      else
      {
         trailer->setLeft(newnode);
      }
   }
}

int BSTree::rsearch(int value)
{
   return rsearch(value, root);
}

int BSTree::rsearch(int value, Node *root)
{
   if (root == nullptr)
   {
      throw NODE_NOT_FOUND;
   }

   if (root->getData() == value)
   {
      return value;
   }

   if (root->getLeft() == nullptr && root->getRight() == nullptr)
   {
      throw NODE_NOT_FOUND;
   }

   if (value > root->getData())
   {
      return rsearch(value, root->getRight());
   }

   return rsearch(value, root->getLeft());
}

void BSTree::rinsert(int value)
{
   rinsert(value, root);
}

void BSTree::rinsert(int value, Node *root)
{
   if (root == nullptr)
   {
      root = new Node(value);
   }
   else if (value > root->getData())
   {
      if (root->getRight() == nullptr)
      {
         return root->setRight(new Node(value));
      }
      else
      {
         return rinsert(value, root->getRight());
      }
   }
   else if (value < root->getData())
   {
      if (root->getLeft() == nullptr)
      {
         return root->setLeft(new Node(value));
      }
      else
      {
         return rinsert(value, root->getLeft());
      }
   }
}

/**
 * Removes a given value from this Tree
 *
 * @param value  The value to remove
 * */
void BSTree::remove(int value)
{
   remove(value, root);
}

void BSTree::remove(int value, Node *root)
{
   // empty subtree
   if (root == nullptr)
   {
      throw NODE_NOT_FOUND;
   }

   // root is value to delete
   if (root->getData() == value)
   {
      // no child
      if (root->getLeft() == nullptr && root->getRight() == nullptr)
      {
         delete root;
         this->root = nullptr;
      }
      // has only a left child
      else if (root->getLeft() != nullptr && root->getRight() == nullptr)
      {
         Node *newRoot = root->getLeft();
         delete root;
         this->root = newRoot;
      }
      // has only a right child
      else if (root->getRight() != nullptr && root->getLeft() == nullptr)
      {
         Node *newRoot = root->getRight();
         delete root;
         this->root = newRoot;
      }
      // has 2 children
      else if (root->getLeft() != nullptr && root->getRight() != nullptr)
      {
         // get smallest
         Node *walker = root->getRight();

         while (walker->getLeft() != nullptr)
         {
            walker = walker->getLeft();
         }

         // copy
         root->setData(walker->getData());

         // delete dupe
         remove(value, root->getRight());
      }
   }
   // left child is value to delete
   else if (root->getLeft() != nullptr && root->getLeft()->getData() == value)
   {
      Node *toDelete = root->getLeft();

      // no child or one left child
      if ((toDelete->getLeft() != nullptr && toDelete->getRight() == nullptr) || (toDelete->getLeft() == nullptr && toDelete->getRight() == nullptr))
      {
         root->setLeft(toDelete->getLeft());
         delete toDelete;
      }
      // one right child
      else if (toDelete->getRight() != nullptr && toDelete->getLeft() == nullptr)
      {
         root->setRight(toDelete->getRight());
         delete toDelete;
      }
      // two children
      else if (toDelete->getLeft() != nullptr && toDelete->getRight() != nullptr)
      {
         // get smallest
         Node *walker = toDelete->getRight();

         while (walker->getLeft() != nullptr)
         {
            walker = walker->getLeft();
         }

         // copy
         toDelete->setData(walker->getData());

         // delete dupe
         remove(value, toDelete->getRight());
      }
   }
   // right child is value to delete
   else if (root->getRight() != nullptr && root->getRight()->getData() == value)
   {
      Node *toDelete = root->getRight();

      // no child or one left child
      if ((toDelete->getLeft() != nullptr && toDelete->getRight() == nullptr) || (toDelete->getLeft() == nullptr && toDelete->getRight() == nullptr))
      {
         root->setLeft(toDelete->getLeft());
         delete toDelete;
      }
      // one right child
      else if (toDelete->getRight() != nullptr && toDelete->getLeft() == nullptr)
      {
         root->setRight(toDelete->getRight());
         delete toDelete;
      }
      // two children
      else if (toDelete->getLeft() != nullptr && toDelete->getRight() != nullptr)
      {
         // get smallest
         Node *walker = toDelete->getRight();

         while (walker->getLeft() != nullptr)
         {
            walker = walker->getLeft();
         }

         // copy
         toDelete->setData(walker->getData());

         // delete dupe
         remove(value, toDelete->getRight());
      }
   }
   else if (value > root->getData())
   {
      remove(value, root->getRight());
   }
   else
   {
      remove(value, root->getLeft());
   }
}