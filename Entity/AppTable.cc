/*--------1---------2---------3---------4---------5---------6---------7---*//**
* @file
*     モジュール名：業務データクラスヘッダ
* <pre>
*
*    １  機能
*        業務データクラスを定義する
*
*    ２  更新履歴
*          REV001 : 新規作成
* </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/

#include <Entity/AppTable.h>

namespace Entity {

/*--------1---------2---------3---------4---------5---------6---------7---*//**
*
*     クラス名：業務データクラス (CApplicationData)
* <pre>
*
*    １    機能
*          業務データを管理する (業務プロセス専用)
*
*    ２    履歴
*            rev001 : 新規作成
* </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/
/// 公開コンストラクタ
AppTable::AppTable(const ::std::string& name) :
        name(name), entity(EntityCache::getTableDef(name)), size(entity.size),
        create(true), data(new char[size]) {
}

AppTable::AppTable(const ::std::string& name, AbstEntity& ent) :
        name(name), entity(EntityCache::getTableDef(name)), size(entity.size),
        create(false), data(reinterpret_cast<char*>(&ent)) {
}

/// デストラクタ
AppTable::~AppTable() {
    if(create && data != nullptr) delete data;
    data = nullptr;
}

/// 名前取得
const ::std::string& AppTable::getTableName() const {
    return name;
}

/// サイズ取得
const size_t AppTable::getTableSize() const {
    return size;
}

/// データ取得
AbstEntity& AppTable::getData() const {
    return *reinterpret_cast<AbstEntity*>(data);
}

const void AppTable::setData(const AbstEntity& ent) {
    ::memcpy(data, &ent, size);
}

/*--------1---------2---------3---------4---------5---------6---------7------*/

} // end namespace Entity
