
#ifndef ENTITYCOMPONENTSYSTEM_H_INCLUDED
#define ENTITYCOMPONENTSYSTEM_H_INCLUDED

#include <vector>
#include <memory>
#include <bitset>
#include <array>
#include <algorithm>
#include <iostream>
class Entity;
class Component;
class Manager;


using ComponentID = std::size_t;

using Group = std::size_t;


 inline ComponentID getNewComponentTypeID () {
    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
    static_assert(std::is_base_of<Component, T>::value, "");
    static ComponentID typeID = getNewComponentTypeID() ;
    return typeID;
}


constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component{
public:
    Entity* entity;
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}
    virtual ~Component() {}

};


class Entity{
private:
    Manager& manager;
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;
    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;

public:
    Entity(Manager& mManager) : manager(mManager) {}

     void update(){
        for (auto& c : components) c->update();
    };

     void draw(){
        for (auto& c : components) c->draw();
    };
    bool IsActive() const {return active;}
    void destroy() {active = false;}

    bool hasGroup(Group mGroup){
        return groupBitSet[mGroup];
    }
    void addGroup(Group mGroup);
    void delGroup(Group mGroup){
        groupBitSet[mGroup] = false;
    }

    template <typename T> bool hasComponent() const{
        return componentBitSet[getComponentTypeID<T>()];
    }

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs) {

    T* c(new T(std::forward<TArgs>(mArgs)...));

    c->entity = this;
    std::unique_ptr<Component> uPtr{ c };
    components.emplace_back(std::move(uPtr));

    componentArray[getComponentTypeID<T>()] = c;
    componentBitSet[getComponentTypeID<T>()] = true;

    c->init();
    return *c;
}
    template<typename T> T& getComponent() const {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }
};

class Manager {
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity*>, maxGroups> groupEntities;
public:
    void update() {
        for (auto& e : entities) e->update();
    }

    void draw() {
        for (auto& e : entities) e->draw();
    }

    void refresh() {
        for (auto i(0u); i < maxGroups; i++) {
            auto& v(groupEntities[i]);
            v.erase(
                std::remove_if(std::begin(v), std::end(v),
                    [i](Entity* mEntity) {
                        return !mEntity->IsActive() || !mEntity->hasGroup(i);
                    }),
                std::end(v));
        }

        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity>& mEntity) {
                return !mEntity->IsActive();
            }),
            std::end(entities));
    }

    void addToGroup(Entity* mEntity, Group mGroup) {
        groupEntities[mGroup].emplace_back(mEntity);
    }

    std::vector<Entity*>& getGroup(Group mGroup) {
        return groupEntities[mGroup];
    }

    Entity& addEntity() {
        Entity* e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{ e };
        entities.emplace_back(std::move(uPtr));
        return *e;
    }

    void clear() {
        entities.clear();
        for (auto& group : groupEntities) {
            group.clear();
        }
    }

    std::size_t getEntityCount() const {
    return entities.size();
    }

};


#endif // ENTITYCOMPONENTSYSTEM_H_INCLUDED
