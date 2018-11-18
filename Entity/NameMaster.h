/*--------1---------2---------3---------4---------5---------6---------7---*//**
 * EntityNameMaster.h
 *
 *  Created on: 2018/07/29
 *      Author: xronia
**//*-----1---------2---------3---------4---------5---------6---------7------*/

#ifndef ENTITY_CENTITYNAMEMASTER_H_
#define ENTITY_CENTITYNAMEMASTER_H_

#include <Entity/AppTable.h>
#include <String/astring.h>

namespace Entity {

class NameMaster : public AbstEntity {
public:
    static const ::std::string& ENTITY_NAME;
    entityname_t name;

    NameMaster();
    NameMaster(const ::std::string&);

    ~NameMaster();
};

/*--------1---------2---------3---------4---------5---------6---------7------*/

}   // end namespace Entity

#endif /* ENTITY_CENTITYNAMEMASTER_H_ */
