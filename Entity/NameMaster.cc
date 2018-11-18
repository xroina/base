/*--------1---------2---------3---------4---------5---------6---------7---*//**
 * EntityNameMaster.cc
 *
 *  Created on: 2018/07/29
 *      Author: xronia
**//*-----1---------2---------3---------4---------5---------6---------7------*/

#include <Entity/EntityDef.h>
#include <Entity/NameMaster.h>

namespace Entity {

const ::std::string& NameMaster::ENTITY_NAME = "$NAME";

NameMaster::NameMaster() : name("") {

}

NameMaster::NameMaster(const ::std::string& name) : name(name) {

}

NameMaster::~NameMaster() {

}

const EntityCache gNameMaster(NameMaster::ENTITY_NAME, { sizeof(NameMaster), {
        {"Name",   {Column::ASTRING,    1, OFFSET(NameMaster, name),    sizeof(NameMaster::name)}},
}});

/*--------1---------2---------3---------4---------5---------6---------7------*/

}   // namespace SharedMemory
