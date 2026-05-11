//
// Created by Oliver Šmítek on 28.11.2025.
//

#include "InsertEntity.h"
#include "../Managers/EntityManager.h"
#include <string>



void InsertEntity::insertEntity(std::string entityName, Entity* entity) {
    entityManager.uMOfEntitys[entityName] = entity;
}
