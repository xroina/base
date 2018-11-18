/*--------1---------2---------3---------4---------5---------6---------7---*//**
 * @file
 *     モジュール名：テーブル情報定義構造体ヘッダ
 * <pre>
 *
 *    １  機能
 *        テーブル情報定義構造体を定義する
 *
 *    ２  更新履歴
 *          REV001 : 新規作成
 * </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/

#include <Entity/EntityDef.h>

namespace Entity {

Column::Column(const Type type, const int key, const size_t offset, const size_t size) :
            type(type), key(key), offset(offset), size(size) {

}

Column::~Column() {

}

EntityDef::EntityDef(const size_t size, const Columns column) :
            size(size), columns(column) {

}

EntityDef::~EntityDef() {

}

/*--------1---------2---------3---------4---------5---------6---------7------*/
} // end namespace Entity

