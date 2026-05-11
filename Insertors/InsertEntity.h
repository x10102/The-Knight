//
// Created by Oliver Šmítek on 28.11.2025.
//
#ifndef INSERTENTITY_H
#define INSERTENTITY_H
#include <string>

#include "../Managers/EntityManager.h"


class Entity;

class InsertEntity {

    InsertEntity() {}

public:
    static InsertEntity& getInstance(){
        static InsertEntity theInstance;
        return theInstance;
    }


public:
    EntityManager& entityManager = EntityManager::getInstance();

    void insertEntity(std::string entityName, Entity* entity);

};

#endif // INSERTENTITY_H
