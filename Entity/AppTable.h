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
#ifndef ENTITY_ABSTENTITY_H_
#define ENTITY_ABSTENTITY_H_

#include <String/astring.h>
#include <Entity/EntityDef.h>
#include <Entity/EntityCache.h>
#include <Exception/exception.h>
#include <cstring>
#include <climits>
#include <string>
#include <vector>
#include <algorithm>

namespace Entity {

static const size_t ENTITY_NAME_LENGTH = 64;        ///< エンティティ名の最大長
static const size_t ENTITY_NAME_LENGTH_MIN = 5;     ///< エンティティ名の最小長

typedef int64_t rowid_t;                            ///< ROW識別子型(64ビット符号あり整数)
typedef ::std::vector<rowid_t> rowid_vec_t;         ///< ROWID配列型
static const rowid_t INVALID_ROWID = LONG_LONG_MIN; ///< ROWID無効値

typedef ::String::astring<ENTITY_NAME_LENGTH> entityname_t;


class AbstEntity {
};

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
class AppTable {
private:
    const ::std::string name;
    const EntityDef& entity;
    const size_t size;
    const bool create = false;
    char* data;

    /// デフォルトコンストラクタ
    AppTable();

public:
    /// 公開コンストラクタ
    explicit AppTable(const ::std::string&);
    explicit AppTable(const ::std::string&, AbstEntity& ent);

    /// デストラクタ
    virtual ~AppTable();

    /// 名前取得
    const ::std::string& getTableName() const;

    /// サイズ取得
    const size_t getTableSize() const;

    /// データ取得
    AbstEntity& getData() const;

    /// データ設定
    template<typename Type>
    const void setData(const Type& ent) {
        if(getTableSize() != sizeof(Type))
            SIZE_MISMATCH("Entity Size UnMatch(name=" << name << ",size="
                    << size << "!=" << sizeof(Type) << ")");
        ::memcpy(data, &ent, getTableSize());
    }

    const void setData(const AbstEntity& ent);

    template<typename Type>
    const void getData(Type& ent) const {
        if(getTableSize() != sizeof(Type))
            SIZE_MISMATCH("Entity Size UnMatch(name=" << name << ",size="
                    << size << "!=" << sizeof(Type) << ")");
        ::memcpy(&ent, data, getTableSize());
    }

    template<typename Type>
    void setValue(const ::std::string& name, const Type& in) {
        auto& columns = entity.columns;
        auto member = columns.find(name);
        if(member == columns.end())
            SIZE_MISMATCH("Entity Member Not Define(name=" << name << ")");
        auto& column = member->second;
        if(column.size != sizeof(Type))
            SIZE_MISMATCH("Entity Member Size UnMatch(name=" << name << ",size="
                    << column.size << "!=" << sizeof(Type) << ")");
        ::memcpy(&data[column.offset], &in, sizeof(Type));
    }

    template<typename Type>
    void getValue(const ::std::string& name, Type& out) {
        auto& columns = entity.columns;
        auto member = columns.find(name);
        if(member == columns.end())
            NOT_DEFINE("Entity Member Not Define(name=" << name << ")");
        auto& column = member->second;
        if(column.size != sizeof(Type))
            SIZE_MISMATCH("Entity Member Size UnMatch(name=" << name << ",size="
                    << column.size << "!=" << sizeof(Type) << ")");
        ::memcpy(&out, &data[column.offset], sizeof(Type));
    }

    template<typename Type>
    Type getValue(const ::std::string& name) {
        Type value;
        getValue(name, value);
        return value;
    }

//    template<typename Type>
//    const Type& operator[](const ::std::string& name) const& {
//        return getValue<Type>(name);
//    }
//
//    template<typename Type>
//    Type& operator[](const ::std::string& name) & {
//        return getValue<Type>(name);
//    }
//
//    template<typename Type>
//    Type operator[](const ::std::string& name) const&& {
//        Type value;
//        getValue(name, value);
//        return value;
//    }
//
//    template<typename Type>
//    const Type& operator()(const ::std::string& name) const& {
//        return getValue<Type>(name);
//    }
//
//    template<typename Type>
//    Type& operator()(const ::std::string& name) & {
//        return getValue<Type>(name);
//    }

};
/*--------1---------2---------3---------4---------5---------6---------7------*/

} // end namespace Entity

#endif // ENTITY_ABSTENTITY_H_
