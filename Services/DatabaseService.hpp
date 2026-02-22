//
// Created by Cris239 on 2/22/2026.
//

#ifndef LOGINSYSTEM_DATABASESERVICE_H
#define LOGINSYSTEM_DATABASESERVICE_H

#include <string>
#include "../UserData.hpp"


class DatabaseService // Stores users in chained hash table.
{
  public:
      struct UserNode // Represents one chained user entry.
      {
          UserData data; // Stores user payload.
          UserNode* next; // Points to next node.
          UserNode* previous; // Points to previous node.

          UserNode(UserData d) : // Creates linked-list node.
              data(d), next(nullptr), previous(nullptr) { }
      };

  private:
      int tableSize; // Tracks total bucket count.
      UserNode** buckets; // Stores bucket head pointers.

      int hashKey(const std::string& key) const // Hashes username to index.
      {
          int total = 0;
          for (int index = 0; index < static_cast<int>(key.length()); index++)
              total = total + key[index];

          return total % tableSize;
      }

  public:
      DatabaseService(int s) : // Initializes bucket array.
          tableSize(s)
      {
          if (tableSize <= 0)
              tableSize = 1;

          buckets = new UserNode*[tableSize];
          for (int index = 0; index < tableSize; index++)
              buckets[index] = nullptr;
      }

      DatabaseService(const DatabaseService&) = delete; // Prevents accidental shallow copies.
      DatabaseService& operator=(const DatabaseService&) = delete; // Prevents accidental assignments.

      void appendUser(const UserData& data) // Inserts user if absent.
      {
          int bucketIndex = hashKey(data.getName());

          if (buckets[bucketIndex] == nullptr)
          {
              buckets[bucketIndex] = new UserNode(data);
              return;
          }

          UserNode* currentNode = buckets[bucketIndex];
          UserNode* appendLocation = nullptr;

          while (currentNode != nullptr)
          {
              if (currentNode->data.getName() == data.getName())
                  return; // already exists

              appendLocation = currentNode;
              currentNode = currentNode->next;
          }

          UserNode* newNode = new UserNode(data);
          newNode->previous = appendLocation;
          appendLocation->next = newNode;
      }

      UserNode* search(const std::string& name) // Finds user by username.
      {
          int bucketIndex = hashKey(name);
          UserNode* currentNode = buckets[bucketIndex];

          while (currentNode != nullptr)
          {
              if (currentNode->data.getName() == name)
                  return currentNode;

              currentNode = currentNode->next;
          }

          return nullptr;
      }

      bool deleteUser(const std::string& name) // Deletes user if found.
      {
          UserNode* deleteNode = search(name);

          if (deleteNode == nullptr)
              return false;

          int bucketIndex = hashKey(name);

          if (deleteNode->previous == nullptr)
              buckets[bucketIndex] = deleteNode->next;
          else
              deleteNode->previous->next = deleteNode->next;

          if (deleteNode->next != nullptr)
              deleteNode->next->previous = deleteNode->previous;

          delete deleteNode;
          return true;
      }

      ~DatabaseService() // Frees all allocated nodes.
      {
          for (int bucket = 0; bucket < tableSize; bucket++)
          {
              UserNode* currentNode = buckets[bucket];
              while (currentNode != nullptr)
              {
                  UserNode* deleteNode = currentNode;
                  currentNode = currentNode->next;
                  delete deleteNode;
              }
          }

          delete[] buckets;
          buckets = nullptr;
      }
};


#endif // LOGINSYSTEM_DATABASESERVICE_H
