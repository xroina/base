/*--------1---------2---------3---------4---------5---------6---------7---*//**
 * Tuple.cc
 *
 *  Created on: 2018/08/04
 *      Author: xronia
**//*-----1---------2---------3---------4---------5---------6---------7------*/

#include <Entity/IndexerCache.h>
#include <Entity/EntityDef.h>
#include <Entity/IndexName.h>

namespace Entity {

constexpr char IndexName::ENTITY_NAME[];
constexpr char IndexNameIndexer::INDEXER_NAME[];

IndexName::IndexName() : entity_name(""), index_id(""),
            index_name(""), indexer_name(""), index_root(0) {

}
IndexName::IndexName(const entityname_t& ent, const entityname_t& id,
        const entityname_t& idx, const entityname_t& idxr,
        const rowid_t& root) : entity_name(ent), index_id(id),
                index_name(idx), indexer_name(idxr), index_root(root) {

}

IndexName::~IndexName() {

}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 *     関数名：インデックス管理マスタにパラメータを登録する
 *     (setTuple)
 * <pre>
 *
 *    １    機能
 *            インデックス管理マスタに指定したパラメータを登録する。
 *
 *    ２    引数
 *           name    : エンティティ名
 *           id      : インデックスID
 *           index   : インデックス名
 *           indexer : インデクサ名
 *           root    : インデックスルートRowID
 *
 *    ３    戻り値
 *            なし
 *
 * </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/
void IndexName::set(const entityname_t& ent, const entityname_t& id,
        const entityname_t& idx, const entityname_t& idxr, const rowid_t& root) {
    this->entity_name   = ent;
    this->index_id      = id;
    this->index_name    = idx;
    this->indexer_name  = idxr;
    this->index_root    = root;
}

IndexNameIndexer::IndexNameIndexer() {

}

IndexNameIndexer::~IndexNameIndexer() {

}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 *     関数名：ノードインデクサの比較処理 (compare)
 * <pre>
 *
 *    １    機能
 *            インデクサ比較処理
 *
 *    ２    引数
 *           obj1            : 比較対象のオブジェクト1          [入力]
 *           obj2            : 比較対象のオブジェクト2          [入力]
 *
 *    ３    戻り値
 *            比較結果
 *
 * </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/
int IndexNameIndexer::compare(const AbstEntity& o1, const AbstEntity& o2) const {

    // 比較結果を返す。
    const IndexName& t1 = static_cast<const IndexName&>(o1);
    const IndexName& t2 = static_cast<const IndexName&>(o2);
    int ret = ::strcmp(t1.entity_name.c_str(), t2.entity_name.c_str());
    if(ret == 0) ret = ::strcmp(t1.index_id.c_str(), t2.index_id.c_str());
    return ret;
}

const ::std::string IndexNameIndexer::getIndexerName() const {
    return INDEXER_NAME;
}

/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 *     関数名：ノードマッチャコンストラクタ (CNodeMatcher)
 * <pre>
 *
 *    １    機能
 *            ノードマッチャの初期化を行う
 *
 *    ２    引数
 *           name            : エンティティ名               [入力]
 *           id              : インデックス               [入力]
 *
 *    ３    戻り値
 *            なし
 *
 * </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/
IndexNameMatcher::IndexNameMatcher(const entityname_t name, const entityname_t id) :
        AbstIndexMatcher(IndexNameIndexer::INDEXER_NAME),
        entity_name(name), index_id(id) {

}

IndexNameMatcher::~IndexNameMatcher() {

}
/*--------1---------2---------3---------4---------5---------6---------7---*//**
 *
 *     関数名：ノードマッチャマッチ処理 (match)
 * <pre>
 *
 *    １    機能
 *            ノードマッチャーのマッチ処理を行う。
 *
 *    ２    引数
 *           obj            : 比較対象               [入力]
 *
 *    ３    戻り値
 *            比較結果
 *
 * </pre>
**//*-----1---------2---------3---------4---------5---------6---------7------*/
int IndexNameMatcher::match(const AbstEntity& obj) const {
    // エンティティ名の比較
    const IndexName& tpl = static_cast<const IndexName&>(obj);
    // 比較結果を返す。
    int ret = ::strcmp(tpl.entity_name.c_str(), this->entity_name.c_str());

    // エンティティ名が同一の場合、さらにインデックスIDを比較
    if(ret == 0) ret = ::strcmp(tpl.index_id.c_str(), this->index_id.c_str());
    return ret;
}

/*--------1---------2---------3---------4---------5---------6---------7------*/

const EntityCache gIndexName(
        IndexName::ENTITY_NAME, {sizeof(IndexName), {
    {"EntityName",  {Column::ASTRING,    1, OFFSET(IndexName, entity_name),  sizeof(IndexName::entity_name)}},
    {"IndexID",     {Column::ASTRING,    1, OFFSET(IndexName, index_id),     sizeof(IndexName::index_id)}},
    {"IndexName",   {Column::ASTRING,    0, OFFSET(IndexName, index_name),   sizeof(IndexName::index_name)}},
    {"IndexerName", {Column::ASTRING,    0, OFFSET(IndexName, indexer_name), sizeof(IndexName::indexer_name)}},
    {"IndexRoot",   {Column::UINT64,     0, OFFSET(IndexName, index_root),   sizeof(IndexName::index_root)}},
}});

const IndexerCache gIndexNameIndexer(new IndexNameIndexer());

                                ///< インデックス管理インデクサ定義

/*--------1---------2---------3---------4---------5---------6---------7------*/

} /* end namespace Entity */
