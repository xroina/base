/*--------1---------2---------3---------4---------5---------6---------7---*//**
* @file
*     モジュール名：テーブル定義リポジトリ
* <pre>
*
*    １  機能
*          テーブル定義リポジトリを定義する
*
*    ２  更新履歴
*          REV001 : 新規作成
* </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/

#ifndef ENTITY_ENTITYCACHE_H_
#define ENTITY_ENTITYCACHE_H_

#include <string>
#include <map>

namespace Entity {

class EntityDef;
/*--------1---------2---------3---------4---------5---------6---------7---*//**
*
*     クラス名：テーブル定義リポジトリ
*               (CTableDefinitionRepository)
* <pre>
*
*    １    機能
*            テーブル定義リポジトリクラスを定義する
*
*    ２    履歴
*            rev001 : 新規作成
* </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/
class EntityCache {
private:
    /// テーブル定義情報格納用マップ型定義
    typedef ::std::map<::std::string, EntityDef> EntityDefs;

    /// テーブル定義情報格納用マップ
    static EntityDefs entity_cache;

public:
    EntityCache(const std::string&, const EntityDef);
    ~EntityCache();

    static EntityDef& getTableDef(const std::string&);
    static void destroy();
};

/*--------1---------2---------3---------4---------5---------6---------7------*/
} // end namespace Entity

#endif /* ENTITY_ENTITYCACHE_H_ */
