//
// Created by Cris239 on 2/22/2026.
//

#ifndef LOGINSYSTEM_DATABASESERVICE_H
#define LOGINSYSTEM_DATABASESERVICE_H

#include <string>
#include "../UserData.hpp"


class DatabaseService   //store user information, uses hash table with linked list for collision
  {
  public:
      struct UserNode
      {
          UserData data;
          UserNode* next;
          UserNode* previous;

          UserNode(UserData d) :
              data(d), next(nullptr), previous(nullptr) { }
      };

  private:
      int tableSize;
      UserNode** buckets;

      int hashKey(std::string key) const
      {
          int total = 0;
          for (int index = 0; index < key.length(); index++)
              total = total + key[index];

          return total % tableSize;
      }

  public:
      DatabaseService(int s) :
          tableSize(s)
      {
          if (tableSize <= 0)
              tableSize = 1;

          buckets = new UserNode*[tableSize];
          for (int index = 0; index < tableSize; index++)
              buckets[index] = nullptr;
      }

      DatabaseService(const DatabaseService&) = delete;
      DatabaseService& operator=(const DatabaseService&) = delete;

      void appendUser(const UserData& data)
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

      UserNode* search(const std::string& name)
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

      bool deleteUser(const std::string& name)
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

      ~DatabaseService()
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
