/*
 * CEntityCache.cpp
 *
 *  Created on: 2015/05/17
 *      Author: xronia
 */

#include <Entity/EntityDef.h>
#include <Entity/EntityCache.h>
#include <Logger/logger.h>
#include <Exception/exception.h>

namespace Entity {

using ::std::string;

// テーブル定義情報格納用マップ
EntityCache::EntityDefs EntityCache::entity_cache
    __attribute__((init_priority(101)));

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 *     関数名：テーブル定義情報登録 (setTableDefinition)
 * <pre>
 *
 *    １    機能
 *            テーブル名をキーとしてテーブル定義情報構造体を登録する。
 *
 *    ２    引数
 *            szTableName            : テーブル名         [入力]
 *            pTableDefinition       : 登録するテーブル定義情報構造体への
 *                                     ポインタ          [入力]
 *
 *    ３    戻り値
 *            なし
 *
 * </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/
EntityCache::EntityCache(const string& name, const EntityDef def) {
    entity_cache.emplace(name, def);

    INFO_LOG("エンティティ(" << name << ")を登録しました");
};

EntityCache::~EntityCache() {

}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
*
*     関数名：テーブル定義情報取得 (getTableDefinition)
* <pre>
*
*    １    機能
*            テーブル定義情報構造体をテーブル名をキーに登録する
*
*    ２    引数
*            szTableName            : テーブル名         [入力]
*    ３    戻り値
*            テーブル定義情報構造体へのポインタ
*            ※テーブル名に該当するテーブル定義情報構造体がない場合はNULL
*
*    ４    履歴
*            rev001 : 新規作成
* </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/
EntityDef& EntityCache::getTableDef(const string& name) {
    auto ret = entity_cache.find(name);
    if(ret == entity_cache.end()) NOT_DEFINE("エンティティ(" << name << ")が見つかりません");
    return ret->second;
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 *     関数名：テーブル定義情報格納用マップ開放 (destroy)
 * <pre>
 *
 *    １    機能
 *            テーブル定義情報格納用マップをクリアする。
 *
 *    ２    引数
 *            なし
 *
 *    ３    戻り値
 *            なし
 *
 *    ４    履歴
 *            rev001 : 新規作成
 * </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/
void EntityCache::destroy() {
    for(auto i = entity_cache.begin(); i != entity_cache.end(); i++) {
//        i->second.columns.clear();

        INFO_LOG("エンティティ(" << i->first << ")を開放しました");
    }
    entity_cache.clear();
}

/*--------1---------2---------3---------4---------5---------6---------7------*/

} // end namespace Entity
