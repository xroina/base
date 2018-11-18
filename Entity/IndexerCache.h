/*--------1---------2---------3---------4---------5---------6---------7---*//**
* @file
*     モジュール名：共通メモリ管理機能インデクサリポジトリ
* <pre>
*    １  機能
*          共通メモリ管理機能インデクサリポジトリを定義する
*
*    ２  更新履歴
*          REV001 : 新規作成
* </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/

#ifndef ENTITY_INDEXERCACHE_H_
#define ENTITY_INDEXERCACHE_H_

#include <string>
#include <map>

namespace Entity {

class ImplIndexer;

/*--------1---------2---------3---------4---------5---------6---------7---*//**
*
*     クラス名：共通メモリ管理機能インデクサリポジトリ
*               (CIndexerRepository)
* <pre>
*
*    １    機能
*          共通メモリ管理機能インデクサリポジトリクラスを定義する
*
*    ２    履歴
*            rev001 : 新規作成
* </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/
class IndexerCache {
private:
    /// インデックスリポジトリ型
    typedef ::std::map<::std::string, const ImplIndexer*> Indexers;

    /// インデクサリポジトリ本体
    static Indexers indexer_cache;

public:
    /// コントラクタ
    IndexerCache(const ImplIndexer*);
    /// デストラクタ
    ~IndexerCache();

    /// インデクサ取得
    static const ImplIndexer& getIndexer(const ::std::string&);

    static void destroy();
};

/*--------1---------2---------3---------4---------5---------6---------7------*/
}   // end namespace Entity

#endif // ENTITY_INDEXERCACHE_H_
