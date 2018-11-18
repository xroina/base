/*--------1---------2---------3---------4---------5---------6---------7---*//**
 * @file
 *     モジュール名：共通メモリ管理機能インデクサリポジトリ
 * <pre>
 *
 *    １  機能
 *          共通メモリ管理機能インデクサリポジトリを定義する
 *
 *    ２  更新履歴
 *          REV001 : 新規作成
 * </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/
#include <Logger/logger.h>
#include <Entity/AppTable.h>
#include <Entity/ImplMatcher.h>
#include <Entity/IndexerCache.h>

namespace Entity {

using ::std::string;

IndexerCache::Indexers IndexerCache::indexer_cache
    __attribute__((init_priority(102)));

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 *     関数名：コントラクタ (CIndexerRepository)
 * <pre>
 *
 *    １    機能
 *            インデクサを指定した名称で登録する
 *
 *    ２    引数
 *            szIndexerName : インデクサ名     [入力]
 *            indexer       : CIndexerInterfaceを継承したインデクサクラス
 *                            のインスタンスへのポインタ      [入力]
 *
 *    ３    戻り値
 *            なし
 *
 *    ４    履歴
 *            REV001 : 新規作成
 * </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/
IndexerCache::IndexerCache(const ImplIndexer* idxr) {

    if(idxr == nullptr) NULLPOINTER("idxr");
    DEBUG_LOG("インデクサ(" << idxr->getIndexerName() << ")");

    indexer_cache.emplace(idxr->getIndexerName(), idxr);

    INFO_LOG("インデクサ(" << idxr->getIndexerName() << ")を登録しました");
}

IndexerCache::~IndexerCache() {

}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 *     関数名：インデクサ取得 (getIndexer)
 * <pre>
 *
 *    １    機能
 *            指定した名称からインデクサのインスタンスを取得する
 *
 *    ２    引数
 *            szIndexerName : インデクサ名     [入力]
 *
 *    ３    戻り値
 *            CIndexerInterfaceを継承したインデクサクラスのインスタンス
 *            へのポインタ
 *
 *    ４    履歴
 *            REV001 : 新規作成
 * </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/
const ImplIndexer& IndexerCache::getIndexer(const string& name) {
    auto ret = indexer_cache.find(name);
    if(ret == indexer_cache.end()) NOT_DEFINE("インデクサ(" << name << ")が見つかりません");
    return *(ret->second);
}

void IndexerCache::destroy() {
    for(auto i = indexer_cache.begin(); i != indexer_cache.end(); i++) {
        if(i->second != nullptr) { delete i->second; i->second = nullptr; }
        INFO_LOG("インデクサ(" << i->first << ")を開放しました");
    }
    indexer_cache.clear();
}

/*--------1---------2---------3---------4---------5---------6---------7------*/
}   // namespace Entity
